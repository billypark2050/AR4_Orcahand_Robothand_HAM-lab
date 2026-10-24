"""ROS 2 driver node for the ORCA Hand (wraps orca_core).

Publishes
  /joint_states                     sensor_msgs/JointState  measured, rad, "<prefix><joint>"
  ~/commanded_joint_states          sensor_msgs/JointState  what was last sent to the hand
Subscribes
  ~/joint_command                   sensor_msgs/JointState  streaming targets (rad, bare or prefixed names,
                                                            any subset of joints; cancels a running trajectory)
Action
  ~/follow_joint_trajectory         control_msgs/FollowJointTrajectory   (MoveIt hand controller)
Services (std_srvs/Trigger)
  ~/enable_torque  ~/disable_torque  ~/neutral  ~/estop  ~/reset_estop
"""
from __future__ import annotations

import math
import threading
import time

import rclpy
from control_msgs.action import FollowJointTrajectory
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup, ReentrantCallbackGroup
from rclpy.executors import ExternalShutdownException, MultiThreadedExecutor
from rclpy.logging import get_logger
from rclpy.node import Node
from sensor_msgs.msg import JointState
from std_msgs.msg import Header
from std_srvs.srv import Trigger

from orcahand_driver.hand_backend import HandBackend, HandNotReadyError


def _dur(d) -> float:
    return d.sec + d.nanosec * 1e-9


class OrcaHandDriver(Node):
    def __init__(self) -> None:
        super().__init__("orcahand_driver")
        p = self.declare_parameter
        p("config_path", "")            # '' = autodetect connected hand (orca_core.load_hand())
        p("calibration_path", "")       # '' = calibration.yaml next to config.yaml
        p("model_name", "")             # e.g. 'orcahand-right' (only used when config_path is '')
        p("mock", False)
        p("joint_prefix", "hand_")
        p("control_rate", 50.0)         # Hz: command stepping + joint_states publishing
        p("max_joint_speed_deg_s", 180.0)
        p("auto_start", True)           # torque on + control mode at startup (never calibrates)
        p("move_to_neutral_on_start", True)
        p("disable_torque_on_shutdown", True)
        p("joint_states_topic", "/joint_states")
        p("goal_tolerance_deg", 15.0)   # tendon hands under load do not track tightly
        p("strict_goal_check", False)   # True: abort the action if the final error exceeds tolerance
        p("goal_settle_time", 0.5)

        g = lambda n: self.get_parameter(n).value  # noqa: E731
        self.backend = HandBackend.from_orca_core(
            config_path=g("config_path"), calibration_path=g("calibration_path"),
            model_name=g("model_name"), mock=g("mock"),
            prefix=g("joint_prefix"), max_speed_deg_s=float(g("max_joint_speed_deg_s")))
        self.get_logger().info(self.backend.connect())
        try:
            if g("auto_start"):
                self.backend.start(move_to_neutral=g("move_to_neutral_on_start"))
                self.get_logger().info("hand initialised, torque ON")
            else:
                self.backend.ensure_calibrated()
                self.get_logger().warn("auto_start=false: torque OFF, call ~/enable_torque to control")
        except Exception:
            self.backend.shutdown(disable_torque=True)  # release the serial port
            raise

        self._dt = 1.0 / float(g("control_rate"))
        self._traj_lock = threading.Lock()
        self._active_goal_id = None

        loop_group = MutuallyExclusiveCallbackGroup()
        cb_group = ReentrantCallbackGroup()
        self._js_pub = self.create_publisher(JointState, g("joint_states_topic"), 10)
        self._cmd_pub = self.create_publisher(JointState, "~/commanded_joint_states", 10)
        self.create_subscription(JointState, "~/joint_command", self._on_command, 10,
                                 callback_group=cb_group)
        for name, fn in (("enable_torque", self._srv_enable), ("disable_torque", self._srv_disable),
                         ("neutral", self._srv_neutral), ("estop", self._srv_estop),
                         ("reset_estop", self._srv_reset_estop)):
            self.create_service(Trigger, f"~/{name}", fn, callback_group=cb_group)
        self._action = ActionServer(
            self, FollowJointTrajectory, "~/follow_joint_trajectory",
            execute_callback=self._execute_traj, goal_callback=self._on_goal,
            cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb_group)
        self._last_tick = time.monotonic()
        self.create_timer(self._dt, self._tick, callback_group=loop_group)

    # ------------------------------------------------------------ loop
    def _tick(self) -> None:
        now = time.monotonic()
        # a late tick must not turn into one big jump
        dt, self._last_tick = min(now - self._last_tick, 3.0 * self._dt), now
        try:
            sent = self.backend.step(dt)
            names, pos = self.backend.read_rad()
        except Exception as e:  # bus errors must not kill the node
            self.get_logger().error(f"hand IO error: {e}", throttle_duration_sec=2.0)
            return
        stamp = self.get_clock().now().to_msg()
        self._js_pub.publish(JointState(header=self._hdr(stamp), name=names, position=pos))
        if sent:
            self._cmd_pub.publish(JointState(
                header=self._hdr(stamp), name=[self.backend.ros_name(j) for j in sent],
                position=[math.radians(v) for v in sent.values()]))

    @staticmethod
    def _hdr(stamp):
        return Header(stamp=stamp)

    # ------------------------------------------------------------ streaming
    def _on_command(self, msg: JointState) -> None:
        if len(msg.position) != len(msg.name):
            self.get_logger().warn("joint_command: name/position size mismatch, ignored")
            return
        # Keep only this hand's joints. Names of other joints (e.g. the arm's joint_1..6 from a
        # GUI that publishes the whole robot) are ignored instead of rejecting the whole message.
        pairs = [(n, p) for n, p in zip(msg.name, msg.position) if self.backend.core_name(n) is not None]
        ignored = [n for n in msg.name if self.backend.core_name(n) is None]
        if ignored:
            self.get_logger().warn(f"joint_command: ignoring non-hand joints {ignored}",
                                   throttle_duration_sec=5.0)
        if not pairs:
            return
        try:
            target = self.backend.to_core_deg([n for n, _ in pairs], [p for _, p in pairs])
        except ValueError as e:
            self.get_logger().warn(f"joint_command rejected: {e}")
            return
        with self._traj_lock:
            self._active_goal_id = None  # preempts a running trajectory
        self.backend.set_target_deg(target)

    # ------------------------------------------------------------ trajectories
    def _on_goal(self, goal) -> GoalResponse:
        if not self.backend.torque_enabled or self.backend.estopped:
            self.get_logger().warn("trajectory rejected: torque off or e-stop latched")
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _execute_traj(self, goal_handle):
        req = goal_handle.request.trajectory
        result = FollowJointTrajectory.Result()
        try:
            traj = self.backend.make_trajectory(
                req.joint_names, [(_dur(pt.time_from_start), pt.positions) for pt in req.points])
        except ValueError as e:
            goal_handle.abort()
            result.error_code = FollowJointTrajectory.Result.INVALID_JOINTS
            result.error_string = str(e)
            return result

        gid = bytes(goal_handle.goal_id.uuid)
        with self._traj_lock:
            self._active_goal_id = gid
        t0 = time.monotonic()
        settle = float(self.get_parameter("goal_settle_time").value)
        while rclpy.ok():
            with self._traj_lock:
                preempted = self._active_goal_id != gid
            if goal_handle.is_cancel_requested or preempted:
                self.backend.hold_current()
                if goal_handle.is_cancel_requested:
                    goal_handle.canceled()
                else:
                    goal_handle.abort()
                result.error_string = "canceled" if goal_handle.is_cancel_requested else "preempted"
                return result
            if not self.backend.torque_enabled or self.backend.estopped:
                goal_handle.abort()
                result.error_code = FollowJointTrajectory.Result.PATH_TOLERANCE_VIOLATED
                result.error_string = "torque disabled / e-stop during execution"
                return result
            t = time.monotonic() - t0
            self.backend.set_target_deg(traj.sample(t))
            if t > traj.duration + settle:
                break
            time.sleep(self._dt)

        final = traj.sample(traj.duration)
        meas = self.backend.read_deg()
        err = max(abs(meas[j] - v) for j, v in final.items() if j in meas)
        tol = float(self.get_parameter("goal_tolerance_deg").value)
        with self._traj_lock:
            if self._active_goal_id == gid:
                self._active_goal_id = None
        if err > tol:
            msg = f"final joint error {err:.1f} deg > tolerance {tol:.1f} deg"
            if self.get_parameter("strict_goal_check").value:
                goal_handle.abort()
                result.error_code = FollowJointTrajectory.Result.GOAL_TOLERANCE_VIOLATED
                result.error_string = msg
                return result
            self.get_logger().warn(msg + " (strict_goal_check=false, reporting success)")
        goal_handle.succeed()
        result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
        return result

    # ------------------------------------------------------------ services
    def _wrap(self, res, fn, ok_msg):
        try:
            fn()
            res.success, res.message = True, ok_msg
        except (HandNotReadyError, Exception) as e:
            res.success, res.message = False, str(e)
        return res

    def _srv_enable(self, _req, res):
        return self._wrap(res, lambda: self.backend.set_torque(True), "torque ON")

    def _srv_disable(self, _req, res):
        return self._wrap(res, lambda: self.backend.set_torque(False), "torque OFF")

    def _srv_estop(self, _req, res):
        with self._traj_lock:
            self._active_goal_id = None
        return self._wrap(res, self.backend.estop, "E-STOP: torque OFF, latched")

    def _srv_reset_estop(self, _req, res):
        return self._wrap(res, self.backend.reset_estop, "e-stop cleared (torque still OFF)")

    def _srv_neutral(self, _req, res):
        neutral = {j: float(v) for j, v in self.backend.hand.config.neutral_position.items()}
        return self._wrap(res, lambda: self.backend.set_target_deg(neutral), "moving to neutral")

    # ------------------------------------------------------------ shutdown
    def close(self) -> None:
        try:
            self.backend.shutdown(bool(self.get_parameter("disable_torque_on_shutdown").value))
        except Exception as e:
            self.get_logger().error(f"shutdown: {e}")


def main(args=None) -> None:
    rclpy.init(args=args)
    node = None
    try:
        node = OrcaHandDriver()
        executor = MultiThreadedExecutor(num_threads=4)
        executor.add_node(node)
        executor.spin()
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    except HandNotReadyError as e:
        get_logger("orcahand_driver").fatal(str(e))
    finally:
        if node is not None:
            node.close()
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()

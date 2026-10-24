"""Relay ONE joint_state_publisher_gui window (arm + hand sliders) to the two controllers.

    jsp_gui (full arm+hand URDF) --/slider_gui/joint_states--> slider_relay
        hand joints ("<hand_prefix>*")  -> /orcahand_driver/joint_command          (JointState)
        arm joints  (joint_1..6)        -> /joint_trajectory_controller/joint_trajectory
                                           (JointTrajectory, one point, arm_move_time s)

Only sliders that actually MOVED are forwarded, so
  * starting the GUI (it publishes its centred defaults) does not make the robot jump,
  * the robot is not re-commanded every 100 ms while you leave the sliders alone,
    so hand_pose / send_goal / MoveIt still work alongside the GUI.
The trajectory controller needs all 6 arm joints: the ones you did not move are
filled in with their current measured position from /joint_states.
"""
from __future__ import annotations

import rclpy
from builtin_interfaces.msg import Duration
from rclpy.node import Node
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

ARM_JOINTS = [f"joint_{i}" for i in range(1, 7)]


class SliderDiff:
    """ROS-free core: which slider values changed since the last message."""

    def __init__(self, eps: float = 1e-4):
        self.eps = eps
        self.last: dict[str, float] | None = None

    def update(self, names, positions) -> dict[str, float]:
        cur = dict(zip(names, positions))
        if self.last is None:          # first message = GUI defaults -> baseline only
            self.last = cur
            return {}
        moved = {n: p for n, p in cur.items()
                 if n not in self.last or abs(p - self.last[n]) > self.eps}
        self.last = cur
        return moved


def arm_goal(moved: dict[str, float], measured: dict[str, float], arm_joints) -> list[float] | None:
    """Full 6-joint target: moved sliders + measured positions for the rest (None if impossible)."""
    if not any(j in moved for j in arm_joints):
        return None
    out = []
    for j in arm_joints:
        if j in moved:
            out.append(moved[j])
        elif j in measured:
            out.append(measured[j])
        else:
            return None                # no state for an untouched joint yet
    return out


class SliderRelay(Node):
    def __init__(self) -> None:
        super().__init__("slider_relay")
        self.declare_parameter("hand_prefix", "hand_")
        self.declare_parameter("tf_prefix", "")
        self.declare_parameter("arm_move_time", 0.5)   # s per slider step (smaller = snappier)
        self.hand_prefix = self.get_parameter("hand_prefix").value
        tfp = self.get_parameter("tf_prefix").value
        self.arm_joints = [tfp + j for j in ARM_JOINTS]
        self.move_time = float(self.get_parameter("arm_move_time").value)

        self.diff = SliderDiff()
        self.measured: dict[str, float] = {}
        self.hand_pub = self.create_publisher(JointState, "/orcahand_driver/joint_command", 10)
        self.arm_pub = self.create_publisher(
            JointTrajectory, "/joint_trajectory_controller/joint_trajectory", 10)
        self.create_subscription(JointState, "/joint_states", self._on_state, 10)
        self.create_subscription(JointState, "/slider_gui/joint_states", self._on_slider, 10)
        self.get_logger().info("slider relay ready: move a slider to command arm / hand")

    def _on_state(self, msg: JointState) -> None:
        for n, p in zip(msg.name, msg.position):
            if n in self.arm_joints:
                self.measured[n] = p

    def _on_slider(self, msg: JointState) -> None:
        moved = self.diff.update(msg.name, msg.position)
        if not moved:
            return
        hand = {n: p for n, p in moved.items() if n.startswith(self.hand_prefix)}
        if hand:
            self.hand_pub.publish(JointState(name=list(hand), position=list(hand.values())))
        goal = arm_goal(moved, self.measured, self.arm_joints)
        if goal is not None:
            sec = int(self.move_time)
            pt = JointTrajectoryPoint(
                positions=goal,
                time_from_start=Duration(sec=sec, nanosec=int((self.move_time - sec) * 1e9)))
            self.arm_pub.publish(JointTrajectory(joint_names=self.arm_joints, points=[pt]))
        elif any(j in moved for j in self.arm_joints):
            self.get_logger().warn("arm slider moved but /joint_states has no arm state yet",
                                   throttle_duration_sec=2.0)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = SliderRelay()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()

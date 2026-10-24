"""AR4 + ORCA Hand: both drivers, one robot_state_publisher, one RViz.

  AR4  : ros2_control_node (annin_ar4_driver HW plugin or mock) + joint_state_broadcaster
         + joint_trajectory_controller           -> publishes arm joints on /joint_states
  Hand : orcahand_driver (orca_core)              -> publishes hand joints on /joint_states
  RSP  : combined URDF (ar4_orca_description)    -> TF for everything -> RViz

Examples
  # no hardware at all
  ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true
  # + MoveIt: drag the goal in RViz, Plan & Execute (arm and/or hand)
  ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true moveit:=true
  # one slider window for arm + hand (needs both controllers running)
  ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true gui:=true
  # real robot (first run after power-up: calibrate:=True)
  ros2 launch ar4_orca_bringup bringup.launch.py calibrate:=True \
      hand_config_path:=$HOME/RobotHand/orcahand/orca_core/orca_core/models/v2/orcahand-right/config.yaml
  # manual finger sliders (streams to the hand while open; close it before running trajectories)
  ... hand_gui:=true
"""
import os
import tempfile

from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, IncludeLaunchDescription, LogInfo, OpaqueFunction,
                            RegisterEventHandler)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit
from launch.substitutions import (Command, FindExecutable, LaunchConfiguration,
                                  PathJoinSubstitution, PythonExpression)
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterFile, ParameterValue
from launch_ros.substitutions import FindPackageShare

ARGS = [
    ("ar_model", "mk5", "AR4 model (mk1..mk5)"),
    ("arm_mock", "false", "true: ros2_control mock hardware instead of the Teensy"),
    ("calibrate", "True", "AR4 limit-switch calibration on startup (needed after power cycle)"),
    ("serial_port", "/dev/ttyACM0", "AR4 Teensy serial port"),
    ("tf_prefix", "", "AR4 tf prefix"),
    ("hand_mock", "false", "true: orca_core MockOrcaHand instead of the real hand"),
    ("hand_config_path", "", "orca_core config.yaml the hand was CALIBRATED with "
                         "('' = orca_core/models/v2/orcahand-<side>/config.yaml if calibrated, else autodetect)"),
    ("hand_side", "right", "right | left"),
    ("hand_prefix", "hand_", "prefix of hand joint/link names"),
    ("hand_auto_start", "true", "torque on + neutral at startup (never calibrates)"),
    ("mount_config", "", "mounting parts + hand pose yaml ('' = ar4_orca_description/config/mount.yaml)"),
    ("rviz", "true", "start RViz (plain RobotModel view; replaced by the MoveIt RViz when moveit:=true)"),
    ("moveit", "false", "also start move_group + RViz MotionPlanning (ar4_orca_moveit_config)"),
    ("hand_gui", "false", "joint_state_publisher_gui streaming to the hand"),
    ("gui", "false", "ONE slider window for arm + hand (jsp_gui + slider_relay -> both controllers)"),
    ("arm_move_time", "0.5", "gui:=true: seconds the arm takes per slider step"),
]


def _hand_gui(context, *_):
    """jsp_gui with a hand-only URDF, its output remapped to the driver's command topic."""
    import xacro

    lc = lambda n: LaunchConfiguration(n).perform(context)  # noqa: E731
    if lc("hand_gui").lower() != "true":
        return []
    urdf = xacro.process_file(
        os.path.join(FindPackageShare("orcahand_ros_description").perform(context),
                     "urdf", "orcahand.urdf.xacro"),
        mappings={"side": lc("hand_side"), "prefix": lc("hand_prefix")}).toxml()
    path = os.path.join(tempfile.gettempdir(), "orcahand_gui.urdf")
    with open(path, "w") as f:
        f.write(urdf)
    return [Node(package="joint_state_publisher_gui", executable="joint_state_publisher_gui",
                 name="hand_slider_gui", arguments=[path],
                 remappings=[("joint_states", "/orcahand_driver/joint_command"),
                             # use ONLY the hand URDF file above: otherwise jsp_gui also picks up the
                             # combined /robot_description (arm + hand) and starts sending joint_1..6
                             ("robot_description", "/hand_slider_gui/robot_description")])]


def _full_gui(context, *_):
    """Arm + hand sliders in one jsp_gui window; slider_relay splits them per controller."""
    lc = lambda n: LaunchConfiguration(n).perform(context)  # noqa: E731
    if lc("gui").lower() != "true":
        return []
    if lc("hand_gui").lower() == "true":
        raise RuntimeError("use either gui:=true (arm + hand) or hand_gui:=true (hand only), not both")
    return [
        # reads the combined /robot_description topic -> sliders for joint_1..6 AND all hand joints.
        # Its output goes to the relay, NOT to /joint_states (that is owned by the controllers).
        Node(package="joint_state_publisher_gui", executable="joint_state_publisher_gui",
             name="slider_gui", remappings=[("joint_states", "/slider_gui/joint_states")]),
        Node(package="orcahand_driver", executable="slider_relay", name="slider_relay",
             output="screen",
             parameters=[{"hand_prefix": lc("hand_prefix"), "tf_prefix": lc("tf_prefix"),
                          "arm_move_time": float(lc("arm_move_time"))}]),
    ]


def _calibrated_hand_config(side):
    """orca_core's packaged config.yaml for this side IF its calibration.yaml says calibrated.

    orca_core's calibration (orca_ui Setup tab / calibrate.py) writes calibration.yaml next to
    the config.yaml it ran with, i.e. orca_core/models/v2/orcahand-<side>/ for the editable
    install. Pinning that file avoids autodetect picking another bundled model
    (e.g. orcahand-touch-<side>) that has no calibration.
    """
    try:
        import orca_core
        import yaml
    except ImportError:
        return "", "orca_core not importable from launch"
    cfg = os.path.join(os.path.dirname(orca_core.__file__), "models", "v2", f"orcahand-{side}", "config.yaml")
    cal = os.path.join(os.path.dirname(cfg), "calibration.yaml")
    if not os.path.exists(cal):
        return "", f"no calibration.yaml at {cal}"
    with open(cal) as f:
        data = yaml.safe_load(f) or {}
    if not data.get("calibrated"):
        return "", f"{cal} exists but calibrated != true"
    return cfg, cal


def _hand_driver(context, *_):
    lc = lambda n: LaunchConfiguration(n).perform(context)  # noqa: E731
    mock = lc("hand_mock").lower() == "true"
    side = lc("hand_side")
    config_path = lc("hand_config_path")
    actions = []
    if mock:
        # mock: ignore the real hand's calibration.yaml (its motor limits are outside the
        # mock motors' +-1 rad travel -> garbage joint angles). A missing file makes
        # orca_core synthesise a consistent mock calibration in memory, so its
        # "not fully calibrated" warnings at start-up are expected here.
        calibration_path = os.path.join(tempfile.gettempdir(), "orcahand_mock_no_calibration.yaml")
        actions.append(LogInfo(msg="[hand] MOCK: real calibration.yaml ignored, synthetic mock calibration used"))
    else:
        calibration_path = ""  # '' = calibration.yaml next to config.yaml
        if not config_path:
            config_path, info = _calibrated_hand_config(side)
            if config_path:
                actions.append(LogInfo(msg=f"[hand] REAL: using calibrated config {config_path} (calibration: {info})"))
            else:
                actions.append(LogInfo(msg=f"[hand] REAL: WARNING no calibrated packaged config ({info}); "
                                           "falling back to hardware autodetect"))
        else:
            actions.append(LogInfo(msg=f"[hand] REAL: using hand_config_path {config_path}"))
    actions.append(Node(
        package="orcahand_driver", executable="orcahand_driver", name="orcahand_driver",
        output="screen",
        emulate_tty=True,                          # show orca_core print() output when it happens,
        additional_env={"PYTHONUNBUFFERED": "1"},  # not all at once on shutdown
        parameters=[
            os.path.join(FindPackageShare("orcahand_driver").perform(context),
                         "config", "orcahand_driver.yaml"),
            {
                "config_path": config_path,
                # mock has no hardware to autodetect: name the packaged model for the side
                "model_name": f"orcahand-{side}" if (mock and not config_path) else "",
                "mock": mock,
                "calibration_path": calibration_path,
                "joint_prefix": lc("hand_prefix"),
                "auto_start": lc("hand_auto_start").lower() == "true",
            },
        ]))
    return actions


def generate_launch_description():
    lc = LaunchConfiguration
    desc_pkg = FindPackageShare("ar4_orca_description")

    xacro_cmd = [PathJoinSubstitution([FindExecutable(name="xacro")]), " ",
                 PathJoinSubstitution([desc_pkg, "urdf", "ar4_orca.urdf.xacro"]),
                 " include_ros2_control:=true", " use_mock_hardware:=", lc("arm_mock")]
    for k in ("ar_model", "calibrate", "serial_port", "hand_side", "hand_prefix"):
        xacro_cmd += [f" {k}:=", lc(k)]
    mount_config = PythonExpression([
        "'", lc("mount_config"), "' or '",
        PathJoinSubstitution([desc_pkg, "config", "mount.yaml"]), "'"])
    xacro_cmd += [" tf_prefix:='", lc("tf_prefix"), "'", " mount_config:=", mount_config]
    robot_description = {"robot_description": ParameterValue(Command(xacro_cmd), value_type=str)}

    rsp = Node(package="robot_state_publisher", executable="robot_state_publisher",
               output="both", parameters=[robot_description])

    controller_manager = Node(
        package="controller_manager", executable="ros2_control_node", output="screen",
        parameters=[robot_description,
                    ParameterFile(PathJoinSubstitution([FindPackageShare("annin_ar4_driver"),
                                                        "config", "controllers.yaml"]),
                                  allow_substs=True),
                    {"tf_prefix": lc("tf_prefix")}])

    def spawner(name):
        return Node(package="controller_manager", executable="spawner",
                    arguments=[name, "-c", "/controller_manager",
                               "--controller-manager-timeout", "120"])

    jsb = spawner("joint_state_broadcaster")
    jtc = spawner("joint_trajectory_controller")

    rviz = Node(package="rviz2", executable="rviz2", output="log",
                arguments=["-d", PathJoinSubstitution([FindPackageShare("ar4_orca_bringup"),
                                                       "rviz", "ar4_orca.rviz"])],
                condition=IfCondition(PythonExpression([
                    "'", lc("rviz"), "'.lower() == 'true' and '", lc("moveit"), "'.lower() != 'true'"])))

    moveit = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(PathJoinSubstitution(
            [FindPackageShare("ar4_orca_moveit_config"), "launch", "moveit.launch.py"])),
        launch_arguments={"ar_model": lc("ar_model"), "tf_prefix": lc("tf_prefix"),
                          "hand_side": lc("hand_side"), "hand_prefix": lc("hand_prefix"),
                          "mount_config": lc("mount_config"), "rviz": lc("rviz")}.items(),
        condition=IfCondition(lc("moveit")))

    return LaunchDescription(
        [DeclareLaunchArgument(n, default_value=d, description=h) for n, d, h in ARGS] + [
            rsp,
            controller_manager,
            jsb,
            # start the trajectory controller only once the broadcaster is up
            RegisterEventHandler(OnProcessExit(target_action=jsb, on_exit=[jtc])),
            OpaqueFunction(function=_hand_driver),
            rviz,
            # MoveIt waits for the trajectory controller so its first planning-scene state is complete
            RegisterEventHandler(OnProcessExit(target_action=jtc, on_exit=[moveit])),
            OpaqueFunction(function=_hand_gui),
            OpaqueFunction(function=_full_gui),
        ])

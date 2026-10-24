"""MoveIt for AR4 mk5 + ORCA Hand: move_group + RViz MotionPlanning.

Run it ON TOP of the hardware/mock bringup (which owns the controllers and /joint_states):

  # terminal 1 (mock or real, see ar4_orca_bringup)
  ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true rviz:=false
  # terminal 2
  ros2 launch ar4_orca_moveit_config moveit.launch.py

or in one go:  ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true moveit:=true

Planning groups (srdf/ar4_orca.srdf.xacro)
  ar_manipulator  joint_1..6, IK tip = <hand_prefix>tower  -> /joint_trajectory_controller/follow_joint_trajectory
  orca_hand       17 hand joints                           -> /orcahand_driver/follow_joint_trajectory
"""
import os

import xacro
import yaml
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

ARGS = [
    ("ar_model", "mk5", "AR4 model"),
    ("tf_prefix", "", "AR4 tf prefix (must match the bringup)"),
    ("hand_side", "right", "right | left"),
    ("hand_prefix", "hand_", "prefix of hand joint/link names (must match the bringup)"),
    ("mount_config", "", "mount yaml ('' = ar4_orca_description/config/mount.yaml)"),
    ("rviz", "true", "start RViz with the MotionPlanning panel"),
    ("use_sim_time", "false", "use /clock"),
]

PKG = "ar4_orca_moveit_config"
DEFAULT_TFP, DEFAULT_HP = "", "hand_"


def _load(name):
    with open(os.path.join(get_package_share_directory(PKG), "config", name)) as f:
        return yaml.safe_load(f)


def _rename(joint, tfp, hp):
    """Default-prefixed joint name in the config files -> the prefixes in use."""
    if joint.startswith(DEFAULT_HP):
        return hp + joint[len(DEFAULT_HP):]
    return tfp + joint


def _setup(context, *_):
    lc = lambda n: LaunchConfiguration(n).perform(context)  # noqa: E731
    tfp, hp = lc("tf_prefix"), lc("hand_prefix")
    use_sim_time = lc("use_sim_time").lower() == "true"

    desc_share = get_package_share_directory("ar4_orca_description")
    mount = lc("mount_config") or os.path.join(desc_share, "config", "mount.yaml")
    urdf = xacro.process_file(
        os.path.join(desc_share, "urdf", "ar4_orca.urdf.xacro"),
        mappings={"ar_model": lc("ar_model"), "tf_prefix": tfp, "hand_side": lc("hand_side"),
                  "hand_prefix": hp, "mount_config": mount,
                  "include_ros2_control": "false"}).toxml()
    srdf = xacro.process_file(
        os.path.join(get_package_share_directory(PKG), "srdf", "ar4_orca.srdf.xacro"),
        mappings={"tf_prefix": tfp, "hand_prefix": hp}).toxml()

    robot_description = {"robot_description": urdf}
    robot_description_semantic = {"robot_description_semantic": srdf}
    kinematics = {"robot_description_kinematics": _load("kinematics.yaml")}

    limits = _load("joint_limits.yaml")
    limits["joint_limits"] = {_rename(j, tfp, hp): v for j, v in limits["joint_limits"].items()}
    planning_limits = {"robot_description_planning": limits}

    controllers = _load("moveit_controllers.yaml")
    mscm = controllers["moveit_simple_controller_manager"]
    for name in mscm["controller_names"]:
        mscm[name]["joints"] = [_rename(j, tfp, hp) for j in mscm[name]["joints"]]

    planning_pipelines = {
        "default_planning_pipeline": "ompl",
        "planning_pipelines": ["ompl", "pilz"],
        "ompl": _load("ompl_planning.yaml"),
        "pilz": _load("pilz_planning.yaml"),
    }
    execution = {
        "moveit_controller_manager": "moveit_simple_controller_manager/MoveItSimpleControllerManager",
        "moveit_manage_controllers": False,
        "trajectory_execution.allowed_execution_duration_scaling": 1.5,
        "trajectory_execution.allowed_goal_duration_margin": 1.0,
        # the tendon hand does not track tightly; the arm keeps a strict start check in practice
        "trajectory_execution.allowed_start_tolerance": 0.05,
    }
    scene = {
        "publish_planning_scene": True,
        "publish_geometry_updates": True,
        "publish_state_updates": True,
        "publish_transforms_updates": True,
        "publish_robot_description_semantic": True,
    }
    common = [robot_description, robot_description_semantic, kinematics, {"use_sim_time": use_sim_time}]

    nodes = [Node(
        package="moveit_ros_move_group", executable="move_group", output="screen",
        parameters=common + [planning_limits, planning_pipelines, execution, controllers, scene])]
    if lc("rviz").lower() == "true":
        nodes.append(Node(
            package="rviz2", executable="rviz2", output="log",
            arguments=["-d", os.path.join(get_package_share_directory(PKG), "rviz", "ar4_orca_moveit.rviz")],
            parameters=common + [planning_pipelines]))
    return nodes


def generate_launch_description():
    return LaunchDescription(
        [DeclareLaunchArgument(n, default_value=d, description=h) for n, d, h in ARGS]
        + [OpaqueFunction(function=_setup)])

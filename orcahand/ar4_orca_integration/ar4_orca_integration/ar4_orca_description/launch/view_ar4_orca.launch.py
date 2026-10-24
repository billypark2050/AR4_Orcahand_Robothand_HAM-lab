"""Visual check of the combined model with joint sliders (no hardware).

ros2 launch ar4_orca_description view_ar4_orca.launch.py
ros2 launch ar4_orca_description view_ar4_orca.launch.py mount_config:=$HOME/my_mount.yaml
"""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare

ARGS = {
    "ar_model": "mk5",
    "hand_side": "right",
    "hand_prefix": "hand_",
    "mount_config": "",   # '' = ar4_orca_description/config/mount.yaml
    "gui": "true",
}


def _mount_config():
    from launch.substitutions import PythonExpression
    return PythonExpression([
        "'", LaunchConfiguration("mount_config"), "' or '",
        PathJoinSubstitution([FindPackageShare("ar4_orca_description"), "config", "mount.yaml"]), "'"])


def generate_launch_description():
    pkg = FindPackageShare("ar4_orca_description")
    cmd = [PathJoinSubstitution([FindExecutable(name="xacro")]), " ",
           PathJoinSubstitution([pkg, "urdf", "ar4_orca.urdf.xacro"]),
           " include_ros2_control:=false"]
    for k in ("ar_model", "hand_side", "hand_prefix"):
        cmd += [f" {k}:=", LaunchConfiguration(k)]
    cmd += [" mount_config:=", _mount_config()]
    robot_description = ParameterValue(Command(cmd), value_type=str)

    return LaunchDescription(
        [DeclareLaunchArgument(k, default_value=v) for k, v in ARGS.items()] + [
            Node(package="robot_state_publisher", executable="robot_state_publisher",
                 parameters=[{"robot_description": robot_description}]),
            Node(package="joint_state_publisher_gui", executable="joint_state_publisher_gui",
                 condition=IfCondition(LaunchConfiguration("gui"))),
            Node(package="rviz2", executable="rviz2",
                 arguments=["-d", PathJoinSubstitution([pkg, "rviz", "ar4_orca.rviz"])]),
        ])

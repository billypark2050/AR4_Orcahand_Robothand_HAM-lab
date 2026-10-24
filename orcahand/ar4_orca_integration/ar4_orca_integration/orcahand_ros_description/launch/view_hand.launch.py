"""View the ORCA hand alone with joint sliders: ros2 launch orcahand_ros_description view_hand.launch.py side:=right"""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    side = LaunchConfiguration("side")
    prefix = LaunchConfiguration("prefix")
    gui = LaunchConfiguration("gui")
    pkg = FindPackageShare("orcahand_ros_description")

    robot_description = ParameterValue(Command([
        PathJoinSubstitution([FindExecutable(name="xacro")]), " ",
        PathJoinSubstitution([pkg, "urdf", "orcahand.urdf.xacro"]),
        " side:=", side, " prefix:=", prefix,
    ]), value_type=str)

    return LaunchDescription([
        DeclareLaunchArgument("side", default_value="right", choices=["right", "left"]),
        DeclareLaunchArgument("prefix", default_value="hand_"),
        DeclareLaunchArgument("gui", default_value="true"),
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             parameters=[{"robot_description": robot_description}]),
        Node(package="joint_state_publisher_gui", executable="joint_state_publisher_gui",
             condition=IfCondition(gui)),
        Node(package="rviz2", executable="rviz2",
             arguments=["-d", PathJoinSubstitution([pkg, "rviz", "view_hand.rviz"])]),
    ])

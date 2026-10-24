"""ORCA hand driver alone.

ros2 launch orcahand_driver orcahand_driver.launch.py config_path:=/path/to/orcahand-right/config.yaml
ros2 launch orcahand_driver orcahand_driver.launch.py mock:=true
"""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    lc = LaunchConfiguration
    return LaunchDescription([
        DeclareLaunchArgument("config_path", default_value=""),
        DeclareLaunchArgument("mock", default_value="false"),
        DeclareLaunchArgument("joint_prefix", default_value="hand_"),
        DeclareLaunchArgument("auto_start", default_value="true"),
        Node(
            package="orcahand_driver", executable="orcahand_driver", name="orcahand_driver",
            output="screen",
            parameters=[
                PathJoinSubstitution([FindPackageShare("orcahand_driver"), "config", "orcahand_driver.yaml"]),
                {
                    "config_path": ParameterValue(lc("config_path"), value_type=str),
                    "mock": ParameterValue(lc("mock"), value_type=bool),
                    "joint_prefix": ParameterValue(lc("joint_prefix"), value_type=str),
                    "auto_start": ParameterValue(lc("auto_start"), value_type=bool),
                },
            ],
        ),
    ])

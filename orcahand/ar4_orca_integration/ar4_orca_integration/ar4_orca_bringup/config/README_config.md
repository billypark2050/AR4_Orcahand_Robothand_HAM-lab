MoveIt for this setup lives in its own package: `ar4_orca_moveit_config`
(SRDF with `ar_manipulator` + `orca_hand` groups, limits, OMPL/Pilz, and the controller map
arm -> /joint_trajectory_controller/follow_joint_trajectory, hand -> /orcahand_driver/follow_joint_trajectory).

    ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true moveit:=true

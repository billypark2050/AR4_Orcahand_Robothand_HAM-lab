cmake_minimum_required(VERSION 3.8)
project(ar4_orca_moveit_config)

find_package(ament_cmake REQUIRED)

install(DIRECTORY launch config srdf rviz
  DESTINATION share/${PROJECT_NAME})

ament_package()

cmake_minimum_required(VERSION 3.8)
project(ar4_orca_description)

find_package(ament_cmake REQUIRED)

install(DIRECTORY urdf launch rviz config meshes
  DESTINATION share/${PROJECT_NAME})

install(PROGRAMS scripts/check_model.py
  DESTINATION lib/${PROJECT_NAME})

ament_package()

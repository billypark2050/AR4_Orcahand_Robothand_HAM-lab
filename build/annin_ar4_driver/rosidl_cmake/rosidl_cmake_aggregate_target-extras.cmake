# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target annin_ar4_driver::annin_ar4_driver
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${annin_ar4_driver_TARGETS}.
if(annin_ar4_driver_TARGETS AND NOT TARGET annin_ar4_driver::annin_ar4_driver)
  add_library(annin_ar4_driver::annin_ar4_driver INTERFACE IMPORTED)
  set_target_properties(annin_ar4_driver::annin_ar4_driver PROPERTIES
    INTERFACE_LINK_LIBRARIES "${annin_ar4_driver_TARGETS}")
endif()

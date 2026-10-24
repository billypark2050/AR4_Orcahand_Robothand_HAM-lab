# generated from ament_cmake_export_targets/cmake/ament_cmake_export_targets-extras.cmake.in

set(_exported_targets "export_annin_ar4_driver__rosidl_generator_c;export_annin_ar4_driver__rosidl_typesupport_fastrtps_c;annin_ar4_driver__rosidl_typesupport_introspection_c;annin_ar4_driver__rosidl_typesupport_c;export_annin_ar4_driver__rosidl_generator_cpp;export_annin_ar4_driver__rosidl_typesupport_fastrtps_cpp;annin_ar4_driver__rosidl_typesupport_introspection_cpp;annin_ar4_driver__rosidl_typesupport_cpp;export_annin_ar4_driver__rosidl_generator_py;export_annin_ar4_driver_hw")

# include all exported targets
if(NOT _exported_targets STREQUAL "")
  foreach(_target ${_exported_targets})
    set(_export_file "${annin_ar4_driver_DIR}/${_target}Export.cmake")
    include("${_export_file}")

    # extract the target names associated with the export
    set(_regex "foreach\\((_cmake)?_expected_?[Tt]arget (IN ITEMS )?(.+)\\)")
    file(
      STRINGS "${_export_file}" _foreach_targets
      REGEX "${_regex}")
    list(LENGTH _foreach_targets _matches)
    if(NOT _matches EQUAL 1)
      message(FATAL_ERROR
        "Failed to find exported target names in '${_export_file}'")
    endif()
    string(REGEX REPLACE "${_regex}" "\\3" _targets "${_foreach_targets}")
    string(REPLACE " " ";" _targets "${_targets}")
    list(LENGTH _targets _length)

    list(APPEND annin_ar4_driver_TARGETS ${_targets})
  endforeach()
endif()

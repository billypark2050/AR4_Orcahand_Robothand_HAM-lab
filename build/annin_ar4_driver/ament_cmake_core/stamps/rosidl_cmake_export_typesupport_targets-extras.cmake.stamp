# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_generator_c:annin_ar4_driver__rosidl_generator_c;__rosidl_typesupport_fastrtps_c:annin_ar4_driver__rosidl_typesupport_fastrtps_c;__rosidl_typesupport_introspection_c:annin_ar4_driver__rosidl_typesupport_introspection_c;__rosidl_typesupport_c:annin_ar4_driver__rosidl_typesupport_c;__rosidl_generator_cpp:annin_ar4_driver__rosidl_generator_cpp;__rosidl_typesupport_fastrtps_cpp:annin_ar4_driver__rosidl_typesupport_fastrtps_cpp;__rosidl_typesupport_introspection_cpp:annin_ar4_driver__rosidl_typesupport_introspection_cpp;__rosidl_typesupport_cpp:annin_ar4_driver__rosidl_typesupport_cpp;:annin_ar4_driver__rosidl_generator_py")

# populate annin_ar4_driver_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "annin_ar4_driver::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'annin_ar4_driver' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND annin_ar4_driver_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()

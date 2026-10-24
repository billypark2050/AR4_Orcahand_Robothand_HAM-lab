#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "annin_ar4_driver::annin_ar4_driver_hw" for configuration ""
set_property(TARGET annin_ar4_driver::annin_ar4_driver_hw APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(annin_ar4_driver::annin_ar4_driver_hw PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libannin_ar4_driver_hw.so"
  IMPORTED_SONAME_NOCONFIG "libannin_ar4_driver_hw.so"
  )

list(APPEND _cmake_import_check_targets annin_ar4_driver::annin_ar4_driver_hw )
list(APPEND _cmake_import_check_files_for_annin_ar4_driver::annin_ar4_driver_hw "${_IMPORT_PREFIX}/lib/libannin_ar4_driver_hw.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

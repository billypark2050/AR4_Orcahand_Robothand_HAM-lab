// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

#ifndef ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "annin_ar4_driver/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_serialize(
  const annin_ar4_driver::srv::CalibrateMask_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  annin_ar4_driver::srv::CalibrateMask_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
get_serialized_size(
  const annin_ar4_driver::srv::CalibrateMask_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
max_serialized_size_CalibrateMask_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_serialize_key(
  const annin_ar4_driver::srv::CalibrateMask_Request & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
get_serialized_size_key(
  const annin_ar4_driver::srv::CalibrateMask_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
max_serialized_size_key_CalibrateMask_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "annin_ar4_driver/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_serialize(
  const annin_ar4_driver::srv::CalibrateMask_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  annin_ar4_driver::srv::CalibrateMask_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
get_serialized_size(
  const annin_ar4_driver::srv::CalibrateMask_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
max_serialized_size_CalibrateMask_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_serialize_key(
  const annin_ar4_driver::srv::CalibrateMask_Response & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
get_serialized_size_key(
  const annin_ar4_driver::srv::CalibrateMask_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
max_serialized_size_key_CalibrateMask_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask_Response)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "annin_ar4_driver/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_serialize(
  const annin_ar4_driver::srv::CalibrateMask_Event & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  annin_ar4_driver::srv::CalibrateMask_Event & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
get_serialized_size(
  const annin_ar4_driver::srv::CalibrateMask_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
max_serialized_size_CalibrateMask_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
cdr_serialize_key(
  const annin_ar4_driver::srv::CalibrateMask_Event & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
get_serialized_size_key(
  const annin_ar4_driver::srv::CalibrateMask_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
max_serialized_size_key_CalibrateMask_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask_Event)();

#ifdef __cplusplus
}
#endif

#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "annin_ar4_driver/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_annin_ar4_driver
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask)();

#ifdef __cplusplus
}
#endif

#endif  // ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

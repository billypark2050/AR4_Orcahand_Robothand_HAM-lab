// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "annin_ar4_driver/srv/detail/calibrate_mask__rosidl_typesupport_introspection_c.h"
#include "annin_ar4_driver/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"
#include "annin_ar4_driver/srv/detail/calibrate_mask__struct.h"


// Include directives for member types
// Member `mask`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  annin_ar4_driver__srv__CalibrateMask_Request__init(message_memory);
}

void annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_fini_function(void * message_memory)
{
  annin_ar4_driver__srv__CalibrateMask_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_member_array[1] = {
  {
    "mask",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(annin_ar4_driver__srv__CalibrateMask_Request, mask),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_members = {
  "annin_ar4_driver__srv",  // message namespace
  "CalibrateMask_Request",  // message name
  1,  // number of fields
  sizeof(annin_ar4_driver__srv__CalibrateMask_Request),
  false,  // has_any_key_member_
  annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_member_array,  // message members
  annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_type_support_handle = {
  0,
  &annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_members,
  get_message_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Request__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask_Request__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_annin_ar4_driver
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Request)() {
  if (!annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_type_support_handle.typesupport_identifier) {
    annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__rosidl_typesupport_introspection_c.h"
// already included above
// #include "annin_ar4_driver/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  annin_ar4_driver__srv__CalibrateMask_Response__init(message_memory);
}

void annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_fini_function(void * message_memory)
{
  annin_ar4_driver__srv__CalibrateMask_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(annin_ar4_driver__srv__CalibrateMask_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(annin_ar4_driver__srv__CalibrateMask_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_members = {
  "annin_ar4_driver__srv",  // message namespace
  "CalibrateMask_Response",  // message name
  2,  // number of fields
  sizeof(annin_ar4_driver__srv__CalibrateMask_Response),
  false,  // has_any_key_member_
  annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_member_array,  // message members
  annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle = {
  0,
  &annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_members,
  get_message_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Response__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask_Response__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_annin_ar4_driver
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Response)() {
  if (!annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle.typesupport_identifier) {
    annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__rosidl_typesupport_introspection_c.h"
// already included above
// #include "annin_ar4_driver/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "annin_ar4_driver/srv/calibrate_mask.h"
// Member `request`
// Member `response`
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  annin_ar4_driver__srv__CalibrateMask_Event__init(message_memory);
}

void annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_fini_function(void * message_memory)
{
  annin_ar4_driver__srv__CalibrateMask_Event__fini(message_memory);
}

size_t annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__size_function__CalibrateMask_Event__request(
  const void * untyped_member)
{
  const annin_ar4_driver__srv__CalibrateMask_Request__Sequence * member =
    (const annin_ar4_driver__srv__CalibrateMask_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_const_function__CalibrateMask_Event__request(
  const void * untyped_member, size_t index)
{
  const annin_ar4_driver__srv__CalibrateMask_Request__Sequence * member =
    (const annin_ar4_driver__srv__CalibrateMask_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_function__CalibrateMask_Event__request(
  void * untyped_member, size_t index)
{
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence * member =
    (annin_ar4_driver__srv__CalibrateMask_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__fetch_function__CalibrateMask_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const annin_ar4_driver__srv__CalibrateMask_Request * item =
    ((const annin_ar4_driver__srv__CalibrateMask_Request *)
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_const_function__CalibrateMask_Event__request(untyped_member, index));
  annin_ar4_driver__srv__CalibrateMask_Request * value =
    (annin_ar4_driver__srv__CalibrateMask_Request *)(untyped_value);
  *value = *item;
}

void annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__assign_function__CalibrateMask_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  annin_ar4_driver__srv__CalibrateMask_Request * item =
    ((annin_ar4_driver__srv__CalibrateMask_Request *)
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_function__CalibrateMask_Event__request(untyped_member, index));
  const annin_ar4_driver__srv__CalibrateMask_Request * value =
    (const annin_ar4_driver__srv__CalibrateMask_Request *)(untyped_value);
  *item = *value;
}

bool annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__resize_function__CalibrateMask_Event__request(
  void * untyped_member, size_t size)
{
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence * member =
    (annin_ar4_driver__srv__CalibrateMask_Request__Sequence *)(untyped_member);
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence__fini(member);
  return annin_ar4_driver__srv__CalibrateMask_Request__Sequence__init(member, size);
}

size_t annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__size_function__CalibrateMask_Event__response(
  const void * untyped_member)
{
  const annin_ar4_driver__srv__CalibrateMask_Response__Sequence * member =
    (const annin_ar4_driver__srv__CalibrateMask_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_const_function__CalibrateMask_Event__response(
  const void * untyped_member, size_t index)
{
  const annin_ar4_driver__srv__CalibrateMask_Response__Sequence * member =
    (const annin_ar4_driver__srv__CalibrateMask_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_function__CalibrateMask_Event__response(
  void * untyped_member, size_t index)
{
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence * member =
    (annin_ar4_driver__srv__CalibrateMask_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__fetch_function__CalibrateMask_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const annin_ar4_driver__srv__CalibrateMask_Response * item =
    ((const annin_ar4_driver__srv__CalibrateMask_Response *)
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_const_function__CalibrateMask_Event__response(untyped_member, index));
  annin_ar4_driver__srv__CalibrateMask_Response * value =
    (annin_ar4_driver__srv__CalibrateMask_Response *)(untyped_value);
  *value = *item;
}

void annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__assign_function__CalibrateMask_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  annin_ar4_driver__srv__CalibrateMask_Response * item =
    ((annin_ar4_driver__srv__CalibrateMask_Response *)
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_function__CalibrateMask_Event__response(untyped_member, index));
  const annin_ar4_driver__srv__CalibrateMask_Response * value =
    (const annin_ar4_driver__srv__CalibrateMask_Response *)(untyped_value);
  *item = *value;
}

bool annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__resize_function__CalibrateMask_Event__response(
  void * untyped_member, size_t size)
{
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence * member =
    (annin_ar4_driver__srv__CalibrateMask_Response__Sequence *)(untyped_member);
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence__fini(member);
  return annin_ar4_driver__srv__CalibrateMask_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(annin_ar4_driver__srv__CalibrateMask_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(annin_ar4_driver__srv__CalibrateMask_Event, request),  // bytes offset in struct
    NULL,  // default value
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__size_function__CalibrateMask_Event__request,  // size() function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_const_function__CalibrateMask_Event__request,  // get_const(index) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_function__CalibrateMask_Event__request,  // get(index) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__fetch_function__CalibrateMask_Event__request,  // fetch(index, &value) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__assign_function__CalibrateMask_Event__request,  // assign(index, value) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__resize_function__CalibrateMask_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(annin_ar4_driver__srv__CalibrateMask_Event, response),  // bytes offset in struct
    NULL,  // default value
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__size_function__CalibrateMask_Event__response,  // size() function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_const_function__CalibrateMask_Event__response,  // get_const(index) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__get_function__CalibrateMask_Event__response,  // get(index) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__fetch_function__CalibrateMask_Event__response,  // fetch(index, &value) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__assign_function__CalibrateMask_Event__response,  // assign(index, value) function pointer
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__resize_function__CalibrateMask_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_members = {
  "annin_ar4_driver__srv",  // message namespace
  "CalibrateMask_Event",  // message name
  3,  // number of fields
  sizeof(annin_ar4_driver__srv__CalibrateMask_Event),
  false,  // has_any_key_member_
  annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_member_array,  // message members
  annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_type_support_handle = {
  0,
  &annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_members,
  get_message_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Event__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask_Event__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_annin_ar4_driver
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Event)() {
  annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Request)();
  annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Response)();
  if (!annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_type_support_handle.typesupport_identifier) {
    annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "annin_ar4_driver/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_members = {
  "annin_ar4_driver__srv",  // service namespace
  "CalibrateMask",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_type_support_handle,
  NULL,  // response message
  // annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle
  NULL  // event_message
  // annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle
};


static rosidl_service_type_support_t annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_type_support_handle = {
  0,
  &annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_members,
  get_service_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Request__rosidl_typesupport_introspection_c__CalibrateMask_Request_message_type_support_handle,
  &annin_ar4_driver__srv__CalibrateMask_Response__rosidl_typesupport_introspection_c__CalibrateMask_Response_message_type_support_handle,
  &annin_ar4_driver__srv__CalibrateMask_Event__rosidl_typesupport_introspection_c__CalibrateMask_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    annin_ar4_driver,
    srv,
    CalibrateMask
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    annin_ar4_driver,
    srv,
    CalibrateMask
  ),
  &annin_ar4_driver__srv__CalibrateMask__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_annin_ar4_driver
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask)(void) {
  if (!annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_type_support_handle.typesupport_identifier) {
    annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, annin_ar4_driver, srv, CalibrateMask_Event)()->data;
  }

  return &annin_ar4_driver__srv__detail__calibrate_mask__rosidl_typesupport_introspection_c__CalibrateMask_service_type_support_handle;
}

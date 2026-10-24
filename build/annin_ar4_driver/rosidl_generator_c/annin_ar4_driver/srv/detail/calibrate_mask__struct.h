// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "annin_ar4_driver/srv/calibrate_mask.h"


#ifndef ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__STRUCT_H_
#define ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'mask'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/CalibrateMask in the package annin_ar4_driver.
typedef struct annin_ar4_driver__srv__CalibrateMask_Request
{
  rosidl_runtime_c__String mask;
} annin_ar4_driver__srv__CalibrateMask_Request;

// Struct for a sequence of annin_ar4_driver__srv__CalibrateMask_Request.
typedef struct annin_ar4_driver__srv__CalibrateMask_Request__Sequence
{
  annin_ar4_driver__srv__CalibrateMask_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} annin_ar4_driver__srv__CalibrateMask_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/CalibrateMask in the package annin_ar4_driver.
typedef struct annin_ar4_driver__srv__CalibrateMask_Response
{
  bool success;
  rosidl_runtime_c__String message;
} annin_ar4_driver__srv__CalibrateMask_Response;

// Struct for a sequence of annin_ar4_driver__srv__CalibrateMask_Response.
typedef struct annin_ar4_driver__srv__CalibrateMask_Response__Sequence
{
  annin_ar4_driver__srv__CalibrateMask_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} annin_ar4_driver__srv__CalibrateMask_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  annin_ar4_driver__srv__CalibrateMask_Event__request__MAX_SIZE = 1
};
// response
enum
{
  annin_ar4_driver__srv__CalibrateMask_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/CalibrateMask in the package annin_ar4_driver.
typedef struct annin_ar4_driver__srv__CalibrateMask_Event
{
  service_msgs__msg__ServiceEventInfo info;
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence request;
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence response;
} annin_ar4_driver__srv__CalibrateMask_Event;

// Struct for a sequence of annin_ar4_driver__srv__CalibrateMask_Event.
typedef struct annin_ar4_driver__srv__CalibrateMask_Event__Sequence
{
  annin_ar4_driver__srv__CalibrateMask_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} annin_ar4_driver__srv__CalibrateMask_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__STRUCT_H_

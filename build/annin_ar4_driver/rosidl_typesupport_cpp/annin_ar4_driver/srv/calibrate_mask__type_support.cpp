// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"
#include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _CalibrateMask_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CalibrateMask_Request_type_support_ids_t;

static const _CalibrateMask_Request_type_support_ids_t _CalibrateMask_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CalibrateMask_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CalibrateMask_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CalibrateMask_Request_type_support_symbol_names_t _CalibrateMask_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, annin_ar4_driver, srv, CalibrateMask_Request)),
  }
};

typedef struct _CalibrateMask_Request_type_support_data_t
{
  void * data[2];
} _CalibrateMask_Request_type_support_data_t;

static _CalibrateMask_Request_type_support_data_t _CalibrateMask_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CalibrateMask_Request_message_typesupport_map = {
  2,
  "annin_ar4_driver",
  &_CalibrateMask_Request_message_typesupport_ids.typesupport_identifier[0],
  &_CalibrateMask_Request_message_typesupport_symbol_names.symbol_name[0],
  &_CalibrateMask_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CalibrateMask_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CalibrateMask_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Request__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask_Request__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Request>()
{
  return &::annin_ar4_driver::srv::rosidl_typesupport_cpp::CalibrateMask_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, annin_ar4_driver, srv, CalibrateMask_Request)() {
  return get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _CalibrateMask_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CalibrateMask_Response_type_support_ids_t;

static const _CalibrateMask_Response_type_support_ids_t _CalibrateMask_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CalibrateMask_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CalibrateMask_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CalibrateMask_Response_type_support_symbol_names_t _CalibrateMask_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, annin_ar4_driver, srv, CalibrateMask_Response)),
  }
};

typedef struct _CalibrateMask_Response_type_support_data_t
{
  void * data[2];
} _CalibrateMask_Response_type_support_data_t;

static _CalibrateMask_Response_type_support_data_t _CalibrateMask_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CalibrateMask_Response_message_typesupport_map = {
  2,
  "annin_ar4_driver",
  &_CalibrateMask_Response_message_typesupport_ids.typesupport_identifier[0],
  &_CalibrateMask_Response_message_typesupport_symbol_names.symbol_name[0],
  &_CalibrateMask_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CalibrateMask_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CalibrateMask_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Response__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask_Response__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Response>()
{
  return &::annin_ar4_driver::srv::rosidl_typesupport_cpp::CalibrateMask_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, annin_ar4_driver, srv, CalibrateMask_Response)() {
  return get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _CalibrateMask_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CalibrateMask_Event_type_support_ids_t;

static const _CalibrateMask_Event_type_support_ids_t _CalibrateMask_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CalibrateMask_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CalibrateMask_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CalibrateMask_Event_type_support_symbol_names_t _CalibrateMask_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, annin_ar4_driver, srv, CalibrateMask_Event)),
  }
};

typedef struct _CalibrateMask_Event_type_support_data_t
{
  void * data[2];
} _CalibrateMask_Event_type_support_data_t;

static _CalibrateMask_Event_type_support_data_t _CalibrateMask_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CalibrateMask_Event_message_typesupport_map = {
  2,
  "annin_ar4_driver",
  &_CalibrateMask_Event_message_typesupport_ids.typesupport_identifier[0],
  &_CalibrateMask_Event_message_typesupport_symbol_names.symbol_name[0],
  &_CalibrateMask_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CalibrateMask_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CalibrateMask_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &annin_ar4_driver__srv__CalibrateMask_Event__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask_Event__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Event>()
{
  return &::annin_ar4_driver::srv::rosidl_typesupport_cpp::CalibrateMask_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, annin_ar4_driver, srv, CalibrateMask_Event)() {
  return get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace annin_ar4_driver
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _CalibrateMask_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CalibrateMask_type_support_ids_t;

static const _CalibrateMask_type_support_ids_t _CalibrateMask_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CalibrateMask_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CalibrateMask_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CalibrateMask_type_support_symbol_names_t _CalibrateMask_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, annin_ar4_driver, srv, CalibrateMask)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, annin_ar4_driver, srv, CalibrateMask)),
  }
};

typedef struct _CalibrateMask_type_support_data_t
{
  void * data[2];
} _CalibrateMask_type_support_data_t;

static _CalibrateMask_type_support_data_t _CalibrateMask_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CalibrateMask_service_typesupport_map = {
  2,
  "annin_ar4_driver",
  &_CalibrateMask_service_typesupport_ids.typesupport_identifier[0],
  &_CalibrateMask_service_typesupport_symbol_names.symbol_name[0],
  &_CalibrateMask_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t CalibrateMask_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CalibrateMask_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<annin_ar4_driver::srv::CalibrateMask_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<annin_ar4_driver::srv::CalibrateMask>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<annin_ar4_driver::srv::CalibrateMask>,
  &annin_ar4_driver__srv__CalibrateMask__get_type_hash,
  &annin_ar4_driver__srv__CalibrateMask__get_type_description,
  &annin_ar4_driver__srv__CalibrateMask__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<annin_ar4_driver::srv::CalibrateMask>()
{
  return &::annin_ar4_driver::srv::rosidl_typesupport_cpp::CalibrateMask_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, annin_ar4_driver, srv, CalibrateMask)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<annin_ar4_driver::srv::CalibrateMask>();
}

#ifdef __cplusplus
}
#endif

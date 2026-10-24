// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "annin_ar4_driver/srv/calibrate_mask.hpp"


#ifndef ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__TRAITS_HPP_
#define ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace annin_ar4_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const CalibrateMask_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: mask
  {
    out << "mask: ";
    rosidl_generator_traits::value_to_yaml(msg.mask, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CalibrateMask_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mask
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mask: ";
    rosidl_generator_traits::value_to_yaml(msg.mask, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CalibrateMask_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_generator_traits
{

[[deprecated("use annin_ar4_driver::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const annin_ar4_driver::srv::CalibrateMask_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  annin_ar4_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use annin_ar4_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const annin_ar4_driver::srv::CalibrateMask_Request & msg)
{
  return annin_ar4_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<annin_ar4_driver::srv::CalibrateMask_Request>()
{
  return "annin_ar4_driver::srv::CalibrateMask_Request";
}

template<>
inline const char * name<annin_ar4_driver::srv::CalibrateMask_Request>()
{
  return "annin_ar4_driver/srv/CalibrateMask_Request";
}

template<>
struct has_fixed_size<annin_ar4_driver::srv::CalibrateMask_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<annin_ar4_driver::srv::CalibrateMask_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace annin_ar4_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const CalibrateMask_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CalibrateMask_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CalibrateMask_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_generator_traits
{

[[deprecated("use annin_ar4_driver::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const annin_ar4_driver::srv::CalibrateMask_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  annin_ar4_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use annin_ar4_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const annin_ar4_driver::srv::CalibrateMask_Response & msg)
{
  return annin_ar4_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<annin_ar4_driver::srv::CalibrateMask_Response>()
{
  return "annin_ar4_driver::srv::CalibrateMask_Response";
}

template<>
inline const char * name<annin_ar4_driver::srv::CalibrateMask_Response>()
{
  return "annin_ar4_driver/srv/CalibrateMask_Response";
}

template<>
struct has_fixed_size<annin_ar4_driver::srv::CalibrateMask_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<annin_ar4_driver::srv::CalibrateMask_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace annin_ar4_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const CalibrateMask_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CalibrateMask_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CalibrateMask_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace annin_ar4_driver

namespace rosidl_generator_traits
{

[[deprecated("use annin_ar4_driver::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const annin_ar4_driver::srv::CalibrateMask_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  annin_ar4_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use annin_ar4_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const annin_ar4_driver::srv::CalibrateMask_Event & msg)
{
  return annin_ar4_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<annin_ar4_driver::srv::CalibrateMask_Event>()
{
  return "annin_ar4_driver::srv::CalibrateMask_Event";
}

template<>
inline const char * name<annin_ar4_driver::srv::CalibrateMask_Event>()
{
  return "annin_ar4_driver/srv/CalibrateMask_Event";
}

template<>
struct has_fixed_size<annin_ar4_driver::srv::CalibrateMask_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Event>
  : std::integral_constant<bool, has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Request>::value && has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<annin_ar4_driver::srv::CalibrateMask_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<annin_ar4_driver::srv::CalibrateMask>()
{
  return "annin_ar4_driver::srv::CalibrateMask";
}

template<>
inline const char * name<annin_ar4_driver::srv::CalibrateMask>()
{
  return "annin_ar4_driver/srv/CalibrateMask";
}

template<>
struct has_fixed_size<annin_ar4_driver::srv::CalibrateMask>
  : std::integral_constant<
    bool,
    has_fixed_size<annin_ar4_driver::srv::CalibrateMask_Request>::value &&
    has_fixed_size<annin_ar4_driver::srv::CalibrateMask_Response>::value
  >
{
};

template<>
struct has_bounded_size<annin_ar4_driver::srv::CalibrateMask>
  : std::integral_constant<
    bool,
    has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Request>::value &&
    has_bounded_size<annin_ar4_driver::srv::CalibrateMask_Response>::value
  >
{
};

template<>
struct is_service<annin_ar4_driver::srv::CalibrateMask>
  : std::true_type
{
};

template<>
struct is_service_request<annin_ar4_driver::srv::CalibrateMask_Request>
  : std::true_type
{
};

template<>
struct is_service_response<annin_ar4_driver::srv::CalibrateMask_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__TRAITS_HPP_

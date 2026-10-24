// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "annin_ar4_driver/srv/calibrate_mask.hpp"


#ifndef ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__BUILDER_HPP_
#define ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "annin_ar4_driver/srv/detail/calibrate_mask__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace annin_ar4_driver
{

namespace srv
{

namespace builder
{

class Init_CalibrateMask_Request_mask
{
public:
  Init_CalibrateMask_Request_mask()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::annin_ar4_driver::srv::CalibrateMask_Request mask(::annin_ar4_driver::srv::CalibrateMask_Request::_mask_type arg)
  {
    msg_.mask = std::move(arg);
    return std::move(msg_);
  }

private:
  ::annin_ar4_driver::srv::CalibrateMask_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::annin_ar4_driver::srv::CalibrateMask_Request>()
{
  return annin_ar4_driver::srv::builder::Init_CalibrateMask_Request_mask();
}

}  // namespace annin_ar4_driver


namespace annin_ar4_driver
{

namespace srv
{

namespace builder
{

class Init_CalibrateMask_Response_message
{
public:
  explicit Init_CalibrateMask_Response_message(::annin_ar4_driver::srv::CalibrateMask_Response & msg)
  : msg_(msg)
  {}
  ::annin_ar4_driver::srv::CalibrateMask_Response message(::annin_ar4_driver::srv::CalibrateMask_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::annin_ar4_driver::srv::CalibrateMask_Response msg_;
};

class Init_CalibrateMask_Response_success
{
public:
  Init_CalibrateMask_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CalibrateMask_Response_message success(::annin_ar4_driver::srv::CalibrateMask_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_CalibrateMask_Response_message(msg_);
  }

private:
  ::annin_ar4_driver::srv::CalibrateMask_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::annin_ar4_driver::srv::CalibrateMask_Response>()
{
  return annin_ar4_driver::srv::builder::Init_CalibrateMask_Response_success();
}

}  // namespace annin_ar4_driver


namespace annin_ar4_driver
{

namespace srv
{

namespace builder
{

class Init_CalibrateMask_Event_response
{
public:
  explicit Init_CalibrateMask_Event_response(::annin_ar4_driver::srv::CalibrateMask_Event & msg)
  : msg_(msg)
  {}
  ::annin_ar4_driver::srv::CalibrateMask_Event response(::annin_ar4_driver::srv::CalibrateMask_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::annin_ar4_driver::srv::CalibrateMask_Event msg_;
};

class Init_CalibrateMask_Event_request
{
public:
  explicit Init_CalibrateMask_Event_request(::annin_ar4_driver::srv::CalibrateMask_Event & msg)
  : msg_(msg)
  {}
  Init_CalibrateMask_Event_response request(::annin_ar4_driver::srv::CalibrateMask_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_CalibrateMask_Event_response(msg_);
  }

private:
  ::annin_ar4_driver::srv::CalibrateMask_Event msg_;
};

class Init_CalibrateMask_Event_info
{
public:
  Init_CalibrateMask_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CalibrateMask_Event_request info(::annin_ar4_driver::srv::CalibrateMask_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_CalibrateMask_Event_request(msg_);
  }

private:
  ::annin_ar4_driver::srv::CalibrateMask_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::annin_ar4_driver::srv::CalibrateMask_Event>()
{
  return annin_ar4_driver::srv::builder::Init_CalibrateMask_Event_info();
}

}  // namespace annin_ar4_driver

#endif  // ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__BUILDER_HPP_

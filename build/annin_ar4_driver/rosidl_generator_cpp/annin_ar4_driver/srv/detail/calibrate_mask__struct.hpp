// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "annin_ar4_driver/srv/calibrate_mask.hpp"


#ifndef ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__STRUCT_HPP_
#define ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Request __attribute__((deprecated))
#else
# define DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Request __declspec(deprecated)
#endif

namespace annin_ar4_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CalibrateMask_Request_
{
  using Type = CalibrateMask_Request_<ContainerAllocator>;

  explicit CalibrateMask_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mask = "";
    }
  }

  explicit CalibrateMask_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : mask(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mask = "";
    }
  }

  // field types and members
  using _mask_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mask_type mask;

  // setters for named parameter idiom
  Type & set__mask(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mask = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Request
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Request
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalibrateMask_Request_ & other) const
  {
    if (this->mask != other.mask) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalibrateMask_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalibrateMask_Request_

// alias to use template instance with default allocator
using CalibrateMask_Request =
  annin_ar4_driver::srv::CalibrateMask_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace annin_ar4_driver


#ifndef _WIN32
# define DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Response __attribute__((deprecated))
#else
# define DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Response __declspec(deprecated)
#endif

namespace annin_ar4_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CalibrateMask_Response_
{
  using Type = CalibrateMask_Response_<ContainerAllocator>;

  explicit CalibrateMask_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit CalibrateMask_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Response
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Response
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalibrateMask_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalibrateMask_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalibrateMask_Response_

// alias to use template instance with default allocator
using CalibrateMask_Response =
  annin_ar4_driver::srv::CalibrateMask_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace annin_ar4_driver


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Event __attribute__((deprecated))
#else
# define DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Event __declspec(deprecated)
#endif

namespace annin_ar4_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CalibrateMask_Event_
{
  using Type = CalibrateMask_Event_<ContainerAllocator>;

  explicit CalibrateMask_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit CalibrateMask_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<annin_ar4_driver::srv::CalibrateMask_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<annin_ar4_driver::srv::CalibrateMask_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Event
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__annin_ar4_driver__srv__CalibrateMask_Event
    std::shared_ptr<annin_ar4_driver::srv::CalibrateMask_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalibrateMask_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalibrateMask_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalibrateMask_Event_

// alias to use template instance with default allocator
using CalibrateMask_Event =
  annin_ar4_driver::srv::CalibrateMask_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace annin_ar4_driver

namespace annin_ar4_driver
{

namespace srv
{

struct CalibrateMask
{
  using Request = annin_ar4_driver::srv::CalibrateMask_Request;
  using Response = annin_ar4_driver::srv::CalibrateMask_Response;
  using Event = annin_ar4_driver::srv::CalibrateMask_Event;
};

}  // namespace srv

}  // namespace annin_ar4_driver

#endif  // ANNIN_AR4_DRIVER__SRV__DETAIL__CALIBRATE_MASK__STRUCT_HPP_

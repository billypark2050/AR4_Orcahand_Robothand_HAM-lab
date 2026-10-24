#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "annin_ar4_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__annin_ar4_driver__srv__CalibrateMask_Request() -> *const std::ffi::c_void;
}

#[link(name = "annin_ar4_driver__rosidl_generator_c")]
extern "C" {
    fn annin_ar4_driver__srv__CalibrateMask_Request__init(msg: *mut CalibrateMask_Request) -> bool;
    fn annin_ar4_driver__srv__CalibrateMask_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CalibrateMask_Request>, size: usize) -> bool;
    fn annin_ar4_driver__srv__CalibrateMask_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CalibrateMask_Request>);
    fn annin_ar4_driver__srv__CalibrateMask_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CalibrateMask_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<CalibrateMask_Request>) -> bool;
}

// Corresponds to annin_ar4_driver__srv__CalibrateMask_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CalibrateMask_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mask: rosidl_runtime_rs::String,

}



impl Default for CalibrateMask_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !annin_ar4_driver__srv__CalibrateMask_Request__init(&mut msg as *mut _) {
        panic!("Call to annin_ar4_driver__srv__CalibrateMask_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CalibrateMask_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { annin_ar4_driver__srv__CalibrateMask_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { annin_ar4_driver__srv__CalibrateMask_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { annin_ar4_driver__srv__CalibrateMask_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CalibrateMask_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CalibrateMask_Request where Self: Sized {
  const TYPE_NAME: &'static str = "annin_ar4_driver/srv/CalibrateMask_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__annin_ar4_driver__srv__CalibrateMask_Request() }
  }
}


#[link(name = "annin_ar4_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__annin_ar4_driver__srv__CalibrateMask_Response() -> *const std::ffi::c_void;
}

#[link(name = "annin_ar4_driver__rosidl_generator_c")]
extern "C" {
    fn annin_ar4_driver__srv__CalibrateMask_Response__init(msg: *mut CalibrateMask_Response) -> bool;
    fn annin_ar4_driver__srv__CalibrateMask_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CalibrateMask_Response>, size: usize) -> bool;
    fn annin_ar4_driver__srv__CalibrateMask_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CalibrateMask_Response>);
    fn annin_ar4_driver__srv__CalibrateMask_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CalibrateMask_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<CalibrateMask_Response>) -> bool;
}

// Corresponds to annin_ar4_driver__srv__CalibrateMask_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CalibrateMask_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for CalibrateMask_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !annin_ar4_driver__srv__CalibrateMask_Response__init(&mut msg as *mut _) {
        panic!("Call to annin_ar4_driver__srv__CalibrateMask_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CalibrateMask_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { annin_ar4_driver__srv__CalibrateMask_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { annin_ar4_driver__srv__CalibrateMask_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { annin_ar4_driver__srv__CalibrateMask_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CalibrateMask_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CalibrateMask_Response where Self: Sized {
  const TYPE_NAME: &'static str = "annin_ar4_driver/srv/CalibrateMask_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__annin_ar4_driver__srv__CalibrateMask_Response() }
  }
}






#[link(name = "annin_ar4_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__annin_ar4_driver__srv__CalibrateMask() -> *const std::ffi::c_void;
}

// Corresponds to annin_ar4_driver__srv__CalibrateMask
#[allow(missing_docs, non_camel_case_types)]
pub struct CalibrateMask;

impl rosidl_runtime_rs::Service for CalibrateMask {
    type Request = CalibrateMask_Request;
    type Response = CalibrateMask_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__annin_ar4_driver__srv__CalibrateMask() }
    }
}



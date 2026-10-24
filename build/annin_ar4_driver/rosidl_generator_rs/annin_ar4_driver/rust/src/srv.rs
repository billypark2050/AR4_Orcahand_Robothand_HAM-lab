#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to annin_ar4_driver__srv__CalibrateMask_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CalibrateMask_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mask: std::string::String,

}



impl Default for CalibrateMask_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CalibrateMask_Request::default())
  }
}

impl rosidl_runtime_rs::Message for CalibrateMask_Request {
  type RmwMsg = super::srv::rmw::CalibrateMask_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mask: msg.mask.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mask: msg.mask.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mask: msg.mask.to_string(),
    }
  }
}


// Corresponds to annin_ar4_driver__srv__CalibrateMask_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CalibrateMask_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for CalibrateMask_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::CalibrateMask_Response::default())
  }
}

impl rosidl_runtime_rs::Message for CalibrateMask_Response {
  type RmwMsg = super::srv::rmw::CalibrateMask_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
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



// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from annin_ar4_driver:srv/CalibrateMask.idl
// generated code does not contain a copyright notice
#include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `mask`
#include "rosidl_runtime_c/string_functions.h"

bool
annin_ar4_driver__srv__CalibrateMask_Request__init(annin_ar4_driver__srv__CalibrateMask_Request * msg)
{
  if (!msg) {
    return false;
  }
  // mask
  if (!rosidl_runtime_c__String__init(&msg->mask)) {
    annin_ar4_driver__srv__CalibrateMask_Request__fini(msg);
    return false;
  }
  return true;
}

void
annin_ar4_driver__srv__CalibrateMask_Request__fini(annin_ar4_driver__srv__CalibrateMask_Request * msg)
{
  if (!msg) {
    return;
  }
  // mask
  rosidl_runtime_c__String__fini(&msg->mask);
}

bool
annin_ar4_driver__srv__CalibrateMask_Request__are_equal(const annin_ar4_driver__srv__CalibrateMask_Request * lhs, const annin_ar4_driver__srv__CalibrateMask_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mask
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mask), &(rhs->mask)))
  {
    return false;
  }
  return true;
}

bool
annin_ar4_driver__srv__CalibrateMask_Request__copy(
  const annin_ar4_driver__srv__CalibrateMask_Request * input,
  annin_ar4_driver__srv__CalibrateMask_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // mask
  if (!rosidl_runtime_c__String__copy(
      &(input->mask), &(output->mask)))
  {
    return false;
  }
  return true;
}

annin_ar4_driver__srv__CalibrateMask_Request *
annin_ar4_driver__srv__CalibrateMask_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Request * msg = (annin_ar4_driver__srv__CalibrateMask_Request *)allocator.allocate(sizeof(annin_ar4_driver__srv__CalibrateMask_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(annin_ar4_driver__srv__CalibrateMask_Request));
  bool success = annin_ar4_driver__srv__CalibrateMask_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
annin_ar4_driver__srv__CalibrateMask_Request__destroy(annin_ar4_driver__srv__CalibrateMask_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    annin_ar4_driver__srv__CalibrateMask_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
annin_ar4_driver__srv__CalibrateMask_Request__Sequence__init(annin_ar4_driver__srv__CalibrateMask_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(annin_ar4_driver__srv__CalibrateMask_Request)) {
      return false;
    }
    data = (annin_ar4_driver__srv__CalibrateMask_Request *)allocator.zero_allocate(size, sizeof(annin_ar4_driver__srv__CalibrateMask_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = annin_ar4_driver__srv__CalibrateMask_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        annin_ar4_driver__srv__CalibrateMask_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
annin_ar4_driver__srv__CalibrateMask_Request__Sequence__fini(annin_ar4_driver__srv__CalibrateMask_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      annin_ar4_driver__srv__CalibrateMask_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

annin_ar4_driver__srv__CalibrateMask_Request__Sequence *
annin_ar4_driver__srv__CalibrateMask_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence * array = (annin_ar4_driver__srv__CalibrateMask_Request__Sequence *)allocator.allocate(sizeof(annin_ar4_driver__srv__CalibrateMask_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = annin_ar4_driver__srv__CalibrateMask_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
annin_ar4_driver__srv__CalibrateMask_Request__Sequence__destroy(annin_ar4_driver__srv__CalibrateMask_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    annin_ar4_driver__srv__CalibrateMask_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
annin_ar4_driver__srv__CalibrateMask_Request__Sequence__are_equal(const annin_ar4_driver__srv__CalibrateMask_Request__Sequence * lhs, const annin_ar4_driver__srv__CalibrateMask_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!annin_ar4_driver__srv__CalibrateMask_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
annin_ar4_driver__srv__CalibrateMask_Request__Sequence__copy(
  const annin_ar4_driver__srv__CalibrateMask_Request__Sequence * input,
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(annin_ar4_driver__srv__CalibrateMask_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(annin_ar4_driver__srv__CalibrateMask_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    annin_ar4_driver__srv__CalibrateMask_Request * data =
      (annin_ar4_driver__srv__CalibrateMask_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!annin_ar4_driver__srv__CalibrateMask_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          annin_ar4_driver__srv__CalibrateMask_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!annin_ar4_driver__srv__CalibrateMask_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
annin_ar4_driver__srv__CalibrateMask_Response__init(annin_ar4_driver__srv__CalibrateMask_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    annin_ar4_driver__srv__CalibrateMask_Response__fini(msg);
    return false;
  }
  return true;
}

void
annin_ar4_driver__srv__CalibrateMask_Response__fini(annin_ar4_driver__srv__CalibrateMask_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
annin_ar4_driver__srv__CalibrateMask_Response__are_equal(const annin_ar4_driver__srv__CalibrateMask_Response * lhs, const annin_ar4_driver__srv__CalibrateMask_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
annin_ar4_driver__srv__CalibrateMask_Response__copy(
  const annin_ar4_driver__srv__CalibrateMask_Response * input,
  annin_ar4_driver__srv__CalibrateMask_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

annin_ar4_driver__srv__CalibrateMask_Response *
annin_ar4_driver__srv__CalibrateMask_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Response * msg = (annin_ar4_driver__srv__CalibrateMask_Response *)allocator.allocate(sizeof(annin_ar4_driver__srv__CalibrateMask_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(annin_ar4_driver__srv__CalibrateMask_Response));
  bool success = annin_ar4_driver__srv__CalibrateMask_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
annin_ar4_driver__srv__CalibrateMask_Response__destroy(annin_ar4_driver__srv__CalibrateMask_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    annin_ar4_driver__srv__CalibrateMask_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
annin_ar4_driver__srv__CalibrateMask_Response__Sequence__init(annin_ar4_driver__srv__CalibrateMask_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(annin_ar4_driver__srv__CalibrateMask_Response)) {
      return false;
    }
    data = (annin_ar4_driver__srv__CalibrateMask_Response *)allocator.zero_allocate(size, sizeof(annin_ar4_driver__srv__CalibrateMask_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = annin_ar4_driver__srv__CalibrateMask_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        annin_ar4_driver__srv__CalibrateMask_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
annin_ar4_driver__srv__CalibrateMask_Response__Sequence__fini(annin_ar4_driver__srv__CalibrateMask_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      annin_ar4_driver__srv__CalibrateMask_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

annin_ar4_driver__srv__CalibrateMask_Response__Sequence *
annin_ar4_driver__srv__CalibrateMask_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence * array = (annin_ar4_driver__srv__CalibrateMask_Response__Sequence *)allocator.allocate(sizeof(annin_ar4_driver__srv__CalibrateMask_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = annin_ar4_driver__srv__CalibrateMask_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
annin_ar4_driver__srv__CalibrateMask_Response__Sequence__destroy(annin_ar4_driver__srv__CalibrateMask_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    annin_ar4_driver__srv__CalibrateMask_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
annin_ar4_driver__srv__CalibrateMask_Response__Sequence__are_equal(const annin_ar4_driver__srv__CalibrateMask_Response__Sequence * lhs, const annin_ar4_driver__srv__CalibrateMask_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!annin_ar4_driver__srv__CalibrateMask_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
annin_ar4_driver__srv__CalibrateMask_Response__Sequence__copy(
  const annin_ar4_driver__srv__CalibrateMask_Response__Sequence * input,
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(annin_ar4_driver__srv__CalibrateMask_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(annin_ar4_driver__srv__CalibrateMask_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    annin_ar4_driver__srv__CalibrateMask_Response * data =
      (annin_ar4_driver__srv__CalibrateMask_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!annin_ar4_driver__srv__CalibrateMask_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          annin_ar4_driver__srv__CalibrateMask_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!annin_ar4_driver__srv__CalibrateMask_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "annin_ar4_driver/srv/detail/calibrate_mask__functions.h"

bool
annin_ar4_driver__srv__CalibrateMask_Event__init(annin_ar4_driver__srv__CalibrateMask_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    annin_ar4_driver__srv__CalibrateMask_Event__fini(msg);
    return false;
  }
  // request
  if (!annin_ar4_driver__srv__CalibrateMask_Request__Sequence__init(&msg->request, 0)) {
    annin_ar4_driver__srv__CalibrateMask_Event__fini(msg);
    return false;
  }
  // response
  if (!annin_ar4_driver__srv__CalibrateMask_Response__Sequence__init(&msg->response, 0)) {
    annin_ar4_driver__srv__CalibrateMask_Event__fini(msg);
    return false;
  }
  return true;
}

void
annin_ar4_driver__srv__CalibrateMask_Event__fini(annin_ar4_driver__srv__CalibrateMask_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  annin_ar4_driver__srv__CalibrateMask_Request__Sequence__fini(&msg->request);
  // response
  annin_ar4_driver__srv__CalibrateMask_Response__Sequence__fini(&msg->response);
}

bool
annin_ar4_driver__srv__CalibrateMask_Event__are_equal(const annin_ar4_driver__srv__CalibrateMask_Event * lhs, const annin_ar4_driver__srv__CalibrateMask_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!annin_ar4_driver__srv__CalibrateMask_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!annin_ar4_driver__srv__CalibrateMask_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
annin_ar4_driver__srv__CalibrateMask_Event__copy(
  const annin_ar4_driver__srv__CalibrateMask_Event * input,
  annin_ar4_driver__srv__CalibrateMask_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!annin_ar4_driver__srv__CalibrateMask_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!annin_ar4_driver__srv__CalibrateMask_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

annin_ar4_driver__srv__CalibrateMask_Event *
annin_ar4_driver__srv__CalibrateMask_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Event * msg = (annin_ar4_driver__srv__CalibrateMask_Event *)allocator.allocate(sizeof(annin_ar4_driver__srv__CalibrateMask_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(annin_ar4_driver__srv__CalibrateMask_Event));
  bool success = annin_ar4_driver__srv__CalibrateMask_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
annin_ar4_driver__srv__CalibrateMask_Event__destroy(annin_ar4_driver__srv__CalibrateMask_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    annin_ar4_driver__srv__CalibrateMask_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
annin_ar4_driver__srv__CalibrateMask_Event__Sequence__init(annin_ar4_driver__srv__CalibrateMask_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(annin_ar4_driver__srv__CalibrateMask_Event)) {
      return false;
    }
    data = (annin_ar4_driver__srv__CalibrateMask_Event *)allocator.zero_allocate(size, sizeof(annin_ar4_driver__srv__CalibrateMask_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = annin_ar4_driver__srv__CalibrateMask_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        annin_ar4_driver__srv__CalibrateMask_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
annin_ar4_driver__srv__CalibrateMask_Event__Sequence__fini(annin_ar4_driver__srv__CalibrateMask_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      annin_ar4_driver__srv__CalibrateMask_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

annin_ar4_driver__srv__CalibrateMask_Event__Sequence *
annin_ar4_driver__srv__CalibrateMask_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  annin_ar4_driver__srv__CalibrateMask_Event__Sequence * array = (annin_ar4_driver__srv__CalibrateMask_Event__Sequence *)allocator.allocate(sizeof(annin_ar4_driver__srv__CalibrateMask_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = annin_ar4_driver__srv__CalibrateMask_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
annin_ar4_driver__srv__CalibrateMask_Event__Sequence__destroy(annin_ar4_driver__srv__CalibrateMask_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    annin_ar4_driver__srv__CalibrateMask_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
annin_ar4_driver__srv__CalibrateMask_Event__Sequence__are_equal(const annin_ar4_driver__srv__CalibrateMask_Event__Sequence * lhs, const annin_ar4_driver__srv__CalibrateMask_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!annin_ar4_driver__srv__CalibrateMask_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
annin_ar4_driver__srv__CalibrateMask_Event__Sequence__copy(
  const annin_ar4_driver__srv__CalibrateMask_Event__Sequence * input,
  annin_ar4_driver__srv__CalibrateMask_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(annin_ar4_driver__srv__CalibrateMask_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(annin_ar4_driver__srv__CalibrateMask_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    annin_ar4_driver__srv__CalibrateMask_Event * data =
      (annin_ar4_driver__srv__CalibrateMask_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!annin_ar4_driver__srv__CalibrateMask_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          annin_ar4_driver__srv__CalibrateMask_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!annin_ar4_driver__srv__CalibrateMask_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

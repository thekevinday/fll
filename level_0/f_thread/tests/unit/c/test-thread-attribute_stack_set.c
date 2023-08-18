#include "test-thread.h"
#include "test-thread-attribute_stack_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_stack_set__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  size_t stack_size = 2;
  int stack[] = { 0, 0 };

  int errnos[] = {
    EACCES,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_attr_setstack, true);
    will_return(__wrap_pthread_attr_setstack, errnos[i]);

    const f_status_t status = f_thread_attribute_stack_set(stack_size, (void *) &stack, &attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_stack_set__parameter_checking(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  size_t stack_size = 2;
  int stack[] = { 0, 0 };

  {
    const f_status_t status = f_thread_attribute_stack_set(stack_size, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_attribute_stack_set(stack_size, (void *) &stack, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_attribute_stack_set(stack_size, 0, &attribute);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_stack_set__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  size_t stack_size = 2;
  int stack[] = { 0, 0 };

  {
    will_return(__wrap_pthread_attr_setstack, false);

    const f_status_t status = f_thread_attribute_stack_set(stack_size, (void *) &stack, &attribute);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-attribute_stack_size_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_stack_size_set__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  size_t stack_size = 2;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_attr_setstacksize, true);
    will_return(__wrap_pthread_attr_setstacksize, errnos[i]);

    const f_status_t status = f_thread_attribute_stack_size_set(stack_size, &attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_stack_size_set__parameter_checking(void **state) {

  size_t stack_size = 2;

  {
    const f_status_t status = f_thread_attribute_stack_size_set(stack_size, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_stack_size_set__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  size_t stack_size = 2;

  {
    will_return(__wrap_pthread_attr_setstacksize, false);

    const f_status_t status = f_thread_attribute_stack_size_set(stack_size, &attribute);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

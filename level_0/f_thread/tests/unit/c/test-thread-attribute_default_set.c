#include "test-thread.h"
#include "test-thread-attribute_default_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_default_set__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;

  int errnos[] = {
    EINVAL,
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_memory_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_setattr_default_np, true);
    will_return(__wrap_pthread_setattr_default_np, errnos[i]);

    const f_status_t status = f_thread_attribute_default_set(&attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_default_set__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_attribute_default_set(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_default_set__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;

  {
    will_return(__wrap_pthread_setattr_default_np, false);

    const f_status_t status = f_thread_attribute_default_set(&attribute);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

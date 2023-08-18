#include "test-thread.h"
#include "test-thread-attribute_scheduler_inherit_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_scheduler_inherit_set__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  int inherit = 0;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_attr_setinheritsched, true);
    will_return(__wrap_pthread_attr_setinheritsched, errnos[i]);

    const f_status_t status = f_thread_attribute_scheduler_inherit_set(inherit, &attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_scheduler_inherit_set__parameter_checking(void **state) {

  int inherit = 0;

  {
    const f_status_t status = f_thread_attribute_scheduler_inherit_set(inherit, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_scheduler_inherit_set__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  int inherit = 0;

  {
    will_return(__wrap_pthread_attr_setinheritsched, false);

    const f_status_t status = f_thread_attribute_scheduler_inherit_set(inherit, &attribute);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

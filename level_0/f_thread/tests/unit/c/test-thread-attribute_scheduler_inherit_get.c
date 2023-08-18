#include "test-thread.h"
#include "test-thread-attribute_scheduler_inherit_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_scheduler_inherit_get__fails(void **state) {

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

    will_return(__wrap_pthread_attr_getinheritsched, true);
    will_return(__wrap_pthread_attr_getinheritsched, errnos[i]);

    const f_status_t status = f_thread_attribute_scheduler_inherit_get(attribute, &inherit);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_scheduler_inherit_get__parameter_checking(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;

  {
    const f_status_t status = f_thread_attribute_scheduler_inherit_get(attribute, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_scheduler_inherit_get__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  int inherit = 0;

  {
    will_return(__wrap_pthread_attr_getinheritsched, false);

    const f_status_t status = f_thread_attribute_scheduler_inherit_get(attribute, &inherit);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

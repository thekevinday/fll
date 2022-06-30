#include "test-thread.h"
#include "test-thread-mutex_attribute_priority_ceiling_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_mutex_attribute_priority_ceiling_set__fails(void **state) {

  f_thread_mutex_attribute_t attribute = f_thread_mutex_attribute_t_initialize;
  int ceiling = 0;

  int errnos[] = {
    EINVAL,
    EPERM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_prohibited,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_mutexattr_setprioceiling, true);
    will_return(__wrap_pthread_mutexattr_setprioceiling, errnos[i]);

    const f_status_t status = f_thread_mutex_attribute_priority_ceiling_set(ceiling, &attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_mutex_attribute_priority_ceiling_set__parameter_checking(void **state) {

  int ceiling = 0;

  {
    const f_status_t status = f_thread_mutex_attribute_priority_ceiling_set(ceiling, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_mutex_attribute_priority_ceiling_set__works(void **state) {

  f_thread_mutex_attribute_t attribute = f_thread_mutex_attribute_t_initialize;
  int ceiling = 0;

  {
    will_return(__wrap_pthread_mutexattr_setprioceiling, false);

    const f_status_t status = f_thread_mutex_attribute_priority_ceiling_set(ceiling, &attribute);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-mutex_attribute_type_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_mutex_attribute_type_get__fails(void **state) {

  f_thread_mutex_attribute_t attribute = f_thread_mutex_attribute_t_initialize;
  int type = 0;

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (uint8_t i = 0; i < 1; ++i) {

    will_return(__wrap_pthread_mutexattr_gettype, true);
    will_return(__wrap_pthread_mutexattr_gettype, errnos[i]);

    const f_status_t status = f_thread_mutex_attribute_type_get(&attribute, &type);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_mutex_attribute_type_get__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_mutex_attribute_type_get(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_mutex_attribute_type_get__works(void **state) {

  f_thread_mutex_attribute_t attribute = f_thread_mutex_attribute_t_initialize;
  int type = 0;

  {
    will_return(__wrap_pthread_mutexattr_gettype, false);

    const f_status_t status = f_thread_mutex_attribute_type_get(&attribute, &type);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

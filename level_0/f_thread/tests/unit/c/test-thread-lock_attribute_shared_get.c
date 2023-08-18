#include "test-thread.h"
#include "test-thread-lock_attribute_shared_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_lock_attribute_shared_get__fails(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  int shared = 0;

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (uint8_t i = 0; i < 1; ++i) {

    will_return(__wrap_pthread_rwlockattr_getpshared, true);
    will_return(__wrap_pthread_rwlockattr_getpshared, errnos[i]);

    const f_status_t status = f_thread_lock_attribute_shared_get(&attribute, &shared);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_lock_attribute_shared_get__parameter_checking(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  int shared = 0;

  {
    const f_status_t status = f_thread_lock_attribute_shared_get(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_lock_attribute_shared_get(&attribute, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_lock_attribute_shared_get(0, &shared);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_lock_attribute_shared_get__works(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  int shared = 0;

  {
    will_return(__wrap_pthread_rwlockattr_getpshared, false);

    const f_status_t status = f_thread_lock_attribute_shared_get(&attribute, &shared);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

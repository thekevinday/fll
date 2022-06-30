#include "test-thread.h"
#include "test-thread-lock_attribute_shared_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_lock_attribute_shared_set__fails(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  int shared = 0;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_rwlockattr_setpshared, true);
    will_return(__wrap_pthread_rwlockattr_setpshared, errnos[i]);

    const f_status_t status = f_thread_lock_attribute_shared_set(shared, &attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_lock_attribute_shared_set__parameter_checking(void **state) {

  int shared = 0;

  {
    const f_status_t status = f_thread_lock_attribute_shared_set(shared, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_lock_attribute_shared_set__works(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  int shared = 0;

  {
    will_return(__wrap_pthread_rwlockattr_setpshared, false);

    const f_status_t status = f_thread_lock_attribute_shared_set(shared, &attribute);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

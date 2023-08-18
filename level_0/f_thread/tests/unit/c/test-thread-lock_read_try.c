#include "test-thread.h"
#include "test-thread-lock_read_try.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_lock_read_try__fails(void **state) {

  f_thread_lock_t lock = f_thread_lock_t_initialize;

  int errnos[] = {
    EAGAIN,
    EBUSY,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_resource_not),
    F_busy,
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_pthread_rwlock_tryrdlock, true);
    will_return(__wrap_pthread_rwlock_tryrdlock, errnos[i]);

    const f_status_t status = f_thread_lock_read_try(&lock);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_lock_read_try__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_lock_read_try(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_lock_read_try__works(void **state) {

  f_thread_lock_t lock = f_thread_lock_t_initialize;

  {
    will_return(__wrap_pthread_rwlock_tryrdlock, false);

    const f_status_t status = f_thread_lock_read_try(&lock);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

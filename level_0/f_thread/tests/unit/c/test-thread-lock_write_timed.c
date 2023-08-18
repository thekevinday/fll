#include "test-thread.h"
#include "test-thread-lock_write_timed.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_lock_write_timed__fails(void **state) {

  f_thread_lock_t lock = f_thread_lock_t_initialize;
  struct timespec timeout;

  memset(&timeout, 0, sizeof(struct timespec));

  int errnos[] = {
    EDEADLK,
    EINVAL,
    ETIMEDOUT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_deadlock),
    F_status_set_error(F_parameter),
    F_time,
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_pthread_rwlock_timedwrlock, true);
    will_return(__wrap_pthread_rwlock_timedwrlock, errnos[i]);

    const f_status_t status = f_thread_lock_write_timed(&timeout, &lock);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_lock_write_timed__parameter_checking(void **state) {

  f_thread_lock_t lock = f_thread_lock_t_initialize;
  struct timespec timeout;

  memset(&timeout, 0, sizeof(struct timespec));

  {
    const f_status_t status = f_thread_lock_write_timed(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_lock_write_timed(&timeout, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_lock_write_timed(0, &lock);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_lock_write_timed__works(void **state) {

  f_thread_lock_t lock = f_thread_lock_t_initialize;
  struct timespec timeout;

  memset(&timeout, 0, sizeof(struct timespec));

  {
    will_return(__wrap_pthread_rwlock_timedwrlock, false);

    const f_status_t status = f_thread_lock_write_timed(&timeout, &lock);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

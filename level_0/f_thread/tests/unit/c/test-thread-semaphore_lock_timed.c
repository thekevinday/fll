#include "test-thread.h"
#include "test-thread-semaphore_lock_timed.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_lock_timed__fails(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  struct timespec timeout;

  memset(&timeout, 0, sizeof(struct timespec));

  int errnos[] = {
    EINTR,
    EINVAL,
    ETIMEDOUT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_interrupt),
    F_status_set_error(F_parameter),
    F_time,
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_sem_timedwait, true);
    will_return(__wrap_sem_timedwait, errnos[i]);

    const f_status_t status = f_thread_semaphore_lock_timed(&timeout, &semaphore);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_semaphore_lock_timed__parameter_checking(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  struct timespec timeout;

  memset(&timeout, 0, sizeof(struct timespec));

  {
    const f_status_t status = f_thread_semaphore_lock_timed(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_semaphore_lock_timed(&timeout, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_semaphore_lock_timed(0, &semaphore);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_semaphore_lock_timed__works(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  struct timespec timeout;

  memset(&timeout, 0, sizeof(struct timespec));

  {
    will_return(__wrap_sem_timedwait, false);

    const f_status_t status = f_thread_semaphore_lock_timed(&timeout, &semaphore);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

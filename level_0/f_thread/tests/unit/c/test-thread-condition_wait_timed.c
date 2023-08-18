#include "test-thread.h"
#include "test-thread-condition_wait_timed.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_condition_wait_timed__fails(void **state) {

  struct timespec wait;
  f_thread_condition_t condition = f_thread_condition_t_initialize;
  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  memset(&wait, 0, sizeof(struct timespec));

  int errnos[] = {
    EINVAL,
    ENOTRECOVERABLE,
    EOWNERDEAD,
    EPERM,
    ETIMEDOUT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_parameter),
    F_status_set_error(F_recover_not),
    F_status_set_error(F_dead),
    F_status_set_error(F_prohibited),
    F_time,
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 6; ++i) {

    will_return(__wrap_pthread_cond_timedwait, true);
    will_return(__wrap_pthread_cond_timedwait, errnos[i]);

    const f_status_t status = f_thread_condition_wait_timed(&wait, &condition, &mutex);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_condition_wait_timed__parameter_checking(void **state) {

  struct timespec wait;
  f_thread_condition_t condition = f_thread_condition_t_initialize;
  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  memset(&wait, 0, sizeof(struct timespec));

  {
    const f_status_t status = f_thread_condition_wait_timed(&wait, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_condition_wait_timed(&wait, &condition, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_condition_wait_timed(&wait, 0, &mutex);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_condition_wait_timed__works(void **state) {

  struct timespec wait;
  f_thread_condition_t condition = f_thread_condition_t_initialize;
  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  memset(&wait, 0, sizeof(struct timespec));

  {
    will_return(__wrap_pthread_cond_timedwait, false);

    const f_status_t status = f_thread_condition_wait_timed(&wait, &condition, &mutex);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-condition_wait.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_condition_wait__fails(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;
  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  int errnos[] = {
    EINVAL,
    ENOTRECOVERABLE,
    EOWNERDEAD,
    EPERM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_recover_not,
    F_dead,
    F_prohibited,
    F_failure,
  };

  for (uint8_t i = 0; i < 5; ++i) {

    will_return(__wrap_pthread_cond_wait, true);
    will_return(__wrap_pthread_cond_wait, errnos[i]);

    const f_status_t status = f_thread_condition_wait(&condition, &mutex);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_condition_wait__parameter_checking(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;
  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  {
    const f_status_t status = f_thread_condition_wait(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_condition_wait(0, &mutex);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_condition_wait(&condition, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_condition_wait__works(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;
  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  {
    will_return(__wrap_pthread_cond_wait, false);

    const f_status_t status = f_thread_condition_wait(&condition, &mutex);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

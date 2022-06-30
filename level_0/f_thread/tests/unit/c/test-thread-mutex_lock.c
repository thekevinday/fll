#include "test-thread.h"
#include "test-thread-mutex_lock.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_mutex_lock__fails(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  int errnos[] = {
    EAGAIN,
    EDEADLK,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_deadlock,
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_pthread_mutex_lock, true);
    will_return(__wrap_pthread_mutex_lock, errnos[i]);

    const f_status_t status = f_thread_mutex_lock(&mutex);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_mutex_lock__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_mutex_lock(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_mutex_lock__works(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;

  {
    will_return(__wrap_pthread_mutex_lock, false);

    const f_status_t status = f_thread_mutex_lock(&mutex);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

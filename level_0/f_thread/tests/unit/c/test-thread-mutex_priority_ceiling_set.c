#include "test-thread.h"
#include "test-thread-mutex_priority_ceiling_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_mutex_priority_ceiling_set__fails(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;
  int ceiling = 0;
  int previous = 0;

  int errnos[] = {
    EAGAIN,
    EDEADLK,
    EINVAL,
    ENOTRECOVERABLE,
    EOWNERDEAD,
    EPERM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_deadlock,
    F_parameter,
    F_recover_not,
    F_dead,
    F_prohibited,
    F_failure,
  };

  for (uint8_t i = 0; i < 7; ++i) {

    will_return(__wrap_pthread_mutex_setprioceiling, true);
    will_return(__wrap_pthread_mutex_setprioceiling, errnos[i]);

    const f_status_t status = f_thread_mutex_priority_ceiling_set(ceiling, &mutex, &previous);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_mutex_priority_ceiling_set__parameter_checking(void **state) {

  int ceiling = 0;
  int previous = 0;

  {
    const f_status_t status = f_thread_mutex_priority_ceiling_set(ceiling, 0, &previous);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_mutex_priority_ceiling_set__works(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;
  int ceiling = 0;
  int previous = 0;

  {
    will_return(__wrap_pthread_mutex_setprioceiling, false);

    const f_status_t status = f_thread_mutex_priority_ceiling_set(ceiling, &mutex, &previous);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

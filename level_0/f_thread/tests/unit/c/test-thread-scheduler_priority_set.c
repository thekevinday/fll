#include "test-thread.h"
#include "test-thread-scheduler_priority_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_scheduler_priority_set__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int priority = 0;

  int errnos[] = {
    EINVAL,
    EPERM,
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_prohibited,
    F_found_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_pthread_setschedprio, true);
    will_return(__wrap_pthread_setschedprio, errnos[i]);

    const f_status_t status = f_thread_scheduler_priority_set(id, priority);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_scheduler_priority_set__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int priority = 0;

  {
    will_return(__wrap_pthread_setschedprio, false);

    const f_status_t status = f_thread_scheduler_priority_set(id, priority);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

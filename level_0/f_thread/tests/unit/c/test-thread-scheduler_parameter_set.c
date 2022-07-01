#include "test-thread.h"
#include "test-thread-scheduler_parameter_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_scheduler_parameter_set__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int policy = 0;
  struct sched_param parameter;

  memset(&parameter, 0, sizeof(struct sched_param));

  int errnos[] = {
    EINVAL,
    EPERM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_prohibited,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_setschedparam, true);
    will_return(__wrap_pthread_setschedparam, errnos[i]);

    const f_status_t status = f_thread_scheduler_parameter_set(id, policy, &parameter);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_scheduler_parameter_set__parameter_checking(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int policy = 0;

  {
    const f_status_t status = f_thread_scheduler_parameter_set(id, policy, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_scheduler_parameter_set__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int policy = 0;
  struct sched_param parameter;

  memset(&parameter, 0, sizeof(struct sched_param));

  {
    will_return(__wrap_pthread_setschedparam, false);

    const f_status_t status = f_thread_scheduler_parameter_set(id, policy, &parameter);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-scheduler_parameter_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_scheduler_parameter_get__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int policy = 0;
  struct sched_param parameter;

  memset(&parameter, 0, sizeof(struct sched_param));

  int errnos[] = {
    ENOTSUP,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_support_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_getschedparam, true);
    will_return(__wrap_pthread_getschedparam, errnos[i]);

    const f_status_t status = f_thread_scheduler_parameter_get(id, &policy, &parameter);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_scheduler_parameter_get__parameter_checking(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int policy = 0;
  struct sched_param parameter;

  memset(&parameter, 0, sizeof(struct sched_param));

  {
    const f_status_t status = f_thread_scheduler_parameter_get(id, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_scheduler_parameter_get(id, &policy, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_scheduler_parameter_get(id, 0, &parameter);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_scheduler_parameter_get__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int policy = 0;
  struct sched_param parameter;

  memset(&parameter, 0, sizeof(struct sched_param));

  {
    will_return(__wrap_pthread_getschedparam, false);

    const f_status_t status = f_thread_scheduler_parameter_get(id, &policy, &parameter);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

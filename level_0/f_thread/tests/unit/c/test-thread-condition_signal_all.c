#include "test-thread.h"
#include "test-thread-condition_signal_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_condition_signal_all__fails(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_cond_broadcast, true);
    will_return(__wrap_pthread_cond_broadcast, errnos[i]);

    const f_status_t status = f_thread_condition_signal_all(&condition);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_condition_signal_all__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_condition_signal_all(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_condition_signal_all__works(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;

  {
    will_return(__wrap_pthread_cond_broadcast, false);

    const f_status_t status = f_thread_condition_signal_all(&condition);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
#include "test-thread.h"
#include "test-thread-cancel_state_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_cancel_state_set__fails(void **state) {

  int state_data = 0;
  int previous = 0;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_setcancelstate, true);
    will_return(__wrap_pthread_setcancelstate, errnos[i]);

    const f_status_t status = f_thread_cancel_state_set(state_data, &previous);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_cancel_state_set__works(void **state) {

  int state_data = 0;
  int previous = 0;

  {
    will_return(__wrap_pthread_setcancelstate, false);

    const f_status_t status = f_thread_cancel_state_set(state_data, &previous);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

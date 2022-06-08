#include "test-signal.h"
#include "test-signal-send.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_send__fails(void **state) {

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

  for (int i = 0; i < 4; ++i) {

    will_return(__wrap_kill, true);
    will_return(__wrap_kill, errnos[i]);

    const f_status_t status = f_signal_send(0, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_send__works(void **state) {

  {
    will_return(__wrap_kill, false);

    const f_status_t status = f_signal_send(0, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

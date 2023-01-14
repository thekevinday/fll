#include "test-signal.h"
#include "test-signal-queue.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_queue__fails(void **state) {

  union sigval value;

  memset(&value, 0, sizeof(union sigval));

  int errnos[] = {
    EAGAIN,
    ENOSYS,
    EINVAL,
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_support_not,
    F_parameter,
    F_found_not,
    F_failure,
  };

  for (int i = 0; i < 5; ++i) {

    will_return(__wrap_sigqueue, true);
    will_return(__wrap_sigqueue, errnos[i]);

    const f_status_t status = f_signal_queue(0, 0, value);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_queue__works(void **state) {

  union sigval value;

  memset(&value, 0, sizeof(union sigval));

  {
    will_return(__wrap_sigqueue, false);

    const f_status_t status = f_signal_queue(0, 0, value);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

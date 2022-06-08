#include "test-signal.h"
#include "test-signal-wait_until.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_wait_until__fails(void **state) {

  int errnos[] = {
    EAGAIN,
    EINTR,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_time_out,
    F_status_set_error(F_interrupt),
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (int i = 0; i < 4; ++i) {

    sigset_t set;
    siginfo_t information;
    struct timespec timeout;

    memset(&set, 0, sizeof(sigset_t));
    memset(&set, 0, sizeof(siginfo_t));
    memset(&set, 0, sizeof(struct timespec));

    will_return(__wrap_sigtimedwait, true);
    will_return(__wrap_sigtimedwait, errnos[i]);

    const f_status_t status = f_signal_wait_until(&set, &timeout, &information);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_signal_wait_until__works(void **state) {

  {
    sigset_t set;
    siginfo_t information;
    struct timespec timeout;

    memset(&set, 0, sizeof(sigset_t));
    memset(&set, 0, sizeof(siginfo_t));
    memset(&set, 0, sizeof(struct timespec));

    will_return(__wrap_sigtimedwait, false);

    const f_status_t status = f_signal_wait_until(&set, &timeout, &information);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-signal.h"
#include "test-signal-wait.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_wait__fails(void **state) {

  int errnos[] = {
    EINTR,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_interrupt,
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (int i = 0; i < 3; ++i) {

    sigset_t set;
    siginfo_t information;

    memset(&set, 0, sizeof(sigset_t));
    memset(&set, 0, sizeof(siginfo_t));

    will_return(__wrap_sigwaitinfo, true);
    will_return(__wrap_sigwaitinfo, errnos[i]);

    const f_status_t status = f_signal_wait(&set, &information);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_signal_wait__works(void **state) {

  {
    sigset_t set;
    siginfo_t information;

    memset(&set, 0, sizeof(sigset_t));
    memset(&set, 0, sizeof(siginfo_t));

    will_return(__wrap_sigwaitinfo, false);

    const f_status_t status = f_signal_wait(&set, &information);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

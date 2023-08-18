#include "test-signal.h"
#include "test-signal-suspend.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_suspend__fails(void **state) {

  sigset_t set;

  memset(&set, 0, sizeof(sigset_t));

  {
    int errnos[] = {
      EFAULT,
      EINTR,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_buffer,
      F_interrupt,
      F_failure,
    };

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_sigsuspend, true);
      will_return(__wrap_sigsuspend, errnos[i]);

      const f_status_t status = f_signal_suspend(&set);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_signal_suspend__parameter_checking(void **state) {

  {
    const f_status_t status = f_signal_suspend(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_suspend__works(void **state) {

  {
    sigset_t set;

    memset(&set, 0, sizeof(sigset_t));

    will_return(__wrap_sigsuspend, false);

    const f_status_t status = f_signal_suspend(&set);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

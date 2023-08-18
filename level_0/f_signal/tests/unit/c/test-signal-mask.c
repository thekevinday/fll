#include "test-signal.h"
#include "test-signal-mask.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_mask__fails(void **state) {

  int errnos[] = {
    EFAULT,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_buffer,
    F_parameter,
    F_failure,
  };

  for (int i = 0; i < 3; ++i) {

    sigset_t next;
    sigset_t current;

    memset(&next, 0, sizeof(sigset_t));
    memset(&current, 0, sizeof(sigset_t));

    will_return(__wrap_sigprocmask, true);
    will_return(__wrap_sigprocmask, errnos[i]);

    const f_status_t status = f_signal_mask(0, &next, &current);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_mask__parameter_checking(void **state) {

  {
    const f_status_t status = f_signal_mask(0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_mask__works(void **state) {

  {
    sigset_t next;
    sigset_t current;

    memset(&next, 0, sizeof(sigset_t));
    memset(&current, 0, sizeof(sigset_t));

    will_return(__wrap_sigprocmask, false);

    const f_status_t status = f_signal_mask(0, &next, &current);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

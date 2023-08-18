#include "test-signal.h"
#include "test-signal-set_fill.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_set_fill__fails(void **state) {

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

    sigset_t set;

    memset(&set, 0, sizeof(sigset_t));

    will_return(__wrap_sigfillset, true);
    will_return(__wrap_sigfillset, errnos[i]);

    const f_status_t status = f_signal_set_fill(&set);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_set_fill__parameter_checking(void **state) {

  {
    const f_status_t status = f_signal_set_fill(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_set_fill__works(void **state) {

  {
    sigset_t set;

    memset(&set, 0, sizeof(sigset_t));

    will_return(__wrap_sigfillset, false);

    const f_status_t status = f_signal_set_fill(&set);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

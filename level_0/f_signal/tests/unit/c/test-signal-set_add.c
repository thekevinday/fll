#include "test-signal.h"
#include "test-signal-set_add.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_set_add__fails(void **state) {

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (int i = 0; i < 2; ++i) {

    sigset_t set;

    memset(&set, 0, sizeof(sigset_t));

    will_return(__wrap_sigaddset, true);
    will_return(__wrap_sigaddset, errnos[i]);

    const f_status_t status = f_signal_set_add(0, &set);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_set_add__parameter_checking(void **state) {

  {
    const f_status_t status = f_signal_set_add(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_set_add__works(void **state) {

  {
    sigset_t set;

    memset(&set, 0, sizeof(sigset_t));

    will_return(__wrap_sigaddset, false);

    const f_status_t status = f_signal_set_add(0, &set);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

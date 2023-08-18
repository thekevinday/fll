#include "test-signal.h"
#include "test-signal-action.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_action__fails(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  struct sigaction action;
  struct sigaction previous;

  memset(&action, 0, sizeof(struct sigaction));
  memset(&previous, 0, sizeof(struct sigaction));

  {
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

      will_return(__wrap_sigaction, true);
      will_return(__wrap_sigaction, errnos[i]);

      const f_status_t status = f_signal_action(signal, &action, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_sigaction, true);
      will_return(__wrap_sigaction, errnos[i]);

      const f_status_t status = f_signal_action(signal, 0, &previous);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_sigaction, true);
      will_return(__wrap_sigaction, errnos[i]);

      const f_status_t status = f_signal_action(signal, &action, &previous);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_signal_action__parameter_checking(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  {
    const f_status_t status = f_signal_action(signal, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_action__works(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  struct sigaction action;
  struct sigaction previous;

  memset(&action, 0, sizeof(struct sigaction));
  memset(&previous, 0, sizeof(struct sigaction));

  {
    will_return(__wrap_sigaction, false);

    const f_status_t status = f_signal_action(signal, &action, 0);

    assert_int_equal(status, F_okay);
  }

  {
    will_return(__wrap_sigaction, false);

    const f_status_t status = f_signal_action(signal, 0, &previous);

    assert_int_equal(status, F_okay);
  }

  {
    will_return(__wrap_sigaction, false);

    const f_status_t status = f_signal_action(signal, &action, &previous);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

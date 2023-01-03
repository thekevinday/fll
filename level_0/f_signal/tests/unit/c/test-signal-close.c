#include "test-signal.h"
#include "test-signal-close.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_close__fails(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  int errnos[] = {
    EBADF,
    EDQUOT,
    EINTR,
    EIO,
    ENOSPC,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_descriptor,
    F_filesystem_quota_block,
    F_interrupt,
    F_input_output,
    F_parameter,
    F_failure,
  };

  signal.id = 0;

  for (int i = 0; i < 6; ++i) {

    will_return(__wrap_close, true);
    will_return(__wrap_close, errnos[i]);

    const f_status_t status = f_signal_close(&signal);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_close__parameter_checking(void **state) {

  {
    const f_status_t status = f_signal_close(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_close__returns_data_not(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  {
    const f_status_t status = f_signal_close(&signal);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_signal_close__works(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  signal.id = 0;

  {
    will_return(__wrap_close, 0);

    const f_status_t status = f_signal_close(&signal);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

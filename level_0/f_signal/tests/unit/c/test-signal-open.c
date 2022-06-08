#include "test-signal.h"
#include "test-signal-open.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_open__fails(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  int errnos[] = {
    EINVAL,
    EMFILE,
    ENFILE,
    ENODEV,
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_file_descriptor_max,
    F_file_open_max,
    F_device,
    F_memory_not,
    F_failure,
  };

  for (int i = 0; i < 6; ++i) {

    will_return(__wrap_signalfd, true);
    will_return(__wrap_signalfd, errnos[i]);

    const f_status_t status = f_signal_open(&signal);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_signal_open__parameter_checking(void **state) {

  {
    const f_status_t status = f_signal_open(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_open__works(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  {
    const int id = 1;
    will_return(__wrap_signalfd, false);
    will_return(__wrap_signalfd, id);

    const f_status_t status = f_signal_open(&signal);

    assert_int_equal(status, F_none);
    assert_int_equal(signal.id, id);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

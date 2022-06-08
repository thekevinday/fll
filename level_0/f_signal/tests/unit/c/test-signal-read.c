#include "test-signal.h"
#include "test-signal-read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_read__fails(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  {
    int errnos[] = {
      EFAULT,
      EINTR,
      EINVAL,
      ENOMEM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_buffer,
      F_interrupt,
      F_parameter,
      F_memory_not,
      F_failure,
    };

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    for (int i = 0; i < 5; ++i) {

      will_return(__wrap_poll, true);
      will_return(__wrap_poll, errnos[i]);

      const f_status_t status = f_signal_read(signal, 0, &information);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  {
    int errnos[] = {
      EAGAIN,
      EBADF,
      EFAULT,
      EINTR,
      EINVAL,
      EIO,
      EISDIR,
      EWOULDBLOCK,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_block,
      F_descriptor,
      F_buffer,
      F_interrupt,
      F_parameter,
      F_input_output,
      F_file_type_directory,
      F_block,
      F_failure,
    };

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_poll, false);
      will_return(__wrap_poll, POLLIN);
      will_return(__wrap_poll, 1);

      will_return(__wrap_read, true);
      will_return(__wrap_read, errnos[i]);

      const f_status_t status = f_signal_read(signal, 0, &information);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_signal_read__parameter_checking(void **state) {

  f_signal_t signal = f_signal_t_initialize;

  {
    const f_status_t status = f_signal_read(signal, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_signal_read__works(void **state) {

  {
    f_signal_t signal = f_signal_t_initialize;
    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    will_return(__wrap_poll, false);
    will_return(__wrap_poll, 0);
    will_return(__wrap_poll, 0);

    const f_status_t status = f_signal_read(signal, 0, &information);

    assert_int_equal(status, F_none);
    assert_int_equal(signal.id, -1);
  }

  {
    f_signal_t signal = f_signal_t_initialize;
    signal.id = 1;
    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    will_return(__wrap_poll, false);
    will_return(__wrap_poll, POLLIN);
    will_return(__wrap_poll, 1);

    will_return(__wrap_read, false);
    will_return(__wrap_read, 1);

    const f_status_t status = f_signal_read(signal, 0, &information);

    assert_int_equal(status, F_signal);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

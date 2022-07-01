#include "test-thread.h"
#include "test-thread-signal_mask.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_signal_mask__fails(void **state) {

  int how = 0;
  sigset_t next;
  sigset_t current;

  memset(&next, 0, sizeof(sigset_t));
  memset(&current, 0, sizeof(sigset_t));

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

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_sigmask, true);
    will_return(__wrap_pthread_sigmask, errnos[i]);

    const f_status_t status = f_thread_signal_mask(how, &next, &current);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_signal_mask__parameter_checking(void **state) {

  int how = 0;
  sigset_t next;
  sigset_t current;

  memset(&next, 0, sizeof(sigset_t));
  memset(&current, 0, sizeof(sigset_t));

  {
    const f_status_t status = f_thread_signal_mask(how, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    will_return(__wrap_pthread_sigmask, false);

    const f_status_t status = f_thread_signal_mask(how, &next, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pthread_sigmask, false);

    const f_status_t status = f_thread_signal_mask(how, 0, &current);

    assert_int_equal(status, F_none);
  }
}

void test__f_thread_signal_mask__works(void **state) {

  int how = 0;
  sigset_t next;
  sigset_t current;

  memset(&next, 0, sizeof(sigset_t));
  memset(&current, 0, sizeof(sigset_t));

  {
    will_return(__wrap_pthread_sigmask, false);

    const f_status_t status = f_thread_signal_mask(how, &next, &current);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

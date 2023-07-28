#include "test-file.h"
#include "test-file-select_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_select_signal__fails(void **state) {

  {
    fd_set read;

    memset(&read, 0, sizeof(fd_set));

    int errnos[] = {
      EBADF,
      EINTR,
      EINVAL,
      ENOMEM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_descriptor,
      F_interrupt,
      F_parameter,
      F_memory_not,
      F_failure,
    };

    for (int i = 0; i < 5; ++i) {

      will_return(__wrap_pselect, true);
      will_return(__wrap_pselect, errnos[i]);

      const f_status_t status = f_file_select_signal(1, &read, 0, 0, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_select_signal__returns_data_not(void **state) {

  fd_set read;
  fd_set write;
  fd_set except;
  struct timespec timeout;
  sigset_t signal;

  memset(&read, 0, sizeof(fd_set));
  memset(&write, 0, sizeof(fd_set));
  memset(&except, 0, sizeof(fd_set));
  memset(&timeout, 0, sizeof(struct timespec));
  memset(&signal, 0, sizeof(sigset_t));

  {
    const f_status_t status = f_file_select_signal(0, &read, &write, &except, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, &write, &except, &timeout, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, &write, &except, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, &write, 0, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, 0, &except, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &write, &except, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, &except, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &write, 0, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &write, &except, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &write, &except, &timeout, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &read, &except, &timeout, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &read, &except, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &read, 0, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, &except, &timeout, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, &except, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, 0, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, 0, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, 0, &timeout, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, 0, &except, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &write, 0, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, 0, 0, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, 0, &write, 0, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, 0, 0, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, &write, 0, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, 0, &except, 0, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(0, &read, 0, 0, &timeout, &signal);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(1, 0, 0, 0, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_select_signal(1, 0, 0, 0, 0, &signal);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_select_signal__works(void **state) {

  fd_set read;
  fd_set write;
  fd_set except;
  struct timespec timeout;
  sigset_t signal;

  memset(&read, 0, sizeof(fd_set));
  memset(&write, 0, sizeof(fd_set));
  memset(&except, 0, sizeof(fd_set));
  memset(&timeout, 0, sizeof(struct timespec));
  memset(&signal, 0, sizeof(sigset_t));

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, &write, &except, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, &write, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, &write, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, &write, 0, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, 0, &except, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, &write, &except, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, 0, 0, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, 0, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, &read, 0, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, &write, 0, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, &write, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, &write, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, 0, &except, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, &read, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, &timeout);

    const f_status_t status = f_file_select_signal(1, 0, &read, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, &write, 0, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, &write, 0, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, 0, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, 0, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, &write, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, &write, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, 0, 0, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, &write, 0, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, 0, &except, 0, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, 0, 0, &timeout, &signal);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, 0, 0, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, &write, 0, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, 0, &except, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, 0, 0, &timeout, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, 0, &except, 0, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, 0, &write, 0, 0, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_pselect, false);
    will_return(__wrap_pselect, 0);

    const f_status_t status = f_file_select_signal(1, &read, 0, 0, 0, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

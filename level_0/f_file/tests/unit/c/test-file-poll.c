#include "test-file.h"
#include "test-file-poll.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_poll__fails(void **state) {

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

    f_polls_t polls = f_polls_t_initialize;
    polls.used = 1;

    for (int i = 0; i < 5; ++i) {

      will_return(__wrap_poll, true);
      will_return(__wrap_poll, errnos[i]);

      const f_status_t status = f_file_poll(polls, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_poll__returns_data_not(void **state) {

  f_polls_t polls = f_polls_t_initialize;

  {
    const f_status_t status = f_file_poll(polls, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_poll__works(void **state) {

  {
    const int fd = 0;
    const int total = 1;
    const short revents = 5;

    f_poll_t poll = macro_f_poll_t_initialize_1(fd, 1, 2);
    f_polls_t polls = macro_f_polls_t_initialize_1(&poll, 0, 1);

    will_return(__wrap_poll, false);
    will_return(__wrap_poll, revents);
    will_return(__wrap_poll, total);

    const f_status_t status = f_file_poll(polls, 0);

    assert_int_equal(status, F_okay);
    assert_int_equal(poll.fd, fd);
    assert_int_equal(poll.events, total);
    assert_int_equal(poll.revents, revents);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-signal_write.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_signal_write__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int signal = 1;

  {
    int errnos[] = {
      EINVAL,
      ESRCH,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_found_not,
      F_failure,
    };

    for (uint8_t i = 0; i < 3; ++i) {

      will_return(__wrap_pthread_kill, true);
      will_return(__wrap_pthread_kill, errnos[i]);

      const f_status_t status = f_thread_signal_write(id, signal);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  {
    signal = 0;

    int errnos[] = {
      EINVAL,
      ESRCH,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_status_set_error(F_parameter),
      F_found_not,
      F_status_set_error(F_failure),
    };

    for (uint8_t i = 0; i < 3; ++i) {

      will_return(__wrap_pthread_kill, true);
      will_return(__wrap_pthread_kill, errnos[i]);

      const f_status_t status = f_thread_signal_write(id, signal);

      assert_int_equal(status, statuss[i]);
    } // for
  }
}

void test__f_thread_signal_write__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int signal = 1;

  {
    will_return(__wrap_pthread_kill, false);

    const f_status_t status = f_thread_signal_write(id, signal);

    assert_int_equal(status, F_okay);
  }

  {
    signal = 0;

    will_return(__wrap_pthread_kill, false);

    const f_status_t status = f_thread_signal_write(id, signal);

    assert_int_equal(status, F_found);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-signal_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_signal_queue__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int signal = 0;
  union sigval value;

  memset(&value, 0, sizeof(union sigval));

  #ifdef _pthread_sigqueue_unsupported_
    const f_status_t status = f_thread_signal_queue(id, signal, value);

    assert_int_equal(status, F_status_set_error(F_implemented_not));
  #else
    {
      int errnos[] = {
        EAGAIN,
        ENOSYS,
        EINVAL,
        ESRCH,
        mock_errno_generic,
      };

      f_status_t statuss[] = {
        F_resource_not,
        F_support_not,
        F_parameter,
        F_found_not,
        F_failure,
      };

      for (uint8_t i = 0; i < 5; ++i) {

        will_return(__wrap_pthread_sigqueue, true);
        will_return(__wrap_pthread_sigqueue, errnos[i]);

        const f_status_t status = f_thread_signal_queue(id, signal, value);

        assert_int_equal(status, F_status_set_error(statuss[i]));
      } // for
    }
  #endif // _pthread_sigqueue_unsupported_
}

void test__f_thread_signal_queue__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;
  int signal = 0;
  union sigval value;

  memset(&value, 0, sizeof(union sigval));

  #ifdef _pthread_sigqueue_unsupported_
    const f_status_t status = f_thread_signal_queue(id, signal, value);

    assert_int_equal(status, F_status_set_error(F_implemented_not));
  #else
    {
      will_return(__wrap_pthread_sigqueue, false);

      const f_status_t status = f_thread_signal_queue(id, signal, value);

      assert_int_equal(status, F_none);
    }
  #endif // _pthread_sigqueue_unsupported_
}

#ifdef __cplusplus
} // extern "C"
#endif

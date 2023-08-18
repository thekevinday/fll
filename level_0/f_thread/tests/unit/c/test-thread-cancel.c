#include "test-thread.h"
#include "test-thread-cancel.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_cancel__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;

  int errnos[] = {
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_found_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_cancel, true);
    will_return(__wrap_pthread_cancel, errnos[i]);

    const f_status_t status = f_thread_cancel(id);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_cancel__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;

  {
    will_return(__wrap_pthread_cancel, false);

    const f_status_t status = f_thread_cancel(id);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-detach.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_detach__fails(void **state) {

  f_thread_id_t id = 0;

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

    will_return(__wrap_pthread_detach, true);
    will_return(__wrap_pthread_detach, errnos[i]);

    const f_status_t status = f_thread_detach(id);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_detach__works(void **state) {

  f_thread_id_t id = 0;

  {
    will_return(__wrap_pthread_detach, false);

    const f_status_t status = f_thread_detach(id);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

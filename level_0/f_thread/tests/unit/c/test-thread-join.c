#include "test-thread.h"
#include "test-thread-join.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_join__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;

  int errnos[] = {
    EDEADLK,
    EINVAL,
    EPERM,
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_deadlock,
    F_parameter,
    F_support_not,
    F_found_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 5; ++i) {

    will_return(__wrap_pthread_join, true);
    will_return(__wrap_pthread_join, errnos[i]);

    const f_status_t status = f_thread_join(id, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_join__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;

  {
    will_return(__wrap_pthread_join, false);

    const f_status_t status = f_thread_join(id, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

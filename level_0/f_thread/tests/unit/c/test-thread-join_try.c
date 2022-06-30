#include "test-thread.h"
#include "test-thread-join_try.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_join_try__fails(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;

  int errnos[] = {
    EBUSY,
    EDEADLK,
    EINVAL,
    EPERM,
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_busy,
    F_status_set_error(F_deadlock),
    F_status_set_error(F_parameter),
    F_status_set_error(F_supported_not),
    F_status_set_error(F_found_not),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 6; ++i) {

    will_return(__wrap_pthread_tryjoin_np, true);
    will_return(__wrap_pthread_tryjoin_np, errnos[i]);

    const f_status_t status = f_thread_join_try(id, 0);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_join_try__works(void **state) {

  f_thread_id_t id = f_thread_id_t_initialize;

  {
    will_return(__wrap_pthread_tryjoin_np, false);

    const f_status_t status = f_thread_join_try(id, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

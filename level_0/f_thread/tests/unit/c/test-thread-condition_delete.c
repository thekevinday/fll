#include "test-thread.h"
#include "test-thread-condition_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_condition_delete__fails(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;

  int errnos[] = {
    EBUSY,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_busy,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_cond_destroy, true);
    will_return(__wrap_pthread_cond_destroy, errnos[i]);

    const f_status_t status = f_thread_condition_delete(&condition);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_condition_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_condition_delete(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_condition_delete__works(void **state) {

  f_thread_condition_t condition = f_thread_condition_t_initialize;

  {
    will_return(__wrap_pthread_cond_destroy, false);

    const f_status_t status = f_thread_condition_delete(&condition);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-once.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_once__fails(void **state) {

  f_thread_once_t once = f_thread_once_t_initialize;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_once, true);
    will_return(__wrap_pthread_once, errnos[i]);

    const f_status_t status = f_thread_once(stub, &once);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_once__parameter_checking(void **state) {

  f_thread_once_t once = f_thread_once_t_initialize;

  {
    const f_status_t status = f_thread_once(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_once(stub, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_once(0, &once);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_once__works(void **state) {

  f_thread_once_t once = f_thread_once_t_initialize;

  {
    will_return(__wrap_pthread_once, false);

    const f_status_t status = f_thread_once(stub, &once);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

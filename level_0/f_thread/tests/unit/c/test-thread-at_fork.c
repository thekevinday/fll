#include "test-thread.h"
#include "test-thread-at_fork.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_at_fork__fails(void **state) {

  int errnos[] = {
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_memory_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_atfork, true);
    will_return(__wrap_pthread_atfork, errnos[i]);

    const f_status_t status = f_thread_at_fork(stub, stub, stub);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_at_fork__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_at_fork(0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_at_fork(stub, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_at_fork(0, stub, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_at_fork(0, 0, stub);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_at_fork(stub, stub, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_at_fork(stub, 0, stub);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_at_fork(0, stub, stub);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_at_fork__works(void **state) {

  {
    will_return(__wrap_pthread_atfork, false);

    const f_status_t status = f_thread_at_fork(stub, stub, stub);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

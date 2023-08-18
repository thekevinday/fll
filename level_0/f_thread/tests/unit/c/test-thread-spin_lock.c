#include "test-thread.h"
#include "test-thread-spin_lock.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_spin_lock__fails(void **state) {

  f_thread_spin_t spin = f_thread_spin_t_initialize;

  int errnos[] = {
    EAGAIN,
    EDEADLK,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_deadlock,
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_pthread_spin_lock, true);
    will_return(__wrap_pthread_spin_lock, errnos[i]);

    const f_status_t status = f_thread_spin_lock(&spin);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_spin_lock__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_spin_lock(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_spin_lock__works(void **state) {

  f_thread_spin_t spin = f_thread_spin_t_initialize;

  {
    will_return(__wrap_pthread_spin_lock, false);

    const f_status_t status = f_thread_spin_lock(&spin);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

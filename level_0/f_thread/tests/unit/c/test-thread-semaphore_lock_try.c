#include "test-thread.h"
#include "test-thread-semaphore_lock_try.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_lock_try__fails(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;

  int errnos[] = {
    EAGAIN,
    EINTR,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_interrupt,
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 4; ++i) {

    will_return(__wrap_sem_trywait, true);
    will_return(__wrap_sem_trywait, errnos[i]);

    const f_status_t status = f_thread_semaphore_lock_try(&semaphore);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_semaphore_lock_try__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_semaphore_lock_try(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_semaphore_lock_try__works(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;

  {
    will_return(__wrap_sem_trywait, false);

    const f_status_t status = f_thread_semaphore_lock_try(&semaphore);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

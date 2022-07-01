#include "test-thread.h"
#include "test-thread-semaphore_unlock.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_unlock__fails(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;

  int errnos[] = {
    EOVERFLOW,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_number_overflow,
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_sem_post, true);
    will_return(__wrap_sem_post, errnos[i]);

    const f_status_t status = f_thread_semaphore_unlock(&semaphore);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_semaphore_unlock__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_semaphore_unlock(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_semaphore_unlock__works(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;

  {
    will_return(__wrap_sem_post, false);

    const f_status_t status = f_thread_semaphore_unlock(&semaphore);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

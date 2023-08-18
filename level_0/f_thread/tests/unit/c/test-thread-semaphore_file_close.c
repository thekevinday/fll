#include "test-thread.h"
#include "test-thread-semaphore_file_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_file_close__fails(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_sem_close, true);
    will_return(__wrap_sem_close, errnos[i]);

    const f_status_t status = f_thread_semaphore_file_close(&semaphore);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_semaphore_file_close__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_semaphore_file_close(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_semaphore_file_close__works(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;

  {
    will_return(__wrap_sem_close, false);

    const f_status_t status = f_thread_semaphore_file_close(&semaphore);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

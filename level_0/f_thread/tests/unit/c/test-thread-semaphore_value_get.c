#include "test-thread.h"
#include "test-thread-semaphore_value_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_value_get__fails(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  int value = 0;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_sem_getvalue, true);
    will_return(__wrap_sem_getvalue, errnos[i]);

    const f_status_t status = f_thread_semaphore_value_get(&semaphore, &value);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_semaphore_value_get__parameter_checking(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  int value = 0;

  {
    const f_status_t status = f_thread_semaphore_value_get(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_semaphore_value_get(&semaphore, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_semaphore_value_get(0, &value);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_semaphore_value_get__works(void **state) {

  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  int value = 0;

  {
    will_return(__wrap_sem_getvalue, false);

    const f_status_t status = f_thread_semaphore_value_get(&semaphore, &value);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

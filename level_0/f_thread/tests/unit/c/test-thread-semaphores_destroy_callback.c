#include "test-thread.h"
#include "test-thread-semaphores_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphores_destroy_callback__fails(void **state) {

  f_thread_semaphore_t data = f_thread_semaphore_t_initialize;
  f_thread_semaphore_t data_array[] = { data };
  f_thread_semaphores_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_thread_semaphores_t datass_array[] = { datas };

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_sem_destroy, true);
    will_return(__wrap_sem_destroy, errnos[i]);

    const f_status_t status = f_thread_semaphores_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_semaphores_destroy_callback__works(void **state) {

  f_thread_semaphore_t data = f_thread_semaphore_t_initialize;
  f_thread_semaphore_t data_array[] = { data };
  f_thread_semaphores_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_thread_semaphores_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_sem_destroy, false);

    const f_status_t status = f_thread_semaphores_destroy_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

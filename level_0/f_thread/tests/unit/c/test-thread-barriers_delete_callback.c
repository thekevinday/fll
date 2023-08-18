#include "test-thread.h"
#include "test-thread-barriers_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_barriers_delete_callback__fails(void **state) {

  f_thread_barrier_t data = f_thread_barrier_t_initialize;
  f_thread_barrier_t data_array[] = { data };
  f_thread_barriers_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_thread_barriers_t datass_array[] = { datas };

  int errnos[] = {
    EBUSY,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_busy),
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 3; ++i) {
    will_return(__wrap_pthread_barrier_destroy, true);
    will_return(__wrap_pthread_barrier_destroy, errnos[i]);

    const f_status_t status = f_thread_barriers_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_barriers_delete_callback__works(void **state) {

  f_thread_barrier_t data = f_thread_barrier_t_initialize;
  f_thread_barrier_t data_array[] = { data };
  f_thread_barriers_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_thread_barriers_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_pthread_barrier_destroy, false);

    const f_status_t status = f_thread_barriers_delete_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

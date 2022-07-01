#include "test-thread.h"
#include "test-thread-spins_decimate_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_spins_decimate_by__parameter_checking(void **state) {

  const int length = 5;
  f_thread_spins_t data = f_thread_spins_t_initialize;

  {
    const f_status_t status = f_thread_spins_decimate_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_thread_spins_decimate_by__returns_data_not(void **state) {

  const int length = 5;
  f_thread_spins_t data = f_thread_spins_t_initialize;

  {
    const f_status_t status = f_thread_spins_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_thread_spins_decimate_by(0, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_thread_spins_decimate_by__works(void **state) {

  const int length = 5;
  f_thread_spins_t data = f_thread_spins_t_initialize;

  {
    const f_status_t status = f_thread_spins_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    for (uint8_t i = 0; i < length; ++i) {
      will_return(__wrap_pthread_spin_destroy, false);
    } // for

    const f_status_t status = f_thread_spins_decimate_by(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

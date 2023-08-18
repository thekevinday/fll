#include "test-memory.h"
#include "test-memory-array_decimate_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_array_decimate_by__parameter_checking(void **state) {

  const int length = 5;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_decimate_by(length, sizeof(int), 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_decimate_by(length, sizeof(int), 0, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_decimate_by(length, sizeof(int), (void **) &data.array, 0, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_decimate_by(length, sizeof(int), (void **) &data.array, &data.used, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_decimate_by(length, 0, (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.array, 0);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_memory_array_decimate_by__returns_data_not(void **state) {

  const int length = 5;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(length, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_memory_array_decimate_by(0, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_memory_array_decimate_by__works(void **state) {

  const int length = 5;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(length, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_memory_array_decimate_by(length, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

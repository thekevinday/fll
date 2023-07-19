#include "test-memory.h"
#include "test-memory-array_increase.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_array_increase__parameter_checking(void **state) {

  const int length = 5;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_increase(length, sizeof(int), 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_increase(length, sizeof(int), 0, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_increase(length, sizeof(int), (void **) &data.array, 0, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_increase(length, sizeof(int), (void **) &data.array, &data.used, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_memory_array_increase__returns_array_too_large(void **state) {

  const f_number_unsigned_t length = F_number_t_size_unsigned_d + 1;
  test_memory_array_t data = test_memory_array_t_initialize;

  data.used = F_number_t_size_unsigned_d;

  {
    const f_status_t status = f_memory_array_increase(length, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_array_too_large));
    assert_int_equal(data.used, F_number_t_size_unsigned_d);
    assert_int_equal(data.size, 0);
  }
}

void test__f_memory_array_increase__returns_data_not(void **state) {

  const int length = 5;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(length, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_memory_array_increase(0, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_memory_array_increase__works(void **state) {

  const int length = 5;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(length, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    data.used = length;

    const f_status_t status = f_memory_array_increase(1, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, length);
    assert_int_equal(data.size, length + 1);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

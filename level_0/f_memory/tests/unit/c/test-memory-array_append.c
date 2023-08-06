#include "test-memory.h"
#include "test-memory-array_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_array_append__parameter_checking(void **state) {

  const int number = 1;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_append((void *) &number, sizeof(int), 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append((void *) &number, sizeof(int), 0, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append((void *) &number, sizeof(int), (void **) &data.array, 0, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append((void *) &number, sizeof(int), (void **) &data.array, &data.used, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append((void *) &number, 0, (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append(0, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_memory_array_append__returns_array_too_large(void **state) {

  const int number = 1;
  test_memory_array_t data = test_memory_array_t_initialize;

  data.used = F_number_t_size_unsigned_d;

  {
    const f_status_t status = f_memory_array_append((void *) &number, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_array_too_large));
    assert_int_equal(data.used, F_number_t_size_unsigned_d);
    assert_int_equal(data.size, 0);
  }
}

void test__f_memory_array_append__works(void **state) {

  const int number = 1;
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_append((void *) &number, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 1);
    assert_int_equal(data.array[0], number);
    assert_int_not_equal(data.size, 0);
  }

  const f_number_unsigned_t size = data.size;
  const int number_next = 2;

  {
    const f_status_t status = f_memory_array_append((void *) &number_next, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 2);
    assert_int_equal(data.array[0], number);
    assert_int_equal(data.array[1], number_next);
    assert_int_not_equal(data.size, 0);
    assert_int_not_equal(data.size, size);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

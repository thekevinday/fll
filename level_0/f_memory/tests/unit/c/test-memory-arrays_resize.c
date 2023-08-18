#include "test-memory.h"
#include "test-memory-arrays_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_arrays_resize__parameter_checking(void **state) {

  const int length = 5;
  test_memory_arrays_t data = test_memory_arrays_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), 0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), 0, &data.used, &data.size, &test_memory_array_callback);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), (void **) &data.array, 0, &data.size, &test_memory_array_callback);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), (void **) &data.array, &data.used, 0, &test_memory_array_callback);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), (void **) &data.array, &data.used, &data.size, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_arrays_resize(length, 0, (void **) &data.array, &data.used, &data.size, &test_memory_array_callback);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_memory_arrays_resize__returns_array_too_large(void **state) {

  const f_number_unsigned_t length = F_number_t_size_unsigned_d + 1;
  test_memory_arrays_t data = test_memory_arrays_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), (void **) &data.array, &data.used, &data.size, &test_memory_array_callback);

    assert_int_equal(status, F_status_set_error(F_array_too_large));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }
}

void test__f_memory_arrays_resize__works(void **state) {

  const int length = 5;
  test_memory_arrays_t data = test_memory_arrays_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(test_memory_array_t), (void **) &data.array, &data.used, &data.size, &test_memory_array_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  // Allocate an additional location to check that the memory callback gets called and works.
  {
    const int length_inner = 2;

    const f_status_t status = f_memory_array_resize(length_inner, sizeof(int), (void **) &data.array[0].array, &data.array[0].used, &data.array[0].size);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.array[0].used, 0);
    assert_int_equal(data.array[0].size, length_inner);
  }

  {
    const f_status_t status = f_memory_arrays_resize(0, sizeof(test_memory_array_t), (void **) &data.array, &data.used, &data.size, &test_memory_array_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

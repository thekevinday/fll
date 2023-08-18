#include "test-memory.h"
#include "test-memory-array_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_array_append_all__parameter_checking(void **state) {

  int sources_array[2] = { 1, 2 };
  test_memory_array_t sources = { .array = sources_array, .used = 2, .size = 0 };
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), 0, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), (void **) &data.array, 0, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), (void **) &data.array, &data.used, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, 0, (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  {
    const f_status_t status = f_memory_array_append_all(0, sources.used, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_memory_array_append_all__returns_array_too_large(void **state) {

  int sources_array[2] = { 1, 2 };
  test_memory_array_t sources = { .array = sources_array, .used = 2, .size = 0 };
  test_memory_array_t data = test_memory_array_t_initialize;

  data.used = F_number_t_size_unsigned_d;

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_status_set_error(F_array_too_large));
    assert_int_equal(data.used, F_number_t_size_unsigned_d);
    assert_int_equal(data.size, 0);
  }
}

void test__f_memory_array_append_all__returns_data_not(void **state) {

  int sources_array[0] = { };
  test_memory_array_t sources = { .array = sources_array, .used = 0, .size = 0 };
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }
}

void test__f_memory_array_append_all__works(void **state) {

  int sources_array[2] = { 1, 2 };
  test_memory_array_t sources = { .array = sources_array, .used = 2, .size = 0 };
  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_append_all((void *) sources.array, sources.used, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 2);
    assert_int_equal(data.array[0], sources.array[0]);
    assert_int_equal(data.array[1], sources.array[1]);
    assert_int_not_equal(data.size, 0);
  }

  const f_number_unsigned_t size = data.size;

  int source_next_array[1] = { 3 };
  test_memory_array_t sources_next = { .array = source_next_array, .used = 1, .size = 0 };

  {
    const f_status_t status = f_memory_array_append_all((void *) sources_next.array, sources_next.used, sizeof(int), (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 3);
    assert_int_equal(data.array[0], sources.array[0]);
    assert_int_equal(data.array[1], sources.array[1]);
    assert_int_equal(data.array[2], sources_next.array[0]);
    assert_int_not_equal(data.size, 0);
    assert_int_not_equal(data.size, size);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

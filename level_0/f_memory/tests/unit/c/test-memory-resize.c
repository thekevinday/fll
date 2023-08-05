#include "test-memory.h"
#include "test-memory-resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_resize__parameter_checking(void **state) {

  {
    const f_status_t status = f_memory_resize(1, 4, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_memory_resize(1, 4, 1, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_memory_array_resize__returns_size_not(void **state) {

  test_memory_array_t data = test_memory_array_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(1, 0, (void **) &data.array, &data.used, &data.size);

    assert_int_equal(status, F_size_not);
    assert_int_equal(data.array, 0);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }
}

void test__f_memory_resize__works(void **state) {

  uint16_t *data = 0;

  {
    const f_status_t status = f_memory_new(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_none);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_resize(1, 4, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_none);
    assert_non_null(data);
  }

  free((void *) data);
}

#ifdef __cplusplus
} // extern "C"
#endif

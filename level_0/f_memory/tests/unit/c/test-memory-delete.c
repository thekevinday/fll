#include "test-memory.h"
#include "test-memory-delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_delete__frees_adjusted_memory(void **state) {

  uint16_t *data = 0;

  {
    const f_status_t status = f_memory_new(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_adjust(1, 4, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_delete(4, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_null(data);
  }
}

void test__f_memory_delete__frees_aligned_memory(void **state) {

  uint16_t *data = 0;

  {
    const f_status_t status = f_memory_new_aligned(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_delete(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_null(data);
  }
}

void test__f_memory_delete__frees_memory(void **state) {

  uint16_t *data = 0;

  {
    const f_status_t status = f_memory_new(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_delete(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_null(data);
  }
}

void test__f_memory_delete__frees_resized_memory(void **state) {

  uint16_t *data = 0;

  {
    const f_status_t status = f_memory_new(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_resize(1, 4, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_delete(4, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_okay);
    assert_null(data);
  }
}

void test__f_memory_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_memory_delete(4, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-memory.h"
#include "test-memory-adjust.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_adjust__parameter_checking(void **state) {

  {
    const f_status_t status = f_memory_adjust(1, 4, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_memory_adjust(1, 4, 1, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_memory_adjust__works(void **state) {

  uint16_t *data = 0;

  {
    const f_status_t status = f_memory_new(1, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_none);
    assert_non_null(data);
  }

  {
    const f_status_t status = f_memory_adjust(1, 4, sizeof(uint16_t), (void **) &data);

    assert_int_equal(status, F_none);
    assert_non_null(data);
  }

  free((void *) data);
}

#ifdef __cplusplus
} // extern "C"
#endif

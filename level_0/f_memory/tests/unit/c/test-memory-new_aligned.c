#include "test-memory.h"
#include "test-memory-new_aligned.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_memory_new_aligned__parameter_checking(void **state) {

  {
    const f_status_t status = f_memory_new_aligned(1, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_memory_new_aligned__works(void **state) {

  uint16_t *data = 0;

  const f_status_t status = f_memory_new_aligned(1, sizeof(uint16_t), (void **) &data);

  assert_int_equal(status, F_okay);
  assert_non_null(data);

  free((void *) data);
}

#ifdef __cplusplus
} // extern "C"
#endif

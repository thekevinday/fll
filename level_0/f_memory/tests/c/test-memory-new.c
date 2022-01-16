#include "test-memory.h"
#include "test-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_level_0_parameter_checking_
  void test__f_memory_new__parameter_checking(void **state) {

    {
      const f_status_t status = f_memory_new(1, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_memory_new__works(void **state) {

  uint16_t *data = 0;

  const f_status_t status = f_memory_new(1, sizeof(uint16_t), (void **) &data);

  assert_int_equal(status, F_none);
  assert_non_null(data);

  free((void *) data);
}

#ifdef __cplusplus
} // extern "C"
#endif

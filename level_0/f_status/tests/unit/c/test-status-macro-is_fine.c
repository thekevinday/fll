#include "test-status.h"
#include "test-status-macro-is_fine.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_is_fine__works(void **state) {

  assert_true(F_status_is_fine(0));
  assert_true(F_status_is_fine(F_none));
  assert_false(F_status_is_fine(F_status_bit_error));
  assert_false(F_status_is_fine(F_status_bit_signal));
  assert_false(F_status_is_fine(F_status_bit_warning));
}

#ifdef __cplusplus
} // extern "C"
#endif

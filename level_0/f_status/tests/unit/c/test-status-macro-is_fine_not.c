#include "test-status.h"
#include "test-status-macro-is_fine_not.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_is_fine_not__works(void **state) {

  assert_false(F_status_is_fine_not(0));
  assert_false(F_status_is_fine_not(F_none));
  assert_true(F_status_is_fine_not(F_status_bit_error));
  assert_true(F_status_is_fine_not(F_status_bit_signal));
  assert_true(F_status_is_fine_not(F_status_bit_warning));
}

#ifdef __cplusplus
} // extern "C"
#endif

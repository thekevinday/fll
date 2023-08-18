#include "test-status.h"
#include "test-status-macro-is_warning.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_is_warning__works(void **state) {

  assert_false(F_status_is_warning(0));
  assert_false(F_status_is_warning(F_okay));
  assert_false(F_status_is_warning(F_status_bit_error));
  assert_true(F_status_is_warning(F_status_bit_signal)); // The signal bit uses the warning bit.
  assert_true(F_status_is_warning(F_status_bit_warning));
}

#ifdef __cplusplus
} // extern "C"
#endif

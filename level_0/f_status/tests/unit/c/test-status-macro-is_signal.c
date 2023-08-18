#include "test-status.h"
#include "test-status-macro-is_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_is_signal__works(void **state) {

  assert_false(F_status_is_signal(0));
  assert_false(F_status_is_signal(F_okay));
  assert_false(F_status_is_signal(F_status_bit_error));
  assert_true(F_status_is_signal(F_status_bit_signal));
  assert_false(F_status_is_signal(F_status_bit_warning));
}

#ifdef __cplusplus
} // extern "C"
#endif

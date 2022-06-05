#include "test-status.h"
#include "test-status-macro-set_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_set_signal__works(void **state) {

  assert_true(F_status_is_signal(F_status_set_signal(0)));
  assert_true(F_status_is_signal(F_status_set_signal(F_none)));
  assert_true(F_status_is_signal(F_status_set_signal(F_status_bit_error)));
  assert_true(F_status_is_signal(F_status_set_signal(F_status_bit_signal)));
  assert_true(F_status_is_signal(F_status_set_signal(F_status_bit_warning)));
}

#ifdef __cplusplus
} // extern "C"
#endif

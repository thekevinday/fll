#include "test-status.h"
#include "test-status-macro-set_error.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_set_error__works(void **state) {

  assert_true(F_status_is_error(F_status_set_error(0)));
  assert_true(F_status_is_error(F_status_set_error(F_okay)));
  assert_true(F_status_is_error(F_status_set_error(F_status_bit_error)));
  assert_true(F_status_is_error(F_status_set_error(F_status_bit_signal)));
  assert_true(F_status_is_error(F_status_set_error(F_status_bit_warning)));
}

#ifdef __cplusplus
} // extern "C"
#endif

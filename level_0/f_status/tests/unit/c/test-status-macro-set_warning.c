#include "test-status.h"
#include "test-status-macro-set_warning.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_set_warning__works(void **state) {

  assert_true(F_status_is_warning(F_status_set_warning(0)));
  assert_true(F_status_is_warning(F_status_set_warning(F_none)));
  assert_true(F_status_is_warning(F_status_set_warning(F_status_bit_error)));
  assert_true(F_status_is_warning(F_status_set_warning(F_status_bit_signal)));
  assert_true(F_status_is_warning(F_status_set_warning(F_status_bit_warning)));
}

#ifdef __cplusplus
} // extern "C"
#endif

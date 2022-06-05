#include "test-status.h"
#include "test-status-macro-is_problem_not.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__F_status_is_problem_not__works(void **state) {

  assert_true(F_status_is_problem_not(0));
  assert_true(F_status_is_problem_not(F_none));
  assert_false(F_status_is_problem_not(F_status_bit_error));
  assert_false(F_status_is_problem_not(F_status_bit_signal));
  assert_false(F_status_is_problem_not(F_status_bit_warning));
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-status.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test__F_status_is_error__works),
    cmocka_unit_test(test__F_status_is_fine__works),
    cmocka_unit_test(test__F_status_is_problem__works),
    cmocka_unit_test(test__F_status_is_signal__works),
    cmocka_unit_test(test__F_status_is_warning__works),

    cmocka_unit_test(test__F_status_is_error_not__works),
    cmocka_unit_test(test__F_status_is_fine_not__works),
    cmocka_unit_test(test__F_status_is_problem_not__works),
    cmocka_unit_test(test__F_status_is_signal_not__works),
    cmocka_unit_test(test__F_status_is_warning_not__works),

    cmocka_unit_test(test__F_status_set_error__works),
    cmocka_unit_test(test__F_status_set_fine__works),
    cmocka_unit_test(test__F_status_set_signal__works),
    cmocka_unit_test(test__F_status_set_warning__works),
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif

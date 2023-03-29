#include "test-compare.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  errno = 0;

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {

    cmocka_unit_test(test__f_compare___works),
    cmocka_unit_test(test__f_compare_dynamic__works),
    cmocka_unit_test(test__f_compare_dynamic_partial__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_dynamic__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_except__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_except_dynamic__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_except_string__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_except_trim__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_except_trim_dynamic__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_except_trim_string__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_string__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_trim__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_trim_dynamic__works),
    cmocka_unit_test(test__f_compare_dynamic_partial_trim_string__works),
    cmocka_unit_test(test__f_compare_dynamic_string__works),
    cmocka_unit_test(test__f_compare_dynamic_trim__trims),
    cmocka_unit_test(test__f_compare_dynamic_trim__something_misses_nothing),
    cmocka_unit_test(test__f_compare_dynamic_trim__works),
    cmocka_unit_test(test__f_compare_dynamic_trim_string__trims),
    cmocka_unit_test(test__f_compare_dynamic_trim_string__something_misses_nothing),
    cmocka_unit_test(test__f_compare_dynamic_trim_string__works),
    cmocka_unit_test(test__f_compare_dynamic_except__works),
    cmocka_unit_test(test__f_compare_dynamic_except_string__works),
    cmocka_unit_test(test__f_compare_dynamic_except_trim__works),
    cmocka_unit_test(test__f_compare_dynamic_except_trim_string__works),
    cmocka_unit_test(test__f_compare_except__works),
    cmocka_unit_test(test__f_compare_except_trim__works),
    cmocka_unit_test(test__f_compare_trim__trims),
    cmocka_unit_test(test__f_compare_trim__something_misses_nothing),
    cmocka_unit_test(test__f_compare_trim__works),

    #ifndef _di_level_0_parameter_checking_
      // f_compare() doesn't use parameter checking.
      // f_compare_dynamic() doesn't use parameter checking.
      // f_compare_dynamic_partial() doesn't use parameter checking.
      // f_compare_dynamic_partial_dynamic() doesn't use parameter checking.
      // f_compare_dynamic_partial_except() doesn't use parameter checking.
      // f_compare_dynamic_partial_except_dynamic() doesn't use parameter checking.
      // f_compare_dynamic_partial_except_string() doesn't use parameter checking.
      // f_compare_dynamic_partial_except_trim() doesn't use parameter checking.
      // f_compare_dynamic_partial_except_trim_dynamic() doesn't use parameter checking.
      // f_compare_dynamic_partial_except_trim_string() doesn't use parameter checking.
      // f_compare_dynamic_partial_string() doesn't use parameter checking.
      // f_compare_dynamic_partial_trim_dynamic() doesn't use parameter checking.
      // f_compare_dynamic_string() doesn't use parameter checking.
      // f_compare_dynamic_trim() doesn't use parameter checking.
      // f_compare_dynamic_trim_string() doesn't use parameter checking.
      // f_compare_dynamic_except() doesn't use parameter checking.
      // f_compare_dynamic_except_string() doesn't use parameter checking.
      // f_compare_dynamic_except_trim() doesn't use parameter checking.
      // f_compare_dynamic_except_trim_string() doesn't use parameter checking.
      // f_compare_except() doesn't use parameter checking.
      // f_compare_except_trim() doesn't use parameter checking.
      // f_compare_trim() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif

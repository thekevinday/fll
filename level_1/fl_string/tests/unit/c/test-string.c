#include "test-string.h"

#ifdef __cplusplus
extern "C" {
#endif

const f_string_range_t f_string_range_empty_c = f_string_range_t_initialize;

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  errno = 0;

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {

    cmocka_unit_test(test__fl_string_compare__works),
    cmocka_unit_test(test__fl_string_dynamic_compare__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_dynamic__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_except__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_except_dynamic__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_except_string__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_except_trim__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_except_trim_dynamic__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_except_trim_string__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_string__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_trim__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_trim_dynamic__works),
    cmocka_unit_test(test__fl_string_dynamic_partial_compare_trim_string__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_string__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_trim__trims),
    cmocka_unit_test(test__fl_string_dynamic_compare_trim__something_misses_nothing),
    cmocka_unit_test(test__fl_string_dynamic_compare_trim__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_trim_string__trims),
    cmocka_unit_test(test__fl_string_dynamic_compare_trim_string__something_misses_nothing),
    cmocka_unit_test(test__fl_string_dynamic_compare_trim_string__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_except__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_except_string__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_except_trim__works),
    cmocka_unit_test(test__fl_string_dynamic_compare_except_trim_string__works),
    cmocka_unit_test(test__fl_string_compare_except__works),
    cmocka_unit_test(test__fl_string_compare_except_trim__works),
    cmocka_unit_test(test__fl_string_compare_trim__trims),
    cmocka_unit_test(test__fl_string_compare_trim__something_misses_nothing),
    cmocka_unit_test(test__fl_string_compare_trim__works),

    #ifndef _di_level_0_parameter_checking_
      // fl_string_compare() doesn't use parameter checking.
      // fl_string_dynamic_compare() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_dynamic() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_except() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_except_dynamic() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_except_string() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_except_trim() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_except_trim_dynamic() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_except_trim_string() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_string() doesn't use parameter checking.
      // fl_string_dynamic_partial_compare_trim_dynamic() doesn't use parameter checking.
      // fl_string_dynamic_compare_string() doesn't use parameter checking.
      // fl_string_dynamic_compare_trim() doesn't use parameter checking.
      // fl_string_dynamic_compare_trim_string() doesn't use parameter checking.
      // fl_string_dynamic_compare_except() doesn't use parameter checking.
      // fl_string_dynamic_compare_except_string() doesn't use parameter checking.
      // fl_string_dynamic_compare_except_trim() doesn't use parameter checking.
      // fl_string_dynamic_compare_except_trim_string() doesn't use parameter checking.
      // fl_string_compare_except() doesn't use parameter checking.
      // fl_string_compare_except_trim() doesn't use parameter checking.
      // fl_string_compare_trim() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif

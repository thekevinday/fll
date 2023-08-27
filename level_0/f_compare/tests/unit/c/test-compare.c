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

    cmocka_unit_test(test__f_compare_utf__works),
    cmocka_unit_test(test__f_compare_utf_dynamic__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_dynamic__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_except__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_except_dynamic__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_except_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_except_trim__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_except_trim_dynamic__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_except_trim_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_trim__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_trim_dynamic__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_partial_trim_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_trim__trims),
    cmocka_unit_test(test__f_compare_utf_dynamic_trim__something_misses_nothing),
    cmocka_unit_test(test__f_compare_utf_dynamic_trim__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_trim_string__trims),
    cmocka_unit_test(test__f_compare_utf_dynamic_trim_string__something_misses_nothing),
    cmocka_unit_test(test__f_compare_utf_dynamic_trim_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_except__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_except_string__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_except_trim__works),
    cmocka_unit_test(test__f_compare_utf_dynamic_except_trim_string__works),
    cmocka_unit_test(test__f_compare_utf_except__works),
    cmocka_unit_test(test__f_compare_utf_except_trim__works),
    cmocka_unit_test(test__f_compare_utf_trim__trims),
    cmocka_unit_test(test__f_compare_utf_trim__something_misses_nothing),
    cmocka_unit_test(test__f_compare_utf_trim__works),

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

      // f_compare_utf() doesn't use parameter checking.
      // f_compare_utf_dynamic() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_dynamic() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_except() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_except_dynamic() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_except_string() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_except_trim() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_except_trim_dynamic() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_except_trim_string() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_string() doesn't use parameter checking.
      // f_compare_utf_dynamic_partial_trim_dynamic() doesn't use parameter checking.
      // f_compare_utf_dynamic_string() doesn't use parameter checking.
      // f_compare_utf_dynamic_trim() doesn't use parameter checking.
      // f_compare_utf_dynamic_trim_string() doesn't use parameter checking.
      // f_compare_utf_dynamic_except() doesn't use parameter checking.
      // f_compare_utf_dynamic_except_string() doesn't use parameter checking.
      // f_compare_utf_dynamic_except_trim() doesn't use parameter checking.
      // f_compare_utf_dynamic_except_trim_string() doesn't use parameter checking.
      // f_compare_utf_except() doesn't use parameter checking.
      // f_compare_utf_except_trim() doesn't use parameter checking.
      // f_compare_utf_trim() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

f_status_t test_convert_dynamic_to_utf(const f_string_static_t dynamic, f_utf_string_dynamic_t * const utf) {

  f_status_t status = f_memory_array_resize(dynamic.used, sizeof(f_utf_char_t), (void **) &utf->string, &utf->used, &utf->size);
  if (F_status_is_error(status)) return status;

  utf->used = 0;

  for (f_number_unsigned_t i = 0; i < dynamic.used; ++i, ++utf->used) {

    status = f_utf_char_to_character(dynamic.string + i, dynamic.used - i, &utf->string[i]);
    if (F_status_is_error(status)) return status;
  } // for

  return F_okay;
}

#ifdef __cplusplus
} // extern "C"
#endif

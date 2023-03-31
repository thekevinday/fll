#include "test-utf.h"

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

    cmocka_unit_test(test__fl_utf_string_compare__works),
    cmocka_unit_test(test__fl_utf_string_compare_trim__trims),
    cmocka_unit_test(test__fl_utf_string_compare_trim__something_misses_nothing),
    cmocka_unit_test(test__fl_utf_string_compare_trim__works),
    cmocka_unit_test(test__fl_utf_string_dynamic_compare__works),
    cmocka_unit_test(test__fl_utf_string_dynamic_compare_trim__trims),
    cmocka_unit_test(test__fl_utf_string_dynamic_compare_trim__something_misses_nothing),
    cmocka_unit_test(test__fl_utf_string_dynamic_compare_trim__works),
    cmocka_unit_test(test__fl_utf_string_dynamic_partial_compare__works),
    cmocka_unit_test(test__fl_utf_string_dynamic_partial_compare_trim__works),

    #ifndef _di_level_0_parameter_checking_
      // fl_utf_string_compare() doesn't use parameter checking.
      // fl_utf_string_compare_trim() doesn't use parameter checking.
      // fl_utf_string_dynamic_compare() doesn't use parameter checking.
      // fl_utf_string_dynamic_compare_trim() doesn't use parameter checking.
      // fl_utf_string_dynamic_partial_compare() doesn't use parameter checking.
      // fl_utf_string_dynamic_partial_compare_trim() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

f_status_t test_convert_dynamic_to_utf(const f_string_static_t dynamic, f_utf_string_dynamic_t * const utf) {

  f_status_t status = f_utf_string_dynamic_resize(dynamic.used, utf);
  if (F_status_is_error(status)) return status;

  utf->used = 0;

  for (f_array_length_t i = 0; i < dynamic.used; ++i, ++utf->used) {

    status = f_utf_char_to_character(dynamic.string + i, dynamic.used - i, &utf->string[i]);
    if (F_status_is_error(status)) return status;
  } // for

  return F_none;
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-conversion.h"

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

    cmocka_unit_test(test__f_conversion_character_is_binary__works),

    cmocka_unit_test(test__f_conversion_character_is_decimal__works),

    cmocka_unit_test(test__f_conversion_character_is_duodecimal__works),

    cmocka_unit_test(test__f_conversion_character_is_hexidecimal__works),

    cmocka_unit_test(test__f_conversion_character_is_octal__works),

    cmocka_unit_test(test__f_conversion_character_to_binary__fails),
    cmocka_unit_test(test__f_conversion_character_to_binary__works),

    cmocka_unit_test(test__f_conversion_character_to_decimal__fails),
    cmocka_unit_test(test__f_conversion_character_to_decimal__works),

    cmocka_unit_test(test__f_conversion_character_to_duodecimal__fails),
    cmocka_unit_test(test__f_conversion_character_to_duodecimal__works),

    cmocka_unit_test(test__f_conversion_character_to_hexidecimal__fails),
    cmocka_unit_test(test__f_conversion_character_to_hexidecimal__works),

    cmocka_unit_test(test__f_conversion_character_to_octal__fails),
    cmocka_unit_test(test__f_conversion_character_to_octal__works),

    cmocka_unit_test(test__f_conversion_number_signed_print__fails),
    cmocka_unit_test(test__f_conversion_number_signed_print__fails_for_prepend),
    cmocka_unit_test(test__f_conversion_number_signed_print__fails_for_zero),

    cmocka_unit_test(test__f_conversion_number_signed_print__works),
    cmocka_unit_test(test__f_conversion_number_signed_print__works_for_zero),
    cmocka_unit_test(test__f_conversion_number_signed_print__works_for_zero_with_width_zero),

    cmocka_unit_test(test__f_conversion_number_signed_to_string__works),
    cmocka_unit_test(test__f_conversion_number_signed_to_string__works_for_prepend),
    cmocka_unit_test(test__f_conversion_number_signed_to_string__works_for_zero),

    cmocka_unit_test(test__f_conversion_number_unsigned_print__fails),
    cmocka_unit_test(test__f_conversion_number_unsigned_print__fails_for_prepend),
    cmocka_unit_test(test__f_conversion_number_unsigned_print__fails_for_zero),

    cmocka_unit_test(test__f_conversion_number_unsigned_print__works),
    cmocka_unit_test(test__f_conversion_number_unsigned_print__works_for_zero),
    cmocka_unit_test(test__f_conversion_number_unsigned_print__works_for_zero_with_width_zero),

    cmocka_unit_test(test__f_conversion_number_unsigned_to_string__works),
    cmocka_unit_test(test__f_conversion_number_unsigned_to_string__works_for_prepend),
    cmocka_unit_test(test__f_conversion_number_unsigned_to_string__works_for_zero),

    #ifndef _di_level_0_parameter_checking_
      // f_conversion_character_is_binary() doesn't use parameter checking.
      // f_conversion_character_is_decimal() doesn't use parameter checking.
      // f_conversion_character_is_duodecimal() doesn't use parameter checking.
      // f_conversion_character_is_hexidecimal() doesn't use parameter checking.
      // f_conversion_character_is_octal() doesn't use parameter checking.
      cmocka_unit_test(test__f_conversion_character_to_binary__parameter_checking),
      cmocka_unit_test(test__f_conversion_character_to_decimal__parameter_checking),
      cmocka_unit_test(test__f_conversion_character_to_duodecimal__parameter_checking),
      cmocka_unit_test(test__f_conversion_character_to_hexidecimal__parameter_checking),
      cmocka_unit_test(test__f_conversion_character_to_octal__parameter_checking),
      cmocka_unit_test(test__f_conversion_number_signed_print__parameter_checking),
      cmocka_unit_test(test__f_conversion_number_signed_to_string__parameter_checking),
      cmocka_unit_test(test__f_conversion_number_unsigned_print__parameter_checking),
      cmocka_unit_test(test__f_conversion_number_unsigned_to_string__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif

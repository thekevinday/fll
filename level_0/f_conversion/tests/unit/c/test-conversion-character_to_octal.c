#include "test-conversion.h"
#include "test-conversion-character_to_octal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_character_to_octal__fails(void **state) {

  uint8_t number;

  for (uint8_t i = 0; i <= 0xff; ++i) {

    const f_status_t status = f_conversion_character_to_octal(i, &number);

    switch (i) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        assert_true(F_status_is_error_not(status));
        break;

      default:
        assert_true(F_status_is_error(status));
        break;
    }

    if (i == 0xff) break;
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_conversion_character_to_octal__parameter_checking(void **state) {

    {
      const f_status_t status = f_conversion_character_to_octal(0, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_conversion_character_to_octal__works(void **state) {

  uint8_t number;

  for (uint8_t i = '0'; i <= '7'; ++i) {

    number = 255;

    f_conversion_character_to_octal(i, &number);

    switch (i) {
      case '0':
        assert_int_equal(number, 0);
        break;

      case '1':
        assert_int_equal(number, 1);
        break;

      case '2':
        assert_int_equal(number, 2);
        break;

      case '3':
        assert_int_equal(number, 3);
        break;

      case '4':
        assert_int_equal(number, 4);
        break;

      case '5':
        assert_int_equal(number, 5);
        break;

      case '6':
        assert_int_equal(number, 6);
        break;

      case '7':
        assert_int_equal(number, 7);
        break;
    }

    if (i == '7') break;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

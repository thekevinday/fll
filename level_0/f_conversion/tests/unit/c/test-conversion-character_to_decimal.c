#include "test-conversion.h"
#include "test-conversion-character_to_decimal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_character_to_decimal__fails(void **state) {

  uint8_t number;

  for (uint8_t i = 0; i <= 0xff; ++i) {

    const f_status_t status = f_conversion_character_to_decimal(i, &number);

    switch (i) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
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
  void test__f_conversion_character_to_decimal__parameter_checking(void **state) {

    {
      const f_status_t status = f_conversion_character_to_decimal(0, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_conversion_character_to_decimal__works(void **state) {

  uint8_t number;

  for (uint8_t i = '0'; i <= '9'; ++i) {

    number = 255;

    f_conversion_character_to_decimal(i, &number);

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

      case '8':
        assert_int_equal(number, 8);
        break;

      case '9':
        assert_int_equal(number, 9);
        break;

      default:
        break;
    }

    if (i == '9') break;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

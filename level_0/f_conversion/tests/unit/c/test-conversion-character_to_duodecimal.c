#include "test-conversion.h"
#include "test-conversion-character_to_duodecimal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_character_to_duodecimal__fails(void **state) {

  uint8_t number;

  for (uint8_t i = 0; i <= 0xff; ++i) {

    const f_status_t status = f_conversion_character_to_duodecimal(i, &number);

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
      case 'a':
      case 'A':
      case 'b':
      case 'B':
        assert_true(F_status_is_error_not(status));
        break;

      default:
        assert_true(F_status_is_error(status));
        break;
    }

    if (i == 0xff) break;
  } // for
}

void test__f_conversion_character_to_duodecimal__parameter_checking(void **state) {

  {
    const f_status_t status = f_conversion_character_to_duodecimal(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_conversion_character_to_duodecimal__works(void **state) {

  uint8_t number;

  for (uint8_t i = '0'; i <= 'b'; ++i) {

    number = 255;

    f_conversion_character_to_duodecimal(i, &number);

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

      case 'a':
      case 'A':
        assert_int_equal(number, 10);
        break;

      case 'b':
      case 'B':
        assert_int_equal(number, 11);
        break;

      default:
        break;
    }

    if (i == 'b') break;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

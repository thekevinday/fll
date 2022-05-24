#include "test-conversion.h"
#include "test-conversion-character_to_binary.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_character_to_binary__fails(void **state) {

  uint8_t number;

  for (uint8_t i = 0; i <= 0xff; ++i) {

    const f_status_t status = f_conversion_character_to_binary(i, &number);

    switch (i) {
      case '0':
      case '1':
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
  void test__f_conversion_character_to_binary__parameter_checking(void **state) {

    {
      const f_status_t status = f_conversion_character_to_binary(0, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_conversion_character_to_binary__works(void **state) {

  uint8_t number;

  for (uint8_t i = '0'; i <= '1'; ++i) {

    number = 255;

    f_conversion_character_to_binary(i, &number);

    switch (i) {
      case '0':
        assert_int_equal(number, 0);
        break;

      case '1':
        assert_int_equal(number, 1);
        break;

      default:
        break;
    }

    if (i == '1') break;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

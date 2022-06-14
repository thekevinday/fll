#include "test-utf.h"
#include "test-utf-character_is_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_character_is_valid__works(void **state) {

  for (uint32_t character = 0; character < UINT32_MAX; ++character) {

    const uint8_t first = macro_f_utf_char_t_to_char_1(character);
    const uint8_t second = macro_f_utf_char_t_to_char_2(character);
    const uint8_t third = macro_f_utf_char_t_to_char_3(character);
    const uint8_t fourth = macro_f_utf_char_t_to_char_4(character);

    const f_status_t status = f_utf_character_is_valid(character);

    // Valid: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx.
    if ((first & 0b11111000) == 0b11111000) {
      assert_false(status);
    }
    else if ((first & 0b11111000) == 0b11110000) {
      if ((second & 0b11000000) == 0b10000000 && (third & 0b11000000) == 0b10000000 && (fourth & 0b11000000) == 0b10000000) {
        assert_true(status);
      }
      else {
        assert_false(status);
      }
    }

    // Valid: 1110xxxx 10xxxxxx 10xxxxxx 00000000.
    else if ((first & 0b11110000) == 0b11100000) {
      if ((second & 0b11000000) == 0b10000000 && (third & 0b11000000) == 0b10000000) {
        assert_true(status);
      }
      else {
        assert_false(status);
      }
    }

    // Valid: 110xxxxx 10xxxxxx 00000000 00000000.
    else if ((first & 0b11100000) == 0b11000000) {
      if ((second & 0b11000000) == 0b10000000) {
        assert_true(status);
      }
      else {
        assert_false(status);
      }
    }

    // Invalid (UTF Fragment): 10xxxxxx 00000000 00000000 00000000.
    else if ((first & 0b11000000) == 0b10000000) {
      assert_int_equal(status, F_status_set_error(F_utf_fragment));
    }

    // Valid: 0xxxxxxx 00000000 00000000 00000000.
    else if (!(first & 0b10000000)) {
      assert_true(status);
    }
    else {
      assert_false(status);
    }
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

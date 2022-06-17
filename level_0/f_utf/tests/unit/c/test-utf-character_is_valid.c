#include "test-utf.h"
#include "test-utf-character_is_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_character_is_valid__works(void **state) {

  for (f_utf_char_t character = 0; character < UINT32_MAX; ++character) {

    const uint8_t first = macro_f_utf_char_t_to_char_1(character);
    const uint8_t second = macro_f_utf_char_t_to_char_2(character);
    const uint8_t third = macro_f_utf_char_t_to_char_3(character);
    const uint8_t fourth = macro_f_utf_char_t_to_char_4(character);
    const uint8_t width = macro_f_utf_char_t_width_is(character);

    const f_status_t status = f_utf_character_is_valid(character);

    // All remaining bytes after width must be zero for valid character.
    if (width == 0 && (second || third || fourth)) {
      assert_int_equal(status, F_false);
    }
    else if (width == 1) {
      assert_int_equal(status, F_status_set_error(F_utf_fragment));
    }
    else if (width == 2 && (third || fourth)) {
      assert_int_equal(status, F_false);
    }
    else if (width == 3 && fourth) {
      assert_int_equal(status, F_false);
    }
    else {

      // Valid: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx.
      if ((first & 0b11111000) == 0b11111000) {
        assert_int_equal(status, F_false);
      }
      else if ((first & 0b11111000) == 0b11110000) {
        if ((second & 0b11000000) == 0b10000000 && (third & 0b11000000) == 0b10000000 && (fourth & 0b11000000) == 0b10000000) {
          assert_int_equal(status, F_true);
        }
        else {
          assert_int_equal(status, F_false);
        }
      }

      // Valid: 1110xxxx 10xxxxxx 10xxxxxx 00000000.
      else if ((first & 0b11110000) == 0b11100000) {
        if ((second & 0b11000000) == 0b10000000 && (third & 0b11000000) == 0b10000000) {
          assert_int_equal(status, F_true);
        }
        else {
          assert_int_equal(status, F_false);
        }
      }

      // Valid: 110xxxxx 10xxxxxx 00000000 00000000.
      else if ((first & 0b11100000) == 0b11000000) {
        if ((second & 0b11000000) == 0b10000000) {
          assert_int_equal(status, F_true);
        }
        else {
          assert_int_equal(status, F_false);
        }
      }

      // Invalid (UTF Fragment): 10xxxxxx 00000000 00000000 00000000.
      else if ((first & 0b11000000) == 0b10000000) {
        assert_int_equal(status, F_status_set_error(F_utf_fragment));
      }

      // Valid: 0xxxxxxx 00000000 00000000 00000000.
      else if (first & 0b10000000) {
        assert_int_equal(status, F_false);
      }
      else {
        assert_int_equal(status, F_true);
      }
    }
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

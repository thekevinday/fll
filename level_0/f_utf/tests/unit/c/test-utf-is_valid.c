#include "test-utf.h"
#include "test-utf-is_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_is_valid__works(void **state) {

  for (uint32_t sequence = 0; sequence < UINT32_MAX; ++sequence) {

    const uint8_t first = macro_f_utf_char_t_to_char_1(sequence);
    const uint8_t second = macro_f_utf_char_t_to_char_2(sequence);
    const uint8_t third = macro_f_utf_char_t_to_char_3(sequence);
    const uint8_t fourth = macro_f_utf_char_t_to_char_4(sequence);

    char buffer[5] = { first, second, third, fourth, 0 };

    // This function only checks validity based on width and does not look at unknown data.
    const f_status_t status = f_utf_is_valid(buffer, 5);

    // Invalid: 11111xxx xxxxxxxx xxxxxxxx xxxxxxxx.
    if ((first & 0b11111000) == 0b11111000) {
      assert_int_equal(status, F_false);

      continue;
    }

    // Valid: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx.
    if ((first & 0b11111000) == 0b11110000) {

      // For first byte 0xf0, only second byte ranges 0x90 to 0xbf are valid.
      if (first == 0xf0) {
        if (second < 0x90 || second > 0xbf) {
          assert_int_equal(status, F_false);

          continue;
        }
      }

      // For first byte 0xf4, only second byte ranges 0x80 to 0x8f are valid.
      else if (first == 0xf4) {
        if (second < 0x80 || second > 0x8f) {
          assert_int_equal(status, F_false);

          continue;
        }
      }

      // For first byte greater than 0xf4 are all invalid.
      else if (first > 0xf4) {
        assert_int_equal(status, F_false);

        continue;
      }

      if ((second & 0b11000000) == 0b10000000 && (third & 0b11000000) == 0b10000000 && (fourth & 0b11000000) == 0b10000000) {
        assert_int_equal(status, F_true);

        continue;
      }

      assert_int_equal(status, F_false);

      continue;
    }

    // Valid: 1110xxxx 10xxxxxx 10xxxxxx ????????.
    if ((first & 0b11110000) == 0b11100000) {

      // For first byte 0xe0, only second byte ranges 0xa0 to 0xbf are valid.
      if (first == 0xe0) {
        if (second < 0xa0 || second > 0xbf) {
          assert_int_equal(status, F_false);

          continue;
        }
      }

      // For first byte 0xed, only second byte ranges 0x80 to 0x9f are valid.
      else if (first == 0xed) {
        if (second < 0x80 || second > 0x9f) {
          assert_int_equal(status, F_false);

          continue;
        }
      }

      if ((second & 0b11000000) == 0b10000000 && (third & 0b11000000) == 0b10000000) {
        assert_int_equal(status, F_true);

        continue;
      }

      assert_int_equal(status, F_false);

      continue;
    }

    // Valid: 110xxxxx 10xxxxxx ???????? ????????.
    if ((first & 0b11100000) == 0b11000000) {

      // Only first byte ranges 0xc3 or greater are valid.
      if (second < 0xc3) {
        assert_int_equal(status, F_false);

        continue;
      }

      if ((second & 0b11000000) == 0b10000000) {
        assert_int_equal(status, F_true);

        continue;
      }

      assert_int_equal(status, F_false);

      continue;
    }

    // Invalid (UTF Fragment): 10xxxxxx ???????? ???????? ????????.
    if ((first & 0b11000000) == 0b10000000) {
      assert_int_equal(status, F_status_set_error(F_utf_fragment));

      continue;
    }

    // Valid: 0xxxxxxx ???????? ???????? ????????.
    if (first < 0x80) {
      assert_int_equal(status, F_true);

      continue;
    }

    // All other values > 0x7f are invalid.
    assert_int_equal(status, F_false);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

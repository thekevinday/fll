#include "test-utf.h"
#include "test-utf-character_is_alphabetic_digit.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void private__test__f_utf_character_is_alphabetic_digit__works(const f_status_t status, const f_utf_char_t sequence) {

  if (!f_utf_character_is_valid(sequence)) {
    if (macro_f_utf_char_t_width_is(sequence) == 1) {
      assert_int_equal(status, F_status_set_error(F_utf_fragment));
    }
    else {
      assert_int_equal(status, F_false);
    }
  }
  else if (f_utf_character_is_digit(sequence, 0)) {
    assert_int_equal(status, F_true);
  }
  else if (f_utf_character_is_zero_width(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_control(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_control_picture(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_combining(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_whitespace(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_whitespace_modifier(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_numeric(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_punctuation(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_symbol(sequence)) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_phonetic(sequence)) {
    assert_int_equal(status, F_false);
  }
  else {
    assert_int_equal(status, F_true);
  }
}

void test__f_utf_character_is_alphabetic_digit__works(void **state) {

  // To save time and effort, this test cheats by assuming the other functions are correct.
  // Use the other functions to determine what the correct return result should be.
  f_utf_char_t sequence = f_utf_char_t_initialize;

  uint8_t first = 0;
  uint8_t second = 0;
  uint8_t third = 0;
  uint8_t fourth = 0;

  // 1-Byte (ASCII).
  for (first = 0x00; first < 0x80; ++first) {

    sequence = macro_f_utf_char_t_from_char_1(first);

    private__test__f_utf_character_is_alphabetic_digit__works(f_utf_character_is_alphabetic_digit(sequence, 0), sequence);
  } // for

  // 2-Byte (ASCII).
  for (first = 0xc2; first < 0xe0; ++first) {

    for (second = 0x80; second < 0xbf; ++second) {

      sequence = macro_f_utf_char_t_from_char_1(first) | macro_f_utf_char_t_from_char_2(second);

      private__test__f_utf_character_is_alphabetic_digit__works(f_utf_character_is_alphabetic_digit(sequence, 0), sequence);
    } // for
  } // for

  // 3-Byte (ASCII).
  for (first = 0xe0; first < 0xf0; ++first) {

    for (second = 0x80; second < 0xbf; ++second) {

      for (third = 0x80; third < 0xbf; ++third) {

        sequence = macro_f_utf_char_t_from_char_1(first) | macro_f_utf_char_t_from_char_2(second) | macro_f_utf_char_t_from_char_3(third);

        private__test__f_utf_character_is_alphabetic_digit__works(f_utf_character_is_alphabetic_digit(sequence, 0), sequence);
      } // for
    } // for
  } // for

  // 4-Byte (ASCII).
  for (first = 0xf0; first < 0xf8; ++first) {

    for (second = 0x80; second < 0xbf; ++second) {

      for (third = 0x80; third < 0xbf; ++third) {

        for (fourth = 0x80; fourth < 0xbf; ++fourth) {

          sequence = macro_f_utf_char_t_from_char_1(first) | macro_f_utf_char_t_from_char_2(second) | macro_f_utf_char_t_from_char_3(third) | macro_f_utf_char_t_from_char_4(fourth);

          private__test__f_utf_character_is_alphabetic_digit__works(f_utf_character_is_alphabetic_digit(sequence, 0), sequence);
        } // for
      } // for
    } // for
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

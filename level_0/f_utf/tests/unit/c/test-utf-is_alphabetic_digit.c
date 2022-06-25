#include "test-utf.h"
#include "test-utf-is_alphabetic_digit.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void private__test__f_utf_is_alphabetic_digit__works(const f_status_t status, const f_utf_char_t sequence) {

  if (f_utf_character_is_valid(sequence) != F_true) {
    if (macro_f_utf_char_t_width_is(sequence) == 1) {
      assert_int_equal(status, F_status_set_error(F_utf_fragment));
    }
    else {
      assert_int_equal(status, F_false);
    }
  }
  else if (f_utf_character_is_digit(sequence, 0) == F_true) {
    assert_int_equal(status, F_true);
  }
  else if (f_utf_character_is_zero_width(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_control(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_control_picture(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_combining(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_whitespace(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_whitespace_modifier(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_numeric(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_punctuation(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_symbol(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else if (f_utf_character_is_phonetic(sequence) == F_true) {
    assert_int_equal(status, F_false);
  }
  else {
    assert_int_equal(status, F_true);
  }
}

void test__f_utf_is_alphabetic_digit__works(void **state) {

  // To save time and effort, this test cheats by assuming the other functions are correct.
  // Use the other functions to determine what the correct return result should be.
  f_utf_char_t sequence = f_utf_char_t_initialize;

  uint8_t buffer[5] = { 0, 0, 0, 0, 0 };

  // 1-Byte (ASCII).
  for (buffer[0] = 0x00; buffer[0] < 0x80; ++buffer[0]) {

    sequence = macro_f_utf_char_t_from_char_1(buffer[0]);

    private__test__f_utf_is_alphabetic_digit__works(f_utf_is_alphabetic_digit((f_string_t) buffer, 5, 0), sequence);
  } // for

  // 2-Byte (ASCII).
  for (buffer[0] = 0xc2; buffer[0] < 0xe0; ++buffer[0]) {

    for (buffer[1] = 0x80; buffer[1] < 0xbf; ++buffer[1]) {

      sequence = macro_f_utf_char_t_from_char_1(buffer[0]) | macro_f_utf_char_t_from_char_2(buffer[1]);

      private__test__f_utf_is_alphabetic_digit__works(f_utf_is_alphabetic_digit((f_string_t) buffer, 5, 0), sequence);
    } // for
  } // for

  buffer[1] = 0;

  // 3-Byte (ASCII).
  for (buffer[0] = 0xe0; buffer[0] < 0xf0; ++buffer[0]) {

    for (buffer[1] = 0x80; buffer[1] < 0xbf; ++buffer[1]) {

      for (buffer[2] = 0x80; buffer[2] < 0xbf; ++buffer[2]) {

        sequence = macro_f_utf_char_t_from_char_1(buffer[0]) | macro_f_utf_char_t_from_char_2(buffer[1]) | macro_f_utf_char_t_from_char_3(buffer[2]);

        private__test__f_utf_is_alphabetic_digit__works(f_utf_is_alphabetic_digit((f_string_t) buffer, 5, 0), sequence);
      } // for
    } // for
  } // for

  buffer[1] = 0;
  buffer[2] = 0;

  // 4-Byte (ASCII).
  for (buffer[0] = 0xf0; buffer[0] < 0xf8; ++buffer[0]) {

    for (buffer[1] = 0x80; buffer[1] < 0xbf; ++buffer[1]) {

      for (buffer[2] = 0x80; buffer[2] < 0xbf; ++buffer[2]) {

        for (buffer[3] = 0x80; buffer[3] < 0xbf; ++buffer[3]) {

          sequence = macro_f_utf_char_t_from_char_1(buffer[0]) | macro_f_utf_char_t_from_char_2(buffer[1]) | macro_f_utf_char_t_from_char_3(buffer[2]) | macro_f_utf_char_t_from_char_4(buffer[3]);

          private__test__f_utf_is_alphabetic_digit__works(f_utf_is_alphabetic_digit((f_string_t) buffer, 5, 0), sequence);
        } // for
      } // for
    } // for
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

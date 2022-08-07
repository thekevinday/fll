#include "utf.h"
#include "private-utf.h"
#include "private-utf_whitespace.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)
  f_status_t private_f_utf_character_is_whitespace(const f_utf_char_t sequence, const bool strict) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Latin-1 Supplement: U+00A0.
      if (sequence == 0xc2a00000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {
        if (strict) {

          // Ogham: U+1680 (isn't whitespace but is technically considered one: ( )).
          if (sequence == 0xe19a8000) {
            return F_true;
          }
        }

        return F_false;
      }

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // General Punctuation: U+2000 to U+200A.
        if (sequence >= 0xe2808000 && sequence <= 0xe2808a00) {
          return F_true;
        }

        // General Punctuation: U+2028, U+2029, U+202F, U+205F.
        if (sequence == 0xe280a800 || sequence == 0xe280a900 || sequence == 0xe2819f00 || sequence == 0xe280af00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+3000.
        if (sequence == 0xe3808000) {
          return F_true;
        }
      }

      return F_false;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)

#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_whitespace_modifier(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Spacing Modifier Letters: U+02B0 to U+02FF.
      if (sequence >= 0xcab00000 && sequence <= 0xcbbf0000) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#if !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)
  f_status_t private_f_utf_character_is_whitespace_other(const f_utf_char_t sequence) {

    // Ogham: U+1680 (isn't whitespace but is technically considered one: ( )).
    if (sequence == 0xe19a8000) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)

#if !defined(_di_f_utf_character_is_whitespace_zero_width_) || !defined(_di_f_utf_is_whitespace_zero_width_)
  f_status_t private_f_utf_character_is_whitespace_zero_width(const f_utf_char_t sequence) {

    // General Punctuation: U+200B (isn't whitespace but is intentended to be interpreted as one in certain circumstances).
    if (sequence == 0xe2808b00) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_zero_width_) || !defined(_di_f_utf_is_whitespace_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif

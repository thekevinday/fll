#include "utf.h"
#include "private-utf.h"
#include "private-utf_alphabetic.h"
#include "private-utf_word.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_word(const f_utf_char_t sequence, const bool strict) {

    if (private_f_utf_character_is_alphabetic_digit(sequence, 0)) {
      return F_true;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {
      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // General Punctuation: U+203F (‿), U+203E (‾), U+2040 (⁀), U+2054 (⁔).
        if (sequence == 0xe280bf00 || sequence == 0xe280be00 || sequence == 0xe2818000 || sequence == 0xe2819400) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // CJK Compatibility Forms: U+FE4D (﹍), U+FE4E (﹎), U+FE4F (﹏).
        if (sequence == 0xefb98d00 || sequence == 0xefb98e00 || sequence == 0xefb98f00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF3F (＿).
        if (sequence == 0xefbcbf00) {
          return F_true;
        }

        if (strict) {

          // Halfwidth and Fullwidth Forms: U+FE33 (︳), U+FE34 (︴).
          if (sequence == 0xefb8b300 || sequence == 0xefb8b400) {
            return F_true;
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#if !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_word_dash(const f_utf_char_t sequence, const bool strict) {

    if (private_f_utf_character_is_word(sequence, strict)) {
      return F_true;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      // General Punctuation: U+2010, U+2011.
      if (sequence == 0xe2809000 || sequence == 0xe2809100) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#if !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_word_dash_plus(const f_utf_char_t sequence, const bool strict) {

    if (private_f_utf_character_is_word_dash(sequence, strict)) {
      return F_true;
    }

    if (strict) {

      // General Punctuation: U+2064.
      if (sequence == 0xe281a400) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

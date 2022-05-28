#include "utf.h"
#include "private-utf.h"
#include "private-utf_alphabetic.h"
#include "private-utf_word.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)
  f_status_t private_f_utf_character_is_word(const f_utf_char_t character, const bool strict) {

    if (private_f_utf_character_is_alphabetic_digit(character)) {
      return F_true;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {
      if (macro_f_utf_char_t_to_char_1(character) == 0xe2) {

        // General Punctuation: U+203F (‿), U+203E (‾), U+2040 (⁀), U+2054 (⁔).
        if (character == 0xe280bf00 || character == 0xe280be00 || character == 0xe2818000 || character == 0xe2819400) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xef) {

        // CJK Compatibility Forms: U+FE4D (﹍), U+FE4E (﹎), U+FE4F (﹏).
        if (character == 0xefb98d00 || character == 0xefb98e00 || character == 0xefb98f00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF3F (＿).
        if (character == 0xefbcbf00) {
          return F_true;
        }

        if (strict) {

          // Halfwidth and Fullwidth Forms: U+FE33 (︳), U+FE34 (︴).
          if (character == 0xefbcbf00 || character == 0xefbcbf00) {
            return F_true;
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)

#if !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)
  f_status_t private_f_utf_character_is_word_dash(const f_utf_char_t character, const bool strict) {

    if (private_f_utf_character_is_word(character, strict)) {
      return F_true;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // General Punctuation: U+2010, U+2011.
      if (character == 0xe2809000 || character == 0xe2809100) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)

#if !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_word_dash_plus(const f_utf_char_t character, const bool strict) {

    if (private_f_utf_character_is_word_dash(character, strict)) {
      return F_true;
    }

    if (strict) {

      // General Punctuation: U+2064.
      if (character == 0xe281a400) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

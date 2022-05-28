#include "utf.h"
#include "private-utf.h"
#include "private-utf_whitespace.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)
  f_status_t private_f_utf_character_is_whitespace(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+00A0.
      if (character == 0xc2a00000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xe2) {

        // General Punctuation: U+2000 to U+200A.
        if (character >= 0xe2808000 && character <= 0xe2808a00) {
          return F_true;
        }

        // General Punctuation: U+2028, U+2029, U+202F, U+205F.
        if (character == 0xe280a800 || character == 0xe280a900 || character == 0xe2819f00 || character == 0xe280af00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe3) {

        // CJK Symbols and Punctuation: U+3000.
        if (character == 0xe3808000) {
          return F_true;
        }
      }

      return F_false;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)

#if !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)
  f_status_t private_f_utf_character_is_whitespace_modifier(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      // Spacing Modifier Letters: U+02B0 to U+02FF.
      if (character >= 0xcab00000 && character <= 0xcbbf0000) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)

#if !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)
  f_status_t private_f_utf_character_is_whitespace_other(const f_utf_char_t character) {

    // Ogham: U+1680 (isn't whitespace but is technically considered one: ( )).
    if (character == 0xe19a8000) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)

#ifdef __cplusplus
} // extern "C"
#endif
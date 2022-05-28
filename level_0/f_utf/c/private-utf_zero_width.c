#include "utf.h"
#include "private-utf.h"
#include "private-utf_zero_width.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)
  f_status_t private_f_utf_character_is_zero_width(const f_utf_char_t character) {

    if (macro_f_utf_char_t_to_char_1(character) == 0xe1) {

      // Mongolian: U+180E.
      if (character == 0xe1a08e00) {
        return F_true;
      }
    }
    else if (macro_f_utf_char_t_to_char_1(character) == 0xe2) {

      // General Punctuation: U+200B, U+200C, U+200D, U+2060.
      if (character == 0xe2808b00 || character == 0xe2808c00 || character == 0xe2808d00 || character == 0xe281a000) {
        return F_true;
      }
    }
    else if (macro_f_utf_char_t_to_char_1(character) == 0xef) {

      // Arabic Presentation Forms-B: U+FEFF.
      if (character == 0xefbbbf00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif
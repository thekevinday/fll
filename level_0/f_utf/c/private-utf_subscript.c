#include "utf.h"
#include "private-utf.h"
#include "private-utf_subscript.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_subscript_) || !defined(_di_f_utf_is_subscript_)
  f_status_t private_f_utf_character_is_subscript(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // Phonetic Extensions: U+1D62 to U+1D6A.
      if (character >= 0xe1b5a200 && character <= 0xe1b5aa00) {
        return F_true;
      }

      // Superscripts and Subscripts: U+2080 to U+208E.
      if (character >= 0xe2828000 && character <= 0xe2828e00) {
        return F_true;
      }

      // Superscripts and Subscripts: U+2090 to U+209C.
      if (character >= 0xe2829000 && character <= 0xe2829c00) {
        return F_true;
      }

      // Latin Extended-C: U+2C7C.
      if (character == 0xe2b1bc00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_subscript_) || !defined(_di_f_utf_is_subscript_)

#ifdef __cplusplus
} // extern "C"
#endif

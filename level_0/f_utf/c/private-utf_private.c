#include "utf.h"
#include "private-utf.h"
#include "private-utf_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)
  f_status_t private_f_utf_character_is_private(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {
      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // High Private Use Surrogates: U+DB80 to U+DBFF.
      if (character >= 0xedae8000 && character <= 0xedafbf00) {
        return F_true;
      }

      // Private Use: U+E000 to U+F8FF.
      if (character >= 0xee808000 && character <= 0xefa3bf00) {
        return F_true;
      }

      return F_false;
    }

    // Supplementary Private Use Area - A: U+F0000 to U+FFFFF.
    if (character >= 0xf3b08080 && character <= 0xf3bfbfbf) {
      return F_true;
    }

    // Supplementary Private Use Area - B: U+100000 to U+10FFFF.
    if (character >= 0xf4808080 && character <= 0xf48fbfbf) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)

#ifdef __cplusplus
} // extern "C"
#endif

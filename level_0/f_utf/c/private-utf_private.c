#include "utf.h"
#include "private-utf.h"
#include "private-utf_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)
  f_status_t private_f_utf_character_is_private(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {
      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      // Private Use: U+E000 to U+F8FF.
      if (sequence >= 0xee808000 && sequence <= 0xefa3bf00) {
        return F_true;
      }

      return F_false;
    }

    // Supplementary Private Use Area - A: U+F0000 to U+FFFFF.
    if (sequence >= 0xf3b08080 && sequence <= 0xf3bfbfbf) {
      return F_true;
    }

    // Supplementary Private Use Area - B: U+100000 to U+10FFFF.
    if (sequence >= 0xf4808080 && sequence <= 0xf48fbfbf) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)

#ifdef __cplusplus
} // extern "C"
#endif

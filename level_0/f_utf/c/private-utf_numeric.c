#include "utf.h"
#include "private-utf.h"
#include "private-utf_digit.h"
#include "private-utf_numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)
  f_status_t private_f_utf_character_is_numeric(const f_utf_char_t sequence) {

    if (private_f_utf_character_is_digit(sequence)) {
      return F_true;
    }

    // @todo add letter UTF-8 numbers.
    // @todo add other UTF-8 numbers.
    // @todo provide functions to identify each number.

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      // Number Forms: U+2150 to U+218B.
      if (sequence >= 0xe2859000 && sequence <= 0xe2868b00) {
        return F_true;
      }
    }
    else if (macro_f_utf_char_t_width_is(sequence) == 4) {

      // Coptic Epact Numbers: U+102E1 to U+102FB.
      if (sequence >= 0xf0908ba1 && sequence <= 0xf0908bbb) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)

#ifdef __cplusplus
} // extern "C"
#endif

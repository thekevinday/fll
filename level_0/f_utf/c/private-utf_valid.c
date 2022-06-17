#include "utf.h"
#include "private-utf.h"
#include "private-utf_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)
  f_status_t private_f_utf_character_is_valid(const f_utf_char_t character) {

    // All characters with data after the width bytes is invalid.
    if (macro_f_utf_char_t_width(character) == 2 && (macro_f_utf_char_t_to_char_3(character) || macro_f_utf_char_t_to_char_4(character))) {
      return F_false;
    }

    if (macro_f_utf_char_t_width(character) == 3 && macro_f_utf_char_t_to_char_4(character)) {
      return F_false;
    }

    // Invalid: 11111xxx xxxxxxxx xxxxxxxx xxxxxxxx.
    if ((macro_f_utf_char_t_to_char_1(character) & 0b11111000) == 0b11111000) {
      return F_false;
    }

    // Valid: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx.
    if ((macro_f_utf_char_t_to_char_1(character) & 0b11111000) == 0b11110000) {
      if ((macro_f_utf_char_t_to_char_2(character) & 0b11000000) == 0b10000000 && (macro_f_utf_char_t_to_char_3(character) & 0b11000000) == 0b10000000 && (macro_f_utf_char_t_to_char_4(character) & 0b11000000) == 0b10000000) {
        return F_true;
      }

      return F_false;
    }

    // Valid: 1110xxxx 10xxxxxx 10xxxxxx ????????.
    else if ((macro_f_utf_char_t_to_char_1(character) & 0b11110000) == 0b11100000) {
      if ((macro_f_utf_char_t_to_char_2(character) & 0b11000000) == 0b10000000 && (macro_f_utf_char_t_to_char_3(character) & 0b11000000) == 0b10000000) {
        return F_true;
      }

      return F_false;
    }

    // Valid: 110xxxxx 10xxxxxx ???????? ????????.
    else if ((macro_f_utf_char_t_to_char_1(character) & 0b11100000) == 0b11000000) {
      if ((macro_f_utf_char_t_to_char_2(character) & 0b11000000) == 0b10000000) {
        return F_true;
      }

      return F_false;
    }

    // Invalid (UTF Fragment): 10xxxxxx ???????? ???????? ????????.
    else if ((macro_f_utf_char_t_to_char_1(character) & 0b11000000) == 0b10000000) {
      return F_status_set_error(F_utf_fragment);
    }

    // Valid: 0xxxxxxx ???????? ???????? ????????.
    else if (macro_f_utf_char_t_to_char_1(character) & 0b10000000) {
      return F_false;
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)

#ifdef __cplusplus
} // extern "C"
#endif

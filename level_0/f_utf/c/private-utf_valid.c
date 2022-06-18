#include "utf.h"
#include "private-utf.h"
#include "private-utf_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)
  f_status_t private_f_utf_character_is_valid(const f_utf_char_t sequence) {

    // Invalid: 11111xxx xxxxxxxx xxxxxxxx xxxxxxxx.
    if ((macro_f_utf_char_t_to_char_1(sequence) & 0b11111000) == 0b11111000) {
      return F_false;
    }

    // Valid: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx.
    if ((macro_f_utf_char_t_to_char_1(sequence) & 0b11111000) == 0b11110000) {

      // For first byte 0xf0, only second byte ranges 0x90 to 0xbf are valid.
      if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {
        if (macro_f_utf_char_t_to_char_2(sequence) < 0x90 || macro_f_utf_char_t_to_char_2(sequence) > 0xbf) {
          return F_false;
        }
      }

      // For first byte 0xf4, only second byte ranges 0x80 to 0x8f are valid.
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xf4) {
        if (macro_f_utf_char_t_to_char_2(sequence) < 0x80 || macro_f_utf_char_t_to_char_2(sequence) > 0x8f) {
          return F_false;
        }
      }

      // For first byte greater than 0xf4 are all invalid.
      else if (macro_f_utf_char_t_to_char_1(sequence) > 0xf4) {
        return F_false;
      }

      if ((macro_f_utf_char_t_to_char_2(sequence) & 0b11000000) == 0b10000000 && (macro_f_utf_char_t_to_char_3(sequence) & 0b11000000) == 0b10000000 && (macro_f_utf_char_t_to_char_4(sequence) & 0b11000000) == 0b10000000) {
        return F_true;
      }

      return F_false;
    }

    // Valid: 1110xxxx 10xxxxxx 10xxxxxx ????????.
    if ((macro_f_utf_char_t_to_char_1(sequence) & 0b11110000) == 0b11100000) {

      // For first byte 0xe0, only second byte ranges 0xa0 to 0xbf are valid.
      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {
        if (macro_f_utf_char_t_to_char_2(sequence) < 0xa0 || macro_f_utf_char_t_to_char_2(sequence) > 0xbf) {
          return F_false;
        }
      }

      // For first byte 0xed, only second byte ranges 0x80 to 0x9f are valid.
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xed) {
        if (macro_f_utf_char_t_to_char_2(sequence) < 0x80 || macro_f_utf_char_t_to_char_2(sequence) > 0x9f) {
          return F_false;
        }
      }

      if ((macro_f_utf_char_t_to_char_2(sequence) & 0b11000000) == 0b10000000 && (macro_f_utf_char_t_to_char_3(sequence) & 0b11000000) == 0b10000000) {

        // All characters with data after the width bytes is invalid.
        if (macro_f_utf_char_t_to_char_4(sequence)) {
          return F_false;
        }

        return F_true;
      }

      return F_false;
    }

    // Valid: 110xxxxx 10xxxxxx ???????? ????????.
    if ((macro_f_utf_char_t_to_char_1(sequence) & 0b11100000) == 0b11000000) {

      // Only first byte ranges 0xc3 or greater are valid.
      if (macro_f_utf_char_t_to_char_2(sequence) < 0xc3) {
        return F_false;
      }

      if ((macro_f_utf_char_t_to_char_2(sequence) & 0b11000000) == 0b10000000) {

        // All characters with data after the width bytes is invalid.
        if (macro_f_utf_char_t_to_char_3(sequence) || macro_f_utf_char_t_to_char_4(sequence)) {
          return F_false;
        }

        return F_true;
      }

      return F_false;
    }

    // Invalid (UTF Fragment): 10xxxxxx ???????? ???????? ????????.
    if ((macro_f_utf_char_t_to_char_1(sequence) & 0b11000000) == 0b10000000) {
      return F_status_set_error(F_utf_fragment);
    }

    // All characters with data after the width bytes is invalid.
    if (macro_f_utf_char_t_to_char_2(sequence) || macro_f_utf_char_t_to_char_3(sequence) || macro_f_utf_char_t_to_char_4(sequence)) {
      return F_false;
    }

    // Valid: 0xxxxxxx ???????? ???????? ????????.
    if (macro_f_utf_char_t_to_char_1(sequence) < 0x80) {
      return F_true;
    }

    // All other values > 0x7f are invalid.
    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)

#ifdef __cplusplus
} // extern "C"
#endif

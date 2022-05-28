#include "utf.h"
#include "private-utf.h"
#include "private-utf_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)
  f_status_t private_f_utf_character_is_valid(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) < 2) {
      if (macro_f_utf_char_t_to_char_1(character) >= 0x00 && macro_f_utf_char_t_to_char_1(character) <= 0x7f) {
        return F_true;
      }

      return false;
    }

    if (macro_f_utf_char_t_width_is(character) == 2) {
      if (macro_f_utf_char_t_to_char_1(character) >= 0xc2 && macro_f_utf_char_t_to_char_1(character) <= 0xdf) {
        if (macro_f_utf_char_t_to_char_2(character) >= 0x80 && macro_f_utf_char_t_to_char_2(character) <= 0xbf) {
          return F_true;
        }
      }

      return false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {
      if (macro_f_utf_char_t_to_char_1(character) == 0xe0) {
        if (macro_f_utf_char_t_to_char_2(character) >= 0xa0 && macro_f_utf_char_t_to_char_2(character) <= 0xbf) {
          if (macro_f_utf_char_t_to_char_3(character) >= 0x80 && macro_f_utf_char_t_to_char_3(character) <= 0xbf) {
            return F_true;
          }
        }
      }
      else if ((macro_f_utf_char_t_to_char_1(character) >= 0xe1 && macro_f_utf_char_t_to_char_1(character) <= 0xec) || (macro_f_utf_char_t_to_char_1(character) >= 0xee && macro_f_utf_char_t_to_char_1(character) <= 0xef)) {
        if (macro_f_utf_char_t_to_char_2(character) >= 0x80 && macro_f_utf_char_t_to_char_2(character) <= 0xbf) {
          if (macro_f_utf_char_t_to_char_3(character) >= 0x80 && macro_f_utf_char_t_to_char_3(character) <= 0xbf) {
            return F_true;
          }
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xed) {
        if (macro_f_utf_char_t_to_char_2(character) >= 0x80 && macro_f_utf_char_t_to_char_2(character) <= 0x9f) {
          if (macro_f_utf_char_t_to_char_3(character) >= 0x80 && macro_f_utf_char_t_to_char_3(character) <= 0xbf) {
            return F_true;
          }
        }
      }

      return false;
    }

    if (macro_f_utf_char_t_to_char_1(character) == 0xf0) {
      if (macro_f_utf_char_t_to_char_2(character) >= 0x90 && macro_f_utf_char_t_to_char_2(character) <= 0xbf) {
        if (macro_f_utf_char_t_to_char_3(character) >= 0x80 && macro_f_utf_char_t_to_char_3(character) <= 0xbf) {
          if (macro_f_utf_char_t_to_char_4(character) >= 0x80 && macro_f_utf_char_t_to_char_4(character) <= 0xbf) {
            return F_true;
          }
        }
      }
    }
    else if (macro_f_utf_char_t_to_char_1(character) >= 0xf1 && macro_f_utf_char_t_to_char_1(character) <= 0xf3) {
      if (macro_f_utf_char_t_to_char_2(character) >= 0x80 && macro_f_utf_char_t_to_char_2(character) <= 0xbf) {
        if (macro_f_utf_char_t_to_char_3(character) >= 0x80 && macro_f_utf_char_t_to_char_3(character) <= 0xbf) {
          if (macro_f_utf_char_t_to_char_4(character) >= 0x80 && macro_f_utf_char_t_to_char_4(character) <= 0xbf) {
            return F_true;
          }
        }
      }
    }
    else if (macro_f_utf_char_t_to_char_1(character) == 0xf4) {
      if (macro_f_utf_char_t_to_char_2(character) >= 0x80 && macro_f_utf_char_t_to_char_2(character) <= 0x8f) {
        if (macro_f_utf_char_t_to_char_3(character) >= 0x80 && macro_f_utf_char_t_to_char_3(character) <= 0xbf) {
          if (macro_f_utf_char_t_to_char_4(character) >= 0x80 && macro_f_utf_char_t_to_char_4(character) <= 0xbf) {
            return F_true;
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)

#ifdef __cplusplus
} // extern "C"
#endif

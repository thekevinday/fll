#include "../utf.h"
#include "../private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_char_to_character_
  f_status_t f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_char_t *character_utf) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
      if (!character_utf) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character) > width_max) {
      return F_status_set_error(F_failure);
    }

    if (macro_f_utf_byte_width_is(*character) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    return private_f_utf_char_to_character(character, width_max, character_utf);
  }
#endif // _di_f_utf_char_to_character_

#ifndef _di_f_utf_char_to_char_
  f_status_t f_utf_char_to_char(const f_utf_char_t unicode, f_string_t *character, f_array_length_t *width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (!character) return F_status_set_error(F_parameter);
      if (!width_max) return F_status_set_error(F_parameter);
      if (!*width_max) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_char_t_width_is(unicode)) {
      if (macro_f_utf_char_t_width_is(unicode) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      memcpy(*character, &unicode, sizeof(f_char_t) * macro_f_utf_char_t_width_is(unicode));
      /*#if __BYTE_ORDER == __LITTLE_ENDIAN
        f_utf_char_t utf = 0;

        switch (macro_f_utf_char_t_width_is(unicode)) {
          case 1:
            utf = macro_f_utf_char_t_from_char_1(macro_f_utf_char_t_to_char_1(unicode));
            break;

          case 2:
            utf = macro_f_utf_char_t_from_char_1(macro_f_utf_char_t_to_char_2(unicode)) | macro_f_utf_char_t_from_char_2(macro_f_utf_char_t_to_char_1(unicode));
            break;

          case 3:
            utf = macro_f_utf_char_t_from_char_1(macro_f_utf_char_t_to_char_3(unicode)) | macro_f_utf_char_t_from_char_2(macro_f_utf_char_t_to_char_2(unicode)) | macro_f_utf_char_t_from_char_3(macro_f_utf_char_t_to_char_1(unicode));
            break;

          case 4:
            utf = macro_f_utf_char_t_from_char_1(macro_f_utf_char_t_to_char_4(unicode)) | macro_f_utf_char_t_from_char_2(macro_f_utf_char_t_to_char_3(unicode)) | macro_f_utf_char_t_from_char_3(macro_f_utf_char_t_to_char_2(unicode)) | macro_f_utf_char_t_from_char_4(macro_f_utf_char_t_to_char_1(unicode));
            break;

          default:
            return F_status_set_error(F_failure);
        }

        memcpy(*character, &utf, sizeof(f_char_t) * macro_f_utf_char_t_width_is(unicode));
      #else
        memcpy(*character, &unicode, sizeof(f_char_t) * macro_f_utf_char_t_width_is(unicode));
      #endif // __BYTE_ORDER == __LITTLE_ENDIAN*/

      return F_none;
    }

    memcpy(*character, &unicode, sizeof(f_char_t));

    /*#if __BYTE_ORDER == __LITTLE_ENDIAN
      f_utf_char_t utf = macro_f_utf_char_t_to_char_1(unicode) << 24;

      memcpy(*character, &utf, sizeof(f_char_t));
    #else
      memcpy(*character, &unicode, sizeof(f_char_t));
    #endif // __BYTE_ORDER == __LITTLE_ENDIAN*/

    return F_none;
  }
#endif // _di_f_utf_char_to_char_

#ifndef _di_f_utf_character_unicode_to_
  f_status_t f_utf_character_unicode_to(const f_utf_char_t character, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_character_unicode_to(character, unicode);
  }
#endif // _di_f_utf_character_unicode_to_

#ifndef _di_f_utf_character_unicode_from_
  f_status_t f_utf_character_unicode_from(const uint32_t unicode, f_utf_char_t *character) {
    #ifndef _di_level_0_parameter_checking_
      if (!character) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (unicode > 0x10ffff) {
      return F_status_set_error(F_utf_not);
    }

    // U+0000 -> U+007F.
    if (unicode < 0x80) {
      *character = unicode;
    }

    // U+0080 -> U+07FF.
    else if (unicode < 0x800) {
      *character = (unicode & 0x7c0) << 2;
      *character |= unicode & 0x3f;
      *character |= 0xc080;
    }

    // U+0800 -> U+FFFF.
    else if (unicode < 0x10000) {
      *character = (unicode & 0xf000) << 4;
      *character |= (unicode & 0xfc0) << 2;
      *character |= unicode & 0x3f;
      *character |= 0xe08080;
    }

    // U+100000 -> U+10FFFF.
    else {
      *character = (unicode & 0x1c0000) << 6;
      *character |= (unicode & 0x3f000) << 4;
      *character |= (unicode & 0xfc0) << 2;
      *character |= unicode & 0x3f;
      *character |= 0xe0808080;
    }

    return F_none;
  }
#endif // _di_f_utf_character_unicode_from_

#ifndef _di_f_utf_character_unicode_string_to_
  f_status_t f_utf_character_unicode_string_to(const f_utf_string_t string, const f_array_length_t length, f_utf_char_t *codepoint) {
    #ifndef _di_level_0_parameter_checking_
      if (!codepoint) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_array_length_t i = 0;

    while (i < length && !string[i]) {
      ++i;
    } // while

    if (i < length) {
      if (macro_f_utf_char_t_width_is(string[i])) {
        i = length;
      }
      else {
        if (macro_f_utf_char_t_to_char_1(string[i]) == f_string_ascii_u_s.string[0] || macro_f_utf_char_t_to_char_1(string[i]) == f_string_ascii_U_s.string[0]) {
          do {
            ++i;
          } while (i < length && !string[i]);

          if (i < length && !macro_f_utf_char_t_width_is(string[i]) && macro_f_utf_char_t_to_char_1(string[i]) == f_string_ascii_plus_s.string[0]) {
            ++i;
          }
          else {
            i = length;
          }
        }
        else {
          i = length;
        }
      }
    }

    if (i == length) {
      return F_status_set_error(F_valid_not);
    }

    f_utf_char_t value = 0;
    f_char_t character = 0;

    for (; i < length; ++i) {

      if (!string[i]) continue;

      // Only ASCII character numbers are allowed to represent
      if (macro_f_utf_char_t_width_is(string[i])) {
        return F_status_set_error(F_valid_not);
      }

      value *= 16;
      character = macro_f_utf_char_t_to_char_1(string[i]);

      if (character > 0x2f && character < 0x3a) {
        value += character - 0x30;
      }
      else if (character > 0x40 && character < 0x47) {
        value += (character - 0x41) + 10;
      }
      else if (character > 0x60 && character < 0x67) {
        value += (character - 0x61) + 10;
      }
      else {
        return F_status_set_error(F_valid_not);
      }
    } // for

    *codepoint = value;

    return F_none;
  }
#endif // _di_f_utf_character_unicode_string_to_

#ifndef _di_f_utf_unicode_from_
  f_status_t f_utf_unicode_from(const f_utf_char_t codepoint, const f_array_length_t width_max, f_string_t *character) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (codepoint > 0x10ffff) {
      return F_status_set_error(F_utf_not);
    }

    if (codepoint < 0x80) {

      // U+0000 -> U+007F
      (*character)[0] = (f_char_t) codepoint;

      if (width_max > 1) {
        (*character)[1] = 0;

        if (width_max > 2) {
          (*character)[2] = 0;

          if (width_max > 3) {
            (*character)[3] = 0;
          }
        }
      }
    }
    else if (codepoint < 0x800) {
      if (width_max < 2) {
        return F_status_set_error(F_utf_not);
      }

      // U+0080 -> U+07FF
      (*character)[0] = F_utf_byte_2_d | ((f_char_t) ((codepoint & 0x7c0) >> 6));
      (*character)[1] = F_utf_byte_1_d | ((f_char_t) (codepoint & 0x3f));

      if (width_max > 2) {
        (*character)[2] = 0;

        if (width_max > 3) {
          (*character)[3] = 0;
        }
      }
    }
    else if (codepoint < 0x10000) {
      if (width_max < 3) {
        return F_status_set_error(F_utf_not);
      }

      // U+0800 -> U+FFFF
      (*character)[0] = F_utf_byte_3_d | ((f_char_t) ((codepoint & 0xf000) >> 12));
      (*character)[1] = F_utf_byte_1_d | ((f_char_t) ((codepoint & 0xfc0) >> 6));
      (*character)[2] = F_utf_byte_1_d | ((f_char_t) (codepoint & 0x3f));

      if (width_max > 3) {
        character[3] = 0;
      }
    }
    else {
      if (width_max < 4) {
        return F_status_set_error(F_utf_not);
      }

      // U+10000 -> U+10FFFF
      (*character)[0] = F_utf_byte_4_d | ((f_char_t) ((codepoint & 0x1c0000) >> 18));
      (*character)[1] = F_utf_byte_1_d | ((f_char_t) ((codepoint & 0x3f000) >> 12));
      (*character)[2] = F_utf_byte_1_d | ((f_char_t) ((codepoint & 0xfc0) >> 6));
      (*character)[3] = F_utf_byte_1_d | ((f_char_t) (codepoint & 0x3f));
    }

    return F_none;
  }
#endif // _di_f_utf_unicode_from_

#ifndef _di_f_utf_unicode_to_
  f_status_t f_utf_unicode_to(const f_string_t character, const f_array_length_t width_max, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_utf_char_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_unicode_to(character_utf, unicode);
  }
#endif // _di_f_utf_unicode_to_

#ifndef _di_f_utf_unicode_string_to_f_
  f_status_t f_utf_unicode_string_to(const f_string_t string, const f_array_length_t length, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_array_length_t i = 0;

    while (i < length && !string[i]) {
      ++i;
    } // while

    if (i < length) {
      if (string[i] == f_string_ascii_u_s.string[0] || string[i] == f_string_ascii_U_s.string[0]) {
        do {
          ++i;
        } while (i < length && !string[i]);

        if (i < length && string[i] == f_string_ascii_plus_s.string[0]) {
          ++i;
        }
        else {
          i = length;
        }
      }
      else {
        i = length;
      }
    }

    if (i == length) {
      return F_status_set_error(F_valid_not);
    }

    uint32_t value = 0;

    for (; i < length; ++i) {

      if (!string[i]) continue;

      value *= 16;

      if (string[i] > 0x2f && string[i] < 0x3a) {
        value += string[i] - 0x30;
      }
      else if (string[i] > 0x40 && string[i] < 0x47) {
        value += (string[i] - 0x41) + 10;
      }
      else if (string[i] > 0x60 && string[i] < 0x67) {
        value += (string[i] - 0x61) + 10;
      }
      else {
        return F_status_set_error(F_valid_not);
      }
    } // for

    if (value > 0x10ffff) {
      return F_status_set_error(F_valid_not);
    }

    *unicode = value;

    return F_none;
  }
#endif // _di_f_utf_unicode_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

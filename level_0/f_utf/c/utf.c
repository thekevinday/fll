#include <level_0/utf.h>
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_character_is_
  f_return_status f_utf_character_is(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return f_true;
  }
#endif // _di_f_utf_character_is_

#ifndef _di_f_utf_character_is_control_
  f_return_status f_utf_character_is_control(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      if (iscntrl(f_macro_utf_character_to_char_1(character))) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return private_f_utf_character_is_control(character, width);
  }
#endif // _di_f_utf_character_is_control_

#ifndef _di_f_utf_character_is_control_picture_
  f_return_status f_utf_character_is_control_picture(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      // There are no control picture characters in ASCII.
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (width != 3) {
      return f_false;
    }

    return private_f_utf_character_is_control_picture(character);
  }
#endif // _di_f_utf_character_is_control_picture_

#ifndef _di_f_utf_character_is_fragment_
  f_return_status f_utf_character_is_fragment(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 1) return f_true;

    return f_false;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_return_status f_utf_character_is_graph(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      if (isgraph(f_macro_utf_character_to_char_1(character))) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (private_f_utf_character_is_control(character, width) == f_true) {
      return f_false;
    }

    if (private_f_utf_character_is_whitespace(character) == f_true) {
      return f_false;
    }

    // This test is in isolation so zero-width characters must be treated as a non-graph.
    if (private_f_utf_character_is_zero_width(character) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_f_utf_character_is_graph_

#ifndef _di_f_utf_character_is_valid_
  f_return_status f_utf_character_is_valid(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0 || width == 1) {
      return f_false;
    }

    return private_f_utf_character_is_valid(character, width);
  }
#endif // _di_f_utf_character_is_valid_

#ifndef _di_f_utf_character_is_whitespace_
  f_return_status f_utf_character_is_whitespace(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      if (isspace(f_macro_utf_character_to_char_1(character))) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return private_f_utf_character_is_whitespace(character);
  }
#endif // _di_f_utf_character_is_whitespace_

#ifndef _di_f_utf_character_is_zero_width_
  f_return_status f_utf_character_is_zero_width(const f_utf_character character) {
    if (f_macro_utf_character_width_is(character) == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return private_f_utf_character_is_zero_width(character);
  }
#endif // _di_f_utf_character_is_zero_width_

#ifndef _di_f_utf_character_to_char_
  f_return_status f_utf_character_to_char(const f_utf_character utf_character, f_string *character, uint8_t *width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (utf_character == 0) return f_status_set_error(f_invalid_parameter);
      if (width_max == 0 && *character != 0) return f_status_set_error(f_invalid_parameter);
      if (width_max != 0 && *character == 0) return f_status_set_error(f_invalid_parameter);
      if (width_max != 0 && *width_max > 4) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    unsigned short width = f_macro_utf_character_width_is(utf_character);

    if (width_max == 0) {
      f_macro_string_new(status, *character, width);

      if (f_status_is_error(status)) return status;

      width = 1;
      *width_max = 1;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }
    else if (width > *width_max) {
      return f_status_set_error(f_failure);
    }

    *width_max = width;

    if (f_utf_is_big_endian()) {
      memcpy(*character, &utf_character, width);
    }
    else {
      uint32_t utf = 0;

      if (width == 1) {
        utf = f_macro_utf_character_to_char_1(utf_character) << 24;
      }
      else if (width == 2) {
        utf = (f_macro_utf_character_to_char_2(utf_character) << 24) | (f_macro_utf_character_to_char_1(utf_character) << 16);
      }
      else if (width == 3) {
        utf = (f_macro_utf_character_to_char_3(utf_character) << 24) | (f_macro_utf_character_to_char_2(utf_character) << 16) | (f_macro_utf_character_to_char_1(utf_character) << 8);
      }
      else if (width == 4) {
        utf = (f_macro_utf_character_to_char_4(utf_character) << 24) | (f_macro_utf_character_to_char_3(utf_character) << 16) | (f_macro_utf_character_to_char_2(utf_character) << 8) | f_macro_utf_character_to_char_1(utf_character);
      }

      memcpy(*character, &utf, width);
    }

    return f_none;
  }
#endif // _di_f_utf_character_to_char_

#ifndef _di_f_utf_is_big_endian_
  f_return_status f_utf_is_big_endian() {
    uint16_t test_int = (0x01 << 8) | 0x02;
    int8_t test_char[2] = {0x01, 0x02};

    if (!memcmp(&test_int, test_char, 2)) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_utf_is_big_endian_

#ifndef _di_f_utf_is_
  f_return_status f_utf_is(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    return f_true;
  }
#endif // _di_f_utf_is_

#ifndef _di_f_utf_is_control_
  f_return_status f_utf_is_control(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (iscntrl(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;

    {
      f_status status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (status != f_none) return status;
    }

    return private_f_utf_character_is_control(character_utf, width);
  }
#endif // _di_f_utf_is_control_

#ifndef _di_f_utf_is_control_picture_
  f_return_status f_utf_is_control_picture(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    // There are not ASCII control pictures.
    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;

    {
      f_status status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (status != f_none) return status;
    }

    return private_f_utf_character_is_control_picture(character_utf);
  }
#endif // _di_f_utf_is_control_picture_

#ifndef _di_f_utf_is_graph_
  f_return_status f_utf_is_graph(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (isgraph(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;

    {
      f_status status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (status != f_none) return status;
    }

    if (private_f_utf_character_is_control(character_utf, width) == f_true) {
      return f_false;
    }

    if (private_f_utf_character_is_whitespace(character_utf) == f_true) {
      return f_false;
    }

    // This test is in isolation so zero-width characters must be treated as a non-graph.
    if (private_f_utf_character_is_zero_width(character_utf) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_f_utf_is_graph_

#ifndef _di_f_utf_is_valid_
  f_return_status f_utf_is_valid(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0 || width == 1) {
      return f_false;
    }

    f_utf_character character_utf = 0;

    {
      f_status status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (status != f_none) return status;
    }

    return private_f_utf_character_is_valid(character_utf, width);
  }
#endif // _di_f_utf_is_valid_

#ifndef _di_f_utf_is_whitespace_
  f_return_status f_utf_is_whitespace(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (isspace(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;

    {
      f_status status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (status != f_none) return status;
    }

    return f_utf_character_is_whitespace(character_utf);
  }
#endif // _di_f_utf_is_whitespace_

#ifndef _di_f_utf_is_zero_width_
  f_return_status f_utf_is_zero_width(const f_string character, const uint8_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (isspace(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;

    {
      f_status status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (status != f_none) return status;
    }

    return private_f_utf_character_is_zero_width(character_utf);
  }
#endif // _di_f_utf_is_zero_width_

#ifndef _di_f_utf_char_to_character_
  f_return_status f_utf_char_to_character(const f_string character, const uint8_t width_max, f_utf_character *character_utf) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return f_status_set_error(f_invalid_parameter);
      if (character_utf == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      *character_utf = f_macro_utf_character_from_char_1(character[0]);
      return f_none;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (width > width_max) {
      return f_status_set_error(f_failure);
    }

    *character_utf = f_macro_utf_character_from_char_1(character[0]);

    if (width < 2) {
      return f_none;
    }

    *character_utf |= f_macro_utf_character_from_char_2(character[1]);

    if (width == 2) {
      return f_none;
    }

    *character_utf |= f_macro_utf_character_from_char_3(character[2]);

    if (width == 3) {
      return f_none;
    }

    *character_utf |= f_macro_utf_character_from_char_4(character[3]);

    return f_none;
  }
#endif // _di_f_utf_char_to_character_

#ifdef __cplusplus
} // extern "C"
#endif

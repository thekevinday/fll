#include "../utf.h"
#include "../private-utf.h"
#include "private-is_unassigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_is_
  f_status_t f_utf_is(const f_string_t character) {

    return macro_f_utf_byte_width_is(*character);
  }
#endif // _di_f_utf_is_

#ifndef _di_f_utf_is_alpha_
  f_status_t f_utf_is_alpha(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_alpha(character_utf);
    }

    if (isalpha(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_alpha_

#ifndef _di_f_utf_is_alpha_digit_
  f_status_t f_utf_is_alpha_digit(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_alpha_digit(character_utf);
    }

    if (isalnum(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_alpha_digit_

#ifndef _di_f_utf_is_alpha_numeric_
  f_status_t f_utf_is_alpha_numeric(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_alpha_numeric(character_utf);
    }

    if (isalnum(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_alpha_numeric_

#ifndef _di_f_utf_is_ascii_
  f_status_t f_utf_is_ascii(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_is_ascii_

#ifndef _di_f_utf_is_combining_
  f_status_t f_utf_is_combining(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_combining(character_utf);
    }

    // There are no ASCII combining characters.
    return F_false;
  }
#endif // _di_f_utf_is_combining_

#ifndef _di_f_utf_is_control_
  f_status_t f_utf_is_control(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control(character_utf);
    }

    return iscntrl(*character);
  }
#endif // _di_f_utf_is_control_

#ifndef _di_f_utf_is_control_code
  f_status_t f_utf_is_control_code(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control_code(character_utf);
    }

    if (iscntrl(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_control_code_

#ifndef _di_f_utf_is_control_format_
  f_status_t f_utf_is_control_format(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control_format(character_utf);
    }

    // There are no ASCII control formats.
    return F_false;
  }
#endif // _di_f_utf_is_control_format_

#ifndef _di_f_utf_is_control_picture_
  f_status_t f_utf_is_control_picture(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (macro_f_utf_byte_width_is(*character) != 3) {
        return F_false;
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control_picture(character_utf);
    }

    // There are no ASCII control pictures.
    return F_false;
  }
#endif // _di_f_utf_is_control_picture_

#ifndef _di_f_utf_is_digit_
  f_status_t f_utf_is_digit(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_digit(character_utf);
    }

    if (isdigit(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_digit_

#ifndef _di_f_utf_is_emoji_
  f_status_t f_utf_is_emoji(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_emoji(character_utf);
    }

    if (isdigit(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_emoji_

#ifndef _di_f_utf_is_fragment_
  f_status_t f_utf_is_fragment(const f_string_t character) {

    if (macro_f_utf_byte_width_is(*character) == 1) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_fragment_

#ifndef _di_f_utf_is_graph_
  f_status_t f_utf_is_graph(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      if (private_f_utf_character_is_control(character_utf)) {
        return F_false;
      }

      if (private_f_utf_character_is_whitespace(character_utf)) {
        return F_false;
      }

      // Zero-width characters are be treated as a non-graph.
      if (private_f_utf_character_is_zero_width(character_utf)) {
        return F_false;
      }

      return F_true;
    }

    if (isgraph(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_graph_

#ifndef _di_f_utf_is_numeric_
  f_status_t f_utf_is_numeric(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_numeric(character_utf);
    }

    if (isdigit(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_numeric_

#ifndef _di_f_utf_is_phonetic_
  f_status_t f_utf_is_phonetic(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_phonetic(character_utf);
    }

    // There are no ASCII phonetic characters.
    return F_false;
  }
#endif // _di_f_utf_is_phonetic_

#ifndef _di_f_utf_is_private_
  f_status_t f_utf_is_private(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_private(character_utf);
    }

    // There are no ASCII private characters.
    return F_false;
  }
#endif // _di_f_utf_is_private_

#ifndef _di_f_utf_is_punctuation_
  f_status_t f_utf_is_punctuation(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_punctuation(character_utf);
    }

    // ASCII: '!' to '#'.
    if (character[0] > 0x20 && character[0] < 0x24) {
      return F_true;
    }

    // ASCII: '%' to '*'.
    if (character[0] > 0x24 && character[0] < 0x2b) {
      return F_true;
    }

    // ASCII: ',' to '/'.
    if (character[0] > 0x2b && character[0] < 0x30) {
      return F_true;
    }

    // ASCII: ':', ';', '?', or '@'.
    if (character[0] == 0x3a || character[0] == 0x3b || character[0] == 0x3f || character[0] == 0x40) {
      return F_true;
    }

    // ASCII: '[' to ']'.
    if (character[0] > 0x5a && character[0] < 0x5d) {
      return F_true;
    }

    // ASCII: '_', '{', or '}'.
    if (character[0] == 0x5f || character[0] == 0x7b || character[0] == 0x7d) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_punctuation_

#ifndef _di_f_utf_is_symbol_
  f_status_t f_utf_is_symbol(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_symbol(character_utf);
    }

    // ASCII: '$' or '+'.
    if (character[0] == 0x24 || character[0] == 0x2b) {
      return F_true;
    }

    // ASCII: '<' to '>'.
    if (character[0] > 0x3c && character[0] < 0x3e) {
      return F_true;
    }

    // ASCII: '^', '`', '|', or '~'.
    if (character[0] == 0x5e || character[0] == 0x60 || character[0] == 0x7c || character[0] == 0x7e) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_symbol_

#ifndef _di_f_utf_is_surrogate_
  f_status_t f_utf_is_surrogate(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_surrogate(character_utf);
    }

    // ASCII are never surrogate.
    return F_false;
  }
#endif // _di_f_utf_is_surrogate_

#ifndef _di_f_utf_is_unassigned_
  f_status_t f_utf_is_unassigned(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_unassigned(character_utf);
    }

    // ASCII are never unassigned.
    return F_false;
  }
#endif // _di_f_utf_is_unassigned_

#ifndef _di_f_utf_is_valid_
  f_status_t f_utf_is_valid(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_valid(character_utf);
    }

    // ASCII are valid.
    return F_true;
  }
#endif // _di_f_utf_is_valid_

#ifndef _di_f_utf_is_whitespace_
  f_status_t f_utf_is_whitespace(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace(character_utf);
    }

    if (isspace(*character)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_whitespace_

#ifndef _di_f_utf_is_whitespace_modifier_
  f_status_t f_utf_is_whitespace_modifier(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace_modifier(character_utf);
    }

    // There are no ASCII whitespace modifiers.
    return F_false;
  }
#endif // _di_f_utf_is_whitespace_modifier_

#ifndef _di_f_utf_is_whitespace_other_
  f_status_t f_utf_is_whitespace_other(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace_other(character_utf);
    }

    // There are no ASCII whitespace other.
    return F_false;
  }
#endif // _di_f_utf_is_whitespace_other_

#ifndef _di_f_utf_is_wide_
  f_status_t f_utf_is_wide(const f_string_t character, const f_array_length_t width_max) {

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_wide(character_utf);
    }

    // There are no wide ASCII characters.
    return F_false;
  }
#endif // _di_f_utf_is_wide_

#ifndef _di_f_utf_is_word_
  f_status_t f_utf_is_word(const f_string_t character, const f_array_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word(character_utf, strict);
    }

    if (isalnum(*character) || *character == f_string_ascii_underscore_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_word_

#ifndef _di_f_utf_is_word_dash_
  f_status_t f_utf_is_word_dash(const f_string_t character, const f_array_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word_dash(character_utf, strict);
    }

    if (isalnum(*character) || *character == f_string_ascii_underscore_s.string[0] || *character == f_string_ascii_minus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_word_dash_

#ifndef _di_f_utf_is_word_dash_plus_
  f_status_t f_utf_is_word_dash_plus(const f_string_t character, const f_array_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word_dash_plus(character_utf, strict);
    }

    if (isalnum(*character) || *character == f_string_ascii_underscore_s.string[0] || *character == f_string_ascii_minus_s.string[0] || *character == f_string_ascii_plus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_word_dash_plus_

#ifndef _di_f_utf_is_zero_width_
  f_status_t f_utf_is_zero_width(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_byte_width_is(*character)) {
      if (macro_f_utf_byte_width_is(*character) > width_max) {
        return F_status_set_error(F_failure);
      }

      if (macro_f_utf_byte_width_is(*character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      f_utf_char_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_zero_width(character_utf);
    }

    // These control characters are considered zero-width spaces.
    if (*character >= 0x00 && *character <= 0x08) {
      return F_true;
    }
    else if (*character >= 0x0c && *character <= 0x1f) {
      return F_true;
    }
    else if (*character == 0x7f) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_zero_width_

#ifdef __cplusplus
} // extern "C"
#endif

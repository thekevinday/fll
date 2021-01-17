#include "utf.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_buffer_decrement_
  f_status_t f_utf_buffer_decrement(const f_string_static_t buffer, f_string_range_t *range, const f_string_length_t step) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) return F_data_not;

    f_string_length_t i = 0;
    uint8_t width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[range->start - 1]);

      if (width > range->start) {
        if (width > 1) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        return F_none_eos;
      }

      i++;
      range->start -= width;
    } while (i < step);

    return F_none;
  }
#endif // _di_f_utf_buffer_decrement_

#ifndef _di_f_utf_buffer_increment_
  f_status_t f_utf_buffer_increment(const f_string_static_t buffer, f_string_range_t *range, const f_string_length_t step) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) return F_data_not;

    f_string_length_t i = 0;
    uint8_t width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[range->start]);

      if (range->start + width > range->stop) {
        if (width > 1) {
          return F_status_set_error(F_complete_not_utf_stop);
        }

        range->start += width;
        return F_none_stop;
      }
      else if (range->start + width >= buffer.used) {
        if (width > 1) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        range->start += width;
        return F_none_eos;
      }

      i++;
      range->start += width;
    } while (i < step);

    return F_none;
  }
#endif // _di_f_utf_buffer_increment_

#ifndef _di_f_utf_character_is_
  f_status_t f_utf_character_is(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_

#ifndef _di_f_utf_character_is_alpha_
  f_status_t f_utf_character_is_alpha(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isalpha(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_alpha(character, width);
  }
#endif // _di_f_utf_character_is_alpha_

#ifndef _di_f_utf_character_is_alpha_digit_
  f_status_t f_utf_character_is_alpha_digit(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_alpha_digit(character, width);
  }
#endif // _di_f_utf_character_is_alpha_digit_

#ifndef _di_f_utf_character_is_alpha_numeric_
  f_status_t f_utf_character_is_alpha_numeric(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_alpha_numeric(character, width);
  }
#endif // _di_f_utf_character_is_alpha_numeric_

#ifndef _di_f_utf_character_is_ascii_
  f_status_t f_utf_character_is_ascii(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_ascii(character, width);
  }
#endif // _di_f_utf_character_is_ascii_

#ifndef _di_f_utf_character_is_combining_
  f_status_t f_utf_character_is_combining(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      // There are no combining characters in ASCII.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    if (width != 3) {
      return F_false;
    }

    return private_f_utf_character_is_combining(character, width);
  }
#endif // _di_f_utf_character_is_combining_

#ifndef _di_f_utf_character_is_control_
  f_status_t f_utf_character_is_control(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (iscntrl(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_control(character, width);
  }
#endif // _di_f_utf_character_is_control_

#ifndef _di_f_utf_character_is_control_picture_
  f_status_t f_utf_character_is_control_picture(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {

      // There are no control picture characters in ASCII.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    if (width != 3) {
      return F_false;
    }

    return private_f_utf_character_is_control_picture(character, width);
  }
#endif // _di_f_utf_character_is_control_picture_

#ifndef _di_f_utf_character_is_digit_
  f_status_t f_utf_character_is_digit(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isdigit(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_digit(character, width);
  }
#endif // _di_f_utf_character_is_digit_

#ifndef _di_f_utf_character_is_emoji_
  f_status_t f_utf_character_is_emoji(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isdigit(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_emoji(character, width);
  }
#endif // _di_f_utf_character_is_emoji_

#ifndef _di_f_utf_character_is_fragment_
  f_status_t f_utf_character_is_fragment(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (width == 1) return F_true;

    return F_false;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_status_t f_utf_character_is_graph(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isgraph(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    if (private_f_utf_character_is_control(character, width)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(character, width)) {
      return F_false;
    }

    if (private_f_utf_character_is_zero_width(character, width)) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_graph_

#ifndef _di_f_utf_character_is_numeric_
  f_status_t f_utf_character_is_numeric(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isdigit(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_numeric(character, width);
  }
#endif // _di_f_utf_character_is_numeric_

#ifndef _di_f_utf_character_is_phonetic_
  f_status_t f_utf_character_is_phonetic(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {

      // There are no ASCII phonetic characters.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_phonetic(character, width);
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_private_
  f_status_t f_utf_character_is_private(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {

      // There are no ASCII private characters.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_private(character, width);
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_punctuation_
  f_status_t f_utf_character_is_punctuation(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {

      // ASCII: '!' to '#'.
      if (character > 0x20000000 && character < 0x24000000) {
        return F_true;
      }

      // ASCII: '%' to '*'.
      if (character > 0x24000000 && character < 0x2b000000) {
        return F_true;
      }

      // ASCII: ',' to '/'.
      if (character > 0x2b000000 && character < 0x30000000) {
        return F_true;
      }

      // ASCII: ':', ';', '?', or '@'.
      if (character == 0x3a000000 || character == 0x3b000000 || character == 0x3f000000 || character == 0x40000000) {
        return F_true;
      }

      // ASCII: '[' to ']'.
      if (character > 0x5a000000 && character < 0x5d000000) {
        return F_true;
      }

      // ASCII: '_', '{', or '}'.
      if (character == 0x5f000000 || character == 0x7b000000 || character == 0x7d000000) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_punctuation(character, width);
  }
#endif // _di_f_utf_character_is_punctuation_

#ifndef _di_f_utf_character_is_symbol_
  f_status_t f_utf_character_is_symbol(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {

      // ASCII: '$' or '+'.
      if (character == 0x24000000 || character == 0x2b000000) {
        return F_true;
      }

      // ASCII: '<' to '>'.
      if (character > 0x3c000000 && character < 0x3e000000) {
        return F_true;
      }

      // ASCII: '^', '`', '|', or '~'.
      if (character == 0x5e000000 || character == 0x60000000 || character == 0x7c000000 || character == 0x7e000000) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_symbol(character, width);
  }
#endif // _di_f_utf_character_is_symbol_

#ifndef _di_f_utf_character_is_unassigned_
  f_status_t f_utf_character_is_unassigned(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width || width == 1) {
      return F_false;
    }

    return private_f_utf_character_is_unassigned(character, width);
  }
#endif // _di_f_utf_character_is_unassigned_

#ifndef _di_f_utf_character_is_valid_
  f_status_t f_utf_character_is_valid(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (width == 1) {
      return F_false;
    }

    return private_f_utf_character_is_valid(character, width);
  }
#endif // _di_f_utf_character_is_valid_

#ifndef _di_f_utf_character_is_whitespace_
  f_status_t f_utf_character_is_whitespace(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isspace(f_macro_utf_character_t_to_char_1(character))) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_whitespace(character, width);
  }
#endif // _di_f_utf_character_is_whitespace_

#ifndef _di_f_utf_character_is_whitespace_modifier_
  f_status_t f_utf_character_is_whitespace_modifier(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      // There are no ASCII whitespace modifiers.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_whitespace_modifier(character, width);
  }
#endif // _di_f_utf_character_is_whitespace_modifier_

#ifndef _di_f_utf_character_is_whitespace_other_
  f_status_t f_utf_character_is_whitespace_other(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {

      // There are no ASCII whitespace other.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_whitespace_other(character, width);
  }
#endif // _di_f_utf_character_is_whitespace_other_

#ifndef _di_f_utf_character_is_word_
  f_status_t f_utf_character_is_word(const f_utf_character_t character, const bool strict) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(f_macro_utf_character_t_to_char_1(character)) || character == '_') {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_word(character, width, strict);
  }
#endif // _di_f_utf_character_is_word_

#ifndef _di_f_utf_character_is_word_dash_
  f_status_t f_utf_character_is_word_dash(const f_utf_character_t character, const bool strict) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(f_macro_utf_character_t_to_char_1(character)) || character == '_' || character == '-') {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_word_dash(character, width, strict);
  }
#endif // _di_f_utf_character_is_word_dash_

#ifndef _di_f_utf_character_is_word_dash_plus_
  f_status_t f_utf_character_is_word_dash_plus(const f_utf_character_t character, const bool strict) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(f_macro_utf_character_t_to_char_1(character)) || character == '_' || character == '-' || character == '+') {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_word_dash_plus(character, width, strict);
  }
#endif // _di_f_utf_character_is_word_dash_plus_

#ifndef _di_f_utf_character_is_zero_width_
  f_status_t f_utf_character_is_zero_width(const f_utf_character_t character) {
    const uint8_t width = f_macro_utf_character_t_width_is(character);

    if (!width) {
      const uint8_t ascii = f_macro_utf_character_t_to_char_1(character);

      // These control characters are considered zero-width spaces.
      if (ascii >= 0x00 && ascii <= 0x08) {
        return F_true;
      }
      else if (ascii == 0x0a) {
        return F_true;
      }
      else if (ascii >= 0x0c && ascii <= 0x1f) {
        return F_true;
      }
      else if (ascii == 0x7f) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_zero_width(character, width);
  }
#endif // _di_f_utf_character_is_zero_width_

#ifndef _di_f_utf_character_to_char_
  f_status_t f_utf_character_to_char(const f_utf_character_t utf_character, f_string_t *character, f_string_length_t *width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (!utf_character) return F_status_set_error(F_parameter);
      if (!width_max && *character) return F_status_set_error(F_parameter);
      if (width_max && !*character) return F_status_set_error(F_parameter);
      if (width_max && *width_max > 4) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    uint8_t width = f_macro_utf_character_t_width_is(utf_character);

    if (!width_max) {
      f_macro_string_t_clear((*character))
      f_macro_string_t_resize(status, (*character), 0, width)
      if (F_status_is_error(status)) return status;

      width = 1;
      *width_max = 1;
    }
    else if (width == 1) {
      return F_status_is_error(F_utf);
    }
    else if (width > *width_max) {
      return F_status_set_error(F_failure);
    }

    *width_max = width;

    if (f_utf_is_big_endian()) {
      memcpy(*character, &utf_character, width);
    }
    else {
      uint32_t utf = 0;

      if (width == 1) {
        utf = f_macro_utf_character_t_to_char_1(utf_character) << 24;
      }
      else if (width == 2) {
        utf = (f_macro_utf_character_t_to_char_2(utf_character) << 24) | (f_macro_utf_character_t_to_char_1(utf_character) << 16);
      }
      else if (width == 3) {
        utf = (f_macro_utf_character_t_to_char_3(utf_character) << 24) | (f_macro_utf_character_t_to_char_2(utf_character) << 16) | (f_macro_utf_character_t_to_char_1(utf_character) << 8);
      }
      else if (width == 4) {
        utf = (f_macro_utf_character_t_to_char_4(utf_character) << 24) | (f_macro_utf_character_t_to_char_3(utf_character) << 16) | (f_macro_utf_character_t_to_char_2(utf_character) << 8) | f_macro_utf_character_t_to_char_1(utf_character);
      }

      memcpy(*character, &utf, width);
    }

    return F_none;
  }
#endif // _di_f_utf_character_to_char_

#ifndef _di_f_utf_is_big_endian_
  f_status_t f_utf_is_big_endian() {
    uint16_t test_int = (0x01 << 8) | 0x02;
    int8_t test_char[2] = {0x01, 0x02};

    if (!memcmp(&test_int, test_char, 2)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_big_endian_

#ifndef _di_f_utf_is_
  f_status_t f_utf_is(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    return F_true;
  }
#endif // _di_f_utf_is_

#ifndef _di_f_utf_is_alpha_
  f_status_t f_utf_is_alpha(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isalpha(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_alpha(character_utf, width);
  }
#endif // _di_f_utf_is_alpha_

#ifndef _di_f_utf_is_alpha_digit_
  f_status_t f_utf_is_alpha_digit(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isalnum(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_alpha_digit(character_utf, width);
  }
#endif // _di_f_utf_is_alpha_digit_

#ifndef _di_f_utf_is_alpha_numeric_
  f_status_t f_utf_is_alpha_numeric(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isalnum(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_alpha_numeric(character_utf, width);
  }
#endif // _di_f_utf_is_alpha_numeric_

#ifndef _di_f_utf_is_ascii_
  f_status_t f_utf_is_ascii(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_ascii(character_utf, width);
  }
#endif // _di_f_utf_is_ascii_

#ifndef _di_f_utf_is_combining_
  f_status_t f_utf_is_combining(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    // There are no ASCII combining characters.
    if (!width) {
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_combining(character_utf, width);
  }
#endif // _di_f_utf_is_combining_

#ifndef _di_f_utf_is_control_
  f_status_t f_utf_is_control(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (iscntrl(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_control(character_utf, width);
  }
#endif // _di_f_utf_is_control_

#ifndef _di_f_utf_is_control_picture_
  f_status_t f_utf_is_control_picture(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    // There are no ASCII control pictures.
    if (!width) {
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_control_picture(character_utf, width);
  }
#endif // _di_f_utf_is_control_picture_

#ifndef _di_f_utf_is_digit_
  f_status_t f_utf_is_digit(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isdigit(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_digit(character_utf, width);
  }
#endif // _di_f_utf_is_digit_

#ifndef _di_f_utf_is_emoji_
  f_status_t f_utf_is_emoji(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isdigit(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_emoji(character_utf, width);
  }
#endif // _di_f_utf_is_emoji_

#ifndef _di_f_utf_is_fragment_
  f_status_t f_utf_is_fragment(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 1) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_fragment_

#ifndef _di_f_utf_is_graph_
  f_status_t f_utf_is_graph(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isgraph(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    if (private_f_utf_character_is_control(character_utf, width)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(character_utf, width)) {
      return F_false;
    }

    // This test is in isolation so zero-width characters must be treated as a non-graph.
    if (private_f_utf_character_is_zero_width(character_utf, width)) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_is_graph_

#ifndef _di_f_utf_is_numeric_
  f_status_t f_utf_is_numeric(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isdigit(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_numeric(character_utf, width);
  }
#endif // _di_f_utf_is_numeric_

#ifndef _di_f_utf_is_phonetic_
  f_status_t f_utf_is_phonetic(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      // There are no ASCII phonetic characters.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_phonetic(character_utf, width);
  }
#endif // _di_f_utf_is_phonetic_

#ifndef _di_f_utf_is_private_
  f_status_t f_utf_is_private(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      // There are no ASCII private characters.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_private(character_utf, width);
  }
#endif // _di_f_utf_is_private_

#ifndef _di_f_utf_is_punctuation_
  f_status_t f_utf_is_punctuation(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {

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

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_punctuation(character_utf, width);
  }
#endif // _di_f_utf_is_punctuation_

#ifndef _di_f_utf_is_symbol_
  f_status_t f_utf_is_symbol(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {

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

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_symbol(character_utf, width);
  }
#endif // _di_f_utf_is_symbol_

#ifndef _di_f_utf_is_unassigned_
  f_status_t f_utf_is_unassigned(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width || width == 1) {
      return F_false;
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_unassigned(character_utf, width);
  }
#endif // _di_f_utf_is_unassigned_

#ifndef _di_f_utf_is_valid_
  f_status_t f_utf_is_valid(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 1) {
      return F_false;
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_valid(character_utf, width);
  }
#endif // _di_f_utf_is_valid_

#ifndef _di_f_utf_is_whitespace_
  f_status_t f_utf_is_whitespace(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isspace(*character)) {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return f_utf_character_is_whitespace(character_utf);
  }
#endif // _di_f_utf_is_whitespace_

#ifndef _di_f_utf_is_whitespace_modifier_
  f_status_t f_utf_is_whitespace_modifier(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {

      // There are no ASCII whitespace modifiers.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_whitespace_modifier(character_utf, width);
  }
#endif // _di_f_utf_is_whitespace_modifier_

#ifndef _di_f_utf_is_whitespace_other_
  f_status_t f_utf_is_whitespace_other(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {

      // There are no ASCII whitespace other.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_whitespace_other(character_utf, width);
  }
#endif // _di_f_utf_is_whitespace_other_

#ifndef _di_f_utf_is_word_
  f_status_t f_utf_is_word(const f_string_t character, const f_string_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isalnum(*character) || *character == '_') {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_word(character_utf, width, strict);
  }
#endif // _di_f_utf_is_word_

#ifndef _di_f_utf_is_word_dash_
  f_status_t f_utf_is_word_dash(const f_string_t character, const f_string_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isalnum(*character) || *character == '_' || *character == '-') {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_word_dash(character_utf, width, strict);
  }
#endif // _di_f_utf_is_word_dash_

#ifndef _di_f_utf_is_word_dash_plus_
  f_status_t f_utf_is_word_dash_plus(const f_string_t character, const f_string_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      if (isalnum(*character) || *character == '_' || *character == '-' || *character == '+') {
        return F_true;
      }

      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_word_dash_plus(character_utf, width, strict);
  }
#endif // _di_f_utf_is_word_dash_plus_

#ifndef _di_f_utf_is_zero_width_
  f_status_t f_utf_is_zero_width(const f_string_t character, const f_string_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {

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

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      f_status_t status = 0;

      status = f_utf_char_to_character(character, width_max, &character_utf);

      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_zero_width(character_utf, width);
  }
#endif // _di_f_utf_is_zero_width_

#ifndef _di_f_utf_char_to_character_
  f_status_t f_utf_char_to_character(const f_string_t character, const f_string_length_t width_max, f_utf_character_t *character_utf) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
      if (!character_utf) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = f_macro_utf_byte_width_is(*character);

    if (!width) {
      *character_utf = f_macro_utf_character_t_from_char_1(character[0]);
      return F_none;
    }
    else if (width == 1) {
      return F_status_is_error(F_utf);
    }

    if (width > width_max) {
      return F_status_set_error(F_failure);
    }

    *character_utf = f_macro_utf_character_t_from_char_1(character[0]);

    if (width < 2) {
      return F_none;
    }

    *character_utf |= f_macro_utf_character_t_from_char_2(character[1]);

    if (width == 2) {
      return F_none;
    }

    *character_utf |= f_macro_utf_character_t_from_char_3(character[2]);

    if (width == 3) {
      return F_none;
    }

    *character_utf |= f_macro_utf_character_t_from_char_4(character[3]);

    return F_none;
  }
#endif // _di_f_utf_char_to_character_

#ifndef _di_f_utf_string_append_
  f_status_t f_utf_string_append(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_append(source, length, destination);
  }
#endif // _di_f_utf_string_append_

#ifndef _di_f_utf_string_append_assure_
  f_status_t f_utf_string_append_assure(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_f_utf_string_append(source, length, destination);

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source[length - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_append_assure_

#ifndef _di_f_utf_string_append_assure_nulless_
  f_status_t f_utf_string_append_assure_nulless(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    if (destination->used < length) {
      return private_f_utf_string_append_nulless(source, length, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source[length - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append_nulless(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_append_assure_nulless_

#ifndef _di_f_utf_string_append_nulless_
  f_status_t f_utf_string_append_nulless(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_append_nulless_

#ifndef _di_f_utf_string_dynamic_append_
  f_status_t f_utf_string_dynamic_append(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_append_

#ifndef _di_f_utf_string_dynamic_append_assure_
  f_status_t f_utf_string_dynamic_append_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_append(source.string, source.used, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= source.used && j <= destination->used) {
      if (!source.string[source.used - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_append_assure_

#ifndef _di_f_utf_string_dynamic_append_assure_nulless_
  f_status_t f_utf_string_dynamic_append_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_append_nulless(source.string, source.used, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= source.used && j <= destination->used) {
      if (!source.string[source.used - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append_nulless(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

#ifndef _di_f_utf_string_dynamic_append_nulless_
  f_status_t f_utf_string_dynamic_append_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_append_nulless_

#ifndef _di_f_utf_string_dynamic_mash_
  f_status_t f_utf_string_dynamic_mash(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mash_

#ifndef _di_f_utf_string_dynamic_mash_nulless_
  f_status_t f_utf_string_dynamic_mash_nulless(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mash_nulless_

#ifndef _di_f_utf_string_dynamic_mish_
  f_status_t f_utf_string_dynamic_mish(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mish_

#ifndef _di_f_utf_string_dynamic_mish_nulless_
  f_status_t f_utf_string_dynamic_mish_nulless(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mish_nulless_

#ifndef _di_f_utf_string_dynamic_partial_append_
  f_status_t f_utf_string_dynamic_partial_append(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_append_

#ifndef _di_f_utf_string_dynamic_partial_append_assure_
  f_status_t f_utf_string_dynamic_partial_append_assure(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_append(source.string + range.start, length, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source.string[range.stop - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while
  }
#endif // _di_f_utf_string_dynamic_partial_append_assure_

#ifndef _di_f_utf_string_dynamic_partial_append_assure_nulless_
  f_status_t f_utf_string_dynamic_partial_append_assure_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_append_nulless(source.string + range.start, length, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source.string[range.stop - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append_nulless(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while
  }
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

#ifndef _di_f_utf_string_dynamic_partial_append_nulless_
  f_status_t f_utf_string_dynamic_partial_append_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_append_nulless_

#ifndef _di_f_utf_string_dynamic_partial_mash_
  f_status_t f_utf_string_dynamic_partial_mash(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mash_

#ifndef _di_f_utf_string_dynamic_partial_mash_nulless_
  f_status_t f_utf_string_dynamic_partial_mash_nulless(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mash_nulless_

#ifndef _di_f_utf_string_dynamic_partial_mish_
  f_status_t f_utf_string_dynamic_partial_mish(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mish_

#ifndef _di_f_utf_string_dynamic_partial_mish_nulless_
  f_status_t f_utf_string_dynamic_partial_mish_nulless(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mish_nulless_

#ifndef _di_f_utf_string_dynamic_partial_prepend_
  f_status_t f_utf_string_dynamic_partial_prepend(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_f_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_

#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_
  f_status_t f_utf_string_dynamic_partial_prepend_assure(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_prepend(source.string + range.start, length, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source.string[i + range.start]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_f_utf_string_prepend(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_

#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_nulless_
  f_status_t f_utf_string_dynamic_partial_prepend_assure_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_prepend_nulless(source.string + range.start, length, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source.string[i + range.start]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_f_utf_string_prepend_nulless(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_nulless

#ifndef _di_f_utf_string_dynamic_partial_prepend_nulless_
  f_status_t f_utf_string_dynamic_partial_prepend_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_f_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_nulless

#ifndef _di_f_utf_string_dynamic_prepend_
  f_status_t f_utf_string_dynamic_prepend(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_prepend_

#ifndef _di_f_utf_string_dynamic_prepend_assure_
  f_status_t f_utf_string_dynamic_prepend_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_prepend(source.string, source.used, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < source.used && j < destination->used) {
      if (!source.string[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_f_utf_string_prepend(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_prepend_assure_

#ifndef _di_f_utf_string_dynamic_prepend_assure_nulless_
  f_status_t f_utf_string_dynamic_prepend_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < source.used && j < destination->used) {
      if (!source.string[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_prepend_assure_nulless_

#ifndef _di_f_utf_string_dynamic_prepend_nulless_
  f_status_t f_utf_string_dynamic_prepend_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_prepend_nulless_

#ifndef _di_f_utf_string_dynamic_seek_line_to_
  f_status_t f_utf_string_dynamic_seek_line_to(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const f_utf_character_t seek_to_this) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_this) {

      if (buffer.string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      range->start++;

      if (f_macro_utf_character_t_width_is(buffer.string[range->start]) == 1) return F_status_set_error(F_utf);

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_seek_line_to_

#ifndef _di_f_utf_string_dynamic_seek_to_
  f_status_t f_utf_string_dynamic_seek_to(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const f_utf_character_t seek_to_this) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_this) {
      range->start++;

      if (f_macro_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_seek_to_

#ifndef _di_f_utf_string_dynamic_terminate_
  f_status_t f_utf_string_dynamic_terminate(f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!destination->used && destination->size && !destination->string[destination->used - 1]) {
      return F_none;
    }

    if (destination->used == f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    const f_string_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total;

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_terminate_

#ifndef _di_f_utf_string_dynamic_terminate_after_
  f_status_t f_utf_string_dynamic_terminate_after(f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used) {
      for (; destination->used; destination->used--) {
        if (!destination->string[destination->used - 1]) continue;
        break;
      } // for
    }

    if (destination->used == f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    const f_string_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total - 1;

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_terminate_after_

#ifndef _di_f_utf_string_mash_
  f_status_t f_utf_string_mash(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source, length, destination);
  }
#endif // _di_f_utf_string_mash_

#ifndef _di_f_utf_string_mash_nulless_
  f_status_t f_utf_string_mash_nulless(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_mash_nulless_

#ifndef _di_f_utf_string_mish_
  f_status_t f_utf_string_mish(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source, length, destination);
  }
#endif // _di_f_utf_string_mish_

#ifndef _di_f_utf_string_mish_nulless_
  f_status_t f_utf_string_mish_nulless(const f_utf_string_t glue, const f_string_length_t glue_length, const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_mish_nulless_

#ifndef _di_f_utf_string_prepend_
  f_status_t f_utf_string_prepend(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_prepend(source, length, destination);
  }
#endif // _di_f_utf_string_prepend_

#ifndef _di_f_utf_string_prepend_assure_
  f_status_t f_utf_string_prepend_assure(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_f_utf_string_prepend(source, length, destination);

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) return private_f_utf_string_prepend(source, length, destination);

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_prepend_assure_

#ifndef _di_f_utf_string_prepend_assure_nulless_
  f_status_t f_utf_string_prepend_assure_nulless(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_f_utf_string_prepend_nulless(source, length, destination);

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) return private_f_utf_string_prepend_nulless(source, length, destination);

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_prepend_assure_nulless_

#ifndef _di_f_utf_string_prepend_nulless_
  f_status_t f_utf_string_prepend_nulless(const f_utf_string_t source, const f_string_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_prepend_nulless_

#ifndef _di_f_utf_string_seek_line_to_
  f_status_t f_utf_string_seek_line_to(const f_utf_string_t string, f_utf_string_range_t *range, const f_utf_character_t seek_to_this) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_t_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] != seek_to_this) {

      if (string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      range->start++;

      if (f_macro_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_line_to_

#ifndef _di_f_utf_string_seek_to_
  f_status_t f_utf_string_seek_to(const f_utf_string_t string, f_utf_string_range_t *range, const f_utf_character_t seek_to_this) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_t_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] != seek_to_this) {
      range->start++;

      if (f_macro_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_to_

#ifdef __cplusplus
} // extern "C"
#endif

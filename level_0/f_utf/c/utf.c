#include "utf.h"
#include "private-utf.h"
#include "private-utf-is_unassigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_buffer_decrement_
  f_status_t f_utf_buffer_decrement(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t i = 0;
    uint8_t width = 0;

    do {
      width = macro_f_utf_byte_width(buffer.string[range->start - 1]);

      if (width > range->start) {
        if (width > 1 && width > range->start + 1) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        return F_none_eos;
      }

      ++i;
      range->start -= width;

    } while (i < step);

    return F_none;
  }
#endif // _di_f_utf_buffer_decrement_

#ifndef _di_f_utf_buffer_increment_
  f_status_t f_utf_buffer_increment(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t i = 0;
    uint8_t width = 0;

    do {
      width = macro_f_utf_byte_width(buffer.string[range->start]);

      if (range->start + width > range->stop) {
        if (width > 1 && range->start + width > range->stop + 1) {
          return F_status_set_error(F_complete_not_utf_stop);
        }

        range->start += width;

        return F_none_stop;
      }
      else if (range->start + width >= buffer.used) {
        if (width > 1 && range->start + width >= buffer.used + 1) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        range->start += width;

        return F_none_eos;
      }

      ++i;
      range->start += width;

    } while (i < step);

    return F_none;
  }
#endif // _di_f_utf_buffer_increment_

#ifndef _di_f_utf_char_to_character_
  f_status_t f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_character_t *character_utf) {
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

#ifndef _di_f_utf_character_is_
  f_status_t f_utf_character_is(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_utf_fragment;
      }

      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_

#ifndef _di_f_utf_character_is_alpha_
  f_status_t f_utf_character_is_alpha(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alpha(character);
    }

    if (isalpha(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alpha_

#ifndef _di_f_utf_character_is_alpha_digit_
  f_status_t f_utf_character_is_alpha_digit(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alpha_digit(character);
    }

    if (isalnum(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alpha_digit_

#ifndef _di_f_utf_character_is_alpha_numeric_
  f_status_t f_utf_character_is_alpha_numeric(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alpha_numeric(character);
    }

    if (isalnum(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alpha_numeric_

#ifndef _di_f_utf_character_is_ascii_
  f_status_t f_utf_character_is_ascii(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_ascii_

#ifndef _di_f_utf_character_is_combining_
  f_status_t f_utf_character_is_combining(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_combining(character);
    }

    // There are no combining characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_combining_

#ifndef _di_f_utf_character_is_control_
  f_status_t f_utf_character_is_control(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control(character);
    }

    if (iscntrl(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_control_

#ifndef _di_f_utf_character_is_control_code_
  f_status_t f_utf_character_is_control_code(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_code(character);
    }

    if (iscntrl(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_control_code_

#ifndef _di_f_utf_character_is_control_picture_
  f_status_t character_is_control_format(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_format(character);
    }

    // There are no control format characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_control_format_

#ifndef _di_f_utf_character_is_control_picture_
  f_status_t f_utf_character_is_control_picture(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_picture(character);
    }

    // There are no control picture characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_control_picture_

#ifndef _di_f_utf_character_is_digit_
  f_status_t f_utf_character_is_digit(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_digit(character);
    }

    if (isdigit(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_digit_

#ifndef _di_f_utf_character_is_emoji_
  f_status_t f_utf_character_is_emoji(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_emoji(character);
    }

    if (isdigit(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_emoji_

#ifndef _di_f_utf_character_is_fragment_
  f_status_t f_utf_character_is_fragment(const f_utf_character_t character) {

    return macro_f_utf_character_t_width_is(character) == 1;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_status_t f_utf_character_is_graph(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (private_f_utf_character_is_control(character)) {
        return F_false;
      }

      if (private_f_utf_character_is_whitespace(character)) {
        return F_false;
      }

      if (private_f_utf_character_is_zero_width(character)) {
        return F_false;
      }

      return F_true;
    }

    if (isgraph(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_graph_

#ifndef _di_f_utf_character_is_numeric_
  f_status_t f_utf_character_is_numeric(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_numeric(character);
    }

    if (isdigit(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_numeric_

#ifndef _di_f_utf_character_is_phonetic_
  f_status_t f_utf_character_is_phonetic(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_phonetic(character);
    }

    // There are no ASCII phonetic characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_private_
  f_status_t f_utf_character_is_private(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_private(character);
    }

    // There are no ASCII private characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_punctuation_
  f_status_t f_utf_character_is_punctuation(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_punctuation(character);
    }

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
#endif // _di_f_utf_character_is_punctuation_

#ifndef _di_f_utf_character_is_symbol_
  f_status_t f_utf_character_is_symbol(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_symbol(character);
    }

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
#endif // _di_f_utf_character_is_symbol_

#ifndef _di_f_utf_character_is_unassigned_
  f_status_t f_utf_character_is_unassigned(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_unassigned(character);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_unassigned_

#ifndef _di_f_utf_character_is_valid_
  f_status_t f_utf_character_is_valid(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_valid(character);
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_valid_

#ifndef _di_f_utf_character_is_whitespace_
  f_status_t f_utf_character_is_whitespace(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace(character);
    }

    if (isspace(macro_f_utf_character_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_

#ifndef _di_f_utf_character_is_whitespace_modifier_
  f_status_t f_utf_character_is_whitespace_modifier(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_modifier(character);
    }

    // There are no ASCII whitespace modifiers.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_modifier_

#ifndef _di_f_utf_character_is_whitespace_other_
  f_status_t f_utf_character_is_whitespace_other(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_other(character);
    }

    // There are no ASCII whitespace other.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_other_

#ifndef _di_f_utf_character_is_wide_
  f_status_t f_utf_character_is_wide(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_wide(character);
    }

    // There are no wide ASCII characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_wide_

#ifndef _di_f_utf_character_is_word_
  f_status_t f_utf_character_is_word(const f_utf_character_t character, const bool strict) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word(character, strict);
    }

    if (isalnum(macro_f_utf_character_t_to_char_1(character)) || character == f_string_ascii_underscore_s[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_

#ifndef _di_f_utf_character_is_word_dash_
  f_status_t f_utf_character_is_word_dash(const f_utf_character_t character, const bool strict) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word_dash(character, strict);
    }

    if (isalnum(macro_f_utf_character_t_to_char_1(character)) || character == f_string_ascii_underscore_s[0] || character == f_string_ascii_minus_s[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_dash_

#ifndef _di_f_utf_character_is_word_dash_plus_
  f_status_t f_utf_character_is_word_dash_plus(const f_utf_character_t character, const bool strict) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word_dash_plus(character, strict);
    }

    if (isalnum(macro_f_utf_character_t_to_char_1(character)) || character == f_string_ascii_underscore_s[0] || character == f_string_ascii_minus_s[0] || character == f_string_ascii_plus_s[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_dash_plus_

#ifndef _di_f_utf_character_is_zero_width_
  f_status_t f_utf_character_is_zero_width(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character)) {
      if (macro_f_utf_character_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_zero_width(character);
    }

    const uint8_t ascii = macro_f_utf_character_t_to_char_1(character);

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
#endif // _di_f_utf_character_is_zero_width_

#ifndef _di_f_utf_character_to_char_
  f_status_t f_utf_character_to_char(const f_utf_character_t utf_character, f_string_t *character, f_array_length_t *width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (!utf_character) return F_status_set_error(F_parameter);
      if (!character) return F_status_set_error(F_parameter);
      if (!width_max) return F_status_set_error(F_parameter);
      if (!*width_max) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_character_t_width_is(utf_character)) {
      if (macro_f_utf_character_t_width_is(utf_character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      #if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32_t utf = 0;

        switch (macro_f_utf_character_t_width_is(utf_character)) {
          case 1:
            utf = macro_f_utf_character_t_to_char_1(utf_character) << 24;
            break;
          case 2:
            utf = (macro_f_utf_character_t_to_char_2(utf_character) << 24) | (macro_f_utf_character_t_to_char_1(utf_character) << 16);
            break;
          case 3:
            utf = (macro_f_utf_character_t_to_char_3(utf_character) << 24) | (macro_f_utf_character_t_to_char_2(utf_character) << 16) | (macro_f_utf_character_t_to_char_1(utf_character) << 8);
            break;
          case 4:
            utf = (macro_f_utf_character_t_to_char_4(utf_character) << 24) | (macro_f_utf_character_t_to_char_3(utf_character) << 16) | (macro_f_utf_character_t_to_char_2(utf_character) << 8) | macro_f_utf_character_t_to_char_1(utf_character);
            break;
          default:
            return F_status_set_error(F_failure);
        }

        memcpy(*character, &utf, macro_f_utf_character_t_width_is(utf_character));
      #else
        memcpy(*character, &utf_character, macro_f_utf_character_t_width_is(utf_character));
      #endif // __BYTE_ORDER == __LITTLE_ENDIAN

      return F_none;
    }

    #if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32_t utf = macro_f_utf_character_t_to_char_1(utf_character) << 24;

      memcpy(*character, &utf, 1);
    #else
      memcpy(*character, &utf_character, 1);
    #endif // __BYTE_ORDER == __LITTLE_ENDIAN

    return F_none;
  }
#endif // _di_f_utf_character_to_char_

#ifndef _di_f_utf_character_unicode_to_
  f_status_t f_utf_character_unicode_to(const f_utf_character_t character, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_character_unicode_to(character, unicode);
  }
#endif // _di_f_utf_character_unicode_to_

#ifndef _di_f_utf_character_unicode_from_
  f_status_t f_utf_character_unicode_from(const uint32_t unicode, f_utf_character_t *character) {
    #ifndef _di_level_0_parameter_checking_
      if (!character) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (unicode > 0x10ffff) {
      return F_status_set_error(F_utf);
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
  f_status_t f_utf_character_unicode_string_to(const f_utf_string_t string, const f_array_length_t length, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_array_length_t i = 0;

    while (i < length && !string[i]) {
      ++i;
    } // while

    if (i < length) {
      if (macro_f_utf_character_t_width_is(string[i])) {
        i = length;
      }
      else {
        if (macro_f_utf_character_t_to_char_1(string[i]) == f_string_ascii_u_s[0] || macro_f_utf_character_t_to_char_1(string[i]) == f_string_ascii_U_s[0]) {
          do {
            ++i;
          } while (i < length && !string[i]);

          if (i < length && !macro_f_utf_character_t_width_is(string[i]) && macro_f_utf_character_t_to_char_1(string[i]) == f_string_ascii_plus_s[0]) {
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

    uint32_t value = 0;
    uint8_t character = 0;

    for (; i < length; ++i) {

      if (!string[i]) continue;

      // Only ASCII character numbers are allowed to represent
      if (macro_f_utf_character_t_width_is(string[i])) {
        return F_status_set_error(F_valid_not);
      }

      value *= 16;
      character = macro_f_utf_character_t_to_char_1(string[i]);

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

    *unicode = value;

    return F_none;
  }
#endif // _di_f_utf_character_unicode_string_to_

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

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

      f_utf_character_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word(character_utf, strict);
    }

    if (isalnum(*character) || *character == f_string_ascii_underscore_s[0]) {
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

      f_utf_character_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word_dash(character_utf, strict);
    }

    if (isalnum(*character) || *character == f_string_ascii_underscore_s[0] || *character == f_string_ascii_minus_s[0]) {
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

      f_utf_character_t character_utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word_dash_plus(character_utf, strict);
    }

    if (isalnum(*character) || *character == f_string_ascii_underscore_s[0] || *character == f_string_ascii_minus_s[0] || *character == f_string_ascii_plus_s[0]) {
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

      f_utf_character_t character_utf = 0;

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

#ifndef _di_f_utf_unicode_from_
  f_status_t f_utf_unicode_from(const uint32_t unicode, const f_array_length_t width_max, f_string_t *character) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // @fixme the code here needs to be reviewed for endianess accuracy for both big and little endian.
    if (unicode > 0x10ffff) {
      return F_status_set_error(F_utf);
    }

    if (unicode < 0x80) {

      // U+0000 -> U+007F
      (*character)[0] = (uint8_t) unicode;

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
    else if (unicode < 0x800) {
      if (width_max < 2) {
        return F_status_set_error(F_utf);
      }

      // U+0080 -> U+07FF
      (*character)[0] = F_utf_byte_2_d | ((uint8_t) ((unicode & 0x7c0) >> 6));
      (*character)[1] = F_utf_byte_1_d | ((uint8_t) (unicode & 0x3f));

      if (width_max > 2) {
        (*character)[2] = 0;

        if (width_max > 2) {
          (*character)[2] = 0;
        }
      }
    }
    else if (unicode < 0x10000) {
      if (width_max < 3) {
        return F_status_set_error(F_utf);
      }

      // U+0800 -> U+FFFF
      (*character)[0] = F_utf_byte_3_d | ((uint8_t) ((unicode & 0xf000) >> 12));
      (*character)[1] = F_utf_byte_1_d | ((uint8_t) ((unicode & 0xfc0) >> 6));
      (*character)[2] = F_utf_byte_1_d | ((uint8_t) (unicode & 0x3f));

      if (width_max > 3) {
        character[3] = 0;
      }
    }
    else {
      if (width_max < 4) {
        return F_status_set_error(F_utf);
      }

      // U+10000 -> U+10FFFF
      (*character)[0] = F_utf_byte_4_d | ((uint8_t) ((unicode & 0x1c0000) >> 18));
      (*character)[1] = F_utf_byte_1_d | ((uint8_t) ((unicode & 0x3f000) >> 12));
      (*character)[2] = F_utf_byte_1_d | ((uint8_t) ((unicode & 0xfc0) >> 6));
      (*character)[3] = F_utf_byte_1_d | ((uint8_t) (unicode & 0x3f));
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

    f_utf_character_t character_utf = 0;

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
      if (string[i] == f_string_ascii_u_s[0] || string[i] == f_string_ascii_U_s[0]) {
        do {
          ++i;
        } while (i < length && !string[i]);

        if (i < length && string[i] == f_string_ascii_plus_s[0]) {
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

    *unicode = value;

    return F_none;
  }
#endif // _di_f_utf_unicode_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

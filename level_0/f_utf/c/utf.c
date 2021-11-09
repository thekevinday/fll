#include "utf.h"
#include "private-utf.h"

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

    return private_f_utf_char_to_character(character, width_max, character_utf);
  }
#endif // _di_f_utf_char_to_character_

#ifndef _di_f_utf_character_is_
  f_status_t f_utf_character_is(const f_utf_character_t character) {

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isalpha(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_ascii(character, width);
  }
#endif // _di_f_utf_character_is_ascii_

#ifndef _di_f_utf_character_is_combining_
  f_status_t f_utf_character_is_combining(const f_utf_character_t character) {

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (iscntrl(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isdigit(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isdigit(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (width == 1) return F_true;

    return F_false;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_status_t f_utf_character_is_graph(const f_utf_character_t character) {

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isgraph(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isdigit(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width || width == 1) {
      return F_false;
    }

    return private_f_utf_character_is_unassigned(character, width);
  }
#endif // _di_f_utf_character_is_unassigned_

#ifndef _di_f_utf_character_is_valid_
  f_status_t f_utf_character_is_valid(const f_utf_character_t character) {

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (width == 1) {
      return F_false;
    }

    return private_f_utf_character_is_valid(character, width);
  }
#endif // _di_f_utf_character_is_valid_

#ifndef _di_f_utf_character_is_whitespace_
  f_status_t f_utf_character_is_whitespace(const f_utf_character_t character) {

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isspace(macro_f_utf_character_t_to_char_1(character))) {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(macro_f_utf_character_t_to_char_1(character)) || character == '_') {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(macro_f_utf_character_t_to_char_1(character)) || character == '_' || character == '-') {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
      if (isalnum(macro_f_utf_character_t_to_char_1(character)) || character == '_' || character == '-' || character == '+') {
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

    const uint8_t width = macro_f_utf_character_t_width_is(character);

    if (!width) {
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

    if (width == 1) {
      return F_status_is_error(F_utf);
    }

    return private_f_utf_character_is_zero_width(character, width);
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

      // @todo endianess is compile time so a function is not needed, replace with macros.
      if (f_utf_is_big_endian()) {
        memcpy(*character, &utf_character, macro_f_utf_character_t_width_is(utf_character));
      }
      else {
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
      }
    }
    else {

      // @todo endianess is compile time so a function is not needed, replace with macros.
      if (f_utf_is_big_endian()) {
        memcpy(*character, &utf_character, 1);
      }
      else {
        uint32_t utf = macro_f_utf_character_t_to_char_1(utf_character) << 24;

        memcpy(*character, &utf, 1);
      }
    }

    return F_none;
  }
#endif // _di_f_utf_character_to_char_

#ifndef _di_f_utf_character_unicode_to_
  f_status_t f_utf_character_unicode_to(const f_utf_character_t character, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_character_t_width(character);

    if (private_f_utf_character_is_valid(character, width) == F_false) {
      return F_status_set_error(F_utf);
    }

    if (width < 2) {

      // U+0000 -> U+007F
      *unicode = macro_f_utf_character_t_to_char_1(character) & 0x7f;
    }
    else if (width == 2) {

      // U+0080 -> U+07FF
      *unicode = (macro_f_utf_character_t_to_char_1(character) & 0x1f) << 6;
      *unicode |= macro_f_utf_character_t_to_char_2(character) & 0x3f;
    }
    else if (width == 3) {

      // U+0800 -> U+FFFF
      *unicode = (macro_f_utf_character_t_to_char_1(character) & 0xf) << 12;
      *unicode |= (macro_f_utf_character_t_to_char_2(character) & 0x3f) << 6;
      *unicode |= macro_f_utf_character_t_to_char_3(character) & 0x3f;
    }
    else if (width == 4) {

      // U+10000 -> U+10FFFF
      *unicode = (macro_f_utf_character_t_to_char_1(character) & 0x7) << 18;
      *unicode |= (macro_f_utf_character_t_to_char_2(character) & 0x3f) << 12;
      *unicode |= (macro_f_utf_character_t_to_char_2(character) & 0x3f) << 6;
      *unicode |= macro_f_utf_character_t_to_char_4(character) & 0x3f;
    }

    return F_none;
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

    if (unicode < 0x80) {

      // U+0000 -> U+007F
      *character = unicode;
    }
    else if (unicode < 0x800) {

      // U+0080 -> U+07FF
      *character = (unicode & 0x7c0) << 2;
      *character |= unicode & 0x3f;
      *character |= 0xc080;
    }
    else if (unicode < 0x10000) {

      // U+0800 -> U+FFFF
      *character = (unicode & 0xf000) << 4;
      *character |= (unicode & 0xfc0) << 2;
      *character |= unicode & 0x3f;
      *character |= 0xe08080;
    }
    else {

      // U+10000 -> U+
      *character = (unicode & 0x1c0000) << 6;
      *character |= (unicode & 0x3f000) << 4;
      *character |= (unicode & 0xfc0) << 2;
      *character |= unicode & 0x3f;
      *character |= 0xe0808080;
    }

    return F_none;
  }
#endif // _di_f_utf_character_unicode_from_

#ifndef _di_f_utf_is_big_endian_
  f_status_t f_utf_is_big_endian() {
    uint16_t test_int = (0x01 << 8) | 0x02;
    uint8_t test_char[2] = {0x01, 0x02};

    if (!memcmp(&test_int, test_char, 2)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_big_endian_

#ifndef _di_f_utf_is_
  f_status_t f_utf_is(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
  f_status_t f_utf_is_alpha(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_alpha(character_utf, width);
  }
#endif // _di_f_utf_is_alpha_

#ifndef _di_f_utf_is_alpha_digit_
  f_status_t f_utf_is_alpha_digit(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_alpha_digit(character_utf, width);
  }
#endif // _di_f_utf_is_alpha_digit_

#ifndef _di_f_utf_is_alpha_numeric_
  f_status_t f_utf_is_alpha_numeric(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_alpha_numeric(character_utf, width);
  }
#endif // _di_f_utf_is_alpha_numeric_

#ifndef _di_f_utf_is_ascii_
  f_status_t f_utf_is_ascii(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_ascii(character_utf, width);
  }
#endif // _di_f_utf_is_ascii_

#ifndef _di_f_utf_is_combining_
  f_status_t f_utf_is_combining(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    // There are no ASCII combining characters.
    if (!width) {
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_combining(character_utf, width);
  }
#endif // _di_f_utf_is_combining_

#ifndef _di_f_utf_is_control_
  f_status_t f_utf_is_control(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_control(character_utf, width);
  }
#endif // _di_f_utf_is_control_

#ifndef _di_f_utf_is_control_picture_
  f_status_t f_utf_is_control_picture(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    // There are no ASCII control pictures.
    if (!width) {
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_control_picture(character_utf, width);
  }
#endif // _di_f_utf_is_control_picture_

#ifndef _di_f_utf_is_digit_
  f_status_t f_utf_is_digit(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_digit(character_utf, width);
  }
#endif // _di_f_utf_is_digit_

#ifndef _di_f_utf_is_emoji_
  f_status_t f_utf_is_emoji(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_emoji(character_utf, width);
  }
#endif // _di_f_utf_is_emoji_

#ifndef _di_f_utf_is_fragment_
  f_status_t f_utf_is_fragment(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (width == 1) {
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

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
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
  f_status_t f_utf_is_numeric(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_numeric(character_utf, width);
  }
#endif // _di_f_utf_is_numeric_

#ifndef _di_f_utf_is_phonetic_
  f_status_t f_utf_is_phonetic(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (!width) {

      // There are no ASCII phonetic characters.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_phonetic(character_utf, width);
  }
#endif // _di_f_utf_is_phonetic_

#ifndef _di_f_utf_is_private_
  f_status_t f_utf_is_private(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (!width) {

      // There are no ASCII private characters.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_private(character_utf, width);
  }
#endif // _di_f_utf_is_private_

#ifndef _di_f_utf_is_punctuation_
  f_status_t f_utf_is_punctuation(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_punctuation(character_utf, width);
  }
#endif // _di_f_utf_is_punctuation_

#ifndef _di_f_utf_is_symbol_
  f_status_t f_utf_is_symbol(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_symbol(character_utf, width);
  }
#endif // _di_f_utf_is_symbol_

#ifndef _di_f_utf_is_unassigned_
  f_status_t f_utf_is_unassigned(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (!width || width == 1) {
      return F_false;
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_unassigned(character_utf, width);
  }
#endif // _di_f_utf_is_unassigned_

#ifndef _di_f_utf_is_valid_
  f_status_t f_utf_is_valid(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (width == 1) {
      return F_false;
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_valid(character_utf, width);
  }
#endif // _di_f_utf_is_valid_

#ifndef _di_f_utf_is_whitespace_
  f_status_t f_utf_is_whitespace(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return f_utf_character_is_whitespace(character_utf);
  }
#endif // _di_f_utf_is_whitespace_

#ifndef _di_f_utf_is_whitespace_modifier_
  f_status_t f_utf_is_whitespace_modifier(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (!width) {

      // There are no ASCII whitespace modifiers.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_whitespace_modifier(character_utf, width);
  }
#endif // _di_f_utf_is_whitespace_modifier_

#ifndef _di_f_utf_is_whitespace_other_
  f_status_t f_utf_is_whitespace_other(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

    if (!width) {

      // There are no ASCII whitespace other.
      return F_false;
    }

    if (width == 1) {
      return F_status_is_error(F_complete_not_utf);
    }

    f_utf_character_t character_utf = 0;

    {
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_whitespace_other(character_utf, width);
  }
#endif // _di_f_utf_is_whitespace_other_

#ifndef _di_f_utf_is_word_
  f_status_t f_utf_is_word(const f_string_t character, const f_array_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_word(character_utf, width, strict);
  }
#endif // _di_f_utf_is_word_

#ifndef _di_f_utf_is_word_dash_
  f_status_t f_utf_is_word_dash(const f_string_t character, const f_array_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_word_dash(character_utf, width, strict);
  }
#endif // _di_f_utf_is_word_dash_

#ifndef _di_f_utf_is_word_dash_plus_
  f_status_t f_utf_is_word_dash_plus(const f_string_t character, const f_array_length_t width_max, const bool strict) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_word_dash_plus(character_utf, width, strict);
  }
#endif // _di_f_utf_is_word_dash_plus_

#ifndef _di_f_utf_is_zero_width_
  f_status_t f_utf_is_zero_width(const f_string_t character, const f_array_length_t width_max) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width_is(*character);

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
      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_character_is_zero_width(character_utf, width);
  }
#endif // _di_f_utf_is_zero_width_

#ifndef _di_f_utf_string_append_
  f_status_t f_utf_string_append(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_append(source, length, destination);
  }
#endif // _di_f_utf_string_append_

#ifndef _di_f_utf_string_append_assure_
  f_status_t f_utf_string_append_assure(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_f_utf_string_append(source, length, destination);

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source[length - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_append_assure_

#ifndef _di_f_utf_string_append_assure_nulless_
  f_status_t f_utf_string_append_assure_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) {
      return F_data_not_eos;
    }

    if (destination->used < length) {
      return private_f_utf_string_append_nulless(source, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source[length - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append_nulless(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_append_assure_nulless_

#ifndef _di_f_utf_string_append_nulless_
  f_status_t f_utf_string_append_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_append_nulless_

#ifndef _di_f_utf_string_mash_
  f_status_t f_utf_string_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
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
  f_status_t f_utf_string_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
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
  f_status_t f_utf_string_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
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
  f_status_t f_utf_string_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
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
  f_status_t f_utf_string_prepend(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_prepend(source, length, destination);
  }
#endif // _di_f_utf_string_prepend_

#ifndef _di_f_utf_string_prepend_assure_
  f_status_t f_utf_string_prepend_assure(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    if (destination->used < length) {
      return private_f_utf_string_prepend(source, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source[i] != destination->string[i]) {
        return private_f_utf_string_prepend(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_prepend_assure_

#ifndef _di_f_utf_string_prepend_assure_nulless_
  f_status_t f_utf_string_prepend_assure_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) {
      return F_data_not_eos;
    }

    if (destination->used < length) {
      return private_f_utf_string_prepend_nulless(source, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source[i] != destination->string[i]) {
        return private_f_utf_string_prepend_nulless(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_prepend_assure_nulless_

#ifndef _di_f_utf_string_prepend_nulless_
  f_status_t f_utf_string_prepend_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_f_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_prepend_nulless_

#ifndef _di_f_utf_string_seek_line_
  f_status_t f_utf_string_seek_line(const f_utf_string_t string, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    while (string[range->start] != F_utf_character_t_eol_d) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      ++range->start;

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_line_

#ifndef _di_f_utf_string_seek_line_to_
  f_status_t f_utf_string_seek_line_to(const f_utf_string_t string, const uint8_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    while (string[range->start] != seek_to) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (string[range->start] == F_utf_character_t_eol_d) {
        return F_none_eol;
      }

      ++range->start;

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_line_to_

#ifndef _di_f_utf_string_seek_to_
  f_status_t f_utf_string_seek_to(const f_utf_string_t string, const uint8_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    while (string[range->start] != seek_to) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      ++range->start;

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_to_

#ifndef _di_f_utf_unicode_to_
  f_status_t f_utf_unicode_to(const f_string_t character, const f_array_length_t width_max, uint32_t *unicode) {
    #ifndef _di_level_0_parameter_checking_
      if (width_max < 1) return F_status_set_error(F_parameter);
      if (!unicode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const uint8_t width = macro_f_utf_byte_width(*character);

    {
      f_utf_character_t character_utf = 0;

      const f_status_t status = private_f_utf_char_to_character(character, width_max, &character_utf);
      if (F_status_is_error(status)) return status;

      if (private_f_utf_character_is_valid(character_utf, width) == F_false) {
        return F_status_set_error(F_utf);
      }
    }

    // @fixme the code here needs to be reviewed for endianess accuracy for both big and little endian.
    if (width == 1) {

      // U+0000 -> U+007F
      *unicode = ((uint8_t) character[0]) & 0x7f;
    }
    else if (width == 2) {

      // U+0080 -> U+07FF
      *unicode = (((uint8_t) character[0]) & 0x1f) << 6;
      *unicode |= ((uint8_t) character[1]) & 0x3f;
    }
    else if (width == 3) {

      // U+0800 -> U+FFFF
      *unicode = (((uint8_t) character[0]) & 0xf) << 12;
      *unicode |= (((uint8_t) character[1]) & 0x3f) << 6;
      *unicode |= ((uint8_t) character[2]) & 0x3f;
    }
    else if (width == 4) {

      // U+10000 -> U+10FFFF
      *unicode = (((uint8_t) character[0]) & 0x7) << 18;
      *unicode |= (((uint8_t) character[1]) & 0x3f) << 12;
      *unicode |= (((uint8_t) character[2]) & 0x3f) << 6;
      *unicode |= ((uint8_t) character[3]) & 0x3f;
    }

    return F_none;
  }
#endif // _di_f_utf_unicode_to_

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

#ifdef __cplusplus
} // extern "C"
#endif

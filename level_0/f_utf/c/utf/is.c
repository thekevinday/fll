#include "../utf.h"
#include "../private-utf.h"
#include "../private-utf_alphabetic.h"
#include "../private-utf_combining.h"
#include "../private-utf_control.h"
#include "../private-utf_digit.h"
#include "../private-utf_emoji.h"
#include "../private-utf_numeric.h"
#include "../private-utf_phonetic.h"
#include "../private-utf_private.h"
#include "../private-utf_punctuation.h"
#include "../private-utf_subscript.h"
#include "../private-utf_superscript.h"
#include "../private-utf_symbol.h"
#include "../private-utf_unassigned.h"
#include "../private-utf_valid.h"
#include "../private-utf_whitespace.h"
#include "../private-utf_wide.h"
#include "../private-utf_word.h"
#include "../private-utf_zero_width.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_is_
  f_status_t f_utf_is(const f_string_t sequence) {

    return macro_f_utf_byte_width_is(*sequence);
  }
#endif // _di_f_utf_is_

#ifndef _di_f_utf_is_alphabetic_
  f_status_t f_utf_is_alphabetic(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_alphabetic(utf);
    }

    if (isalpha(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_alphabetic_

#ifndef _di_f_utf_is_alphabetic_digit_
  f_status_t f_utf_is_alphabetic_digit(const f_string_t sequence, const f_number_unsigned_t width_max, uint64_t * const value) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_alphabetic_digit(utf, value);
    }

    if (isalpha(*sequence)) return F_true;

    return private_f_utf_character_is_digit_for_ascii(*sequence, value);
  }
#endif // _di_f_utf_is_alphabetic_digit_

#ifndef _di_f_utf_is_alphabetic_numeric_
  f_status_t f_utf_is_alphabetic_numeric(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_alphabetic_numeric(utf);
    }

    if (isalnum(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_alphabetic_numeric_

#ifndef _di_f_utf_is_ascii_
  f_status_t f_utf_is_ascii(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_is_ascii_

#ifndef _di_f_utf_is_combining_
  f_status_t f_utf_is_combining(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_combining(utf);
    }

    // There are no ASCII combining characters.
    return F_false;
  }
#endif // _di_f_utf_is_combining_

#ifndef _di_f_utf_is_control_
  f_status_t f_utf_is_control(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control(utf);
    }

    if (iscntrl(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_control_

#ifndef _di_f_utf_is_control_code_
  f_status_t f_utf_is_control_code(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control_code(utf);
    }

    if (iscntrl(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_control_code_

#ifndef _di_f_utf_is_control_format_
  f_status_t f_utf_is_control_format(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control_format(utf);
    }

    // There are no ASCII control formats.
    return F_false;
  }
#endif // _di_f_utf_is_control_format_

#ifndef _di_f_utf_is_control_picture_
  f_status_t f_utf_is_control_picture(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);
      if (macro_f_utf_byte_width_is(*sequence) != 3) return F_false;

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_control_picture(utf);
    }

    // There are no ASCII control pictures.
    return F_false;
  }
#endif // _di_f_utf_is_control_picture_

#ifndef _di_f_utf_is_digit_
  f_status_t f_utf_is_digit(const f_string_t sequence, const f_number_unsigned_t width_max, uint64_t * const value) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_digit(utf, value);
    }

    return private_f_utf_character_is_digit_for_ascii(*sequence, value);
  }
#endif // _di_f_utf_is_digit_

#ifndef _di_f_utf_is_emoji_
  f_status_t f_utf_is_emoji(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_emoji(utf);
    }

    return F_false;
  }
#endif // _di_f_utf_is_emoji_

#ifndef _di_f_utf_is_fragment_
  f_status_t f_utf_is_fragment(const f_string_t sequence) {

    if (macro_f_utf_byte_width_is(*sequence) == 1) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_fragment_

#ifndef _di_f_utf_is_graph_
  f_status_t f_utf_is_graph(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      if (private_f_utf_character_is_control(utf)) {
        return F_false;
      }

      if (private_f_utf_character_is_whitespace(utf, F_true)) {
        return F_false;
      }

      // Zero-width characters are be treated as a non-graph.
      if (private_f_utf_character_is_zero_width(utf)) {
        return F_false;
      }

      return F_true;
    }

    if (isgraph(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_graph_

#ifndef _di_f_utf_is_numeric_
  f_status_t f_utf_is_numeric(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_numeric(utf);
    }

    if (isdigit(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_numeric_

#ifndef _di_f_utf_is_phonetic_
  f_status_t f_utf_is_phonetic(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_phonetic(utf);
    }

    // There are no ASCII phonetic characters.
    return F_false;
  }
#endif // _di_f_utf_is_phonetic_

#ifndef _di_f_utf_is_private_
  f_status_t f_utf_is_private(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_private(utf);
    }

    // There are no ASCII private characters.
    return F_false;
  }
#endif // _di_f_utf_is_private_

#ifndef _di_f_utf_is_punctuation_
  f_status_t f_utf_is_punctuation(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_punctuation(utf);
    }

    // ASCII: U+0021 '!' to U+0023 '#'.
    if (sequence[0] > 0x20 && sequence[0] < 0x24) {
      return F_true;
    }

    // ASCII: U+0025 '%' to U+002A '*'.
    if (sequence[0] > 0x24 && sequence[0] < 0x2b) {
      return F_true;
    }

    // ASCII: U+002C ',' to U+002F '/'.
    if (sequence[0] > 0x2b && sequence[0] < 0x30) {
      return F_true;
    }

    // ASCII: U+003A ':', U+003B ';', U+003F '?', or U+0040 '@'.
    if (sequence[0] == 0x3a || sequence[0] == 0x3b || sequence[0] == 0x3f || sequence[0] == 0x40) {
      return F_true;
    }

    // ASCII: U+005B '[' to U+005D ']'.
    if (sequence[0] > 0x5a && sequence[0] < 0x5e) {
      return F_true;
    }

    // ASCII: U+005F '_', U+007B '{', or U+007D '}'.
    if (sequence[0] == 0x5f || sequence[0] == 0x7b || sequence[0] == 0x7d) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_punctuation_

#ifndef _di_f_utf_is_subscript_
  f_status_t f_utf_is_subscript(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_subscript(utf);
    }

    return F_false;
  }
#endif // _di_f_utf_is_subscript_

#ifndef _di_f_utf_is_superscript_
  f_status_t f_utf_is_superscript(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_superscript(utf);
    }

    return F_false;
  }
#endif // _di_f_utf_is_superscript_

#ifndef _di_f_utf_is_symbol_
  f_status_t f_utf_is_symbol(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_symbol(utf);
    }

    // ASCII: U+0024 ('$') or U+002B ('+').
    if (sequence[0] == 0x24 || sequence[0] == 0x2b) {
      return F_true;
    }

    // ASCII: U+003C ('<') to U+003E ('>').
    if (sequence[0] >= 0x3c && sequence[0] <= 0x3e) {
      return F_true;
    }

    // ASCII: U+005E ('^'), U+0060 ('`'), U+007C ('|'), or U+007E ('~').
    if (sequence[0] == 0x5e || sequence[0] == 0x60 || sequence[0] == 0x7c || sequence[0] == 0x7e) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_symbol_

#ifndef _di_f_utf_is_unassigned_
  f_status_t f_utf_is_unassigned(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_unassigned(utf);
    }

    // ASCII are never unassigned.
    return F_false;
  }
#endif // _di_f_utf_is_unassigned_

#ifndef _di_f_utf_is_valid_
  f_status_t f_utf_is_valid(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_valid(utf);
    }

    // ASCII are valid.
    return F_true;
  }
#endif // _di_f_utf_is_valid_

#ifndef _di_f_utf_is_whitespace_
  f_status_t f_utf_is_whitespace(const f_string_t sequence, const f_number_unsigned_t width_max, const bool strict) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace(utf, strict);
    }

    if (isspace(*sequence)) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_whitespace_

#ifndef _di_f_utf_is_whitespace_modifier_
  f_status_t f_utf_is_whitespace_modifier(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace_modifier(utf);
    }

    // There are no ASCII whitespace modifiers.
    return F_false;
  }
#endif // _di_f_utf_is_whitespace_modifier_

#ifndef _di_f_utf_is_whitespace_other_
  f_status_t f_utf_is_whitespace_other(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace_other(utf);
    }

    // There are no ASCII whitespace other.
    return F_false;
  }
#endif // _di_f_utf_is_whitespace_other_

#ifndef _di_f_utf_is_whitespace_zero_width_
  f_status_t f_utf_is_whitespace_zero_width(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_whitespace_zero_width(utf);
    }

    // There are no ASCII whitespace zero-width.
    return F_false;
  }
#endif // _di_f_utf_is_whitespace_zero_width_

#ifndef _di_f_utf_is_wide_
  f_status_t f_utf_is_wide(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_wide(utf);
    }

    // There are no wide ASCII characters.
    return F_false;
  }
#endif // _di_f_utf_is_wide_

#ifndef _di_f_utf_is_word_
  f_status_t f_utf_is_word(const f_string_t sequence, const f_number_unsigned_t width_max, const bool strict) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word(utf, strict);
    }

    if (isalnum(*sequence) || *sequence == f_string_ascii_underscore_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_word_

#ifndef _di_f_utf_is_word_dash_
  f_status_t f_utf_is_word_dash(const f_string_t sequence, const f_number_unsigned_t width_max, const bool strict) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word_dash(utf, strict);
    }

    if (isalnum(*sequence) || *sequence == f_string_ascii_underscore_s.string[0] || *sequence == f_string_ascii_minus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_word_dash_

#ifndef _di_f_utf_is_word_dash_plus_
  f_status_t f_utf_is_word_dash_plus(const f_string_t sequence, const f_number_unsigned_t width_max, const bool strict) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      return private_f_utf_character_is_word_dash_plus(utf, strict);
    }

    if (isalnum(*sequence) || *sequence == f_string_ascii_underscore_s.string[0] || *sequence == f_string_ascii_minus_s.string[0] || *sequence == f_string_ascii_plus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_is_word_dash_plus_

#ifndef _di_f_utf_is_zero_width_
  f_status_t f_utf_is_zero_width(const f_string_t sequence, const f_number_unsigned_t width_max) {

    if (width_max < 1) return F_data_not;

    if (macro_f_utf_byte_width_is(*sequence)) {
      if (macro_f_utf_byte_width_is(*sequence) > width_max) return F_status_set_error(F_complete_not_utf);
      if (macro_f_utf_byte_width_is(*sequence) == 1) return F_status_set_error(F_utf_fragment);

      f_utf_char_t utf = 0;

      {
        const f_status_t status = private_f_utf_char_to_character(sequence, width_max, &utf);
        if (F_status_is_error(status)) return status;
      }

      // Control and combining characters are zero-width.
      if (private_f_utf_character_is_control(utf)) return F_true;
      if (private_f_utf_character_is_combining(utf)) return F_true;

      return private_f_utf_character_is_zero_width(utf);
    }

    // These control characters are considered zero-width spaces.
    if (*sequence >= 0x00 && *sequence < 0x09) return F_true;
    if (*sequence > 0x0b && *sequence < 0x20) return F_true;
    if (*sequence == 0x7f) return F_true;

    return F_false;
  }
#endif // _di_f_utf_is_zero_width_

#ifdef __cplusplus
} // extern "C"
#endif

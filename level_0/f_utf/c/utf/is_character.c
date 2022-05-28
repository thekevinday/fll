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
#include "../private-utf_surrogate.h"
#include "../private-utf_symbol.h"
#include "../private-utf_valid.h"
#include "../private-utf_whitespace.h"
#include "../private-utf_wide.h"
#include "../private-utf_word.h"
#include "../private-utf_zero_width.h"
#include "private-is_unassigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_character_is_
  f_status_t f_utf_character_is(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_utf_fragment;
      }

      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_

#ifndef _di_f_utf_character_is_alphabetic_
  f_status_t f_utf_character_is_alpha(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alphabetic(character);
    }

    if (isalpha(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alphabetic_

#ifndef _di_f_utf_character_is_alphabetic_digit_
  f_status_t f_utf_character_is_alpha_digit(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alphabetic_digit(character);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alphabetic_digit_

#ifndef _di_f_utf_character_is_alphabetic_numeric_
  f_status_t f_utf_character_is_alphabetic_numeric(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alphabetic_numeric(character);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alphabetic_numeric_

#ifndef _di_f_utf_character_is_ascii_
  f_status_t f_utf_character_is_ascii(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_ascii_

#ifndef _di_f_utf_character_is_combining_
  f_status_t f_utf_character_is_combining(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_combining(character);
    }

    // There are no combining characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_combining_

#ifndef _di_f_utf_character_is_control_
  f_status_t f_utf_character_is_control(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control(character);
    }

    if (iscntrl(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_control_

#ifndef _di_f_utf_character_is_control_code_
  f_status_t f_utf_character_is_control_code(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_code(character);
    }

    if (iscntrl(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_control_code_

#ifndef _di_f_utf_character_is_control_picture_
  f_status_t character_is_control_format(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_format(character);
    }

    // There are no control format characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_control_format_

#ifndef _di_f_utf_character_is_control_picture_
  f_status_t f_utf_character_is_control_picture(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_picture(character);
    }

    // There are no control picture characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_control_picture_

#ifndef _di_f_utf_character_is_digit_
  f_status_t f_utf_character_is_digit(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_digit(character);
    }

    if (isdigit(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_digit_

#ifndef _di_f_utf_character_is_emoji_
  f_status_t f_utf_character_is_emoji(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_emoji(character);
    }

    if (isdigit(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_emoji_

#ifndef _di_f_utf_character_is_fragment_
  f_status_t f_utf_character_is_fragment(const f_utf_char_t character) {

    return macro_f_utf_char_t_width_is(character) == 1;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_status_t f_utf_character_is_graph(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
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

    if (isgraph(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_graph_

#ifndef _di_f_utf_character_is_numeric_
  f_status_t f_utf_character_is_numeric(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_numeric(character);
    }

    if (isdigit(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_numeric_

#ifndef _di_f_utf_character_is_phonetic_
  f_status_t f_utf_character_is_phonetic(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_phonetic(character);
    }

    // There are no ASCII phonetic characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_private_
  f_status_t f_utf_character_is_private(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_private(character);
    }

    // There are no ASCII private characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_punctuation_
  f_status_t f_utf_character_is_punctuation(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_punctuation(character);
    }

    // ASCII: U+0021 '!' to U+0023 '#'.
    if (character > 0x20000000 && character < 0x24000000) {
      return F_true;
    }

    // ASCII: U+0025 '%' to U+002A '*'.
    if (character > 0x24000000 && character < 0x2b000000) {
      return F_true;
    }

    // ASCII: U+002C ',' to U+002F '/'.
    if (character > 0x2b000000 && character < 0x30000000) {
      return F_true;
    }

    // ASCII: U+003A ':', U+003B ';', U+003F '?', or U+0040 '@'.
    if (character == 0x3a000000 || character == 0x3b000000 || character == 0x3f000000 || character == 0x40000000) {
      return F_true;
    }

    // ASCII: U+005B '[' to U+005D ']'.
    if (character > 0x5a000000 && character < 0x5e000000) {
      return F_true;
    }

    // ASCII: U+005F '_', U+007B '{', or U+007D '}'.
    if (character == 0x5f000000 || character == 0x7b000000 || character == 0x7d000000) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_punctuation_

#ifndef _di_f_utf_character_is_subscript_
  f_status_t f_utf_character_is_subscript(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_subscript(character);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_subscript_

#ifndef _di_f_utf_character_is_superscript_
  f_status_t f_utf_character_is_superscript(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_superscript(character);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_superscript_

#ifndef _di_f_utf_character_is_symbol_
  f_status_t f_utf_character_is_symbol(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
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
  f_status_t f_utf_character_is_unassigned(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_unassigned(character);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_unassigned_

#ifndef _di_f_utf_character_is_valid_
  f_status_t f_utf_character_is_valid(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_valid(character);
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_valid_

#ifndef _di_f_utf_character_is_whitespace_
  f_status_t f_utf_character_is_whitespace(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace(character);
    }

    if (isspace(macro_f_utf_char_t_to_char_1(character))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_

#ifndef _di_f_utf_character_is_whitespace_modifier_
  f_status_t f_utf_character_is_whitespace_modifier(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_modifier(character);
    }

    // There are no ASCII whitespace modifiers.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_modifier_

#ifndef _di_f_utf_character_is_whitespace_other_
  f_status_t f_utf_character_is_whitespace_other(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_other(character);
    }

    // There are no ASCII whitespace other.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_other_

#ifndef _di_f_utf_character_is_wide_
  f_status_t f_utf_character_is_wide(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_wide(character);
    }

    // There are no wide ASCII characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_wide_

#ifndef _di_f_utf_character_is_word_
  f_status_t f_utf_character_is_word(const f_utf_char_t character, const bool strict) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word(character, strict);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(character)) || character == f_string_ascii_underscore_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_

#ifndef _di_f_utf_character_is_word_dash_
  f_status_t f_utf_character_is_word_dash(const f_utf_char_t character, const bool strict) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word_dash(character, strict);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(character)) || character == f_string_ascii_underscore_s.string[0] || character == f_string_ascii_minus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_dash_

#ifndef _di_f_utf_character_is_word_dash_plus_
  f_status_t f_utf_character_is_word_dash_plus(const f_utf_char_t character, const bool strict) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word_dash_plus(character, strict);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(character)) || character == f_string_ascii_underscore_s.string[0] || character == f_string_ascii_minus_s.string[0] || character == f_string_ascii_plus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_dash_plus_

#ifndef _di_f_utf_character_is_zero_width_
  f_status_t f_utf_character_is_zero_width(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character)) {
      if (macro_f_utf_char_t_width_is(character) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_zero_width(character);
    }

    const uint8_t ascii = macro_f_utf_char_t_to_char_1(character);

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

#ifdef __cplusplus
} // extern "C"
#endif

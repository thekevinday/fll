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

#ifndef _di_f_utf_character_is_
  f_status_t f_utf_character_is(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_utf_fragment;
      }

      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_

#ifndef _di_f_utf_character_is_alphabetic_
  f_status_t f_utf_character_is_alphabetic(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alphabetic(sequence);
    }

    if (isalpha(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alphabetic_

#ifndef _di_f_utf_character_is_alphabetic_digit_
  f_status_t f_utf_character_is_alphabetic_digit(const f_utf_char_t sequence, uint64_t * const value) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alphabetic_digit(sequence, value);
    }

    if (isalpha(macro_f_utf_char_t_to_char_1(sequence))) return F_true;

    return private_f_utf_character_is_digit_for_ascii(macro_f_utf_char_t_to_char_1(sequence), value);
  }
#endif // _di_f_utf_character_is_alphabetic_digit_

#ifndef _di_f_utf_character_is_alphabetic_numeric_
  f_status_t f_utf_character_is_alphabetic_numeric(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_alphabetic_numeric(sequence);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_alphabetic_numeric_

#ifndef _di_f_utf_character_is_ascii_
  f_status_t f_utf_character_is_ascii(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_f_utf_character_is_ascii_

#ifndef _di_f_utf_character_is_combining_
  f_status_t f_utf_character_is_combining(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_combining(sequence);
    }

    // There are no combining characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_combining_

#ifndef _di_f_utf_character_is_control_
  f_status_t f_utf_character_is_control(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control(sequence);
    }

    if (iscntrl(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_control_

#ifndef _di_f_utf_character_is_control_code_
  f_status_t f_utf_character_is_control_code(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_code(sequence);
    }

    if (iscntrl(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_control_code_

#ifndef _di_f_utf_character_is_control_format_
  f_status_t f_utf_character_is_control_format(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_format(sequence);
    }

    // There are no ASCII control formats.
    return F_false;
  }
#endif // _di_f_utf_character_is_control_format_

#ifndef _di_f_utf_character_is_control_picture_
  f_status_t f_utf_character_is_control_picture(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_control_picture(sequence);
    }

    // There are no control picture characters in ASCII.
    return F_false;
  }
#endif // _di_f_utf_character_is_control_picture_

#ifndef _di_f_utf_character_is_digit_
  f_status_t f_utf_character_is_digit(const f_utf_char_t sequence, uint64_t * const value) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_digit(sequence, value);
    }

    return private_f_utf_character_is_digit_for_ascii(macro_f_utf_char_t_to_char_1(sequence), value);
  }
#endif // _di_f_utf_character_is_digit_

#ifndef _di_f_utf_character_is_emoji_
  f_status_t f_utf_character_is_emoji(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_emoji(sequence);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_emoji_

#ifndef _di_f_utf_character_is_fragment_
  f_status_t f_utf_character_is_fragment(const f_utf_char_t sequence) {

    return macro_f_utf_char_t_width_is(sequence) == 1;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_status_t f_utf_character_is_graph(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (private_f_utf_character_is_control(sequence)) {
        return F_false;
      }

      if (private_f_utf_character_is_whitespace(sequence, F_true)) {
        return F_false;
      }

      if (private_f_utf_character_is_zero_width(sequence)) {
        return F_false;
      }

      return F_true;
    }

    if (isgraph(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_graph_

#ifndef _di_f_utf_character_is_numeric_
  f_status_t f_utf_character_is_numeric(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_numeric(sequence);
    }

    if (isdigit(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_numeric_

#ifndef _di_f_utf_character_is_phonetic_
  f_status_t f_utf_character_is_phonetic(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_phonetic(sequence);
    }

    // There are no ASCII phonetic characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_private_
  f_status_t f_utf_character_is_private(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_private(sequence);
    }

    // There are no ASCII private characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_phonetic_

#ifndef _di_f_utf_character_is_punctuation_
  f_status_t f_utf_character_is_punctuation(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_punctuation(sequence);
    }

    // ASCII: U+0021 '!' to U+0023 '#'.
    if (sequence > 0x20000000 && sequence < 0x24000000) {
      return F_true;
    }

    // ASCII: U+0025 '%' to U+002A '*'.
    if (sequence > 0x24000000 && sequence < 0x2b000000) {
      return F_true;
    }

    // ASCII: U+002C ',' to U+002F '/'.
    if (sequence > 0x2b000000 && sequence < 0x30000000) {
      return F_true;
    }

    // ASCII: U+003A ':', U+003B ';', U+003F '?', or U+0040 '@'.
    if (sequence == 0x3a000000 || sequence == 0x3b000000 || sequence == 0x3f000000 || sequence == 0x40000000) {
      return F_true;
    }

    // ASCII: U+005B '[' to U+005D ']'.
    if (sequence > 0x5a000000 && sequence < 0x5e000000) {
      return F_true;
    }

    // ASCII: U+005F '_', U+007B '{', or U+007D '}'.
    if (sequence == 0x5f000000 || sequence == 0x7b000000 || sequence == 0x7d000000) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_punctuation_

#ifndef _di_f_utf_character_is_subscript_
  f_status_t f_utf_character_is_subscript(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_subscript(sequence);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_subscript_

#ifndef _di_f_utf_character_is_superscript_
  f_status_t f_utf_character_is_superscript(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_superscript(sequence);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_superscript_

#ifndef _di_f_utf_character_is_symbol_
  f_status_t f_utf_character_is_symbol(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_symbol(sequence);
    }

    // ASCII: U+0024 ('$') or U+002B ('+').
    if (sequence == 0x24000000 || sequence == 0x2b000000) {
      return F_true;
    }

    // ASCII: U+003C ('<') to U+003E ('>').
    if (sequence >= 0x3c000000 && sequence <= 0x3e000000) {
      return F_true;
    }

    // ASCII: U+005E ('^'), U+0060 ('`'), U+007C ('|'), or U+007E ('~').
    if (sequence == 0x5e000000 || sequence == 0x60000000 || sequence == 0x7c000000 || sequence == 0x7e000000) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_symbol_

#ifndef _di_f_utf_character_is_unassigned_
  f_status_t f_utf_character_is_unassigned(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_unassigned(sequence);
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_unassigned_

#ifndef _di_f_utf_character_is_valid_
  f_status_t f_utf_character_is_valid(const f_utf_char_t sequence) {

    // The is valid check handles fragment checks and other validity checks.
    return private_f_utf_character_is_valid(sequence);
  }
#endif // _di_f_utf_character_is_valid_

#ifndef _di_f_utf_character_is_whitespace_
  f_status_t f_utf_character_is_whitespace(const f_utf_char_t sequence, const bool strict) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace(sequence, strict);
    }

    if (isspace(macro_f_utf_char_t_to_char_1(sequence))) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_

#ifndef _di_f_utf_character_is_whitespace_modifier_
  f_status_t f_utf_character_is_whitespace_modifier(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_modifier(sequence);
    }

    // There are no ASCII whitespace modifiers.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_modifier_

#ifndef _di_f_utf_character_is_whitespace_other_
  f_status_t f_utf_character_is_whitespace_other(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_other(sequence);
    }

    // There are no ASCII whitespace other.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_other_

#ifndef _di_f_utf_character_is_whitespace_zero_width_
  f_status_t f_utf_character_is_whitespace_zero_width(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_whitespace_zero_width(sequence);
    }

    // There are no ASCII whitespace zero-width.
    return F_false;
  }
#endif // _di_f_utf_character_is_whitespace_zero_width_

#ifndef _di_f_utf_character_is_wide_
  f_status_t f_utf_character_is_wide(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_wide(sequence);
    }

    // There are no wide ASCII characters.
    return F_false;
  }
#endif // _di_f_utf_character_is_wide_

#ifndef _di_f_utf_character_is_word_
  f_status_t f_utf_character_is_word(const f_utf_char_t sequence, const bool strict) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word(sequence, strict);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(sequence)) || macro_f_utf_char_t_to_char_1(sequence) == f_string_ascii_underscore_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_

#ifndef _di_f_utf_character_is_word_dash_
  f_status_t f_utf_character_is_word_dash(const f_utf_char_t sequence, const bool strict) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word_dash(sequence, strict);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(sequence)) || macro_f_utf_char_t_to_char_1(sequence) == f_string_ascii_underscore_s.string[0] || macro_f_utf_char_t_to_char_1(sequence) == f_string_ascii_minus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_dash_

#ifndef _di_f_utf_character_is_word_dash_plus_
  f_status_t f_utf_character_is_word_dash_plus(const f_utf_char_t sequence, const bool strict) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_word_dash_plus(sequence, strict);
    }

    if (isalnum(macro_f_utf_char_t_to_char_1(sequence)) || macro_f_utf_char_t_to_char_1(sequence) == f_string_ascii_underscore_s.string[0] || macro_f_utf_char_t_to_char_1(sequence) == f_string_ascii_minus_s.string[0] || macro_f_utf_char_t_to_char_1(sequence) == f_string_ascii_plus_s.string[0]) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_utf_character_is_word_dash_plus_

#ifndef _di_f_utf_character_is_zero_width_
  f_status_t f_utf_character_is_zero_width(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence)) {
      if (macro_f_utf_char_t_width_is(sequence) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      return private_f_utf_character_is_zero_width(sequence);
    }

    const uint8_t ascii = macro_f_utf_char_t_to_char_1(sequence);

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

#include "utf.h"
#include "private-utf.h"
#include "private-utf_valid.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_surrogate_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)
  f_status_t private_f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_char_t *character_utf) {

    if (!macro_f_utf_byte_width_is(*character)) {
      *character_utf = macro_f_utf_char_t_from_char_1(character[0]);

      return F_none;
    }

    if (macro_f_utf_byte_width_is(*character) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    if (macro_f_utf_byte_width_is(*character) > width_max) {
      return F_status_set_error(F_complete_not_utf);
    }

    *character_utf = macro_f_utf_char_t_from_char_1(character[0]);

    if (macro_f_utf_byte_width_is(*character) < 2) {
      return F_none;
    }

    *character_utf |= macro_f_utf_char_t_from_char_2(character[1]);

    if (macro_f_utf_byte_width_is(*character) == 2) {
      return F_none;
    }

    *character_utf |= macro_f_utf_char_t_from_char_3(character[2]);

    if (macro_f_utf_byte_width_is(*character) == 3) {
      return F_none;
    }

    *character_utf |= macro_f_utf_char_t_from_char_4(character[3]);

    return F_none;
  }
#endif // !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_surrogate_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)

#if !defined(_di_f_utf_unicode_to_) || !defined(_di_f_utf_character_unicode_to_)
  f_status_t private_f_utf_character_unicode_to(const f_utf_char_t character, uint32_t *unicode) {

    if (macro_f_utf_char_t_width_is(character) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    if (private_f_utf_character_is_valid(character) == F_false) {
      return F_status_set_error(F_utf_not);
    }

    // U+0000 -> U+007F (ASCII).
    if (macro_f_utf_char_t_width(character) == 1) {
      *unicode = macro_f_utf_char_t_to_char_1(character) & 0x7f;
    }

    // U+0080 -> U+07FF.
    else if (macro_f_utf_char_t_width(character) == 2) {
      *unicode = (macro_f_utf_char_t_to_char_1(character) & 0x1f) << 6;
      *unicode |= macro_f_utf_char_t_to_char_2(character) & 0x3f;
    }

    // U+0800 -> U+FFFF.
    else if (macro_f_utf_char_t_width(character) == 3) {
      *unicode = (macro_f_utf_char_t_to_char_1(character) & 0xf) << 12;
      *unicode |= (macro_f_utf_char_t_to_char_2(character) & 0x3f) << 6;
      *unicode |= macro_f_utf_char_t_to_char_3(character) & 0x3f;
    }

    // U+10000 -> U+10FFFF.
    else if (macro_f_utf_char_t_width(character) == 4) {
      *unicode = (macro_f_utf_char_t_to_char_1(character) & 0x7) << 18;
      *unicode |= (macro_f_utf_char_t_to_char_2(character) & 0x3f) << 12;
      *unicode |= (macro_f_utf_char_t_to_char_2(character) & 0x3f) << 6;
      *unicode |= macro_f_utf_char_t_to_char_4(character) & 0x3f;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_unicode_to_) || !defined(_di_f_utf_character_unicode_to_)

#ifdef __cplusplus
} // extern "C"
#endif

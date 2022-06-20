#include "utf.h"
#include "private-utf.h"
#include "private-utf_alphabetic.h"
#include "private-utf_combining.h"
#include "private-utf_control.h"
#include "private-utf_decimal.h"
#include "private-utf_digit.h"
#include "private-utf_numeric.h"
#include "private-utf_phonetic.h"
#include "private-utf_punctuation.h"
#include "private-utf_symbol.h"
#include "private-utf_whitespace.h"
#include "private-utf_zero_width.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_)
  f_status_t private_f_utf_character_is_alphabetic(const f_utf_char_t sequence) {

    if (private_f_utf_character_is_zero_width(sequence)) {
      return F_false;
    }

    // The is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_combining(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_numeric(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(sequence)) {
      return F_false;
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_)

#if !defined(_di_f_utf_character_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_decimal_)
  f_status_t private_f_utf_character_is_alphabetic_decimal(const f_utf_char_t sequence, uint32_t * const value) {

    if (private_f_utf_character_is_decimal(sequence, F_true, value)) {
      return F_true;
    }

    if (private_f_utf_character_is_zero_width(sequence)) {
      return F_false;
    }

    // The is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_numeric(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(sequence)) {
      return F_false;
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_decimal_)

#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_digit_)
  f_status_t private_f_utf_character_is_alphabetic_digit(const f_utf_char_t sequence) {

    if (private_f_utf_character_is_digit(sequence)) {
      return F_true;
    }

    if (private_f_utf_character_is_zero_width(sequence)) {
      return F_false;
    }

    // The is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_numeric(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(sequence)) {
      return F_false;
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_digit_)

#if !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_is_alphabetic_numeric_)
  f_status_t private_f_utf_character_is_alphabetic_numeric(const f_utf_char_t sequence) {

    if (private_f_utf_character_is_numeric(sequence)) {
      return F_true;
    }

    if (private_f_utf_character_is_zero_width(sequence)) {
      return F_false;
    }

    // The is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(sequence)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(sequence)) {
      return F_false;
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_is_alphabetic_numeric_)

#ifdef __cplusplus
} // extern "C"
#endif

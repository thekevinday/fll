#include "utf.h"
#include "private-utf.h"
#include "private-utf_zero_width.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_graph_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_)
  f_status_t private_f_utf_character_is_zero_width(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 3) {
      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // General Punctuation: U+2028 to U+2029.
        if (sequence >= 0xf090b4a3 && sequence <= 0xf090b4a7) {
          return F_true;
        }

        // General Punctuation: U+2066 to U+2069.
        if (sequence >= 0xe281a600 && sequence <= 0xe281a900) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {
        if (macro_f_utf_char_t_to_char_2(sequence) == 0xbf) {

          // Unassigned and reserved for future use: U+FFF0 to U+FFF8 (these are assumed to be zero-width).
          if (sequence >= 0xefbfb000 && sequence <= 0xefbfb900) {
            return F_true;
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_graph_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif

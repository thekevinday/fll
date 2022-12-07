#include "utf.h"
#include "private-utf.h"
#include "private-utf_digit.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Given the value, this will conditionally convert the range into an appropriate base-10 integer.
   *
   * This does not handle non-decimal values (non-base-10).
   *
   * @param sequence
   *   The character sequence to process.
   * @param start
   *   An inclusive start range.
   *   The base-10 stop range calculated from this.
   * @param value
   *   The value to update, if non-NULL.
   *
   * @return
   *   F_true for valid digit in the requested range.
   *   F_false, otherwise.
   */
  static inline f_status_t private_inline_f_utf_character_handle_digit(const f_utf_char_t sequence, const f_utf_char_t start, uint64_t * const value) {

    if (value) {
      f_char_t ascii = 0x30;

      if (macro_f_utf_char_t_width(sequence) == 2) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 3) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 4) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
      }

      return private_f_utf_character_is_digit_for_ascii(ascii, value);
    }

    return F_true;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Given the value, this will conditionally convert the range into an appropriate base-10 integer.
   *
   * This does not handle non-decimal values (non-base-10).
   *
   * This applies an offset with the intent of being used for producing values greater than 9 (such as 10 through 19).
   *
   * @param sequence
   *   The character sequence to process.
   * @param start
   *   An inclusive start range.
   *   The base-10 stop range calculated from this.
   * @param offset
   *   An offset needed to add to the calculated base-10 value.
   *   If value is 9 and offset is 10 then the a value of 19 is returned.
   * @param value
   *   The value to update, if non-NULL.
   *
   * @return
   *   F_true for valid digit in the requested range.
   *   F_false, otherwise.
   */
  static inline f_status_t private_inline_f_utf_character_handle_digit_offset(const f_utf_char_t sequence, const f_utf_char_t start, const uint8_t offset, uint64_t * const value) {

    if (value) {
      f_char_t ascii = 0x30;

      if (macro_f_utf_char_t_width(sequence) == 2) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 3) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 4) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
      }

      if (private_f_utf_character_is_digit_for_ascii(ascii, value) == F_true) {
        *value += offset;

        return F_true;
      }

      return F_false;
    }

    return F_true;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Given the value, this will conditionally convert the range into an appropriate base-10 integer from 1 to 9.
   *
   * This does not handle non-decimal values (non-base-10).
   *
   * @param sequence
   *   The character sequence to process.
   * @param start
   *   An inclusive start range.
   *   The base-10 stop range calculated from this.
   * @param value
   *   The value to update, if non-NULL.
   *
   * @return
   *   F_true for valid digit in the requested range.
   *   F_false, otherwise.
   */
  static inline f_status_t private_inline_f_utf_character_handle_digit_from_one(const f_utf_char_t sequence, const f_utf_char_t start, uint64_t * const value) {

    if (value) {
      f_char_t ascii = 0x31;

      if (macro_f_utf_char_t_width(sequence) == 2) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 3) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 4) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
      }

      return private_f_utf_character_is_digit_for_ascii(ascii, value);
    }

    return F_true;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Given the value, this will conditionally convert the range into an appropriate base-10 integer from 2 to 9.
   *
   * This does not handle non-decimal values (non-base-10).
   *
   * @param sequence
   *   The character sequence to process.
   * @param start
   *   An inclusive start range.
   *   The base-10 stop range calculated from this.
   * @param value
   *   The value to update, if non-NULL.
   *
   * @return
   *   F_true for valid digit in the requested range.
   *   F_false, otherwise.
   */
  static inline f_status_t private_inline_f_utf_character_handle_digit_from_two(const f_utf_char_t sequence, const f_utf_char_t start, uint64_t * const value) {

    if (value) {
      f_char_t ascii = 0x32;

      if (macro_f_utf_char_t_width(sequence) == 2) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 3) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 4) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
      }

      return private_f_utf_character_is_digit_for_ascii(ascii, value);
    }

    return F_true;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Given the value, this will conditionally convert the range into an appropriate base-10 integer from 3 to 9.
   *
   * This does not handle non-decimal values (non-base-10).
   *
   * @param sequence
   *   The character sequence to process.
   * @param start
   *   An inclusive start range.
   *   The base-10 stop range calculated from this.
   * @param value
   *   The value to update, if non-NULL.
   *
   * @return
   *   F_true for valid digit in the requested range.
   *   F_false, otherwise.
   */
  static inline f_status_t private_inline_f_utf_character_handle_digit_from_three(const f_utf_char_t sequence, const f_utf_char_t start, uint64_t * const value) {

    if (value) {
      f_char_t ascii = 0x33;

      if (macro_f_utf_char_t_width(sequence) == 2) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 3) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 4) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
      }

      return private_f_utf_character_is_digit_for_ascii(ascii, value);
    }

    return F_true;
  }

  /**
   * Inline helper function to reduce amount of code typed.
   *
   * Given the value, this will conditionally convert the range into an appropriate base-10 integer from 4 to 9.
   *
   * This does not handle non-decimal values (non-base-10).
   *
   * @param sequence
   *   The character sequence to process.
   * @param start
   *   An inclusive start range.
   *   The base-10 stop range calculated from this.
   * @param value
   *   The value to update, if non-NULL.
   *
   * @return
   *   F_true for valid digit in the requested range.
   *   F_false, otherwise.
   */
  static inline f_status_t private_inline_f_utf_character_handle_digit_from_four(const f_utf_char_t sequence, const f_utf_char_t start, uint64_t * const value) {

    if (value) {
      f_char_t ascii = 0x34;

      if (macro_f_utf_char_t_width(sequence) == 2) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 3) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
      }
      else if (macro_f_utf_char_t_width(sequence) == 4) {
        ascii += (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
      }

      return private_f_utf_character_is_digit_for_ascii(ascii, value);
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_digit(const f_utf_char_t sequence, uint64_t * const value) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Arabic: U+0660 to U+0669.
      if (sequence >= 0xd9a00000 && sequence <= 0xd9a90000) {
        return private_inline_f_utf_character_handle_digit(sequence, 0xd9a00000, value);
      }

      // Extended Arabic: U+06F0 to U+06F9.
      if (sequence >= 0xdbb00000 && sequence <= 0xdbb90000) {
        return private_inline_f_utf_character_handle_digit(sequence, 0xdbb00000, value);
      }

      // NKo: U+07C0 to U+07C9.
      if (sequence >= 0xdf800000 && sequence <= 0xdf890000) {
        return private_inline_f_utf_character_handle_digit(sequence, 0xdf800000, value);
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Devanagari: U+0966 to U+096F.
        if (sequence >= 0xe0a5a600 && sequence <= 0xe0a5af00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0a5a600, value);
        }

        // Bengali: U+09E6 to U+09EF.
        if (sequence >= 0xe0a7a600 && sequence <= 0xe0a7af00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0a7a600, value);
        }

        // Gurmukhi: U+0A66 to U+0A6F.
        if (sequence >= 0xe0a9a600 && sequence <= 0xe0a9af00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0a9a600, value);
        }

        // Gujarati: U+0AE6 to U+0AEF.
        if (sequence >= 0xe0aba600 && sequence <= 0xe0abaf00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0aba600, value);
        }

        // Oriya: U+0B66 to U+0B6F.
        if (sequence >= 0xe0ada600 && sequence <= 0xe0adaf00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0ada600, value);
        }

        // Tamil: U+0BE6 to U+0BF2.
        if (sequence >= 0xe0afa600 && sequence <= 0xe0afb200) {

          // Tamil: U+0BE6 to U+0BEF.
          if (sequence <= 0xe0afaf00) {
            return private_inline_f_utf_character_handle_digit(sequence, 0xe0afa600, value);
          }

          // Tamil: U+0BF0.
          if (sequence == 0xe0afb000) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Tamil: U+0BF1.
          if (sequence == 0xe0afb100) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Tamil: U+0BF2.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Telugu: U+0C66 to U+0C72.
        if (sequence >= 0xe0b1a600 && sequence <= 0xe0b1af00) {

          // Telugu: U+0C66 to U+0C6F.
          if (sequence <= 0xe0b1af00) {
            return private_inline_f_utf_character_handle_digit(sequence, 0xe0b1a600, value);
          }

          // Telugu: U+0C70.
          if (sequence == 0xe0afb000) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Telugu: U+0C71.
          if (sequence == 0xe0afb100) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Telugu: U+0C72.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Kannada: U+0CE6 to U+0CEF.
        if (sequence >= 0xe0b3a600 && sequence <= 0xe0b3af00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0b3a600, value);
        }

        // Malayalam: U+0D66 to U+0D6F.
        if (sequence >= 0xe0b5a600 && sequence <= 0xe0b5af00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0b5a600, value);
        }

        // Sinhala: U+0DE6 to U+0DEF.
        if (sequence >= 0xe0b7a600 && sequence <= 0xe0b7af00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0b7a600, value);
        }

        // Thai: U+0E50 to U+0E59.
        if (sequence >= 0xe0b99000 && sequence <= 0xe0b99900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0b99000, value);
        }

        // Lao: U+0ED0 to U+0ED9.
        if (sequence >= 0xe0bb9000 && sequence <= 0xe0bb9900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0bb9000, value);
        }

        // Tibetan: U+0F20 to U+0F29.
        if (sequence >= 0xe0bca000 && sequence <= 0xe0bca900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe0bca000, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Myanmar: U+1040 to U+1049.
        if (sequence >= 0xe1818000 && sequence <= 0xe1818900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1818000, value);
        }

        // Myanmar (Shan): U+1090 to U+1099.
        if (sequence >= 0xe1829000 && sequence <= 0xe1829900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1829000, value);
        }

        // Ethiopic: U+1369 to U+137C.
        if (sequence >= 0xe18da900 && sequence <= 0xe18dbc00) {

          // Ethiopic: U+1369 to U+1371.
          if (sequence <= 0xe18db100) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe18da900, value);
          }

          // Ethiopic: U+1372.
          if (sequence == 0xe18db200) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ethiopic: U+1373.
          if (sequence == 0xe18db300) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Ethiopic: U+1374.
          if (sequence == 0xe18db400) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Ethiopic: U+1375.
          if (sequence == 0xe18db500) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Ethiopic: U+1376.
          if (sequence == 0xe18db600) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ethiopic: U+1377.
          if (sequence == 0xe18db700) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Ethiopic: U+1378.
          if (sequence == 0xe18db800) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Ethiopic: U+1379.
          if (sequence == 0xe18db900) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Ethiopic: U+137A.
          if (sequence == 0xe18dba00) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Ethiopic: U+137B.
          if (sequence == 0xe18dbb00) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Ethiopic: U+137C.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Runic: U+16EE to U+16F0.
        if (sequence >= 0xe19bae00 && sequence <= 0xe19bb000) {

          // Runic: U+16EE.
          if (sequence == 0xe19bae00) {
            if (value) {
              *value = 17;
            }

            return F_true;
          }

          // Runic: U+16EF.
          if (sequence == 0xe19baf00) {
            if (value) {
              *value = 18;
            }

            return F_true;
          }

          // Runic: U+16F0.
          if (value) {
            *value = 19;
          }

          return F_true;
        }

        // Khmer: U+17E0 to U+17E9.
        if (sequence >= 0xe19fa000 && sequence <= 0xe19fa900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe19fa000, value);
        }

        // Khmer: U+17F0 to U+17F9.
        if (sequence >= 0xe19fb000 && sequence <= 0xe19fb900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe19fb000, value);
        }

        // Mongolian: U+1810 to U+1819.
        if (sequence >= 0xe1a09000 && sequence <= 0xe1a09900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1a09000, value);
        }

        // Limbu: U+1946 to U+194F.
        if (sequence >= 0xe1a58600 && sequence <= 0xe1a58f00) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1a58600, value);
        }

        // New Tai Lue: U+19D0 to U+19D9.
        if (sequence >= 0xe1a79000 && sequence <= 0xe1a79900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1a79000, value);
        }

        // New Tai Lue: U+19DA.
        if (sequence == 0xe1a79a00) {
          if (value) {
            *value = 1;
          }

          return F_true;
        }

        // Tai Tham (Hora): U+1A80 to U+1A89.
        if (sequence >= 0xe1aa8000 && sequence <= 0xe1aa8900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1aa8000, value);
        }

        // Tai Tham (Tham): U+1A90 to U+1A99.
        if (sequence >= 0xe1aa9000 && sequence <= 0xe1aa9900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1aa9000, value);
        }

        // Balinese: U+1B50 to U+1B59.
        if (sequence >= 0xe1ad9000 && sequence <= 0xe1ad9900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1ad9000, value);
        }

        // Sundanese: U+1BB0 to U+1BB9.
        if (sequence >= 0xe1aeb000 && sequence <= 0xe1aeb900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1aeb000, value);
        }

        // Lepcha: U+1C40 to U+1C49.
        if (sequence >= 0xe1b18000 && sequence <= 0xe1b18900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1b18000, value);
        }

        // Ol Chiki: U+1C50 to U+1C59.
        if (sequence >= 0xe1b19000 && sequence <= 0xe1b19900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xe1b19000, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // Superscripts and Subscripts: U+2070 to U+2089.
        if (sequence >= 0xe281b000 && sequence <= 0xe2828900) {

          // Superscripts and Subscripts: U+2070.
          if (sequence == 0xe281b000) {
            if (value) {
              *value = 0;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2074.
          if (sequence == 0xe281b400) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2075.
          if (sequence == 0xe281b500) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2076.
          if (sequence == 0xe281b600) {
            if (value) {
              *value = 6;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2077.
          if (sequence == 0xe281b700) {
            if (value) {
              *value = 7;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2078.
          if (sequence == 0xe281b800) {
            if (value) {
              *value = 8;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2079.
          if (sequence == 0xe281b900) {
            if (value) {
              *value = 9;
            }

            return F_true;
          }

          // Superscripts and Subscripts: U+2080 to U+2089.
          return private_inline_f_utf_character_handle_digit(sequence, 0xe2828000, value);
        }

        // Number Forms: U+2160 to U+2188.
        if (sequence >= 0xe285a000 && sequence <= 0xe2868800) {

          // Number Forms: U+2160 to U+2168.
          if (sequence <= 0xe285a800) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe285a000, value);
          }

          // Number Forms: U+2170 to U+2178.
          if (sequence >= 0xe285b000 && sequence <= 0xe285b800) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe285b000, value);
          }

          // Number Forms: U+2185.
          if (sequence == 0xe2868500) {
            if (value) {
              *value = 6;
            }

            return F_true;
          }

          // Number Forms: U+2169, U+2179.
          if (sequence == 0xe285a900 || sequence == 0xe285b900) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Number Forms: U+216A, U+217A.
          else if (sequence == 0xe285aa00 || sequence == 0xe285ba00) {
            if (value) {
              *value = 11;
            }

            return F_true;
          }

          // Number Forms: U+216B, U+217B.
          else if (sequence == 0xe285ab00 || sequence == 0xe285bb00) {
            if (value) {
              *value = 12;
            }

            return F_true;
          }

          // Number Forms: U+216C, U+217C, U+2186.
          else if (sequence == 0xe285ac00 || sequence == 0xe285bc00 || sequence == 0xe2868600) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Number Forms: U+216D, U+217D, U+2183 (reversed, large), U+2184 (reversed, small).
          else if (sequence == 0xe285ad00 || sequence == 0xe285bd00 || sequence == 0xe2868300 || sequence == 0xe2868400) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Number Forms: U+216E, U+217E.
          else if (sequence == 0xe285ae00 || sequence == 0xe285be00) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Number Forms: U+216F, U+217F, U+2180 (1000 "CD").
          else if (sequence == 0xe285af00 || sequence == 0xe285bf00 || sequence == 0xe2868000) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Number Forms: U+2181.
          else if (sequence == 0xe2868100) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Number Forms: U+2182.
          else if (sequence == 0xe2868200) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Number Forms: U+2187.
          else if (sequence == 0xe2868700) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Number Forms: U+2188.
          else if (sequence == 0xe2868800) {
            if (value) {
              *value = 100000;
            }

            return F_true;
          }
        }

        // Enclosed Alphanumerics: U+2460 to U+249B.
        if (sequence >= 0xe291a000 && sequence <= 0xe2929b00) {

          // Enclosed Alphanumerics: U+2460 to U+2468.
          if (sequence <= 0xe291a800) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe291a000, value);
          }

          // Enclosed Alphanumerics: U+2469 to U+2472.
          if (sequence <= 0xe291b200) {
            return private_inline_f_utf_character_handle_digit_offset(sequence, 0xe291a900, 10, value);
          }

          // Enclosed Alphanumerics: U+2473.
          if (sequence == 0xe291b300) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Enclosed Alphanumerics: U+2474 to U+247C.
          if (sequence <= 0xe291bc00) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe291b400, value);
          }

          // Enclosed Alphanumerics: U+247D to U+247F.
          if (sequence <= 0xe291bf00) {
            return private_inline_f_utf_character_handle_digit_offset(sequence, 0xe291bd00, 10, value);
          }

          // Enclosed Alphanumerics: U+2480 to U+2486.
          if (sequence <= 0xe2928600) {
            return private_inline_f_utf_character_handle_digit_offset(sequence, 0xe2928000, 13, value);
          }

          // Enclosed Alphanumerics: U+2487.
          if (sequence == 0xe2928700) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Enclosed Alphanumerics: U+2487.
          if (sequence == 0xe2928700) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Enclosed Alphanumerics: U+2488 to U+2490.
          if (sequence <= 0xe2929000) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe2928800, value);
          }

          // Enclosed Alphanumerics: U+2491 to U+249A.
          if (sequence <= 0xe2929a00) {
            return private_inline_f_utf_character_handle_digit_offset(sequence, 0xe2929100, 10, value);
          }

          // Enclosed Alphanumerics: U+249B.
          if (value) {
            *value = 20;
          }

          return F_true;
        }

        // Enclosed Alphanumerics: U+24EA to U+24FF.
        if (sequence >= 0xe293aa00 && sequence <= 0xe293bf00) {

          // Enclosed Alphanumerics: U+24EA.
          if (sequence == 0xe293aa00) {
            if (value) {
              *value = 0;
            }

            return F_true;
          }

          // Enclosed Alphanumerics: U+24EB to U+24F3.
          if (sequence <= 0xe293b300) {
            return private_inline_f_utf_character_handle_digit_offset(sequence, 0xe293aa00, 10, value);
          }

          // Enclosed Alphanumerics: U+24F4.
          if (sequence == 0xe293b400) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Enclosed Alphanumerics: U+24F5 to U+24FD.
          if (sequence <= 0xe293bd00) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe293b500, value);
          }

          // Enclosed Alphanumerics: U+24FE.
          if (sequence == 0xe293be00) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Enclosed Alphanumerics: U+24FF.
          if (sequence == 0xe293bf00) {
            if (value) {
              *value = 0;
            }

            return F_true;
          }
        }

        // Dingbats: U+2776 to U+2793.
        if (sequence >= 0xe29db600 && sequence <= 0xe29e9300) {

          // Dingbats: U+2776 to U+277E.
          if (sequence <= 0xe29dbe00) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe29db600, value);
          }

          // Dingbats: U+277F.
          if (sequence == 0xe29dbf00) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Dingbats: U+2780 to U+2788.
          if (sequence <= 0xe29e8800) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe29e8000, value);
          }

          // Dingbats: U+2789.
          if (sequence == 0xe29e8900) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Dingbats: U+278A to U+2792.
          if (sequence <= 0xe29e9200) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe29e8a00, value);
          }

          // Dingbats: U+2793.
          if (value) {
            *value = 10;
          }

          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+3007.
        if (sequence == 0xe3808700) {
          if (value) {
            *value = 0;
          }

          return F_true;
        }

        // CJK Symbols and Punctuation: U+3021 to U+3029.
        if (sequence >= 0xe380a100 && sequence <= 0xe380a900) {
          return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe380a100, value);
        }

        // CJK Symbols and Punctuation: U+3038 to U+303A.
        if (sequence >= 0xe380b800 && sequence <= 0xe380ba00) {

          // CJK Symbols and Punctuation: U+3038.
          if (sequence == 0xe380b800) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // CJK Symbols and Punctuation: U+3039.
          if (sequence == 0xe380b900) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // CJK Symbols and Punctuation: U+303A.
          if (value) {
            *value = 30;
          }

          return F_true;
        }

        // Kanbun: U+3192 to U+3195.
        if (sequence >= 0xe3869200 && sequence <= 0xe3869500) {
          return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe3869200, value);
        }

        // Enclosed CJK Letters and Months: U+3220 to U+3229.
        if (sequence >= 0xe388a000 && sequence <= 0xe388a900) {

          // Enclosed CJK Letters and Months: U+3220 to U+3228.
          if (sequence <= 0xe388a800) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe388a000, value);
          }

          // Enclosed CJK Letters and Months: U+3229.
          if (value) {
            *value = 10;
          }

          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3248 to U+324F.
        if (sequence >= 0xe3898800 && sequence <= 0xe3898f00) {

          // Enclosed CJK Letters and Months: U+3248.
          if (sequence == 0xe3898800) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3249.
          if (sequence == 0xe3898900) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+324A.
          if (sequence == 0xe3898a00) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+324B.
          if (sequence == 0xe3898b00) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+324C.
          if (sequence == 0xe3898c00) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+324D.
          if (sequence == 0xe3898d00) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+324E.
          if (sequence == 0xe3898e00) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+324F.
          if (value) {
            *value = 80;
          }

          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3251 to U+325F.
        if (sequence >= 0xe3899100 && sequence <= 0xe3899f00) {

          // Enclosed CJK Letters and Months: U+3251.
          if (sequence == 0xe3899100) {
            if (value) {
              *value = 21;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3252.
          if (sequence == 0xe3899200) {
            if (value) {
              *value = 22;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3253.
          if (sequence == 0xe3899300) {
            if (value) {
              *value = 23;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3254.
          if (sequence == 0xe3899400) {
            if (value) {
              *value = 24;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3255.
          if (sequence == 0xe3899500) {
            if (value) {
              *value = 25;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3256.
          if (sequence == 0xe3899600) {
            if (value) {
              *value = 26;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3257.
          if (sequence == 0xe3899700) {
            if (value) {
              *value = 27;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3258.
          if (sequence == 0xe3899800) {
            if (value) {
              *value = 28;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+3259.
          if (sequence == 0xe3899900) {
            if (value) {
              *value = 29;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+325A.
          if (sequence == 0xe3899a00) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+325B.
          if (sequence == 0xe3899b00) {
            if (value) {
              *value = 31;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+325C.
          if (sequence == 0xe3899c00) {
            if (value) {
              *value = 32;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+325D.
          if (sequence == 0xe3899d00) {
            if (value) {
              *value = 33;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+325E.
          if (sequence == 0xe3899e00) {
            if (value) {
              *value = 34;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+325F.
          if (sequence == 0xe3899f00) {
            if (value) {
              *value = 35;
            }

            return F_true;
          }
        }

        // Enclosed CJK Letters and Months: U+3280 to U+3289.
        if (sequence >= 0xe38a8000 && sequence <= 0xe38a8900) {

          // Enclosed CJK Letters and Months: U+3280 to U+3288.
          if (sequence <= 0xe38a8800) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xe38a8000, value);
          }

          // Enclosed CJK Letters and Months: U+3289.
          if (value) {
            *value = 10;
          }

          return F_true;
        }

        // Enclosed CJK Letters and Months: U+32B1 to U+32BF.
        if (sequence >= 0xe38ab100 && sequence <= 0xe38abf00) {

          // Enclosed CJK Letters and Months: U+32B1.
          if (sequence == 0xe38ab100) {
            if (value) {
              *value = 36;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B2.
          if (sequence == 0xe38ab200) {
            if (value) {
              *value = 37;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B3.
          if (sequence == 0xe38ab300) {
            if (value) {
              *value = 38;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B4.
          if (sequence == 0xe38ab400) {
            if (value) {
              *value = 39;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B5.
          if (sequence == 0xe38ab500) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B6.
          if (sequence == 0xe38ab600) {
            if (value) {
              *value = 41;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B7.
          if (sequence == 0xe38ab700) {
            if (value) {
              *value = 42;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B8.
          if (sequence == 0xe38ab800) {
            if (value) {
              *value = 43;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32B9.
          if (sequence == 0xe38ab900) {
            if (value) {
              *value = 44;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32BA.
          if (sequence == 0xe38aba00) {
            if (value) {
              *value = 45;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32BB.
          if (sequence == 0xe38abb00) {
            if (value) {
              *value = 46;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32BC.
          if (sequence == 0xe38abc00) {
            if (value) {
              *value = 47;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32BD.
          if (sequence == 0xe38abd00) {
            if (value) {
              *value = 48;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32BE.
          if (sequence == 0xe38abe00) {
            if (value) {
              *value = 49;
            }

            return F_true;
          }

          // Enclosed CJK Letters and Months: U+32BF.
          if (value) {
            *value = 50;
          }

          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Vai: U+A620 to U+A629.
        if (sequence >= 0xea98a000 && sequence <= 0xea98a900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xea98a000, value);
        }

        // Bamum: U+A6E6 to U+A6EF.
        if (sequence >= 0xea9ba600 && sequence <= 0xea9baf00) {

          // Bamum: U+A6E6 to U+A6EE.
          if (sequence <= 0xea9bae00) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xea9ba600, value);
          }

          // Enclosed CJK Letters and Months: U+A6EF.
          if (value) {
            *value = 0;
          }

          return F_true;
        }

        // Common Indic Number Forms: U+A830 to U+A835.
        if (sequence >= 0xeaa0b000 && sequence <= 0xeaa0b500) {
          return F_true;
        }

        // Saurashtra: U+A8D0 to U+A8D9.
        if (sequence >= 0xeaa39000 && sequence <= 0xeaa39900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xeaa39000, value);
        }

        // Kayah Li: U+A900 to U+A909.
        if (sequence >= 0xeaa48000 && sequence <= 0xeaa48900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xeaa48000, value);
        }

        // Javanese: U+A9D0 to U+A9D9.
        if (sequence >= 0xeaa79000 && sequence <= 0xeaa79900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xeaa79000, value);
        }

        // Myanmar Extended-B: U+A9F0 to U+A9F9.
        if (sequence >= 0xeaa7b000 && sequence <= 0xeaa7b900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xeaa7b000, value);
        }

        // Cham: U+AA50 to U+AA59.
        if (sequence >= 0xeaa99000 && sequence <= 0xeaa99900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xeaa99000, value);
        }

        // Meetei Mayek: U+ABF0 to U+ABF9.
        if (sequence >= 0xeaafb000 && sequence <= 0xeaafb900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xeaafb000, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // Halfwidth and Fullwidth Forms: U+FF10 to U+FF19.
        if (sequence >= 0xefbc9000 && sequence <= 0xefbc9900) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xefbc9000, value);
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(sequence) == 0x90) {

        // Aegean Numbers: U+10107 to U+10133.
        if (sequence >= 0xf0908487 && sequence <= 0xf09084b3) {

          // Aegean Numbers: U+10107 to U+1010F.
          if (sequence <= 0xf090848f) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf0908487, value);
          }

          // Aegean Numbers: U+10110.
          if (sequence == 0xf0908490) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Aegean Numbers: U+10111.
          if (sequence == 0xf0908491) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Aegean Numbers: U+10112.
          if (sequence == 0xf0908492) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Aegean Numbers: U+10113.
          if (sequence == 0xf0908493) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Aegean Numbers: U+10114.
          if (sequence == 0xf0908494) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Aegean Numbers: U+10115.
          if (sequence == 0xf0908495) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Aegean Numbers: U+10116.
          if (sequence == 0xf0908496) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Aegean Numbers: U+10117.
          if (sequence == 0xf0908497) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Aegean Numbers: U+10118.
          if (sequence == 0xf0908498) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Aegean Numbers: U+10119.
          if (sequence == 0xf0908499) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Aegean Numbers: U+1011A.
          if (sequence == 0xf090849a) {
            if (value) {
              *value = 200;
            }

            return F_true;
          }

          // Aegean Numbers: U+1011B.
          if (sequence == 0xf090849b) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Aegean Numbers: U+1011C.
          if (sequence == 0xf090849c) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Aegean Numbers: U+1011D.
          if (sequence == 0xf090849d) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Aegean Numbers: U+1011E.
          if (sequence == 0xf090849e) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Aegean Numbers: U+1011F.
          if (sequence == 0xf090849f) {
            if (value) {
              *value = 700;
            }

            return F_true;
          }

          // Aegean Numbers: U+10120.
          if (sequence == 0xf09084a0) {
            if (value) {
              *value = 800;
            }

            return F_true;
          }

          // Aegean Numbers: U+10121.
          if (sequence == 0xf09084a1) {
            if (value) {
              *value = 900;
            }

            return F_true;
          }

          // Aegean Numbers: U+10122.
          if (sequence == 0xf09084a2) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10123.
          if (sequence == 0xf09084a3) {
            if (value) {
              *value = 2000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10124.
          if (sequence == 0xf09084a4) {
            if (value) {
              *value = 3000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10125.
          if (sequence == 0xf09084a5) {
            if (value) {
              *value = 4000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10126.
          if (sequence == 0xf09084a6) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10127.
          if (sequence == 0xf09084a7) {
            if (value) {
              *value = 6000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10128.
          if (sequence == 0xf09084a8) {
            if (value) {
              *value = 7000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10129.
          if (sequence == 0xf09084a9) {
            if (value) {
              *value = 8000;
            }

            return F_true;
          }

          // Aegean Numbers: U+1012a.
          if (sequence == 0xf09084aa) {
            if (value) {
              *value = 9000;
            }

            return F_true;
          }

          // Aegean Numbers: U+1012b.
          if (sequence == 0xf09084ab) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Aegean Numbers: U+1012c.
          if (sequence == 0xf09084ac) {
            if (value) {
              *value = 20000;
            }

            return F_true;
          }

          // Aegean Numbers: U+1012d.
          if (sequence == 0xf09084ad) {
            if (value) {
              *value = 30000;
            }

            return F_true;
          }

          // Aegean Numbers: U+1012e.
          if (sequence == 0xf09084ae) {
            if (value) {
              *value = 40000;
            }

            return F_true;
          }

          // Aegean Numbers: U+1012f.
          if (sequence == 0xf09084af) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10130.
          if (sequence == 0xf09084b0) {
            if (value) {
              *value = 60000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10131.
          if (sequence == 0xf09084b1) {
            if (value) {
              *value = 70000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10132.
          if (sequence == 0xf09084b2) {
            if (value) {
              *value = 80000;
            }

            return F_true;
          }

          // Aegean Numbers: U+10133.
          if (value) {
            *value = 90000;
          }

          return F_true;
        }

        // Ancient Greek Numbers: U+10142 to U+10174.
        if (sequence >= 0xf0908582 && sequence <= 0xf09085b4) {

          // Ancient Greek Numbers: U+10142.
          if (sequence == 0xf0908582) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10143.
          if (sequence == 0xf0908583) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10144.
          if (sequence == 0xf0908584) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10145.
          if (sequence == 0xf0908585) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10146.
          if (sequence == 0xf0908586) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10147.
          if (sequence == 0xf0908587) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10148.
          if (sequence == 0xf0908588) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10149.
          if (sequence == 0xf0908589) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1014A.
          if (sequence == 0xf090858a) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1014B.
          if (sequence == 0xf090858b) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1014C.
          if (sequence == 0xf090858c) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1014D.
          if (sequence == 0xf090858d) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1014E.
          if (sequence == 0xf090858e) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1014F.
          if (sequence == 0xf090858f) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10150.
          if (sequence == 0xf0908590) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10151.
          if (sequence == 0xf0908591) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10152.
          if (sequence == 0xf0908592) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10153.
          if (sequence == 0xf0908593) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10154.
          if (sequence == 0xf0908594) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10155.
          if (sequence == 0xf0908595) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10156.
          if (sequence == 0xf0908596) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10157.
          if (sequence == 0xf0908597) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10158.
          if (sequence == 0xf0908598) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10159.
          if (sequence == 0xf0908599) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1015A.
          if (sequence == 0xf090859a) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1015B.
          if (sequence == 0xf090859b) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1015C.
          if (sequence == 0xf090859c) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1015D.
          if (sequence == 0xf090859d) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1015E.
          if (sequence == 0xf090859e) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1015F.
          if (sequence == 0xf090859f) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10160.
          if (sequence == 0xf09085a0) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10161.
          if (sequence == 0xf09085a1) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10162.
          if (sequence == 0xf09085a2) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10163.
          if (sequence == 0xf09085a3) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10164.
          if (sequence == 0xf09085a4) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10165.
          if (sequence == 0xf09085a5) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10166.
          if (sequence == 0xf09085a6) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10167.
          if (sequence == 0xf09085a7) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10168.
          if (sequence == 0xf09085a8) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10169.
          if (sequence == 0xf09085a9) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10169.
          if (sequence == 0xf09085a9) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1016A.
          if (sequence == 0xf09085aa) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1016B.
          if (sequence == 0xf09085ab) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1016C.
          if (sequence == 0xf09085ac) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1016D.
          if (sequence == 0xf09085ad) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1016E.
          if (sequence == 0xf09085ae) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+1016F.
          if (sequence == 0xf09085af) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10170.
          if (sequence == 0xf09085b0) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10171.
          if (sequence == 0xf09085b1) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10172.
          if (sequence == 0xf09085b2) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10173.
          if (sequence == 0xf09085b3) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Ancient Greek Numbers: U+10174.
          if (sequence == 0xf09085b4) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }
        }

        // Ancient Greek Numbers: U+1018A.
        if (sequence == 0xf090868a) {
          if (value) {
            *value = 0;
          }

          return F_true;
        }

        // Coptic Epact Numbers: U+102E1 to U+102FB.
        if (sequence >= 0xf0908ba1 && sequence <= 0xf0908bbb) {

          // Coptic Epact Numbers: U+102E1 to U+102E9.
          if (sequence <= 0xf0908ba9) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf0908ba1, value);
          }

          // Coptic Epact Numbers: U+102EA.
          if (sequence == 0xf0908baa) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102EB.
          if (sequence == 0xf0908bab) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102EC.
          if (sequence == 0xf0908bac) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102ED.
          if (sequence == 0xf0908bad) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102EE.
          if (sequence == 0xf0908bae) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102EF.
          if (sequence == 0xf0908baf) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F0.
          if (sequence == 0xf0908bb0) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F1.
          if (sequence == 0xf0908bb1) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F2.
          if (sequence == 0xf0908bb2) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F3.
          if (sequence == 0xf0908bb3) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F4.
          if (sequence == 0xf0908bb4) {
            if (value) {
              *value = 200;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F5.
          if (sequence == 0xf0908bb5) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F6.
          if (sequence == 0xf0908bb6) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F7.
          if (sequence == 0xf0908bb7) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F8.
          if (sequence == 0xf0908bb8) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102F9.
          if (sequence == 0xf0908bb9) {
            if (value) {
              *value = 700;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102FA.
          if (sequence == 0xf0908bba) {
            if (value) {
              *value = 800;
            }

            return F_true;
          }

          // Coptic Epact Numbers: U+102FB.
          if (value) {
            *value = 900;
          }

          return F_true;
        }

        // Old Italic: U+10320 to U+10323.
        if (sequence >= 0xf0908ca0 && sequence <= 0xf0908ca3) {

          // Old Italic: U+10320.
          if (sequence == 0xf0908ca0) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Old Italic: U+10321.
          if (sequence == 0xf0908ca1) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Old Italic: U+10322.
          if (sequence == 0xf0908ca2) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Old Italic: U+10323.
          if (value) {
            *value = 50;
          }

          return F_true;
        }

        // Gothic: U+10341.
        if (sequence == 0xf0908d81) {
          if (value) {
            *value = 90;
          }

          return F_true;
        }

        // Gothic: U+1034A.
        if (sequence == 0xf0908d8a) {
          if (value) {
            *value = 900;
          }

          return F_true;
        }

        // Old Persian: U+103D1 to U+103D5.
        if (sequence >= 0xf0908f91 && sequence <= 0xf0908f95) {

          // Old Persian: U+103D1.
          if (sequence == 0xf0908f91) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Old Persian: U+103D2.
          if (sequence == 0xf0908f92) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Old Persian: U+103D3.
          if (sequence == 0xf0908f93) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Old Persian: U+103D4.
          if (sequence == 0xf0908f94) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Old Persian: U+103D5.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Osmanya: U+104A0 to U+104A9.
        if (sequence >= 0xf09092a0 && sequence <= 0xf09092a9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09092a0, value);
        }

        // Imperial Aramaic: U+10858 to U+1085F.
        if (sequence >= 0xf090a198 && sequence <= 0xf090a19f) {

          // Imperial Aramaic: U+10858.
          if (sequence == 0xf090a198) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Imperial Aramaic: U+10859.
          if (sequence == 0xf090a199) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Imperial Aramaic: U+1085a.
          if (sequence == 0xf090a19a) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Imperial Aramaic: U+1085b.
          if (sequence == 0xf090a19b) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Imperial Aramaic: U+1085c.
          if (sequence == 0xf090a19c) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Imperial Aramaic: U+1085d.
          if (sequence == 0xf090a19d) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Imperial Aramaic: U+1085e.
          if (sequence == 0xf090a19e) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Imperial Aramaic: U+1085f.
          if (value) {
            *value = 10000;
          }

          return F_true;
        }

        // Palmyrene: U+10879 to U+1087F.
        if (sequence >= 0xf090a1b9 && sequence <= 0xf090a1bf) {

          // Palmyrene: U+10879.
          if (sequence == 0xf090a1b9) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Palmyrene: U+1087A.
          if (sequence == 0xf090a1ba) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Palmyrene: U+1087B.
          if (sequence == 0xf090a1bb) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Palmyrene: U+1087C.
          if (sequence == 0xf090a1bc) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Palmyrene: U+1087D.
          if (sequence == 0xf090a1bd) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Palmyrene: U+1087E.
          if (sequence == 0xf090a1be) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Palmyrene: U+1087F.
          if (value) {
            *value = 20;
          }

          return F_true;
        }

        // Nabataean: U+108A7 to U+108AF.
        if (sequence >= 0xf090a2a7 && sequence <= 0xf090a2af) {

          // Nabataean: U+108A7.
          if (sequence == 0xf090a2a7) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Nabataean: U+108A8.
          if (sequence == 0xf090a2a8) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Nabataean: U+108A9.
          if (sequence == 0xf090a2a9) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Nabataean: U+108AA.
          if (sequence == 0xf090a2aa) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Nabataean: U+108AB.
          if (sequence == 0xf090a2ab) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Nabataean: U+108AC.
          if (sequence == 0xf090a2ac) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Nabataean: U+108AD.
          if (sequence == 0xf090a2ad) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Nabataean: U+108AE.
          if (sequence == 0xf090a2ae) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Nabataean: U+108AF.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Hatran: U+108FB to U+108FF.
        if (sequence >= 0xf090a3bb && sequence <= 0xf090a3bf) {

          // Hatran: U+108FB.
          if (sequence == 0xf090a3bb) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Hatran: U+108FC.
          if (sequence == 0xf090a3bc) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Hatran: U+108FD.
          if (sequence == 0xf090a3bd) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Hatran: U+108FE.
          if (sequence == 0xf090a3be) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Hatran: U+108FF.
          if (sequence == 0xf090a3bf) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }
        }

        // Phoenician: U+10916 to U+1091B.
        if (sequence >= 0xf090a496 && sequence <= 0xf090a49b) {

          // Phoenician: U+10916.
          if (sequence == 0xf090a496) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Phoenician: U+10917.
          if (sequence == 0xf090a497) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Phoenician: U+10918.
          if (sequence == 0xf090a498) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Phoenician: U+10919.
          if (sequence == 0xf090a499) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Phoenician: U+1091A.
          if (sequence == 0xf090a49a) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Phoenician: U+1091B.
          if (value) {
            *value = 3;
          }

          return F_true;
        }

        // Meroitic Cursive: U+109C0 to U+109F5.
        if (sequence >= 0xf090a780 && sequence <= 0xf090a7b5) {

          // Meroitic Cursive: U+109C0 to U+109C8.
          if (sequence <= 0xf090a788) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf090a780, value);
          }

          // Meroitic Cursive: U+109C9.
          if (sequence == 0xf090a789) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109CA.
          if (sequence == 0xf090a78a) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109CB.
          if (sequence == 0xf090a78b) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109CC.
          if (sequence == 0xf090a78c) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109CD.
          if (sequence == 0xf090a78d) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109CE.
          if (sequence == 0xf090a78e) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109CF.
          if (sequence == 0xf090a78f) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // U+109D1 and U+109D2 are fractions.

          // Meroitic Cursive: U+109D2.
          if (sequence == 0xf090a792) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D3.
          if (sequence == 0xf090a793) {
            if (value) {
              *value = 200;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D4.
          if (sequence == 0xf090a794) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D5.
          if (sequence == 0xf090a795) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D6.
          if (sequence == 0xf090a796) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D7.
          if (sequence == 0xf090a797) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D8.
          if (sequence == 0xf090a798) {
            if (value) {
              *value = 700;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109D9.
          if (sequence == 0xf090a799) {
            if (value) {
              *value = 800;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109DA.
          if (sequence == 0xf090a79a) {
            if (value) {
              *value = 900;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109DB.
          if (sequence == 0xf090a79b) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109DC.
          if (sequence == 0xf090a79c) {
            if (value) {
              *value = 2000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109DD.
          if (sequence == 0xf090a79d) {
            if (value) {
              *value = 3000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109DE.
          if (sequence == 0xf090a79e) {
            if (value) {
              *value = 4000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109DF.
          if (sequence == 0xf090a79f) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E0.
          if (sequence == 0xf090a7a0) {
            if (value) {
              *value = 6000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E1.
          if (sequence == 0xf090a7a1) {
            if (value) {
              *value = 7000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E2.
          if (sequence == 0xf090a7a2) {
            if (value) {
              *value = 8000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E3.
          if (sequence == 0xf090a7a3) {
            if (value) {
              *value = 9000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E4.
          if (sequence == 0xf090a7a4) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E5.
          if (sequence == 0xf090a7a5) {
            if (value) {
              *value = 20000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E6.
          if (sequence == 0xf090a7a6) {
            if (value) {
              *value = 30000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E7.
          if (sequence == 0xf090a7a7) {
            if (value) {
              *value = 40000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E8.
          if (sequence == 0xf090a7a8) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109E9.
          if (sequence == 0xf090a7a9) {
            if (value) {
              *value = 60000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109EA.
          if (sequence == 0xf090a7aa) {
            if (value) {
              *value = 70000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109EB.
          if (sequence == 0xf090a7ab) {
            if (value) {
              *value = 80000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109EC.
          if (sequence == 0xf090a7ac) {
            if (value) {
              *value = 90000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109ED.
          if (sequence == 0xf090a7ad) {
            if (value) {
              *value = 100000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109EE.
          if (sequence == 0xf090a7ae) {
            if (value) {
              *value = 200000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109EF.
          if (sequence == 0xf090a7af) {
            if (value) {
              *value = 300000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109F0.
          if (sequence == 0xf090a7b0) {
            if (value) {
              *value = 400000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109F1.
          if (sequence == 0xf090a7b1) {
            if (value) {
              *value = 500000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109F2.
          if (sequence == 0xf090a7b2) {
            if (value) {
              *value = 600000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109F3.
          if (sequence == 0xf090a7b3) {
            if (value) {
              *value = 700000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109F4.
          if (sequence == 0xf090a7b4) {
            if (value) {
              *value = 800000;
            }

            return F_true;
          }

          // Meroitic Cursive: U+109F5.
          if (sequence == 0xf090a7b5) {
            if (value) {
              *value = 900000;
            }

            return F_true;
          }
        }

        // Kharoshthi: U+10A40 to U+10A47.
        if (sequence >= 0xf090a980 && sequence <= 0xf090a987) {

          // Kharoshthi: U+10A40.
          if (sequence == 0xf090a980) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Kharoshthi: U+10A41.
          if (sequence == 0xf090a981) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Kharoshthi: U+10A42.
          if (sequence == 0xf090a982) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Kharoshthi: U+10A43.
          if (sequence == 0xf090a983) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Kharoshthi: U+10A44.
          if (sequence == 0xf090a984) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Kharoshthi: U+10A45.
          if (sequence == 0xf090a985) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Kharoshthi: U+10A46.
          if (sequence == 0xf090a986) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Kharoshthi: U+10A47.
          if (sequence == 0xf090a987) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }
        }

        // Old South Arabian: U+10A7D.
        if (sequence == 0xf090a9bd) {
          if (value) {
            *value = 1;
          }

          return F_true;
        }

        // Old South Arabian: U+10A7E.
        if (sequence == 0xf090a9be) {
          if (value) {
            *value = 50;
          }

          return F_true;
        }

        // Old North Arabian: U+10A9D to U+10A9F.
        if (sequence >= 0xf090aa9d && sequence <= 0xf090aa9f) {

          // Old North Arabian: U+10A9D.
          if (sequence == 0xf090aa9d) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Old North Arabian: U+10A9E.
          if (sequence == 0xf090aa9e) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Old North Arabian: U+10A9F.
          if (value) {
            *value = 20;
          }

          return F_true;
        }

        // Old North Arabian: U+10AEB to U+10AEF.
        if (sequence >= 0xf090abab && sequence <= 0xf090abaf) {

          // Old North Arabian: U+10AEB.
          if (sequence == 0xf090abab) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Old North Arabian: U+10AEC.
          if (sequence == 0xf090abac) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Old North Arabian: U+10AED.
          if (sequence == 0xf090abad) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Old North Arabian: U+10AEE.
          if (sequence == 0xf090abae) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Old North Arabian: U+10AEF.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Inscriptional Parthian: U+10B58 to U+10B5F.
        if (sequence >= 0xf090ad98 && sequence <= 0xf090ad9f) {

          // Inscriptional Parthian: U+10B58.
          if (sequence == 0xf090ad98) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B59.
          if (sequence == 0xf090ad99) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B5A.
          if (sequence == 0xf090ad9a) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B5B.
          if (sequence == 0xf090ad9b) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B5C.
          if (sequence == 0xf090ad9c) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B5D.
          if (sequence == 0xf090ad9d) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B5E.
          if (sequence == 0xf090ad9e) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Inscriptional Parthian: U+10B5F.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Inscriptional Pahlavi: U+10B78 to U+10B7F.
        if (sequence >= 0xf090adb8 && sequence <= 0xf090adbf) {

          // Inscriptional Pahlavi: U+10B78.
          if (sequence == 0xf090adb8) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B79.
          if (sequence == 0xf090adb9) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B7A.
          if (sequence == 0xf090adba) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B7B.
          if (sequence == 0xf090adbb) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B7C.
          if (sequence == 0xf090adbc) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B7D.
          if (sequence == 0xf090adbd) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B7E.
          if (sequence == 0xf090adbe) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Inscriptional Pahlavi: U+10B7F.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Psalter Pahlavi: U+10BA9 to U+10BAF.
        if (sequence >= 0xf090aea9 && sequence <= 0xf090aeaf) {

          // Psalter Pahlavi: U+10BA9.
          if (sequence == 0xf090aea9) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Psalter Pahlavi: U+10BAA.
          if (sequence == 0xf090aeaa) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Psalter Pahlavi: U+10BAB.
          if (sequence == 0xf090aeab) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Psalter Pahlavi: U+10BAC.
          if (sequence == 0xf090aeac) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Psalter Pahlavi: U+10BAD.
          if (sequence == 0xf090aead) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Psalter Pahlavi: U+10BAE.
          if (sequence == 0xf090aeae) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Psalter Pahlavi: U+10BAF.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Old Hungarian: U+10CFA to U+10CFF.
        if (sequence >= 0xf090b3ba && sequence <= 0xf090b3bf) {

          // Old Hungarian: U+10CFA.
          if (sequence == 0xf090b3ba) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Old Hungarian: U+10CFB.
          if (sequence == 0xf090b3bb) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Old Hungarian: U+10CFC.
          if (sequence == 0xf090b3bc) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Old Hungarian: U+10CFD.
          if (sequence == 0xf090b3bd) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Old Hungarian: U+10CFE.
          if (sequence == 0xf090b3be) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Old Hungarian: U+10CFF.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Rumi Numeral Symbols: U+10E60 to U+10E7A.
        if (sequence >= 0xf090b9a0 && sequence <= 0xf090b9ba) {

          // Rumi Numeral Symbols: U+10E60 to U+10E68.
          if (sequence <= 0xf090b9a8) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf090b9a0, value);
          }

          // Rumi Numeral Symbols: U+10E69.
          if (sequence == 0xf090b9a9) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E6A.
          if (sequence == 0xf090b9aa) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E6B.
          if (sequence == 0xf090b9ab) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E6C.
          if (sequence == 0xf090b9ac) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E6D.
          if (sequence == 0xf090b9ad) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E6E.
          if (sequence == 0xf090b9ae) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E6F.
          if (sequence == 0xf090b9af) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E70.
          if (sequence == 0xf090b9b0) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E71.
          if (sequence == 0xf090b9b1) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E72.
          if (sequence == 0xf090b9b2) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E73.
          if (sequence == 0xf090b9b3) {
            if (value) {
              *value = 200;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E74.
          if (sequence == 0xf090b9b4) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E75.
          if (sequence == 0xf090b9b5) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E76.
          if (sequence == 0xf090b9b6) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E77.
          if (sequence == 0xf090b9b7) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E78.
          if (sequence == 0xf090b9b8) {
            if (value) {
              *value = 700;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E79.
          if (sequence == 0xf090b9b9) {
            if (value) {
              *value = 800;
            }

            return F_true;
          }

          // Rumi Numeral Symbols: U+10E7A.
          if (value) {
            *value = 900;
          }

          return F_true;
        }

        // Old Sogdian: U+10F1D to U+10F25.
        if (sequence >= 0xf090bc9d && sequence <= 0xf090bca5) {

          // Old Sogdian: U+10F1D.
          if (sequence == 0xf090bc9d) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Old Sogdian: U+10F1E.
          if (sequence == 0xf090bc9e) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Old Sogdian: U+10F1F.
          if (sequence == 0xf090bc9f) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Old Sogdian: U+10F20.
          if (sequence == 0xf090bca0) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Old Sogdian: U+10F21.
          if (sequence == 0xf090bca1) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Old Sogdian: U+10F22.
          if (sequence == 0xf090bca2) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Old Sogdian: U+10F23.
          if (sequence == 0xf090bca3) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Old Sogdian: U+10F24.
          if (sequence == 0xf090bca4) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Old Sogdian: U+10F25.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Sogdian: U+10F51 to U+10F54.
        if (sequence >= 0xf090bd91 && sequence <= 0xf090bd94) {

          // Sogdian: U+10F51.
          if (sequence == 0xf090bd91) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Sogdian: U+10F52.
          if (sequence == 0xf090bd92) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Sogdian: U+10F53.
          if (sequence == 0xf090bd93) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Sogdian: U+10F54.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Chorasmian Number: U+10FC5 to U+10FCB.
        if (sequence >= 0xf090bf85 && sequence <= 0xf090bf8b) {

          // Chorasmian Number: U+10FC5.
          if (sequence == 0xf090bf85) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Chorasmian Number: U+10FC6.
          if (sequence == 0xf090bf86) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Chorasmian Number: U+10FC7.
          if (sequence == 0xf090bf87) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Chorasmian Number: U+10FC8.
          if (sequence == 0xf090bf88) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Chorasmian Number: U+10FC9.
          if (sequence == 0xf090bf89) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Chorasmian Number: U+10FCA.
          if (sequence == 0xf090bf8a) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Chorasmian Number: U+10FCA.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Hanifi Rohingya: U+10D30 to U+10D39.
        if (sequence >= 0xf090b4b0 && sequence <= 0xf090b4b9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf090b4b0, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Brahmi: U+11066 to U+1106F.
        if (sequence >= 0xf09181a6 && sequence <= 0xf09181af) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09181a6, value);
        }

        // Sora Sompeng: U+110F0 to U+110F9.
        if (sequence >= 0xf09183b0 && sequence <= 0xf09183b9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09183b0, value);
        }

        // Chakma: U+11136 to U+1113F.
        if (sequence >= 0xf09184b6 && sequence <= 0xf09184bf) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09184b6, value);
        }

        // Sharada: U+111D0 to U+111D9.
        if (sequence >= 0xf0918790 && sequence <= 0xf0918799) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0918790, value);
        }

        // Khudawadi: U+112F0 to U+112F9.
        if (sequence >= 0xf0918bb0 && sequence <= 0xf0918bb9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0918bb0, value);
        }

        // Newa: U+11450 to U+11459.
        if (sequence >= 0xf0919190 && sequence <= 0xf0919199) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0919190, value);
        }

        // Tirhuta: U+114D0 to U+114D9.
        if (sequence >= 0xf0919390 && sequence <= 0xf0919399) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0919390, value);
        }

        // Modi: U+11650 to U+11659.
        if (sequence >= 0xf0919990 && sequence <= 0xf0919999) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0919990, value);
        }

        // Takri: U+116C0 to U+116C9.
        if (sequence >= 0xf0919b80 && sequence <= 0xf0919b89) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0919b80, value);
        }

        // Ahom: U+11730 to U+11739.
        if (sequence >= 0xf0919cb0 && sequence <= 0xf0919cb9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf0919cb0, value);
        }

        // Warang Citi: U+118E0 to U+118E9.
        if (sequence >= 0xf091a3a0 && sequence <= 0xf091a3a9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf091a3a0, value);
        }

        // Dives Akuru: U+11950 to U+11959.
        if (sequence >= 0xf091a590 && sequence <= 0xf091a599) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf091a590, value);
        }

        // Bhaiksuki: U+11C50 to U+11C59.
        if (sequence >= 0xf091b190 && sequence <= 0xf091b199) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf091b190, value);
        }

        // Bhaiksuki: U+11C5A to U+11C6C.
        if (sequence >= 0xf091b19a && sequence <= 0xf091b1ac) {

          // Bhaiksuki: U+11C5A to U+11C62.
          if (sequence <= 0xf091b1a2) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf091b19a, value);
          }

          // Bhaiksuki: U+11C63.
          if (sequence == 0xf091b1a3) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C64.
          if (sequence == 0xf091b1a4) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C65.
          if (sequence == 0xf091b1a5) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C66.
          if (sequence == 0xf091b1a6) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C67.
          if (sequence == 0xf091b1a7) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C68.
          if (sequence == 0xf091b1a8) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C69.
          if (sequence == 0xf091b1a9) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C6A.
          if (sequence == 0xf091b1aa) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C6B.
          if (sequence == 0xf091b1ab) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Bhaiksuki: U+11C6C.
          if (value) {
            *value = 100;
          }

          return F_true;
        }

        // Masaram Gondi: U+11D50 to U+11D59.
        if (sequence >= 0xf091b590 && sequence <= 0xf091b599) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf091b590, value);
        }

        // Gunjala Gondi: U+11DA0 to U+11DA9.
        if (sequence >= 0xf091b6a0 && sequence <= 0xf091b6a9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf091b6a0, value);
        }

        // Brahmi: U+11052 to U+11065.
        if (sequence >= 0xf0918192 && sequence <= 0xf09181a5) {

          // Brahmi: U+11052 to U+1105A.
          if (sequence <= 0xf091819a) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf0918192, value);
          }

          // Brahmi: U+1105B.
          if (sequence == 0xf091819b) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Brahmi: U+1105C.
          if (sequence == 0xf091819c) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Brahmi: U+1105D.
          if (sequence == 0xf091819d) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Brahmi: U+1105E.
          if (sequence == 0xf091819e) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Brahmi: U+1105F.
          if (sequence == 0xf091819f) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Brahmi: U+11060.
          if (sequence == 0xf09181a0) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Brahmi: U+11061.
          if (sequence == 0xf09181a1) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Brahmi: U+11062.
          if (sequence == 0xf09181a2) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Brahmi: U+11063.
          if (sequence == 0xf09181a3) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Brahmi: U+11064.
          if (sequence == 0xf09181a4) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Brahmi: U+11065.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Sinhala Archaic Numbers: U+111E1 to U+111F4.
        if (sequence >= 0xf09187a1 && sequence <= 0xf09187b4) {

          // Sinhala Archaic Numbers: U+111E1 to U+111E9.
          if (sequence <= 0xf09187a9) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09187a1, value);
          }

          // Sinhala Archaic Numbers: U+111EA.
          if (sequence == 0xf09187aa) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111EB.
          if (sequence == 0xf09187ab) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111EC.
          if (sequence == 0xf09187ac) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111ED.
          if (sequence == 0xf09187ad) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111EE.
          if (sequence == 0xf09187ae) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111EF.
          if (sequence == 0xf09187af) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111F0.
          if (sequence == 0xf09187b0) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111F1.
          if (sequence == 0xf09187b1) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111F2.
          if (sequence == 0xf09187b2) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111F3.
          if (sequence == 0xf09187b3) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Sinhala Archaic Numbers: U+111F4.
          if (value) {
            *value = 1000;
          }

          return F_true;
        }

        // Ahom: U+1173A.
        if (sequence == 0xf0919cba) {
          if (value) {
            *value = 10;
          }

          return F_true;
        }

        // Ahom: U+1173B.
        if (sequence == 0xf0919cbb) {
          if (value) {
            *value = 20;
          }

          return F_true;
        }

        // Warang Citi: U+118EA to U+118F2.
        if (sequence >= 0xf091a3aa && sequence <= 0xf091a3b2) {

          // Warang Citi: U+118EA.
          if (sequence == 0xf091a3aa) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Warang Citi: U+118EB.
          if (sequence == 0xf091a3ab) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Warang Citi: U+118EC.
          if (sequence == 0xf091a3ac) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Warang Citi: U+118ED.
          if (sequence == 0xf091a3ad) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Warang Citi: U+118EE.
          if (sequence == 0xf091a3ae) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Warang Citi: U+118EF.
          if (sequence == 0xf091a3af) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Warang Citi: U+118F0.
          if (sequence == 0xf091a3b0) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Warang Citi: U+118F1.
          if (sequence == 0xf091a3b1) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Warang Citi: U+118F2.
          if (value) {
            *value = 90;
          }

          return F_true;
        }

        // Kawi: U+11F50 to U+11F59.
        if (sequence >= 0xf091bd90 && sequence <= 0xf091bd99) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf091bd90, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x92) {

        // Cuneiform Numbers and Punctuation: U+12400 to U+1246E.
        if (sequence >= 0xf0929080 && sequence <= 0xf09291ae) {

          // Cuneiform Numbers and Punctuation: U+12400 to U+12407.
          if (sequence <= 0xf0929087) {
            return private_inline_f_utf_character_handle_digit_from_two(sequence, 0xf0929080, value);
          }

          // Cuneiform Numbers and Punctuation: U+12408 to U+1240E.
          if (sequence <= 0xf092908e) {
            return private_inline_f_utf_character_handle_digit_from_three(sequence, 0xf0929088, value);
          }

          // Cuneiform Numbers and Punctuation: U+1240F to U+12414.
          if (sequence <= 0xf0929094) {
            return private_inline_f_utf_character_handle_digit_from_four(sequence, 0xf092908f, value);
          }

          // Cuneiform Numbers and Punctuation: U+12415 to U+1241D.
          if (sequence <= 0xf092909d) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf0929095, value);
          }

          // Cuneiform Numbers and Punctuation: U+1241E to U+12422.
          if (sequence <= 0xf09290a2) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf092909e, value);
          }

          // Cuneiform Numbers and Punctuation: U+12423.
          if (sequence == 0xf09290a3) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12424, U+12425.
          if (sequence == 0xf09290a4 || sequence == 0xf09290a5) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12426 to U+1242B.
          if (sequence <= 0xf09290ab) {
            return private_inline_f_utf_character_handle_digit_from_four(sequence, 0xf09290a6, value);
          }

          // Cuneiform Numbers and Punctuation: U+1242C to U+1242E.
          if (sequence <= 0xf09290ae) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09290ac, value);
          }

          // Cuneiform Numbers and Punctuation: U+1242F to U+12431.
          if (sequence <= 0xf09290b1) {
            return private_inline_f_utf_character_handle_digit_from_three(sequence, 0xf09290af, value);
          }

          // Cuneiform Numbers and Punctuation: U+12432.
          if (sequence == 0xf09290b2) {
            if (value) {
              *value = 216000;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12433.
          if (sequence == 0xf09290b3) {
            if (value) {
              *value = 432000;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12434.
          if (sequence == 0xf09290b4) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12435.
          if (sequence == 0xf09290b5) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12436.
          if (sequence == 0xf09290b6) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12437.
          if (sequence == 0xf09290b7) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12438.
          if (sequence == 0xf09290b8) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12439.
          if (sequence == 0xf09290b9) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1243A.
          if (sequence == 0xf09290ba) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1243B.
          if (sequence == 0xf09290bb) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1243C.
          if (sequence == 0xf09290bc) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1243D.
          if (sequence == 0xf09290bd) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1243E.
          if (sequence == 0xf09290be) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1243F.
          if (sequence == 0xf09290bf) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12440.
          if (sequence == 0xf0929180) {
            if (value) {
              *value = 6;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12441.
          if (sequence == 0xf0929181) {
            if (value) {
              *value = 7;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12442.
          if (sequence == 0xf0929182) {
            if (value) {
              *value = 7;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12443.
          if (sequence == 0xf0929183) {
            if (value) {
              *value = 7;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12444.
          if (sequence == 0xf0929184) {
            if (value) {
              *value = 8;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12445.
          if (sequence == 0xf0929185) {
            if (value) {
              *value = 8;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12446.
          if (sequence == 0xf0929186) {
            if (value) {
              *value = 9;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12447.
          if (sequence == 0xf0929187) {
            if (value) {
              *value = 9;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12448.
          if (sequence == 0xf0929188) {
            if (value) {
              *value = 9;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12449.
          if (sequence == 0xf0929189) {
            if (value) {
              *value = 9;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1244A.
          if (sequence == 0xf092918a) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1244B.
          if (sequence == 0xf092918b) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1244C.
          if (sequence == 0xf092918c) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1244D.
          if (sequence == 0xf092918d) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1244E.
          if (sequence == 0xf092918e) {
            if (value) {
              *value = 6;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1244F.
          if (sequence == 0xf092918f) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12450.
          if (sequence == 0xf0929190) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12451.
          if (sequence == 0xf0929191) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12452.
          if (sequence == 0xf0929192) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12453.
          if (sequence == 0xf0929193) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12454.
          if (sequence == 0xf0929194) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12455.
          if (sequence == 0xf0929195) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12456.
          if (sequence == 0xf0929196) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12457.
          if (sequence == 0xf0929197) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12458.
          if (sequence == 0xf0929198) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12459.
          if (sequence == 0xf0929199) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12467.
          if (sequence == 0xf09291a7) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12468.
          if (sequence == 0xf09291a8) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+12469.
          if (sequence == 0xf09291a9) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1246A.
          if (sequence == 0xf09291aa) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1246B.
          if (sequence == 0xf09291ab) {
            if (value) {
              *value = 6;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1246C.
          if (sequence == 0xf09291ac) {
            if (value) {
              *value = 7;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1246D.
          if (sequence == 0xf09291ad) {
            if (value) {
              *value = 8;
            }

            return F_true;
          }

          // Cuneiform Numbers and Punctuation: U+1246E.
          if (sequence == 0xf09291ae) {
            if (value) {
              *value = 9;
            }

            return F_true;
          }
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x96) {

        // Mro: U+16A60 to U+16A69.
        if (sequence >= 0xf096a9a0 && sequence <= 0xf096a9a9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf096a9a0, value);
        }

        // Tangsa: U+16AC0 to U+16AC9.
        if (sequence >= 0xf096ab80 && sequence <= 0xf096ab89) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf096ab80, value);
        }

        // Pahawh Hmong: U+16B50 to U+16B59.
        if (sequence >= 0xf096ad90 && sequence <= 0xf096ad99) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf096ad90, value);
        }

        // Pahawh Hmong: U+16B5B to U+16B61.
        if (sequence >= 0xf096ad9b && sequence <= 0xf096ada1) {

          // Pahawh Hmong: U+16B5B.
          if (sequence == 0xf096ad9b) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Pahawh Hmong: U+16B5C.
          if (sequence == 0xf096ad9c) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Pahawh Hmong: U+16B5D.
          if (sequence == 0xf096ad9d) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Pahawh Hmong: U+16B5E.
          if (sequence == 0xf096ad9e) {
            if (value) {
              *value = 1000000;
            }

            return F_true;
          }

          // Pahawh Hmong: U+16B5F.
          if (sequence == 0xf096ad9f) {
            if (value) {
              *value = 100000000;
            }

            return F_true;
          }

          // Pahawh Hmong: U+16B60.
          if (sequence == 0xf096ada0) {
            if (value) {
              *value = 10000000000;
            }

            return F_true;
          }

          // Pahawh Hmong: U+16B61.
          if (value) {
            *value = 1000000000000;
          }

          return F_true;
        }

        // Medefaidrin: U+16E80 to U+16E96.
        if (sequence >= 0xf096ba80 && sequence <= 0xf096ba96) {

          // Medefaidrin: U+16E80 to U+16E89.
          if (sequence <= 0xf096ba89) {
            return private_inline_f_utf_character_handle_digit(sequence, 0xf096ba80, value);
          }

          // Medefaidrin: U+16E8A to U+16E93.
          if (sequence <= 0xf096ba93) {
            return private_inline_f_utf_character_handle_digit_offset(sequence, 0xf096ba8a, 10, value);
          }

          // Medefaidrin: U+16E94 to U+16E96.
          return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf096ba94, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

        // Kaktovik Numerals: U+1D2C0 to U+1D2D3.
        if (sequence >= 0xf09d8b80 && sequence <= 0xf09d8b93) {

          // Kaktovik Numerals: U+1D2C0 to U+1D2C9.
          if (sequence <= 0xf09d8b89) {
            return private_inline_f_utf_character_handle_digit(sequence, 0xf09d8b80, value);
          }

          // Kaktovik Numerals: U+1D2CA to U+1D2D3.
          return private_inline_f_utf_character_handle_digit_offset(sequence, 0xf09d8b8a, 10, value);
        }

        // Mayan Numerals: U+1D2E0 to U+1D2F3.
        if (sequence >= 0xf09d8ba0 && sequence <= 0xf09d8bb3) {

          // Mayan Numerals: U+1D2E0 to U+1D2E9.
          if (sequence <= 0xf09d8ba9) {
            return private_inline_f_utf_character_handle_digit(sequence, 0xf09d8ba0, value);
          }

          // Mayan Numerals: U+1D2EA to U+1D2F3.
          return private_inline_f_utf_character_handle_digit_offset(sequence, 0xf09d8baa, 10, value);
        }

        // Counting Rod Numerals: U+1D360 to U+1D378.
        if (sequence >= 0xf09d8da0 && sequence <= 0xf09d8db8) {

          // Counting Rod Numerals: U+1D360 to U+1D368.
          if (sequence <= 0xf09d8da8) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09d8da0, value);
          }

          // Counting Rod Numerals: U+1D369.
          if (sequence == 0xf09d8da9) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D36A.
          if (sequence == 0xf09d8daa) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D36B.
          if (sequence == 0xf09d8dab) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D36C.
          if (sequence == 0xf09d8dac) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D36D.
          if (sequence == 0xf09d8dad) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D36E.
          if (sequence == 0xf09d8dae) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D36F.
          if (sequence == 0xf09d8daf) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D370.
          if (sequence == 0xf09d8db0) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D371.
          if (sequence == 0xf09d8db1) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D372.
          if (sequence == 0xf09d8db2) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D373.
          if (sequence == 0xf09d8db3) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D374.
          if (sequence == 0xf09d8db4) {
            if (value) {
              *value = 3;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D375.
          if (sequence == 0xf09d8db5) {
            if (value) {
              *value = 4;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D376.
          if (sequence == 0xf09d8db6) {
            if (value) {
              *value = 5;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D377.
          if (sequence == 0xf09d8db7) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Counting Rod Numerals: U+1D378.
          if (value) {
            *value = 5;
          }

          return F_true;
        }

        // Mathematical Alphanumeric (Bold) Symbols: U+1D7CE to U+1D7D7.
        if (sequence >= 0xf09d9f8e && sequence <= 0xf09d9f97) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09d9f8e, value);
        }

        // Mathematical Alphanumeric (Double-Struck) Symbols: U+1D7D8 to U+1D7E1.
        if (sequence >= 0xf09d9f98 && sequence <= 0xf09d9fa1) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09d9f98, value);
        }

        // Mathematical Alphanumeric (Sans-Serif) Symbols: U+1D7E2 to U+1D7EB.
        if (sequence >= 0xf09d9fa2 && sequence <= 0xf09d9fab) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09d9fa2, value);
        }

        // Mathematical Alphanumeric (Sans-Serif Bold) Symbols: U+1D7EC to U+1D7F5.
        if (sequence >= 0xf09d9fac && sequence <= 0xf09d9fb5) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09d9fac, value);
        }

        // Mathematical Alphanumeric (Monospace) Symbols: U+1D7F6 to U+1D7FF.
        if (sequence >= 0xf09d9fb6 && sequence <= 0xf09d9fbf) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09d9fb6, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9e) {

        // Nag Mundari: U+1E4F0 to U+1E4F9.
        if (sequence >= 0xf09e93b0 && sequence <= 0xf09e93b9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09e93b0, value);
        }

        // Mende Kikakui: U+1E8C7 to U+1E8CF.
        if (sequence >= 0xf09ea387 && sequence <= 0xf09ea38f) {
          return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09ea387, value);
        }

        // Indic Siyaq Numbers: U+1EC71 to U+1ECB4.
        if (sequence >= 0xf09eb1b1 && sequence <= 0xf09eb2b4) {

          // Indic Siyaq Numbers: U+1EC71 to U+1EC79.
          if (sequence <= 0xf09eb1b9) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09eb1b1, value);
          }

          // Indic Siyaq Numbers: U+1EC7A.
          if (sequence == 0xf09eb1ba) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC7B.
          if (sequence == 0xf09eb1bb) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC7C.
          if (sequence == 0xf09eb1bc) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC7D.
          if (sequence == 0xf09eb1bd) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC7E.
          if (sequence == 0xf09eb1be) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC7F.
          if (sequence == 0xf09eb1bf) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC80.
          if (sequence == 0xf09eb280) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC81.
          if (sequence == 0xf09eb281) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC82.
          if (sequence == 0xf09eb282) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC83.
          if (sequence == 0xf09eb283) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC84.
          if (sequence == 0xf09eb284) {
            if (value) {
              *value = 200;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC85.
          if (sequence == 0xf09eb285) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC86.
          if (sequence == 0xf09eb286) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC87.
          if (sequence == 0xf09eb287) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC88.
          if (sequence == 0xf09eb288) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC89.
          if (sequence == 0xf09eb289) {
            if (value) {
              *value = 700;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC8A.
          if (sequence == 0xf09eb28a) {
            if (value) {
              *value = 800;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC8B.
          if (sequence == 0xf09eb28b) {
            if (value) {
              *value = 900;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC8C.
          if (sequence == 0xf09eb28c) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC8D.
          if (sequence == 0xf09eb28d) {
            if (value) {
              *value = 2000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC8E.
          if (sequence == 0xf09eb28e) {
            if (value) {
              *value = 3000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC8F.
          if (sequence == 0xf09eb28f) {
            if (value) {
              *value = 4000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC90.
          if (sequence == 0xf09eb290) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC91.
          if (sequence == 0xf09eb291) {
            if (value) {
              *value = 6000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC92.
          if (sequence == 0xf09eb292) {
            if (value) {
              *value = 7000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC93.
          if (sequence == 0xf09eb293) {
            if (value) {
              *value = 8000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC94.
          if (sequence == 0xf09eb294) {
            if (value) {
              *value = 9000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC95.
          if (sequence == 0xf09eb295) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC96.
          if (sequence == 0xf09eb296) {
            if (value) {
              *value = 20000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC97.
          if (sequence == 0xf09eb297) {
            if (value) {
              *value = 30000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC98.
          if (sequence == 0xf09eb298) {
            if (value) {
              *value = 40000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC99.
          if (sequence == 0xf09eb299) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC9A.
          if (sequence == 0xf09eb29a) {
            if (value) {
              *value = 60000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC9B.
          if (sequence == 0xf09eb29b) {
            if (value) {
              *value = 70000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC9C.
          if (sequence == 0xf09eb29c) {
            if (value) {
              *value = 80000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC9D.
          if (sequence == 0xf09eb29d) {
            if (value) {
              *value = 90000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC9E.
          if (sequence == 0xf09eb29e) {
            if (value) {
              *value = 100000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1EC9F.
          if (sequence == 0xf09eb29f) {
            if (value) {
              *value = 200000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECA0.
          if (sequence == 0xf09eb2a0) {
            if (value) {
              *value = 100000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECA1.
          if (sequence == 0xf09eb2a1) {
            if (value) {
              *value = 10000000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECA2.
          if (sequence == 0xf09eb2a2) {
            if (value) {
              *value = 20000000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECA3 to U+1ECAB.
          if (sequence <= 0xf09eb2ab) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09eb2a3, value);
          }

          // These are not whole numbers: U+1ECAC, U+1ECAD, U+1ECAE, U+1ECAF, and U+1ECB0.

          // Indic Siyaq Numbers: U+1ECB1.
          if (sequence == 0xf09eb2b1) {
            if (value) {
              *value = 1;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECB2.
          if (sequence == 0xf09eb2b2) {
            if (value) {
              *value = 2;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECB3.
          if (sequence == 0xf09eb2b3) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Indic Siyaq Numbers: U+1ECB4.
          if (sequence == 0xf09eb2b4) {
            if (value) {
              *value = 100000;
            }

            return F_true;
          }
        }

        // Nyiakeng Puachue Hmong: U+1E140 to U+1E149.
        if (sequence >= 0xf09e8580 && sequence <= 0xf09e8589) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09e8580, value);
        }

        // Wancho: U+1E2F0 to U+1E2F9.
        if (sequence >= 0xf09e8bb0 && sequence <= 0xf09e8bb9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09e8bb0, value);
        }

        // Adlam: U+1E950 to U+1E959.
        if (sequence >= 0xf09ea590 && sequence <= 0xf09ea599) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09ea590, value);
        }

        // Ottoman Siyaq Numbers: U+1ED01 to U+1ED3B.
        if (sequence >= 0xf09eb481 && sequence <= 0xf09eb4bb) {

          // Ottoman Siyaq Numbers: U+1ED01 to U+1ED09.
          if (sequence <= 0xf09eb489) {
            return private_inline_f_utf_character_handle_digit_from_one(sequence, 0xf09eb481, value);
          }

          // Ottoman Siyaq Numbers: U+1ED0A.
          if (sequence == 0xf09eb48a) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED0B.
          if (sequence == 0xf09eb48b) {
            if (value) {
              *value = 20;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED0C.
          if (sequence == 0xf09eb48c) {
            if (value) {
              *value = 30;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED0D.
          if (sequence == 0xf09eb48d) {
            if (value) {
              *value = 40;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED0E.
          if (sequence == 0xf09eb48e) {
            if (value) {
              *value = 50;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED0F.
          if (sequence == 0xf09eb48f) {
            if (value) {
              *value = 60;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED10.
          if (sequence == 0xf09eb490) {
            if (value) {
              *value = 70;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED11.
          if (sequence == 0xf09eb491) {
            if (value) {
              *value = 80;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED12.
          if (sequence == 0xf09eb492) {
            if (value) {
              *value = 90;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED13.
          if (sequence == 0xf09eb493) {
            if (value) {
              *value = 100;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED14.
          if (sequence == 0xf09eb494) {
            if (value) {
              *value = 200;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED15.
          if (sequence == 0xf09eb495) {
            if (value) {
              *value = 300;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED16.
          if (sequence == 0xf09eb496) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED17.
          if (sequence == 0xf09eb497) {
            if (value) {
              *value = 500;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED18.
          if (sequence == 0xf09eb498) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED19.
          if (sequence == 0xf09eb499) {
            if (value) {
              *value = 700;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED1A.
          if (sequence == 0xf09eb49a) {
            if (value) {
              *value = 800;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED1B.
          if (sequence == 0xf09eb49b) {
            if (value) {
              *value = 900;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED1C.
          if (sequence == 0xf09eb49c) {
            if (value) {
              *value = 1000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED1D.
          if (sequence == 0xf09eb49d) {
            if (value) {
              *value = 2000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED1E.
          if (sequence == 0xf09eb49e) {
            if (value) {
              *value = 3000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED1F.
          if (sequence == 0xf09eb49f) {
            if (value) {
              *value = 4000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED20.
          if (sequence == 0xf09eb4a0) {
            if (value) {
              *value = 5000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED21.
          if (sequence == 0xf09eb4a1) {
            if (value) {
              *value = 6000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED22.
          if (sequence == 0xf09eb4a2) {
            if (value) {
              *value = 7000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED23.
          if (sequence == 0xf09eb4a3) {
            if (value) {
              *value = 8000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED24.
          if (sequence == 0xf09eb4a4) {
            if (value) {
              *value = 9000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED25.
          if (sequence == 0xf09eb4a5) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED26.
          if (sequence == 0xf09eb4a6) {
            if (value) {
              *value = 20000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED27.
          if (sequence == 0xf09eb4a7) {
            if (value) {
              *value = 30000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED28.
          if (sequence == 0xf09eb4a8) {
            if (value) {
              *value = 40000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED29.
          if (sequence == 0xf09eb4a9) {
            if (value) {
              *value = 50000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED2A.
          if (sequence == 0xf09eb4aa) {
            if (value) {
              *value = 60000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED2B.
          if (sequence == 0xf09eb4ab) {
            if (value) {
              *value = 70000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED2C.
          if (sequence == 0xf09eb4ac) {
            if (value) {
              *value = 80000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED2D.
          if (sequence == 0xf09eb4ad) {
            if (value) {
              *value = 90000;
            }

            return F_true;
          }

          // Not a whole number: U+1ED2E.

          // Ottoman Siyaq Numbers: U+1ED2F to U+1ED36.
          if (sequence >= 0xf09eb4af && sequence <= 0xf09eb4b6) {
            return private_inline_f_utf_character_handle_digit_from_two(sequence, 0xf09eb4af, value);
          }

          // Ottoman Siyaq Numbers: U+1ED37.
          if (sequence == 0xf09eb4b7) {
            if (value) {
              *value = 10;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED38.
          if (sequence == 0xf09eb4b8) {
            if (value) {
              *value = 400;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED39.
          if (sequence == 0xf09eb4b9) {
            if (value) {
              *value = 600;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED3A.
          if (sequence == 0xf09eb4ba) {
            if (value) {
              *value = 2000;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED3B.
          if (sequence == 0xf09eb4bb) {
            if (value) {
              *value = 10000;
            }

            return F_true;
          }
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Enclosed Alphanumeric Supplement: U+1F100 to U+1F10C.
        if (sequence >= 0xf09f8480 && sequence <= 0xf09f848c) {

          // Enclosed Alphanumeric Supplement: U+1F100.
          if (sequence == 0xf09f8480) {
            if (value) {
              *value = 0;
            }

            return F_true;
          }

          // Ottoman Siyaq Numbers: U+1ED01 to U+1F10A.
          if (sequence <= 0xf09f848a) {
            return private_inline_f_utf_character_handle_digit(sequence, 0xf09f8481, value);
          }

          // Enclosed Alphanumeric Supplement: U+1F10B, U+1F10C.
          if (value) {
            *value = 0;
          }

          return F_true;
        }

        // Symbols for Legacy Computing (Segmented): U+1FBF0 to U+1FBF9.
        if (sequence >= 0xf09fafb0 && sequence <= 0xf09fafb9) {
          return private_inline_f_utf_character_handle_digit(sequence, 0xf09fafb0, value);
        }
      }
    }

    if (value) {
      *value = F_type_size_max_64_unsigned_d;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_digit_for_ascii(const f_char_t character, uint64_t * const value) {

    if (isdigit(character)) {
      if (value) {
        if (character == f_string_ascii_0_s.string[0]) {
          *value = 0;
        }
        else if (character == f_string_ascii_1_s.string[0]) {
          *value = 1;
        }
        else if (character == f_string_ascii_2_s.string[0]) {
          *value = 2;
        }
        else if (character == f_string_ascii_3_s.string[0]) {
          *value = 3;
        }
        else if (character == f_string_ascii_4_s.string[0]) {
          *value = 4;
        }
        else if (character == f_string_ascii_5_s.string[0]) {
          *value = 5;
        }
        else if (character == f_string_ascii_6_s.string[0]) {
          *value = 6;
        }
        else if (character == f_string_ascii_7_s.string[0]) {
          *value = 7;
        }
        else if (character == f_string_ascii_8_s.string[0]) {
          *value = 8;
        }
        else if (character == f_string_ascii_9_s.string[0]) {
          *value = 9;
        }
        else if (character == f_string_ascii_a_s.string[0] || character == f_string_ascii_A_s.string[0]) {
          *value = 10;
        }
        else if (character == f_string_ascii_b_s.string[0] || character == f_string_ascii_B_s.string[0]) {
          *value = 11;
        }
        else if (character == f_string_ascii_c_s.string[0] || character == f_string_ascii_C_s.string[0]) {
          *value = 12;
        }
        else if (character == f_string_ascii_d_s.string[0] || character == f_string_ascii_D_s.string[0]) {
          *value = 13;
        }
        else if (character == f_string_ascii_e_s.string[0] || character == f_string_ascii_E_s.string[0]) {
          *value = 14;
        }
        else if (character == f_string_ascii_f_s.string[0] || character == f_string_ascii_F_s.string[0]) {
          *value = 15;
        }
        else {
          *value = F_type_size_max_64_unsigned_d;
        }
      }

      return F_true;
    }

    if (value) {
      *value = F_type_size_max_64_unsigned_d;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

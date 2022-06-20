#include "utf.h"
#include "private-utf.h"
#include "private-utf_decimal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Inline helper function to reduce amount of code typed.
 *
 * Given the value, this will conditionally convert the range into an appropriate base-10 integer.
 *
 * This does not handle non-decimal values (non-base-10).
 *
 * @param sequence
 *   The character sequence to process.
 * @param always
 *   The always return F_true boolean.
 * @param start
 *   An inclusive start range.
 *   The stop range is determined from this.
 * @param value
 *   The value to update, if non-NULL.
 *
 * @return
 *   F_true for valid digit in the requested range.
 *   F_false, otherwise.
 */
static inline f_status_t private_inline_f_utf_character_handle_decimal(const f_utf_char_t sequence, const bool always, const f_utf_char_t start, uint32_t * const value) {

  if (value) {
    f_char_t ascii = 0;

    if (macro_f_utf_char_t_width(sequence) == 2) {
      ascii = (f_char_t) macro_f_utf_char_t_to_char_2(sequence - start);
    }
    else if (macro_f_utf_char_t_width(sequence) == 3) {
      ascii = (f_char_t) macro_f_utf_char_t_to_char_3(sequence - start);
    }
    else if (macro_f_utf_char_t_width(sequence) == 4) {
      ascii = (f_char_t) macro_f_utf_char_t_to_char_4(sequence - start);
    }

    ascii += 0x30;

    return private_f_utf_character_is_decimal_for_ascii(ascii, always, value);
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
 * @param always
 *   The always return F_true boolean.
 * @param start
 *   An inclusive start range.
 *   The stop range is determined from this.
 * @param value
 *   The value to update, if non-NULL.
 *
 * @return
 *   F_true for valid digit in the requested range.
 *   F_false, otherwise.
 */
static inline f_status_t private_inline_f_utf_character_handle_roman_numeral(const f_utf_char_t sequence, const bool always, const f_utf_char_t start, uint32_t * const value) {

  if (value) {
    const f_char_t ascii = ((f_char_t) macro_f_utf_char_t_to_char_3(sequence - start)) + 0x31;

    return private_f_utf_character_is_decimal_for_ascii(ascii, always, value);
  }

  return F_true;
}

#if !defined(_di_f_utf_character_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_decimal_) || !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)
  f_status_t private_f_utf_character_is_decimal(const f_utf_char_t sequence, const bool always, uint32_t * const value) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Arabic: U+0660 to U+0669.
      if (sequence >= 0xd9a00000 && sequence <= 0xd9a90000) {
        return private_inline_f_utf_character_handle_decimal(sequence, always, 0xd9a00000, value);
      }

      // Extended Arabic: U+06F0 to U+06F9.
      if (sequence >= 0xdbb00000 && sequence <= 0xdbb90000) {
        return private_inline_f_utf_character_handle_decimal(sequence, always, 0xdbb00000, value);
      }

      // NKo: U+07C0 to U+07C9.
      if (sequence >= 0xdf800000 && sequence <= 0xdf890000) {
        return private_inline_f_utf_character_handle_decimal(sequence, always, 0xdf800000, value);
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Devanagari: U+0966 to U+096F.
        if (sequence >= 0xe0a5a600 && sequence <= 0xe0a5af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0a5a600, value);
        }

        // Bengali: U+09E6 to U+09EF.
        if (sequence >= 0xe0a7a600 && sequence <= 0xe0a7af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0a7a600, value);
        }

        // Gurmukhi: U+0A66 to U+0A6F.
        if (sequence >= 0xe0a9a600 && sequence <= 0xe0a9af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0a9a600, value);
        }

        // Gujarati: U+0AE6 to U+0AEF.
        if (sequence >= 0xe0aba600 && sequence <= 0xe0abaf00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0aba600, value);
        }

        // Oriya: U+0B66 to U+0B6F.
        if (sequence >= 0xe0ada600 && sequence <= 0xe0adaf00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0ada600, value);
        }

        // Tamil: U+0BE6 to U+0BEF.
        if (sequence >= 0xe0afa600 && sequence <= 0xe0afaf00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0afa600, value);
        }

        // Telugu: U+0C66 to U+0C6F.
        if (sequence >= 0xe0b1a600 && sequence <= 0xe0b1af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0b1a600, value);
        }

        // Kannada: U+0CE6 to U+0CEF.
        if (sequence >= 0xe0b3a600 && sequence <= 0xe0b3af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0b3a600, value);
        }

        // Malayalam: U+0D66 to U+0D6F.
        if (sequence >= 0xe0b5a600 && sequence <= 0xe0b5af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0b5a600, value);
        }

        // Sinhala: U+0DE6 to U+0DEF.
        if (sequence >= 0xe0b7a600 && sequence <= 0xe0b7af00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0b7a600, value);
        }

        // Thai: U+0E50 to U+0E59.
        if (sequence >= 0xe0b99000 && sequence <= 0xe0b99900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0b99000, value);
        }

        // Lao: U+0ED0 to U+0ED9.
        if (sequence >= 0xe0bb9000 && sequence <= 0xe0bb9900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0bb9000, value);
        }

        // Tibetan: U+0F20 to U+0F29.
        if (sequence >= 0xe0bca000 && sequence <= 0xe0bca900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe0bca000, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Myanmar: U+1040 to U+1049.
        if (sequence >= 0xe1818000 && sequence <= 0xe1818900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1818000, value);
        }

        // Myanmar (Shan): U+1090 to U+1099.
        if (sequence >= 0xe1829000 && sequence <= 0xe1829900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1829000, value);
        }

        // Khmer: U+17E0 to U+17E9.
        if (sequence >= 0xe19fa000 && sequence <= 0xe19fa900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe19fa000, value);
        }

        // Mongolian: U+1810 to U+1819.
        if (sequence >= 0xe1a09000 && sequence <= 0xe1a09900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1a09000, value);
        }

        // Limbu: U+1946 to U+194F.
        if (sequence >= 0xe1a58600 && sequence <= 0xe1a58f00) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1a58600, value);
        }

        // New Tai Lue: U+19D0 to U+19D9.
        if (sequence >= 0xe1a79000 && sequence <= 0xe1a79900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1a79000, value);
        }

        // Tai Tham (Hora): U+1A80 to U+1A89.
        if (sequence >= 0xe1aa8000 && sequence <= 0xe1aa8900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1aa8000, value);
        }

        // Tai Tham (Tham): U+1A90 to U+1A99.
        if (sequence >= 0xe1aa9000 && sequence <= 0xe1aa9900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1aa9000, value);
        }

        // Balinese: U+1B50 to U+1B59.
        if (sequence >= 0xe1ad9000 && sequence <= 0xe1ad9900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1ad9000, value);
        }

        // Sundanese: U+1BB0 to U+1BB9.
        if (sequence >= 0xe1aeb000 && sequence <= 0xe1aeb900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1aeb000, value);
        }

        // Lepcha: U+1C40 to U+1C49.
        if (sequence >= 0xe1b18000 && sequence <= 0xe1b18900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1b18000, value);
        }

        // Ol Chiki: U+1C50 to U+1C59.
        if (sequence >= 0xe1b19000 && sequence <= 0xe1b19900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xe1b19000, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // Number Forms (Roman Numerals): U+2160 to U+2188.
        if (sequence >= 0xe285a000 && sequence <= 0xe2868800) {

          // Roman Numerals (large) for 1-9: U+2160 to U+2168.
          if (sequence >= 0xe285a000 && sequence <= 0xe285a800) {
            return private_inline_f_utf_character_handle_roman_numeral(sequence, always, 0xe285a000, value);
          }

          // Roman Numerals (small) for 1-9: U+2170 to U+2178.
          if (sequence >= 0xe285b000 && sequence <= 0xe285b800) {
            return private_inline_f_utf_character_handle_roman_numeral(sequence, always, 0xe285b000, value);
          }

          // Roman Numeral (late form) for 6: U+2185.
          if (!value || *value > 5) {
            if (sequence == 0xe2868500) {
              *value = 6;

              return F_true;
            }
          }

          if (value) {
            if (*value > 9) {

              // Roman Numeral: U+2169, U+2179.
              if (sequence == 0xe285a900 || sequence == 0xe285b900) {
                *value = 10;

                return F_true;
              }

              if (*value > 10) {

                // Roman Numeral: U+216A, U+217A.
                if (sequence == 0xe285aa00 || sequence == 0xe285ba00) {
                  *value = 11;

                  return F_true;
                }

                if (*value > 11) {

                  // Roman Numeral: U+216B, U+217B.
                  if (sequence == 0xe285ab00 || sequence == 0xe285bb00) {
                    *value = 12;

                    return F_true;
                  }

                  // All remaining are out of the range 0-16 and value must be set to 0xffff for them to be processed.
                  if (*value == F_type_size_max_32_unsigned_d) {

                    // Roman Numeral: U+216C, U+217C, U+2186.
                    if (sequence == 0xe285ac00 || sequence == 0xe285bc00 || sequence == 0xe2868600) {
                      *value = 50;

                      return F_true;
                    }

                    // Roman Numeral: U+216D, U+217D, U+2183 (reversed, large), U+2184 (reversed, small).
                    if (sequence == 0xe285ad00 || sequence == 0xe285bd00 || sequence == 0xe2868300 || sequence == 0xe2868400) {
                      *value = 100;

                      return F_true;
                    }

                    // Roman Numeral: U+216E, U+217E.
                    if (sequence == 0xe285ae00 || sequence == 0xe285be00) {
                      *value = 500;

                      return F_true;
                    }

                    // Roman Numeral: U+216F, U+217F, U+2180 (1000 "CD").
                    if (sequence == 0xe285af00 || sequence == 0xe285bf00 || sequence == 0xe2868000) {
                      *value = 1000;

                      return F_true;
                    }

                    // Roman Numeral: U+2181.
                    if (sequence == 0xe2868100) {
                      *value = 5000;

                      return F_true;
                    }

                    // Roman Numeral: U+2182.
                    if (sequence == 0xe2868200) {
                      *value = 10000;

                      return F_true;
                    }

                    // Roman Numeral: U+2187.
                    if (sequence == 0xe2868700) {
                      *value = 50000;

                      return F_true;
                    }

                    // Roman Numeral: U+2188.
                    if (sequence == 0xe2868800) {
                      *value = 100000;

                      return F_true;
                    }
                  }
                }
              }
            }

            *value = F_type_size_max_32_unsigned_d;
          }

          if (always) {
            return F_true;
          }
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Vai: U+A620 to U+A629.
        if (sequence >= 0xea98a000 && sequence <= 0xea98a900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xea98a000, value);
        }

        // Saurashtra: U+A8D0 to U+A8D9.
        if (sequence >= 0xeaa39000 && sequence <= 0xeaa39900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xeaa39000, value);
        }

        // Kayah Li: U+A900 to U+A909.
        if (sequence >= 0xeaa48000 && sequence <= 0xeaa48900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xeaa48000, value);
        }

        // Javanese: U+A9D0 to U+A9D9.
        if (sequence >= 0xeaa79000 && sequence <= 0xeaa79900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xeaa79000, value);
        }

        // Myanmar Extended-B: U+A9F0 to U+A9F9.
        if (sequence >= 0xeaa7b000 && sequence <= 0xeaa7b900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xeaa7b000, value);
        }

        // Cham: U+AA50 to U+AA59.
        if (sequence >= 0xeaa99000 && sequence <= 0xeaa99900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xeaa99000, value);
        }

        // Meetei Mayek: U+ABF0 to U+ABF9.
        if (sequence >= 0xeaafb000 && sequence <= 0xeaafb900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xeaafb000, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // Halfwidth and Fullwidth Forms: U+FF10 to U+FF19.
        if (sequence >= 0xefbc9000 && sequence <= 0xefbc9900) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xefbc9000, value);
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(sequence) == 0x90) {

        // Osmanya: U+104A0 to U+104A9.
        if (sequence >= 0xf09092a0 && sequence <= 0xf09092a9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09092a0, value);
        }

        // Hanifi Rohingya: U+10D30 to U+10D39.
        if (sequence >= 0xf090b4b0 && sequence <= 0xf090b4b9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf090b4b0, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Brahmi: U+11066 to U+1106F.
        if (sequence >= 0xf09181a6 && sequence <= 0xf09181af) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09181a6, value);
        }

        // Sora Sompeng: U+110F0 to U+110F9.
        if (sequence >= 0xf09183b0 && sequence <= 0xf09183b9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09183b0, value);
        }

        // Chakma: U+11136 to U+1113F.
        if (sequence >= 0xf09184b6 && sequence <= 0xf09184bf) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09184b6, value);
        }

        // Sharada: U+111D0 to U+111D9.
        if (sequence >= 0xf0918790 && sequence <= 0xf0918799) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0918790, value);
        }

        // Khudawadi: U+112F0 to U+112F9.
        if (sequence >= 0xf0918bb0 && sequence <= 0xf0918bb9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0918bb0, value);
        }

        // Newa: U+11450 to U+11459.
        if (sequence >= 0xf0919190 && sequence <= 0xf0919199) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0919190, value);
        }

        // Tirhuta: U+114D0 to U+114D9.
        if (sequence >= 0xf0919390 && sequence <= 0xf0919399) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0919390, value);
        }

        // Modi: U+11650 to U+11659.
        if (sequence >= 0xf0919990 && sequence <= 0xf0919999) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0919990, value);
        }

        // Takri: U+116C0 to U+116C9.
        if (sequence >= 0xf0919b80 && sequence <= 0xf0919b89) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0919b80, value);
        }

        // Ahom: U+11730 to U+11739.
        if (sequence >= 0xf0919cb0 && sequence <= 0xf0919cb9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf0919cb0, value);
        }

        // Warang Citi: U+118E0 to U+118E9.
        if (sequence >= 0xf091a3a0 && sequence <= 0xf091a3a9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf091a3a0, value);
        }

        // Dives Akuru: U+11950 to U+11959.
        if (sequence >= 0xf091a590 && sequence <= 0xf091a599) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf091a590, value);
        }

        // Bhaiksuki: U+11C50 to U+11C59.
        if (sequence >= 0xf091b190 && sequence <= 0xf091b199) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf091b190, value);
        }

        // Masaram Gondi: U+11D50 to U+11D59.
        if (sequence >= 0xf091b590 && sequence <= 0xf091b599) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf091b590, value);
        }

        // Gunjala Gondi: U+11DA0 to U+11DA9.
        if (sequence >= 0xf091b6a0 && sequence <= 0xf091b6a9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf091b6a0, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x96) {

        // Mro: U+16A60 to U+16A69.
        if (sequence >= 0xf096a9a0 && sequence <= 0xf096a9a9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf096a9a0, value);
        }

        // Tangsa: U+16AC0 to U+16AC9.
        if (sequence >= 0xf096ab80 && sequence <= 0xf096ab89) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf096ab80, value);
        }

        // Pahawh Hmong: U+16B50 to U+16B59.
        if (sequence >= 0xf096ad90 && sequence <= 0xf096ad99) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf096ad90, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

        // Mathematical Alphanumeric (Bold) Symbols: U+1D7CE to U+1D7D7.
        if (sequence >= 0xf09d9f8e && sequence <= 0xf09d9f97) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09d9f8e, value);
        }

        // Mathematical Alphanumeric (Double-Struck) Symbols: U+1D7D8 to U+1D7E1.
        if (sequence >= 0xf09d9f98 && sequence <= 0xf09d9fa1) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09d9f98, value);
        }

        // Mathematical Alphanumeric (Sans-Serif) Symbols: U+1D7E2 to U+1D7EB.
        if (sequence >= 0xf09d9fa2 && sequence <= 0xf09d9fab) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09d9fa2, value);
        }

        // Mathematical Alphanumeric (Sans-Serif Bold) Symbols: U+1D7EC to U+1D7F5.
        if (sequence >= 0xf09d9fac && sequence <= 0xf09d9fb5) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09d9fac, value);
        }

        // Mathematical Alphanumeric (Monospace) Symbols: U+1D7F6 to U+1D7FF.
        if (sequence >= 0xf09d9fb6 && sequence <= 0xf09d9fbf) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09d9fb6, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9e) {

        // Nyiakeng Puachue Hmong: U+1E140 to U+1E149.
        if (sequence >= 0xf09e8580 && sequence <= 0xf09e8589) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09e8580, value);
        }

        // Wancho: U+1E2F0 to U+1E2F9.
        if (sequence >= 0xf09e8bb0 && sequence <= 0xf09e8bb9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09e8bb0, value);
        }

        // Adlam: U+1E950 to U+1E959.
        if (sequence >= 0xf09ea590 && sequence <= 0xf09ea599) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09ea590, value);
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Symbols for Legacy Computing (Segmented): U+1FBF0 to U+1FBF9.
        if (sequence >= 0xf09fafb0 && sequence <= 0xf09fafb9) {
          return private_inline_f_utf_character_handle_decimal(sequence, always, 0xf09fafb0, value);
        }
      }
    }

    if (value) {
      *value = F_type_size_max_32_unsigned_d;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_decimal_) || !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)

#if !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)
  f_status_t private_f_utf_character_is_decimal_for_ascii(const f_char_t character, const bool always, uint32_t * const value) {

    if (always) {
      if (isdigit(character)) {
        if (value) {
          if (character == f_string_ascii_0_s.string[0]) {
            *value = 0;

            return F_true;
          }
          else if (character == f_string_ascii_1_s.string[0]) {
            if (!*value || *value > 1) {
              *value = 1;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_2_s.string[0]) {
            if (!*value || *value > 2) {
              *value = 2;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_3_s.string[0]) {
            if (!*value || *value > 3) {
              *value = 3;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_4_s.string[0]) {
            if (!*value || *value > 4) {
              *value = 4;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_5_s.string[0]) {
            if (!*value || *value > 5) {
              *value = 5;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_6_s.string[0]) {
            if (!*value || *value > 6) {
              *value = 6;

              return F_true;
            }
          }
          else if (character == f_string_ascii_7_s.string[0]) {
            if (!*value || *value > 7) {
              *value = 7;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_8_s.string[0]) {
            if (!*value || *value > 8) {
              *value = 8;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }
          else if (character == f_string_ascii_9_s.string[0]) {
            if (!*value || *value > 9) {
              *value = 9;
            }
            else {
              *value = F_type_size_max_32_unsigned_d;
            }

            return F_true;
          }

          if (*value > 10) {
            if (character == f_string_ascii_a_s.string[0] || character == f_string_ascii_A_s.string[0]) {
              *value = 10;

              return F_true;
            }

            if (*value > 11) {
              if (character == f_string_ascii_b_s.string[0] || character == f_string_ascii_B_s.string[0]) {
                *value = 11;

                return F_true;
              }

              if (*value > 12) {
                if (character == f_string_ascii_c_s.string[0] || character == f_string_ascii_C_s.string[0]) {
                  *value = 12;

                  return F_true;
                }

                if (*value > 13) {
                  if (character == f_string_ascii_d_s.string[0] || character == f_string_ascii_D_s.string[0]) {
                    *value = 13;

                    return F_true;
                  }

                  if (*value > 14) {
                    if (character == f_string_ascii_e_s.string[0] || character == f_string_ascii_E_s.string[0]) {
                      *value = 14;

                      return F_true;
                    }

                    if (*value > 15) {
                      if (character == f_string_ascii_f_s.string[0] || character == f_string_ascii_F_s.string[0]) {
                        *value = 15;

                        return F_true;
                      }
                    }
                  }
                }
              }
            }
          }

          *value = F_type_size_max_32_unsigned_d;
        }

        return F_true;
      }

      return F_false;
    }

    if (isdigit(character)) {
      if (value) {
        if (character == f_string_ascii_0_s.string[0]) {
          *value = 0;

          return F_true;
        }

        if (character == f_string_ascii_1_s.string[0]) {
          if (!*value || *value > 1) {
            *value = 1;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_2_s.string[0]) {
          if (!*value || *value > 2) {
            *value = 2;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_3_s.string[0]) {
          if (!*value || *value > 3) {
            *value = 3;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_4_s.string[0]) {
          if (!*value || *value > 4) {
            *value = 4;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_5_s.string[0]) {
          if (!*value || *value > 5) {
            *value = 5;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_6_s.string[0]) {
          if (!*value || *value > 6) {
            *value = 6;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_7_s.string[0]) {
          if (!*value || *value > 7) {
            *value = 7;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_8_s.string[0]) {
          if (!*value || *value > 8) {
            *value = 8;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (character == f_string_ascii_9_s.string[0]) {
          if (!*value || *value > 9) {
            *value = 9;

            return F_true;
          }

          *value = F_type_size_max_32_unsigned_d;

          return F_false;
        }

        if (*value > 10) {
          if (character == f_string_ascii_a_s.string[0] || character == f_string_ascii_A_s.string[0]) {
            *value = 10;

            return F_true;
          }

          if (*value > 11) {
            if (character == f_string_ascii_b_s.string[0] || character == f_string_ascii_B_s.string[0]) {
              *value = 11;

              return F_true;
            }

            if (*value > 12) {
              if (character == f_string_ascii_c_s.string[0] || character == f_string_ascii_C_s.string[0]) {
                *value = 12;

                return F_true;
              }

              if (*value > 13) {
                if (character == f_string_ascii_d_s.string[0] || character == f_string_ascii_D_s.string[0]) {
                  *value = 13;

                  return F_true;
                }

                if (*value > 14) {
                  if (character == f_string_ascii_e_s.string[0] || character == f_string_ascii_E_s.string[0]) {
                    *value = 14;

                    return F_true;
                  }

                  if (*value > 15) {
                    if (character == f_string_ascii_f_s.string[0] || character == f_string_ascii_F_s.string[0]) {
                      *value = 15;

                      return F_true;
                    }
                  }
                }
              }
            }
          }
        }

        *value = F_type_size_max_32_unsigned_d;

        return F_false;
      }

      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)

#ifdef __cplusplus
} // extern "C"
#endif

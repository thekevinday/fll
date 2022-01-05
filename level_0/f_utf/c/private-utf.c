#include "utf.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alpha_) || !defined(_di_f_utf_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_surrogate_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)
  f_status_t private_f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_character_t *character_utf) {

    if (!macro_f_utf_byte_width_is(*character)) {
      *character_utf = macro_f_utf_character_t_from_char_1(character[0]);

      return F_none;
    }

    if (macro_f_utf_byte_width_is(*character) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    if (macro_f_utf_byte_width_is(*character) > width_max) {
      return F_status_set_error(F_failure);
    }

    *character_utf = macro_f_utf_character_t_from_char_1(character[0]);

    if (macro_f_utf_byte_width_is(*character) < 2) {
      return F_none;
    }

    *character_utf |= macro_f_utf_character_t_from_char_2(character[1]);

    if (macro_f_utf_byte_width_is(*character) == 2) {
      return F_none;
    }

    *character_utf |= macro_f_utf_character_t_from_char_3(character[2]);

    if (macro_f_utf_byte_width_is(*character) == 3) {
      return F_none;
    }

    *character_utf |= macro_f_utf_character_t_from_char_4(character[3]);

    return F_none;
  }
#endif // !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alpha_) || !defined(_di_f_utf_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_surrogate_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)

#if !defined(_di_f_utf_character_is_alpha_) || !defined(_di_f_utf_is_alpha_)
  f_status_t private_f_utf_character_is_alpha(const f_utf_character_t character) {

    if (private_f_utf_character_is_zero_width(character)) {
      return F_false;
    }

    // is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_combining(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_numeric(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(character)) {
      return F_false;
    }

    return F_true;
  }
#endif // !defined(_di_f_utf_character_is_alpha_) || !defined(_di_f_utf_is_alpha_)

#if !defined(_di_f_utf_character_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_digit_)
  f_status_t private_f_utf_character_is_alpha_digit(const f_utf_character_t character) {

    if (private_f_utf_character_is_digit(character)) {
      return F_true;
    }

    if (private_f_utf_character_is_zero_width(character)) {
      return F_false;
    }

    // is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_numeric(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(character)) {
      return F_false;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_digit_)

#if !defined(_di_f_utf_character_is_alpha_numeric_) || !defined(_di_f_utf_is_alpha_numeric_)
  f_status_t private_f_utf_character_is_alpha_numeric(const f_utf_character_t character) {

    if (private_f_utf_character_is_numeric(character)) {
      return F_true;
    }

    if (private_f_utf_character_is_zero_width(character)) {
      return F_false;
    }

    // is_control() handles both is_control_code() and is_control_format().
    if (private_f_utf_character_is_control(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_control_picture(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_whitespace_modifier(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_punctuation(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_symbol(character)) {
      return F_false;
    }

    if (private_f_utf_character_is_phonetic(character)) {
      return F_false;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alpha_numeric_) || !defined(_di_f_utf_is_alpha_numeric_)

#if !defined(_di_f_utf_character_is_ascii_) || !defined(_di_f_utf_is_ascii_)
  f_status_t private_f_utf_character_is_ascii(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) < 2) {
      if (macro_f_utf_character_t_to_char_1(character) >= 0x00 && macro_f_utf_character_t_to_char_1(character) <= 0x7f) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_ascii_) || !defined(_di_f_utf_is_ascii_)

#if !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)
  f_status_t private_f_utf_character_is_combining(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Diacritical Marks: U+0300 to U+036F.
      if (character >= 0xcc800000 && character <= 0xcdaf0000) {
        return F_true;
      }

      // Cyrillic: U+0483 to U+0489.
      if (character >= 0xd2830000 && character <= 0xd2890000) {
        return F_true;
      }

      // Hebrew: U+0591 to U+05BD.
      if (character >= 0xd6910000 && character <= 0xd6bd0000) {
        return F_true;
      }

      // Hebrew: U+05C1 to U+05C7.
      if (character >= 0xd7810000 && character <= 0xd7870000) {
        return F_true;
      }

      // Arabic: U+0610 to U+061A.
      if (character >= 0xd8900000 && character <= 0xd89a0000) {
        return F_true;
      }

      // Arabic: U+064B to U+065F.
      if (character >= 0xd98b0000 && character <= 0xd99f0000) {
        return F_true;
      }

      // Arabic: U+0670.
      if (character == 0xd9b00000) {
        return F_true;
      }

      // Arabic: U+06D6 to U+06DC.
      if (character >= 0xdb960000 && character <= 0xdb9c0000) {
        return F_true;
      }

      // Arabic: U+06D6 to U+06DC.
      if (character >= 0xdb960000 && character <= 0xdb9c0000) {
        return F_true;
      }

      // Arabic: U+06DF to U+06E4.
      if (character >= 0xdb9f0000 && character <= 0xdba40000) {
        return F_true;
      }

      // Arabic: U+06E7 to U+06E8.
      if (character >= 0xdba70000 && character <= 0xdba80000) {
        return F_true;
      }

      // Arabic: U+06EA to U+06ED.
      if (character >= 0xdbaa0000 && character <= 0xdbad0000) {
        return F_true;
      }

      // Syriac: U+0711.
      if (character == 0xdc910000) {
        return F_true;
      }

      // Syriac: U+0730 to U+074A.
      if (character >= 0xdcb00000 && character <= 0xdd8a0000) {
        return F_true;
      }

      // Thaana: U+07A6 to U+07B0.
      if (character >= 0xdea60000 && character <= 0xdeb00000) {
        return F_true;
      }

      // NKo: U+07EB to U+07F3.
      if (character >= 0xdfab0000 && character <= 0xdfb30000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // Samaritan: U+0816 to U+0819.
      if (character >= 0xe0a09600 && character <= 0xe0a09900) {
        return F_true;
      }

      // Samaritan: U+081B to U+0823.
      if (character >= 0xe0a09b00 && character <= 0xe0a0a300) {
        return F_true;
      }

      // Samaritan: U+0825 to U+0827.
      if (character >= 0xe0a0a500 && character <= 0xe0a0a700) {
        return F_true;
      }

      // Samaritan: U+0829.
      if (character == 0xe0a0a900) {
        return F_true;
      }

      // Samaritan: U+082A to U+082D.
      if (character >= 0xe0a0aa00 && character <= 0xe0a0ad00) {
        return F_true;
      }

      // Mandaic: U+0859 to U+085B.
      if (character >= 0xe0a19900 && character <= 0xe0a19b00) {
        return F_true;
      }

      // Arabic Extended-A: U+08E3 to U+0902.
      if (character >= 0xe0a3a300 && character <= 0xe0a48200) {
        return F_true;
      }

      // Devanagari: U+093A, U+093C.
      if (character == 0xe0a4ba00 || character == 0xe0a4bc00) {
        return F_true;
      }

      // Devanagari: U+0941 to U+0948.
      if (character >= 0xe0a58100 && character <= 0xe0a58800) {
        return F_true;
      }

      // Devanagari: U+094D.
      if (character == 0xe0a58d00) {
        return F_true;
      }

      // Devanagari: U+0951 to U+0957.
      if (character >= 0xe0a59100 && character <= 0xe0a59700) {
        return F_true;
      }

      // Devanagari: U+0962 to U+0963.
      if (character >= 0xe0a5a200 && character <= 0xe0a5a300) {
        return F_true;
      }

      // Bengali: U+0981, U+09BC.
      if (character == 0xe0a68100 || character == 0xe0a6bc00) {
        return F_true;
      }

      // Bengali: U+09C1 to U+09C4.
      if (character >= 0xe0a78100 && character <= 0xe0a78400) {
        return F_true;
      }

      // Bengali: U+09CD.
      if (character == 0xe0a78d00) {
        return F_true;
      }

      // Bengali: U+09E2 to U+09E3.
      if (character >= 0xe0a7a200 && character <= 0xe0a7a300) {
        return F_true;
      }

      // Gurmukhi: U+0A01 to U+0A02.
      if (character >= 0xe0a88100 && character <= 0xe0a88200) {
        return F_true;
      }

      // Gurmukhi: U+0A3C.
      if (character == 0xe0a8bc00) {
        return F_true;
      }

      // Gurmukhi: U+0A41 to U+0A42.
      if (character >= 0xe0a98100 && character <= 0xe0a98200) {
        return F_true;
      }

      // Gurmukhi: U+0A47 to U+0A48.
      if (character >= 0xe0a98700 && character <= 0xe0a98800) {
        return F_true;
      }

      // Gurmukhi: U+0A4B to U+0A4D.
      if (character >= 0xe0a98b00 && character <= 0xe0a98d00) {
        return F_true;
      }

      // Gurmukhi: U+0A51.
      if (character == 0xe0a99100) {
        return F_true;
      }

      // Gurmukhi: U+0A70 to U+0A71.
      if (character >= 0xe0a9b000 && character <= 0xe0a9b100) {
        return F_true;
      }

      // Gurmukhi: U+0A75.
      if (character == 0xe0a9b500) {
        return F_true;
      }

      // Gujarati: U+0A81 to U+0A82.
      if (character >= 0xe0aa8100 && character <= 0xe0aa8200) {
        return F_true;
      }

      // Gujarati: U+0ABC.
      if (character == 0xe0aabc00) {
        return F_true;
      }

      // Gujarati: U+0AC1 to U+0AC5.
      if (character >= 0xe0ab8100 && character <= 0xe0ab8500) {
        return F_true;
      }

      // Gujarati: U+0AC7 to U+0AC8.
      if (character >= 0xe0ab8700 && character <= 0xe0ab8800) {
        return F_true;
      }

      // Gujarati: U+0ACD.
      if (character == 0xe0ab8d00) {
        return F_true;
      }

      // Gujarati: U+0AE2 to U+0AE3.
      if (character >= 0xe0aba200 && character <= 0xe0aba300) {
        return F_true;
      }

      // Oriya: U+0B01, U+0B3C, U+0B3F.
      if (character == 0xe0ac8100 || character == 0xe0acbc00 || character == 0xe0acbf00) {
        return F_true;
      }

      // Oriya: U+0B41 to U+0B44.
      if (character >= 0xe0ad8100 && character <= 0xe0ad8400) {
        return F_true;
      }

      // Oriya: U+0B4D, U+0B56, U+0B62, U+0B63.
      if (character == 0xe0ad8d00 || character == 0xe0ad9600 || character == 0xe0ada200 || character == 0xe0ada300) {
        return F_true;
      }

      // Tamil: U+0BC0, U+0BCD.
      if (character == 0xe0af8000 || character == 0xe0af8d00) {
        return F_true;
      }

      // Telugu: U+0C00.
      if (character == 0xe0b08000) {
        return F_true;
      }

      // Telugu: U+0C3E to U+0C40.
      if (character >= 0xe0b0be00 && character <= 0xe0b18000) {
        return F_true;
      }

      // Telugu: U+0C46 to U+0C48.
      if (character >= 0xe0b18600 && character <= 0xe0b18800) {
        return F_true;
      }

      // Telugu: U+0C4A to U+0C4D.
      if (character >= 0xe0b18a00 && character <= 0xe0b18d00) {
        return F_true;
      }

      // Telugu: U+0C55, U+0C56, U+0C62, U+0C63.
      if (character == 0xe0b19500 || character == 0xe0b19600 || character == 0xe0b1a200 || character == 0xe0b1a300) {
        return F_true;
      }

      // Kannada: U+0C81.
      if (character == 0xe0b28100) {
        return F_true;
      }

      // Kannada: U+0CBC to U+0CCD.
      if (character >= 0xe0b2bc00 && character <= 0xe0b38d00) {
        return F_true;
      }

      // Kannada: U+0CE2, U+0CE3.
      if (character == 0xe0b3a200 || character == 0xe0b3a300) {
        return F_true;
      }

      // Malayalam: U+0D01.
      if (character == 0xe0b48100) {
        return F_true;
      }

      // Malayalam: U+0D41 to U+0D44.
      if (character >= 0xe0b58100 && character <= 0xe0b58400) {
        return F_true;
      }

      // Malayalam: U+0D4D, U+0D62, U+0D63.
      if (character == 0xe0b58d00 || character == 0xe0b5a200 || character == 0xe0b5a300) {
        return F_true;
      }

      // Sinhala: U+0DCA.
      if (character == 0xe0b78a00) {
        return F_true;
      }

      // Sinhala: U+0DD2 to U+0DD4.
      if (character >= 0xe0b79200 && character <= 0xe0b79400) {
        return F_true;
      }

      // Sinhala: U+0DD6.
      if (character == 0xe0b79600) {
        return F_true;
      }

      // Thai: U+0E31.
      if (character == 0xe0b8b100) {
        return F_true;
      }

      // Thai: U+0E34 to U+0E3A.
      if (character >= 0xe0b8b400 && character <= 0xe0b8ba00) {
        return F_true;
      }

      // Thai: U+0E47 to U+0E4E.
      if (character >= 0xe0b98700 && character <= 0xe0b98e00) {
        return F_true;
      }

      // Lao: U+0EB1.
      if (character == 0xe0bab100) {
        return F_true;
      }

      // Lao: U+0EB4 to U+0EB9.
      if (character >= 0xe0bab400 && character <= 0xe0bab900) {
        return F_true;
      }

      // Lao: U+0EBB, U+0EBC.
      if (character == 0xe0babb00 || character == 0xe0babc00) {
        return F_true;
      }

      // Tibetan: U+0F18 to U+0F19.
      if (character >= 0xe0bc9800 && character <= 0xe0bc9900) {
        return F_true;
      }

      // Tibetan: U+0F35, U+0F37, U+0F39.
      if (character == 0xe0bcb500 || character == 0xe0bcb700 || character == 0xe0bcb900) {
        return F_true;
      }

      // Tibetan: U+0F71 to U+0F7E.
      if (character >= 0xe0bdb100 && character <= 0xe0bdbe00) {
        return F_true;
      }

      // Tibetan: U+0F80 to U+0F84.
      if (character >= 0xe0be8000 && character <= 0xe0be8400) {
        return F_true;
      }

      // Tibetan: U+0F86 to U+0F87.
      if (character >= 0xe0be8600 && character <= 0xe0be8700) {
        return F_true;
      }

      // Tibetan: U+0F8D to U+0F97.
      if (character >= 0xe0be8d00 && character <= 0xe0be9700) {
        return F_true;
      }

      // Tibetan: U+0F99 to U+0FBC.
      if (character >= 0xe0be9900 && character <= 0xe0bebc00) {
        return F_true;
      }

      // Tibetan: U+0FC6.
      if (character == 0xe0bf8600) {
        return F_true;
      }

      // Myanmar: U+102D to U+1030.
      if (character >= 0xe180ad00 && character <= 0xe180b000) {
        return F_true;
      }

      // Myanmar: U+1039 to U+103A.
      if (character >= 0xe180b900 && character <= 0xe180ba00) {
        return F_true;
      }

      // Myanmar: U+103D to U+103E.
      if (character >= 0xe180bd00 && character <= 0xe180be00) {
        return F_true;
      }

      // Myanmar: U+1058 to U+1059.
      if (character >= 0xe1819800 && character <= 0xe1819900) {
        return F_true;
      }

      // Myanmar: U+105E to U+1060.
      if (character >= 0xe1819e00 && character <= 0xe181a000) {
        return F_true;
      }

      // Myanmar: U+1071 to U+1074.
      if (character >= 0xe181b100 && character <= 0xe181b400) {
        return F_true;
      }

      // Myanmar: U+1082, U+1085, U+1086, U+108D.
      if (character == 0xe1828200 || character == 0xe1828500 || character == 0xe1828600 || character == 0xe1828d00) {
        return F_true;
      }

      // Myanmar: U+109D.
      if (character == 0xe1829d00) {
        return F_true;
      }

      // Ethiopic: U+135D to U+135F.
      if (character >= 0xe18d9d00 && character <= 0xe18d9f00) {
        return F_true;
      }

      // Tagalog: U+1712 to U+1714.
      if (character >= 0xe19c9200 && character <= 0xe19c9400) {
        return F_true;
      }

      // Hanunoo: U+1732 to U+1734.
      if (character >= 0xe19cb200 && character <= 0xe19cb400) {
        return F_true;
      }

      // Buhid: U+1752 to U+1753.
      if (character >= 0xe19d9200 && character <= 0xe19d9300) {
        return F_true;
      }

      // Tagbanwa: U+1772 to U+1773.
      if (character >= 0xe19db200 && character <= 0xe19db300) {
        return F_true;
      }

      // Khmer: U+17B4 to U+17B5.
      if (character >= 0xe19eb400 && character <= 0xe19eb500) {
        return F_true;
      }

      // Khmer: U+17B7 to U+17BD.
      if (character >= 0xe19eb700 && character <= 0xe19ebd00) {
        return F_true;
      }

      // Khmer: U+17C6, U+17C9.
      if (character == 0xe19f8600 || character == 0xe19f8900) {
        return F_true;
      }

      // Khmer: U+17CA to U+17D3.
      if (character >= 0xe19f8a00 && character <= 0xe19f9300) {
        return F_true;
      }

      // Khmer: U+17DD.
      if (character == 0xe19f9d00) {
        return F_true;
      }

      // Mongolian: U+180B to U+180D.
      if (character >= 0xe1a08b00 && character <= 0xe1a08d00) {
        return F_true;
      }

      // Mongolian: U+18A9.
      if (character == 0xe1a2a900) {
        return F_true;
      }

      // Mongolian: U+1920 to U+1922.
      if (character >= 0xe1a4a000 && character <= 0xe1a4a200) {
        return F_true;
      }

      // Limbu: U+1927, U+1928, U+1932.
      if (character == 0xe1a4a700 || character == 0xe1a4a800 || character == 0xe1a4b200) {
        return F_true;
      }

      // Limbu: U+1939 to U+193B.
      if (character >= 0xe1a4b900 && character <= 0xe1a4bb00) {
        return F_true;
      }

      // Buginese: U+1A17 to U+1A18.
      if (character >= 0xe1a89700 && character <= 0xe1a89800) {
        return F_true;
      }

      // Buginese: U+1A1B.
      if (character == 0xe1a89b00) {
        return F_true;
      }

      // Tai Tham: U+1A56.
      if (character == 0xe1a99600) {
        return F_true;
      }

      // Tai Tham: U+1A58 to U+1A5E.
      if (character >= 0xe1a99800 && character <= 0xe1a99e00) {
        return F_true;
      }

      // Tai Tham: U+1A60, U+1A62.
      if (character == 0xe1a9a000 || character == 0xe1a9a200) {
        return F_true;
      }

      // Tai Tham: U+1A65 to U+1A6C.
      if (character >= 0xe1a9a500 && character <= 0xe1a9ac00) {
        return F_true;
      }

      // Tai Tham: U+1A73 to U+1A7C.
      if (character >= 0xe1a9b300 && character <= 0xe1a9bc00) {
        return F_true;
      }

      // Tai Tham: U+1A7F.
      if (character == 0xe1a9bf00) {
        return F_true;
      }

      // Diacritical Marks Extended: U+1AB0 to U+1ACE.
      if (character >= 0xe1aab000 && character <= 0xe1ab8e00) {
        return F_true;
      }

      // Balinese: U+1B00 to U+1B03.
      if (character >= 0xe1ac8000 && character <= 0xe1ac8300) {
        return F_true;
      }

      // Balinese: U+1B34.
      if (character == 0xe1acb400) {
        return F_true;
      }

      // Balinese: U+1B36 to U+1B3A.
      if (character >= 0xe1acb600 && character <= 0xe1acba00) {
        return F_true;
      }

      // Balinese: U+1B3C, U+1B42.
      if (character == 0xe1acbc00 || character == 0xe1ad8200) {
        return F_true;
      }

      // Balinese: U+1B6B to U+1B73.
      if (character >= 0xe1adab00 && character <= 0xe1adb300) {
        return F_true;
      }

      // Sundanese: U+1B80 to U+1B81.
      if (character >= 0xe1ae8000 && character <= 0xe1ae8100) {
        return F_true;
      }

      // Sundanese: U+1BA2 to U+1BA5.
      if (character >= 0xe1aea200 && character <= 0xe1aea500) {
        return F_true;
      }

      // Sundanese: U+1BA8 to U+1BA9.
      if (character >= 0xe1aea800 && character <= 0xe1aea900) {
        return F_true;
      }

      // Sundanese: U+1BAB to U+1BAD.
      if (character >= 0xe1aeab00 && character <= 0xe1aead00) {
        return F_true;
      }

      // Batak: U+1BE6, U+1BE8, U+1BE9, U+1BED.
      if (character == 0xe1afa600 || character == 0xe1afa800 || character == 0xe1afa900 || character == 0xe1afad00) {
        return F_true;
      }

      // Batak: U+1BEF, U+1BF0, U+1BF1.
      if (character == 0xe1afaf00 || character == 0xe1afb000 || character == 0xe1afb100) {
        return F_true;
      }

      // Lepcha: U+1C2C to U+1C33.
      if (character >= 0xe1b0ac00 && character <= 0xe1b0b300) {
        return F_true;
      }

      // Lepcha: U+1C36 to U+1C37.
      if (character >= 0xe1b0b600 && character <= 0xe1b0b700) {
        return F_true;
      }

      // Vedic Extensions: U+1CD4 to U+1CD2.
      if (character >= 0xe1b39400 && character <= 0xe1b39200) {
        return F_true;
      }

      // Vedic Extensions: U+1CD0 to U+1CE0.
      if (character >= 0xe1b39000 && character <= 0xe1b3a000) {
        return F_true;
      }

      // Vedic Extensions: U+1CE2 to U+1CE8.
      if (character >= 0xe1b3a200 && character <= 0xe1b3a800) {
        return F_true;
      }

      // Vedic Extensions: U+1CED, U+1CF4, U+1CF8, U+1CF9.
      if (character == 0xe1b3ad00 || character == 0xe1b3b400 || character == 0xe1b3b800 || character == 0xe1b3b900) {
        return F_true;
      }

      // Vedic Extensions: U+1DC0 to U+1CE8.
      if (character >= 0xe1b78000 && character <= 0xe1b3a800) {
        return F_true;
      }

      // Diacritical Marks Supplement: U+1DC0 to U+1DFF.
      if (character >= 0xe1b78000 && character <= 0xe1b7bf00) {
        return F_true;
      }

      // Diacritical Marks Supplement: U+1DFB to U+1DFF.
      if (character >= 0xe1b7bb00 && character <= 0xe1b7bf00) {
        return F_true;
      }

      // Diacritical Marks For Symbols: U+20D0 to U+20F0.
      if (character >= 0xe2839000 && character <= 0xe283b000) {
        return F_true;
      }

      // Combining Half Marks: U+FE20 to U+FE2F.
      if (character >= 0xefb8a000 && character <= 0xefb8af00) {
        return F_true;
      }

      // CJK Symbols and Punctuation: U+302A to U+302D.
      if (character >= 0xe380aa00 && character <= 0xe380ad00) {
        return F_true;
      }

      // Hiragana: U+3099, U+309A.
      if (character == 0xe3829900 || character == 0xe3829a00) {
        return F_true;
      }

      // Cyrillic Extended-B: U+3099.
      if (character == 0xea99af00) {
        return F_true;
      }

      // Cyrillic Extended-B: U+A66F to U+A672.
      if (character >= 0xea99af00 && character <= 0xea99b200) {
        return F_true;
      }

      // Cyrillic Extended-B: U+A674 to U+A69F.
      if (character >= 0xea99b400 && character <= 0xea9a9f00) {
        return F_true;
      }

      // Bamum: U+A6F0 to U+A6F1.
      if (character >= 0xea9bb000 && character <= 0xea9bb100) {
        return F_true;
      }

      // Syloti Nagri: U+A802, U+A806, U+A80B, U+A825.
      if (character == 0xeaa08200 || character == 0xeaa08600 || character == 0xeaa08b00 || character == 0xeaa0a500) {
        return F_true;
      }

      // Syloti Nagri: U+A826.
      if (character == 0xeaa0a600) {
        return F_true;
      }

      // Saurashtra: U+A8C4.
      if (character == 0xeaa38400) {
        return F_true;
      }

      // Devanagari Extended: U+A6F0 to U+A8F1.
      if (character >= 0xeaa3a000 && character <= 0xeaa3b100) {
        return F_true;
      }

      // Kayah Li: U+A926 to U+A92D.
      if (character >= 0xeaa4a600 && character <= 0xeaa4ad00) {
        return F_true;
      }

      // Rejang: U+A947 to U+A951.
      if (character >= 0xeaa58700 && character <= 0xeaa59100) {
        return F_true;
      }

      // Javanese: U+A980 to U+A982.
      if (character >= 0xeaa68000 && character <= 0xeaa68200) {
        return F_true;
      }

      // Javanese: U+A9B3.
      if (character == 0xeaa6b300) {
        return F_true;
      }

      // Javanese: U+A9B6 to U+A9B9.
      if (character >= 0xeaa6b600 && character <= 0xeaa6b900) {
        return F_true;
      }

      // Javanese: U+A9BC.
      if (character == 0xeaa6bc00) {
        return F_true;
      }

      // Myanmar Extended-B: U+A9E5.
      if (character == 0xeaa7a500) {
        return F_true;
      }

      // Cham: U+AA29 to U+AA2E.
      if (character >= 0xeaa8a900 && character <= 0xeaa8ae00) {
        return F_true;
      }

      // Cham: U+AA31 to U+AA32.
      if (character >= 0xeaa8b100 && character <= 0xeaa8b200) {
        return F_true;
      }

      // Cham: U+AA35 to U+AA36.
      if (character >= 0xeaa8b500 && character <= 0xeaa8b600) {
        return F_true;
      }

      // Cham: U+AA43, U+AA4C.
      if (character == 0xeaa98300 || character == 0xeaa98c00) {
        return F_true;
      }

      // Tai Viet: U+AA7C.
      if (character == 0xeaa9bc00) {
        return F_true;
      }

      // Tai Viet: U+AAB0.
      if (character == 0xeaaab000) {
        return F_true;
      }

      // Tai Viet: U+AAB2 to U+AAB4.
      if (character >= 0xeaaab200 && character <= 0xeaaab400) {
        return F_true;
      }

      // Tai Viet: U+AAB7 to U+AAB8.
      if (character >= 0xeaaab700 && character <= 0xeaaab800) {
        return F_true;
      }

      // Tai Viet: U+AABE to U+AABF.
      if (character >= 0xeaaabe00 && character <= 0xeaaabf00) {
        return F_true;
      }

      // Tai Viet: U+AAC1.
      if (character == 0xeaab8100) {
        return F_true;
      }

      // Meetei Mayek Extensions: U+AAEC, U+AAED, U+AAF6.
      if (character == 0xeaabac00 || character == 0xeaabad00 || character == 0xeaabb600) {
        return F_true;
      }

      // Meetei Mayek: U+ABE5, U+ABE8, U+ABED.
      if (character == 0xeaafa500 || character == 0xeaafa800 || character == 0xeaafad00) {
        return F_true;
      }

      // Alphabetic Presentation Forms: U+FB1E.
      if (character == 0xefac9e00) {
        return F_true;
      }

      // Variation Selectors: U+FE00 to U+FE0F.
      if (character >= 0xefb88000 && character <= 0xefb88f00) {
        return F_true;
      }

      // Variation Selectors: U+FE20 to U+FE0F.
      if (character >= 0xefb88000 && character <= 0xefb88f00) {
        return F_true;
      }

      // Combining Half Marks: U+FE20 to U+FE2F.
      if (character >= 0xefb8a000 && character <= 0xefb8af00) {
        return F_true;
      }

      return F_false;
    }

    // Phaistos Disc: U+101FD.
    if (character == 0xf09087bd) {
      return F_true;
    }

    // Coptic Epact Numbers: U+102E0.
    if (character == 0xf0908ba0) {
      return F_true;
    }

    // Old Permic: U+10376 to U+1037A.
    if (character >= 0xf0908db6 && character <= 0xf0908dba) {
      return F_true;
    }

    // Kharoshthi: U+10A01 to U+10A03.
    if (character >= 0xf090a881 && character <= 0xf090a883) {
      return F_true;
    }

    // Kharoshthi: U+10A01, U+10A03, U+10A05, U+10A06.
    if (character == 0xf090a881 || character == 0xf090a883 || character == 0xf090a885 || character == 0xf090a886) {
      return F_true;
    }

    // Kharoshthi: U+10A0C to U+10A0F.
    if (character >= 0xf090a88c && character <= 0xf090a88f) {
      return F_true;
    }

    // Kharoshthi: U+10A38 to U+10A3A.
    if (character >= 0xf090a8b8 && character <= 0xf090a8ba) {
      return F_true;
    }

    // Kharoshthi: U+10A3F.
    if (character == 0xf090a8bf) {
      return F_true;
    }

    // Manichaean: U+10AE5, U+10AE6.
    if (character == 0xf090aba5 || character == 0xf090aba6) {
      return F_true;
    }

    // Brahmi: U+11001.
    if (character == 0xf0918081) {
      return F_true;
    }

    // Brahmi: U+11038 to U+11046.
    if (character >= 0xf09180b8 && character <= 0xf0918186) {
      return F_true;
    }

    // Brahmi .. Kaithi: U+1107F to U+11081.
    if (character >= 0xf09181bf && character <= 0xf0918281) {
      return F_true;
    }

    // Kaithi: U+110B3 to U+110B6.
    if (character >= 0xf09182b3 && character <= 0xf09182b6) {
      return F_true;
    }

    // Kaithi: U+110B9, U+110BA.
    if (character == 0xf09182b9 || character == 0xf09182ba) {
      return F_true;
    }

    // Chakma: U+11100 to U+11102.
    if (character >= 0xf0918480 && character <= 0xf0918482) {
      return F_true;
    }

    // Chakma: U+11127 to U+1112B.
    if (character >= 0xf09184a7 && character <= 0xf09184ab) {
      return F_true;
    }

    // Chakma: U+1112D to U+11134.
    if (character >= 0xf09184ad && character <= 0xf09184b4) {
      return F_true;
    }

    // Mahajani: U+11173.
    if (character == 0xf09185b3) {
      return F_true;
    }

    // Sharada: U+11180 to U+11181.
    if (character >= 0xf0918680 && character <= 0xf0918681) {
      return F_true;
    }

    // Sharada: U+111B6 to U+111BE.
    if (character >= 0xf09186b6 && character <= 0xf09186be) {
      return F_true;
    }

    // Sharada: U+111CA to U+111CC.
    if (character >= 0xf091878a && character <= 0xf091878c) {
      return F_true;
    }

    // Sharada: U+111CA to U+111CC.
    if (character >= 0xf091878a && character <= 0xf091878c) {
      return F_true;
    }

    // Khojki: U+1122F to U+11231.
    if (character >= 0xf09188af && character <= 0xf09188b1) {
      return F_true;
    }

    // Khojki: U+11234, U+11236, U+11237.
    if (character == 0xf09188b4 || character == 0xf09188b6 || character == 0xf09188b7) {
      return F_true;
    }

    // Khudawadi: U+112DF, U+112DF.
    if (character == 0xf0918b9f || character == 0xf0918b9f) {
      return F_true;
    }

    // Khojki: U+112E3 to U+112EA.
    if (character >= 0xf0918ba3 && character <= 0xf0918baa) {
      return F_true;
    }

    // Grantha: U+11300, U+11301, U+1133C, U+11340.
    if (character == 0xf0918c80 || character == 0xf0918c81 || character == 0xf0918cbc || character == 0xf0918d80) {
      return F_true;
    }

    // Grantha: U+11366 to U+1136C.
    if (character >= 0xf0918da6 && character <= 0xf0918dac) {
      return F_true;
    }

    // Grantha: U+11370 to U+11374.
    if (character >= 0xf0918db0 && character <= 0xf0918db4) {
      return F_true;
    }

    // Tirhuta: U+114B3 to U+114B8.
    if (character >= 0xf09192b3 && character <= 0xf09192b8) {
      return F_true;
    }

    // Tirhuta: U+114BA, U+114BF, U+114C0, U+114C2.
    if (character == 0xf09192ba || character == 0xf09192bf || character == 0xf0919380 || character == 0xf0919382) {
      return F_true;
    }

    // Tirhuta: U+114C3.
    if (character == 0xf0919383) {
      return F_true;
    }

    // Siddham: U+115B2 to U+115B5.
    if (character >= 0xf09196b2 && character <= 0xf09196b5) {
      return F_true;
    }

    // Siddham: U+115BC to U+115BD.
    if (character >= 0xf09196bc && character <= 0xf09196bd) {
      return F_true;
    }

    // Siddham: U+115BF, U+115C0, U+115DC, U+115DD.
    if (character == 0xf09196bf || character == 0xf0919780 || character == 0xf091979c || character == 0xf091979d) {
      return F_true;
    }

    // Modi: U+11633 to U+1163A.
    if (character >= 0xf09198b3 && character <= 0xf09198ba) {
      return F_true;
    }

    // Modi: U+1163D to U+11640.
    if (character >= 0xf09198bd && character <= 0xf0919980) {
      return F_true;
    }

    // Takri: U+116AB, U+116AD.
    if (character == 0xf0919aab || character == 0xf0919aad) {
      return F_true;
    }

    // Takri: U+116B0 to U+116B5.
    if (character >= 0xf0919ab0 && character <= 0xf0919ab5) {
      return F_true;
    }

    // Takri: U+116B7.
    if (character == 0xf0919ab7) {
      return F_true;
    }

    // Ahom: U+1171D to U+1171F.
    if (character >= 0xf0919c9d && character <= 0xf0919c9f) {
      return F_true;
    }

    // Ahom: U+11722 to U+11725.
    if (character >= 0xf0919ca2 && character <= 0xf0919ca5) {
      return F_true;
    }

    // Ahom: U+11727 to U+1172B.
    if (character >= 0xf0919ca7 && character <= 0xf0919cab) {
      return F_true;
    }

    // Bassa Vah: U+16AF0 to U+16AF4.
    if (character >= 0xf096abb0 && character <= 0xf096abb4) {
      return F_true;
    }

    // Pahawh Hmong: U+16B30 to U+16B36.
    if (character >= 0xf096acb0 && character <= 0xf096acb6) {
      return F_true;
    }

    // Miao: U+16F8F to U+16F92.
    if (character >= 0xf096be8f && character <= 0xf096be92) {
      return F_true;
    }

    // Duployan: U+1BC9D to U+1BC9E.
    if (character >= 0xf09bb29d && character <= 0xf09bb29e) {
      return F_true;
    }

    // Musical Symbols: U+1D167 to U+1D169.
    if (character >= 0xf09d85a7 && character <= 0xf09d85a9) {
      return F_true;
    }

    // Musical Symbols: U+1D17B to U+1D182.
    if (character >= 0xf09d85bb && character <= 0xf09d8682) {
      return F_true;
    }

    // Musical Symbols: U+1D185 to U+1D18B.
    if (character >= 0xf09d8685 && character <= 0xf09d868b) {
      return F_true;
    }

    // Musical Symbols: U+1D1AA to U+1D1AD.
    if (character >= 0xf09d86aa && character <= 0xf09d86ad) {
      return F_true;
    }

    // Ancient Greek Musical Notation: U+1D242 to U+1D244.
    if (character >= 0xf09d8982 && character <= 0xf09d8984) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA00 to U+1DA36.
    if (character >= 0xf09da880 && character <= 0xf09da8b6) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA3B to U+1DA6C.
    if (character >= 0xf09da8bb && character <= 0xf09da9ac) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA75, U+1DA84.
    if (character == 0xf09da9b5 || character == 0xf09daa84) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA9B to U+1DA9F.
    if (character >= 0xf09daa9b && character <= 0xf09daa9f) {
      return F_true;
    }

    // Sutton SignWriting: U+1DAA1 to U+1DAAF.
    if (character >= 0xf09daaa1 && character <= 0xf09daaaf) {
      return F_true;
    }

    // Mende Kikakui: U+1E8D0 to U+1E8D6.
    if (character >= 0xf09ea390 && character <= 0xf09ea396) {
      return F_true;
    }

    // Variation Selectors Supplement: U+E0100 to U+E01EF.
    if (character >= 0xf3a08480 && character <= 0xf3a087af) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)

#if !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)
  f_status_t private_f_utf_character_is_control(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Control Codes.

      // Latin-1 Supplement: U+0080 to U+009F.
      if (character >= 0xc2800000 && character <= 0xc29f0000) {
        return F_true;
      }

      // Control Formats.

      // Latin-1 Supplement: U+00AD.
      if (character == 0xc2ad0000) {
        return F_true;
      }

      // Arabic: U+0600 to U+0605.
      if (character >= 0xd8800000 && character <= 0xd8850000) {
        return F_true;
      }

      // Arabic: U+061C, U+06DD.
      if (character == 0xd89c0000 || character == 0xdb9d0000) {
        return F_true;
      }

      // Syriac: U+070F.
      if (character == 0xdc8f0000) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 3) {

      // Control Formats.

      // Arabic Extended-A: U+08E2.
      if (character == 0xe0a3a200) {
        return F_true;
      }

      // Mongolian: U+180E.
      if (character == 0xe1a08e00) {
        return F_true;
      }

      // General Punctuation: U+200B to U+200F.
      if (character >= 0xe2808b00 && character <= 0xe2808f00) {
        return F_true;
      }

      // General Punctuation: U+202A to U+202E.
      if (character >= 0xe280aa00 && character <= 0xe280ae00) {
        return F_true;
      }

      // General Punctuation: U+2060 to U+2064.
      if (character >= 0xe281a000 && character <= 0xe281a400) {
        return F_true;
      }

      // General Punctuation: U+2066 to U+206F.
      if (character >= 0xe281a600 && character <= 0xe281af00) {
        return F_true;
      }

      // Arabic Presentation Forms-B: U+FEFF.
      if (character == 0xefbbbf00) {
        return F_true;
      }

      // Specials: U+FFF9 to U+FFFB.
      if (character >= 0xefbfb900 && character <= 0xefbfbb00) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 4) {

      // Control Formats.

      // Kaithi: U+110BD, U+110CD.
      if (character == 0xf09182bd || character == 0xf091838d) {
        return F_true;
      }

      // Egyptian Hieroglyphics: U+13430 to U+13438.
      if (character >= 0xf09390b0 && character <= 0xf09390b8) {
        return F_true;
      }

      // Shothand Format Controls: U+1BCA0 to U+1BCA3.
      if (character >= 0xf09bb2a0 && character <= 0xf09bb2a3) {
        return F_true;
      }

      // Music Symbols: U+1D173 to U+1D17A.
      if (character >= 0xf09d85b3 && character <= 0xf09d85ba) {
        return F_true;
      }

      // Tags: U+E0001.
      if (character == 0xf3a08081) {
        return F_true;
      }

      // Tags: U+E0020 to U+E007F.
      if (character >= 0xf3a080a0 && character <= 0xf3a081bf) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)

#if !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_control_code_)
  f_status_t private_f_utf_character_is_control_code(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+0080 to U+009F.
      if (character >= 0xc2800000 && character <= 0xc29f0000) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_contro_codel_)

#if !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)
  f_status_t private_f_utf_character_is_control_format(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+00AD.
      if (character == 0xc2ad0000) {
        return F_true;
      }

      // Arabic: U+0600 to U+0605.
      if (character >= 0xd8800000 && character <= 0xd8850000) {
        return F_true;
      }

      // Arabic: U+061C, U+06DD.
      if (character == 0xd89c0000 || character == 0xdb9d0000) {
        return F_true;
      }

      // Syriac: U+070F.
      if (character == 0xdc8f0000) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 3) {

      // Arabic Extended-A: U+08E2.
      if (character == 0xe0a3a200) {
        return F_true;
      }

      // Mongolian: U+180E.
      if (character == 0xe1a08e00) {
        return F_true;
      }

      // General Punctuation: U+200B to U+200F.
      if (character >= 0xe2808b00 && character <= 0xe2808f00) {
        return F_true;
      }

      // General Punctuation: U+202A to U+202E.
      if (character >= 0xe280aa00 && character <= 0xe280ae00) {
        return F_true;
      }

      // General Punctuation: U+2060 to U+2064.
      if (character >= 0xe281a000 && character <= 0xe281a400) {
        return F_true;
      }

      // General Punctuation: U+2066 to U+206F.
      if (character >= 0xe281a600 && character <= 0xe281af00) {
        return F_true;
      }

      // Arabic Presentation Forms-B: U+FEFF.
      if (character == 0xefbbbf00) {
        return F_true;
      }

      // Specials: U+FFF9 to U+FFFB.
      if (character >= 0xefbfb900 && character <= 0xefbfbb00) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 4) {

      // Kaithi: U+110BD, U+110CD.
      if (character == 0xf09182bd || character == 0xf091838d) {
        return F_true;
      }

      // Egyptian Hieroglyphics: U+13430 to U+13438.
      if (character >= 0xf09390b0 && character <= 0xf09390b8) {
        return F_true;
      }

      // Shothand Format Controls: U+1BCA0 to U+1BCA3.
      if (character >= 0xf09bb2a0 && character <= 0xf09bb2a3) {
        return F_true;
      }

      // Music Symbols: U+1D173 to U+1D17A.
      if (character >= 0xf09d85b3 && character <= 0xf09d85ba) {
        return F_true;
      }

      // Tags: U+E0001.
      if (character == 0xf3a08081) {
        return F_true;
      }

      // Tags: U+E0020 to U+E007F.
      if (character >= 0xf3a080a0 && character <= 0xf3a081bf) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)

#if !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)
  f_status_t private_f_utf_character_is_control_picture(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // Control Pictures: U+2400 to U+2426.
      if (character >= 0xe2908000 && character <= 0xe290a600) {
        return F_true;
      }

      // Specials: U+FFFC to U+FFFD.
      if (character == 0xefbfbc00 || character == 0xefbfbd00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)

#if !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)
  f_status_t private_f_utf_character_is_digit(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {
      uint16_t bytes = (uint16_t) ((character & 0xffff0000) >> 16);

      // Arabic: U+0660 to U+0669.
      if (bytes >= 0xd9a0 && bytes <= 0xd9a9) {
        return F_true;
      }

      // Extended Arabic: U+06F0 to U+06F9.
      if (bytes >= 0xdbb0 && bytes <= 0xdbb9) {
        return F_true;
      }

      // NKo: U+07C0 to U+07C9.
      if (bytes >= 0xdf80 && bytes <= 0xdf89) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {
      uint16_t bytes = (uint16_t) ((character & 0x00ffff00) >> 8);

      if (macro_f_utf_character_t_to_char_1(character) == 0xe0) {

        // Devanagari: U+0966 to U+096F.
        if (bytes >= 0xa5a6 && bytes <= 0xa5af) {
          return F_true;
        }

        // Bengali: U+09E6 to U+09EF.
        if (bytes >= 0xa7a6 && bytes <= 0xa7af) {
          return F_true;
        }

        // Gurmukhi: U+0A66 to U+0A6F.
        if (bytes >= 0xa9a6 && bytes <= 0xa9af) {
          return F_true;
        }

        // Gujarati: U+0AE6 to U+0AEF.
        if (bytes >= 0xaba6 && bytes <= 0xabaf) {
          return F_true;
        }

        // Oriya: U+0B66 to U+0B6F.
        if (bytes >= 0xada6 && bytes <= 0xadaf) {
          return F_true;
        }

        // Tamil: U+0BE6 to U+0BEF.
        if (bytes >= 0xafa6 && bytes <= 0xafaf) {
          return F_true;
        }

        // Telugu: U+0C66 to U+0C6F.
        if (bytes >= 0xb1a6 && bytes <= 0xb1af) {
          return F_true;
        }

        // Kannada: U+0CE6 to U+0CEF.
        if (bytes >= 0xb3a6 && bytes <= 0xb3af) {
          return F_true;
        }

        // Malayalam: U+0D66 to U+0D6F.
        if (bytes >= 0xb5a6 && bytes <= 0xb5af) {
          return F_true;
        }

        // Sinhala: U+0DE6 to U+0DEF.
        if (bytes >= 0xb7a6 && bytes <= 0xb7af) {
          return F_true;
        }

        // Thai: U+0E50 to U+0E59.
        if (bytes >= 0xb990 && bytes <= 0xb999) {
          return F_true;
        }

        // Lao: U+0ED0 to U+0ED9.
        if (bytes >= 0xbb90 && bytes <= 0xbb99) {
          return F_true;
        }

        // Tibetan: U+0F20 to U+0F29.
        if (bytes >= 0xbca0 && bytes <= 0xbca9) {
          return F_true;
        }

        // Myanmar: U+1040 to U+1049.
        if (bytes >= 0x8180 && bytes <= 0x8189) {
          return F_true;
        }

        // Myanmar (Shan): U+1090 to U+1099.
        if (bytes >= 0x8290 && bytes <= 0x8299) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xe1) {

        // Khmer: U+17E0 to U+17E9.
        if (bytes >= 0x9fa0 && bytes <= 0x9fa9) {
          return F_true;
        }

        // Mongolian: U+1810 to U+1819.
        if (bytes >= 0xa090 && bytes <= 0xa099) {
          return F_true;
        }

        // Limbu: U+1946 to U+194F.
        if (bytes >= 0xa586 && bytes <= 0xa58f) {
          return F_true;
        }

        // New Tai Lue: U+19D0 to U+19D9.
        if (bytes >= 0xa790 && bytes <= 0xa799) {
          return F_true;
        }

        // Tai Tham (Hora): U+1A80 to U+1A89.
        if (bytes >= 0xaa80 && bytes <= 0xaa89) {
          return F_true;
        }

        // Tai Tham (Tham): U+1A90 to U+1A99.
        if (bytes >= 0xaa90 && bytes <= 0xaa99) {
          return F_true;
        }

        // Balinese: U+1B50 to U+1B59.
        if (bytes >= 0xad90 && bytes <= 0xad99) {
          return F_true;
        }

        // Sundanese: U+1BB0 to U+1BB9.
        if (bytes >= 0xaeb0 && bytes <= 0xaeb9) {
          return F_true;
        }

        // Lepcha: U+1C40 to U+1C49.
        if (bytes >= 0xb180 && bytes <= 0xb189) {
          return F_true;
        }

        // Ol Chiki: U+1C50 to U+1C59.
        if (bytes >= 0xb190 && bytes <= 0xb199) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xea) {

        // Vai: U+A620 to U+A629.
        if (bytes >= 0x98a0 && bytes <= 0x98a9) {
          return F_true;
        }

        // Saurashtra: U+A8D0 to U+A8D9.
        if (bytes >= 0xa390 && bytes <= 0xa399) {
          return F_true;
        }

        // Kayah Li: U+A900 to U+A909.
        if (bytes >= 0xa480 && bytes <= 0xa489) {
          return F_true;
        }

        // Javanese: U+A9D0 to U+A9D9.
        if (bytes >= 0xa790 && bytes <= 0xa799) {
          return F_true;
        }

        // Myanmar Extended-B: U+A9F0 to U+A9F9.
        if (bytes >= 0xa7b0 && bytes <= 0xa7b9) {
          return F_true;
        }

        // Cham: U+AA50 to U+AA59.
        if (bytes >= 0xa990 && bytes <= 0xa999) {
          return F_true;
        }

        // Meetei Mayek: U+ABF0 to U+ABF9.
        if (bytes >= 0xafb0 && bytes <= 0xafb9) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xef) {

        // Halfwidth and Fullwidth Forms: U+FF10 to U+FF19.
        if (bytes >= 0xbc90 && bytes <= 0xbc99) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 4) {
      uint16_t bytes = (uint16_t) ((character & 0xffff0000) >> 16);

      if (macro_f_utf_character_t_to_char_1(character) == 0xf0) {
        if (macro_f_utf_character_t_to_char_2(character) == 0x90) {

          // Osmanya: U+104A0 to U+104A9.
          if (bytes >= 0x92a0 && bytes <= 0x92a9) {
            return F_true;
          }

          // Hanifi Rohingya: U+10D30 to U+10D39.
          if (bytes >= 0xb4b0 && bytes <= 0xb4b9) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x91) {

          // Brahmi: U+11066 to U+1106F.
          if (bytes >= 0x81a6 && bytes <= 0x81af) {
            return F_true;
          }

          // Sora Sompeng: U+110F0 to U+110F9.
          if (bytes >= 0x83b0 && bytes <= 0x83b9) {
            return F_true;
          }

          // Chakma: U+11136 to U+1113F.
          if (bytes >= 0x84b6 && bytes <= 0x84bf) {
            return F_true;
          }

          // Sharada: U+111D0 to U+111D9.
          if (bytes >= 0x8790 && bytes <= 0x8799) {
            return F_true;
          }

          // Khudawadi: U+112F0 to U+112F9.
          if (bytes >= 0x8bb0 && bytes <= 0x8bb9) {
            return F_true;
          }

          // Newa: U+11450 to U+11459.
          if (bytes >= 0x9190 && bytes <= 0x9199) {
            return F_true;
          }

          // Tirhuta: U+9199 to U+114D9.
          if (bytes >= 0x9390 && bytes <= 0x9399) {
            return F_true;
          }

          // Modi: U+11650 to U+11659.
          if (bytes >= 0x9990 && bytes <= 0x9999) {
            return F_true;
          }

          // Takri: U+116C0 to U+116C9.
          if (bytes >= 0x9b80 && bytes <= 0x9b89) {
            return F_true;
          }

          // Ahom: U+11730 to U+11739.
          if (bytes >= 0x9cb0 && bytes <= 0x9cb9) {
            return F_true;
          }

          // Warang Citi: U+118E0 to U+118E9.
          if (bytes >= 0xa3a0 && bytes <= 0xa3a9) {
            return F_true;
          }

          // Dives Akuru: U+11950 to U+11959.
          if (bytes >= 0xa590 && bytes <= 0xa599) {
            return F_true;
          }

          // Bhaiksuki: U+11C50 to U+11C59.
          if (bytes >= 0xb190 && bytes <= 0xb199) {
            return F_true;
          }

          // Masaram Gondi: U+11D50 to U+11D59.
          if (bytes >= 0xb590 && bytes <= 0xb599) {
            return F_true;
          }

          // Gunjala Gondi: U+11DA0 to U+11DA9.
          if (bytes >= 0xb6a0 && bytes <= 0xb6a9) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x96) {

          // Mro: U+16A60 to U+16A69.
          if (bytes >= 0xa9a0 && bytes <= 0xa9a9) {
            return F_true;
          }

          // Pahawh Hmong: U+16B50 to U+16B59.
          if (bytes >= 0xad90 && bytes <= 0xad99) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x9d) {

          // Mathematical Alphanumeric (Bold) Symbols: U+1D7CE to U+1D7D7.
          if (bytes >= 0x9f8e && bytes <= 0x9f97) {
            return F_true;
          }

          // Mathematical Alphanumeric (Double-Struck) Symbols: U+1D7D8 to U+1D7E1.
          if (bytes >= 0x9f98 && bytes <= 0x9fa1) {
            return F_true;
          }

          // Mathematical Alphanumeric (Sans-Serif) Symbols: U+1D7E2 to U+1D7EB.
          if (bytes >= 0x9fa2 && bytes <= 0x9fab) {
            return F_true;
          }

          // Mathematical Alphanumeric (Sans-Serif Bold) Symbols: U+1D7EC to U+1D7F5.
          if (bytes >= 0x9fac && bytes <= 0x9fb5) {
            return F_true;
          }

          // Mathematical Alphanumeric (Monospace) Symbols: U+1D7F6 to U+1D7FF.
          if (bytes >= 0x9fb6 && bytes <= 0x9fbf) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x9e) {

          // Nyiakeng Puachue Hmong: U+1E140 to U+1E149.
          if (bytes >= 0x8580 && bytes <= 0x8589) {
            return F_true;
          }

          // Wancho: U+1E2F0 to U+1E2F9.
          if (bytes >= 0x8bb0 && bytes <= 0x8bb9) {
            return F_true;
          }

          // Adlam: U+1E950 to U+1E959.
          if (bytes >= 0xa590 && bytes <= 0xa599) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x9f) {

          // Symbols for Legacy Computing (Segmented): U+1FBF0 to U+1FBF9.
          if (bytes >= 0xafb0 && bytes <= 0xafb9) {
            return F_true;
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)

#if !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)
  f_status_t private_f_utf_character_is_emoji(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+00A9, U+00AE.
      if (character == 0xc2a90000 || character == 0xc2ae0000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // General Punctuation: U+203C, U+2049.
      if (character == 0xe280bc00 || character == 0xe2818900) {
        return F_true;
      }

      // Letterlike Symbols: U+2122, U+2139
      if (character == 0xe2818900 || character == 0xe284b900) {
        return F_true;
      }

      // Arrows: U+2194 to U+2199.
      if (character >= 0xe2869400 && character <= 0xe2869900) {
        return F_true;
      }

      // Arrows: U+21A9, U+21AA.
      if (character == 0xe286a900 || character == 0xe286aa00) {
        return F_true;
      }

      // Miscellaneous Technical: U+231A, U+231B.
      if (character == 0xe28c9a00 || character == 0xe28c9b00) {
        return F_true;
      }

      // U+2328, U+23CF.
      if (character == 0xe28ca800 || character == 0xe28f8f00) {
        return F_true;
      }

      // U+23E9 to U+23F3.
      if (character >= 0xe28fa900 && character <= 0xe28fb300) {
        return F_true;
      }

      // U+23F8 to U+23FA.
      if (character >= 0xe28fb800 && character <= 0xe28fba00) {
        return F_true;
      }

      // U+24C2, U+25AA, U+25AB, U+25B6.
      if (character == 0xe2938200 || character == 0xe296aa00 || character == 0xe296ab00 || character == 0xe296b600) {
        return F_true;
      }

      // U+25C0.
      if (character == 0xe2978000) {
        return F_true;
      }

      // U+25FB to U+25FE.
      if (character >= 0xe297bb00 && character <= 0xe297be00) {
        return F_true;
      }

      // U+2600 to U+2604.
      if (character >= 0xe2988000 && character <= 0xe2988400) {
        return F_true;
      }

      // U+260E, U+2611, U+2614, U+2615.
      if (character == 0xe2988e00 || character == 0xe2989100 || character == 0xe2989400 || character == 0xe2989500) {
        return F_true;
      }

      // U+2618, U+261D, U+2620, U+2622.
      if (character == 0xe2989800 || character == 0xe2989d00 || character == 0xe298a000 || character == 0xe298a200) {
        return F_true;
      }

      // U+2623, U+2626, U+262A, U+262E.
      if (character == 0xe298a300 || character == 0xe298a600 || character == 0xe298aa00 || character == 0xe298ae00) {
        return F_true;
      }

      // U+262F.
      if (character == 0xe298af00) {
        return F_true;
      }

      // U+2638 to U+263A.
      if (character >= 0x00000000 && character <= 0x00000000) {
        return F_true;
      }

      // U+2640, U+2642.
      if (character == 0xe2998000 || character == 0xe2998200) {
        return F_true;
      }

      // U+2648 to U+2653.
      if (character >= 0xe2998800 && character <= 0xe2999300) {
        return F_true;
      }

      // U+265F, U+2660, U+2663, U+2665.
      if (character == 0xe2999f00 || character == 0xe299a000 || character == 0xe299a300 || character == 0xe299a500) {
        return F_true;
      }

      // U+2666, U+2668, U+267B, U+267E.
      if (character == 0xe299a600 || character == 0xe299a800 || character == 0xe299bb00 || character == 0xe299be00) {
        return F_true;
      }

      // U+267F.
      if (character == 0xe299bf00) {
        return F_true;
      }

      // U+2692 to U+2697.
      if (character >= 0xe29a9200 && character <= 0xe29a9700) {
        return F_true;
      }

      // U+2699, U+269B, U+269C, U+26A0.
      if (character == 0xe29a9900 || character == 0xe29a9b00 || character == 0xe29a9c00 || character == 0xe29aa000) {
        return F_true;
      }

      // U+26A1, U+26A7, U+26AA, U+26AB.
      if (character == 0xe29aa100 || character == 0xe29aa700 || character == 0xe29aaa00 || character == 0xe29aab00) {
        return F_true;
      }

      // U+26B0, U+26B1, U+26BD, U+26BE.
      if (character == 0x00000000 || character == 0x00000000 || character == 0x00000000 || character == 0x00000000) {
        return F_true;
      }

      // U+26C4, U+26C5, U+26C8, U+26CE.
      if (character == 0x00000000 || character == 0x00000000 || character == 0x00000000 || character == 0x00000000) {
        return F_true;
      }

      // U+26CF, U+26D1, U+26D3, U+26D4.
      if (character == 0x00000000 || character == 0x00000000 || character == 0x00000000 || character == 0x00000000) {
        return F_true;
      }

      // U+26E9, U+26EA.
      if (character == 0xe29ba900 || character == 0xe29baa00) {
        return F_true;
      }

      // U+26F0 to U+26F5.
      if (character >= 0xe29bb000 && character <= 0xe29bb500) {
        return F_true;
      }

      // U+26F7 to U+26FA.
      if (character >= 0xe29bb700 && character <= 0xe29bba00) {
        return F_true;
      }

      // U+26FD, U+2702, U+2705.
      if (character == 0xe29bbd00 || character == 0xe29c8200 || character == 0xe29c8500) {
        return F_true;
      }

      // U+2708 to U+270D.
      if (character >= 0xe29c8800 && character <= 0xe29c8d00) {
        return F_true;
      }

      // U+270F, U+2712, U+2714, U+2716.
      if (character == 0xe29c8f00 || character == 0xe29c9200 || character == 0xe29c9400 || character == 0xe29c9600) {
        return F_true;
      }

      // U+271D, U+2721, U+2728, U+2733.
      if (character == 0xe29c9d00 || character == 0xe29ca100 || character == 0xe29ca800 || character == 0xe29cb300) {
        return F_true;
      }

      // U+2734, U+2744, U+2747, U+274C.
      if (character == 0xe29cb400 || character == 0xe29d8400 || character == 0xe29d8700 || character == 0xe29d8c00) {
        return F_true;
      }

      // U+274E.
      if (character == 0xe29d8e00) {
        return F_true;
      }

      // U+2753 to U+2755.
      if (character >= 0xe29d9300 && character <= 0xe29d9500) {
        return F_true;
      }

      // U+2757, U+2763, U+2764.
      if (character == 0xe29d9700 || character == 0xe29da300 || character == 0xe29da400) {
        return F_true;
      }

      // U+2795 to U+2797.
      if (character >= 0xe29e9500 && character <= 0xe29e9700) {
        return F_true;
      }

      // U+27A1, U+27B0, U+27BF, U+2934.
      if (character == 0xe29ea100 || character == 0xe29eb000 || character == 0xe29ebf00 || character == 0xe2a4b400) {
        return F_true;
      }

      // U+2935.
      if (character == 0xe2a4b500) {
        return F_true;
      }

      // U+2B05 to U+2B07.
      if (character >= 0xe2ac8500 && character <= 0xe2ac8700) {
        return F_true;
      }

      // U+2B1B, U+2B1C, U+2B50, U+2B55.
      if (character == 0xe2ac9b00 || character == 0xe2ac9c00 || character == 0xe2ad9000 || character == 0xe2ad9500) {
        return F_true;
      }

      // U+3030, U+303D, U+3297, U+3299.
      if (character == 0xe380b000 || character == 0xe380bd00 || character == 0xe38a9700 || character == 0xe38a9900) {
        return F_true;
      }

      // U+1F004.
      if (character == 0x00000000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 4) {

      // U+1F0CF to U+1F171.
      if (character >= 0xf09f8084 && character <= 0xf09f85b1) {
        return F_true;
      }

      // U+1F17E, U+1F17F, U+1F18E.
      if (character == 0xf09f85be || character == 0xf09f85bf || character == 0xf09f868e) {
        return F_true;
      }

      // U+1F191 to U+1F19A.
      if (character >= 0xf09f8691 && character <= 0xf09f869a) {
        return F_true;
      }

      // U+1F201, U+1F202, U+1F21A, U+1F22F.
      if (character == 0xf09f8881 || character == 0xf09f8882 || character == 0xf09f889a || character == 0xf09f88af) {
        return F_true;
      }

      // U+1F232 to U+1F23A.
      if (character >= 0xf09f88b2 && character <= 0xf09f88ba) {
        return F_true;
      }

      // U+1F250, U+1F251.
      if (character == 0xf09f8990 || character == 0xf09f8991) {
        return F_true;
      }

      // U+1F300 to U+1F321.
      if (character >= 0xf09f8c80 && character <= 0xf09f8ca1) {
        return F_true;
      }

      // U+1F324 to U+1F393.
      if (character >= 0xf09f8ca4 && character <= 0xf09f8e93) {
        return F_true;
      }

      // U+1F396, U+1F397.
      if (character == 0xf09f8e96 || character == 0xf09f8e97) {
        return F_true;
      }

      // U+1F399 to U+1F39B.
      if (character >= 0xf09f8e99 && character <= 0xf09f8e9b) {
        return F_true;
      }

      // U+1F39E to U+1F3F0.
      if (character >= 0xf09f8e9e && character <= 0xf09f8fb0) {
        return F_true;
      }

      // U+1F3F3 to U+1F3F5.
      if (character >= 0xf09f8fb3 && character <= 0xf09f8fb5) {
        return F_true;
      }

      // U+1F3F7 to U+1F4FD.
      if (character >= 0xf09f8fb7 && character <= 0xf09f93bd) {
        return F_true;
      }

      // U+1F4FF to U+1F53D.
      if (character >= 0xf09f93bf && character <= 0xf09f94bd) {
        return F_true;
      }

      // U+1F549 to U+1F54E.
      if (character >= 0xf09f9589 && character <= 0xf09f958e) {
        return F_true;
      }

      // U+1F550 to U+1F567.
      if (character >= 0xf09f9590 && character <= 0xf09f95a7) {
        return F_true;
      }

      // U+1F56F, U+1F570.
      if (character == 0xf09f95af || character == 0xf09f95b0) {
        return F_true;
      }

      // U+1F573 to U+1F57A.
      if (character >= 0xf09f95b3 && character <= 0xf09f95ba) {
        return F_true;
      }

      // U+1F587.
      if (character == 0xf09f9687) {
        return F_true;
      }

      // U+1F58A to U+1F58D.
      if (character >= 0xf09f968a && character <= 0xf09f968d) {
        return F_true;
      }

      // U+1F590, U+1F595, U+1F596, U+1F5A4.
      if (character == 0xf09f9690 || character == 0xf09f9695 || character == 0xf09f9696 || character == 0xf09f96a4) {
        return F_true;
      }

      // U+1F5A5, U+1F5A8, U+1F5B1, U+1F5B2.
      if (character == 0xf09f96a5 || character == 0xf09f96a8 || character == 0xf09f96b1 || character == 0xf09f96b2) {
        return F_true;
      }

      // U+1F5BC.
      if (character == 0xf09f96bc) {
        return F_true;
      }

      // U+1F5C2 to U+1F5C4.
      if (character >= 0xf09f9782 && character <= 0xf09f9784) {
        return F_true;
      }

      // U+1F5D1 to U+1F5D3.
      if (character >= 0xf09f9791 && character <= 0xf09f9793) {
        return F_true;
      }

      // U+1F5DC to U+1F5DE.
      if (character >= 0xf09f979c && character <= 0xf09f979e) {
        return F_true;
      }

      // U+1F5E1, U+1F5E3, U+1F5E8, U+1F5EF.
      if (character == 0xf09f97a1 || character == 0xf09f97a3 || character == 0xf09f97a8 || character == 0xf09f97af) {
        return F_true;
      }

      // U+1F5F3.
      if (character == 0xf09f97b3) {
        return F_true;
      }

      // U+1F5FA to U+1F6C5.
      if (character >= 0xf09f97ba && character <= 0xf09f9b85) {
        return F_true;
      }

      // U+1F6CB to U+1F6D2.
      if (character >= 0xf09f9b8b && character <= 0xf09f9b92) {
        return F_true;
      }

      // U+1F6D5 to U+1F6D7.
      if (character >= 0xf09f9b95 && character <= 0xf09f9b97) {
        return F_true;
      }

      // U+1F6E0 to U+1F6E5.
      if (character >= 0xf09f9ba0 && character <= 0xf09f9ba5) {
        return F_true;
      }

      // U+1F6E9, U+1F6EB, U+1F6EC, U+1F6F0.
      if (character == 0xf09f9ba9 || character == 0xf09f9bab || character == 0xf09f9bac || character == 0xf09f9bb0) {
        return F_true;
      }

      // U+1F6F3 to U+1F6FC.
      if (character >= 0xf09f9bb3 && character <= 0xf09f9bbc) {
        return F_true;
      }

      // U+1F7E0 to U+1F7EB.
      if (character >= 0xf09f9fa0 && character <= 0xf09f9fab) {
        return F_true;
      }

      // U+1F90C to U+1F93A.
      if (character >= 0xf09fa48c && character <= 0xf09fa4ba) {
        return F_true;
      }

      // U+1F93C to U+1F945.
      if (character >= 0xf09fa4bc && character <= 0xf09fa585) {
        return F_true;
      }

      // U+1F947 to U+1F978.
      if (character >= 0xf09fa587 && character <= 0xf09fa5b8) {
        return F_true;
      }

      // U+1F97A to U+1F9CB.
      if (character >= 0xf09fa5ba && character <= 0xf09fa78b) {
        return F_true;
      }

      // U+1F9CD to U+1FA74.
      if (character >= 0xf09fa78d && character <= 0xf09fa9b4) {
        return F_true;
      }

      // U+1FA70 to U+1FA74.
      if (character >= 0xf09fa9b0 && character <= 0xf09fa9b4) {
        return F_true;
      }

      // U+1FA78 to U+1FA7A.
      if (character >= 0xf09fa9b8 && character <= 0xf09fa9ba) {
        return F_true;
      }

      // U+1FA80 to U+1FA86.
      if (character >= 0xf09faa80 && character <= 0xf09faa86) {
        return F_true;
      }

      // U+1FA90 to U+1FAA8.
      if (character >= 0xf09faa90 && character <= 0xf09faaa8) {
        return F_true;
      }

      // U+1FAB0 to U+1FAB6.
      if (character >= 0xf09faab0 && character <= 0xf09faab6) {
        return F_true;
      }

      // U+1FAC0 to U+1FAC2.
      if (character >= 0xf09fab80 && character <= 0xf09fab82) {
        return F_true;
      }

      // U+1FAD0 to U+1FAD6.
      if (character >= 0xf09fab90 && character <= 0xf09fab96) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)

#if !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)
  f_status_t private_f_utf_character_is_numeric(const f_utf_character_t character) {

    if (private_f_utf_character_is_digit(character)) {
      return F_true;
    }

    // @todo add letter UTF-8 numbers.
    // @todo add other UTF-8 numbers.

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // Number Forms: U+2150 to U+218B.
      if (character >= 0xe2859000 && character <= 0xe2868b00) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 4) {

      // Coptic Epact Numbers: U+102E1 to U+102FB.
      if (character >= 0xf0908ba1 && character <= 0xf0908bbb) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)

#if !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)
  f_status_t private_f_utf_character_is_phonetic(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // Phonetic Extensions: U+1D00 to U+1D7F.
      if (character >= 0xe1b48000 && character <= 0xe1b5bf00) {
        return F_true;
      }

      // Phonetic Extensions Supplement: U+1D80 to U+1DBF.
      if (character >= 0xe1b6bf00 && character <= 0xe1b6bf00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)

#if !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)
  f_status_t private_f_utf_character_is_private(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) < 3) {
      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // High Private Use Surrogates: U+DB80 to U+DBFF.
      if (character >= 0xedae8000 && character <= 0xedafbf00) {
        return F_true;
      }

      // Private Use: U+E000 to U+F8FF.
      if (character >= 0xee808000 && character <= 0xefa3bf00) {
        return F_true;
      }

      return F_false;
    }

    // Supplementary Private Use Area - A: U+F0000 to U+FFFFF.
    if (character >= 0xf3b08080 && character <= 0xf3bfbfbf) {
      return F_true;
    }

    // Supplementary Private Use Area - B: U+100000 to U+10FFFF.
    if (character >= 0xf4808080 && character <= 0xf48fbfbf) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)

#if !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_is_punctuation_)
  f_status_t private_f_utf_character_is_punctuation(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      if (macro_f_utf_character_t_to_char_1(character) == 0xc2) {
        // Latin-1 Supplement: U+00A1, U+00A7, U+00B6, U+00B7.
        if (character == 0xc2a10000 || character == 0xc2a70000 || character == 0xc2b60000 || character == 0xc2b70000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00BF
        if (character == 0xc2bf0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xcd) {

        // Greek and Coptic: U+037E
        if (character == 0xcdbe0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xce) {

        // Greek and Coptic: U+0387
        if (character == 0xce870000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xd5) {

        // Armenian: U+055A to U+055
        if (character >= 0xd59a0000 && character <= 0xd59f0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xd6) {

        // Armenian: U+0589
        if (character == 0xd6890000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xd7) {

        // Hebrew: U+05C0, U+05C3, U+05C6, U+05F3.
        if (character == 0xd7800000 || character == 0xd7830000 || character == 0xd7860000 || character == 0xd7b30000) {
          return F_true;
        }

        // Hebrew: U+05F4.
        if (character == 0xd7b40000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xd8) {

        // Arabic: U+0609, U+060A, U+060C, U+060D.
        if (character == 0xd8890000 || character == 0xd88a0000 || character == 0xd88c0000 || character == 0xd88d0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xd9) {

        // Arabic: U+061B, U+061E, U+061F, U+06D4.
        if (character == 0xd89b0000 || character == 0xd89e0000 || character == 0xd89f0000 || character == 0xdb940000) {
          return F_true;
        }

        // Arabic: U+066A to U+066D.
        if (character >= 0xd9aa0000 && character <= 0xd9ad0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xdc) {

        // Syriac: U+0700 to U+070D.
        if (character >= 0xdc800000 && character <= 0xdc8d0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xdf) {

        // NKo: U+07F7 to U+07F9.
        if (character >= 0xdfb70000 && character <= 0xdfb90000) {
          return F_true;
        }
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 3) {

      if (macro_f_utf_character_t_to_char_1(character) == 0xe0) {

        // Samaritan: U+0830 to U+083E.
        if (character >= 0xe0a0b000 && character <= 0xe0a0be00) {
          return F_true;
        }

        // Mandaic: U+085E.
        if (character == 0xe0a19e00) {
          return F_true;
        }

        // Devanagari: U+0964, U+0965, U+09670.
        if (character == 0xe0a5a400 || character == 0xe0a5a500 || character == 0xe0a5b000) {
          return F_true;
        }

        // Bengali: U+09FD.
        if (character == 0xe0a7bd00) {
          return F_true;
        }

        // Gurmukhi: U+0A76.
        if (character == 0xe0a9b600) {
          return F_true;
        }

        // Gujarati: U+0AF0.
        if (character == 0xe0abb000) {
          return F_true;
        }

        // Telugu: U+0C77.
        if (character == 0xe0b1b700) {
          return F_true;
        }

        // Kannada: U+0C84.
        if (character == 0xe0b28400) {
          return F_true;
        }

        // Sinhala: U+0DF4.
        if (character == 0xe0b7b400) {
          return F_true;
        }

        // Thai: U+0E4F to U+0E5B.
        if (character >= 0xe0b98f00 && character <= 0xe0b99b00) {
          return F_true;
        }

        // Tibetan: U+0F04 to U+0F14.
        if (character >= 0xe0bc8400 && character <= 0xe0bc9400) {
          return F_true;
        }

        // Tibetan: U+0F85.
        if (character == 0xe0be8500) {
          return F_true;
        }

        // Tibetan: U+0FD0 to U+0FDA.
        if (character >= 0xe0bf9000 && character <= 0xe0bf9a00) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xe1) {

        // Myanmar: U+104A to U+104F.
        if (character >= 0xe1818a00 && character <= 0xe1818f00) {
          return F_true;
        }

        // Georgian: U+10FB.
        if (character == 0xe183bb00) {
          return F_true;
        }

        // Ethiopic: U+1360 to U+1368.
        if (character >= 0xe18da000 && character <= 0xe18da800) {
          return F_true;
        }

        // Unified Canadian Aboriginal Syllabics: U+166E.
        if (character == 0xe199ae00) {
          return F_true;
        }

        // Runic: U+16EB to U+104F.
        if (character >= 0xe19bab00 && character <= 0xe19bad00) {
          return F_true;
        }

        // Hanunoo: U+1735, U+1736.
        if (character == 0xe19cb500 || character == 0xe19cb600) {
          return F_true;
        }

        // Khmer: U+17D4 to U+17D6.
        if (character >= 0xe19f9400 && character <= 0xe19f9600) {
          return F_true;
        }

        // Khmer: U+17D8 to U+17DA.
        if (character >= 0xe19f9800 && character <= 0xe19f9a00) {
          return F_true;
        }

        // Mongolian: U+1800 to U+180A.
        if (character >= 0xe1a08000 && character <= 0xe1a08a00) {
          return F_true;
        }

        // Limbu: U+1944, U+1945.
        if (character == 0xe1a58400 || character == 0xe1a58500) {
          return F_true;
        }

        // Buginese: U+1A1E, U+1A1F.
        if (character == 0xe1a89e00 || character == 0xe1a89f00) {
          return F_true;
        }

        // Tai Tham: U+1AA0 to U+1AAD.
        if (character >= 0xe1aaa000 && character <= 0xe1aaad00) {
          return F_true;
        }

        // Balinese: U+1B5A to U+1B60.
        if (character >= 0xe1ad9a00 && character <= 0xe1ada000) {
          return F_true;
        }

        // Batak: U+1BFC to U+1BFF.
        if (character >= 0xe1afbc00 && character <= 0xe1afbf00) {
          return F_true;
        }

        // Lepcha: U+1C3B to U+1BFF.
        if (character >= 0xe1b0bb00 && character <= 0xe1afbf00) {
          return F_true;
        }

        // Ol Chiki: U+1C7E, U+1C7F.
        if (character == 0xe1b1be00 || character == 0xe1b1bf00) {
          return F_true;
        }

        // Sundanese Supplement: U+1CC0 to U+1CC7.
        if (character >= 0xe1b38000 && character <= 0xe1b38700) {
          return F_true;
        }

        // Ol Chiki: U+1C7E, U+1C7F.
        if (character == 0xe1b1be00 || character == 0xe1b1bf00) {
          return F_true;
        }

        // Vedic Extensions: U+1CD3.
        if (character == 0xe1b39300) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xe2) {

        // General Punctuation: U+2010 to U+2027.
        if (character >= 0xe2809000 && character <= 0xe280a700) {
          return F_true;
        }

        // General Punctuation: U+2030 to U+205E.
        if (character >= 0xe280b000 && character <= 0xe2819e00) {
          return F_true;
        }

        // Coptic: U+2CF9 to U+2CFF.
        if (character >= 0xe2b3b900 && character <= 0xe2b3bf00) {
          return F_true;
        }

        // Tifinagh: U+2D70.
        if (character == 0xe2b5b000) {
          return F_true;
        }

        // Supplemental Punctuation: U+2E00 to U+2E52.
        if (character == 0xe2b88000 || character == 0xe2b99200) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xe3) {

        // CJK Symbols and Punctuation: U+3001 to U+3003.
        if (character >= 0xe3808100 && character <= 0xe3808300) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+303D, U+30FB.
        if (character == 0xe380bd00 || character == 0xe383bb00) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xea) {

        // Lisu: U+A4FE, U+A4FF.
        if (character == 0xea93be00 || character == 0xea93bf00) {
          return F_true;
        }

        // Vai: U+A60D to U+A60F.
        if (character >= 0xea988d00 && character <= 0xea988f00) {
          return F_true;
        }

        // Cyrillic Extended-B: U+A673, U+A67E.
        if (character == 0xea99b300 || character == 0xea99be00) {
          return F_true;
        }

        // Bamum: U+A6F2 to U+A6F7.
        if (character >= 0xea9bb200 && character <= 0xea9bb700) {
          return F_true;
        }

        // Phags-pa: U+A874 to U+A877.
        if (character >= 0xeaa1b400 && character <= 0xeaa1b700) {
          return F_true;
        }

        // Saurashtra: U+A673, U+A8CF.
        if (character == 0xea99b300 || character == 0xeaa38f00) {
          return F_true;
        }

        // Devanagari Extended: U+A8F8 to U+A8FC.
        if (character >= 0xeaa3b800 && character <= 0xeaa3bc00) {
          return F_true;
        }

        // Kayah Li: U+A92E, U+A92F.
        if (character == 0xeaa4ae00 || character == 0xeaa4af00) {
          return F_true;
        }

        // Rejang: U+A92E, U+A92F.
        if (character == 0xeaa4ae00 || character == 0xeaa59f00) {
          return F_true;
        }

        // Javanese: U+A9C1 to U+A9DF.
        if (character >= 0xeaa78100 && character <= 0xeaa79f00) {
          return F_true;
        }

        // Cham: U+AA5C to U+AA5F.
        if (character >= 0xeaa99c00 && character <= 0xeaa99f00) {
          return F_true;
        }

        // Tai Viet: U+AADE, U+AADF.
        if (character == 0xeaab9e00 || character == 0xeaab9f00) {
          return F_true;
        }

        // Meetei Mayek Extensions: U+AAF0, U+AAF1.
        if (character == 0xeaabb000 || character == 0xeaabb100) {
          return F_true;
        }

        // Meetei Mayek: U+ABEB.
        if (character == 0xeaafab00) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xef) {

        // Vertical Forms: U+FE10 to U+FE19.
        if (character >= 0xefb89000 && character <= 0xefb89900) {
          return F_true;
        }

        // CJK Compatibility Forms: U+FE30, U+FE45, U+FE46, U+FE49.
        if (character == 0xefb8b000 || character == 0xefb98500 || character == 0xefb98600 || character == 0xefb98900) {
          return F_true;
        }

        // CJK Compatibility Forms: U+FE4A to U+FE4C.
        if (character >= 0xefb98a00 && character <= 0xefb98c00) {
          return F_true;
        }

        // Small Form Variants: U+FE50 to U+FE57.
        if (character >= 0xefb99000 && character <= 0xefb99700) {
          return F_true;
        }

        // Small Form Variants: U+FE5F to U+FE61.
        if (character >= 0xefb99f00 && character <= 0xefb9a100) {
          return F_true;
        }

        // Small Form Variants: U+FE68, U+FE6A, U+FE6B.
        if (character == 0xefb9a800 || character == 0xefb9aa00 || character == 0xefb9ab00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF01 to U+FF07.
        if (character >= 0xefbc8100 && character <= 0xefbc8100) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF0A, U+FF0C.
        if (character == 0xefbc8a00 || character == 0xefbc8c00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF0E to U+FF1B.
        if (character >= 0xefbc8e00 && character <= 0xefbc9b00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF1F, U+FF20, U+FF3C, U+FF61.
        if (character == 0xefbc9f00 || character == 0xefbca000 || character == 0xefbcbc00 || character == 0xefbda100) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF64, U+FF65.
        if (character == 0xefbda400 || character == 0xefbda500) {
          return F_true;
        }
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 4) {
      if (macro_f_utf_character_t_to_char_1(character) == 0xf0) {
        if (macro_f_utf_character_t_to_char_2(character) == 0x90) {

          // Aegean Numbers: U+10100 to U+10102.
          if (character >= 0xf0908480 && character <= 0xf0908482) {
            return F_true;
          }

          // Ugaritic: U+1039F, U+103D0.
          if (character == 0xf0908e9f || character == 0xf0908f90) {
            return F_true;
          }

          // Caucasian Albanian: U+1056F.
          if (character == 0xf09095af) {
            return F_true;
          }

          // Imperial Aramaic: U+10857.
          if (character == 0xf090a197) {
            return F_true;
          }

          // Phoenician: U+1091F.
          if (character == 0xf090a49f) {
            return F_true;
          }

          // Lydian: U+1093F.
          if (character == 0xf090a4bf) {
            return F_true;
          }

          // Kharoshthi: U+10A50 to U+10A58.
          if (character >= 0xf090a990 && character <= 0xd802de58) {
            return F_true;
          }

          // Old South Arabian: U+10A7F.
          if (character == 0xf090a9bf) {
            return F_true;
          }

          // Manichaean: U+10AF0 to U+10AF6.
          if (character >= 0xf090abb0 && character <= 0xf090abb6) {
            return F_true;
          }

          // Avestan: U+10B39.
          if (character == 0xf090a9bf) {
            return F_true;
          }

          // Avestan: U+10B3A to U+10B3F.
          if (character >= 0xf090acba && character <= 0xf090acbf) {
            return F_true;
          }

          // Psalter Pahlavi: U+10B99 to U+10B9C.
          if (character >= 0xf090ae99 && character <= 0xf090ae9c) {
            return F_true;
          }

          // Sogdian: U+10F55 to U+10F59.
          if (character >= 0xf090bd95 && character <= 0xf090bd99) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x91) {

          // Brahmi: U+11047 to U+1104D.
          if (character >= 0xf0918187 && character <= 0xf091818d) {
            return F_true;
          }

          // Kaithi: U+110BB to U+110C1.
          if (character >= 0xf09182bb && character <= 0xf0918381) {
            return F_true;
          }

          // Chakma: U+11140 to U+11143.
          if (character >= 0xf0918580 && character <= 0xf0918583) {
            return F_true;
          }

          // Mahajani: U+11174 to U+11175.
          if (character == 0xf09185b4 || character == 0xf09185b5) {
            return F_true;
          }

          // Sharada: U+111C5 to U+111DF.
          if (character >= 0xf0918785 && character <= 0xf091879f) {
            return F_true;
          }

          // Khojki: U+11238 to U+1123D.
          if (character >= 0xf09188b8 && character <= 0xf09188bd) {
            return F_true;
          }

          // Multani: U+112A9.
          if (character == 0xf0918aa9) {
            return F_true;
          }

          // Newa: U+1144B to U+1145D.
          if (character >= 0xf091918b && character <= 0xf091919d) {
            return F_true;
          }

          // Tirhuta: U+114C6.
          if (character == 0xf0919386) {
            return F_true;
          }

          // Siddham: U+115C1 to U+115D7.
          if (character >= 0xf0919781 && character <= 0xf0919797) {
            return F_true;
          }

          // Modi: U+11641 to U+11643.
          if (character >= 0xf0919981 && character <= 0xf0919983) {
            return F_true;
          }

          // Mongolian Supplement: U+11660 to U+1166C.
          if (character >= 0xf09199a0 && character <= 0xf09199ac) {
            return F_true;
          }

          // Ahom: U+1173C to U+1173E.
          if (character >= 0xf0919cbc && character <= 0xf0919cbe) {
            return F_true;
          }

          // Dogra: U+1183B.
          if (character == 0xf091a0bb) {
            return F_true;
          }

          // Dives Akuru: U+11944 to U+11946.
          if (character >= 0xf091a584 && character <= 0xf091a586) {
            return F_true;
          }

          // Nandinagari: U+119E2.
          if (character == 0xf091a7a2) {
            return F_true;
          }

          // Zanabazar Square: U+11A3F to U+11A46.
          if (character >= 0xd806de3f && character <= 0xf091a986) {
            return F_true;
          }

          // Soyombo: U+11A9A to U+11AA2.
          if (character >= 0xd806de9a && character <= 0xd806dea2) {
            return F_true;
          }

          // Bhaiksuki: U+11C41 to U+11C45.
          if (character >= 0xf091b181 && character <= 0xf091b185) {
            return F_true;
          }

          // Marchen: U+11C70, U+11C71.
          if (character == 0xf091b1b0 || character == 0xf091b1b1) {
            return F_true;
          }

          // Makasar: U+11EF7, U+11EF8.
          if (character == 0xf091bbb7 || character == 0xf091bbb8) {
            return F_true;
          }

          // Tamil Supplement: U+11FFF.
          if (character == 0xf091bfbf) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x92) {

          // Cuneiform Numbers and Punctuation: U+12470 to U+12474.
          if (character >= 0xf09291b0 && character <= 0xf09291b4) {
            return F_true;
          }
        }
        else if (macro_f_utf_character_t_to_char_2(character) == 0x96) {

          // Mro: U+16A6E, U+16A6F.
          if (character == 0xf096a9ae || character == 0xf096a9af) {
            return F_true;
          }

          // Bassa Vah: U+16AF5.
          if (character == 0xf096abb5) {
            return F_true;
          }

          // Pahawh Hmong: U+16B37 to U+16B44.
          if (character >= 0xf096acb7 && character <= 0xf096ad84) {
            return F_true;
          }

          // Medefaidrin: U+16E97 to U+16E9A.
          if (character >= 0xf096ba97 && character <= 0xf096ba9a) {
            return F_true;
          }

          // Ideographic Symbols and Punctuation: U+16FE2.
          if (character == 0xf096bfa2) {
            return F_true;
          }

          // Duployan: U+1BC9F.
          if (character == 0xf09bb29f) {
            return F_true;
          }

          // Sutton SignWriting: U+1DA87 to U+1DA8B.
          if (character >= 0xf09daa87 && character <= 0xf09daa8b) {
            return F_true;
          }

          // Adlam: U+1E95E, U+1E95F.
          if (character == 0xf09ea59e || character == 0xf09ea59f) {
            return F_true;
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_is_punctuation_)

#if !defined(_di_f_utf_character_is_surrogate_) || !defined(_di_f_utf_is_surrogate_)
  f_status_t private_f_utf_character_is_surrogate(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // High Surrogates: U+D800 to U+DB7F.
      if (character >= 0xeda08000 && character <= 0xedadbf00) {
        return F_true;
      }

      // High Private Use Surrogates: U+DB80 to U+DBFF.
      if (character >= 0xedae8000 && character <= 0xedafbf00) {
        return F_true;
      }

      // Low Surrogates: U+DC00 to U+DFFF.
      if (character >= 0xedb08000 && character <= 0xedbfbf00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_surrogate_) || !defined(_di_f_utf_is_surrogate_)

#if !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)
  f_status_t private_f_utf_character_is_symbol(const f_utf_character_t character) {

    // @todo handle all Unicode "symbol".

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)

#if !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)
  f_status_t private_f_utf_character_is_valid(const f_utf_character_t character) {

    // @todo Check to see if this logic handles U+FDD0 to U+FDEF and any character ending in FFFE or FFFF.
    // Codes U+FDD0 to U+FDEF are: 0xefb79000 to 0xefb7af00.

    if (macro_f_utf_character_t_width_is(character) < 2) {
      if (macro_f_utf_character_t_to_char_1(character) >= 0x00 && macro_f_utf_character_t_to_char_1(character) <= 0x7f) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 2) {
      if (macro_f_utf_character_t_to_char_1(character) >= 0xc2 && macro_f_utf_character_t_to_char_1(character) <= 0xdf) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0x80 && macro_f_utf_character_t_to_char_2(character) <= 0xbf) {
          return F_true;
        }
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 3) {
      if (macro_f_utf_character_t_to_char_1(character) == 0xe0) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0xa0 && macro_f_utf_character_t_to_char_2(character) <= 0xbf) {
          if (macro_f_utf_character_t_to_char_3(character) >= 0x80 && macro_f_utf_character_t_to_char_3(character) <= 0xbf) {
            return F_true;
          }
        }
      }
      else if ((macro_f_utf_character_t_to_char_1(character) >= 0xe1 && macro_f_utf_character_t_to_char_1(character) <= 0xec) || (macro_f_utf_character_t_to_char_1(character) >= 0xee && macro_f_utf_character_t_to_char_1(character) <= 0xef)) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0x80 && macro_f_utf_character_t_to_char_2(character) <= 0xbf) {
          if (macro_f_utf_character_t_to_char_3(character) >= 0x80 && macro_f_utf_character_t_to_char_3(character) <= 0xbf) {
            return F_true;
          }
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xed) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0x80 && macro_f_utf_character_t_to_char_2(character) <= 0x9f) {
          if (macro_f_utf_character_t_to_char_3(character) >= 0x80 && macro_f_utf_character_t_to_char_3(character) <= 0xbf) {
            return F_true;
          }
        }
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 4) {
      if (macro_f_utf_character_t_to_char_1(character) == 0xf0) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0x90 && macro_f_utf_character_t_to_char_2(character) <= 0xbf) {
          if (macro_f_utf_character_t_to_char_3(character) >= 0x80 && macro_f_utf_character_t_to_char_3(character) <= 0xbf) {
            if (macro_f_utf_character_t_to_char_4(character) >= 0x80 && macro_f_utf_character_t_to_char_4(character) <= 0xbf) {
              return F_true;
            }
          }
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) >= 0xf1 && macro_f_utf_character_t_to_char_1(character) <= 0xf3) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0x80 && macro_f_utf_character_t_to_char_2(character) <= 0xbf) {
          if (macro_f_utf_character_t_to_char_3(character) >= 0x80 && macro_f_utf_character_t_to_char_3(character) <= 0xbf) {
            if (macro_f_utf_character_t_to_char_4(character) >= 0x80 && macro_f_utf_character_t_to_char_4(character) <= 0xbf) {
              return F_true;
            }
          }
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xf4) {
        if (macro_f_utf_character_t_to_char_2(character) >= 0x80 && macro_f_utf_character_t_to_char_2(character) <= 0x8f) {
          if (macro_f_utf_character_t_to_char_3(character) >= 0x80 && macro_f_utf_character_t_to_char_3(character) <= 0xbf) {
            if (macro_f_utf_character_t_to_char_4(character) >= 0x80 && macro_f_utf_character_t_to_char_4(character) <= 0xbf) {
              return F_true;
            }
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)

#if !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)
  f_status_t private_f_utf_character_is_whitespace(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+00A0.
      if (character == 0xc2a00000) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 3) {
      if (macro_f_utf_character_t_to_char_1(character) == 0xe2) {

        // General Punctuation: U+2000 to U+200A.
        if (character >= 0xe2808000 && character <= 0xe2808a00) {
          return F_true;
        }

        // General Punctuation: U+2028, U+2029, U+202F, U+205F.
        if (character == 0xe280a800 || character == 0xe280a900 || character == 0xe2819f00 || character == 0xe280af00) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xe3) {

        // CJK Symbols and Punctuation: U+3000.
        if (character == 0xe3808000) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)

#if !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)
  f_status_t private_f_utf_character_is_whitespace_modifier(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Spacing Modifier Letters: U+02B0 to U+02FF.
      if (character >= 0xcab00000 && character <= 0xcbbf0000) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)

#if !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)
  f_status_t private_f_utf_character_is_whitespace_other(const f_utf_character_t character) {

    // Ogham: U+1680 (isn't whitespace but is technically considered one: ( )).
    if (character == 0xe19a8000) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)

#if !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)
  f_status_t private_f_utf_character_is_wide(const f_utf_character_t character) {
    #ifndef _di_level_0_parameter_checking_
      if (!character) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (macro_f_utf_character_t_width_is(character) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    if (macro_f_utf_character_t_width_is(character) == 2) {
      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // Hangul Jamo: U+1100 to U+115F.
      if (character >= 0xe1848000 && character <= 0xe1859f00) {
        return F_true;
      }

      // Miscellaneous Technical: U+2329, U+232A.
      if (character == 0xe28ca900 || character == 0xe28caa00) {
        return F_true;
      }

      // CJK Radicals Supplement: U+2E80 to U+2EF3.
      if (character >= 0xe2ba8000 && character <= 0xe2bbb300) {
        return F_true;
      }

      // Kangxi Radicals: U+2F00 to U+2FD5.
      if (character >= 0xe2bc8000 && character <= 0xe2bf9500) {
        return F_true;
      }

      // Ideographic Description Characters: U+2FF0 to U+2FFB.
      if (character >= 0xe2bfb000 && character <= 0xe2bfbb00) {
        return F_true;
      }

      // CJK Symbols and Punctuation: U+3000 to U+303E.
      if (character >= 0xe3808000 && character <= 0xe380be00) {
        return F_true;
      }

      // Hiragana .. Katakana: U+3041 to U+30FF.
      if (character >= 0xe3818100 && character <= 0xe383bf00) {
        return F_true;
      }

      // Bopomofo .. Enclosed CJK Letters and Months: U+3105 to U+3247.
      if (character >= 0xe3848500 && character <= 0xe3898700) {
        return F_true;
      }

      // .. Enclosed CJK Letters and Months: U+3250 to U+32FE.
      if (character >= 0xe3899000 && character <= 0xe38bfe00) {
        return F_true;
      }

      // CJK Compatibility .. CJK Unified Ideographs Extension A: U+3300 to U+4DB5.
      if (character >= 0xe38c8000 && character <= 0xe4b6b500) {
        return F_true;
      }

      // CJK Unified Ideographs: U+4E00 to U+9FD5.
      if (character >= 0xe4b88000 && character <= 0xe9bf9500) {
        return F_true;
      }

      // Yi Syllables: U+A000 to U+A48C.
      if (character >= 0xea808000 && character <= 0xea928c00) {
        return F_true;
      }

      // Yi Radicals: U+A490 to U+A4C6.
      if (character >= 0xea929000 && character <= 0xea938600) {
        return F_true;
      }

      // Hangul Jamo Extended-A: U+A960 to U+A97C.
      if (character >= 0xeaa5a000 && character <= 0xeaa5bc00) {
        return F_true;
      }

      // Hangul Syllables: U+AC00 to U+D7A3.
      if (character >= 0xeab08000 && character <= 0xed9ea300) {
        return F_true;
      }

      // CJK Compatibility Ideographs: U+F900 to U+FA6D.
      if (character >= 0xefa48000 && character <= 0xefa9ad00) {
        return F_true;
      }

      // CJK Compatibility Ideographs: U+FA70 to U+FAD9.
      if (character >= 0xefa9b000 && character <= 0xefab9900) {
        return F_true;
      }

      // Vertical Forms .. Small Form Variants: U+FE10 to U+FE6B.
      if (character >= 0xefb89000 && character <= 0xefb9ab00) {
        return F_true;
      }

      // Half Width and Full Width Forms: U+FF01 to U+FF60.
      if (character >= 0xefbc8100 && character <= 0xefbda000) {
        return F_true;
      }

      // Half Width and Full Width Forms: U+FFE0 to U+FFE6.
      if (character >= 0xefbfa000 && character <= 0xefbfa600) {
        return F_true;
      }

      return F_false;
    }

    // CJK Unified Ideographs Extension C .. CJK Unified Ideographs Extension E: U+2A700 to U+2CEA1.
    if (character >= 0xf0aa9c80 && character <= 0xf0acbaa1) {
      return F_true;
    }

    // CJK Compatibility Ideographs Supplement: U+2F800 to U+2FA1D.
    if (character >= 0xf0afa080 && character <= 0xf0afa89d) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)

#if !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)
  f_status_t private_f_utf_character_is_word(const f_utf_character_t character, const bool strict) {

    if (private_f_utf_character_is_alpha_digit(character)) {
      return F_true;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {
      if (macro_f_utf_character_t_to_char_1(character) == 0xe2) {

        // General Punctuation: U+203F (‿), U+203E (‾), U+2040 (⁀), U+2054 (⁔).
        if (character == 0xe280bf00 || character == 0xe280be00 || character == 0xe2818000 || character == 0xe2819400) {
          return F_true;
        }
      }
      else if (macro_f_utf_character_t_to_char_1(character) == 0xef) {

        // General Punctuation: U+FE4D (﹍), U+FE4E (﹎), U+FE4F (﹏).
        if (character == 0xefb98d00 || character == 0xefb98e00 || character == 0xefb98f00) {
          return F_true;
        }

        // General Punctuation: U+FF3F (＿).
        if (character == 0xefbcbf00) {
          return F_true;
        }

        if (strict) {

          // General Punctuation: U+FE33 (︳), U+FE34 (︴).
          if (character == 0xefbcbf00 || character == 0xefbcbf00) {
          }
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)

#if !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)
  f_status_t private_f_utf_character_is_word_dash(const f_utf_character_t character, const bool strict) {

    if (private_f_utf_character_is_word(character, strict)) {
      return F_true;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // General Punctuation: U+2010, U+2011.
      if (character == 0xe2809000 || character == 0xe2809100) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)

#if !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_word_dash_plus(const f_utf_character_t character, const bool strict) {

    if (private_f_utf_character_is_word_dash(character, strict)) {
      return F_true;
    }

    if (strict) {

      // General Punctuation: U+2064.
      if (character == 0xe281a400) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)

#if !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)
  f_status_t private_f_utf_character_is_zero_width(const f_utf_character_t character) {

    if (macro_f_utf_character_t_to_char_1(character) == 0xe1) {

      // Mongolian: U+180E.
      if (character == 0xe1a08e00) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_to_char_1(character) == 0xe2) {

      // General Punctuation: U+200B, U+200C, U+200D, U+2060.
      if (character == 0xe2808b00 || character == 0xe2808c00 || character == 0xe2808d00 || character == 0xe281a000) {
        return F_true;
      }
    }
    else if (macro_f_utf_character_t_to_char_1(character) == 0xef) {

      // Arabic Presentation Forms-B: U+FEFF.
      if (character == 0xefbbbf00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)

#if !defined(_di_f_utf_unicode_to_) || !defined(_di_f_utf_character_unicode_to_)
  f_status_t private_f_utf_character_unicode_to(const f_utf_character_t character, uint32_t *unicode) {

    if (macro_f_utf_character_t_width_is(character) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    if (private_f_utf_character_is_valid(character) == F_false) {
      return F_status_set_error(F_utf);
    }

    // U+0000 -> U+007F (ASCII).
    if (macro_f_utf_character_t_width(character) == 1) {
      *unicode = macro_f_utf_character_t_to_char_1(character) & 0x7f;
    }

    // U+0080 -> U+07FF.
    else if (macro_f_utf_character_t_width(character) == 2) {
      *unicode = (macro_f_utf_character_t_to_char_1(character) & 0x1f) << 6;
      *unicode |= macro_f_utf_character_t_to_char_2(character) & 0x3f;
    }

    // U+0800 -> U+FFFF.
    else if (macro_f_utf_character_t_width(character) == 3) {
      *unicode = (macro_f_utf_character_t_to_char_1(character) & 0xf) << 12;
      *unicode |= (macro_f_utf_character_t_to_char_2(character) & 0x3f) << 6;
      *unicode |= macro_f_utf_character_t_to_char_3(character) & 0x3f;
    }

    // U+10000 -> U+10FFFF.
    else if (macro_f_utf_character_t_width(character) == 4) {
      *unicode = (macro_f_utf_character_t_to_char_1(character) & 0x7) << 18;
      *unicode |= (macro_f_utf_character_t_to_char_2(character) & 0x3f) << 12;
      *unicode |= (macro_f_utf_character_t_to_char_2(character) & 0x3f) << 6;
      *unicode |= macro_f_utf_character_t_to_char_4(character) & 0x3f;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_unicode_to_) || !defined(_di_f_utf_character_unicode_to_)

#ifdef __cplusplus
} // extern "C"
#endif

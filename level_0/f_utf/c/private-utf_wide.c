#include "utf.h"
#include "private-utf.h"
#include "private-utf_wide.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)
  f_status_t private_f_utf_character_is_wide(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {
      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

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

#ifdef __cplusplus
} // extern "C"
#endif

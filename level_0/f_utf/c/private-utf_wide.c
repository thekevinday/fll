#include "utf.h"
#include "private-utf.h"
#include "private-utf_wide.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)
  f_status_t private_f_utf_character_is_wide(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {
      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      // Hangul Jamo: U+1100 to U+115F.
      if (sequence >= 0xe1848000 && sequence <= 0xe1859f00) {
        return F_true;
      }

      // Miscellaneous Technical: U+2329, U+232A.
      if (sequence == 0xe28ca900 || sequence == 0xe28caa00) {
        return F_true;
      }

      // CJK Radicals Supplement: U+2E80 to U+2EF3.
      if (sequence >= 0xe2ba8000 && sequence <= 0xe2bbb300) {
        return F_true;
      }

      // Kangxi Radicals: U+2F00 to U+2FD5.
      if (sequence >= 0xe2bc8000 && sequence <= 0xe2bf9500) {
        return F_true;
      }

      // Ideographic Description Characters: U+2FF0 to U+2FFB.
      if (sequence >= 0xe2bfb000 && sequence <= 0xe2bfbb00) {
        return F_true;
      }

      // CJK Symbols and Punctuation: U+3000 to U+303E.
      if (sequence >= 0xe3808000 && sequence <= 0xe380be00) {
        return F_true;
      }

      // Hiragana .. Katakana: U+3041 to U+30FF.
      if (sequence >= 0xe3818100 && sequence <= 0xe383bf00) {
        return F_true;
      }

      // Bopomofo .. Enclosed CJK Letters and Months: U+3105 to U+3247.
      if (sequence >= 0xe3848500 && sequence <= 0xe3898700) {
        return F_true;
      }

      // .. Enclosed CJK Letters and Months: U+3250 to U+32FE.
      if (sequence >= 0xe3899000 && sequence <= 0xe38bfe00) {
        return F_true;
      }

      // CJK Compatibility .. CJK Unified Ideographs Extension A: U+3300 to U+4DB5.
      if (sequence >= 0xe38c8000 && sequence <= 0xe4b6b500) {
        return F_true;
      }

      // CJK Unified Ideographs: U+4E00 to U+9FD5.
      if (sequence >= 0xe4b88000 && sequence <= 0xe9bf9500) {
        return F_true;
      }

      // Yi Syllables: U+A000 to U+A48C.
      if (sequence >= 0xea808000 && sequence <= 0xea928c00) {
        return F_true;
      }

      // Yi Radicals: U+A490 to U+A4C6.
      if (sequence >= 0xea929000 && sequence <= 0xea938600) {
        return F_true;
      }

      // Hangul Jamo Extended-A: U+A960 to U+A97C.
      if (sequence >= 0xeaa5a000 && sequence <= 0xeaa5bc00) {
        return F_true;
      }

      // Hangul Syllables: U+AC00 to U+D7A3.
      if (sequence >= 0xeab08000 && sequence <= 0xed9ea300) {
        return F_true;
      }

      // CJK Compatibility Ideographs: U+F900 to U+FA6D.
      if (sequence >= 0xefa48000 && sequence <= 0xefa9ad00) {
        return F_true;
      }

      // CJK Compatibility Ideographs: U+FA70 to U+FAD9.
      if (sequence >= 0xefa9b000 && sequence <= 0xefab9900) {
        return F_true;
      }

      // Vertical Forms .. Small Form Variants: U+FE10 to U+FE6B.
      if (sequence >= 0xefb89000 && sequence <= 0xefb9ab00) {
        return F_true;
      }

      // Half Width and Full Width Forms: U+FF01 to U+FF60.
      if (sequence >= 0xefbc8100 && sequence <= 0xefbda000) {
        return F_true;
      }

      // Half Width and Full Width Forms: U+FFE0 to U+FFE6.
      if (sequence >= 0xefbfa000 && sequence <= 0xefbfa600) {
        return F_true;
      }

      return F_false;
    }

    // CJK Unified Ideographs Extension B .. CJK Unified Ideographs Extension H: U+20000 to U+323AF.
    if (sequence >= 0xf0a08080 && sequence <= 0xf0b28eaf) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)

#ifdef __cplusplus
} // extern "C"
#endif

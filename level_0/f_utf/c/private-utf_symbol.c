#include "utf.h"
#include "private-utf.h"
#include "private-utf_symbol.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)
  f_status_t private_f_utf_character_is_symbol(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xc2) {

        // Latin-1 Supplement: U+00A2 to U+00A5.
        if (character >= 0xc2a20000 && character <= 0xc2a50000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00A8, U+00AF, U+00B4, U+00B8.
        if (character == 0xc2a80000 || character == 0xc2af0000 || character == 0xc2b40000 || character == 0xc2b80000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xcb) {

        // Spacing Modifier Letters: U+02C2 to U+02C5.
        if (character >= 0xcb820000 && character <= 0xcb850000) {
          return F_true;
        }

        // Spacing Modifier Letters: U+02D2 to U+02DF.
        if (character >= 0xcb920000 && character <= 0xcb9f0000) {
          return F_true;
        }

        // Spacing Modifier Letters: U+02E5 to U+02EB.
        if (character >= 0xcba50000 && character <= 0xcbab0000) {
          return F_true;
        }

        // Spacing Modifier Letters: U+02ED to U+02FF.
        if (character >= 0xcbad0000 && character <= 0xcbbf0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xcd) {

        // Greek and Coptic: U+0375.
        if (character == 0xcdb50000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xce) {

        // Greek and Coptic: U+0384, U+0385.
        if (character == 0xce840000 || character == 0xce850000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xd6) {

        // Armenian: U+00A2.
        if (character == 0xd68f0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xd8) {

        // Arabic: U+00A2.
        if (character == 0xd88b0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xdf) {

        // NKo: U+07FE, U+07FF.
        if (character == 0xdfbe0000 || character == 0xdfbf0000) {
          return F_true;
        }
      }
      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xe0) {

        // Arabic Extended-B: U+0888.
        if (character == 0xe0a28800) {
          return F_true;
        }

        // Bengali: U+09F2, U+09F3, U+09FB.
        if (character == 0xe0a7b200 || character == 0xe0a7b300 || character == 0xe0a7bb00) {
          return F_true;
        }

        // Gujarati: U+0AF1.
        if (character == 0xe0abb100) {
          return F_true;
        }

        // Tamil: U+0BF9.
        if (character == 0xe0afb900) {
          return F_true;
        }

        // Thai: U+0E3F.
        if (character == 0xe0b8bf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe1) {

        // Khmer: U+17DB.
        if (character == 0xe19f9b00) {
          return F_true;
        }

        // Greek Extended: U+1FBD, U+1FBF, U+1FC0, U+1FC1.
        if (character == 0xe1bebd00 || character == 0xe1bebf00 || character == 0xe1bf8000 || character == 0xe1bf8100) {
          return F_true;
        }

        // Greek Extended: U+1FCD to U+1FCF.
        if (character >= 0xe1bf8d00 && character <= 0xe1bf8f00) {
          return F_true;
        }

        // Greek Extended: U+1FDD to U+1FDF.
        if (character >= 0xe1bf9d00 && character <= 0xe1bf9f00) {
          return F_true;
        }

        // Greek Extended: U+1FED to U+1FEF.
        if (character >= 0xe1bfad00 && character <= 0xe1bfaf00) {
          return F_true;
        }

        // Greek Extended: U+1FFD, U+1FFE.
        if (character == 0xe1bfbd00 || character == 0xe1bfbe00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe2) {

        // Currency Symbols: U+20A0 to U+20C0.
        if (character >= 0xe282a000 && character <= 0xe2838000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe3) {

        // Hiragana: U+309B, U+309C.
        if (character == 0xe3829b00 || character == 0xe3829c00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xea) {

        // Modifier Tone Letters: U+A700 to U+A716.
        if (character >= 0xea9c8000 && character <= 0xea9c9600) {
          return F_true;
        }

        // Modifier Tone Letters: U+A720, U+A721.
        if (character == 0xea9ca000 || character == 0xea9ca100) {
          return F_true;
        }

        // Latin Extended-D: U+A789, U+A78A.
        if (character == 0xea9e8900 || character == 0xea9e8a00) {
          return F_true;
        }

        // Common Indic Number Forms: U+A838.
        if (character == 0xeaa0b800) {
          return F_true;
        }

        // Latin Extended-E: U+AB5B, U+AB6A, U+AB6B.
        if (character == 0xeaad9b00 || character == 0xeaadaa00 || character == 0xeaadab00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xef) {

        // Arabic Presentation Forms-A: U+FBB2 to U+FBC2.
        if (character >= 0xefaeb200 && character <= 0xefaf8200) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FDFC.
        if (character == 0xefb7bc00) {
          return F_true;
        }

        // Small Form Variants: U+FE69.
        if (character == 0xefb9a900) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF04, U+FF3E, U+FF40, U+FFE0.
        if (character == 0xefbc8400 || character == 0xefbcbe00 || character == 0xefbd8000 || character == 0xefbfa000) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE1, U+FFE3, U+FFE5, U+FFE6.
        if (character == 0xefbfa100 || character == 0xefbfa300 || character == 0xefbfa500 || character == 0xefbfa600) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(character) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(character) == 0x91) {

        // Tamil Supplement: U+11FDD to U+11FE0.
        if (character >= 0xf091bf9d && character <= 0xf091bfa0) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(character) == 0x9e) {

        // Wancho: U+1E2FF.
        if (character == 0xf09e8bbf) {
          return F_true;
        }

        // Indic Siyaq Numbers: U+ECB0.
        if (character == 0xf09eb2b0) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(character) == 0x9f) {

        // Miscellaneous Symbols and Pictographs: U+1F3FB to U+1F3FF.
        if (character >= 0xf09f8fbb && character <= 0xf09f8fbf) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)

#ifdef __cplusplus
} // extern "C"
#endif

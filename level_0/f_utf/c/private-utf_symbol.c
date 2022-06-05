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

        // Latin-1 Supplement: U+00A8, U+00AC, U+00AF, U+00B1.
        if (character == 0xc2a80000 || character == 0xc2ac0000 || character == 0xc2af0000 || character == 0xc2b10000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00B4, U+00B8, U+00D7, U+00F7.
        if (character == 0xc2b40000 || character == 0xc2b80000 || character == 0xc3970000 || character == 0xc3b70000) {
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
      else if (macro_f_utf_char_t_to_char_1(character) == 0xcf) {

        // Greek and Coptic: U+03F6.
        if (character == 0xcfb60000) {
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

        // Arabic: U+0606 to U+0608.
        if (character >= 0xd8860000 && character <= 0xd8880000) {
          return F_true;
        }

        // Arabic: U+ U+060B.
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

        // General Punctuation: U+2044, U+2052.
        if (character == 0xe2818400 || character == 0xe2819200) {
          return F_true;
        }

        // Superscripts and Subscripts: U+207A, U+207C.
        if (character == 0xe281ba00 || character == 0xe281bc00) {
          return F_true;
        }

        // Superscripts and Subscripts: U+208A, U+208C.
        if (character == 0xe2828a00 || character == 0xe2828c00) {
          return F_true;
        }

        // Currency Symbols: U+20A0 to U+20C0.
        if (character >= 0xe282a000 && character <= 0xe2838000) {
          return F_true;
        }

        // Letterlike Symbols: U+2118.
        if (character == 0xe2849800) {
          return F_true;
        }

        // Letterlike Symbols: U+2140 to U+2144.
        if (character >= 0xe2858000 && character <= 0xe2858400) {
          return F_true;
        }

        // Letterlike Symbols: U+214B.
        if (character == 0xe2858b00) {
          return F_true;
        }

        // Arrows: U+2190 to U+2194.
        if (character >= 0xe2869000 && character <= 0xe2869400) {
          return F_true;
        }

        // Arrows: U+219A, U+219B, U+21A0, U+21A3.
        if (character == 0xe2869a00 || character == 0xe2869b00 || character == 0xe286a000 || character == 0xe286a300) {
          return F_true;
        }

        // Arrows: U+21A6, U+21AE, U+21CE, U+21CF.
        if (character == 0xe286a600 || character == 0xe286ae00 || character == 0xe2878e00 || character == 0xe2878f00) {
          return F_true;
        }

        // Arrows: U+21D2, U+21D4.
        if (character == 0xe2879200 || character == 0xe2879400) {
          return F_true;
        }

        // Arrows to Mathematical Operators: U+21F4 to U+22FF.
        if (character >= 0xe287b400 && character <= 0xe28bbf00) {
          return F_true;
        }

        // Miscellaneous Technical: U+2320, U+2321, U+237C.
        if (character == 0xe28ca000 || character == 0xe28ca100 || character == 0xe28dbc00) {
          return F_true;
        }

        // Miscellaneous Technical: U+239B to U+23B3.
        if (character >= 0xe28e9b00 && character <= 0xe28eb300) {
          return F_true;
        }

        // Miscellaneous Technical: U+23DC to U+23E1.
        if (character >= 0xe28f9c00 && character <= 0xe28fa100) {
          return F_true;
        }

        // Geometric Shapes: U+25B7 to U+25C1.
        if (character >= 0xe296b700 && character <= 0xe2978100) {
          return F_true;
        }

        // Geometric Shapes: U+25F8 to U+25FF.
        if (character >= 0xe297b800 && character <= 0xe297bf00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+266F.
        if (character == 0xe299af00) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-A: U+27C0 to U+27C4.
        if (character >= 0xe29f8000 && character <= 0xe29f8400) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-A: U+27C7 to U+27E5.
        if (character >= 0xe29f8700 && character <= 0xe29fa500) {
          return F_true;
        }

        // Supplemental Arrows-A: U+27F0 to U+27FF.
        if (character >= 0xe29fb000 && character <= 0xe29fbf00) {
          return F_true;
        }

        // Supplemental Arrows-B to Miscellaneous Mathematical Symbols-B: U+2900 to U+2982.
        if (character >= 0xe2a48000 && character <= 0xe2a68200) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+2999 to U+29D7.
        if (character >= 0xe2a69900 && character <= 0xe2a79700) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+29DC to U+29FB.
        if (character >= 0xe2a79c00 && character <= 0xe2a7bb00) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B to Supplemental Mathematical Operators: U+29FE to U+2AFF.
        if (character >= 0xe2a7be00 && character <= 0xe2abbf00) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2B30 to U+2B44.
        if (character >= 0xe2acb000 && character <= 0xe2ad8400) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2B47 to U+2B4C.
        if (character >= 0xe2ad8700 && character <= 0xe2ad8c00) {
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

        // Alphabetic Presentation Forms: U+FB29.
        if (character == 0xefaca900) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FBB2 to U+FBC2.
        if (character >= 0xefaeb200 && character <= 0xefaf8200) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FDFC.
        if (character == 0xefb7bc00) {
          return F_true;
        }

        // Small Form Variants: U+FE62, U+FE64, U+FE65, U+FE66.
        if (character == 0xefb9a200 || character == 0xefb9a400 || character == 0xefb9a500 || character == 0xefb9a600) {
          return F_true;
        }

        // Small Form Variants: U+FE69.
        if (character == 0xefb9a900) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF04, U+FF0B.
        if (character == 0xefbc8400 || character == 0xefbc8b00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF1C to U+FF1E.
        if (character >= 0xefbc9c00 && character <= 0xefbc9e00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF3E, U+FF40, .
        if (character == 0xefbcbe00 || character == 0xefbd8000) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE0, U+FFE1, U+FFE3, U+FFE5.
        if (character == 0xefbfa000 || character == 0xefbfa100 || character == 0xefbfa300 || character == 0xefbfa500) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE6.
        if (character == 0xefbfa600) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF5C, U+FF5E, U+FFE2.
        if (character == 0xefbd9c00 || character == 0xefbd9e00 || character == 0xefbfa200) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE9 to U+FFEC.
        if (character >= 0xefbfa900 && character <= 0xefbfac00) {
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

        // Mathematical Alphanumeric Symbols: U+1D6C1, U+1D6FB, U+1D715, U+1D735.
        if (character == 0xf09d9b81 || character == 0xf09d9bbb || character == 0x09d9c95 || character == 0xf09d9cb5) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D74F, U+1D76F, U+1D789, U+1D7A9.
        if (character == 0xf09d9d8f || character == 0xf09d9daf || character == 0xf09d9e89 || character == 0xf09d9ea9) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D7C3, U+1EEF0, U+1EEF1.
        if (character == 0xf09d9f83 || character == 0xf09ebbb0 || character == 0xf09ebbb1) {
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

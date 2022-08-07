#include "utf.h"
#include "private-utf.h"
#include "private-utf_symbol.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_symbol(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xc2) {

        // Latin-1 Supplement: U+00A2 to U+00A6.
        if (sequence >= 0xc2a20000 && sequence <= 0xc2a60000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00A8, U+00A9, U+00AC, U+00AE.
        if (sequence == 0xc2a80000 || sequence == 0xc2a90000 || sequence == 0xc2ac0000 || sequence == 0xc2ae0000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00AF, U+00B0, U+00B1, U+00B4.
        if (sequence == 0xc2af0000 || sequence == 0xc2b00000 || sequence == 0xc2b10000 || sequence == 0xc2b40000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00B8.
        if (sequence == 0xc2b80000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xc3) {

        // Latin-1 Supplement: U+00D7, U+00F7.
        if (sequence == 0xc3970000 || sequence == 0xc3b70000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xcb) {

        // Spacing Modifier Letters: U+02C2 to U+02C5.
        if (sequence >= 0xcb820000 && sequence <= 0xcb850000) {
          return F_true;
        }

        // Spacing Modifier Letters: U+02D2 to U+02DF.
        if (sequence >= 0xcb920000 && sequence <= 0xcb9f0000) {
          return F_true;
        }

        // Spacing Modifier Letters: U+02E5 to U+02EB.
        if (sequence >= 0xcba50000 && sequence <= 0xcbab0000) {
          return F_true;
        }

        // Spacing Modifier Letters: U+02ED to U+02FF.
        if (sequence >= 0xcbad0000 && sequence <= 0xcbbf0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xcd) {

        // Greek and Coptic: U+0375.
        if (sequence == 0xcdb50000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xce) {

        // Greek and Coptic: U+0384, U+0385.
        if (sequence == 0xce840000 || sequence == 0xce850000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xcf) {

        // Greek and Coptic: U+03F6.
        if (sequence == 0xcfb60000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd2) {

        // Cyrillic: U+0482.
        if (sequence == 0xd2820000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd6) {

        // Armenian: U+058D to U+058F.
        if (sequence >= 0xd68d0000 && sequence <= 0xd68f0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd8) {

        // Arabic: U+0606 to U+0608.
        if (sequence >= 0xd8860000 && sequence <= 0xd8880000) {
          return F_true;
        }

        // Arabic: U+060B, U+060E, U+060F.
        if (sequence == 0xd88b0000 || sequence == 0xd88e0000 || sequence == 0xd88f0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdb) {

        // Arabic: U+06DE, U+06E9, U+06FD, U+06FE.
        if (sequence == 0xdb9e0000 || sequence == 0xdba90000 || sequence == 0xdbbd0000 || sequence == 0xdbbe0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdf) {

        // NKo: U+07F6, U+07FE, U+07FF.
        if (sequence == 0xdfb60000 || sequence == 0xdfbe0000 || sequence == 0xdfbf0000) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Arabic Extended-B: U+0888.
        if (sequence == 0xe0a28800) {
          return F_true;
        }

        // Bengali: U+09F2, U+09F3, U+09FA, U+09FB.
        if (sequence == 0xe0a7b200 || sequence == 0xe0a7b300 || sequence == 0xe0a7ba00 || sequence == 0xe0a7bb00) {
          return F_true;
        }

        // Gujarati: U+0AF1.
        if (sequence == 0xe0abb100) {
          return F_true;
        }

        // Oriya: U+0B70.
        if (sequence == 0xe0adb000) {
          return F_true;
        }

        // Tamil: U+0BF3 to U+0BFA.
        if (sequence >= 0xe0afb300 && sequence <= 0xe0afba00) {
          return F_true;
        }

        // Telugu: U+0C7F.
        if (sequence == 0xe0b1bf00) {
          return F_true;
        }

        // Malayalam: U+0D4F, U+0D79.
        if (sequence == 0xe0b58f00 || sequence == 0xe0b5b900) {
          return F_true;
        }

        // Thai: U+0E3F.
        if (sequence == 0xe0b8bf00) {
          return F_true;
        }

        // Tibetan: U+0F01 to U+0F03.
        if (sequence >= 0xe0bc8100 && sequence <= 0xe0bc8300) {
          return F_true;
        }

        // Tibetan: U+0F13.
        if (sequence == 0xe0bc9300) {
          return F_true;
        }

        // Tibetan: U+0F15 to U+0F17.
        if (sequence >= 0xe0bc9500 && sequence <= 0xe0bc9700) {
          return F_true;
        }

        // Tibetan: U+0F1A to U+0F1F.
        if (sequence >= 0xe0bc9a00 && sequence <= 0xe0bc9f00) {
          return F_true;
        }

        // Tibetan: U+0F34, U+0F36, U+0F38.
        if (sequence == 0xe0bcb400 || sequence == 0xe0bcb600 || sequence == 0xe0bcb800) {
          return F_true;
        }

        // Tibetan: U+0FBE to U+0FC5.
        if (sequence >= 0xe0bebe00 && sequence <= 0xe0bf8500) {
          return F_true;
        }

        // Tibetan: U+0FC7 to U+0FCC.
        if (sequence >= 0xe0bf8700 && sequence <= 0xe0bf8c00) {
          return F_true;
        }

        // Tibetan: U+0FCE, U+0FCF.
        if (sequence == 0xe0bf8e00 || sequence == 0xe0bf8f00) {
          return F_true;
        }

        // Tibetan: U+0FD5 to U+0FD8.
        if (sequence >= 0xe0bf9500 && sequence <= 0xe0bf9800) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Myanmar: U+109E, U+109F.
        if (sequence == 0xe1829e00 || sequence == 0xe1829f00) {
          return F_true;
        }

        // Ethiopic Supplement: U+1390 to U+1399.
        if (sequence >= 0xe18e9000 && sequence <= 0xe18e9900) {
          return F_true;
        }

        // Unified Canadian Aboriginal Syllabics: U+166D.
        if (sequence == 0xe199ad00) {
          return F_true;
        }

        // Khmer: U+17DB.
        if (sequence == 0xe19f9b00) {
          return F_true;
        }

        // Limbu: U+1940.
        if (sequence == 0xe1a58000) {
          return F_true;
        }

        // New Tai Lue to Khmer Symbols: U+19DE to U+19FF.
        if (sequence >= 0xe1a79e00 && sequence <= 0xe1a7bf00) {
          return F_true;
        }

        // Balinese: U+1B61 to U+1B6A.
        if (sequence >= 0xe1ada100 && sequence <= 0xe1adaa00) {
          return F_true;
        }

        // Balinese: U+1B74 to U+1B7C.
        if (sequence >= 0xe1adb400 && sequence <= 0xe1adbc00) {
          return F_true;
        }

        // Greek Extended: U+1FBD, U+1FBF, U+1FC0, U+1FC1.
        if (sequence == 0xe1bebd00 || sequence == 0xe1bebf00 || sequence == 0xe1bf8000 || sequence == 0xe1bf8100) {
          return F_true;
        }

        // Greek Extended: U+1FCD to U+1FCF.
        if (sequence >= 0xe1bf8d00 && sequence <= 0xe1bf8f00) {
          return F_true;
        }

        // Greek Extended: U+1FDD to U+1FDF.
        if (sequence >= 0xe1bf9d00 && sequence <= 0xe1bf9f00) {
          return F_true;
        }

        // Greek Extended: U+1FED to U+1FEF.
        if (sequence >= 0xe1bfad00 && sequence <= 0xe1bfaf00) {
          return F_true;
        }

        // Greek Extended: U+1FFD, U+1FFE.
        if (sequence == 0xe1bfbd00 || sequence == 0xe1bfbe00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // General Punctuation: U+2044, U+2052.
        if (sequence == 0xe2818400 || sequence == 0xe2819200) {
          return F_true;
        }

        // Superscripts and Subscripts: U+207A to U+207C.
        if (sequence >= 0xe281ba00 && sequence <= 0xe281bc00) {
          return F_true;
        }

        // Superscripts and Subscripts: U+208A to U+208C.
        if (sequence >= 0xe2828a00 && sequence <= 0xe2828c00) {
          return F_true;
        }

        // Currency Symbols: U+20A0 to U+20C0.
        if (sequence >= 0xe282a000 && sequence <= 0xe2838000) {
          return F_true;
        }

        // Letterlike Symbols: U+2100, U+2101.
        if (sequence == 0xe2848000 || sequence == 0xe2848100) {
          return F_true;
        }

        // Letterlike Symbols: U+2103 to U+2106.
        if (sequence >= 0xe2848300 && sequence <= 0xe2848600) {
          return F_true;
        }

        // Letterlike Symbols: U+2108, U+2109, U+2114.
        if (sequence == 0xe2848800 || sequence == 0xe2848900 || sequence == 0xe2849400) {
          return F_true;
        }

        // Letterlike Symbols: U+2116 to U+2118.
        if (sequence >= 0xe2849600 && sequence <= 0xe2849800) {
          return F_true;
        }

        // Letterlike Symbols: U+211E to U+2123.
        if (sequence >= 0xe2849e00 && sequence <= 0xe284a300) {
          return F_true;
        }

        // Letterlike Symbols: U+2140 to U+2144.
        if (sequence >= 0xe2858000 && sequence <= 0xe2858400) {
          return F_true;
        }

        // Letterlike Symbols: U+214B.
        if (sequence == 0xe2858b00) {
          return F_true;
        }

        // Arrows: U+2190 to U+2194.
        if (sequence >= 0xe2869000 && sequence <= 0xe2869400) {
          return F_true;
        }

        // Arrows: U+219A, U+219B, U+21A0, U+21A3.
        if (sequence == 0xe2869a00 || sequence == 0xe2869b00 || sequence == 0xe286a000 || sequence == 0xe286a300) {
          return F_true;
        }

        // Arrows: U+21A6, U+21AE, U+21CE, U+21CF.
        if (sequence == 0xe286a600 || sequence == 0xe286ae00 || sequence == 0xe2878e00 || sequence == 0xe2878f00) {
          return F_true;
        }

        // Arrows: U+21D2, U+21D4.
        if (sequence == 0xe2879200 || sequence == 0xe2879400) {
          return F_true;
        }

        // Arrows to Mathematical Operators: U+21F4 to U+22FF.
        if (sequence >= 0xe287b400 && sequence <= 0xe28bbf00) {
          return F_true;
        }

        // Letterlike Symbols: U+2125, U+2127, U+2129, U+212E.
        if (sequence == 0xe284a500 || sequence == 0xe284a700 || sequence == 0xe284a900 || sequence == 0xe284ae00) {
          return F_true;
        }

        // Letterlike Symbols: U+213A, U+213B.
        if (sequence == 0xe284ba00 || sequence == 0xe284bb00) {
          return F_true;
        }

        // Letterlike Symbols: U+2140 to U+2144.
        if (sequence >= 0xe2858000 && sequence <= 0xe2858400) {
          return F_true;
        }

        // Letterlike Symbols: U+214A to U+214D.
        if (sequence >= 0xe2858a00 && sequence <= 0xe2858d00) {
          return F_true;
        }

        // Letterlike Symbols: U+214F.
        if (sequence == 0xe2858f00) {
          return F_true;
        }

        // Number Forms: U+218A, U+218B.
        if (sequence == 0xe2868a00 || sequence == 0xe2868b00) {
          return F_true;
        }

        // Arrows to Miscellaneous Technical: U+2190 to U+2328.
        if (sequence >= 0xe2869000 && sequence <= 0xe28ca800) {
          return F_true;
        }

        // Miscellaneous Technical: U+232B to U+2426.
        if (sequence >= 0xe28cab00 && sequence <= 0xe290a600) {
          return F_true;
        }

        // Optical Character Recognition: U+2440 to U+244A.
        if (sequence >= 0xe2918000 && sequence <= 0xe2918a00) {
          return F_true;
        }

        // Enclosed Alphanumerics: U+249C to U+24E9.
        if (sequence >= 0xe2929c00 && sequence <= 0xe293a900) {
          return F_true;
        }

        // Box Drawing to Geometric Shapes: U+2500 to U+2767.
        if (sequence >= 0xe2948000 && sequence <= 0xe29da700) {
          return F_true;
        }

        // Dingbats to Miscellaneous Mathematical Symbols-A: U+2794 to U+27C4.
        if (sequence >= 0xe29e9400 && sequence <= 0xe29f8400) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-A: U+27C7 to U+27E5.
        if (sequence >= 0xe29f8700 && sequence <= 0xe29fa500) {
          return F_true;
        }

        // Supplemental Arrows-A: U+27F0 to U+27FF.
        if (sequence >= 0xe29fb000 && sequence <= 0xe29fbf00) {
          return F_true;
        }

        // Braille Patterns to Miscellaneous Mathematical Symbols-B: U+2800 to U+2982.
        if (sequence >= 0xe2a08000 && sequence <= 0xe2a68200) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+2999 to U+29D7.
        if (sequence >= 0xe2a69900 && sequence <= 0xe2a79700) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+29DC to U+29FB.
        if (sequence >= 0xe2a79c00 && sequence <= 0xe2a7bb00) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B to Supplemental Mathematical Operators: U+29FE to U+2B73.
        if (sequence >= 0xe2a7be00 && sequence <= 0xe2adb300) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2B76 to U+2B95.
        if (sequence >= 0xe2adb600 && sequence <= 0xe2ae9500) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2B97 to U+2BFF.
        if (sequence >= 0xe2ae9700 && sequence <= 0xe2afbf00) {
          return F_true;
        }

        // Coptic: U+2CE5 to U+2CEA.
        if (sequence >= 0xe2b3a500 && sequence <= 0xe2b3aa00) {
          return F_true;
        }

        // Supplemental Punctuation: U+2E50, U+2E51.
        if (sequence == 0xe2b99000 || sequence == 0xe2b99100) {
          return F_true;
        }

        // CJK Radicals Supplement: U+2E80 to U+2E99.
        if (sequence >= 0xe2ba8000 && sequence <= 0xe2ba9900) {
          return F_true;
        }

        // CJK Radicals Supplement: U+2E9B to U+2EF3.
        if (sequence >= 0xe2ba9b00 && sequence <= 0xe2bbb300) {
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
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+3004, U+3012, U+3013, U+3020.
        if (sequence == 0xe3808400 || sequence == 0xe3809200 || sequence == 0xe3809300 || sequence == 0xe380a000) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+3036, U+3037, U+303E, U+303F.
        if (sequence == 0xe380b600 || sequence == 0xe380b700 || sequence == 0xe380be00 || sequence == 0xe380bf00) {
          return F_true;
        }

        // Hiragana: U+309B, U+309C.
        if (sequence == 0xe3829b00 || sequence == 0xe3829c00) {
          return F_true;
        }

        // Kanbun: U+3190, U+3191.
        if (sequence == 0xe3869000 || sequence == 0xe3869100) {
          return F_true;
        }

        // Kanbun to CJK Strokes: U+3196 to U+31E3.
        if (sequence >= 0xe3869600 && sequence <= 0xe387a300) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3200 to U+321E.
        if (sequence >= 0xe3888000 && sequence <= 0xe3889e00) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+322A to U+3247.
        if (sequence >= 0xe388aa00 && sequence <= 0xe3898700) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3250.
        if (sequence == 0xe3899000) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3260 to U+327F.
        if (sequence >= 0xe389a000 && sequence <= 0xe389bf00) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+328A to U+32B0.
        if (sequence >= 0xe38a8a00 && sequence <= 0xe38ab000) {
          return F_true;
        }

        // Enclosed CJK Letters and Months to CJK Compatibility: U+32C0 to U+33FF.
        if (sequence >= 0xe38b8000 && sequence <= 0xe38fbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe4) {

        // Yijing Hexagram Symbols: U+4DC0 to U+4DFF.
        if (sequence >= 0xe4b78000 && sequence <= 0xe4b7bf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Yi Radicals: U+A490 to U+A4C6.
        if (sequence >= 0xea929000 && sequence <= 0xea938600) {
          return F_true;
        }

        // Modifier Tone Letters: U+A700 to U+A716.
        if (sequence >= 0xea9c8000 && sequence <= 0xea9c9600) {
          return F_true;
        }

        // Modifier Tone Letters: U+A720, U+A721.
        if (sequence == 0xea9ca000 || sequence == 0xea9ca100) {
          return F_true;
        }

        // Latin Extended-D: U+A789, U+A78A.
        if (sequence == 0xea9e8900 || sequence == 0xea9e8a00) {
          return F_true;
        }

        // Syloti Nagri: U+A828 to U+A82B.
        if (sequence >= 0xeaa0a800 && sequence <= 0xeaa0ab00) {
          return F_true;
        }

        // Common Indic Number Forms: U+A836 to U+A839.
        if (sequence >= 0xeaa0b600 && sequence <= 0xeaa0b900) {
          return F_true;
        }

        // Myanmar Extended-A: U+AA77 to U+AA79.
        if (sequence >= 0xeaa9b700 && sequence <= 0xeaa9b900) {
          return F_true;
        }

        // Latin Extended-E: U+AB5B, U+AB6A, U+AB6B.
        if (sequence == 0xeaad9b00 || sequence == 0xeaadaa00 || sequence == 0xeaadab00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // Alphabetic Presentation Forms: U+FB29.
        if (sequence == 0xefaca900) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FBB2 to U+FBC2.
        if (sequence >= 0xefaeb200 && sequence <= 0xefaf8200) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FD40 to U+FD4F.
        if (sequence >= 0xefb58000 && sequence <= 0xefb58f00) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FDCF.
        if (sequence == 0xefb78f00) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FDFC to U+FDFF.
        if (sequence >= 0xefb7bc00 && sequence <= 0xefb7bf00) {
          return F_true;
        }

        // Small Form Variants: U+FE62.
        if (sequence == 0xefb9a200) {
          return F_true;
        }

        // Small Form Variants: U+FE64 to U+FE66.
        if (sequence >= 0xefb9a400 && sequence <= 0xefb9a600) {
          return F_true;
        }

        // Small Form Variants: U+FE69.
        if (sequence == 0xefb9a900) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF04, U+FF0B.
        if (sequence == 0xefbc8400 || sequence == 0xefbc8b00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF1C to U+FF1E.
        if (sequence >= 0xefbc9c00 && sequence <= 0xefbc9e00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF3E, U+FF40.
        if (sequence == 0xefbcbe00 || sequence == 0xefbd8000) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE0 to U+FFE6.
        if (sequence >= 0xefbfa000 && sequence <= 0xefbfa600) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF5C, U+FF5E, U+FFE2.
        if (sequence == 0xefbd9c00 || sequence == 0xefbd9e00 || sequence == 0xefbfa200) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE8 to U+FFEE.
        if (sequence >= 0xefbfa800 && sequence <= 0xefbfae00) {
          return F_true;
        }

        // Specials: U+FFFC, U+FFFD.
        if (sequence == 0xefbfbc00 || sequence == 0xefbfbd00) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(sequence) == 0x90) {

        // Aegean Numbers: U+10137 to U+1013F.
        if (sequence >= 0xf09084b7 && sequence <= 0xf09084bf) {
          return F_true;
        }

        // Ancient Greek Numbers: U+10179 to U+10189.
        if (sequence >= 0xf09085b9 && sequence <= 0xf0908689) {
          return F_true;
        }

        // Ancient Greek Numbers: U+1018C to U+1018E.
        if (sequence >= 0xf090868c && sequence <= 0xf090868e) {
          return F_true;
        }

        // Ancient Symbols: U+10190 to U+1019C.
        if (sequence >= 0xf0908690 && sequence <= 0xf090869c) {
          return F_true;
        }

        // Ancient Symbols: U+10190 to U+1019C.
        if (sequence >= 0xf0908690 && sequence <= 0xf090869c) {
          return F_true;
        }

        // Ancient Symbols: U+101A0.
        if (sequence == 0xf09086a0) {
          return F_true;
        }

        // Phaistos Disc: U+101D0 to U+101FC.
        if (sequence >= 0xf0908790 && sequence <= 0xf09087bc) {
          return F_true;
        }

        // Palmyrene: U+10877, U+10878.
        if (sequence == 0xf090a1b7 || sequence == 0xf090a1b8) {
          return F_true;
        }

        // Manichaean: U+10AC8.
        if (sequence == 0xf090ab88) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Ahom: U+1173F.
        if (sequence == 0xf0919cbf) {
          return F_true;
        }

        // Tamil Supplement: U+11FD5 to U+11FF1.
        if (sequence >= 0xf091bf95 && sequence <= 0xf091bfb1) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D6C1, U+1D6FB, U+1D715, U+1D735.
        if (sequence == 0xf09d9b81 || sequence == 0xf09d9bbb || sequence == 0x09d9c95 || sequence == 0xf09d9cb5) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D74F, U+1D76F, U+1D789, U+1D7A9.
        if (sequence == 0xf09d9d8f || sequence == 0xf09d9daf || sequence == 0xf09d9e89 || sequence == 0xf09d9ea9) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D7C3, U+1EEF0, U+1EEF1.
        if (sequence == 0xf09d9f83 || sequence == 0xf09ebbb0 || sequence == 0xf09ebbb1) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x96) {

        // Pahawh Hmong: U+16B3C to U+16B3F.
        if (sequence >= 0xf096acbc && sequence <= 0xf096acbf) {
          return F_true;
        }

        // Pahawh Hmong: U+16B45.
        if (sequence == 0xf096ad85) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9b) {

        // Duployan: U+1BC9C.
        if (sequence == 0xf09bb29c) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9c) {

        // Znamenny Musical Notation: U+1CF50 to U+1CFC3.
        if (sequence >= 0xf09cbd90 && sequence <= 0xf09cbf83) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

        // Byzantine Musical Notation: U+1D000 to U+1D1EA.
        if (sequence >= 0xf09d8080 && sequence <= 0xf09d87aa) {
          return F_true;
        }

        // Ancient Greek Musical Notation: U+1D200 to U+1D245.
        if (sequence >= 0xf09d8080 && sequence <= 0xf09d8985) {
          return F_true;
        }

        // Tai Xuan Jing Symbols: U+1D300 to U+1D356.
        if (sequence >= 0xf09d8c80 && sequence <= 0xf09d8d96) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D6C1, U+1D6DB, U+1D6FB, U+1D715.
        if (sequence == 0xf09d9b81 || sequence == 0xf09d9b9b || sequence == 0xf09d9bbb || sequence == 0xf09d9c95) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D735, U+1D74F, U+1D76F, U+1D789.
        if (sequence == 0xf09d9cb5 || sequence == 0xf09d9d8f || sequence == 0xf09d9daf || sequence == 0xf09d9e89) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D7A9, U+1D7C3.
        if (sequence == 0xf09d9ea9 || sequence == 0xf09d9f83) {
          return F_true;
        }

        // Sutton SignWriting: U+1D800 to U+1D9FF.
        if (sequence >= 0xf09da080 && sequence <= 0xf09da7bf) {
          return F_true;
        }

        // Sutton SignWriting: U+1DA37 to U+1DA3A.
        if (sequence >= 0xf09da8b7 && sequence <= 0xf09da8ba) {
          return F_true;
        }

        // Sutton SignWriting: U+1DA6D to U+1DA86.
        if (sequence >= 0xf09da9ad && sequence <= 0xf09daa86) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9e) {

        // Nyiakeng Puachue Hmong: U+1E14F.
        if (sequence == 0xf09e858f) {
          return F_true;
        }

        // Wancho: U+1E2FF.
        if (sequence == 0xf09e8bbf) {
          return F_true;
        }

        // Indic Siyaq Numbers: U+1ECAC, U+ECB0.
        if (sequence == 0xf09eb2ac || sequence == 0xf09eb2b0) {
          return F_true;
        }

        // Ottoman Siyaq Numbers: U+1ED2E.
        if (sequence == 0xf09eb4ae) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EEF0, U+1EEF1.
        if (sequence == 0xf09ebbb0 || sequence == 0xf09ebbb1) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Mahjong Tiles to Domino Tiles: U+1F000 to U+1F093.
        if (sequence >= 0xf09f8080 && sequence <= 0xf09f8293) {
          return F_true;
        }

        // Playing Cards: U+1F0A0 to U+1F0AE.
        if (sequence >= 0xf09f82a0 && sequence <= 0xf09f82ae) {
          return F_true;
        }

        // Playing Cards: U+1F0B1 to U+1F0BF.
        if (sequence >= 0xf09f82b1 && sequence <= 0xf09f82bf) {
          return F_true;
        }

        // Playing Cards: U+1F0C1 to U+1F0CF.
        if (sequence >= 0xf09f8381 && sequence <= 0xf09f838f) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F0D1 to U+1F1AD.
        if (sequence >= 0xf09f8391 && sequence <= 0xf09f86ad) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F10D to U+1F1AD.
        if (sequence >= 0xf09f848d && sequence <= 0xf09f86ad) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement to Enclosed Ideographic Supplement: U+1F1E6 to U+1F202.
        if (sequence >= 0xf09f87a6 && sequence <= 0xf09f8882) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F210 to U+1F23B.
        if (sequence >= 0xf09f8890 && sequence <= 0xf09f88bb) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F240 to U+1F248.
        if (sequence >= 0xf09f8980 && sequence <= 0xf09f8988) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F250, U+1F251.
        if (sequence == 0xf09f8990 || sequence == 0xf09f8991) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F260 to U+1F265.
        if (sequence >= 0xf09f89a0 && sequence <= 0xf09f89a5) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F300 to U+1F6EC.
        if (sequence >= 0xf09f8c80 && sequence <= 0xf09f9bac) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6F0 to U+1F6FC.
        if (sequence >= 0xf09f9bb0 && sequence <= 0xf09f9bbc) {
          return F_true;
        }

        // Alchemical Symbols: U+1F6F0 to U+1F773.
        if (sequence >= 0xf09f9c80 && sequence <= 0xf09f9db3) {
          return F_true;
        }

        // Geometric Shapes Extended: U+1F780 to U+1F7D8.
        if (sequence >= 0xf09f9e80 && sequence <= 0xf09f9f98) {
          return F_true;
        }

        // Geometric Shapes Extended: U+1F7E0 to U+1F7EB.
        if (sequence >= 0xf09f9fa0 && sequence <= 0xf09f9fab) {
          return F_true;
        }

        // Geometric Shapes Extended: U+1F7F0.
        if (sequence == 0xf09f9fb0) {
          return F_true;
        }

        // Supplemental Arrows-C: U+1F800 to U+1F80B.
        if (sequence >= 0xf09fa080 && sequence <= 0xf09fa08b) {
          return F_true;
        }

        // Supplemental Arrows-C: U+1F810 to U+1F847.
        if (sequence >= 0xf09fa090 && sequence <= 0xf09fa187) {
          return F_true;
        }

        // Supplemental Arrows-C: U+1F850 to U+1F887.
        if (sequence >= 0xf09fa190 && sequence <= 0xf09fa287) {
          return F_true;
        }

        // Supplemental Arrows-C: U+1F890 to U+1F8AD.
        if (sequence >= 0xf09fa290 && sequence <= 0xf09fa2ad) {
          return F_true;
        }

        // Supplemental Arrows-C: U+1F8B0, U+1F8B1.
        if (sequence == 0xf09fa2b0 || sequence == 0xf09fa2b1) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs to Chess Symbols: U+1F900 to U+1FA53.
        if (sequence >= 0xf09fa480 && sequence <= 0xf09fa993) {
          return F_true;
        }

        // Chess Symbols: U+1FA60 to U+1FA6D.
        if (sequence >= 0xf09fa9a0 && sequence <= 0xf09fa9ad) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA70 to U+1FA74.
        if (sequence >= 0xf09fa9b0 && sequence <= 0xf09fa9b4) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA78 to U+1FA7C.
        if (sequence >= 0xf09fa9b8 && sequence <= 0xf09fa9bc) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA80 to U+1FA86.
        if (sequence >= 0xf09faa80 && sequence <= 0xf09faa86) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA90 to U+1FAAC.
        if (sequence >= 0xf09faa90 && sequence <= 0xf09faaac) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAB0 to U+1FAC5.
        if (sequence >= 0xf09faab0 && sequence <= 0xf09fab85) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAD0 to U+1FAE7.
        if (sequence >= 0xf09fab90 && sequence <= 0xf09faba7) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAF0 to U+1FAF6.
        if (sequence >= 0xf09fabb0 && sequence <= 0xf09fabb6) {
          return F_true;
        }

        // Symbols for Legacy Computing: U+1FB00 to U+1FBCA.
        if (sequence >= 0xf09fac80 && sequence <= 0xf09faf8a) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

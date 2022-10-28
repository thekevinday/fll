#include "utf.h"
#include "private-utf.h"
#include "private-utf_punctuation.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_punctuation(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xc2) {

        // Latin-1 Supplement: U+00A1, U+00A7, U+00AB, U+00B6.
        if (sequence == 0xc2a10000 || sequence == 0xc2a70000 || sequence == 0xc2ab0000 || sequence == 0xc2b60000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00B7, U+00BB, U+00BF.
        if (sequence == 0xc2b70000 || sequence == 0xc2bb0000 || sequence == 0xc2bf0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xcd) {

        // Greek and Coptic: U+037E.
        if (sequence == 0xcdbe0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xce) {

        // Greek and Coptic: U+0387.
        if (sequence == 0xce870000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd5) {

        // Armenian: U+055A to U+055F.
        if (sequence >= 0xd59a0000 && sequence <= 0xd59f0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd6) {

        // Armenian: U+0589, U+058A.
        if (sequence == 0xd6890000 || sequence == 0xd68a0000) {
          return F_true;
        }

        // Hebrew: U+05BE.
        if (sequence == 0xd6be0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd7) {

        // Hebrew: U+05C0, U+05C3, U+05C6.
        if (sequence == 0xd7800000 || sequence == 0xd7830000 || sequence == 0xd7860000) {
          return F_true;
        }

        // Hebrew: U+05F3, U+05F4.
        if (sequence == 0xd7b30000 || sequence == 0xd7b40000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd8) {

        // Arabic: U+0609, U+060A, U+060C, U+060D.
        if (sequence == 0xd8890000 || sequence == 0xd88a0000 || sequence == 0xd88c0000 || sequence == 0xd88d0000) {
          return F_true;
        }

        // Arabic: U+061B.
        if (sequence == 0xd89b0000) {
          return F_true;
        }

        // Arabic: U+061D to U+061F.
        if (sequence >= 0xd89d0000 && sequence <= 0xd89f0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdb) {

        // Arabic: U+06D4.
        if (sequence == 0xdb940000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xd9) {

        // Arabic: U+066A to U+066D.
        if (sequence >= 0xd9aa0000 && sequence <= 0xd9ad0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdc) {

        // Syriac: U+0700 to U+070D.
        if (sequence >= 0xdc800000 && sequence <= 0xdc8d0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdf) {

        // NKo: U+07F7 to U+07F9.
        if (sequence >= 0xdfb70000 && sequence <= 0xdfb90000) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Samaritan: U+0830 to U+083E.
        if (sequence >= 0xe0a0b000 && sequence <= 0xe0a0be00) {
          return F_true;
        }

        // Mandaic: U+085E.
        if (sequence == 0xe0a19e00) {
          return F_true;
        }

        // Devanagari: U+0964, U+0965, U+0970.
        if (sequence == 0xe0a5a400 || sequence == 0xe0a5a500 || sequence == 0xe0a5b000) {
          return F_true;
        }

        // Bengali: U+09FD.
        if (sequence == 0xe0a7bd00) {
          return F_true;
        }

        // Gurmukhi: U+0A64, U+0A65, U+0A76.
        if (sequence == 0xe0a9a400 || sequence == 0xe0a9a500 || sequence == 0xe0a9b600) {
          return F_true;
        }

        // Gujarati: U+0AF0.
        if (sequence == 0xe0abb000) {
          return F_true;
        }

        // Telugu: U+0C77.
        if (sequence == 0xe0b1b700) {
          return F_true;
        }

        // Kannada: U+0C84.
        if (sequence == 0xe0b28400) {
          return F_true;
        }

        // Sinhala: U+0DF4.
        if (sequence == 0xe0b7b400) {
          return F_true;
        }

        // Thai: U+0E4F, U+0E5A, U+0E5B.
        if (sequence == 0xe0b98f00 || sequence == 0xe0b99a00 || sequence == 0xe0b99b00) {
          return F_true;
        }

        // Tibetan: U+0F04 to U+0F12.
        if (sequence >= 0xe0bc8400 && sequence <= 0xe0bc9200) {
          return F_true;
        }

        // Tibetan: U+0F14, U+0F85.
        if (sequence == 0xe0bc9400 || sequence == 0xe0be8500) {
          return F_true;
        }

        // Tibetan: U+0F3A to U+0F3D.
        if (sequence >= 0xe0bcba00 && sequence <= 0xe0bcbd00) {
          return F_true;
        }

        // Tibetan: U+0FD0 to U+0FD4.
        if (sequence >= 0xe0bf9000 && sequence <= 0xe0bf9400) {
          return F_true;
        }

        // Tibetan: U+0FD9 to U+0FDA.
        if (sequence >= 0xe0bf9900 && sequence <= 0xe0bf9a00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Myanmar: U+104A to U+104F.
        if (sequence >= 0xe1818a00 && sequence <= 0xe1818f00) {
          return F_true;
        }

        // Georgian: U+10FB.
        if (sequence == 0xe183bb00) {
          return F_true;
        }

        // Ethiopic: U+1360 to U+1368.
        if (sequence >= 0xe18da000 && sequence <= 0xe18da800) {
          return F_true;
        }

        // Unified Canadian Aboriginal Syllabics: U+1400, U+166E.
        if (sequence == 0xe1908000 || sequence == 0xe199ae00) {
          return F_true;
        }

        // Ogham: U+169B, U+169C.
        if (sequence == 0xe19a9b00 || sequence == 0xe19a9c00) {
          return F_true;
        }

        // Runic: U+16EB to U+16ED.
        if (sequence >= 0xe19bab00 && sequence <= 0xe19bad00) {
          return F_true;
        }

        // Hanunoo: U+1735, U+1736.
        if (sequence == 0xe19cb500 || sequence == 0xe19cb600) {
          return F_true;
        }

        // Khmer: U+17D4 to U+17D6.
        if (sequence >= 0xe19f9400 && sequence <= 0xe19f9600) {
          return F_true;
        }

        // Khmer: U+17D8 to U+17DA.
        if (sequence >= 0xe19f9800 && sequence <= 0xe19f9a00) {
          return F_true;
        }

        // Mongolian: U+1800 to U+180A.
        if (sequence >= 0xe1a08000 && sequence <= 0xe1a08a00) {
          return F_true;
        }

        // Limbu: U+1944, U+1945.
        if (sequence == 0xe1a58400 || sequence == 0xe1a58500) {
          return F_true;
        }

        // Buginese: U+1A1E, U+1A1F.
        if (sequence == 0xe1a89e00 || sequence == 0xe1a89f00) {
          return F_true;
        }

        // Tai Tham: U+1AA0 to U+1AA6.
        if (sequence >= 0xe1aaa000 && sequence <= 0xe1aaa600) {
          return F_true;
        }

        // Tai Tham: U+1AA8 to U+1AAD.
        if (sequence >= 0xe1aaa800 && sequence <= 0xe1aaad00) {
          return F_true;
        }

        // Balinese: U+1B5A to U+1B60.
        if (sequence >= 0xe1ad9a00 && sequence <= 0xe1ada000) {
          return F_true;
        }

        // Balinese: U+1B7D to U+1B7E.
        if (sequence == 0xe1adbd00 || sequence == 0xe1adbe00) {
          return F_true;
        }

        // Batak: U+1BFC to U+1BFF.
        if (sequence >= 0xe1afbc00 && sequence <= 0xe1afbf00) {
          return F_true;
        }

        // Lepcha: U+1C3B to U+1C3F.
        if (sequence >= 0xe1b0bb00 && sequence <= 0xe1b0bf00) {
          return F_true;
        }

        // Ol Chiki: U+1C7E, U+1C7F.
        if (sequence == 0xe1b1be00 || sequence == 0xe1b0bf00) {
          return F_true;
        }

        // Sundanese Supplement: U+1CC0 to U+1CC7.
        if (sequence >= 0xe1b38000 && sequence <= 0xe1b38700) {
          return F_true;
        }

        // Ol Chiki: U+1C7E, U+1C7F.
        if (sequence == 0xe1b1be00 || sequence == 0xe1b1bf00) {
          return F_true;
        }

        // Vedic Extensions: U+1CD3.
        if (sequence == 0xe1b39300) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // Superscripts and Subscripts: U+207D, U+207E, U+208D, U+208E.
        if (sequence == 0xe281bd00 || sequence == 0xe281be00 || sequence == 0xe2828d00 || sequence == 0xe2828e00) {
          return F_true;
        }

        // General Punctuation: U+2010 to U+2027.
        if (sequence >= 0xe2809000 && sequence <= 0xe280a700) {
          return F_true;
        }

        // General Punctuation: U+2030 to U+205E.
        if (sequence >= 0xe280b000 && sequence <= 0xe2819e00) {
          return F_true;
        }

        // Miscellaneous Technical: U+2308 to U+230B.
        if (sequence >= 0xe28c8800 && sequence <= 0xe28c8b00) {
          return F_true;
        }

        // Miscellaneous Technical: U+2329, U+232A.
        if (sequence == 0xe28ca900 || sequence == 0xe28caa00) {
          return F_true;
        }

        // Dingbats: U+2768 to U+2775.
        if (sequence >= 0xe29da800 && sequence <= 0xe29db500) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-A: U+27C5, U+27C6.
        if (sequence == 0xe29f8500 || sequence == 0xe29f8600) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-A: U+27E6 to U+27EF.
        if (sequence >= 0xe29fa600 && sequence <= 0xe29faf00) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+2983 to U+2998.
        if (sequence >= 0xe2a68300 && sequence <= 0xe2a69800) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+29D8 to U+29DB.
        if (sequence >= 0xe2a79800 && sequence <= 0xe2a79b00) {
          return F_true;
        }

        // Miscellaneous Mathematical Symbols-B: U+29FC to U+29FD.
        if (sequence >= 0xe2a7bc00 && sequence <= 0xe2a7bd00) {
          return F_true;
        }

        // Coptic: U+2CF9 to U+2CFC.
        if (sequence >= 0xe2b3b900 && sequence <= 0xe2b3bc00) {
          return F_true;
        }

        // Coptic: U+2CFE to U+2CFF.
        if (sequence >= 0xe2b3be00 && sequence <= 0xe2b3bf00) {
          return F_true;
        }

        // Tifinagh: U+2D70.
        if (sequence == 0xe2b5b000) {
          return F_true;
        }

        // Supplemental Punctuation: U+2E00 to U+2E2E.
        if (sequence >= 0xe2b88000 && sequence <= 0xe2b8ae00) {
          return F_true;
        }

        // Supplemental Punctuation: U+2E30 to U+2E4F.
        if (sequence >= 0xe2b8b000 && sequence <= 0xe2b98f00) {
          return F_true;
        }

        // Supplemental Punctuation: U+2E52 to U+2E5D.
        if (sequence >= 0xe2b99200 && sequence <= 0xe2b99d00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+3001 to U+3003.
        if (sequence >= 0xe3808100 && sequence <= 0xe3808300) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+3008 to U+3011.
        if (sequence >= 0xe3808800 && sequence <= 0xe3809100) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+3014 to U+301F.
        if (sequence >= 0xe3809400 && sequence <= 0xe3809f00) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+3030, U+303D.
        if (sequence == 0xe380b000 || sequence == 0xe380bd00) {
          return F_true;
        }

        // Katakana: U+30A0, U+30FB.
        if (sequence == 0xe382a000 || sequence == 0xe383bb00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Lisu: U+A4FE, U+A4FF.
        if (sequence == 0xea93be00 || sequence == 0xea93bf00) {
          return F_true;
        }

        // Vai: U+A60D to U+A60F.
        if (sequence >= 0xea988d00 && sequence <= 0xea988f00) {
          return F_true;
        }

        // Cyrillic Extended-B: U+A673, U+A67E.
        if (sequence == 0xea99b300 || sequence == 0xea99be00) {
          return F_true;
        }

        // Bamum: U+A6F2 to U+A6F7.
        if (sequence >= 0xea9bb200 && sequence <= 0xea9bb700) {
          return F_true;
        }

        // Phags-pa: U+A874 to U+A877.
        if (sequence >= 0xeaa1b400 && sequence <= 0xeaa1b700) {
          return F_true;
        }

        // Saurashtra: U+A8CE, U+A8CF.
        if (sequence == 0xeaa38e00 || sequence == 0xeaa38f00) {
          return F_true;
        }

        // Devanagari Extended: U+A8F8 to U+A8FA.
        if (sequence >= 0xeaa3b800 && sequence <= 0xeaa3ba00) {
          return F_true;
        }

        // Devanagari Extended: U+A8FC to U+A8FF.
        if (sequence >= 0xeaa3bc00 && sequence <= 0xeaa3bf00) {
          return F_true;
        }

        // Kayah Li: U+A92E, U+A92F.
        if (sequence == 0xeaa4ae00 || sequence == 0xeaa4af00) {
          return F_true;
        }

        // Rejang: U+A95F.
        if (sequence == 0xeaa59f00) {
          return F_true;
        }

        // Javanese: U+A9C1 to U+A9DF.
        if (sequence >= 0xeaa78100 && sequence <= 0xeaa79f00) {
          return F_true;
        }

        // Cham: U+AA5C to U+AA5F.
        if (sequence >= 0xeaa99c00 && sequence <= 0xeaa99f00) {
          return F_true;
        }

        // Tai Viet: U+AADE, U+AADF.
        if (sequence == 0xeaab9e00 || sequence == 0xeaab9f00) {
          return F_true;
        }

        // Meetei Mayek Extensions: U+AAF0, U+AAF1.
        if (sequence == 0xeaabb000 || sequence == 0xeaabb100) {
          return F_true;
        }

        // Meetei Mayek: U+ABEB.
        if (sequence == 0xeaafab00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // Alphabetic Presentation Forms-A: U+FD3E, U+FD3F.
        if (sequence == 0xefb4be00 || sequence == 0xefb4bf00) {
          return F_true;
        }

        // Vertical Forms: U+FE10 to U+FE19.
        if (sequence >= 0xefb89000 && sequence <= 0xefb89900) {
          return F_true;
        }

        // CJK Compatibility Forms: U+FE30 to U+FE52.
        if (sequence >= 0xefb8b000 && sequence <= 0xefb99200) {
          return F_true;
        }

        // Small Form Variants: U+FE54 to U+FE63.
        if (sequence >= 0xefb99400 && sequence <= 0xefb9a300) {
          return F_true;
        }

        // Small Form Variants: U+FE63, U+FE68, U+FE6A, U+FE6B.
        if (sequence == 0xefb9a300 || sequence == 0xefb9a800 || sequence == 0xefb9aa00 || sequence == 0xefb9ab00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF01 to U+FF03.
        if (sequence >= 0xefbc8100 && sequence <= 0xefbc8300) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF05 to U+FF0A.
        if (sequence >= 0xefbc8500 && sequence <= 0xefbc8a00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF0C to U+FF0F.
        if (sequence >= 0xefbc8c00 && sequence <= 0xefbc8f00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF1A to U+FF1B.
        if (sequence >= 0xefbc9a00 && sequence <= 0xefbc9b00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF1F, U+FF20.
        if (sequence == 0xefbc9f00 || sequence == 0xefbca000) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF3B to U+FF3D.
        if (sequence >= 0xefbcbb00 && sequence <= 0xefbcbd00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF3F, U+FF5B, U+FF5D.
        if (sequence == 0xefbcbf00 || sequence == 0xefbd9b00 || sequence == 0xefbd9d00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF5F to U+FF65.
        if (sequence >= 0xefbd9f00 && sequence <= 0xefbda500) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {
      if (macro_f_utf_char_t_to_char_2(sequence) == 0x90) {

        // Aegean Numbers: U+10100 to U+10102.
        if (sequence >= 0xf0908480 && sequence <= 0xf0908482) {
          return F_true;
        }

        // Ugaritic: U+1039F, U+103D0.
        if (sequence == 0xf0908e9f || sequence == 0xf0908f90) {
          return F_true;
        }

        // Caucasian Albanian: U+1056F.
        if (sequence == 0xf09095af) {
          return F_true;
        }

        // Imperial Aramaic: U+10857.
        if (sequence == 0xf090a197) {
          return F_true;
        }

        // Phoenician: U+1091F.
        if (sequence == 0xf090a49f) {
          return F_true;
        }

        // Lydian: U+1093F.
        if (sequence == 0xf090a4bf) {
          return F_true;
        }

        // Kharoshthi: U+10A50 to U+10A58.
        if (sequence >= 0xf090a990 && sequence <= 0xf090a998) {
          return F_true;
        }

        // Old South Arabian: U+10A7F.
        if (sequence == 0xf090a9bf) {
          return F_true;
        }

        // Manichaean: U+10AF0 to U+10AF6.
        if (sequence >= 0xf090abb0 && sequence <= 0xf090abb6) {
          return F_true;
        }

        // Avestan: U+10B39.
        if (sequence == 0xf090acb9) {
          return F_true;
        }

        // Avestan: U+10B3A to U+10B3F.
        if (sequence >= 0xf090acba && sequence <= 0xf090acbf) {
          return F_true;
        }

        // Psalter Pahlavi: U+10B99 to U+10B9C.
        if (sequence >= 0xf090ae99 && sequence <= 0xf090ae9c) {
          return F_true;
        }

        // Yezidi: U+10EAD.
        if (sequence == 0xf090baad) {
          return F_true;
        }

        // Sogdian: U+10F55 to U+10F59.
        if (sequence >= 0xf090bd95 && sequence <= 0xf090bd99) {
          return F_true;
        }

        // Old Uyghur: U+10F86 to U+10F89.
        if (sequence >= 0xf090be86 && sequence <= 0xf090be89) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Brahmi: U+11047 to U+1104D.
        if (sequence >= 0xf0918187 && sequence <= 0xf091818d) {
          return F_true;
        }

        // Kaithi: U+110BB to U+110C1.
        if (sequence >= 0xf09182bb && sequence <= 0xf0918381) {
          return F_true;
        }

        // Chakma: U+11140 to U+11143.
        if (sequence >= 0xf0918580 && sequence <= 0xf0918583) {
          return F_true;
        }

        // Mahajani: U+11174 to U+11175.
        if (sequence == 0xf09185b4 || sequence == 0xf09185b5) {
          return F_true;
        }

        // Sharada: U+111C5 to U+111C8.
        if (sequence >= 0xf0918785 && sequence <= 0xf0918785) {
          return F_true;
        }

        // Sharada: U+111CD.
        if (sequence == 0xf091878d) {
          return F_true;
        }

        // Sharada: U+111DB to U+111DF.
        if (sequence >= 0xf091879b && sequence <= 0xf091879f) {
          return F_true;
        }

        // Khojki: U+11238 to U+1123D.
        if (sequence >= 0xf09188b8 && sequence <= 0xf09188bd) {
          return F_true;
        }

        // Multani: U+112A9.
        if (sequence == 0xf0918aa9) {
          return F_true;
        }

        // Newa: U+1144B to U+1144F.
        if (sequence >= 0xf091918b && sequence <= 0xf091918f) {
          return F_true;
        }

        // Newa: U+1145A.
        if (sequence == 0xf091919a) {
          return F_true;
        }

        // Tirhuta: U+114C6.
        if (sequence == 0xf0919386) {
          return F_true;
        }

        // Siddham: U+115C1 to U+115D7.
        if (sequence >= 0xf0919781 && sequence <= 0xf0919797) {
          return F_true;
        }

        // Modi: U+11641 to U+11643.
        if (sequence >= 0xf0919981 && sequence <= 0xf0919983) {
          return F_true;
        }

        // Mongolian Supplement: U+11660 to U+1166C.
        if (sequence >= 0xf09199a0 && sequence <= 0xf09199ac) {
          return F_true;
        }

        // Ahom: U+1173C to U+1173E.
        if (sequence >= 0xf0919cbc && sequence <= 0xf0919cbe) {
          return F_true;
        }

        // Dogra: U+1183B.
        if (sequence == 0xf091a0bb) {
          return F_true;
        }

        // Dives Akuru: U+11944 to U+11946.
        if (sequence >= 0xf091a584 && sequence <= 0xf091a586) {
          return F_true;
        }

        // Nandinagari: U+119E2.
        if (sequence == 0xf091a7a2) {
          return F_true;
        }

        // Zanabazar Square: U+11A3F to U+11A46.
        if (sequence >= 0xd806de3f && sequence <= 0xf091a986) {
          return F_true;
        }

        // Soyombo: U+11A9A to U+11A9C.
        if (sequence >= 0xd806de9a && sequence <= 0xf091aa9c) {
          return F_true;
        }

        // Soyombo: U+11A9E to U+11AA2.
        if (sequence >= 0xf091aa9e && sequence <= 0xf091aaa2) {
          return F_true;
        }

        // Bhaiksuki: U+11C41 to U+11C45.
        if (sequence >= 0xf091b181 && sequence <= 0xf091b185) {
          return F_true;
        }

        // Marchen: U+11C70, U+11C71.
        if (sequence == 0xf091b1b0 || sequence == 0xf091b1b1) {
          return F_true;
        }

        // Makasar: U+11EF7, U+11EF8.
        if (sequence == 0xf091bbb7 || sequence == 0xf091bbb8) {
          return F_true;
        }

        // Kawi: U+11F43 to U+11F4F.
        if (sequence >= 0xf091bd83 && sequence <= 0xf091bd8f) {
          return F_true;
        }

        // Tamil Supplement: U+11FFF.
        if (sequence == 0xf091bfbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x92) {

        // Cuneiform Numbers and Punctuation: U+12470 to U+12474.
        if (sequence >= 0xf09291b0 && sequence <= 0xf09291b4) {
          return F_true;
        }

        // Cypro-Minoan: U+12FF1, U+12FF1.
        if (sequence == 0xf092bfb1 || sequence == 0xf092bfb2) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x96) {

        // Mro: U+16A6E, U+16A6F.
        if (sequence == 0xf096a9ae || sequence == 0xf096a9af) {
          return F_true;
        }

        // Bassa Vah: U+16AF5.
        if (sequence == 0xf096abb5) {
          return F_true;
        }

        // Pahawh Hmong: U+16B37 to U+16B3B.
        if (sequence >= 0xf096acb7 && sequence <= 0xf096acbb) {
          return F_true;
        }

        // Pahawh Hmong: U+16B44.
        if (sequence >= 0xf096ad84) {
          return F_true;
        }

        // Medefaidrin: U+16E97 to U+16E9A.
        if (sequence >= 0xf096ba97 && sequence <= 0xf096ba9a) {
          return F_true;
        }

        // Ideographic Symbols and Punctuation: U+16FE2.
        if (sequence == 0xf096bfa2) {
          return F_true;
        }

        // Duployan: U+1BC9F.
        if (sequence == 0xf09bb29f) {
          return F_true;
        }

        // Sutton SignWriting: U+1DA87 to U+1DA8B.
        if (sequence >= 0xf09daa87 && sequence <= 0xf09daa8b) {
          return F_true;
        }

        // Adlam: U+1E95E, U+1E95F.
        if (sequence == 0xf09ea59e || sequence == 0xf09ea59f) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9b) {

        // Duployan: U+1BC9F.
        if (sequence == 0xf09bb29f) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

        // Sutton SignWriting: U+1DA87 to U+1DA8B.
        if (sequence >= 0xf09daa87 && sequence <= 0xf09daa8b) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9e) {

        // Adlam: U+1E95E to U+1E95F.
        if (sequence >= 0xf09ea59e && sequence <= 0xf09ea59f) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "utf.h"
#include "private-utf.h"
#include "private-utf_digit.h"
#include "private-utf_numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  f_status_t private_f_utf_character_is_numeric(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Latin-1 Supplement: U+00B2, U+00B3, U+00B9.
      if (sequence == 0xc2b20000 || sequence == 0xc2b30000 || sequence == 0xc2b90000) {
        return F_true;
      }

      // Latin-1 Supplement: U+00BC to U+00BE.
      if (sequence >= 0xc2bc0000 && sequence <= 0xc2be0000) {
        return F_true;
      }

      // Arabic: U+0660 to U+0669.
      if (sequence >= 0xd9a00000 && sequence <= 0xd9a90000) {
        return F_true;
      }

      // Extended Arabic: U+06F0 to U+06F9.
      if (sequence >= 0xdbb00000 && sequence <= 0xdbb90000) {
        return F_true;
      }

      // NKo: U+07C0 to U+07C9.
      if (sequence >= 0xdf800000 && sequence <= 0xdf890000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Devanagari: U+0966 to U+096F.
        if (sequence >= 0xe0a5a600 && sequence <= 0xe0a5af00) {
          return F_true;
        }

        // Bengali: U+09E6 to U+09EF.
        if (sequence >= 0xe0a7a600 && sequence <= 0xe0a7af00) {
          return F_true;
        }

        // Bengali: U+09F4 to U+09F9.
        if (sequence >= 0xe0a7b400 && sequence <= 0xe0a7b900) {
          return F_true;
        }

        // Gurmukhi: U+0A66 to U+0A6F.
        if (sequence >= 0xe0a9a600 && sequence <= 0xe0a9af00) {
          return F_true;
        }

        // Gujarati: U+0AE6 to U+0AEF.
        if (sequence >= 0xe0aba600 && sequence <= 0xe0abaf00) {
          return F_true;
        }

        // Oriya: U+0B66 to U+0B6F.
        if (sequence >= 0xe0ada600 && sequence <= 0xe0adaf00) {
          return F_true;
        }

        // Oriya: U+0B72 to U+0B77.
        if (sequence >= 0xe0adb200 && sequence <= 0xe0adb700) {
          return F_true;
        }

        // Tamil: U+0BE6 to U+0BF2.
        if (sequence >= 0xe0afa600 && sequence <= 0xe0afb200) {
          return F_true;
        }

        // Telugu: U+0C66 to U+0C6F.
        if (sequence >= 0xe0b1a600 && sequence <= 0xe0b1af00) {
          return F_true;
        }

        // Telugu: U+0C78 to U+0C7E.
        if (sequence >= 0xe0b1b800 && sequence <= 0xe0b1be00) {
          return F_true;
        }

        // Kannada: U+0CE6 to U+0CEF.
        if (sequence >= 0xe0b3a600 && sequence <= 0xe0b3af00) {
          return F_true;
        }

        // Malayalam: U+0D58 to U+0D5E.
        if (sequence >= 0xe0b59800 && sequence <= 0xe0b59e00) {
          return F_true;
        }

        // Malayalam: U+0D66 to U+0D78.
        if (sequence >= 0xe0b5a600 && sequence <= 0xe0b5b800) {
          return F_true;
        }

        // Sinhala: U+0DE6 to U+0DEF.
        if (sequence >= 0xe0b7a600 && sequence <= 0xe0b7af00) {
          return F_true;
        }

        // Thai: U+0E50 to U+0E59.
        if (sequence >= 0xe0b99000 && sequence <= 0xe0b99900) {
          return F_true;
        }

        // Lao: U+0ED0 to U+0ED9.
        if (sequence >= 0xe0bb9000 && sequence <= 0xe0bb9900) {
          return F_true;
        }

        // Tibetan: U+0F20 to U+0F33.
        if (sequence >= 0xe0bca000 && sequence <= 0xe0bcb300) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Myanmar: U+1040 to U+1049.
        if (sequence >= 0xe1818000 && sequence <= 0xe1818900) {
          return F_true;
        }

        // Myanmar (Shan): U+1090 to U+1099.
        if (sequence >= 0xe1829000 && sequence <= 0xe1829900) {
          return F_true;
        }

        // Ethiopic: U+1369 to U+137C.
        if (sequence >= 0xe18da900 && sequence <= 0xe18dbc00) {
          return F_true;
        }

        // Runic: U+16EE to U+16F0.
        if (sequence >= 0xe19bae00 && sequence <= 0xe19bb000) {
          return F_true;
        }

        // Khmer: U+17E0 to U+17E9.
        if (sequence >= 0xe19fa000 && sequence <= 0xe19fa900) {
          return F_true;
        }

        // Khmer: U+17F0 to U+17F9.
        if (sequence >= 0xe19fb000 && sequence <= 0xe19fb900) {
          return F_true;
        }

        // Mongolian: U+1810 to U+1819.
        if (sequence >= 0xe1a09000 && sequence <= 0xe1a09900) {
          return F_true;
        }

        // Limbu: U+1946 to U+194F.
        if (sequence >= 0xe1a58600 && sequence <= 0xe1a58f00) {
          return F_true;
        }

        // New Tai Lue: U+19D0 to U+19DA.
        if (sequence >= 0xe1a79000 && sequence <= 0xe1a79a00) {
          return F_true;
        }

        // Tai Tham (Hora): U+1A80 to U+1A89.
        if (sequence >= 0xe1aa8000 && sequence <= 0xe1aa8900) {
          return F_true;
        }

        // Tai Tham (Tham): U+1A90 to U+1A99.
        if (sequence >= 0xe1aa9000 && sequence <= 0xe1aa9900) {
          return F_true;
        }

        // Balinese: U+1B50 to U+1B59.
        if (sequence >= 0xe1ad9000 && sequence <= 0xe1ad9900) {
          return F_true;
        }

        // Sundanese: U+1BB0 to U+1BB9.
        if (sequence >= 0xe1aeb000 && sequence <= 0xe1aeb900) {
          return F_true;
        }

        // Lepcha: U+1C40 to U+1C49.
        if (sequence >= 0xe1b18000 && sequence <= 0xe1b18900) {
          return F_true;
        }

        // Ol Chiki: U+1C50 to U+1C59.
        if (sequence >= 0xe1b19000 && sequence <= 0xe1b19900) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // Superscripts and Subscripts: U+2070.
        if (sequence == 0xe281b000) {
          return F_true;
        }

        // Superscripts and Subscripts: U+2074 to U+2089.
        if (sequence >= 0xe281b400 && sequence <= 0xe2828900) {
          return F_true;
        }

        // Number Forms: U+2150 to U+2189.
        if (sequence >= 0xe2859000 && sequence <= 0xe2868900) {
          return F_true;
        }

        // Enclosed Alphanumerics: U+2460 to U+249B.
        if (sequence >= 0xe291a000 && sequence <= 0xe2929b00) {
          return F_true;
        }

        // Enclosed Alphanumerics: U+24EA to U+24FF.
        if (sequence >= 0xe293aa00 && sequence <= 0xe293bf00) {
          return F_true;
        }

        // Dingbats: U+2776 to U+2793.
        if (sequence >= 0xe29db600 && sequence <= 0xe29e9300) {
          return F_true;
        }

        // Coptic: U+2CFD.
        if (sequence == 0xe2b3bd00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+3007.
        if (sequence == 0xe3808700) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+3021 to U+3029.
        if (sequence >= 0xe380a100 && sequence <= 0xe380a900) {
          return F_true;
        }

        // CJK Symbols and Punctuation: U+3038 to U+303A.
        if (sequence >= 0xe380b800 && sequence <= 0xe380ba00) {
          return F_true;
        }

        // Kanbun: U+3192 to U+3195.
        if (sequence >= 0xe3869200 && sequence <= 0xe3869500) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3220 to U+3229.
        if (sequence >= 0xe388a000 && sequence <= 0xe388a900) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3248 to U+324F.
        if (sequence >= 0xe3898800 && sequence <= 0xe3898f00) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+3251 to U+3289.
        if (sequence >= 0xe3899100 && sequence <= 0xe38a8900) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+32B1 to U+32BF.
        if (sequence >= 0xe38ab100 && sequence <= 0xe38abf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Vai: U+A620 to U+A629.
        if (sequence >= 0xea98a000 && sequence <= 0xea98a900) {
          return F_true;
        }

        // Bamum: U+A6E6 to U+A6EF.
        if (sequence >= 0xea98a000 && sequence <= 0xea9baf00) {
          return F_true;
        }

        // Common Indic Number Forms: U+A830 to U+A835.
        if (sequence >= 0xeaa0b000 && sequence <= 0xeaa0b500) {
          return F_true;
        }

        // Saurashtra: U+A8D0 to U+A8D9.
        if (sequence >= 0xeaa39000 && sequence <= 0xeaa39900) {
          return F_true;
        }

        // Kayah Li: U+A900 to U+A909.
        if (sequence >= 0xeaa48000 && sequence <= 0xeaa48900) {
          return F_true;
        }

        // Javanese: U+A9D0 to U+A9D9.
        if (sequence >= 0xeaa79000 && sequence <= 0xeaa79900) {
          return F_true;
        }

        // Myanmar Extended-B: U+A9F0 to U+A9F9.
        if (sequence >= 0xeaa7b000 && sequence <= 0xeaa7b900) {
          return F_true;
        }

        // Cham: U+AA50 to U+AA59.
        if (sequence >= 0xeaa99000 && sequence <= 0xeaa99900) {
          return F_true;
        }

        // Meetei Mayek: U+ABF0 to U+ABF9.
        if (sequence >= 0xeaafb000 && sequence <= 0xeaafb900) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // Halfwidth and Fullwidth Forms: U+FF10 to U+FF19.
        if (sequence >= 0xefbc9000 && sequence <= 0xefbc9900) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(sequence) == 0x90) {

        // Aegean Numbers: U+10107 to U+10133.
        if (sequence >= 0xf0908487 && sequence <= 0xf09084b3) {
          return F_true;
        }

        // Ancient Greek Numbers: U+10140 to U+10178.
        if (sequence >= 0xf0908580 && sequence <= 0xf09085b8) {
          return F_true;
        }

        // Ancient Greek Numbers: U+1018A to U+1018B.
        if (sequence >= 0xf090868a && sequence <= 0xf090868b) {
          return F_true;
        }

        // Coptic Epact Numbers: U+102E1 to U+102FB.
        if (sequence >= 0xf0908ba1 && sequence <= 0xf0908bbb) {
          return F_true;
        }

        // Old Italic: U+10320 to U+10323.
        if (sequence >= 0xf0908ca0 && sequence <= 0xf0908ca3) {
          return F_true;
        }

        // Gothic: U+10341, U+1034A.
        if (sequence == 0xf0908d81 || sequence == 0xf0908d8a) {
          return F_true;
        }

        // Old Persian: U+103D1 to U+103D5.
        if (sequence >= 0xf0908f91 && sequence <= 0xf0908f95) {
          return F_true;
        }

        // Osmanya: U+104A0 to U+104A9.
        if (sequence >= 0xf09092a0 && sequence <= 0xf09092a9) {
          return F_true;
        }

        // Imperial Aramaic: U+10858 to U+1085F.
        if (sequence >= 0xf090a198 && sequence <= 0xf090a19f) {
          return F_true;
        }

        // Palmyrene: U+10879 to U+1087F.
        if (sequence >= 0xf090a198 && sequence <= 0xf090a1bf) {
          return F_true;
        }

        // Nabataean: U+108A7 to U+108AF.
        if (sequence >= 0xf090a2a7 && sequence <= 0xf090a2af) {
          return F_true;
        }

        // Hatran: U+108FB to U+108FF.
        if (sequence >= 0xf090a3bb && sequence <= 0xf090a3bf) {
          return F_true;
        }

        // Phoenician to Meroitic Cursive: U+10916 to U+109BD.
        if (sequence >= 0xf090a496 && sequence <= 0xf090a6bd) {
          return F_true;
        }

        // Meroitic Cursive: U+109C0 to U+109CF.
        if (sequence >= 0xf090a780 && sequence <= 0xf090a78f) {
          return F_true;
        }

        // Meroitic Cursive: U+109D2 to U+109FF.
        if (sequence >= 0xf090a792 && sequence <= 0xf090a7bf) {
          return F_true;
        }

        // Kharoshthi: U+10A40 to U+10A48.
        if (sequence >= 0xf090a980 && sequence <= 0xf090a988) {
          return F_true;
        }

        // Old South Arabian: U+10A7D to U+10A7E.
        if (sequence >= 0xf090a9bd && sequence <= 0xf090a9be) {
          return F_true;
        }

        // Old North Arabian: U+10A9D to U+10A9F.
        if (sequence >= 0xf090aa9d && sequence <= 0xf090aa9f) {
          return F_true;
        }

        // Manichaean: U+10AEB to U+10AEF.
        if (sequence >= 0xf090abab && sequence <= 0xf090abaf) {
          return F_true;
        }

        // Inscriptional Parthian: U+10B58 to U+10B5F.
        if (sequence >= 0xf090ad98 && sequence <= 0xf090ad9f) {
          return F_true;
        }

        // Inscriptional Pahlavi: U+10B78 to U+10B7F.
        if (sequence >= 0xf090adb8 && sequence <= 0xf090adbf) {
          return F_true;
        }

        // Psalter Pahlavi: U+10BA9 to U+10BAF.
        if (sequence >= 0xf090aea9 && sequence <= 0xf090aeaf) {
          return F_true;
        }

        // Old Hungarian: U+10CFA to U+10CFF.
        if (sequence >= 0xf090b3ba && sequence <= 0xf090b3bf) {
          return F_true;
        }

        // Hanifi Rohingya: U+10D30 to U+10D39.
        if (sequence >= 0xf090b4b0 && sequence <= 0xf090b4b9) {
          return F_true;
        }

        // Rumi Numeral Symbols: U+10E60 to U+10E7E.
        if (sequence >= 0xf090b9a0 && sequence <= 0xf090b9be) {
          return F_true;
        }

        // Old Sogdian: U+10F1D to U+10F26.
        if (sequence >= 0xf090bc9d && sequence <= 0xf090bca6) {
          return F_true;
        }

        // Sogdian: U+10F51 to U+10F54.
        if (sequence >= 0xf090bd91 && sequence <= 0xf090bd94) {
          return F_true;
        }

        // Chorasmian: U+10FC5 to U+10FCB.
        if (sequence >= 0xf090bf85 && sequence <= 0xf090bf8b) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Brahmi: U+11052 to U+1106F.
        if (sequence >= 0xf0918192 && sequence <= 0xf09181af) {
          return F_true;
        }

        // Sora Sompeng: U+110F0 to U+110F9.
        if (sequence >= 0xf09183b0 && sequence <= 0xf09183b9) {
          return F_true;
        }

        // Chakma: U+11136 to U+1113F.
        if (sequence >= 0xf09184b6 && sequence <= 0xf09184bf) {
          return F_true;
        }

        // Sharada: U+111D0 to U+111D9.
        if (sequence >= 0xf0918790 && sequence <= 0xf0918799) {
          return F_true;
        }

        // Sinhala Archaic Numbers: U+111E1 to U+111F4.
        if (sequence >= 0xf09187a1 && sequence <= 0xf09187b4) {
          return F_true;
        }

        // Khudawadi: U+112F0 to U+112F9.
        if (sequence >= 0xf0918bb0 && sequence <= 0xf0918bb9) {
          return F_true;
        }

        // Newa: U+11450 to U+11459.
        if (sequence >= 0xf0919190 && sequence <= 0xf0919199) {
          return F_true;
        }

        // Tirhuta: U+114D0 to U+114D9.
        if (sequence >= 0xf0919390 && sequence <= 0xf0919399) {
          return F_true;
        }

        // Modi: U+11650 to U+11659.
        if (sequence >= 0xf0919990 && sequence <= 0xf0919999) {
          return F_true;
        }

        // Takri: U+116C0 to U+116C9.
        if (sequence >= 0xf0919b80 && sequence <= 0xf0919b89) {
          return F_true;
        }

        // Ahom: U+11730 to U+1173B.
        if (sequence >= 0xf0919cb0 && sequence <= 0xf0919cbb) {
          return F_true;
        }

        // Warang Citi: U+118E0 to U+118F2.
        if (sequence >= 0xf091a3a0 && sequence <= 0xf091a3b2) {
          return F_true;
        }

        // Dives Akuru: U+11950 to U+11959.
        if (sequence >= 0xf091a590 && sequence <= 0xf091a599) {
          return F_true;
        }

        // Bhaiksuki: U+11C50 to U+11C6C.
        if (sequence >= 0xf091b190 && sequence <= 0xf091b1ac) {
          return F_true;
        }

        // Masaram Gondi: U+11D50 to U+11D59.
        if (sequence >= 0xf091b590 && sequence <= 0xf091b599) {
          return F_true;
        }

        // Gunjala Gondi: U+11DA0 to U+11DA9.
        if (sequence >= 0xf091b6a0 && sequence <= 0xf091b6a9) {
          return F_true;
        }

        // Kawi: U+11F50 to U+11F59.
        if (sequence >= 0xf091bd90 && sequence <= 0xf091bd99) {
          return F_true;
        }

        // Tamil Supplement: U+11FC0 to U+11FD4.
        if (sequence >= 0xf091bf80 && sequence <= 0xf091bf94) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x92) {

        // Cuneiform Numbers and Punctuation: U+12400 to U+1246E.
        if (sequence >= 0xf0929080 && sequence <= 0xf09291ae) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x96) {

        // Mro: U+16A60 to U+16A69.
        if (sequence >= 0xf096a9a0 && sequence <= 0xf096a9a9) {
          return F_true;
        }

        // Tangsa: U+16AC0 to U+16AC9.
        if (sequence >= 0xf096ab80 && sequence <= 0xf096ab89) {
          return F_true;
        }

        // Pahawh Hmong: U+16B50 to U+16B59.
        if (sequence >= 0xf096ad90 && sequence <= 0xf096ad99) {
          return F_true;
        }

        // Pahawh Hmong: U+16B5B to U+16B61.
        if (sequence >= 0xf096ad9b && sequence <= 0xf096ada1) {
          return F_true;
        }

        // Medefaidrin: U+16E80 to U+16E96.
        if (sequence >= 0xf096ba80 && sequence <= 0xf096ba96) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

        // Kaktovik Numerals: U+1D2C0 to U+1D2D3.
        if (sequence >= 0xf09d8b80 && sequence <= 0xf09d8b93) {
          return F_true;
        }

        // Mayan Numerals: U+1D2E0 to U+1D2F3.
        if (sequence >= 0xf09d8ba0 && sequence <= 0xf09d8bb3) {
          return F_true;
        }

        // Counting Rod Numerals: U+1D360 to U+1D378.
        if (sequence >= 0xf09d8da0 && sequence <= 0xf09d8db8) {
          return F_true;
        }

        // Mathematical Alphanumeric (Bold) Symbols: U+1D7CE to U+1D7D7.
        if (sequence >= 0xf09d9f8e && sequence <= 0xf09d9f97) {
          return F_true;
        }

        // Mathematical Alphanumeric (Double-Struck) Symbols: U+1D7D8 to U+1D7E1.
        if (sequence >= 0xf09d9f98 && sequence <= 0xf09d9fa1) {
          return F_true;
        }

        // Mathematical Alphanumeric (Sans-Serif) Symbols: U+1D7E2 to U+1D7EB.
        if (sequence >= 0xf09d9fa2 && sequence <= 0xf09d9fab) {
          return F_true;
        }

        // Mathematical Alphanumeric (Sans-Serif Bold) Symbols: U+1D7EC to U+1D7F5.
        if (sequence >= 0xf09d9fac && sequence <= 0xf09d9fb5) {
          return F_true;
        }

        // Mathematical Alphanumeric (Monospace) Symbols: U+1D7F6 to U+1D7FF.
        if (sequence >= 0xf09d9fb6 && sequence <= 0xf09d9fbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9e) {

        // Nyiakeng Puachue Hmong: U+1E140 to U+1E149.
        if (sequence >= 0xf09e8580 && sequence <= 0xf09e8589) {
          return F_true;
        }

        // Wancho: U+1E2F0 to U+1E2F9.
        if (sequence >= 0xf09e8bb0 && sequence <= 0xf09e8bb9) {
          return F_true;
        }

        // Nag Mundari: U+1E4F0 to U+1E4F9.
        if (sequence >= 0xf09e93b0 && sequence <= 0xf09e93b9) {
          return F_true;
        }

        // Mende Kikakui: U+1E8C7 to U+1E8CF.
        if (sequence >= 0xf09ea387 && sequence <= 0xf09ea38f) {
          return F_true;
        }

        // Adlam: U+1E950 to U+1E959.
        if (sequence >= 0xf09ea590 && sequence <= 0xf09ea599) {
          return F_true;
        }

        // Indic Siyaq Numbers: U+1EC71 to U+1ECAF.
        if (sequence >= 0xf09eb1b1 && sequence <= 0xf09eb2af) {
          return F_true;
        }

        // Indic Siyaq Numbers: U+1ECB1 to U+1ECB4.
        if (sequence >= 0xf09eb2b1 && sequence <= 0xf09eb2b4) {
          return F_true;
        }

        // Ottoman Siyaq Numbers: U+1ED01 to U+1ED3D.
        if (sequence >= 0xf09eb481 && sequence <= 0xf09eb4bd) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Enclosed Alphanumeric Supplement: U+1F100 to U+1F10C.
        if (sequence >= 0xf09f8480 && sequence <= 0xf09f848c) {
          return F_true;
        }

        // Symbols for Legacy Computing (Segmented): U+1FBF0 to U+1FBF9.
        if (sequence >= 0xf09fafb0 && sequence <= 0xf09fafb9) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

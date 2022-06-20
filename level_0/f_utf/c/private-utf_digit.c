#include "utf.h"
#include "private-utf.h"
#include "private-utf_digit.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_decimal_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)
  f_status_t private_f_utf_character_is_digit(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

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

        // Tamil: U+0BE6 to U+0BEF.
        if (sequence >= 0xe0afa600 && sequence <= 0xe0afaf00) {
          return F_true;
        }

        // Telugu: U+0C66 to U+0C6F.
        if (sequence >= 0xe0b1a600 && sequence <= 0xe0b1af00) {
          return F_true;
        }

        // Kannada: U+0CE6 to U+0CEF.
        if (sequence >= 0xe0b3a600 && sequence <= 0xe0b3af00) {
          return F_true;
        }

        // Malayalam: U+0D66 to U+0D6F.
        if (sequence >= 0xe0b5a600 && sequence <= 0xe0b5af00) {
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

        // Tibetan: U+0F20 to U+0F29.
        if (sequence >= 0xe0bca000 && sequence <= 0xe0bca900) {
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

        // Khmer: U+17E0 to U+17E9.
        if (sequence >= 0xe19fa000 && sequence <= 0xe19fa900) {
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

        // New Tai Lue: U+19D0 to U+19D9.
        if (sequence >= 0xe1a79000 && sequence <= 0xe1a79900) {
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

        // Number Forms: U+2160 to U+2188 (Roman Numerals).
        if (sequence >= 0xe285a000 && sequence <= 0xe2868800) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Vai: U+A620 to U+A629.
        if (sequence >= 0xea98a000 && sequence <= 0xea98a900) {
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

        // Osmanya: U+104A0 to U+104A9.
        if (sequence >= 0xf09092a0 && sequence <= 0xf09092a9) {
          return F_true;
        }

        // Hanifi Rohingya: U+10D30 to U+10D39.
        if (sequence >= 0xf090b4b0 && sequence <= 0xf090b4b9) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Brahmi: U+11066 to U+1106F.
        if (sequence >= 0xf09181a6 && sequence <= 0xf09181af) {
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

        // Ahom: U+11730 to U+11739.
        if (sequence >= 0xf0919cb0 && sequence <= 0xf0919cb9) {
          return F_true;
        }

        // Warang Citi: U+118E0 to U+118E9.
        if (sequence >= 0xf091a3a0 && sequence <= 0xf091a3a9) {
          return F_true;
        }

        // Dives Akuru: U+11950 to U+11959.
        if (sequence >= 0xf091a590 && sequence <= 0xf091a599) {
          return F_true;
        }

        // Bhaiksuki: U+11C50 to U+11C59.
        if (sequence >= 0xf091b190 && sequence <= 0xf091b199) {
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
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

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

        // Adlam: U+1E950 to U+1E959.
        if (sequence >= 0xf09ea590 && sequence <= 0xf09ea599) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Symbols for Legacy Computing (Segmented): U+1FBF0 to U+1FBF9.
        if (sequence >= 0xf09fafb0 && sequence <= 0xf09fafb9) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_decimal_) || !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)

#ifdef __cplusplus
} // extern "C"
#endif

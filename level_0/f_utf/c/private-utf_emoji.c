#include "utf.h"
#include "private-utf.h"
#include "private-utf_emoji.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)
  f_status_t private_f_utf_character_is_emoji(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Latin-1 Supplement: U+00A9, U+00AE.
      if (sequence == 0xc2a90000 || sequence == 0xc2ae0000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // General Punctuation: U+203C, U+2049.
        if (sequence == 0xe280bc00 || sequence == 0xe2818900) {
          return F_true;
        }

        // Letterlike Symbols: U+2122, U+2139
        if (sequence == 0xe284a200 || sequence == 0xe284b900) {
          return F_true;
        }

        // Arrows: U+2194 to U+2199.
        if (sequence >= 0xe2869400 && sequence <= 0xe2869900) {
          return F_true;
        }

        // Arrows: U+21A9, U+21AA.
        if (sequence == 0xe286a900 || sequence == 0xe286aa00) {
          return F_true;
        }

        // Miscellaneous Technical: U+231A, U+231B.
        if (sequence == 0xe28c9a00 || sequence == 0xe28c9b00) {
          return F_true;
        }

        // Miscellaneous Technical: U+2328, U+23CF.
        if (sequence == 0xe28ca800 || sequence == 0xe28f8f00) {
          return F_true;
        }

        // Miscellaneous Technical: U+23E9 to U+23F3.
        if (sequence >= 0xe28fa900 && sequence <= 0xe28fb300) {
          return F_true;
        }

        // Miscellaneous Technical: U+23F8 to U+23FA.
        if (sequence >= 0xe28fb800 && sequence <= 0xe28fba00) {
          return F_true;
        }

        // Enclosed Alphanumerics: U+24C2.
        if (sequence == 0xe2938200) {
          return F_true;
        }

        // Geometric Shapes: U+25AA, U+25AB, U+25B6, U+25C0.
        if (sequence == 0xe296aa00 || sequence == 0xe296ab00 || sequence == 0xe296b600 || sequence == 0xe2978000) {
          return F_true;
        }

        // Geometric Shapes: U+25FB to U+25FE.
        if (sequence >= 0xe297bb00 && sequence <= 0xe297be00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2600 to U+2604.
        if (sequence >= 0xe2988000 && sequence <= 0xe2988400) {
          return F_true;
        }

        // Miscellaneous Symbols: U+260E, U+2611, U+2614, U+2615.
        if (sequence == 0xe2988e00 || sequence == 0xe2989100 || sequence == 0xe2989400 || sequence == 0xe2989500) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2618, U+261D, U+2620, U+2622.
        if (sequence == 0xe2989800 || sequence == 0xe2989d00 || sequence == 0xe298a000 || sequence == 0xe298a200) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2623, U+2626, U+262A, U+262E.
        if (sequence == 0xe298a300 || sequence == 0xe298a600 || sequence == 0xe298aa00 || sequence == 0xe298ae00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+262F.
        if (sequence == 0xe298af00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2638 to U+263A.
        if (sequence >= 0xe298b800 && sequence <= 0xe298ba00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2640, U+2642.
        if (sequence == 0xe2998000 || sequence == 0xe2998200) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2648 to U+2653.
        if (sequence >= 0xe2998800 && sequence <= 0xe2999300) {
          return F_true;
        }

        // Miscellaneous Symbols: U+265F, U+2660, U+2663, U+2665.
        if (sequence == 0xe2999f00 || sequence == 0xe299a000 || sequence == 0xe299a300 || sequence == 0xe299a500) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2666, U+2668, U+267B, U+267E.
        if (sequence == 0xe299a600 || sequence == 0xe299a800 || sequence == 0xe299bb00 || sequence == 0xe299be00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+267F.
        if (sequence == 0xe299bf00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2692 to U+2697.
        if (sequence >= 0xe29a9200 && sequence <= 0xe29a9700) {
          return F_true;
        }

        // Miscellaneous Symbols: U+2699, U+269B, U+269C, U+26A0.
        if (sequence == 0xe29a9900 || sequence == 0xe29a9b00 || sequence == 0xe29a9c00 || sequence == 0xe29aa000) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26A1, U+26A7, U+26AA, U+26AB.
        if (sequence == 0xe29aa100 || sequence == 0xe29aa700 || sequence == 0xe29aaa00 || sequence == 0xe29aab00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26B0, U+26B1, U+26BD, U+26BE.
        if (sequence == 0xe29ab000 || sequence == 0xe29ab100 || sequence == 0xe29abd00 || sequence == 0xe29abe00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26C4, U+26C5, U+26C8, U+26CE.
        if (sequence == 0xe29b8400 || sequence == 0xe29b8500 || sequence == 0xe29b8800 || sequence == 0xe29b8e00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26CF, U+26D1, U+26D3, U+26D4.
        if (sequence == 0xe29b8f00 || sequence == 0xe29b9100 || sequence == 0xe29b9300 || sequence == 0xe29b9400) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26E9, U+26EA.
        if (sequence == 0xe29ba900 || sequence == 0xe29baa00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26F0 to U+26F5.
        if (sequence >= 0xe29bb000 && sequence <= 0xe29bb500) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26F7 to U+26FA.
        if (sequence >= 0xe29bb700 && sequence <= 0xe29bba00) {
          return F_true;
        }

        // Miscellaneous Symbols: U+26FD.
        if (sequence == 0xe29bbd00) {
          return F_true;
        }

        // Dingbats: U+2702, U+2705.
        if (sequence == 0xe29c8200 || sequence == 0xe29c8500) {
          return F_true;
        }

        // Dingbats: U+2708 to U+270D.
        if (sequence >= 0xe29c8800 && sequence <= 0xe29c8d00) {
          return F_true;
        }

        // Dingbats: U+270F, U+2712, U+2714, U+2716.
        if (sequence == 0xe29c8f00 || sequence == 0xe29c9200 || sequence == 0xe29c9400 || sequence == 0xe29c9600) {
          return F_true;
        }

        // Dingbats: U+271D, U+2721, U+2728, U+2733.
        if (sequence == 0xe29c9d00 || sequence == 0xe29ca100 || sequence == 0xe29ca800 || sequence == 0xe29cb300) {
          return F_true;
        }

        // Dingbats: U+2734, U+2744, U+2747, U+274C.
        if (sequence == 0xe29cb400 || sequence == 0xe29d8400 || sequence == 0xe29d8700 || sequence == 0xe29d8c00) {
          return F_true;
        }

        // Dingbats: U+274E.
        if (sequence == 0xe29d8e00) {
          return F_true;
        }

        // Dingbats: U+2753 to U+2755.
        if (sequence >= 0xe29d9300 && sequence <= 0xe29d9500) {
          return F_true;
        }

        // Dingbats: U+2757, U+2763, U+2764.
        if (sequence == 0xe29d9700 || sequence == 0xe29da300 || sequence == 0xe29da400) {
          return F_true;
        }

        // Dingbats: U+2795 to U+2797.
        if (sequence >= 0xe29e9500 && sequence <= 0xe29e9700) {
          return F_true;
        }

        // Dingbats: U+27A1, U+27B0, U+27BF, U+2934.
        if (sequence == 0xe29ea100 || sequence == 0xe29eb000 || sequence == 0xe29ebf00 || sequence == 0xe2a4b400) {
          return F_true;
        }

        // Supplemental Arrows-B: U+2935.
        if (sequence == 0xe2a4b500) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2B05 to U+2B07.
        if (sequence >= 0xe2ac8500 && sequence <= 0xe2ac8700) {
          return F_true;
        }

        // U+2B1B, U+2B1C, U+2B50, U+2B55.
        if (sequence == 0xe2ac9b00 || sequence == 0xe2ac9c00 || sequence == 0xe2ad9000 || sequence == 0xe2ad9500) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+3030, U+303D, U+3297, U+3299.
        if (sequence == 0xe380b000 || sequence == 0xe380bd00 || sequence == 0xe38a9700 || sequence == 0xe38a9900) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Mahjong Tiles: U+1F004.
        if (sequence == 0xf09f8084) {
          return F_true;
        }

        // Playing Cards: U+1F0CF to U+1F171.
        if (sequence >= 0xf09f8084 && sequence <= 0xf09f85b1) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F17E, U+1F17F, U+1F18E.
        if (sequence == 0xf09f85be || sequence == 0xf09f85bf || sequence == 0xf09f868e) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F191 to U+1F19A.
        if (sequence >= 0xf09f8691 && sequence <= 0xf09f869a) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F1E6.
        if (sequence == 0xf09f87a6) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F201, U+1F202, U+1F21A, U+1F22F.
        if (sequence == 0xf09f8881 || sequence == 0xf09f8882 || sequence == 0xf09f889a || sequence == 0xf09f88af) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F232 to U+1F23A.
        if (sequence >= 0xf09f88b2 && sequence <= 0xf09f88ba) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F250, U+1F251.
        if (sequence == 0xf09f8990 || sequence == 0xf09f8991) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F300 to U+1F321.
        if (sequence >= 0xf09f8c80 && sequence <= 0xf09f8ca1) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F324 to U+1F393.
        if (sequence >= 0xf09f8ca4 && sequence <= 0xf09f8e93) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F396, U+1F397.
        if (sequence == 0xf09f8e96 || sequence == 0xf09f8e97) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F399 to U+1F39B.
        if (sequence >= 0xf09f8e99 && sequence <= 0xf09f8e9b) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F39E to U+1F3F0.
        if (sequence >= 0xf09f8e9e && sequence <= 0xf09f8fb0) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F3F3 to U+1F3F5.
        if (sequence >= 0xf09f8fb3 && sequence <= 0xf09f8fb5) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F3F7 to U+1F4FD.
        if (sequence >= 0xf09f8fb7 && sequence <= 0xf09f93bd) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F4FF to U+1F53D.
        if (sequence >= 0xf09f93bf && sequence <= 0xf09f94bd) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F549 to U+1F54E.
        if (sequence >= 0xf09f9589 && sequence <= 0xf09f958e) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F550 to U+1F567.
        if (sequence >= 0xf09f9590 && sequence <= 0xf09f95a7) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F56F, U+1F570.
        if (sequence == 0xf09f95af || sequence == 0xf09f95b0) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F573 to U+1F57A.
        if (sequence >= 0xf09f95b3 && sequence <= 0xf09f95ba) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F587.
        if (sequence == 0xf09f9687) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F58A to U+1F58D.
        if (sequence >= 0xf09f968a && sequence <= 0xf09f968d) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F590, U+1F595, U+1F596, U+1F5A4.
        if (sequence == 0xf09f9690 || sequence == 0xf09f9695 || sequence == 0xf09f9696 || sequence == 0xf09f96a4) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5A5, U+1F5A8, U+1F5B1, U+1F5B2.
        if (sequence == 0xf09f96a5 || sequence == 0xf09f96a8 || sequence == 0xf09f96b1 || sequence == 0xf09f96b2) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5BC.
        if (sequence == 0xf09f96bc) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5C2 to U+1F5C4.
        if (sequence >= 0xf09f9782 && sequence <= 0xf09f9784) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5D1 to U+1F5D3.
        if (sequence >= 0xf09f9791 && sequence <= 0xf09f9793) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5DC to U+1F5DE.
        if (sequence >= 0xf09f979c && sequence <= 0xf09f979e) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5E1, U+1F5E3, U+1F5E8, U+1F5EF.
        if (sequence == 0xf09f97a1 || sequence == 0xf09f97a3 || sequence == 0xf09f97a8 || sequence == 0xf09f97af) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5F3.
        if (sequence == 0xf09f97b3) {
          return F_true;
        }

        // Miscellaneous Symbols and Pictographs: U+1F5FA to U+1F6C5.
        if (sequence >= 0xf09f97ba && sequence <= 0xf09f9b85) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6CB to U+1F6D2.
        if (sequence >= 0xf09f9b8b && sequence <= 0xf09f9b92) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6D5 to U+1F6D7.
        if (sequence >= 0xf09f9b95 && sequence <= 0xf09f9b97) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6DC to U+1F6DF.
        if (sequence >= 0xf09f9b9c && sequence <= 0xf09f9b9f) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6E0 to U+1F6E5.
        if (sequence >= 0xf09f9ba0 && sequence <= 0xf09f9ba5) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6E9, U+1F6EB, U+1F6EC, U+1F6F0.
        if (sequence == 0xf09f9ba9 || sequence == 0xf09f9bab || sequence == 0xf09f9bac || sequence == 0xf09f9bb0) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6F3 to U+1F6FC.
        if (sequence >= 0xf09f9bb3 && sequence <= 0xf09f9bbc) {
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

        // Supplemental Symbols and Pictographs: U+1F90C to U+1F93A.
        if (sequence >= 0xf09fa48c && sequence <= 0xf09fa4ba) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs: U+1F93C to U+1F945.
        if (sequence >= 0xf09fa4bc && sequence <= 0xf09fa585) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs to Symbols and Pictographs Extended-A: U+1F947 to U+U+1FA74.
        if (sequence >= 0xf09fa587 && sequence <= 0xf09fa9b4) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA70 to U+1FA7C.
        if (sequence >= 0xf09fa9b0 && sequence <= 0xf09fa9bc) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA80 to U+1FA88.
        if (sequence >= 0xf09faa80 && sequence <= 0xf09faa88) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA90 to U+1FABD.
        if (sequence >= 0xf09faa90 && sequence <= 0xf09faabd) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FABF to U+1FAC5.
        if (sequence >= 0xf09faabf && sequence <= 0xf09fab85) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FACE to U+1FADB.
        if (sequence >= 0xf09fab8e && sequence <= 0xf09fab9b) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAE0 to U+1FAE8.
        if (sequence >= 0xf09faba0 && sequence <= 0xf09faba8) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAF0 to U+1FAF8.
        if (sequence >= 0xf09fabb0 && sequence <= 0xf09fabb8) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)

#ifdef __cplusplus
} // extern "C"
#endif

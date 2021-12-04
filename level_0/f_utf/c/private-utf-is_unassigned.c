#include "utf.h"
#include "private-utf.h"
#include "private-utf-is_unassigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_unassigned_) || !defined(_di_f_utf_is_unassigned_)
  f_status_t private_f_utf_character_is_unassigned(const f_utf_character_t character) {

    if (macro_f_utf_character_t_width_is(character) < 2) {
      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 2) {

      // Greek and Coptic: U+0378 to U+0379.
      if (character >= 0xcdb80000 && character <= 0xcdb90000) {
        return F_true;
      }

      // Greek and Coptic: U+0380 to U+0383.
      if (character >= 0xce800000 && character <= 0xce830000) {
        return F_true;
      }

      // Greek and Coptic: U+038B, U+038D, U+03A2.
      if (character == 0xce8b0000 || character == 0xce8d0000 || character == 0xcea20000) {
        return F_true;
      }

      // Armenian: U+0530.
      if (character == 0xd4b00000) {
        return F_true;
      }

      // Armenian: U+0557 to U+0558.
      if (character >= 0xd5970000 && character <= 0xd5980000) {
        return F_true;
      }

      // Armenian: U+0560, U+0588, U+058B, U+058C.
      if (character == 0xd5a00000 || character == 0xd6880000 || character == 0xd68b0000 || character == 0xd68c0000) {
        return F_true;
      }

      // Armenian: U+0530.
      if (character == 0xd4b00000) {
        return F_true;
      }

      // Hebrew: U+0590.
      if (character == 0xd6900000) {
        return F_true;
      }

      // Hebrew: U+05C8 to U+05CF.
      if (character >= 0xd7880000 && character <= 0xd78f0000) {
        return F_true;
      }

      // Hebrew: U+05EB to U+05EF.
      if (character >= 0xd7ab0000 && character <= 0xd7af0000) {
        return F_true;
      }

      // Hebrew: U+05F5 to U+05FF.
      if (character >= 0xd7b50000 && character <= 0xd7bf0000) {
        return F_true;
      }

      // Syriac: U+074B to U+074C.
      if (character >= 0xdd8b0000 && character <= 0xdd8c0000) {
        return F_true;
      }

      // Thaana: U+07B2 to U+07BF.
      if (character >= 0xdeb20000 && character <= 0xdebf0000) {
        return F_true;
      }

      // Nko: U+07FB to U+07FF.
      if (character >= 0xdfbb0000 && character <= 0xdfbf0000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_character_t_width_is(character) == 3) {

      // Samaritan: U+082E, U+082F, U+083F.
      if (character == 0xe0a0ae00 || character == 0xe0a0af00 || character == 0xe0a0bf00) {
        return F_true;
      }

      // Mandaic: U+085C, U+085D, U+085F.
      if (character == 0xe0a19c00 || character == 0xe0a19d00 || character == 0xe0a19f00) {
        return F_true;
      }

      // Arabic Extended A: U+08B5 to U+08E2.
      if (character >= 0xe0a2b500 && character <= 0xe0a3a200) {
        return F_true;
      }

      // Bengali: U+0984, U+098D, U+098E, U+0991.
      if (character == 0xe0a68400 || character == 0xe0a68d00 || character == 0xe0a68e00 || character == 0xe0a69100) {
        return F_true;
      }

      // Bengali: U+0992, U+09A9, U+09B1.
      if (character == 0xe0a69200 || character == 0xe0a6a900 || character == 0xe0a6b100) {
        return F_true;
      }

      // Bengali: U+09B3 to U+09B5.
      if (character >= 0xe0a6b300 && character <= 0xe0a6b500) {
        return F_true;
      }

      // Bengali: U+09BA to U+09BB.
      if (character >= 0xe0a6ba00 && character <= 0xe0a6bb00) {
        return F_true;
      }

      // Bengali: U+09C5 to U+09C6.
      if (character >= 0xe0a78500 && character <= 0xe0a78600) {
        return F_true;
      }

      // Bengali: U+09C9 to U+09CA.
      if (character >= 0xe0a78900 && character <= 0xe0a78a00) {
        return F_true;
      }

      // Bengali: U+09CF to U+09D6.
      if (character >= 0xe0a78f00 && character <= 0xe0a79600) {
        return F_true;
      }

      // Bengali: U+09D8 to U+09DB.
      if (character >= 0xe0a79800 && character <= 0xe0a79b00) {
        return F_true;
      }

      // Bengali: U+09DE, U+09E4, U+09E5.
      if (character == 0xe0a79e00 || character == 0xe0a7a400 || character == 0xe0a7a500) {
        return F_true;
      }

      // Bengali: U+09FC to U+09FF.
      if (character >= 0xe0a7bc00 && character <= 0xe0a7bf00) {
        return F_true;
      }

      // Gurmukhi: U+0A00, U+0A04.
      if (character == 0xe0a88000 || character == 0xe0a88400) {
        return F_true;
      }

      // Gurmukhi: U+0A0B to U+0A0E.
      if (character >= 0xe0a88b00 && character <= 0xe0a88e00) {
        return F_true;
      }

      // Gurmukhi: U+0A11 to U+0A12.
      if (character >= 0xe0a89100 && character <= 0xe0a89200) {
        return F_true;
      }

      // Gurmukhi: U+0A29, U+0A31, U+0A34, U+0A37.
      if (character == 0xe0a8a900 || character == 0xe0a8b100 || character == 0xe0a8b400 || character == 0xe0a8b700) {
        return F_true;
      }

      // Gurmukhi: U+0A3A, U+0A3B, U+0A3D.
      if (character == 0xe0a8ba00 || character == 0xe0a8bb00 || character == 0xe0a8bd00) {
        return F_true;
      }

      // Gurmukhi: U+0A43 to U+0A46.
      if (character >= 0xe0a98300 && character <= 0xe0a98600) {
        return F_true;
      }

      // Gurmukhi: U+0A49 to U+0A4A.
      if (character >= 0xe0a98900 && character <= 0xe0a98a00) {
        return F_true;
      }

      // Gurmukhi: U+0A4E to U+0A50.
      if (character >= 0xe0a98e00 && character <= 0xe0a99000) {
        return F_true;
      }

      // Gurmukhi: U+0A52 to U+0A58.
      if (character >= 0xe0a99200 && character <= 0xe0a99800) {
        return F_true;
      }

      // Gurmukhi: U+0A5D.
      if (character == 0xe0a99d00) {
        return F_true;
      }

      // Gurmukhi: U+0A5F to U+0A65.
      if (character >= 0xe0a99f00 && character <= 0xe0a9a500) {
        return F_true;
      }

      // Gurmukhi: U+0A76 to U+0A7F.
      if (character >= 0xe0a9b600 && character <= 0xe0a9bf00) {
        return F_true;
      }

      // @todo

      return F_false;
    }

    // Linear B Syllabary: U+1000C, U+10027, U+1003B, U+1003E.
    if (character == 0xf090808c || character == 0xf09080a7 || character == 0xf09080bb || character == 0xf09080be) {
      return F_true;
    }

    // Linear B Syllabary: U+1004E, U+1004F.
    if (character == 0xf090818e || character == 0xf090818f) {
      return F_true;
    }

    // Linear B Syllabary: U+1005E to U+1007F.
    if (character >= 0xf090819e && character <= 0xf09081bf) {
      return F_true;
    }

    // Linear B Ideograms: U+100FB to U+100FF.
    if (character >= 0xf09083bb && character <= 0xf09083bf) {
      return F_true;
    }

    // Aegean Numbers: U+10103 to U+10106.
    if (character >= 0xf0908483 && character <= 0xf0908486) {
      return F_true;
    }

    // Aegean Numbers: U+10134 to U+10136.
    if (character >= 0xf09084b4 && character <= 0xf09084b6) {
      return F_true;
    }

    // Ancient Greek Numbers: U+1018D to U+1018F.
    if (character >= 0xf090868d && character <= 0xf090868f) {
      return F_true;
    }

    // Ancient Symbols: U+1019C to U+1019F.
    if (character >= 0xf090869c && character <= 0xf090869f) {
      return F_true;
    }

    // Ancient Symbols: U+101A1 to U+101CF.
    if (character >= 0xf09086a1 && character <= 0xf090878f) {
      return F_true;
    }

    // Phaistos Disc: U+101FE to U+101FF.
    if (character >= 0xf09087be && character <= 0xf09087bf) {
      return F_true;
    }

    // Lycian: U+1029D to U+1029F.
    if (character >= 0xf0908a9d && character <= 0xf0908a9f) {
      return F_true;
    }

    // Carian: U+102D1 to U+102DF.
    if (character >= 0xf0908b91 && character <= 0xf0908b9f) {
      return F_true;
    }

    // Coptic Epact Numbers: U+102FC to U+102FF.
    if (character >= 0xf0908bbc && character <= 0xf0908bbf) {
      return F_true;
    }

    // Old Italic: U+10324 to U+1032F.
    if (character >= 0xf0908ca4 && character <= 0xf0908caf) {
      return F_true;
    }

    // Old Permic: U+1037B to U+1037F.
    if (character >= 0xf0908dbb && character <= 0xf0908dbf) {
      return F_true;
    }

    // Gothic: U+1034B to U+1034F.
    if (character >= 0xf0908d8b && character <= 0xf0908d8f) {
      return F_true;
    }

    // Ugaritic: U+1039E.
    if (character == 0xf0908e9e) {
      return F_true;
    }

    // Old Persian: U+103C4 to U+103C7.
    if (character >= 0xf0908f84 && character <= 0xf0908f87) {
      return F_true;
    }

    // Old Persian: U+103D6 to U+103DF.
    if (character >= 0xf0908f96 && character <= 0xf0908f9f) {
      return F_true;
    }

    // Osmanya: U+104AA to U+104AF.
    if (character >= 0xf09092aa && character <= 0xf09092af) {
      return F_true;
    }

    // Elbasan: U+10528 to U+1052F.
    if (character >= 0xf09094a8 && character <= 0xf09094af) {
      return F_true;
    }

    // Caucasian Albanian: U+10564 to U+1056E.
    if (character >= 0xf09095a4 && character <= 0xf09095ae) {
      return F_true;
    }

    // Linear A: U+10737 to U+1077F.
    if (character >= 0xf0909cb7 && character <= 0xf0909dbf) {
      return F_true;
    }

    // Cypriot Syllabary: U+10806, U+10807, U+10809, U+10836.
    if (character == 0xf090a086 || character == 0xf090a087 || character == 0xf090a089 || character == 0xf090a0b6) {
      return F_true;
    }

    // Cypriot Syllabary: U+10839 to U+1083B.
    if (character >= 0xf090a0b9 && character <= 0xf090a0bb) {
      return F_true;
    }

    // Cypriot Syllabary: U+10839 to U+1083B.
    if (character >= 0xf090a0b9 && character <= 0xf090a0bb) {
      return F_true;
    }

    // Cypriot Syllabary: U+1083D to U+1083E.
    if (character >= 0xf090a0bd && character <= 0xf090a0be) {
      return F_true;
    }

    // Nabataean: U+1089F to U+108A6.
    if (character >= 0xf090a29f && character <= 0xf090a2a6) {
      return F_true;
    }

    // Hatran: U+108F3.
    if (character == 0xf090a3b3) {
      return F_true;
    }

    // Hatran: U+108F6 to U+108FA.
    if (character >= 0xf090a3b6 && character <= 0xf090a3ba) {
      return F_true;
    }

    // Phoenician: U+1091C to U+1091E.
    if (character >= 0xf090a49c && character <= 0xf090a49e) {
      return F_true;
    }

    // Lydian: U+1093A to U+1093E.
    if (character >= 0xf090a4ba && character <= 0xf090a4be) {
      return F_true;
    }

    // Meroitic Cursive: U+109B8 to U+109BB.
    if (character >= 0xf090a6b8 && character <= 0xf090a6bb) {
      return F_true;
    }

    // Meroitic Cursive: U+109D0 to U+109D1.
    if (character >= 0xf090a790 && character <= 0xf090a791) {
      return F_true;
    }

    // Kharoshthi: U+10A04.
    if (character == 0xf090a884) {
      return F_true;
    }

    // Kharoshthi: U+10A07 to U+10A0B.
    if (character >= 0xf090a887 && character <= 0xf090a88b) {
      return F_true;
    }

    // Kharoshthi: U+10A18.
    if (character == 0xf090a898) {
      return F_true;
    }

    // Kharoshthi: U+10A34 to U+10A37.
    if (character >= 0xf090a8b4 && character <= 0xf090a8b7) {
      return F_true;
    }

    // Kharoshthi: U+10A3B to U+10A3E.
    if (character >= 0xf090a8bb && character <= 0xf090a8be) {
      return F_true;
    }

    // Kharoshthi: U+10A48 to U+10A4F.
    if (character >= 0xf090a988 && character <= 0xf090a98f) {
      return F_true;
    }

    // Kharoshthi: U+10A59 to U+10A5F.
    if (character >= 0xf090a999 && character <= 0xf090a99f) {
      return F_true;
    }

    // Manichaean: U+10A5F to U+10AEA.
    if (character >= 0xf090a99f && character <= 0xf090abaa) {
      return F_true;
    }

    // Manichaean: U+10A5F to U+10AEA.
    if (character >= 0xf090a99f && character <= 0xf090abaa) {
      return F_true;
    }

    // Manichaean: U+10AF7 to U+10AFF.
    if (character >= 0xf090abb7 && character <= 0xf090abbf) {
      return F_true;
    }

    // Avestan: U+10B36 to U+10B38.
    if (character >= 0xf090acb6 && character <= 0xf090acb8) {
      return F_true;
    }

    // Inscriptional Parthian: U+10B56 to U+10B57.
    if (character >= 0xf090ad96 && character <= 0xf090ad97) {
      return F_true;
    }

    // Inscriptional Pahlavi: U+10B73 to U+10B77.
    if (character >= 0xf090adb3 && character <= 0xf090adb7) {
      return F_true;
    }

    // Psalter Pahlavi: U+10B92 to U+10B98.
    if (character >= 0xf090ae92 && character <= 0xf090ae98) {
      return F_true;
    }

    // Psalter Pahlavi: U+10B9D to U+10BA8.
    if (character >= 0xf090ae9d && character <= 0xf090aea8) {
      return F_true;
    }

    // Old Turkic: U+10C49 to U+10C4F.
    if (character >= 0xf090b189 && character <= 0xf090b18f) {
      return F_true;
    }

    // Old Hungarian: U+10CB3 to U+10CBF.
    if (character >= 0xf090b2b3 && character <= 0xf090b2bf) {
      return F_true;
    }

    // Old Hungarian: U+10CF3 to U+10CF9.
    if (character >= 0xf090b3b3 && character <= 0xf090b3b9) {
      return F_true;
    }

    // Rumi Numeral Symbols: U+10E7F.
    if (character == 0xf090b9bf) {
      return F_true;
    }

    // Brahmi: U+1104E to U+11051.
    if (character >= 0xf091818e && character <= 0xf0918191) {
      return F_true;
    }

    // Brahmi: U+11070 to U+1107E.
    if (character >= 0xf09181b0 && character <= 0xf09181be) {
      return F_true;
    }

    // Kaithi: U+110C2 to U+110CF.
    if (character >= 0xf0918382 && character <= 0xf091838f) {
      return F_true;
    }

    // Sora Sompeng: U+110E9 to U+110EF.
    if (character >= 0xf09183a9 && character <= 0xf09183af) {
      return F_true;
    }

    // Sora Sompeng: U+110FA to U+110FF.
    if (character >= 0xf09183ba && character <= 0xf09183bf) {
      return F_true;
    }

    // Supplemental Symbols and Pictographs: U+1F9C1 to U+1FFFD.
    if (character >= 0xf09fa781 && character <= 0xf09fbfbd) {
      return F_true;
    }

    // Chakma: U+11135.
    if (character == 0xf09184b5) {
      return F_true;
    }

    // Chakma: U+11144 to U+1114F.
    if (character >= 0xf0918584 && character <= 0xf091858f) {
      return F_true;
    }

    // Mahajani: U+11177 to U+1117F.
    if (character >= 0xf09185b7 && character <= 0xf09185bf) {
      return F_true;
    }

    // Sharada: U+111CE to U+111CF.
    if (character >= 0xf091878e && character <= 0xf091878f) {
      return F_true;
    }

    // Sinhala Archaic Numbers: U+111E0.
    if (character == 0xf09187a0) {
      return F_true;
    }

    // Sinhala Archaic Numbers: U+111F5 to U+111FF.
    if (character >= 0xf09187b5 && character <= 0xf09187bf) {
      return F_true;
    }

    // Khojki: U+11212.
    if (character == 0xf0918892) {
      return F_true;
    }

    // Khojki: U+1123E to U+1124F.
    if (character >= 0xf09188be && character <= 0xf091898f) {
      return F_true;
    }

    // Multani: U+11287, U+11289, U+1128E, U+1129E.
    if (character == 0xf0918a87 || character == 0xf0918a89 || character == 0xf0918a8e || character == 0xf0918a9e) {
      return F_true;
    }

    // Multani: U+112AA to U+112AF.
    if (character >= 0xf0918aaa && character <= 0xf0918aaf) {
      return F_true;
    }

    // Khudawadi: U+112EB to U+112EF.
    if (character >= 0xf0918bab && character <= 0xf0918baf) {
      return F_true;
    }

    // Khudawadi: U+112FA to U+112FF.
    if (character >= 0xf0918bba && character <= 0xf0918bbf) {
      return F_true;
    }

    // Grantha: U+11304.
    if (character == 0xf0918c84) {
      return F_true;
    }

    // Grantha: U+1130D to U+1130E.
    if (character >= 0xf0918c8d && character <= 0xf0918c8e) {
      return F_true;
    }

    // Grantha: U+11311 to U+11312.
    if (character >= 0xf0918c91 && character <= 0xf0918c92) {
      return F_true;
    }

    // Grantha: U+11329, U+11331, U+11334.
    if (character == 0xf0918ca9 || character == 0xf0918cb1 || character == 0xf0918cb4) {
      return F_true;
    }

    // Grantha: U+1133A to U+1133B.
    if (character >= 0xf0918cb4 && character <= 0xf0918cbb) {
      return F_true;
    }

    // Grantha: U+11345 to U+11346.
    if (character >= 0xf0918d85 && character <= 0xf0918d86) {
      return F_true;
    }

    // Grantha: U+11349 to U+1134A.
    if (character >= 0xf0918d89 && character <= 0xf0918d8a) {
      return F_true;
    }

    // Grantha: U+1134E to U+1134F.
    if (character >= 0xf0918d8e && character <= 0xf0918d8f) {
      return F_true;
    }

    // Grantha: U+11351 to U+11356.
    if (character >= 0xf0918d91 && character <= 0xf0918d96) {
      return F_true;
    }

    // Grantha: U+11358 to U+1135C.
    if (character >= 0xf0918d98 && character <= 0xf0918d9c) {
      return F_true;
    }

    // Grantha: U+11364 to U+11365.
    if (character >= 0xf0918da4 && character <= 0xf0918da5) {
      return F_true;
    }

    // Grantha: U+1136D to U+1136F.
    if (character >= 0xf0918dad && character <= 0xf0918daf) {
      return F_true;
    }

    // Grantha: U+11375 to U+1137F.
    if (character >= 0xf0918db5 && character <= 0xf0918dbf) {
      return F_true;
    }

    // Tirhuta: U+114C8 to U+114CF.
    if (character >= 0xf0919388 && character <= 0xf091938f) {
      return F_true;
    }

    // Tirhuta: U+114DA to U+114DF.
    if (character >= 0xf091939a && character <= 0xf091939f) {
      return F_true;
    }

    // Siddham: U+115B6 to U+115B7.
    if (character >= 0xf09196b6 && character <= 0xf09196b7) {
      return F_true;
    }

    // Siddham: U+115DE to U+115FF.
    if (character >= 0xf091979e && character <= 0xf09197bf) {
      return F_true;
    }

    // Modi: U+11645 to U+1164F.
    if (character >= 0xf0919985 && character <= 0xf091998f) {
      return F_true;
    }

    // Modi: U+1165A to U+1165F.
    if (character >= 0xf091999a && character <= 0xf091999f) {
      return F_true;
    }

    // Takri: U+116B8 to U+116BF.
    if (character >= 0xf0919ab8 && character <= 0xf0919abf) {
      return F_true;
    }

    // Takri: U+116CA to U+116CF.
    if (character >= 0xf0919b8a && character <= 0xf0919b8f) {
      return F_true;
    }

    // Ahom: U+1171A to U+1171C.
    if (character >= 0xf0919c9a && character <= 0xf0919c9c) {
      return F_true;
    }

    // Ahom: U+1172C to U+1172F.
    if (character >= 0xf0919cac && character <= 0xf0919caf) {
      return F_true;
    }

    // Warang Citi: U+118F3 to U+118FE.
    if (character >= 0xf091a3b3 && character <= 0xF091A3BE) {
      return F_true;
    }

    // Pau Cin Hau: U+11AF9 to U+11AFF.
    if (character >= 0xf091abb9 && character <= 0xf091abbf) {
      return F_true;
    }

    // Cuneiform: U+1239A to U+123FF.
    if (character >= 0xf0928e9a && character <= 0xf0928fbf) {
      return F_true;
    }

    // Cuneiform Numbers and Punctuation: U+1246F to U+1247F.
    if (character >= 0xf09291af && character <= 0xf09291bf) {
      return F_true;
    }

    // Early Dynastic Cuneiform: U+12544 to U+1254F.
    if (character >= 0xf0929584 && character <= 0xf092958f) {
      return F_true;
    }

    // Egyptian Hieroglyphs: U+1342F.
    if (character == 0xf09390af) {
      return F_true;
    }

    // Anatolian Hieroglyphs: U+14647 to U+1467F.
    if (character >= 0xf0949987 && character <= 0xf09499bf) {
      return F_true;
    }

    // Bamum Supplement: U+16A39 to U+16A3F.
    if (character >= 0xf096a8b9 && character <= 0xf096a8bf) {
      return F_true;
    }

    // Mro: U+16A5F.
    if (character == 0xf096a99f) {
      return F_true;
    }

    // Mro: U+16A6A to U+16A6D.
    if (character >= 0xf096a9aa && character <= 0xf096a9ad) {
      return F_true;
    }

    // Bassa Vah: U+16AEE to U+16AEF.
    if (character >= 0xf096abae && character <= 0xf096abaf) {
      return F_true;
    }

    // Bassa Vah: U+16AF6 to U+16AFF.
    if (character >= 0xf096abb6 && character <= 0xf096abb6) {
      return F_true;
    }

    // Pahawh Hmong: U+16B46 to U+16B4F.
    if (character >= 0xf096ad86 && character <= 0xf096ad8f) {
      return F_true;
    }

    // Pahawh Hmong: U+16B5A, U+16B62.
    if (character == 0xf096ad9a || character == 0xf096ada2) {
      return F_true;
    }

    // Pahawh Hmong: U+16B78 to U+16B7C.
    if (character >= 0xf096adb8 && character <= 0xf096adbc) {
      return F_true;
    }

    // Miao: U+16F45 to U+16F4F.
    if (character >= 0xf096bd85 && character <= 0xf096bd8f) {
      return F_true;
    }

    // Miao: U+16F7F to U+16F8E.
    if (character >= 0xf096bdbf && character <= 0xf096be8e) {
      return F_true;
    }

    // Kana Supplement: U+1B002 to U+1B0FF.
    if (character >= 0xf09b8082 && character <= 0xf09b83bf) {
      return F_true;
    }

    // Duployan: U+1BC6B to U+1BC6F.
    if (character >= 0xf09bb1ab && character <= 0xf09bb1af) {
      return F_true;
    }

    // Duployan: U+1BC7D to U+1BC7F.
    if (character >= 0xf09bb1bd && character <= 0xf09bb1bf) {
      return F_true;
    }

    // Duployan: U+1BC89 to U+1BC8F.
    if (character >= 0xf09bb289 && character <= 0xf09bb28f) {
      return F_true;
    }

    // Duployan: U+1BC9A to U+1BC9B.
    if (character >= 0xf09bb29a && character <= 0xf09bb29b) {
      return F_true;
    }

    // Shorthand Format Controls: U+1BCA4 to U+1BCAF.
    if (character >= 0xf09bb2a4 && character <= 0xf09bb2af) {
      return F_true;
    }

    // Byzantine Musical Symbols: U+1D0F6 to U+1D0FF.
    if (character >= 0xf09d83b6 && character <= 0xf09d83bf) {
      return F_true;
    }

    // Musical Symbols: U+1D127 to U+1D128.
    if (character >= 0xf09d84a7 && character <= 0xf09d84a8) {
      return F_true;
    }

    // Musical Symbols: U+1D1E9 to U+1D1FF.
    if (character >= 0xf09d87a9 && character <= 0xf09d87bf) {
      return F_true;
    }

    // Ancient Greek Musical Notation: U+1D246 to U+1D24F.
    if (character >= 0xf09d8986 && character <= 0xf09d898f) {
      return F_true;
    }

    // Tai Xuan Jing Symbols: U+1D357 to U+1D35F.
    if (character >= 0xf09d8d97 && character <= 0xf09d8d9f) {
      return F_true;
    }

    // Counting Rod Numerals: U+1D372 to U+1D37F.
    if (character >= 0xf09d8db2 && character <= 0xf09d8dbf) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D506.
    if (character == 0xf09d9486) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D50B to U+1D50C.
    if (character >= 0xf09d948b && character <= 0xf09d948c) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D515, U+1D51D, U+1D53A, U+1D53F.
    if (character == 0xf09d9495 || character == 0xf09d949d || character == 0xf09d94ba || character == 0xf09d94bf) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D515.
    if (character == 0xf09d9495) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D547 to U+1D549.
    if (character >= 0xf09d9587 && character <= 0xf09d9589) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D551, U+1D6A6, U+1D6A7.
    if (character == 0xf09d9591 || character == 0xf09d9aa6 || character == 0xf09d9aa7) {
      return F_true;
    }

    // Mathematical Alphanumeric Symbols: U+1D7CC to U+1D7CD.
    if (character >= 0xf09d9f8c && character <= 0xf09d9f8d) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA8C to U+1DA9A.
    if (character >= 0xf09daa8c && character <= 0xf09daa9a) {
      return F_true;
    }

    // Sutton SignWriting: U+1DAA0.
    if (character == 0xf09daaa0) {
      return F_true;
    }

    // Mende Kikakui: U+1E8C5 to U+1E8C6.
    if (character >= 0xf09ea385 && character <= 0xf09ea386) {
      return F_true;
    }

    // Mende Kikakui: U+1E8D7 to U+1E8DF.
    if (character >= 0xf09ea397 && character <= 0xf09ea39f) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE04, U+1EE20, U+1EE23.
    if (character == 0xf09eb884 || character == 0xf09eb8a0 || character == 0xf09eb8a3) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE25 to U+1EE26.
    if (character >= 0xf09eb8a5 && character <= 0xf09eb8a6) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE28, U+1EE33, U+1EE38, U+1EE3A.
    if (character == 0xf09eb8a8 || character == 0xf09eb8b3 || character == 0xf09eb8b8 || character == 0xf09eb8ba) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE3C to U+1EE41.
    if (character >= 0xf09eb8bc && character <= 0xf09eb981) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE43 to U+1EE46.
    if (character >= 0xf09eb983 && character <= 0xf09eb986) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE48, U+1EE4A, U+1EE4C, U+1EE50.
    if (character == 0xf09eb988 || character == 0xf09eb98a || character == 0xf09eb98c || character == 0xf09eb990) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE53, U+1EE55, U+1EE56, U+1EE58.
    if (character == 0xf09eb993 || character == 0xf09eb995 || character == 0xf09eb996 || character == 0xf09eb998) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE5A, U+1EE5C, U+1EE5E, U+1EE60.
    if (character == 0xf09eb99a || character == 0xf09eb99c || character == 0xf09eb99e || character == 0xf09eb9a0) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE63, U+1EE65, U+1EE66, U+1EE6B.
    if (character == 0xf09eb9a3 || character == 0xf09eb9a5 || character == 0xf09eb9a6 || character == 0xf09eb9ab) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE73, U+1EE78, U+1EE7D, U+1EE7F.
    if (character == 0xf09eb9b3 || character == 0xf09eb9b8 || character == 0xf09eb9bd || character == 0xf09eb9bf) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE8A.
    if (character == 0xf09eba8a) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EE9C to U+1EEA0.
    if (character >= 0xf09eba9c && character <= 0xf09ebaa0) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EEA4, U+1EEAA.
    if (character == 0xf09ebaa4 || character == 0xf09ebaaa) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EEBC to U+1EEEF.
    if (character >= 0xf09ebabc && character <= 0xf09ebbaf) {
      return F_true;
    }

    // Arabic Mathematical Alphabetic Symbols: U+1EEF2 to U+1EEFF.
    if (character >= 0xf09ebbb2 && character <= 0xf09ebbbf) {
      return F_true;
    }

    // Mahjong Tiles: U+1F02C to U+1F02F.
    if (character >= 0xf09f80ac && character <= 0xf09f80af) {
      return F_true;
    }

    // Domino Tiles: U+1F094 to U+1F09F.
    if (character >= 0xf09f8294 && character <= 0xf09f829f) {
      return F_true;
    }

    // Playing Cards: U+1F0AF to U+1F0B0.
    if (character >= 0xf09f82af && character <= 0xf09f82b0) {
      return F_true;
    }

    // Playing Cards: U+1F0C0, U+1F0D0.
    if (character == 0xf09f8380 || character == 0xf09f8390) {
      return F_true;
    }

    // Playing Cards: U+1F0F6 to U+1F0FF.
    if (character >= 0xf09f83b6 && character <= 0xf09f83bf) {
      return F_true;
    }

    // Enclosed Alphanumeric Supplement: U+1F10D to U+1F10F.
    if (character >= 0xf09f848d && character <= 0xf09f848f) {
      return F_true;
    }

    // Enclosed Alphanumeric Supplement: U+1F12F.
    if (character == 0xf09f84af) {
      return F_true;
    }

    // Enclosed Alphanumeric Supplement: U+1F16C to U+1F16F.
    if (character >= 0xf09f85ac && character <= 0xf09f85af) {
      return F_true;
    }

    // Enclosed Alphanumeric Supplement: U+1F19B to U+1F1E5.
    if (character >= 0xf09f869b && character <= 0xf09f87a5) {
      return F_true;
    }

    // Enclosed Ideographic Supplement: U+1F203 to U+1F20F.
    if (character >= 0xf09f8883 && character <= 0xf09f888f) {
      return F_true;
    }

    // Enclosed Ideographic Supplement: U+1F23B to U+1F23F.
    if (character >= 0xf09f88bb && character <= 0xf09f88bf) {
      return F_true;
    }

    // Enclosed Ideographic Supplement: U+1F249 to U+1F24F.
    if (character >= 0xf09f8989 && character <= 0xf09f898f) {
      return F_true;
    }

    // Enclosed Ideographic Supplement: U+1F252 to U+1F2FF.
    if (character >= 0xf09f8992 && character <= 0xf09f8bbf) {
      return F_true;
    }

    // Transport and Map Symbols: U+1F6D1 to U+1F6DF.
    if (character >= 0xf09f9b91 && character <= 0xf09f9b9f) {
      return F_true;
    }

    // Transport and Map Symbols: U+1F6ED to U+1F6EF.
    if (character >= 0xf09f9bad && character <= 0xf09f9baf) {
      return F_true;
    }

    // Transport and Map Symbols: U+1F6F4 to U+1F6FF.
    if (character >= 0xf09f9bb4 && character <= 0xf09f9bbf) {
      return F_true;
    }

    // Alchemical Symbols: U+1F774 to U+1F77F.
    if (character >= 0xf09f9db4 && character <= 0xf09f9dbf) {
      return F_true;
    }

    // Geometric Shapes Extended: U+1F7D5 to U+1F7FF.
    if (character >= 0xf09f9f95 && character <= 0xf09f9fbf) {
      return F_true;
    }

    // Supplemental Arrows C: U+1F80C to U+1F80F.
    if (character >= 0xf09fa08c && character <= 0xf09fa08f) {
      return F_true;
    }

    // Supplemental Arrows C: U+1F848 to U+1F84F.
    if (character >= 0xf09fa188 && character <= 0xf09fa18f) {
      return F_true;
    }

    // Supplemental Arrows C: U+1F85A to U+1F85F.
    if (character >= 0xf09fa19a && character <= 0xf09fa19f) {
      return F_true;
    }

    // Supplemental Arrows C: U+1F888 to U+1F88F.
    if (character >= 0xf09fa288 && character <= 0xf09fa28f) {
      return F_true;
    }

    // Supplemental Arrows C: U+1F8AE to U+1F8FF.
    if (character >= 0xf09fa2ae && character <= 0xf09fa3bf) {
      return F_true;
    }

    // Supplemental Symbols and Pictographs: U+1F900 to U+1F90F.
    if (character >= 0xf09fa480 && character <= 0xf09fa48f) {
      return F_true;
    }

    // Supplemental Symbols and Pictographs: U+1F919 to U+1F97F.
    if (character >= 0xf09fa499 && character <= 0xf09fa5bf) {
      return F_true;
    }

    // Supplemental Symbols and Pictographs: U+1F985 to U+1F9BF.
    if (character >= 0xf09fa685 && character <= 0xf09fa6bf) {
      return F_true;
    }

    // Supplemental Symbols and Pictographs: U+1F9C1 to U+1F9FF.
    if (character >= 0xf09fa781 && character <= 0xf09fa7bf) {
      return F_true;
    }

    // CJK Unified Ideographs Extension B: U+2A6D7 to U+2A6FF.
    if (character >= 0xf0aa9b97 && character <= 0xf0aa9bbf) {
      return F_true;
    }

    // CJK Unified Ideographs Extension C: U+2B735 to U+2B73F.
    if (character >= 0xf0ab9cb5 && character <= 0xf0ab9cbf) {
      return F_true;
    }

    // CJK Unified Ideographs Extension D: U+2B81E to U+2B81F.
    if (character >= 0xf0aba09e && character <= 0xf0aba09f) {
      return F_true;
    }

    // CJK Unified Ideographs Extension E: U+2CEA2 to U+2F7FD.
    if (character >= 0xf0acbaa2 && character <= 0xf0af9fbd) {
      return F_true;
    }

    // CJK Compatibility Ideographs Supplement: U+2FA1E to U+2FFFD.
    if (character >= 0xf0b08080 && character <= 0xf0afbfbd) {
      return F_true;
    }

    // Tertiary Ideographic Plane: U+30000 to U+3FFFD.
    if (character >= 0xf0b08080 && character <= 0xf0bfbfbd) {
      return F_true;
    }

    // Plane 5: U+40000 to U+4FFFD.
    if (character >= 0xf1808080 && character <= 0xf18fbfbd) {
      return F_true;
    }

    // Plane 6: U+50000 to U+5FFFD.
    if (character >= 0xf1908080 && character <= 0xf19fbfbd) {
      return F_true;
    }

    // Plane 7: U+60000 to U+6FFFD.
    if (character >= 0xf1a08080 && character <= 0xf1afbfbd) {
      return F_true;
    }

    // Plane 8: U+70000 to U+7FFFD.
    if (character >= 0xf1b08080 && character <= 0xf1bfbfbd) {
      return F_true;
    }

    // Plane 9: U+80000 to U+8FFFD.
    if (character >= 0xf2808080 && character <= 0xf28fbfbd) {
      return F_true;
    }

    // Plane 10: U+90000 to U+9FFFD.
    if (character >= 0xf2908080 && character <= 0xf29fbfbd) {
      return F_true;
    }

    // Plane 11: U+A0000 to U+AFFFD.
    if (character >= 0xf2a08080 && character <= 0xf2afbfbd) {
      return F_true;
    }

    // Plane 12: U+B0000 to U+BFFFD.
    if (character >= 0xf2b08080 && character <= 0xf2bfbfbd) {
      return F_true;
    }

    // Plane 13: U+C0000 to U+CFFFD.
    if (character >= 0xf3808080 && character <= 0xf38fbfbd) {
      return F_true;
    }

    // Plane 14: U+D0000 to U+DFFFD.
    if (character >= 0xf3908080 && character <= 0xf39fbfbd) {
      return F_true;
    }

    // Supplementary Special Purpose, Tags: U+E0000.
    if (character == 0xf3a08080) {
      return F_true;
    }

    // Supplementary Special Purpose, Tags: U+E0002 to U+E001F.
    if (character >= 0xf3a08082 && character <= 0xf3a0809f) {
      return F_true;
    }

    // Supplementary Special Purpose, between Tags and Variation Selectors Supplement: U+E0080 to U+E00FF.
    if (character >= 0xf3a08280 && character <= 0xf3a083bf) {
      return F_true;
    }

    // Supplementary Special Purpose, after Variation Selectors Supplement: U+E01F0 to U+EFFFD.
    if (character >= 0xf3a087b0 && character <= 0xf3afbfbd) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_unassigned_) || !defined(_di_f_utf_is_unassigned_)

#ifdef __cplusplus
} // extern "C"
#endif

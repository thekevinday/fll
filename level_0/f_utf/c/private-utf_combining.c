#include "utf.h"
#include "private-utf.h"
#include "private-utf_combining.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)
  f_status_t private_f_utf_character_is_combining(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      // Diacritical Marks: U+0300 to U+036F.
      if (sequence >= 0xcc800000 && sequence <= 0xcdaf0000) {
        return F_true;
      }

      // Cyrillic: U+0483 to U+0489.
      if (sequence >= 0xd2830000 && sequence <= 0xd2890000) {
        return F_true;
      }

      // Hebrew: U+0591 to U+05BD.
      if (sequence >= 0xd6910000 && sequence <= 0xd6bd0000) {
        return F_true;
      }

      // Hebrew: U+05C1 to U+05C7.
      if (sequence >= 0xd7810000 && sequence <= 0xd7870000) {
        return F_true;
      }

      // Arabic: U+0610 to U+061A.
      if (sequence >= 0xd8900000 && sequence <= 0xd89a0000) {
        return F_true;
      }

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xd9) {

        // Arabic: U+064B to U+065F.
        if (sequence >= 0xd98b0000 && sequence <= 0xd99f0000) {
          return F_true;
        }

        // Arabic: U+0670.
        if (sequence == 0xd9b00000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdb) {

        // Arabic: U+06D6 to U+06DC.
        if (sequence >= 0xdb960000 && sequence <= 0xdb9c0000) {
          return F_true;
        }

        // Arabic: U+06D6 to U+06DC.
        if (sequence >= 0xdb960000 && sequence <= 0xdb9c0000) {
          return F_true;
        }

        // Arabic: U+06DF to U+06E4.
        if (sequence >= 0xdb9f0000 && sequence <= 0xdba40000) {
          return F_true;
        }

        // Arabic: U+06E7 to U+06E8.
        if (sequence >= 0xdba70000 && sequence <= 0xdba80000) {
          return F_true;
        }

        // Arabic: U+06EA to U+06ED.
        if (sequence >= 0xdbaa0000 && sequence <= 0xdbad0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdc) {

        // Syriac: U+0711.
        if (sequence == 0xdc910000) {
          return F_true;
        }

        // Syriac: U+0730 to U+073F.
        if (sequence >= 0xdcb00000 && sequence <= 0xdcbf0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdd) {

        // Syriac: U+0740 to U+074A.
        if (sequence >= 0xdd800000 && sequence <= 0xdd8a0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xde) {

        // Thaana: U+07A6 to U+07B0.
        if (sequence >= 0xdea60000 && sequence <= 0xdeb00000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xdf) {

        // NKo: U+07EB to U+07F3.
        if (sequence >= 0xdfab0000 && sequence <= 0xdfb30000) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Samaritan: U+0816 to U+0819.
        if (sequence >= 0xe0a09600 && sequence <= 0xe0a09900) {
          return F_true;
        }

        // Samaritan: U+081B to U+0823.
        if (sequence >= 0xe0a09b00 && sequence <= 0xe0a0a300) {
          return F_true;
        }

        // Samaritan: U+0825 to U+0827.
        if (sequence >= 0xe0a0a500 && sequence <= 0xe0a0a700) {
          return F_true;
        }

        // Samaritan: U+0829.
        if (sequence == 0xe0a0a900) {
          return F_true;
        }

        // Samaritan: U+082A to U+082D.
        if (sequence >= 0xe0a0aa00 && sequence <= 0xe0a0ad00) {
          return F_true;
        }

        // Mandaic: U+0859 to U+085B.
        if (sequence >= 0xe0a19900 && sequence <= 0xe0a19b00) {
          return F_true;
        }

        // Arabic Extended-B: U+0898 to U+089F.
        if (sequence >= 0xe0a29800 && sequence <= 0xe0a29f00) {
          return F_true;
        }

        // Arabic Extended-A: U+08CA to U+08FF.
        if (sequence >= 0xe0a38a00 && sequence <= 0xe0a3bf00) {
          return F_true;
        }

        // Devanagari: U+0900 to U+0903.
        if (sequence >= 0xe0a48000 && sequence <= 0xe0a48300) {
          return F_true;
        }

        // Devanagari: U+093A to U+093C.
        if (sequence >= 0xe0a4ba00 && sequence <= 0xe0a4bc00) {
          return F_true;
        }

        // Devanagari: U+093E to U+094F.
        if (sequence >= 0xe0a4be00 && sequence <= 0xe0a58f00) {
          return F_true;
        }

        // Devanagari: U+0951 to U+0957.
        if (sequence >= 0xe0a59100 && sequence <= 0xe0a59700) {
          return F_true;
        }

        // Devanagari: U+0962 to U+0963.
        if (sequence >= 0xe0a5a200 && sequence <= 0xe0a5a300) {
          return F_true;
        }

        // Bengali: U+0981 to U+0983.
        if (sequence >= 0xe0a68100 && sequence <= 0xe0a68300) {
          return F_true;
        }

        // Bengali: U+09BC.
        if (sequence == 0xe0a6bc00) {
          return F_true;
        }

        // Bengali: U+09BE to U+09C4.
        if (sequence >= 0xe0a6be00 && sequence <= 0xe0a78400) {
          return F_true;
        }

        // Bengali: U+09C7, U+09C8.
        if (sequence == 0xe0a78700 || sequence == 0xe0a78800) {
          return F_true;
        }

        // Bengali: U+09CB to U+09CD.
        if (sequence >= 0xe0a78b00 && sequence <= 0xe0a78d00) {
          return F_true;
        }

        // Bengali: U+09E2, U+09E3, U+09FE.
        if (sequence == 0xe0a7a200 || sequence == 0xe0a7a300 || sequence == 0xe0a7be00) {
          return F_true;
        }

        // Gurmukhi: U+0A01 to U+0A03.
        if (sequence >= 0xe0a88100 && sequence <= 0xe0a88300) {
          return F_true;
        }

        // Gurmukhi: U+0A3C.
        if (sequence == 0xe0a8bc00) {
          return F_true;
        }

        // Gurmukhi: U+0A3E to U+0A42.
        if (sequence >= 0xe0a8be00 && sequence <= 0xe0a98200) {
          return F_true;
        }

        // Gurmukhi: U+0A47 to U+0A48.
        if (sequence >= 0xe0a98700 && sequence <= 0xe0a98800) {
          return F_true;
        }

        // Gurmukhi: U+0A4B to U+0A4D.
        if (sequence >= 0xe0a98b00 && sequence <= 0xe0a98d00) {
          return F_true;
        }

        // Gurmukhi: U+0A51.
        if (sequence == 0xe0a99100) {
          return F_true;
        }

        // Gurmukhi: U+0A70, U+0A71, U+0A75.
        if (sequence == 0xe0a9b000 || sequence == 0xe0a9b100 || sequence == 0xe0a9b500) {
          return F_true;
        }

        // Gujarati: U+0A81 to U+0A82.
        if (sequence >= 0xe0aa8100 && sequence <= 0xe0aa8200) {
          return F_true;
        }

        // Gujarati: U+0ABC.
        if (sequence == 0xe0aabc00) {
          return F_true;
        }

        // Gujarati: U+0ABE to U+0AC5.
        if (sequence >= 0xe0aabe00 && sequence <= 0xe0ab8500) {
          return F_true;
        }

        // Gujarati: U+0AC7 to U+0AC9.
        if (sequence >= 0xe0ab8700 && sequence <= 0xe0ab8900) {
          return F_true;
        }

        // Gujarati: U+0ACB to U+0ACD.
        if (sequence >= 0xe0ab8b00 && sequence <= 0xe0ab8d00) {
          return F_true;
        }

        // Gujarati: U+0AE2 to U+0AE3.
        if (sequence >= 0xe0aba200 && sequence <= 0xe0aba300) {
          return F_true;
        }

        // Gujarati: U+0AFA to U+0AFF.
        if (sequence >= 0xe0abba00 && sequence <= 0xe0abbf00) {
          return F_true;
        }

        // Oriya: U+0B01, U+0B3C, U+0B3F.
        if (sequence == 0xe0ac8100 || sequence == 0xe0acbc00 || sequence == 0xe0acbf00) {
          return F_true;
        }

        // Oriya: U+0B41 to U+0B44.
        if (sequence >= 0xe0ad8100 && sequence <= 0xe0ad8400) {
          return F_true;
        }

        // Oriya: U+0B4D, U+0B56, U+0B62, U+0B63.
        if (sequence == 0xe0ad8d00 || sequence == 0xe0ad9600 || sequence == 0xe0ada200 || sequence == 0xe0ada300) {
          return F_true;
        }

        // Tamil: U+0BC0, U+0BCD.
        if (sequence == 0xe0af8000 || sequence == 0xe0af8d00) {
          return F_true;
        }

        // Telugu: U+0C00.
        if (sequence == 0xe0b08000) {
          return F_true;
        }

        // Telugu: U+0C3E to U+0C40.
        if (sequence >= 0xe0b0be00 && sequence <= 0xe0b18000) {
          return F_true;
        }

        // Telugu: U+0C46 to U+0C48.
        if (sequence >= 0xe0b18600 && sequence <= 0xe0b18800) {
          return F_true;
        }

        // Telugu: U+0C4A to U+0C4D.
        if (sequence >= 0xe0b18a00 && sequence <= 0xe0b18d00) {
          return F_true;
        }

        // Telugu: U+0C55, U+0C56, U+0C62, U+0C63.
        if (sequence == 0xe0b19500 || sequence == 0xe0b19600 || sequence == 0xe0b1a200 || sequence == 0xe0b1a300) {
          return F_true;
        }

        // Kannada: U+0C81.
        if (sequence == 0xe0b28100) {
          return F_true;
        }

        // Kannada: U+0CBC to U+0CCD.
        if (sequence >= 0xe0b2bc00 && sequence <= 0xe0b38d00) {
          return F_true;
        }

        // Kannada: U+0CE2, U+0CE3, U+0CF3.
        if (sequence == 0xe0b3a200 || sequence == 0xe0b3a300 || sequence == 0xe0b3b300) {
          return F_true;
        }

        // Malayalam: U+0D01.
        if (sequence == 0xe0b48100) {
          return F_true;
        }

        // Malayalam: U+0D41 to U+0D44.
        if (sequence >= 0xe0b58100 && sequence <= 0xe0b58400) {
          return F_true;
        }

        // Malayalam: U+0D4D, U+0D62, U+0D63.
        if (sequence == 0xe0b58d00 || sequence == 0xe0b5a200 || sequence == 0xe0b5a300) {
          return F_true;
        }

        // Sinhala: U+0DCA.
        if (sequence == 0xe0b78a00) {
          return F_true;
        }

        // Sinhala: U+0DD2 to U+0DD4.
        if (sequence >= 0xe0b79200 && sequence <= 0xe0b79400) {
          return F_true;
        }

        // Sinhala: U+0DD6.
        if (sequence == 0xe0b79600) {
          return F_true;
        }

        // Thai: U+0E31.
        if (sequence == 0xe0b8b100) {
          return F_true;
        }

        // Thai: U+0E34 to U+0E3A.
        if (sequence >= 0xe0b8b400 && sequence <= 0xe0b8ba00) {
          return F_true;
        }

        // Thai: U+0E47 to U+0E4E.
        if (sequence >= 0xe0b98700 && sequence <= 0xe0b98e00) {
          return F_true;
        }

        // Lao: U+0EB1.
        if (sequence == 0xe0bab100) {
          return F_true;
        }

        // Lao: U+0EB4 to U+0EB9.
        if (sequence >= 0xe0bab400 && sequence <= 0xe0bab900) {
          return F_true;
        }

        // Lao: U+0EBB, U+0EBC, U+0ECE.
        if (sequence == 0xe0babb00 || sequence == 0xe0babc00 || sequence == 0xe0bb8e00) {
          return F_true;
        }

        // Tibetan: U+0F18 to U+0F19.
        if (sequence >= 0xe0bc9800 && sequence <= 0xe0bc9900) {
          return F_true;
        }

        // Tibetan: U+0F35, U+0F37, U+0F39.
        if (sequence == 0xe0bcb500 || sequence == 0xe0bcb700 || sequence == 0xe0bcb900) {
          return F_true;
        }

        // Tibetan: U+0F71 to U+0F7E.
        if (sequence >= 0xe0bdb100 && sequence <= 0xe0bdbe00) {
          return F_true;
        }

        // Tibetan: U+0F80 to U+0F84.
        if (sequence >= 0xe0be8000 && sequence <= 0xe0be8400) {
          return F_true;
        }

        // Tibetan: U+0F86 to U+0F87.
        if (sequence >= 0xe0be8600 && sequence <= 0xe0be8700) {
          return F_true;
        }

        // Tibetan: U+0F8D to U+0F97.
        if (sequence >= 0xe0be8d00 && sequence <= 0xe0be9700) {
          return F_true;
        }

        // Tibetan: U+0F99 to U+0FBC.
        if (sequence >= 0xe0be9900 && sequence <= 0xe0bebc00) {
          return F_true;
        }

        // Tibetan: U+0FC6.
        if (sequence == 0xe0bf8600) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Myanmar: U+102D to U+1030.
        if (sequence >= 0xe180ad00 && sequence <= 0xe180b000) {
          return F_true;
        }

        // Myanmar: U+1039 to U+103A.
        if (sequence >= 0xe180b900 && sequence <= 0xe180ba00) {
          return F_true;
        }

        // Myanmar: U+103D to U+103E.
        if (sequence >= 0xe180bd00 && sequence <= 0xe180be00) {
          return F_true;
        }

        // Myanmar: U+1058 to U+1059.
        if (sequence >= 0xe1819800 && sequence <= 0xe1819900) {
          return F_true;
        }

        // Myanmar: U+105E to U+1060.
        if (sequence >= 0xe1819e00 && sequence <= 0xe181a000) {
          return F_true;
        }

        // Myanmar: U+1071 to U+1074.
        if (sequence >= 0xe181b100 && sequence <= 0xe181b400) {
          return F_true;
        }

        // Myanmar: U+1082, U+1085, U+1086, U+108D.
        if (sequence == 0xe1828200 || sequence == 0xe1828500 || sequence == 0xe1828600 || sequence == 0xe1828d00) {
          return F_true;
        }

        // Myanmar: U+109D.
        if (sequence == 0xe1829d00) {
          return F_true;
        }

        // Ethiopic: U+135D to U+135F.
        if (sequence >= 0xe18d9d00 && sequence <= 0xe18d9f00) {
          return F_true;
        }

        // Tagalog: U+1712 to U+1714.
        if (sequence >= 0xe19c9200 && sequence <= 0xe19c9400) {
          return F_true;
        }

        // Hanunoo: U+1732 to U+1734.
        if (sequence >= 0xe19cb200 && sequence <= 0xe19cb400) {
          return F_true;
        }

        // Buhid: U+1752 to U+1753.
        if (sequence >= 0xe19d9200 && sequence <= 0xe19d9300) {
          return F_true;
        }

        // Tagbanwa: U+1772 to U+1773.
        if (sequence >= 0xe19db200 && sequence <= 0xe19db300) {
          return F_true;
        }

        // Khmer: U+17B4 to U+17B5.
        if (sequence >= 0xe19eb400 && sequence <= 0xe19eb500) {
          return F_true;
        }

        // Khmer: U+17B7 to U+17BD.
        if (sequence >= 0xe19eb700 && sequence <= 0xe19ebd00) {
          return F_true;
        }

        // Khmer: U+17C6, U+17C9.
        if (sequence == 0xe19f8600 || sequence == 0xe19f8900) {
          return F_true;
        }

        // Khmer: U+17CA to U+17D3.
        if (sequence >= 0xe19f8a00 && sequence <= 0xe19f9300) {
          return F_true;
        }

        // Khmer: U+17DD.
        if (sequence == 0xe19f9d00) {
          return F_true;
        }

        // Mongolian: U+180B to U+180D.
        if (sequence >= 0xe1a08b00 && sequence <= 0xe1a08d00) {
          return F_true;
        }

        // Mongolian: U+18A9.
        if (sequence == 0xe1a2a900) {
          return F_true;
        }

        // Mongolian: U+1920 to U+1922.
        if (sequence >= 0xe1a4a000 && sequence <= 0xe1a4a200) {
          return F_true;
        }

        // Limbu: U+1927, U+1928, U+1932.
        if (sequence == 0xe1a4a700 || sequence == 0xe1a4a800 || sequence == 0xe1a4b200) {
          return F_true;
        }

        // Limbu: U+1939 to U+193B.
        if (sequence >= 0xe1a4b900 && sequence <= 0xe1a4bb00) {
          return F_true;
        }

        // Buginese: U+1A17 to U+1A18.
        if (sequence >= 0xe1a89700 && sequence <= 0xe1a89800) {
          return F_true;
        }

        // Buginese: U+1A1B.
        if (sequence == 0xe1a89b00) {
          return F_true;
        }

        // Tai Tham: U+1A56.
        if (sequence == 0xe1a99600) {
          return F_true;
        }

        // Tai Tham: U+1A58 to U+1A5E.
        if (sequence >= 0xe1a99800 && sequence <= 0xe1a99e00) {
          return F_true;
        }

        // Tai Tham: U+1A60, U+1A62.
        if (sequence == 0xe1a9a000 || sequence == 0xe1a9a200) {
          return F_true;
        }

        // Tai Tham: U+1A65 to U+1A6C.
        if (sequence >= 0xe1a9a500 && sequence <= 0xe1a9ac00) {
          return F_true;
        }

        // Tai Tham: U+1A73 to U+1A7C.
        if (sequence >= 0xe1a9b300 && sequence <= 0xe1a9bc00) {
          return F_true;
        }

        // Tai Tham: U+1A7F.
        if (sequence == 0xe1a9bf00) {
          return F_true;
        }

        // Diacritical Marks Extended: U+1AB0 to U+1ACE.
        if (sequence >= 0xe1aab000 && sequence <= 0xe1ab8e00) {
          return F_true;
        }

        // Balinese: U+1B00 to U+1B03.
        if (sequence >= 0xe1ac8000 && sequence <= 0xe1ac8300) {
          return F_true;
        }

        // Balinese: U+1B34.
        if (sequence == 0xe1acb400) {
          return F_true;
        }

        // Balinese: U+1B36 to U+1B3A.
        if (sequence >= 0xe1acb600 && sequence <= 0xe1acba00) {
          return F_true;
        }

        // Balinese: U+1B3C, U+1B42.
        if (sequence == 0xe1acbc00 || sequence == 0xe1ad8200) {
          return F_true;
        }

        // Balinese: U+1B6B to U+1B73.
        if (sequence >= 0xe1adab00 && sequence <= 0xe1adb300) {
          return F_true;
        }

        // Sundanese: U+1B80 to U+1B81.
        if (sequence >= 0xe1ae8000 && sequence <= 0xe1ae8100) {
          return F_true;
        }

        // Sundanese: U+1BA2 to U+1BA5.
        if (sequence >= 0xe1aea200 && sequence <= 0xe1aea500) {
          return F_true;
        }

        // Sundanese: U+1BA8 to U+1BA9.
        if (sequence >= 0xe1aea800 && sequence <= 0xe1aea900) {
          return F_true;
        }

        // Sundanese: U+1BAB to U+1BAD.
        if (sequence >= 0xe1aeab00 && sequence <= 0xe1aead00) {
          return F_true;
        }

        // Batak: U+1BE6, U+1BE8, U+1BE9, U+1BED.
        if (sequence == 0xe1afa600 || sequence == 0xe1afa800 || sequence == 0xe1afa900 || sequence == 0xe1afad00) {
          return F_true;
        }

        // Batak: U+1BEF, U+1BF0, U+1BF1.
        if (sequence == 0xe1afaf00 || sequence == 0xe1afb000 || sequence == 0xe1afb100) {
          return F_true;
        }

        // Lepcha: U+1C2C to U+1C33.
        if (sequence >= 0xe1b0ac00 && sequence <= 0xe1b0b300) {
          return F_true;
        }

        // Lepcha: U+1C36 to U+1C37.
        if (sequence >= 0xe1b0b600 && sequence <= 0xe1b0b700) {
          return F_true;
        }

        // Vedic Extensions: U+1CD4 to U+1CD2.
        if (sequence >= 0xe1b39400 && sequence <= 0xe1b39200) {
          return F_true;
        }

        // Vedic Extensions: U+1CD0 to U+1CE0.
        if (sequence >= 0xe1b39000 && sequence <= 0xe1b3a000) {
          return F_true;
        }

        // Vedic Extensions: U+1CE2 to U+1CE8.
        if (sequence >= 0xe1b3a200 && sequence <= 0xe1b3a800) {
          return F_true;
        }

        // Vedic Extensions: U+1CED, U+1CF4, U+1CF8, U+1CF9.
        if (sequence == 0xe1b3ad00 || sequence == 0xe1b3b400 || sequence == 0xe1b3b800 || sequence == 0xe1b3b900) {
          return F_true;
        }

        // Vedic Extensions: U+1DC0 to U+1CE8.
        if (sequence >= 0xe1b78000 && sequence <= 0xe1b3a800) {
          return F_true;
        }

        // Diacritical Marks Supplement: U+1DC0 to U+1DFF.
        if (sequence >= 0xe1b78000 && sequence <= 0xe1b7bf00) {
          return F_true;
        }

        // Diacritical Marks Supplement: U+1DFB to U+1DFF.
        if (sequence >= 0xe1b7bb00 && sequence <= 0xe1b7bf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // Diacritical Marks For Symbols: U+20D0 to U+20F0.
        if (sequence >= 0xe2839000 && sequence <= 0xe283b000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // CJK Symbols and Punctuation: U+302A to U+302D.
        if (sequence >= 0xe380aa00 && sequence <= 0xe380ad00) {
          return F_true;
        }

        // Hiragana: U+3099, U+309A.
        if (sequence == 0xe3829900 || sequence == 0xe3829a00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Cyrillic Extended-B: U+3099.
        if (sequence == 0xea99af00) {
          return F_true;
        }

        // Cyrillic Extended-B: U+A66F to U+A672.
        if (sequence >= 0xea99af00 && sequence <= 0xea99b200) {
          return F_true;
        }

        // Cyrillic Extended-B: U+A674 to U+A69F.
        if (sequence >= 0xea99b400 && sequence <= 0xea9a9f00) {
          return F_true;
        }

        // Bamum: U+A6F0 to U+A6F1.
        if (sequence >= 0xea9bb000 && sequence <= 0xea9bb100) {
          return F_true;
        }

        // Syloti Nagri: U+A802, U+A806, U+A80B, U+A825.
        if (sequence == 0xeaa08200 || sequence == 0xeaa08600 || sequence == 0xeaa08b00 || sequence == 0xeaa0a500) {
          return F_true;
        }

        // Syloti Nagri: U+A826.
        if (sequence == 0xeaa0a600) {
          return F_true;
        }

        // Saurashtra: U+A8C4, U+A8C5.
        if (sequence == 0xeaa38400 || sequence == 0xeaa38500) {
          return F_true;
        }

        // Devanagari Extended: U+A8E0 to U+A8F1.
        if (sequence >= 0xeaa3a000 && sequence <= 0xeaa3b100) {
          return F_true;
        }

        // Kayah Li: U+A926 to U+A92D.
        if (sequence >= 0xeaa4a600 && sequence <= 0xeaa4ad00) {
          return F_true;
        }

        // Rejang: U+A947 to U+A951.
        if (sequence >= 0xeaa58700 && sequence <= 0xeaa59100) {
          return F_true;
        }

        // Javanese: U+A980 to U+A982.
        if (sequence >= 0xeaa68000 && sequence <= 0xeaa68200) {
          return F_true;
        }

        // Javanese: U+A9B3.
        if (sequence == 0xeaa6b300) {
          return F_true;
        }

        // Javanese: U+A9B6 to U+A9B9.
        if (sequence >= 0xeaa6b600 && sequence <= 0xeaa6b900) {
          return F_true;
        }

        // Javanese: U+A9BC.
        if (sequence == 0xeaa6bc00) {
          return F_true;
        }

        // Myanmar Extended-B: U+A9E5.
        if (sequence == 0xeaa7a500) {
          return F_true;
        }

        // Cham: U+AA29 to U+AA2E.
        if (sequence >= 0xeaa8a900 && sequence <= 0xeaa8ae00) {
          return F_true;
        }

        // Cham: U+AA31 to U+AA32.
        if (sequence >= 0xeaa8b100 && sequence <= 0xeaa8b200) {
          return F_true;
        }

        // Cham: U+AA35 to U+AA36.
        if (sequence >= 0xeaa8b500 && sequence <= 0xeaa8b600) {
          return F_true;
        }

        // Cham: U+AA43, U+AA4C.
        if (sequence == 0xeaa98300 || sequence == 0xeaa98c00) {
          return F_true;
        }

        // Tai Viet: U+AA7C.
        if (sequence == 0xeaa9bc00) {
          return F_true;
        }

        // Tai Viet: U+AAB0.
        if (sequence == 0xeaaab000) {
          return F_true;
        }

        // Tai Viet: U+AAB2 to U+AAB4.
        if (sequence >= 0xeaaab200 && sequence <= 0xeaaab400) {
          return F_true;
        }

        // Tai Viet: U+AAB7 to U+AAB8.
        if (sequence >= 0xeaaab700 && sequence <= 0xeaaab800) {
          return F_true;
        }

        // Tai Viet: U+AABE to U+AABF.
        if (sequence >= 0xeaaabe00 && sequence <= 0xeaaabf00) {
          return F_true;
        }

        // Tai Viet: U+AAC1.
        if (sequence == 0xeaab8100) {
          return F_true;
        }

        // Meetei Mayek Extensions: U+AAEC, U+AAED, U+AAF6.
        if (sequence == 0xeaabac00 || sequence == 0xeaabad00 || sequence == 0xeaabb600) {
          return F_true;
        }

        // Meetei Mayek: U+ABE5, U+ABE8, U+ABED.
        if (sequence == 0xeaafa500 || sequence == 0xeaafa800 || sequence == 0xeaafad00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // Alphabetic Presentation Forms: U+FB1E.
        if (sequence == 0xefac9e00) {
          return F_true;
        }

        // Variation Selectors: U+FE00 to U+FE0F.
        if (sequence >= 0xefb88000 && sequence <= 0xefb88f00) {
          return F_true;
        }

        // Variation Selectors: U+FE20 to U+FE0F.
        if (sequence >= 0xefb88000 && sequence <= 0xefb88f00) {
          return F_true;
        }

        // Combining Half Marks: U+FE20 to U+FE2F.
        if (sequence >= 0xefb8a000 && sequence <= 0xefb8af00) {
          return F_true;
        }
      }

      return F_false;
    }

    // Phaistos Disc: U+101FD.
    if (sequence == 0xf09087bd) {
      return F_true;
    }

    // Coptic Epact Numbers: U+102E0.
    if (sequence == 0xf0908ba0) {
      return F_true;
    }

    // Old Permic: U+10376 to U+1037A.
    if (sequence >= 0xf0908db6 && sequence <= 0xf0908dba) {
      return F_true;
    }

    // Kharoshthi: U+10A01 to U+10A03.
    if (sequence >= 0xf090a881 && sequence <= 0xf090a883) {
      return F_true;
    }

    // Kharoshthi: U+10A01, U+10A03, U+10A05, U+10A06.
    if (sequence == 0xf090a881 || sequence == 0xf090a883 || sequence == 0xf090a885 || sequence == 0xf090a886) {
      return F_true;
    }

    // Kharoshthi: U+10A0C to U+10A0F.
    if (sequence >= 0xf090a88c && sequence <= 0xf090a88f) {
      return F_true;
    }

    // Kharoshthi: U+10A38 to U+10A3A.
    if (sequence >= 0xf090a8b8 && sequence <= 0xf090a8ba) {
      return F_true;
    }

    // Kharoshthi: U+10A3F.
    if (sequence == 0xf090a8bf) {
      return F_true;
    }

    // Manichaean: U+10AE5, U+10AE6.
    if (sequence == 0xf090aba5 || sequence == 0xf090aba6) {
      return F_true;
    }

    // Hanifi Rohingya: U+10D24 to U+10D27.
    if (sequence >= 0xf090b4a3 && sequence <= 0xf090b4a7) {
      return F_true;
    }

    // Yezidi: U+10EAB to U+10EAD.
    if (sequence >= 0xf090baab && sequence <= 0xf090baad) {
      return F_true;
    }

    // Arabic Extended-C: U+10EFD to U+10EFF.
    if (sequence >= 0xf090bbbd && sequence <= 0xf090bbbf) {
      return F_true;
    }

    // Brahmi: U+11001.
    if (sequence == 0xf0918081) {
      return F_true;
    }

    // Brahmi: U+11038 to U+11046.
    if (sequence >= 0xf09180b8 && sequence <= 0xf0918186) {
      return F_true;
    }

    // Brahmi .. Kaithi: U+1107F to U+11081.
    if (sequence >= 0xf09181bf && sequence <= 0xf0918281) {
      return F_true;
    }

    // Kaithi: U+110B3 to U+110B6.
    if (sequence >= 0xf09182b3 && sequence <= 0xf09182b6) {
      return F_true;
    }

    // Kaithi: U+110B9, U+110BA.
    if (sequence == 0xf09182b9 || sequence == 0xf09182ba) {
      return F_true;
    }

    // Chakma: U+11100 to U+11102.
    if (sequence >= 0xf0918480 && sequence <= 0xf0918482) {
      return F_true;
    }

    // Chakma: U+11127 to U+1112B.
    if (sequence >= 0xf09184a7 && sequence <= 0xf09184ab) {
      return F_true;
    }

    // Chakma: U+1112D to U+11134.
    if (sequence >= 0xf09184ad && sequence <= 0xf09184b4) {
      return F_true;
    }

    // Mahajani: U+11173.
    if (sequence == 0xf09185b3) {
      return F_true;
    }

    // Sharada: U+11180 to U+11181.
    if (sequence >= 0xf0918680 && sequence <= 0xf0918681) {
      return F_true;
    }

    // Sharada: U+111B6 to U+111BE.
    if (sequence >= 0xf09186b6 && sequence <= 0xf09186be) {
      return F_true;
    }

    // Sharada: U+111CA to U+111CC.
    if (sequence >= 0xf091878a && sequence <= 0xf091878c) {
      return F_true;
    }

    // Sharada: U+111CA to U+111CC.
    if (sequence >= 0xf091878a && sequence <= 0xf091878c) {
      return F_true;
    }

    // Kawi: U+11F00 to U+11F03.
    if (sequence >= 0xf091bc80 && sequence <= 0xf091bc83) {
      return F_true;
    }

    // Kawi: U+11F34 to U+11F3A.
    if (sequence >= 0xf091bcb4 && sequence <= 0xf091bcba) {
      return F_true;
    }

    // Kawi: U+11F3E to U+11F42.
    if (sequence >= 0xf091bcbe && sequence <= 0xf091bd82) {
      return F_true;
    }

    // Khojki: U+1122F to U+11231.
    if (sequence >= 0xf09188af && sequence <= 0xf09188b1) {
      return F_true;
    }

    // Khojki: U+11234, U+11236, U+11237.
    if (sequence == 0xf09188b4 || sequence == 0xf09188b6 || sequence == 0xf09188b7) {
      return F_true;
    }

    // Khudawadi: U+112DF, U+112DF.
    if (sequence == 0xf0918b9f || sequence == 0xf0918b9f) {
      return F_true;
    }

    // Khojki: U+112E3 to U+112EA.
    if (sequence >= 0xf0918ba3 && sequence <= 0xf0918baa) {
      return F_true;
    }

    // Grantha: U+11300, U+11301, U+1133C, U+11340.
    if (sequence == 0xf0918c80 || sequence == 0xf0918c81 || sequence == 0xf0918cbc || sequence == 0xf0918d80) {
      return F_true;
    }

    // Grantha: U+11366 to U+1136C.
    if (sequence >= 0xf0918da6 && sequence <= 0xf0918dac) {
      return F_true;
    }

    // Grantha: U+11370 to U+11374.
    if (sequence >= 0xf0918db0 && sequence <= 0xf0918db4) {
      return F_true;
    }

    // Tirhuta: U+114B3 to U+114B8.
    if (sequence >= 0xf09192b3 && sequence <= 0xf09192b8) {
      return F_true;
    }

    // Tirhuta: U+114BA, U+114BF, U+114C0, U+114C2.
    if (sequence == 0xf09192ba || sequence == 0xf09192bf || sequence == 0xf0919380 || sequence == 0xf0919382) {
      return F_true;
    }

    // Tirhuta: U+114C3.
    if (sequence == 0xf0919383) {
      return F_true;
    }

    // Siddham: U+115B2 to U+115B5.
    if (sequence >= 0xf09196b2 && sequence <= 0xf09196b5) {
      return F_true;
    }

    // Siddham: U+115BC to U+115BD.
    if (sequence >= 0xf09196bc && sequence <= 0xf09196bd) {
      return F_true;
    }

    // Siddham: U+115BF, U+115C0, U+115DC, U+115DD.
    if (sequence == 0xf09196bf || sequence == 0xf0919780 || sequence == 0xf091979c || sequence == 0xf091979d) {
      return F_true;
    }

    // Modi: U+11633 to U+1163A.
    if (sequence >= 0xf09198b3 && sequence <= 0xf09198ba) {
      return F_true;
    }

    // Modi: U+1163D to U+11640.
    if (sequence >= 0xf09198bd && sequence <= 0xf0919980) {
      return F_true;
    }

    // Takri: U+116AB, U+116AD.
    if (sequence == 0xf0919aab || sequence == 0xf0919aad) {
      return F_true;
    }

    // Takri: U+116B0 to U+116B5.
    if (sequence >= 0xf0919ab0 && sequence <= 0xf0919ab5) {
      return F_true;
    }

    // Takri: U+116B7.
    if (sequence == 0xf0919ab7) {
      return F_true;
    }

    // Ahom: U+1171D to U+1171F.
    if (sequence >= 0xf0919c9d && sequence <= 0xf0919c9f) {
      return F_true;
    }

    // Ahom: U+11722 to U+11725.
    if (sequence >= 0xf0919ca2 && sequence <= 0xf0919ca5) {
      return F_true;
    }

    // Ahom: U+11727 to U+1172B.
    if (sequence >= 0xf0919ca7 && sequence <= 0xf0919cab) {
      return F_true;
    }

    // Bassa Vah: U+16AF0 to U+16AF4.
    if (sequence >= 0xf096abb0 && sequence <= 0xf096abb4) {
      return F_true;
    }

    // Pahawh Hmong: U+16B30 to U+16B36.
    if (sequence >= 0xf096acb0 && sequence <= 0xf096acb6) {
      return F_true;
    }

    // Miao: U+16F8F to U+16F92.
    if (sequence >= 0xf096be8f && sequence <= 0xf096be92) {
      return F_true;
    }

    // Duployan: U+1BC9D to U+1BC9E.
    if (sequence >= 0xf09bb29d && sequence <= 0xf09bb29e) {
      return F_true;
    }

    // Musical Symbols: U+1D167 to U+1D169.
    if (sequence >= 0xf09d85a7 && sequence <= 0xf09d85a9) {
      return F_true;
    }

    // Musical Symbols: U+1D17B to U+1D182.
    if (sequence >= 0xf09d85bb && sequence <= 0xf09d8682) {
      return F_true;
    }

    // Musical Symbols: U+1D185 to U+1D18B.
    if (sequence >= 0xf09d8685 && sequence <= 0xf09d868b) {
      return F_true;
    }

    // Musical Symbols: U+1D1AA to U+1D1AD.
    if (sequence >= 0xf09d86aa && sequence <= 0xf09d86ad) {
      return F_true;
    }

    // Ancient Greek Musical Notation: U+1D242 to U+1D244.
    if (sequence >= 0xf09d8982 && sequence <= 0xf09d8984) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA00 to U+1DA36.
    if (sequence >= 0xf09da880 && sequence <= 0xf09da8b6) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA3B to U+1DA6C.
    if (sequence >= 0xf09da8bb && sequence <= 0xf09da9ac) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA75, U+1DA84.
    if (sequence == 0xf09da9b5 || sequence == 0xf09daa84) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA9B to U+1DA9F.
    if (sequence >= 0xf09daa9b && sequence <= 0xf09daa9f) {
      return F_true;
    }

    // Sutton SignWriting: U+1DAA1 to U+1DAAF.
    if (sequence >= 0xf09daaa1 && sequence <= 0xf09daaaf) {
      return F_true;
    }

    // Cyrillic Extended-D: U+1E08F.
    if (sequence == 0xf09e828f) {
      return F_true;
    }

    // Nag Mundari: U+1E4EC to U+1E4EF.
    if (sequence >= 0xf09e93ac && sequence <= 0xf09e93af) {
      return F_true;
    }

    // Mende Kikakui: U+1E8D0 to U+1E8D6.
    if (sequence >= 0xf09ea390 && sequence <= 0xf09ea396) {
      return F_true;
    }

    // Variation Selectors Supplement: U+E0100 to U+E01EF.
    if (sequence >= 0xf3a08480 && sequence <= 0xf3a087af) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)

#ifdef __cplusplus
} // extern "C"
#endif

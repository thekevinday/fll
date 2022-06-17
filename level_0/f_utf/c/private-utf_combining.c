#include "utf.h"
#include "private-utf.h"
#include "private-utf_combining.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)
  f_status_t private_f_utf_character_is_combining(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      // Diacritical Marks: U+0300 to U+036F.
      if (character >= 0xcc800000 && character <= 0xcdaf0000) {
        return F_true;
      }

      // Cyrillic: U+0483 to U+0489.
      if (character >= 0xd2830000 && character <= 0xd2890000) {
        return F_true;
      }

      // Hebrew: U+0591 to U+05BD.
      if (character >= 0xd6910000 && character <= 0xd6bd0000) {
        return F_true;
      }

      // Hebrew: U+05C1 to U+05C7.
      if (character >= 0xd7810000 && character <= 0xd7870000) {
        return F_true;
      }

      // Arabic: U+0610 to U+061A.
      if (character >= 0xd8900000 && character <= 0xd89a0000) {
        return F_true;
      }

      if (macro_f_utf_char_t_to_char_1(character) == 0xd9) {

        // Arabic: U+064B to U+065F.
        if (character >= 0xd98b0000 && character <= 0xd99f0000) {
          return F_true;
        }

        // Arabic: U+0670.
        if (character == 0xd9b00000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xdb) {

        // Arabic: U+06D6 to U+06DC.
        if (character >= 0xdb960000 && character <= 0xdb9c0000) {
          return F_true;
        }

        // Arabic: U+06D6 to U+06DC.
        if (character >= 0xdb960000 && character <= 0xdb9c0000) {
          return F_true;
        }

        // Arabic: U+06DF to U+06E4.
        if (character >= 0xdb9f0000 && character <= 0xdba40000) {
          return F_true;
        }

        // Arabic: U+06E7 to U+06E8.
        if (character >= 0xdba70000 && character <= 0xdba80000) {
          return F_true;
        }

        // Arabic: U+06EA to U+06ED.
        if (character >= 0xdbaa0000 && character <= 0xdbad0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xdc) {

        // Syriac: U+0711.
        if (character == 0xdc910000) {
          return F_true;
        }

        // Syriac: U+0730 to U+073F.
        if (character >= 0xdcb00000 && character <= 0xdcbf0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xdd) {

        // Syriac: U+0740 to U+074A.
        if (character >= 0xdd800000 && character <= 0xdd8a0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xde) {

        // Thaana: U+07A6 to U+07B0.
        if (character >= 0xdea60000 && character <= 0xdeb00000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xdf) {

        // NKo: U+07EB to U+07F3.
        if (character >= 0xdfab0000 && character <= 0xdfb30000) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xe0) {

        // Samaritan: U+0816 to U+0819.
        if (character >= 0xe0a09600 && character <= 0xe0a09900) {
          return F_true;
        }

        // Samaritan: U+081B to U+0823.
        if (character >= 0xe0a09b00 && character <= 0xe0a0a300) {
          return F_true;
        }

        // Samaritan: U+0825 to U+0827.
        if (character >= 0xe0a0a500 && character <= 0xe0a0a700) {
          return F_true;
        }

        // Samaritan: U+0829.
        if (character == 0xe0a0a900) {
          return F_true;
        }

        // Samaritan: U+082A to U+082D.
        if (character >= 0xe0a0aa00 && character <= 0xe0a0ad00) {
          return F_true;
        }

        // Mandaic: U+0859 to U+085B.
        if (character >= 0xe0a19900 && character <= 0xe0a19b00) {
          return F_true;
        }

        // Arabic Extended-B: U+0898 to U+089F.
        if (character >= 0xe0a29800 && character <= 0xe0a29f00) {
          return F_true;
        }

        // Arabic Extended-A: U+08CA to U+08FF.
        if (character >= 0xe0a38a00 && character <= 0xe0a3bf00) {
          return F_true;
        }

        // Devanagari: U+0900 to U+0903.
        if (character >= 0xe0a48000 && character <= 0xe0a48300) {
          return F_true;
        }

        // Devanagari: U+093A to U+093C.
        if (character >= 0xe0a4ba00 && character <= 0xe0a4bc00) {
          return F_true;
        }

        // Devanagari: U+093E to U+094F.
        if (character >= 0xe0a4be00 && character <= 0xe0a58f00) {
          return F_true;
        }

        // Devanagari: U+0951 to U+0957.
        if (character >= 0xe0a59100 && character <= 0xe0a59700) {
          return F_true;
        }

        // Devanagari: U+0962 to U+0963.
        if (character >= 0xe0a5a200 && character <= 0xe0a5a300) {
          return F_true;
        }

        // Bengali: U+0981 to U+0983.
        if (character >= 0xe0a68100 && character <= 0xe0a68300) {
          return F_true;
        }

        // Bengali: U+09BC.
        if (character == 0xe0a6bc00) {
          return F_true;
        }

        // Bengali: U+09BE to U+09C4.
        if (character >= 0xe0a6be00 && character <= 0xe0a78400) {
          return F_true;
        }

        // Bengali: U+09C7, U+09C8.
        if (character == 0xe0a78700 || character == 0xe0a78800) {
          return F_true;
        }

        // Bengali: U+09CB to U+09CD.
        if (character >= 0xe0a78b00 && character <= 0xe0a78d00) {
          return F_true;
        }

        // Bengali: U+09E2, U+09E3, U+09FE.
        if (character == 0xe0a7a200 || character == 0xe0a7a300 || character == 0xe0a7be00) {
          return F_true;
        }

        // Gurmukhi: U+0A01 to U+0A03.
        if (character >= 0xe0a88100 && character <= 0xe0a88300) {
          return F_true;
        }

        // Gurmukhi: U+0A3C.
        if (character == 0xe0a8bc00) {
          return F_true;
        }

        // Gurmukhi: U+0A3E to U+0A42.
        if (character >= 0xe0a8be00 && character <= 0xe0a98200) {
          return F_true;
        }

        // Gurmukhi: U+0A47 to U+0A48.
        if (character >= 0xe0a98700 && character <= 0xe0a98800) {
          return F_true;
        }

        // Gurmukhi: U+0A4B to U+0A4D.
        if (character >= 0xe0a98b00 && character <= 0xe0a98d00) {
          return F_true;
        }

        // Gurmukhi: U+0A51.
        if (character == 0xe0a99100) {
          return F_true;
        }

        // Gurmukhi: U+0A70, U+0A71, U+0A75.
        if (character == 0xe0a9b000 || character == 0xe0a9b100 || character == 0xe0a9b500) {
          return F_true;
        }

        // Gujarati: U+0A81 to U+0A82.
        if (character >= 0xe0aa8100 && character <= 0xe0aa8200) {
          return F_true;
        }

        // Gujarati: U+0ABC.
        if (character == 0xe0aabc00) {
          return F_true;
        }

        // Gujarati: U+0ABE to U+0AC5.
        if (character >= 0xe0aabe00 && character <= 0xe0ab8500) {
          return F_true;
        }

        // Gujarati: U+0AC7 to U+0AC9.
        if (character >= 0xe0ab8700 && character <= 0xe0ab8900) {
          return F_true;
        }

        // Gujarati: U+0ACB to U+0ACD.
        if (character >= 0xe0ab8b00 && character <= 0xe0ab8d00) {
          return F_true;
        }

        // Gujarati: U+0AE2 to U+0AE3.
        if (character >= 0xe0aba200 && character <= 0xe0aba300) {
          return F_true;
        }

        // Gujarati: U+0AFA to U+0AFF.
        if (character >= 0xe0abba00 && character <= 0xe0abbf00) {
          return F_true;
        }

        // Oriya: U+0B01, U+0B3C, U+0B3F.
        if (character == 0xe0ac8100 || character == 0xe0acbc00 || character == 0xe0acbf00) {
          return F_true;
        }

        // Oriya: U+0B41 to U+0B44.
        if (character >= 0xe0ad8100 && character <= 0xe0ad8400) {
          return F_true;
        }

        // Oriya: U+0B4D, U+0B56, U+0B62, U+0B63.
        if (character == 0xe0ad8d00 || character == 0xe0ad9600 || character == 0xe0ada200 || character == 0xe0ada300) {
          return F_true;
        }

        // Tamil: U+0BC0, U+0BCD.
        if (character == 0xe0af8000 || character == 0xe0af8d00) {
          return F_true;
        }

        // Telugu: U+0C00.
        if (character == 0xe0b08000) {
          return F_true;
        }

        // Telugu: U+0C3E to U+0C40.
        if (character >= 0xe0b0be00 && character <= 0xe0b18000) {
          return F_true;
        }

        // Telugu: U+0C46 to U+0C48.
        if (character >= 0xe0b18600 && character <= 0xe0b18800) {
          return F_true;
        }

        // Telugu: U+0C4A to U+0C4D.
        if (character >= 0xe0b18a00 && character <= 0xe0b18d00) {
          return F_true;
        }

        // Telugu: U+0C55, U+0C56, U+0C62, U+0C63.
        if (character == 0xe0b19500 || character == 0xe0b19600 || character == 0xe0b1a200 || character == 0xe0b1a300) {
          return F_true;
        }

        // Kannada: U+0C81.
        if (character == 0xe0b28100) {
          return F_true;
        }

        // Kannada: U+0CBC to U+0CCD.
        if (character >= 0xe0b2bc00 && character <= 0xe0b38d00) {
          return F_true;
        }

        // Kannada: U+0CE2, U+0CE3.
        if (character == 0xe0b3a200 || character == 0xe0b3a300) {
          return F_true;
        }

        // Malayalam: U+0D01.
        if (character == 0xe0b48100) {
          return F_true;
        }

        // Malayalam: U+0D41 to U+0D44.
        if (character >= 0xe0b58100 && character <= 0xe0b58400) {
          return F_true;
        }

        // Malayalam: U+0D4D, U+0D62, U+0D63.
        if (character == 0xe0b58d00 || character == 0xe0b5a200 || character == 0xe0b5a300) {
          return F_true;
        }

        // Sinhala: U+0DCA.
        if (character == 0xe0b78a00) {
          return F_true;
        }

        // Sinhala: U+0DD2 to U+0DD4.
        if (character >= 0xe0b79200 && character <= 0xe0b79400) {
          return F_true;
        }

        // Sinhala: U+0DD6.
        if (character == 0xe0b79600) {
          return F_true;
        }

        // Thai: U+0E31.
        if (character == 0xe0b8b100) {
          return F_true;
        }

        // Thai: U+0E34 to U+0E3A.
        if (character >= 0xe0b8b400 && character <= 0xe0b8ba00) {
          return F_true;
        }

        // Thai: U+0E47 to U+0E4E.
        if (character >= 0xe0b98700 && character <= 0xe0b98e00) {
          return F_true;
        }

        // Lao: U+0EB1.
        if (character == 0xe0bab100) {
          return F_true;
        }

        // Lao: U+0EB4 to U+0EB9.
        if (character >= 0xe0bab400 && character <= 0xe0bab900) {
          return F_true;
        }

        // Lao: U+0EBB, U+0EBC.
        if (character == 0xe0babb00 || character == 0xe0babc00) {
          return F_true;
        }

        // Tibetan: U+0F18 to U+0F19.
        if (character >= 0xe0bc9800 && character <= 0xe0bc9900) {
          return F_true;
        }

        // Tibetan: U+0F35, U+0F37, U+0F39.
        if (character == 0xe0bcb500 || character == 0xe0bcb700 || character == 0xe0bcb900) {
          return F_true;
        }

        // Tibetan: U+0F71 to U+0F7E.
        if (character >= 0xe0bdb100 && character <= 0xe0bdbe00) {
          return F_true;
        }

        // Tibetan: U+0F80 to U+0F84.
        if (character >= 0xe0be8000 && character <= 0xe0be8400) {
          return F_true;
        }

        // Tibetan: U+0F86 to U+0F87.
        if (character >= 0xe0be8600 && character <= 0xe0be8700) {
          return F_true;
        }

        // Tibetan: U+0F8D to U+0F97.
        if (character >= 0xe0be8d00 && character <= 0xe0be9700) {
          return F_true;
        }

        // Tibetan: U+0F99 to U+0FBC.
        if (character >= 0xe0be9900 && character <= 0xe0bebc00) {
          return F_true;
        }

        // Tibetan: U+0FC6.
        if (character == 0xe0bf8600) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe1) {

        // Myanmar: U+102D to U+1030.
        if (character >= 0xe180ad00 && character <= 0xe180b000) {
          return F_true;
        }

        // Myanmar: U+1039 to U+103A.
        if (character >= 0xe180b900 && character <= 0xe180ba00) {
          return F_true;
        }

        // Myanmar: U+103D to U+103E.
        if (character >= 0xe180bd00 && character <= 0xe180be00) {
          return F_true;
        }

        // Myanmar: U+1058 to U+1059.
        if (character >= 0xe1819800 && character <= 0xe1819900) {
          return F_true;
        }

        // Myanmar: U+105E to U+1060.
        if (character >= 0xe1819e00 && character <= 0xe181a000) {
          return F_true;
        }

        // Myanmar: U+1071 to U+1074.
        if (character >= 0xe181b100 && character <= 0xe181b400) {
          return F_true;
        }

        // Myanmar: U+1082, U+1085, U+1086, U+108D.
        if (character == 0xe1828200 || character == 0xe1828500 || character == 0xe1828600 || character == 0xe1828d00) {
          return F_true;
        }

        // Myanmar: U+109D.
        if (character == 0xe1829d00) {
          return F_true;
        }

        // Ethiopic: U+135D to U+135F.
        if (character >= 0xe18d9d00 && character <= 0xe18d9f00) {
          return F_true;
        }

        // Tagalog: U+1712 to U+1714.
        if (character >= 0xe19c9200 && character <= 0xe19c9400) {
          return F_true;
        }

        // Hanunoo: U+1732 to U+1734.
        if (character >= 0xe19cb200 && character <= 0xe19cb400) {
          return F_true;
        }

        // Buhid: U+1752 to U+1753.
        if (character >= 0xe19d9200 && character <= 0xe19d9300) {
          return F_true;
        }

        // Tagbanwa: U+1772 to U+1773.
        if (character >= 0xe19db200 && character <= 0xe19db300) {
          return F_true;
        }

        // Khmer: U+17B4 to U+17B5.
        if (character >= 0xe19eb400 && character <= 0xe19eb500) {
          return F_true;
        }

        // Khmer: U+17B7 to U+17BD.
        if (character >= 0xe19eb700 && character <= 0xe19ebd00) {
          return F_true;
        }

        // Khmer: U+17C6, U+17C9.
        if (character == 0xe19f8600 || character == 0xe19f8900) {
          return F_true;
        }

        // Khmer: U+17CA to U+17D3.
        if (character >= 0xe19f8a00 && character <= 0xe19f9300) {
          return F_true;
        }

        // Khmer: U+17DD.
        if (character == 0xe19f9d00) {
          return F_true;
        }

        // Mongolian: U+180B to U+180D.
        if (character >= 0xe1a08b00 && character <= 0xe1a08d00) {
          return F_true;
        }

        // Mongolian: U+18A9.
        if (character == 0xe1a2a900) {
          return F_true;
        }

        // Mongolian: U+1920 to U+1922.
        if (character >= 0xe1a4a000 && character <= 0xe1a4a200) {
          return F_true;
        }

        // Limbu: U+1927, U+1928, U+1932.
        if (character == 0xe1a4a700 || character == 0xe1a4a800 || character == 0xe1a4b200) {
          return F_true;
        }

        // Limbu: U+1939 to U+193B.
        if (character >= 0xe1a4b900 && character <= 0xe1a4bb00) {
          return F_true;
        }

        // Buginese: U+1A17 to U+1A18.
        if (character >= 0xe1a89700 && character <= 0xe1a89800) {
          return F_true;
        }

        // Buginese: U+1A1B.
        if (character == 0xe1a89b00) {
          return F_true;
        }

        // Tai Tham: U+1A56.
        if (character == 0xe1a99600) {
          return F_true;
        }

        // Tai Tham: U+1A58 to U+1A5E.
        if (character >= 0xe1a99800 && character <= 0xe1a99e00) {
          return F_true;
        }

        // Tai Tham: U+1A60, U+1A62.
        if (character == 0xe1a9a000 || character == 0xe1a9a200) {
          return F_true;
        }

        // Tai Tham: U+1A65 to U+1A6C.
        if (character >= 0xe1a9a500 && character <= 0xe1a9ac00) {
          return F_true;
        }

        // Tai Tham: U+1A73 to U+1A7C.
        if (character >= 0xe1a9b300 && character <= 0xe1a9bc00) {
          return F_true;
        }

        // Tai Tham: U+1A7F.
        if (character == 0xe1a9bf00) {
          return F_true;
        }

        // Diacritical Marks Extended: U+1AB0 to U+1ACE.
        if (character >= 0xe1aab000 && character <= 0xe1ab8e00) {
          return F_true;
        }

        // Balinese: U+1B00 to U+1B03.
        if (character >= 0xe1ac8000 && character <= 0xe1ac8300) {
          return F_true;
        }

        // Balinese: U+1B34.
        if (character == 0xe1acb400) {
          return F_true;
        }

        // Balinese: U+1B36 to U+1B3A.
        if (character >= 0xe1acb600 && character <= 0xe1acba00) {
          return F_true;
        }

        // Balinese: U+1B3C, U+1B42.
        if (character == 0xe1acbc00 || character == 0xe1ad8200) {
          return F_true;
        }

        // Balinese: U+1B6B to U+1B73.
        if (character >= 0xe1adab00 && character <= 0xe1adb300) {
          return F_true;
        }

        // Sundanese: U+1B80 to U+1B81.
        if (character >= 0xe1ae8000 && character <= 0xe1ae8100) {
          return F_true;
        }

        // Sundanese: U+1BA2 to U+1BA5.
        if (character >= 0xe1aea200 && character <= 0xe1aea500) {
          return F_true;
        }

        // Sundanese: U+1BA8 to U+1BA9.
        if (character >= 0xe1aea800 && character <= 0xe1aea900) {
          return F_true;
        }

        // Sundanese: U+1BAB to U+1BAD.
        if (character >= 0xe1aeab00 && character <= 0xe1aead00) {
          return F_true;
        }

        // Batak: U+1BE6, U+1BE8, U+1BE9, U+1BED.
        if (character == 0xe1afa600 || character == 0xe1afa800 || character == 0xe1afa900 || character == 0xe1afad00) {
          return F_true;
        }

        // Batak: U+1BEF, U+1BF0, U+1BF1.
        if (character == 0xe1afaf00 || character == 0xe1afb000 || character == 0xe1afb100) {
          return F_true;
        }

        // Lepcha: U+1C2C to U+1C33.
        if (character >= 0xe1b0ac00 && character <= 0xe1b0b300) {
          return F_true;
        }

        // Lepcha: U+1C36 to U+1C37.
        if (character >= 0xe1b0b600 && character <= 0xe1b0b700) {
          return F_true;
        }

        // Vedic Extensions: U+1CD4 to U+1CD2.
        if (character >= 0xe1b39400 && character <= 0xe1b39200) {
          return F_true;
        }

        // Vedic Extensions: U+1CD0 to U+1CE0.
        if (character >= 0xe1b39000 && character <= 0xe1b3a000) {
          return F_true;
        }

        // Vedic Extensions: U+1CE2 to U+1CE8.
        if (character >= 0xe1b3a200 && character <= 0xe1b3a800) {
          return F_true;
        }

        // Vedic Extensions: U+1CED, U+1CF4, U+1CF8, U+1CF9.
        if (character == 0xe1b3ad00 || character == 0xe1b3b400 || character == 0xe1b3b800 || character == 0xe1b3b900) {
          return F_true;
        }

        // Vedic Extensions: U+1DC0 to U+1CE8.
        if (character >= 0xe1b78000 && character <= 0xe1b3a800) {
          return F_true;
        }

        // Diacritical Marks Supplement: U+1DC0 to U+1DFF.
        if (character >= 0xe1b78000 && character <= 0xe1b7bf00) {
          return F_true;
        }

        // Diacritical Marks Supplement: U+1DFB to U+1DFF.
        if (character >= 0xe1b7bb00 && character <= 0xe1b7bf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe2) {

        // Diacritical Marks For Symbols: U+20D0 to U+20F0.
        if (character >= 0xe2839000 && character <= 0xe283b000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe3) {

        // CJK Symbols and Punctuation: U+302A to U+302D.
        if (character >= 0xe380aa00 && character <= 0xe380ad00) {
          return F_true;
        }

        // Hiragana: U+3099, U+309A.
        if (character == 0xe3829900 || character == 0xe3829a00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xea) {

        // Cyrillic Extended-B: U+3099.
        if (character == 0xea99af00) {
          return F_true;
        }

        // Cyrillic Extended-B: U+A66F to U+A672.
        if (character >= 0xea99af00 && character <= 0xea99b200) {
          return F_true;
        }

        // Cyrillic Extended-B: U+A674 to U+A69F.
        if (character >= 0xea99b400 && character <= 0xea9a9f00) {
          return F_true;
        }

        // Bamum: U+A6F0 to U+A6F1.
        if (character >= 0xea9bb000 && character <= 0xea9bb100) {
          return F_true;
        }

        // Syloti Nagri: U+A802, U+A806, U+A80B, U+A825.
        if (character == 0xeaa08200 || character == 0xeaa08600 || character == 0xeaa08b00 || character == 0xeaa0a500) {
          return F_true;
        }

        // Syloti Nagri: U+A826.
        if (character == 0xeaa0a600) {
          return F_true;
        }

        // Saurashtra: U+A8C4, U+A8C5.
        if (character == 0xeaa38400 || character == 0xeaa38500) {
          return F_true;
        }

        // Devanagari Extended: U+A8E0 to U+A8F1.
        if (character >= 0xeaa3a000 && character <= 0xeaa3b100) {
          return F_true;
        }

        // Kayah Li: U+A926 to U+A92D.
        if (character >= 0xeaa4a600 && character <= 0xeaa4ad00) {
          return F_true;
        }

        // Rejang: U+A947 to U+A951.
        if (character >= 0xeaa58700 && character <= 0xeaa59100) {
          return F_true;
        }

        // Javanese: U+A980 to U+A982.
        if (character >= 0xeaa68000 && character <= 0xeaa68200) {
          return F_true;
        }

        // Javanese: U+A9B3.
        if (character == 0xeaa6b300) {
          return F_true;
        }

        // Javanese: U+A9B6 to U+A9B9.
        if (character >= 0xeaa6b600 && character <= 0xeaa6b900) {
          return F_true;
        }

        // Javanese: U+A9BC.
        if (character == 0xeaa6bc00) {
          return F_true;
        }

        // Myanmar Extended-B: U+A9E5.
        if (character == 0xeaa7a500) {
          return F_true;
        }

        // Cham: U+AA29 to U+AA2E.
        if (character >= 0xeaa8a900 && character <= 0xeaa8ae00) {
          return F_true;
        }

        // Cham: U+AA31 to U+AA32.
        if (character >= 0xeaa8b100 && character <= 0xeaa8b200) {
          return F_true;
        }

        // Cham: U+AA35 to U+AA36.
        if (character >= 0xeaa8b500 && character <= 0xeaa8b600) {
          return F_true;
        }

        // Cham: U+AA43, U+AA4C.
        if (character == 0xeaa98300 || character == 0xeaa98c00) {
          return F_true;
        }

        // Tai Viet: U+AA7C.
        if (character == 0xeaa9bc00) {
          return F_true;
        }

        // Tai Viet: U+AAB0.
        if (character == 0xeaaab000) {
          return F_true;
        }

        // Tai Viet: U+AAB2 to U+AAB4.
        if (character >= 0xeaaab200 && character <= 0xeaaab400) {
          return F_true;
        }

        // Tai Viet: U+AAB7 to U+AAB8.
        if (character >= 0xeaaab700 && character <= 0xeaaab800) {
          return F_true;
        }

        // Tai Viet: U+AABE to U+AABF.
        if (character >= 0xeaaabe00 && character <= 0xeaaabf00) {
          return F_true;
        }

        // Tai Viet: U+AAC1.
        if (character == 0xeaab8100) {
          return F_true;
        }

        // Meetei Mayek Extensions: U+AAEC, U+AAED, U+AAF6.
        if (character == 0xeaabac00 || character == 0xeaabad00 || character == 0xeaabb600) {
          return F_true;
        }

        // Meetei Mayek: U+ABE5, U+ABE8, U+ABED.
        if (character == 0xeaafa500 || character == 0xeaafa800 || character == 0xeaafad00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xef) {

        // Alphabetic Presentation Forms: U+FB1E.
        if (character == 0xefac9e00) {
          return F_true;
        }

        // Variation Selectors: U+FE00 to U+FE0F.
        if (character >= 0xefb88000 && character <= 0xefb88f00) {
          return F_true;
        }

        // Variation Selectors: U+FE20 to U+FE0F.
        if (character >= 0xefb88000 && character <= 0xefb88f00) {
          return F_true;
        }

        // Combining Half Marks: U+FE20 to U+FE2F.
        if (character >= 0xefb8a000 && character <= 0xefb8af00) {
          return F_true;
        }
      }

      return F_false;
    }

    // Phaistos Disc: U+101FD.
    if (character == 0xf09087bd) {
      return F_true;
    }

    // Coptic Epact Numbers: U+102E0.
    if (character == 0xf0908ba0) {
      return F_true;
    }

    // Old Permic: U+10376 to U+1037A.
    if (character >= 0xf0908db6 && character <= 0xf0908dba) {
      return F_true;
    }

    // Kharoshthi: U+10A01 to U+10A03.
    if (character >= 0xf090a881 && character <= 0xf090a883) {
      return F_true;
    }

    // Kharoshthi: U+10A01, U+10A03, U+10A05, U+10A06.
    if (character == 0xf090a881 || character == 0xf090a883 || character == 0xf090a885 || character == 0xf090a886) {
      return F_true;
    }

    // Kharoshthi: U+10A0C to U+10A0F.
    if (character >= 0xf090a88c && character <= 0xf090a88f) {
      return F_true;
    }

    // Kharoshthi: U+10A38 to U+10A3A.
    if (character >= 0xf090a8b8 && character <= 0xf090a8ba) {
      return F_true;
    }

    // Kharoshthi: U+10A3F.
    if (character == 0xf090a8bf) {
      return F_true;
    }

    // Manichaean: U+10AE5, U+10AE6.
    if (character == 0xf090aba5 || character == 0xf090aba6) {
      return F_true;
    }

    // Brahmi: U+11001.
    if (character == 0xf0918081) {
      return F_true;
    }

    // Brahmi: U+11038 to U+11046.
    if (character >= 0xf09180b8 && character <= 0xf0918186) {
      return F_true;
    }

    // Brahmi .. Kaithi: U+1107F to U+11081.
    if (character >= 0xf09181bf && character <= 0xf0918281) {
      return F_true;
    }

    // Kaithi: U+110B3 to U+110B6.
    if (character >= 0xf09182b3 && character <= 0xf09182b6) {
      return F_true;
    }

    // Kaithi: U+110B9, U+110BA.
    if (character == 0xf09182b9 || character == 0xf09182ba) {
      return F_true;
    }

    // Chakma: U+11100 to U+11102.
    if (character >= 0xf0918480 && character <= 0xf0918482) {
      return F_true;
    }

    // Chakma: U+11127 to U+1112B.
    if (character >= 0xf09184a7 && character <= 0xf09184ab) {
      return F_true;
    }

    // Chakma: U+1112D to U+11134.
    if (character >= 0xf09184ad && character <= 0xf09184b4) {
      return F_true;
    }

    // Mahajani: U+11173.
    if (character == 0xf09185b3) {
      return F_true;
    }

    // Sharada: U+11180 to U+11181.
    if (character >= 0xf0918680 && character <= 0xf0918681) {
      return F_true;
    }

    // Sharada: U+111B6 to U+111BE.
    if (character >= 0xf09186b6 && character <= 0xf09186be) {
      return F_true;
    }

    // Sharada: U+111CA to U+111CC.
    if (character >= 0xf091878a && character <= 0xf091878c) {
      return F_true;
    }

    // Sharada: U+111CA to U+111CC.
    if (character >= 0xf091878a && character <= 0xf091878c) {
      return F_true;
    }

    // Khojki: U+1122F to U+11231.
    if (character >= 0xf09188af && character <= 0xf09188b1) {
      return F_true;
    }

    // Khojki: U+11234, U+11236, U+11237.
    if (character == 0xf09188b4 || character == 0xf09188b6 || character == 0xf09188b7) {
      return F_true;
    }

    // Khudawadi: U+112DF, U+112DF.
    if (character == 0xf0918b9f || character == 0xf0918b9f) {
      return F_true;
    }

    // Khojki: U+112E3 to U+112EA.
    if (character >= 0xf0918ba3 && character <= 0xf0918baa) {
      return F_true;
    }

    // Grantha: U+11300, U+11301, U+1133C, U+11340.
    if (character == 0xf0918c80 || character == 0xf0918c81 || character == 0xf0918cbc || character == 0xf0918d80) {
      return F_true;
    }

    // Grantha: U+11366 to U+1136C.
    if (character >= 0xf0918da6 && character <= 0xf0918dac) {
      return F_true;
    }

    // Grantha: U+11370 to U+11374.
    if (character >= 0xf0918db0 && character <= 0xf0918db4) {
      return F_true;
    }

    // Tirhuta: U+114B3 to U+114B8.
    if (character >= 0xf09192b3 && character <= 0xf09192b8) {
      return F_true;
    }

    // Tirhuta: U+114BA, U+114BF, U+114C0, U+114C2.
    if (character == 0xf09192ba || character == 0xf09192bf || character == 0xf0919380 || character == 0xf0919382) {
      return F_true;
    }

    // Tirhuta: U+114C3.
    if (character == 0xf0919383) {
      return F_true;
    }

    // Siddham: U+115B2 to U+115B5.
    if (character >= 0xf09196b2 && character <= 0xf09196b5) {
      return F_true;
    }

    // Siddham: U+115BC to U+115BD.
    if (character >= 0xf09196bc && character <= 0xf09196bd) {
      return F_true;
    }

    // Siddham: U+115BF, U+115C0, U+115DC, U+115DD.
    if (character == 0xf09196bf || character == 0xf0919780 || character == 0xf091979c || character == 0xf091979d) {
      return F_true;
    }

    // Modi: U+11633 to U+1163A.
    if (character >= 0xf09198b3 && character <= 0xf09198ba) {
      return F_true;
    }

    // Modi: U+1163D to U+11640.
    if (character >= 0xf09198bd && character <= 0xf0919980) {
      return F_true;
    }

    // Takri: U+116AB, U+116AD.
    if (character == 0xf0919aab || character == 0xf0919aad) {
      return F_true;
    }

    // Takri: U+116B0 to U+116B5.
    if (character >= 0xf0919ab0 && character <= 0xf0919ab5) {
      return F_true;
    }

    // Takri: U+116B7.
    if (character == 0xf0919ab7) {
      return F_true;
    }

    // Ahom: U+1171D to U+1171F.
    if (character >= 0xf0919c9d && character <= 0xf0919c9f) {
      return F_true;
    }

    // Ahom: U+11722 to U+11725.
    if (character >= 0xf0919ca2 && character <= 0xf0919ca5) {
      return F_true;
    }

    // Ahom: U+11727 to U+1172B.
    if (character >= 0xf0919ca7 && character <= 0xf0919cab) {
      return F_true;
    }

    // Bassa Vah: U+16AF0 to U+16AF4.
    if (character >= 0xf096abb0 && character <= 0xf096abb4) {
      return F_true;
    }

    // Pahawh Hmong: U+16B30 to U+16B36.
    if (character >= 0xf096acb0 && character <= 0xf096acb6) {
      return F_true;
    }

    // Miao: U+16F8F to U+16F92.
    if (character >= 0xf096be8f && character <= 0xf096be92) {
      return F_true;
    }

    // Duployan: U+1BC9D to U+1BC9E.
    if (character >= 0xf09bb29d && character <= 0xf09bb29e) {
      return F_true;
    }

    // Musical Symbols: U+1D167 to U+1D169.
    if (character >= 0xf09d85a7 && character <= 0xf09d85a9) {
      return F_true;
    }

    // Musical Symbols: U+1D17B to U+1D182.
    if (character >= 0xf09d85bb && character <= 0xf09d8682) {
      return F_true;
    }

    // Musical Symbols: U+1D185 to U+1D18B.
    if (character >= 0xf09d8685 && character <= 0xf09d868b) {
      return F_true;
    }

    // Musical Symbols: U+1D1AA to U+1D1AD.
    if (character >= 0xf09d86aa && character <= 0xf09d86ad) {
      return F_true;
    }

    // Ancient Greek Musical Notation: U+1D242 to U+1D244.
    if (character >= 0xf09d8982 && character <= 0xf09d8984) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA00 to U+1DA36.
    if (character >= 0xf09da880 && character <= 0xf09da8b6) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA3B to U+1DA6C.
    if (character >= 0xf09da8bb && character <= 0xf09da9ac) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA75, U+1DA84.
    if (character == 0xf09da9b5 || character == 0xf09daa84) {
      return F_true;
    }

    // Sutton SignWriting: U+1DA9B to U+1DA9F.
    if (character >= 0xf09daa9b && character <= 0xf09daa9f) {
      return F_true;
    }

    // Sutton SignWriting: U+1DAA1 to U+1DAAF.
    if (character >= 0xf09daaa1 && character <= 0xf09daaaf) {
      return F_true;
    }

    // Mende Kikakui: U+1E8D0 to U+1E8D6.
    if (character >= 0xf09ea390 && character <= 0xf09ea396) {
      return F_true;
    }

    // Variation Selectors Supplement: U+E0100 to U+E01EF.
    if (character >= 0xf3a08480 && character <= 0xf3a087af) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)

#ifdef __cplusplus
} // extern "C"
#endif

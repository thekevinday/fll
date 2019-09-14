#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_character_is_
  f_return_status f_utf_character_is(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return f_true;
  }
#endif // _di_f_utf_character_is_

#ifndef _di_f_utf_character_is_bom_
  f_return_status f_utf_character_is_bom(const f_utf_character character) {
    if (character == f_utf_character_mask_bom) {
      return f_true;
    }

    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return f_false;
  }
#endif // _di_f_utf_character_is_bom_

#ifndef _di_f_utf_character_is_control_
  f_return_status f_utf_character_is_control(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      if (iscntrl(f_macro_utf_character_to_char_1(character))) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (width == 2) {
      // Latin-1 Supplement: U+0080 to U+009F.
      if (character >= 0xc2800000 && character <= 0xc29f0000) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      // @todo these might not be "control characters" and instead be "marking characters" or "combining characters".
      // Special: U+FFF9 to U+FFFB.
      if (character >= 0xefbfb900 && character <= 0xefbfbb00) {
        return f_true;
      }

      return f_false;
    }

    if (width == 4) {
      // Tags: U+E0001 and U+E007F.
      if (character == 0xf3a08081 || character == 0xf3a081bf) {
        return f_true;
      }
    }

    return f_false;
  }
#endif // _di_f_utf_character_is_control_

#ifndef _di_f_utf_character_is_control_picture_
  f_return_status f_utf_character_is_control_picture(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      // There are no control picture characters in ASCII.
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (width != 3) {
      return f_false;
    }

    // Control Pictures: U+2400 to U+2426.
    if (character >= 0xe2908000 && character <= 0xe290a600) {
      return f_true;
    }

    // Specials: U+FFFC to U+FFFD.
    if (character == 0xefbfbc00 || character == 0xefbfbd00) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_utf_character_is_control_picture_

#ifndef _di_f_utf_character_is_fragment_
  f_return_status f_utf_character_is_fragment(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 1) return f_true;

    return f_false;
  }
#endif // _di_f_utf_character_is_fragment_

#ifndef _di_f_utf_character_is_graph_
  f_return_status f_utf_character_is_graph(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      if (isgraph(f_macro_utf_character_to_char_1(character))) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (f_utf_character_is_control(character) == f_true) {
      return f_false;
    }

    if (f_utf_character_is_whitespace(character) == f_true) {
      return f_false;
    }

    // @todo: does this need to check combining and marking characters? or are those still considered graph characters?

    return f_true;
  }
#endif // _di_f_utf_character_is_graph_

#ifndef _di_f_utf_character_is_valid_
  f_return_status f_utf_character_is_valid(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    // reduce the number of checks by grouping checks by first byte.
    uint8_t byte_first = f_macro_utf_character_to_char_1(character);

    if (width == 2) {
      if (byte_first == 0xdc) {
        // Syriac: U+070E.
        if (character == 0xdc8e0000) {
          return f_false;
        }
      }
      else if (byte_first == 0xdd) {
        // Syriac: U+074B, U+074C.
        if (character == 0xdd8b0000 || character == 0xdd8c0000) {
          return f_false;
        }
      }
      else if (byte_first == 0xde) {
        // Thaana: U+07B2 to U+07BF.
        if (character >= 0xdeb20000 && character <= 0xdebf0000) {
          return f_false;
        }
      }
      else if (byte_first == 0xdf) {
        // NKo: U+07FB to U+07FF.
        if (character >= 0xdfbb0000 && character <= 0xdfbf0000) {
          return f_false;
        }
      }
    }
    else if (width == 3) {
      if (byte_first == 0xe0) {
        // Oriya: U+0B50, U+0B55.
        if (character >= 0xe0ad9000 && character <= 0xe0ad9500) {
          return f_false;
        }

        // Oriya: U+0B58, U+0B5B.
        if (character >= 0xe0ad9800 && character <= 0xe0ad9b00) {
          return f_false;
        }

        // Oriya: U+0B78, U+0B7F.
        if (character >= 0xe0adb800 && character <= 0xe0adbf00) {
          return f_false;
        }

        // Oriya: U+0B00, U+0B04, U+0B0D.
        if (character == 0xe0ac8000 || character == 0xe0ac8400 || character == 0xe0ac8d00) {
          return f_false;
        }

        // Oriya: U+0B0E, U+0B11, U+0B29.
        if (character == 0xe0ac8e00 || character == 0xe0ac9100 || character == 0xe0aca900) {
          return f_false;
        }

        // Oriya: U+0B31, U+0B34, U+0B3A.
        if (character == 0xe0acb100 || character == 0xe0acb400 || character == 0xe0acba00) {
          return f_false;
        }

        // Oriya: U+0B3B, U+0B45, U+0B46.
        if (character == 0xe0acbb00 || character == 0xe0ad8500 || character == 0xe0ad8600) {
          return f_false;
        }

        // Oriya: U+0B49, U+0B4A, U+0B4E.
        if (character == 0xe0ad8900 || character == 0xe0ad8A00 || character == 0xe0ad8e00) {
          return f_false;
        }

        // Oriya: U+0B4F, U+0B5E, U+0B64.
        if (character == 0xe0ad8f00 || character == 0xe0ad9e00 || character == 0xe0ada400) {
          return f_false;
        }

        // Oriya: U+0B65.
        if (character == 0xe0ada500) {
          return f_false;
        }

        // Sinhala: U+0D97 to U+0D99.
        if (character >= 0xe0b69700 && character <= 0xe0b69900) {
          return f_false;
        }

        // Sinhala: U+0DC7 to U+0DC9.
        if (character >= 0xe0b78700 && character <= 0xe0b78900) {
          return f_false;
        }

        // Sinhala: U+0DCB to U+0DCE.
        if (character >= 0xe0b78b00 && character <= 0xe0b78e00) {
          return f_false;
        }

        // Sinhala: U+0DE0 to U+0DE5.
        if (character >= 0xe0b7a000 && character <= 0xe0b7a500) {
          return f_false;
        }

        // Sinhala: U+0DF5 to U+0DFF.
        if (character >= 0xe0b7b500 && character <= 0xe0b7bf00) {
          return f_false;
        }

        // Sinhala: U+0D80, U+0D81, U+0D84.
        if (character == 0xe0b68000 || character == 0xe0b68100 || character == 0xe0b68400) {
          return f_false;
        }

        // Sinhala: U+0DB2, U+0DBC, U+0DBE.
        if (character == 0xe0b6b200 || character == 0xe0b6bc00 || character == 0xe0b6be00) {
          return f_false;
        }

        // Sinhala: U+0DBF, U+0DD5, U+0DD7.
        if (character == 0xe0b6bf00 || character == 0xe0b79500 || character == 0xe0b79700) {
          return f_false;
        }

        // Sinhala: U+0DF0, U+0DF1.
        if (character == 0xe0b7b000 || character == 0xe0b7b100) {
          return f_false;
        }

        // Samaritan: U+082E, U+082F, U+083F.
        if (character == 0xe0a0ae00 || character == 0xe0a0af00 || character == 0xe0a0bf00) {
          return f_false;
        }

        // Tamil: U+0B80, U+0B81.
        if (character == 0xe0ae8000 || character == 0xe0ae8100) {
          return f_false;
        }

        // Tamil: U+0B8B to U+0B8D.
        if (character >= 0xe0ae8b00 && character <= 0xe0ae8d00) {
          return f_false;
        }

        // Tamil: U+0B96 to U+0B98.
        if (character >= 0xe0ae9600 && character <= 0xe0ae9800) {
          return f_false;
        }

        // Tamil: U+0BA0 to U+0BA2.
        if (character >= 0xe0aea000 && character <= 0xe0aea200) {
          return f_false;
        }

        // Tamil: U+0BA5 to U+0BA7.
        if (character >= 0xe0aea500 && character <= 0xe0aea700) {
          return f_false;
        }

        // Tamil: U+0BAB to U+0BAD.
        if (character >= 0xe0aeab00 && character <= 0xe0aead00) {
          return f_false;
        }

        // Tamil: U+0BBA to U+0BBD.
        if (character >= 0xe0aeba00 && character <= 0xe0aebd00) {
          return f_false;
        }

        // Tamil: U+0BC3 to U+0BC5.
        if (character >= 0xe0af8300 && character <= 0xe0af8500) {
          return f_false;
        }

        // Tamil: U+0BCE, U+0BCF.
        if (character == 0xe0af8e00 || character == 0xe0af8f00) {
          return f_false;
        }

        // Tamil: U+0BD1 to U+0BD6.
        if (character >= 0xe0af9100 && character <= 0xe0af9600) {
          return f_false;
        }

        // Tamil: U+0BD8 to U+0BE5.
        if (character >= 0xe0af9800 && character <= 0xe0af9800) {
          return f_false;
        }

        // Tamil: U+0BFB to U+0BFF.
        if (character >= 0xe0afbb00 && character <= 0xe0afbf00) {
          return f_false;
        }

        // Tamil: U+0B84, U+0B91, U+0BC9.
        if (character == 0xe0ae8400 || character == 0xe0ae9100 || character == 0xe0af8900) {
          return f_false;
        }

        // Telugu: U+0C3A to U+0C3C.
        if (character >= 0xe0b0ba00 && character <= 0xe0b0bc00) {
          return f_false;
        }

        // Telugu: U+0C4E to U+0C54.
        if (character >= 0xe0b18e00 && character <= 0xe0b19400) {
          return f_false;
        }

        // Telugu: U+0C5B to U+0C5F.
        if (character >= 0xe0b19b00 && character <= 0xe0b19f00) {
          return f_false;
        }

        // Telugu: U+0C64, U+0C65.
        if (character == 0xe0b1a400 || character == 0xe0b1a500) {
          return f_false;
        }

        // Telugu: U+0C70 to U+0C77.
        if (character >= 0xe0b1b000 && character <= 0xe0b1b700) {
          return f_false;
        }

        // Telugu: U+0C04, U+0C0D, U+0C29.
        if (character == 0xe0b08400 || character == 0xe0b08d00 || character == 0xe0b0a900) {
          return f_false;
        }

        // Telugu: U+0C45, U+0C49, U+0C57.
        if (character == 0xe0b18500 || character == 0xe0b18900 || character == 0xe0b19700) {
          return f_false;
        }

        // Thai: U+0E5C to U+0E7F.
        if (character >= 0xe0b99c00 && character <= 0xe0b9bf00) {
          return f_false;
        }

        // Thai: U+0E3B to U+0E3E.
        if (character >= 0xe0b8bb00 && character <= 0xe0b8be00) {
          return f_false;
        }

        // Thai: U+0E00.
        if (character == 0xe0b88000) {
          return f_false;
        }

        // Tibetan: U+0FDB to U+0FFF.
        if (character >= 0xe0bf9b00 && character <= 0xe0bfbf00) {
          return f_false;
        }

        // Tibetan: U+0F6D to U+0F70.
        if (character >= 0xe0bdad00 && character <= 0xe0bdb000) {
          return f_false;
        }

        // Tibetan: U+0F48, U+0F98, U+0FBD, U+0FCD
        if (character == 0xe0bd8800 || character == 0xe0be9800 || character == 0xe0bebd00 || character == 0xe0bf8d) {
          return f_false;
        }
      }
      else if (byte_first == 0xe1) {
        // New Tai Lue: U+19AC to U+19AF.
        if (character >= 0xe1a6ac00 && character <= 0xe1a6af00) {
          return f_false;
        }

        // New Tai Lue: U+19CA to U+19CF.
        if (character >= 0xe1a78a00 && character <= 0xe1a78f00) {
          return f_false;
        }

        // New Tai Lue: U+19DB to U+19DD.
        if (character >= 0xe1a79b00 && character <= 0xe1a79d00) {
          return f_false;
        }

        // Ogham: U+169D to U+169F.
        if (character >= 0xe19a9d00 && character <= 0xe19a9f00) {
          return f_false;
        }

        // Runic: U+16F9 to U+16FF.
        if (character >= 0xe19bb900 && character <= 0xe19bbf00) {
          return f_false;
        }

        // Sundanese Supplement: U+1CC8 to U+1CCF.
        if (character >= 0xe1b38800 && character <= 0xe1b38f00) {
          return f_false;
        }
        // Tagalog: U+1715 to U+171f.
        if (character >= 0xe19c9500 && character <= 0xe19c9f00) {
          return f_false;
        }

        // Tagalog: U+170D
        if (character == 0xe19c8d00) {
          return f_false;
        }

        // Tagbanwa: U+1774 to U+177f.
        if (character >= 0xe19db400 && character <= 0xe19dbf00) {
          return f_false;
        }

        // Tagbanwa: U+176D, U+1771
        if (character == 0xe19dad00 || character == 0xe19db100) {
          return f_false;
        }

        // Tai Lee: U+196E, U+196F.
        if (character == 0xe1a5ae00 || character == 0xe1a5ef00) {
          return f_false;
        }

        // Tai Lee: U+1975 to U+197F.
        if (character >= 0xe1a5b500 && character <= 0xe1a5bf00) {
          return f_false;
        }

        // Tai Tham: U+1A7D to U+1A7E.
        if (character >= 0xe1a9bd00 && character <= 0xe1a9be00) {
          return f_false;
        }

        // Tai Tham: U+1A8A to U+1A8F.
        if (character >= 0xe1aa8a00 && character <= 0xe1aa8f00) {
          return f_false;
        }

        // Tai Tham: U+1A9A to U+1A9F.
        if (character >= 0xe1aa9a00 && character <= 0xe1aa9f00) {
          return f_false;
        }

        // Tai Tham: U+1AAE to U+1AAF.
        if (character >= 0xe1aaae00 && character <= 0xe1aaaf00) {
          return f_false;
        }

        // Tai Tham: U+1A5F.
        if (character == 0xe1a99f00) {
          return f_false;
        }

        // Unified Canadian Aboriginal Syllabics Extended: U+18F6 to U+18FF.
        if (character >= 0xe1a3b600 && character <= 0xe1a3bf00) {
          return f_false;
        }

        // Vedic Extensions: U+1CF7 and U+1CFA to U+1CFF.
        if (character == 0xe1b3b700 || character >= 0xe1b3ba00 && character <= 0xe1b3bf00) {
          return f_false;
        }
      }
      else if (byte_first == 0xe2) {
        // Miscellaneous Symbols and Arrows: U+2BBA to U+2BBC.
        if (character >= 0xe2aeba00 && character <= 0xe2aebc00) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2BD2 to U+2BEB.
        if (character >= 0xe2af9200 && character <= 0xe2afab00) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2BF0 to U+2BFF.
        if (character >= 0xe2afb000 && character <= 0xe2afbf00) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2B74, U+2B75, U+2B96.
        if (character == 0xe2adb400 || character == 0xe2adb500 || character == 0xe2ae9600) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2B97, U+2BC9.
        if (character == 0xe2ae9700 || character == 0xe2af8900) {
          return f_false;
        }

        // Miscellaneous Technical: U+23FF.
        if (character == 0xe28fbf00) {
          return f_false;
        }

        // Number Forms: U+218C to U+218F.
        if (character >= 0xe2868c00 && character <= 0xe2868f00) {
          return f_false;
        }

        // Optical Character Recognition: U+244B to U+245F.
        if (character >= 0xe2918b00 && character <= 0xe2919f00) {
          return f_false;
        }

        // Superscripts and Subscripts: U+2072, U+2073, U+208F.
        if (character == 0xe281b200 || character == 0xe281b300 || character == 0xe2828f00) {
          return f_false;
        }

        // Superscripts and Subscripts: U+209D to U+209F.
        if (character >= 0xe2829d00 && character <= 0xe2829f00) {
          return f_false;
        }

        // Supplemental Punctuation: U+2E45 to U+2E7F.
        if (character >= 0xe2b98500 && character <= 0xe2b9bf00) {
          return f_false;
        }

        // Tifinagh: U+2D68 to U+2D6E.
        if (character >= 0xe2b5a800 && character <= 0xe2b5ae00) {
          return f_false;
        }

        // Tifinagh: U+2D71 to U+2D7E.
        if (character >= 0xe2b5b100 && character <= 0xe2b5be00) {
          return f_false;
        }
      }
      else if (byte_first == 0xea) {
        // Meetei Mayek: U+ABFA to U+ABFF.
        if (character >= 0xeaafba00 && character <= 0xeaafbf00) {
          return f_false;
        }

        // Meetei Mayek: U+ABEE, U+ABEF.
        if (character == 0xeaafae00 || character == 0xeaafaf00) {
          return f_false;
        }

        // Meetei Mayek Extensions: U+AAF7 to U+AAFF.
        if (character >= 0xeaabb700 && character <= 0xeaabbf00) {
          return f_false;
        }

        // Myanmar Extended-B: U+A9FF.
        if (character == 0xeaa7bf00) {
          return f_false;
        }

        // Phags-pa: U+A878, U+A87F.
        if (character >= 0xeaa1b800 && character <= 0xeaa1bf00) {
          return f_false;
        }

        // Rejang: U+A954 to U+A95E.
        if (character >= 0xeaa59400 && character <= 0xeaa59e00) {
          return f_false;
        }

        // Syloti Nagri: U+A82C to U+A82F.
        if (character >= 0xeaa0ac00 && character <= 0xeaa0af00) {
          return f_false;
        }

        // Saurashtra: U+A8C6 to U+A8CD.
        if (character >= 0xeaa38600 && character <= 0xeaa38d00) {
          return f_false;
        }

        // Saurashtra: U+A8DA to U+A8DF.
        if (character >= 0xeaa39a00 && character <= 0xeaa39f00) {
          return f_false;
        }

        // Tai Viet: U+AAC3 to U+AADA.
        if (character >= 0xeaab8300 && character <= 0xeaab9a00) {
          return f_false;
        }

        // Vai: U+A62C to U+A63F.
        if (character >= 0xea98ac00 && character <= 0xea98bf00) {
          return f_false;
        }

        // Yi Radicals: U+A4C7 to U+A4CF.
        if (character >= 0xea938700 && character <= 0xea938f00) {
          return f_false;
        }

        // Yi Syllables: U+A48D to U+A48F.
        if (character >= 0xea928d00 && character <= 0xea928f00) {
          return f_false;
        }
      }
      else if (byte_first == 0xee) {
        // consider all private use codes as valid, U+E000 to U+F8FF.
        if (character >= 0xee808000 && character <= 0xefa3bf00) {
          return f_true;
        }
      }
      else if (byte_first == 0xef) {
        // consider all private use codes as valid, U+E000 to U+F8FF.
        if (character >= 0xee808000 && character <= 0xefa3bf00) {
          return f_true;
        }

        // Small Form Variants: U+FE6C to U+FE6F.
        if (character >= 0xefb9ac00 && character <= 0xefb9af00) {
          return f_false;
        }

        // Small Form Variants: U+FE53, U+FE67.
        if (character == 0xefb99300 || character == 0xefb9a700) {
          return f_false;
        }

        // Vertical Forms: U+FE10 to U+FE1F.
        if (character >= 0xefb89000 && character <= 0xefb89f00) {
          return f_false;
        }

        // Specials: U+FFF0 to U+FFF8.
        if (character >= 0xefbfb000 && character <= 0xefbfb800) {
          return f_false;
        }

        // Specials: U+FFFE to U+FFFF.
        if (character >= 0xefbfbe00 && character <= 0xefbfbf00) {
          return f_false;
        }
      }
    }
    else if (width == 4) {
      // reduce the number of checks by grouping checks by second byte.
      uint8_t byte_second = f_macro_utf_character_to_char_2(character);

      if (byte_first == 0xf0) {
        if (byte_second == 0x90) {
          // Manichaean: U+10AE7 to U+10AEA.
          if (character >= 0xf090aba7 && character <= 0xf090abaa) {
            return f_false;
          }

          // Manichaean: U+10AF7 to U+10AFF.
          if (character >= 0xf090abb7 && character <= 0xf090abbf) {
            return f_false;
          }

          // Meroitic Cursive: U+109B8 to U+109BB.
          if (character >= 0xf090a6b8 && character <= 0xf090a6bb) {
            return f_false;
          }

          // Meroitic Cursive: U+109D0, U+109D1.
          if (character == 0xf090a790 || character == 0xf090a791) {
            return f_false;
          }

          // Nabataean: U+1089F to U+108A6.
          if (character >= 0xf090a29f && character <= 0xf090a2a6) {
            return f_false;
          }

          // Old Hungarian: U+10CB3 to U+10CBF.
          if (character >= 0xf090b2b3 && character <= 0xf090b2bf) {
            return f_false;
          }

          // Old Hungarian: U+10CF3 to U+10CF9.
          if (character >= 0xf090b3b3 && character <= 0xf090b3b9) {
            return f_false;
          }

          // Old Italic: U+10324 to U+1032F.
          if (character >= 0xf0908ca4 && character <= 0xf0908caf) {
            return f_false;
          }

          // Old Permic: U+1037B to U+1037F.
          if (character >= 0xf0908dbb && character <= 0xf0908dbf) {
            return f_false;
          }

          // Old Persian: U+103C4 to U+103C7.
          if (character >= 0xf0908f84 && character <= 0xf0908f87) {
            return f_false;
          }

          // Old Persian: U+103D6 to U+103DF.
          if (character >= 0xf0908f96 && character <= 0xf0908f9f) {
            return f_false;
          }

          // Old Turkic: U+10C49 to U+10C4F.
          if (character >= 0xf090b189 && character <= 0xf090b18f) {
            return f_false;
          }

          // Osage: U+104D4 to U+104D7.
          if (character >= 0xf0909394 && character <= 0xf0909397) {
            return f_false;
          }

          // Osage: U+104FC to U+104FF.
          if (character >= 0xf09093bc && character <= 0xf09093bf) {
            return f_false;
          }

          // Osmanya: U+104AA to U+104AF.
          if (character >= 0xf09092aa && character <= 0xf09092af) {
            return f_false;
          }

          // Osmanya: U+1049E to U+1049F.
          if (character == 0xf090929e || character == 0xf090929f) {
            return f_false;
          }

          // Phaistos Disc: U+101FE, U+101FF.
          if (character == 0xf09087be || character == 0xf09087bf) {
            return f_false;
          }

          // Phoenician: U+1091C to U+1091E.
          if (character >= 0xf090a49c && character <= 0xf090a49e) {
            return f_false;
          }

          // Psalter Pahlavi: U+10B92 to U+10B98.
          if (character >= 0xf090ae92 && character <= 0xf090ae98) {
            return f_false;
          }

          // Psalter Pahlavi: U+10B9D to U+10BA8.
          if (character >= 0xf090ae9d && character <= 0xf090aea8) {
            return f_false;
          }

          // Rumi Numeral Symbols: U+10E7F.
          if (character == 0xf090b9bf) {
            return f_false;
          }

          // Ugaritic: U+1039E.
          if (character == 0xf0908e9e) {
            return f_false;
          }
        }
        else if (byte_second == 0x91) {
          // Marchen: U+11CB7 to U+11CBF.
          if (character >= 0xf091b2b7 && character <= 0xf091b2bf) {
            return f_false;
          }

          // Marchen: U+11C90, U+11C91, U+11CA8.
          if (character == 0xf091b290 || character == 0xf091b291 || character == 0xf091b2a8) {
            return f_false;
          }

          // Modi: U+11645 to U+1164F.
          if (character >= 0xf0919985 && character <= 0xf091998f) {
            return f_false;
          }

          // Modi: U+1165A to U+1165F.
          if (character >= 0xf091999a && character <= 0xf091999f) {
            return f_false;
          }

          // Mongolian Supplement: U+1166D to U+1167F.
          if (character >= 0xf09199ad && character <= 0xf09199bf) {
            return f_false;
          }

          // Multani: U+112AA to U+112AF.
          if (character >= 0xf0918aaa && character <= 0xf0918aaf) {
            return f_false;
          }

          // Multani: U+11287, U+11289, U+1128E, U+1129E.
          if (character == 0xf0918a87 || character == 0xf0918a89 || character == 0xf0918a8e || character == 0xf0918a9e) {
            return f_false;
          }

          // Newa: U+1145E to U+1147F.
          if (character >= 0xf091919e && character <= 0xf09191bf) {
            return f_false;
          }

          // Newa: U+1145A, U+1145C.
          if (character == 0xf091919a || character == 0xf091919c) {
            return f_false;
          }

          // Pau Cin Hau: U+11AF9, U+11AFF.
          if (character >= 0xf091abbf && character <= 0xf091abbf) {
            return f_false;
          }

          // Sharada: U+111CE, U+111CF.
          if (character == 0xf091878e || character == 0xf091878f) {
            return f_false;
          }

          // Siddham: U+115DE to U+115FF.
          if (character >= 0xf091979e && character <= 0xf09197bf) {
            return f_false;
          }

          // Siddham: U+115B6, U+115B7.
          if (character == 0xf09196b6 || character == 0xf09196b7) {
            return f_false;
          }

          // Sinhala Archaic Numbers: U+111F5 to U+111FF.
          if (character >= 0xf09187b5 && character <= 0xf09187bf) {
            return f_false;
          }

          // Sinhala Archaic Numbers: U+1F93F.
          if (character == 0xf09187a0) {
            return f_false;
          }

          // Sora Sompeng: U+110E9 to U+110EF.
          if (character >= 0xf09183a9 && character <= 0xf09183af) {
            return f_false;
          }

          // Sora Sompeng: U+110FA to U+110FF.
          if (character >= 0xf09183ba && character <= 0xf09183bf) {
            return f_false;
          }

          // Takri: U+116B8 to U+116BF.
          if (character >= 0xf0919ab8 && character <= 0xf0919abf) {
            return f_false;
          }

          // Takri: U+116CA to U+116CF.
          if (character >= 0xf0919b8a && character <= 0xf0919b8f) {
            return f_false;
          }

          // Tirhuta: U+114C8 to U+114CF.
          if (character >= 0xf0919388 && character <= 0xf091938f) {
            return f_false;
          }

          // Tirhuta: U+114DA to U+114DF.
          if (character >= 0xf091939a && character <= 0xf091939f) {
            return f_false;
          }

          // Warang Citi: U+118F3 to U+118FE.
          if (character >= 0xf091a3b3 && character <= 0xf091a3be) {
            return f_false;
          }
        }
        else if (byte_second == 0x96) {
          // Miao: U+16F45 to U+16F4F.
          if (character >= 0xf096bd85 && character <= 0xf096bd8f) {
            return f_false;
          }

          // Miao: U+16F7F to U+16F8E.
          if (character >= 0xf096bdbf && character <= 0xf096be8e) {
            return f_false;
          }

          // Mro: U+16A6A to U+16A6D.
          if (character >= 0xf096a9aa && character <= 0xf096a9ad) {
            return f_false;
          }

          // Mro: U+16A5F.
          if (character == 0xf096a99f) {
            return f_false;
          }

          // Pahawh Hmong: U+16B46 to U+16B4F.
          if (character >= 0xf096ad86 && character <= 0xf096ad8f) {
            return f_false;
          }

          // Pahawh Hmong: U+16B78 to U+16B7C.
          if (character >= 0xf096adb8 && character <= 0xf096adbc) {
            return f_false;
          }

          // Pahawh Hmong: U+16B5A, U+16B62.
          if (character == 0xf096ad9a || character == 0xf096ada2) {
            return f_false;
          }
        }
        else if (byte_second == 0x9b) {
          // Shorthand Format Controls: U+1BCA4 to U+1BCAF.
          if (character >= 0xf09bb2a4 && character <= 0xf09bb2af) {
            return f_false;
          }
        }
        else if (byte_second == 0x9d) {
          // Mathematical Alphanumeric Symbols: U+1D547 to U+1D549.
          if (character >= 0xf09d9587 && character <= 0xf09d9589) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D455, U+1D49D, U+1D4A0, U+1D4A1.
          if (character == 0xf09d9195 || character == 0xf09d929d || character == 0xf09d92a0 || character == 0xf09d92a1) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D4A3, U+1D4A4, U+1D4A7, U+1D4A8.
          if (character == 0xf09d92a3 || character == 0xf09d92a4 || character == 0xf09d92a7 || character == 0xf09d92a8) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D4AD, U+1D4BA, U+1D4BC, U+1D4C4.
          if (character == 0xf09d92ad || character == 0xf09d92ba || character == 0xf09d92bc || character == 0xf09d9384) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D506, U+1D50B, U+1D50C, U+1D515.
          if (character == 0xf09d9486 || character == 0xf09d948b || character == 0xf09d948c || character == 0xf09d9495) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D51D, U+1D53A, U+1D53F, U+1D545.
          if (character == 0xf09d949d || character == 0xf09d94ba || character == 0xf09d94bf || character == 0xf09d9585) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D551, U+1D6A6, U+1D7CC, U+1D7CD.
          if (character == 0xf09d9591 || character == 0xf09d9aa6 || character == 0xf09d9aa7 || character == 0xf09d9f8c || character == 0xf09d9f8d) {
            return f_false;
          }

          // Musical Symbols: U+1D1E9 to U+1D1FF.
          if (character >= 0xf09d87a9 && character <= 0xf09d87bf) {
            return f_false;
          }

          // Musical Symbols: U+1D127 to U+1D128.
          if (character == 0xf09d84a7 || character == 0xf09d84a8) {
            return f_false;
          }

          // Sutton SignWriting: U+1DA8C to U+1DA9A.
          if (character >= 0xf09daa8c && character <= 0xf09daa9a) {
            return f_false;
          }

          // Tai Xuan Jing Symbols: U+1D357 to U+1D35F.
          if (character >= 0xf09d8d97 && character <= 0xf09d8d9f) {
            return f_false;
          }
        }
        else if (byte_second == 0x9e) {
          // Mende Kikakui: U+1E8D7 to U+1E8DF.
          if (character >= 0xf09ea397 && character <= 0xf09ea39f) {
            return f_false;
          }

          // Mende Kikakui: U+1E8C5, U+1E8C6.
          if (character == 0xf09ea385 || character == 0xf09ea386) {
            return f_false;
          }
        }
        else if (byte_second == 0x9f) {
          // Playing Cards: U+1F0AF, U+1F0C0, U+1F0D0.
          if (character == 0xf09f82af || character == 0xf09f8380 || character == 0xf09f8390) {
            return f_false;
          }

          // Playing Cards: U+1F0F6 to U+1F0FF.
          if (character >= 0xf09f83b6 && character <= 0xf09f83bf) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F80C to U+1F80F.
          if (character >= 0xf09fa08c && character <= 0xf09fa08f) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F848 to U+1F84F.
          if (character >= 0xf09fa188 && character <= 0xf09fa18f) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F85A to U+1F85F.
          if (character >= 0xf09fa19a && character <= 0xf09fa19f) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F8AE to U+1F8FF.
          if (character >= 0xf09fa2ae && character <= 0xf09fa3bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F900 to U+1F90F.
          if (character >= 0xf09fa480 && character <= 0xf09fa48f) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F928 to U+1F92F.
          if (character >= 0xf09fa4a8 && character <= 0xf09fa4af) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F94C to U+1F94F.
          if (character >= 0xf09fa58c && character <= 0xf09fa58f) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F960 to U+1F97F.
          if (character >= 0xf09fa5a0 && character <= 0xf09fa5bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F992 to U+1F9BF.
          if (character >= 0xf09fa692 && character <= 0xf09fa6bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F9C1 to U+1F9FF.
          if (character >= 0xf09fa781 && character <= 0xf09fa7bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F91F, U+1F931, U+1F932.
          if (character == 0xf09fa49f || character == 0xf09fa4b1 || character == 0xf09fa4b2) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F93F, U+1F95F.
          if (character == 0xf09fa4bf || character == 0xf09fa59f) {
            return f_false;
          }

          // Transport and Map Symbols: U+1F6D3 to U+1F6DF.
          if (character >= 0xf09f9b93 && character <= 0xf09f9b9f) {
            return f_false;
          }

          // Transport and Map Symbols: U+1F6ED to U+1F6EF.
          if (character >= 0xf09f9bad && character <= 0xf09f9baf) {
            return f_false;
          }

          // Transport and Map Symbols: U+1F6F7 to U+1F6FF.
          if (character >= 0xf09f9bb7 && character <= 0xf09f9bbf) {
            return f_false;
          }
        }
        else if (byte_second == 0x98) {
          // Tangut: U+187ED to U+187FF.
          if (character >= 0xf0989fad && character <= 0xf0989fbf) {
            return f_false;
          }

          // Tangut Components: U+18AF3 to U+18AFF.
          if (character >= 0xf098abb3 && character <= 0xf098abbf) {
            return f_false;
          }
        }
      }
      else if (byte_first == 0xf3) {
        // Consider all private use codes as valid, U+F0000 to U+FFFFF.
        if (character >= 0xf3b08080 && character <= 0xf3bfbfbf) {
          return f_true;
        }

        // Tags: U+E0000, U+E0002 to U+E001F.
        if (character == 0xf3a08080 || character >= 0xf3a08082 && character <= 0xf3a081bf) {
          return f_false;
        }
      }
      else if (byte_first == 0xf4) {
        // Consider all private use codes as valid, U+100000 to U+10FFFF.
        if (character >= 0xf4808080 && character <= 0xf48fbfbf) {
          return f_true;
        }
      }
      else {
        // Unicode (and therefore UTF-8) does not support representing any character greater than this (U+10FFFF).
        if (character > 0xf48fbfbf) {
          return f_false;
        }
      }
    }

    return f_true;
  }
#endif // _di_f_utf_character_is_value_

#ifndef _di_f_utf_character_is_whitespace_
  f_return_status f_utf_character_is_whitespace(const f_utf_character character) {
    unsigned short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      if (isspace(f_macro_utf_character_to_char_1(character))) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    // Latin-1 Supplement: U+00A0, U+00AD.
    if (character == 0xc2a00000 || character == 0xc2ad0000) {
      return f_true;
    }

    // Tags: U+E0020.
    if (character == 0xf3a08080) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_utf_character_is_whitespace_

#ifndef _di_f_utf_character_to_char_
  f_return_status f_utf_character_to_char(const f_utf_character utf_character, f_string *character, unsigned short *max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (utf_character == 0) return f_status_set_error(f_invalid_parameter);
      if (max_width == 0 && *character != 0) return f_status_set_error(f_invalid_parameter);
      if (max_width != 0 && *character == 0) return f_status_set_error(f_invalid_parameter);
      if (max_width != 0 && *max_width > 4) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    unsigned short width = f_macro_utf_character_width_is(utf_character);

    if (max_width == 0) {
      f_macro_string_new(status, *character, width);

      if (f_status_is_error(status)) return status;

      width = 1;
      *max_width = 1;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }
    else if (width > *max_width) {
      return f_status_set_error(f_failure);
    }

    *max_width = width;

    if (f_utf_is_big_endian()) {
      memcpy(*character, &utf_character, sizeof(int8_t) * width);
    }
    else {
      uint32_t utf = 0;

      if (width == 1) {
        utf = f_macro_utf_character_to_char_1(utf_character) << 24;
      }
      else if (width == 2) {
        utf = (f_macro_utf_character_to_char_2(utf_character) << 24) | (f_macro_utf_character_to_char_1(utf_character) << 16);
      }
      else if (width == 3) {
        utf = (f_macro_utf_character_to_char_3(utf_character) << 24) | (f_macro_utf_character_to_char_2(utf_character) << 16) | (f_macro_utf_character_to_char_1(utf_character) << 8);
      }
      else if (width == 4) {
        utf = (f_macro_utf_character_to_char_4(utf_character) << 24) | (f_macro_utf_character_to_char_3(utf_character) << 16) | (f_macro_utf_character_to_char_2(utf_character) << 8) | f_macro_utf_character_to_char_1(utf_character);
      }

      memcpy(*character, &utf, sizeof(int8_t) * width);
    }

    return f_none;
  }
#endif // _di_f_utf_character_to_char_

#ifndef _di_f_utf_is_big_endian_
  f_return_status f_utf_is_big_endian() {
    uint16_t test_int = (0x01 << 8) | 0x02;
    int8_t test_char[2] = {0x01, 0x02};

    if (!memcmp(&test_int, test_char, 2)) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_utf_is_big_endian_

#ifndef _di_f_utf_is_
  f_return_status f_utf_is(const f_string character, const unsigned short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    unsigned short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    return f_true;
  }
#endif // _di_f_utf_is_

#ifndef _di_f_utf_is_bom_
  f_return_status f_utf_is_bom(const f_string character, const unsigned short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    unsigned short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_maybe);
    }

    if (width == 3) {
      if (!memcmp(character, f_utf_bom, width)) {
        return f_true;
      }
    }

    return f_false;
  }
#endif // _di_f_utf_is_bom_

#ifndef _di_f_utf_is_control_
  f_return_status f_utf_is_control(const f_string character, const unsigned short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (iscntrl(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;
    f_status status = 0;

    status = f_utf_char_to_character(character, max_width, &character_utf);

    if (status != f_none) return status;

    return f_utf_character_is_control(character_utf);
  }
#endif // _di_f_utf_is_control_

#ifndef _di_f_utf_is_control_picture_
  f_return_status f_utf_is_control_picture(const f_string character, const unsigned short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    // There are not ASCII control pictures.
    if (width == 0) {
      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;
    f_status status = 0;

    status = f_utf_char_to_character(character, max_width, &character_utf);

    if (status != f_none) return status;

    return f_utf_character_is_control_picture(character_utf);
  }
#endif // _di_f_utf_is_control_picture_

#ifndef _di_f_utf_is_graph_
  f_return_status f_utf_is_graph(const f_string character, const unsigned short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (isgraph(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;
    f_status status = 0;

    status = f_utf_char_to_character(character, max_width, &character_utf);

    if (status != f_none) return status;

    return f_utf_character_is_graph(character_utf);
  }
#endif // _di_f_utf_is_graph_

#ifndef _di_f_utf_is_whitespace_
  f_return_status f_utf_is_whitespace(const f_string character, const unsigned short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    unsigned short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      if (isspace(*character)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    f_utf_character character_utf = 0;
    f_status status = 0;

    status = f_utf_char_to_character(character, max_width, &character_utf);

    if (status != f_none) return status;

    return f_utf_character_is_whitespace(character_utf);
  }
#endif // _di_f_utf_is_whitespace_

#ifndef _di_f_utf_char_to_character_
  f_return_status f_utf_char_to_character(const f_string character, const unsigned short max_width, f_utf_character *character_utf) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
      if (character_utf == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    unsigned short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      *character_utf = f_macro_utf_character_from_char_1(character[0]);
      return f_none;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_failure);
    }

    *character_utf = 0;
    *character_utf |= f_macro_utf_character_to_char_1(character[0]);

    if (width < 2) {
      return f_none;
    }

    *character_utf |= f_macro_utf_character_to_char_2(character[1]);

    if (width == 2) {
      return f_none;
    }

    *character_utf |= f_macro_utf_character_to_char_3(character[2]);

    if (width == 3) {
      return f_none;
    }

    *character_utf |= f_macro_utf_character_to_char_4(character[3]);

    return f_none;
  }
#endif // _di_f_utf_char_to_character_

#ifdef __cplusplus
} // extern "C"
#endif

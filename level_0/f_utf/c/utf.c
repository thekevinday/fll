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
      uint8_t byte = f_macro_utf_character_to_char_2(character);

      if (byte_first == 0xcd) {
        // Greek and Coptic: U+0378, U+0379.
        if (byte == 0xb8 || byte == 0xb9) {
          return f_false;
        }
      }
      else if (byte_first == 0xce) {
        // Greek and Coptic: U+0380 to U+0383.
        if (byte >= 0x80 && byte <= 0x83) {
          return f_false;
        }

        // Greek and Coptic: U+038B, U+038D, U+03A2.
        if (byte == 0x8b || byte == 0x8d || byte == 0xa2) {
          return f_false;
        }
      }
      else if (byte_first == 0xd4) {
        // Armenian: U+0530.
        if (byte == 0xb0) {
          return f_false;
        }
      }
      else if (byte_first == 0xd5) {
        // Armenian: U+0557, U+0558, U+0560, U+0588.
        if (byte == 0x97 || byte == 0x98 || byte == 0xa0 || byte == 0x88) {
          return f_false;
        }
      }
      else if (byte_first == 0xd6) {
        // Armenian: U+058B, U+058C.
        if (byte == 0x8b || byte == 0x8c) {
          return f_false;
        }

        // Hebrew: U+0590.
        if (byte == 0x90) {
          return f_false;
        }
      }
      else if (byte_first == 0xd7) {
        // Hebrew: U+05C8 to U+05CF.
        if (byte >= 0x88 && byte <= 0x8F) {
          return f_false;
        }

        // Hebrew: U+05EB to U+05EF.
        if (byte >= 0xab && byte <= 0xaf) {
          return f_false;
        }

        // Hebrew: U+05F5 to U+05FF.
        if (byte >= 0xb5 && byte <= 0xbf) {
          return f_false;
        }
      }
      else if (byte_first == 0xdc) {
        // Syriac: U+070E.
        if (byte == 0x8e) {
          return f_false;
        }
      }
      else if (byte_first == 0xdd) {
        // Syriac: U+074B, U+074C.
        if (byte == 0x8b || byte == 0x8c) {
          return f_false;
        }
      }
      else if (byte_first == 0xde) {
        // Thaana: U+07B2 to U+07BF.
        if (byte >= 0xb2 && byte <= 0xbf) {
          return f_false;
        }
      }
      else if (byte_first == 0xdf) {
        // NKo: U+07FB to U+07FF.
        if (byte >= 0xbb && byte <= 0xbf) {
          return f_false;
        }
      }
    }
    else if (width == 3) {
      // @todo: investigate potential performance gains by storing and compararing against the lower 16 bits on the idea that the register size needed for comparrison will be smaller and therefore a faster comparison (16-bit vs 32-bit).
      if (byte_first == 0xe0) {
        // Bengali: U+09B3 to U+09B5.
        if (character >= 0xe0a6b300 && character <= 0xe0a6b500) {
          return f_false;
        }

        // Bengali: U+09CF to U+09D6.
        if (character >= 0xe0a78f00 && character <= 0xe0a79600) {
          return f_false;
        }

        // Bengali: U+09D8 to U+09DB.
        if (character >= 0xe0a79800 && character <= 0xe0a79b00) {
          return f_false;
        }

        // Bengali: U+09FC to U+09FF.
        if (character >= 0xe0a7bc00 && character <= 0xe0a7bf00) {
          return f_false;
        }

        // Bengali: U+0984, U+098D, U+098E, U+0991.
        if (character == 0xe0a68400 || character == 0xe0a68d00 || character == 0xe0a68e00 || character == 0xe0a69100) {
          return f_false;
        }

        // Bengali: U+0992, U+09A9, U+09B1, U+09BA.
        if (character == 0xe0a69200 || character == 0xe0a6a900 || character == 0xe0a6b100 || character == 0xe0a6ba00) {
          return f_false;
        }

        // Bengali: U+09BB, U+09C5, U+09C6, U+09C9.
        if (character == 0xe0a6bb00 || character == 0xe0a78500 || character == 0xe0a78600 || character == 0xe0a78900) {
          return f_false;
        }

        // Bengali: U+09CA, U+09DE, U+09E4, U+09E5.
        if (character == 0xe0a78a00 || character == 0xe0a79e00 || character == 0xe0a7a400 || character == 0xe0a7a500) {
          return f_false;
        }

        // Gujarati: U+0AD1 to U+0ADF.
        if (character >= 0xe0ab9100 && character <= 0xe0ab9400) {
          return f_false;
        }

        // Gujarati: U+0AF2 to U+0AF8.
        if (character >= 0xe0abb200 && character <= 0xe0abb800) {
          return f_false;
        }

        // Gujarati: U+0AFA to U+0AFF.
        if (character >= 0xe0abba00 && character <= 0xe0abbf00) {
          return f_false;
        }

        // Gujarati: U+0A80, U+0A84, U+0A8E, U+0A92.
        if (character == 0xe0aa8000 || character == 0xe0aa8400 || character == 0xe0aa8e00 || character == 0xe0aa9200) {
          return f_false;
        }

        // Gujarati: U+0AA9, U+0AB1, U+0AB4, U+0ABA.
        if (character == 0xe0aaa900 || character == 0xe0aab100 || character == 0xe0aab400 || character == 0xe0aaba00) {
          return f_false;
        }

        // Gujarati: U+0ABB, U+0AC6, U+0ACA, U+0ACE.
        if (character == 0xe0aabb00 || character == 0xe0ab8600 || character == 0xe0ab8a00 || character == 0xe0ab8e00) {
          return f_false;
        }

        // Gujarati: U+0ACF, U+0AE4, U+0AE5.
        if (character == 0xe0ab8f00 || character == 0xe0aba400 || character == 0xe0aba500) {
          return f_false;
        }

        // Gurmukhi: U+0A0B to U+0A0E.
        if (character >= 0xe0a88b00 && character <= 0xe0a88e00) {
          return f_false;
        }

        // Gurmukhi: U+0A43 to U+0A46.
        if (character >= 0xe0a98300 && character <= 0xe0a98600) {
          return f_false;
        }

        // Gurmukhi: U+0A4E to U+0A50.
        if (character >= 0xe0a98e00 && character <= 0xe0a99000) {
          return f_false;
        }

        // Gurmukhi: U+0A52 to U+0A58.
        if (character >= 0xe0a99200 && character <= 0xe0a99800) {
          return f_false;
        }

        // Gurmukhi: U+0A5F to U+0A65.
        if (character >= 0xe0a99f00 && character <= 0xe0a9a500) {
          return f_false;
        }

        // Gurmukhi: U+0A76 to U+0A7F.
        if (character >= 0xe0a9b600 && character <= 0xe0a9bf00) {
          return f_false;
        }

        // Gurmukhi: U+0A00, U+0A04, U+0A11, U+0A12.
        if (character == 0xe0a88000 || character == 0xe0a88400 || character == 0xe0a89100 || character == 0xe0a89200) {
          return f_false;
        }

        // Gurmukhi: U+0A29, U+0A31, U+0A34, U+0A37.
        if (character == 0xe0a8a900 || character == 0xe0a8b100 || character == 0xe0a8b400 || character == 0xe0a8b700) {
          return f_false;
        }

        // Gurmukhi: U+0A3A, U+0A3B, U+0A3D, U+0A49.
        if (character == 0xe0a8ba00 || character == 0xe0a8bb00 || character == 0xe0a8bd00 || character == 0xe0a98900) {
          return f_false;
        }

        // Gurmukhi: U+0A4A, U+0A5D.
        if (character == 0xe0a98a00 || character == 0xe0a99d00) {
          return f_false;
        }

        // Kannada: U+0CCE to U+0CD4.
        if (character >= 0xe0b38e00 && character <= 0xe0b39400) {
          return f_false;
        }

        // Kannada: U+0CD7 to U+0CDD.
        if (character >= 0xe0b39700 && character <= 0xe0b39d00) {
          return f_false;
        }

        // Kannada: U+0CF3 to U+0CFF.
        if (character >= 0xe0b3b300 && character <= 0xe0b3bf00) {
          return f_false;
        }

        // Kannada: U+0C84, U+0C8D, U+0C91, U+0CA9.
        if (character == 0xe0b28400 || character == 0xe0b28d00 || character == 0xe0b29100 || character == 0xe0b2a900) {
          return f_false;
        }

        // Kannada: U+0CB4, U+0CBA, U+0CBB, U+0CC5.
        if (character == 0xe0b28400 || character == 0xe0b2ba00 || character == 0xe0b2bb00 || character == 0xe0b38500) {
          return f_false;
        }

        // Kannada: U+0CC9, U+0CDF, U+0CE4, U+0CE5.
        if (character == 0xe0b38900 || character == 0xe0b39f00 || character == 0xe0b3a400 || character == 0xe0b3a500) {
          return f_false;
        }

        // Kannada: U+0CF0.
        if (character == 0xe0b3b0) {
          return f_false;
        }

        // Lao: U+0E90 to U+0E93.
        if (character >= 0xe0ba9000 && character <= 0xe0ba9300) {
          return f_false;
        }

        // Lao: U+0EE0 to U+0EFF.
        if (character >= 0xe0bba000 && character <= 0xe0bbbf00) {
          return f_false;
        }

        // Lao: U+0E80, U+0E83, U+0E85, U+0E86.
        if (character == 0xe0ba8000 || character == 0xe0ba8300 || character == 0xe0ba8500 || character == 0xe0ba8600) {
          return f_false;
        }

        // Lao: U+0E89, U+0E8B, U+0E8C, U+0E8E.
        if (character == 0xe0ba8900 || character == 0xe0ba8b00 || character == 0xe0ba8c00 || character == 0xe0ba8e00) {
          return f_false;
        }

        // Lao: U+0E8F, U+0E98, U+0EA0, U+0EA4.
        if (character == 0xe0ba8f00 || character == 0xe0ba9800 || character == 0xe0baa000 || character == 0xe0baa400) {
          return f_false;
        }

        // Lao: U+0EA6, U+0EA8, U+0EA9, U+0EAC.
        if (character == 0xe0ba8600 || character == 0xe0ba8800 || character == 0xe0baa900 || character == 0xe0baac00) {
          return f_false;
        }

        // Lao: U+0EBA, U+0EBE, U+0EBF, U+0EC5.
        if (character == 0xe0baba00 || character == 0xe0babe00 || character == 0xe0babf00 || character == 0xe0bb8500) {
          return f_false;
        }

        // Lao: U+0EC7, U+0ECE, U+0ECF, U+0EDA.
        if (character == 0xe0bb8700 || character == 0xe0bb8e00 || character == 0xe0bb8f00 || character == 0xe0bb9a00) {
          return f_false;
        }

        // Lao: U+0EDB.
        if (character == 0xe0bb9b00) {
          return f_false;
        }

        // Malayalam: U+0D50 to U+0D53.
        if (character >= 0xe0b59000 && character <= 0xe0b59300) {
          return f_false;
        }

        // Malayalam: U+0D00, U+0D04, U+0D0D, U+0D11.
        if (character == 0xe0b48000 || character == 0xe0b48400 || character == 0xe0b48d00 || character == 0xe0b49100) {
          return f_false;
        }

        // Malayalam: U+0D3B, U+0D3C, U+0D45, U+0D49.
        if (character == 0xe0b4bb00 || character == 0xe0b4bc00 || character == 0xe0b58500 || character == 0xe0b58900) {
          return f_false;
        }

        // Malayalam: U+0D64, U+0D65.
        if (character == 0xe0b5a400 || character == 0xe0b5a500) {
          return f_false;
        }

        // Mandaic: U+085C, U+085D, U+085F.
        if (character == 0xe0a19c00 || character == 0xe0a19d00 || character == 0xe0a19f00) {
          return f_false;
        }

        // Oriya: U+0B50 to U+0B55.
        if (character >= 0xe0ad9000 && character <= 0xe0ad9500) {
          return f_false;
        }

        // Oriya: U+0B58 to U+0B5B.
        if (character >= 0xe0ad9800 && character <= 0xe0ad9b00) {
          return f_false;
        }

        // Oriya: U+0B78 to U+0B7F.
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

        // Tibetan: U+0F48, U+0F98, U+0FBD, U+0FCD.
        if (character == 0xe0bd8800 || character == 0xe0be9800 || character == 0xe0bebd00 || character == 0xe0bf8d00) {
          return f_false;
        }
      }
      else if (byte_first == 0xe1) {
        // Batak: U+1BF4 to U+1BFB.
        if (character >= 0xe1afb400 && character <= 0xe1afbb00) {
          return f_false;
        }

        // Buginese: U+1A1C to U+1A1D.
        if (character >= 0xe1a89c00 && character <= 0xe1a89d00) {
          return f_false;
        }

        // Buhid: U+1754 to U+175F.
        if (character >= 0xe19d9400 && character <= 0xe19d9f00) {
          return f_false;
        }

        // Cherokee: U+13F6, U+13F7, U+13FE, U+13FF.
        if (character == 0xe18fb600 || character <= 0xe18fb700 || character <= 0xe18fbe00 || character <= 0xe18fbf00) {
          return f_false;
        }

        // Combining Diacritical Marks Supplement: U+1ABF to U+1AFF.
        if (character >= 0xe1aabf00 && character <= 0xe1abbf00) {
          return f_false;
        }

        // Cyrillic Extended-C: U+1C89 to U+1C8F.
        if (character >= 0xe1b28900 && character <= 0xe1b28f00) {
          return f_false;
        }

        // Ethiopic: U+137D to U+137F.
        if (character >= 0xe18dbd00 && character <= 0xe18dbf00) {
          return f_false;
        }

        // Ethiopic: U+1249, U+124E, U+124F, U+1257.
        if (character == 0xe1898900 || character == 0xe1898e00 || character == 0xe1898f00 || character == 0xe1899700) {
          return f_false;
        }

        // Ethiopic: U+1259, U+125E, U+125F, U+1289.
        if (character == 0xe1899900 || character == 0xe1899e00 || character == 0xe1899f00 || character == 0xe18a8900) {
          return f_false;
        }

        // Ethiopic: U+128E, U+128F, U+12B1, U+12B6.
        if (character == 0xe18a8e00 || character == 0xe18a8f00 || character == 0xe18ab100 || character == 0xe18ab600) {
          return f_false;
        }

        // Ethiopic: U+12B7, U+12BF, U+12C1, U+12C6.
        if (character == 0xe18ab700 || character == 0xe18abf00 || character == 0xe18b8100 || character == 0xe18b8600) {
          return f_false;
        }

        // Ethiopic: U+12C7, U+12D7, U+1311, U+1316.
        if (character == 0xe18b8700 || character == 0xe18b9700 || character == 0xe18c9100 || character == 0xe18c9600) {
          return f_false;
        }

        // Ethiopic: U+1317, U+135B, U+135C.
        if (character == 0xe18c9700 || character == 0xe18d9b00 || character == 0xe18d9c00) {
          return f_false;
        }

        // Ethiopic Supplement: U+139A to U+139F.
        if (character >= 0xe18e9a00 && character <= 0xe18e9f00) {
          return f_false;
        }

        // Georgian: U+10C8 to U+10CC.
        if (character >= 0xe1838800 && character <= 0xe1838c00) {
          return f_false;
        }

        // Georgian: U+10C6, U+10CE, U+10CF.
        if (character == 0xe1838600 || character == 0xe1838e00 || character == 0xe1838f00) {
          return f_false;
        }

        // Greek Extended: U+1F16, U+1F17, U+1F1E, U+1F1F.
        if (character == 0xe1bc9600 || character == 0xe1bc9700 || character == 0xe1bc9e00 || character == 0xe1bc9f00) {
          return f_false;
        }

        // Greek Extended: U+1F46, U+1F47, U+1F4E, U+1F4F.
        if (character == 0xe1bd8600 || character == 0xe1bd8700 || character == 0xe1bd8e00 || character == 0xe1bd8f00) {
          return f_false;
        }

        // Greek Extended: U+1F58, U+1F5A, U+1F5C, U+1F5E.
        if (character == 0xe1bd9800 || character == 0xe1bd9a00 || character == 0xe1bd9c00 || character == 0xe1bd9e00) {
          return f_false;
        }

        // Greek Extended: U+1F7E, U+1F7F, U+1FB5, U+1FC5.
        if (character == 0xe1bdbe00 || character == 0xe1bdbf00 || character == 0xe1beb500 || character == 0xe1bf8500) {
          return f_false;
        }

        // Greek Extended: U+1FD4, U+1FD5, U+1FDC, U+1FF0.
        if (character == 0xe1bf9400 || character == 0xe1bf9500 || character == 0xe1bf9c00 || character == 0xe1bfb000) {
          return f_false;
        }

        // Greek Extended: U+1FF1, U+1FF5, U+1FFF.
        if (character == 0xe1bfb100 || character == 0xe1bfb500 || character == 0xe1bfbf00) {
          return f_false;
        }

        // Hanunoo: U+1737 to U+173F.
        if (character >= 0xe19cb700 && character <= 0xe19cbf00) {
          return f_false;
        }

        // Khmer: U+17EA to U+17EF.
        if (character >= 0xe19faa00 && character <= 0xe19faf00) {
          return f_false;
        }

        // Khmer: U+17FA to U+17FF.
        if (character >= 0xe19fba00 && character <= 0xe19fbf00) {
          return f_false;
        }

        // Khmer: U+17DE, U+17DF.
        if (character == 0xe19f9e00 || character == 0xe19f9f00) {
          return f_false;
        }

        // Lepcha: U+1C38 to U+1C3A.
        if (character >= 0xe1b0b800 && character <= 0xe1b0ba00) {
          return f_false;
        }

        // Lepcha: U+1C4A to U+1C4C.
        if (character >= 0xe1b18a00 && character <= 0xe1b18c00) {
          return f_false;
        }

        // Limbu: U+192C to U+192F.
        if (character >= 0xe1a4ac00 && character <= 0xe1a4af00) {
          return f_false;
        }

        // Limbu: U+193C to U+193F.
        if (character >= 0xe1a4bc00 && character <= 0xe1a4bf00) {
          return f_false;
        }

        // Limbu: U+1941 to U+1943.
        if (character >= 0xe1a58100 && character <= 0xe1a58300) {
          return f_false;
        }

        // Limbu: U+191F.
        if (character == 0xe1a49f00) {
          return f_false;
        }

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
        // CJK Radicals Supplement: U+2E9A, U+2EF4 to U+2EFF.
        if (character == 0xe2ba9a00 || character >= 0xe2bbb400 && character <= 0xe2bbbf00) {
          return f_false;
        }

        // Combining Diacritical Marks for Symbols: U+20F1 to U+20FF.
        if (character >= 0xe283b100 && character <= 0xe283bf00) {
          return f_false;
        }

        // Control Pictures: U+2427 to U+243F.
        if (character >= 0xe290a700 && character <= 0xe290bf00) {
          return f_false;
        }

        // Coptic: U+2CF4 to U+2CF8.
        if (character >= 0xe2b3b400 && character <= 0xe2b3b800) {
          return f_false;
        }

        // Currency Symbols: U+20BF to U+20CF.
        if (character >= 0xe282bf00 && character <= 0xe2838f00) {
          return f_false;
        }

        // Ethiopic Extended: U+2D97 to U+2D9F.
        if (character >= 0xe2b69700 && character <= 0xe2b69f00) {
          return f_false;
        }

        // Ethiopic Extended: U+2DA7, U+2DAF, U+2DB7, U+2DBF.
        if (character == 0xe2b6a700 || character == 0xe2b6af00 || character == 0xe2b6b700 || character == 0xe2b6bf00) {
          return f_false;
        }

        // Ethiopic Extended: U+2DC7, U+2DCF, U+2DD7, U+2DDF.
        if (character == 0xe2b78700 || character == 0xe2b78f00 || character == 0xe2b79700 || character == 0xe2b79f00) {
          return f_false;
        }

        // General Punctuation: U+2065.
        if (character == 0xe281a500) {
          return f_false;
        }

        // Georgian Supplement: U+2D28 to U+2D2C.
        if (character >= 0xe2b4a800 && character <= 0xe2b4ac00) {
          return f_false;
        }

        // Georgian Supplement: U+2D26, U+2D2E, U+2D2F.
        if (character == 0xe2b4a600 || character == 0xe2b4ae00 || character == 0xe2b4af00) {
          return f_false;
        }

        // Glagolitic: U+2C2F, U+2C5F.
        if (character == 0xe2b0af00 || character == 0xe2b19f00) {
          return f_false;
        }

        // Ideographic Description Characters: U+2FFC to U+2FFF.
        if (character >= 0xe2bfbc00 && character <= 0xe2bfbf00) {
          return f_false;
        }

        // Kangxi Radicals: U+2FD6 to U+2FDF.
        if (character >= 0xe2bf9600 && character <= 0xe2bf9f00) {
          return f_false;
        }

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
      else if (byte_first == 0xe3) {
        // Bopomofo: U+3100 to U+3104.
        if (character >= 0xe3848000 && character <= 0xe3848400) {
          return f_false;
        }

        // Bopomofo: U+312E, U+312F.
        if (character == 0xe384ae00 || character == 0xe384af00) {
          return f_false;
        }

        // Bopomofo Extended: U+31BB to U+31BF.
        if (character >= 0xe386bb00 && character <= 0xe386bf00) {
          return f_false;
        }

        // CJK Strokes: U+31E4 to U+31EF.
        if (character >= 0xe387a400 && character <= 0xe387af00) {
          return f_false;
        }

        // Enclosed CJK Letters and Months: U+321F, U+32FF.
        if (character == 0xe3889f00 || character == 0xe38bbf00) {
          return f_false;
        }

        // Hangul Compatibility Jamo: U+3130, U+318F.
        if (character == 0xe384b000 || character == 0xe3868f00) {
          return f_false;
        }

        // Hiragana: U+3040, U+3097, U+3098.
        if (character == 0xe3818000 || character == 0xe3829700 || character == 0xe3829800) {
          return f_false;
        }
      }
      else if (byte_first == 0xe4) {
        // CJK Unified Ideographs Extension A: U+4DB6, U+4DBF.
        if (character >= 0xe4b6b600 && character <= 0xe4b6bf00) {
          return f_false;
        }
      }
      else if (byte_first == 0xe9) {
        // CJK Unified Ideographs: U+9FD6, U+9FFF.
        if (character >= 0xe9bf9600 && character <= 0xe9bfbf00) {
          return f_false;
        }
      }
      else if (byte_first == 0xea) {
        // Balinese: U+1B4C to U+1B4F.
        if (character >= 0xeaad8c00 && character <= 0xeaad8f00) {
          return f_false;
        }

        // Balinese: U+1B7D to U+1B7F.
        if (character >= 0xeaadbd00 && character <= 0xeaadbf00) {
          return f_false;
        }

        // Bamum: U+A6F8 to U+A6FF.
        if (character >= 0xea9bb800 && character <= 0xea9bbf00) {
          return f_false;
        }

        // Cham: U+AA37 to U+AA3F.
        if (character >= 0xeaa8b700 && character <= 0xeaa8bf00) {
          return f_false;
        }

        // Cham: U+AA4E, U+AA4F, U+AA5A, U+AA5B.
        if (character == 0xeaa98e00 || character == 0xeaa98f00 || character == 0xeaa99a00 || character == 0xeaa99b00) {
          return f_false;
        }

        // Common Indic Number Forms: U+A83A, U+A83F.
        if (character == 0xeaa0ba00 || character == 0xeaa0bf00) {
          return f_false;
        }

        // Ethiopic Extended-A: U+AB17 to U+AB1F.
        if (character >= 0xeaac9700 && character <= 0xeaac9f00) {
          return f_false;
        }

        // Ethiopic Extended-A: U+AB00, U+AB07, U+AB08, U+AB0F.
        if (character == 0xeaac8000 || character == 0xeaac8700 || character == 0xeaac8800 || character == 0xeaac8f00) {
          return f_false;
        }

        // Ethiopic Extended-A: U+AB10, U+AB27, U+AB2F.
        if (character == 0xeaac9000 || character == 0xeaaca700 || character == 0xeaacaf00) {
          return f_false;
        }

        // Hangul Jamo Extended-A: U+A97D to U+A97F.
        if (character >= 0xeaa5bd00 && character <= 0xeaa5bf00) {
          return f_false;
        }

        // Javanese: U+A9CE, U+A9DA to U+A9DD.
        if (character == 0xeaa78e00 || character >= 0xeaa79a00 && character <= 0xeaa7a79d) {
          return f_false;
        }

        // Latin Extended-D: U+A7AF, U+A7B8 to U+A7F6.
        if (character == 0xea9eaf00 || character >= 0xea9eb800 && character <= 0xea9fb600) {
          return f_false;
        }

        // Latin Extended-E: U+AB66 to U+AB6F.
        if (character >= 0xeaada600 && character <= 0xeaadaf00) {
          return f_false;
        }

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
      else if (byte_first == 0xed) {
        // Hangul Jamo Extended-B: U+D7C7 to U+D7CA.
        if (character >= 0xed9f8700 && character <= 0xed9f8a00)  {
          return f_false;
        }

        // Hangul Jamo Extended-B: U+D7FC to U+D7FF.
        if (character >= 0xed9fbc00 && character <= 0xed9fbf00)  {
          return f_false;
        }

        // Hangul Syllables: U+D7A4 to U+D7AF.
        if (character >= 0xed9ea400 && character <= 0xed9eaf00)  {
          return f_false;
        }

        // Low Surrogates: U+DC00 to U+DFFF.
        if (character >= 0xedbfb000 && character <= 0xedbfbf00)  {
          return f_false;
        }

        // High Surrogates: U+D800 to U+DB7F.
        if (character >= 0xeda08000 && character <= 0xedadbf00) {
          return f_false;
        }

        // High Private Use Surrogates: U+DB80 to U+DBFF.
        if (character >= 0xedae8000 && character <= 0xedafbf00) {
          return f_false;
        }
      }
      else if (byte_first == 0xee) {
        // @todo update this range to only 0xee.
        // consider all private use codes as valid, U+E000 to U+F8FF.
        if (character >= 0xee808000 && character <= 0xefa3bf00) {
          return f_true;
        }
      }
      else if (byte_first == 0xef) {
        // @todo update this range to only 0xef
        // consider all private use codes as valid, U+E000 to U+F8FF.
        if (character >= 0xee808000 && character <= 0xefa3bf00) {
          return f_true;
        }

        // Arabic Presentation Forms-A: U+FBC2 to U+FBD2.
        if (character >= 0xefaf8200 && character <= 0xefaf9200) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FD40 to U+FD4F.
        if (character >= 0xefb58000 && character <= 0xefb58f00) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FDC8 to U+FDEF.
        if (character >= 0xefb78800 && character <= 0xefb7af00) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FD90, U+FD91, U+FDFE, U+FDFF.
        if (character == 0xefb69000 || character == 0xefb69100 || character == 0xefb7be00 || character == 0xefb7bf00) {
          return f_false;
        }

        // Arabic Presentation Forms-B: U+FE75, U+FEFD, U+FEFE.
        if (character == 0xefb9b500 || character == 0xefbbbd00 || character == 0xefbbbe00) {
          return f_false;
        }

        // CJK Compatibility Ideographs: U+FADA to U+FAFF.
        if (character >= 0xefab9a00 && character <= 0xefabbf00) {
          return f_false;
        }

        // CJK Compatibility Ideographs: U+FA6E, U+FA6F.
        if (character == 0xefa9ae00 || character == 0xefa9af00) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FFDD to U+FFDF.
        if (character >= 0xefbf9d00 && character <= 0xefbf9f00) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FF00, U+FFBF, U+FFC0, U+FFC1.
        if (character == 0xefbc8000 || character == 0xefbebf00 || character == 0xefbf8000 || character == 0xefbf8100) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FFC8, U+FFC9, U+FFD0, U+FFD1.
        if (character == 0xefbf8800 || character == 0xefbf8900 || character == 0xefbf9000 || character == 0xefbf9100) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FFD8, U+FFD9, U+FFE7, U+FFEF.
        if (character == 0xefbf9800 || character == 0xefbf9900 || character == 0xefbfa700 || character == 0xefbfaf00) {
          return f_false;
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
      // @todo: investigate potential performance gains by storing and compararing against the lower 16 bits on the idea that the register size needed for comparrison will be smaller and therefore a faster comparison (16-bit vs 32-bit).
      // reduce the number of checks by grouping checks by second byte.
      uint8_t byte_second = f_macro_utf_character_to_char_2(character);

      if (byte_first == 0xf0) {
        if (byte_second == 0x90) {
          // Avestan: U+10B36 to U+10B38.
          if (character >= 0xf090acb6 && character <= 0xf090acb8) {
            return f_false;
          }

          // Carian: U+102D1 to U+102DF.
          if (character >= 0xf0908b91 && character <= 0xf0908b9f) {
            return f_false;
          }

          // Caucasian Albanian: U+10564 to U+1056E.
          if (character >= 0xf09095a4 && character <= 0xf09095ae) {
            return f_false;
          }

          // Coptic Epact Numbers: U+102FC to U+102FF.
          if (character >= 0xf0908bbc && character <= 0xf0908bbf) {
            return f_false;
          }

          // Cypriot Syllabary: U+10839 to U+1083B.
          if (character >= 0xf090a0b9 && character <= 0xf090a0bb) {
            return f_false;
          }

          // Cypriot Syllabary: U+10806, U+10807, U+10809.
          if (character == 0xf090a086 || character == 0xf090a087 || character == 0xf090a089) {
            return f_false;
          }

          // Cypriot Syllabary: U+10836, U+1083D, U+1083E.
          if (character == 0xf090a0b6 || character == 0xf090a0bd || character == 0xf090a0be) {
            return f_false;
          }

          // Elbasan: U+10528 to U+1052F.
          if (character >= 0xf09094a8 && character <= 0xf09094af) {
            return f_false;
          }

          // Gothic: U+1034B to U+1034F.
          if (character >= 0xf0908d8b && character <= 0xf0908d8f) {
            return f_false;
          }

          // Hatran: U+108F3.
          if (character == 0xf090a3b3) {
            return f_false;
          }

          // Hatran: U+108F6 to U+108FA.
          if (character >= 0xf090a3b6 && character <= 0xf090a3ba) {
            return f_false;
          }

          // Imperial Aramaic: U+10856.
          if (character == 0xf090a196) {
            return f_false;
          }

          // Inscriptional Pahlavi: U+10B73 to U+10B77.
          if (character >= 0xf090adb3 && character <= 0xf090adb7) {
            return f_false;
          }

          // Inscriptional Parthian: U+10B56 to U+10B57.
          if (character >= 0xf090ad96 && character <= 0xf090ad97) {
            return f_false;
          }

          // Kharoshthi: U+10A07 to U+10A0B.
          if (character >= 0xf090a887 && character <= 0xf090a88b) {
            return f_false;
          }

          // Kharoshthi: U+10A34 to U+10A37.
          if (character >= 0xf090a8b4 && character <= 0xf090a8b7) {
            return f_false;
          }

          // Kharoshthi: U+10A3B to U+10A3E.
          if (character >= 0xf090a8bb && character <= 0xf090a8be) {
            return f_false;
          }

          // Kharoshthi: U+10A48 to U+10A4F.
          if (character >= 0xf090a988 && character <= 0xf090a98f) {
            return f_false;
          }

          // Kharoshthi: U+10A59 to U+10A5F.
          if (character >= 0xf090a999 && character <= 0xf090a99f) {
            return f_false;
          }

          // Kharoshthi: U+10A04, U+10A14, U+10A18.
          if (character == 0xf090a884 || character == 0xf090a894 || character == 0xf090a898) {
            return f_false;
          }

          // Linear A: U+10737 to U+1073F.
          if (character >= 0xf0909cb7 && character <= 0xf0909cbf) {
            return f_false;
          }

          // Linear A: U+10756 to U+1075F.
          if (character >= 0xf0909d96 && character <= 0xf0909d9f) {
            return f_false;
          }

          // Linear A: U+10768 to U+1077F.
          if (character >= 0xf0909da8 && character <= 0xf0909dbf) {
            return f_false;
          }

          // Linear B Ideograms: U+100FB to U+100FF.
          if (character >= 0xf09083bb && character <= 0xf09083bf) {
            return f_false;
          }

          // Linear B Syllabary: U+1005E to U+1007F.
          if (character >= 0xf090819e && character <= 0xf09081bf) {
            return f_false;
          }

          // Linear B Syllabary: U+1000C, U+10027, U+1003B.
          if (character == 0xf090808c || character == 0xf09080a7 || character == 0xf09080bb) {
            return f_false;
          }

          // Linear B Syllabary: U+1003E, U+1004E, U+1004F.
          if (character == 0xf09080be || character == 0xf090818e || character == 0xf090818f) {
            return f_false;
          }

          // Lycian: U+1029D to U+1029F.
          if (character >= 0xf0908a9d && character <= 0xf0908a9f) {
            return f_false;
          }

          // Lydian: U+1093A to U+1093E.
          if (character >= 0xf090a4ba && character <= 0xf090a4be) {
            return f_false;
          }

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
          // Bhaiksuki: U+11C46 to U+11C4F.
          if (character >= 0xf091b186 && character <= 0xf091b18f) {
            return f_false;
          }

          // Bhaiksuki: U+11C6D to U+11C6F.
          if (character >= 0xf091b1ad && character <= 0xf091b1af) {
            return f_false;
          }

          // Bhaiksuki: U+11C09, U+11C37.
          if (character == 0xf091b089 || character == 0xf091b0b7) {
            return f_false;
          }

          // Brahmi: U+1104E to U+11051.
          if (character >= 0xf091818e && character <= 0xf0918191) {
            return f_false;
          }

          // Brahmi: U+11070 to U+1107E.
          if (character >= 0xf09181b0 && character <= 0xf09181be) {
            return f_false;
          }

          // Chakma: U+11135, U+11144 to U+1114F.
          if (character == 0xf09184b5 || character >= 0xf0918584 && character <= 0xf091858f) {
            return f_false;
          }

          // Grantha: U+11351 to U+11356.
          if (character >= 0xf0918d91 && character <= 0xf0918d96) {
            return f_false;
          }

          // Grantha: U+11358 to U+1135C.
          if (character >= 0xf0918d98 && character <= 0xf0918d9c) {
            return f_false;
          }

          // Grantha: U+1136D to U+1136F.
          if (character >= 0xf0918dad && character <= 0xf0918daf) {
            return f_false;
          }

          // Grantha: U+11375 to U+1137F.
          if (character >= 0xf0918db5 && character <= 0xf0918dbf) {
            return f_false;
          }

          // Grantha: U+11304, U+1130D, U+1130E, U+11311.
          if (character == 0xf0918c84 || character == 0xf0918c8d || character == 0xf0918c8e || character == 0xf0918c91) {
            return f_false;
          }

          // Grantha: U+11312, U+11329, U+11331, U+11334.
          if (character == 0xf0918c92 || character == 0xf0918ca9 || character == 0xf0918cb1 || character == 0xf0918cb4) {
            return f_false;
          }

          // Grantha: U+1133A, U+1133B, U+11345, U+11346.
          if (character == 0xf0918cba || character == 0xf0918cbb || character == 0xf0918d85 || character == 0xf0918d86) {
            return f_false;
          }

          // Grantha: U+11349, U+1134A, U+1134E, U+1134F.
          if (character == 0xf0918d89 || character == 0xf0918d8a || character == 0xf0918d8e || character == 0xf0918d8f) {
            return f_false;
          }

          // Grantha: U+11364, U+11365.
          if (character == 0xf0918da4 || character == 0xf0918da5) {
            return f_false;
          }

          // Kaithi: U+110C2 to U+110CF.
          if (character >= 0xf0918382 && character <= 0xf091838f) {
            return f_false;
          }

          // Khojki: U+1123F to U+1124F.
          if (character >= 0xf09188bf && character <= 0xf091898f) {
            return f_false;
          }

          // Khojki: U+11212.
          if (character == 0xf0918892) {
            return f_false;
          }

          // Khudawadi: U+112EB to U+112EF.
          if (character >= 0xf0918bab && character <= 0xf0918baf) {
            return f_false;
          }

          // Khudawadi: U+112FA to U+112FF.
          if (character >= 0xf0918bba && character <= 0xf0918bbf) {
            return f_false;
          }

          // Mahajani: U+11177 to U+1117F.
          if (character >= 0xf09185b7 && character <= 0xf09185bf) {
            return f_false;
          }

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
        else if (byte_second == 0x92) {
          // Cuneiform: U+1239A to U+123FF.
          if (character >= 0xf0928e9a && character <= 0xf0928fbf) {
            return f_false;
          }

          // Cuneiform Numbers and Punctuation: U+1246F, U+12475 to U+1247F.
          if (character == 0xf09291af || character >= 0xf09291b5 && character <= 0xf09291bf) {
            return f_false;
          }

          // Early Dynastic Cuneiform: U+12544 to U+1254F.
          if (character >= 0xf0929584 && character <= 0xf092958f) {
            return f_false;
          }
        }
        else if (byte_second == 0x93) {
          // Egyptian Hieroglyphs: U+1342F.
          if (character == 0xf09390af) {
            return f_false;
          }
        }
        else if (byte_second == 0x96) {
          // Bamum Supplement: U+16A39 to U+16A3F.
          if (character >= 0xf096a8b9 && character <= 0xf096a8bf) {
            return f_false;
          }

          // Bassa Vah: U+16AF6 to U+16AFF.
          if (character >= 0xf096abb6 && character <= 0xf096abbf) {
            return f_false;
          }

          // Bassa Vah: U+16AEE, U+16AEF.
          if (character == 0xf096abae || character == 0xf096abaf) {
            return f_false;
          }

          // Ideographic Symbols and Punctuation: U+16FE1 to U+16FFF.
          if (character >= 0xf096bfa1 && character <= 0xf096bfbf) {
            return f_false;
          }

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
          // Duployan: U+1BC6B to U+1BC6F.
          if (character >= 0xf09bb1ab && character <= 0xf09bb1af) {
            return f_false;
          }

          // Duployan: U+1BC7D to U+1BC7F.
          if (character >= 0xf09bb1bd && character <= 0xf09bb1bf) {
            return f_false;
          }

          // Duployan: U+1BC89 to U+1BC8F.
          if (character >= 0xf09bb289 && character <= 0xf09bb28f) {
            return f_false;
          }

          // Duployan: U+1BC9A to U+1BC9B.
          if (character == 0xf09bb29a || character == 0xf09bb29b) {
            return f_false;
          }

          // Kana Supplement: U+1B002 to U+1B0FF.
          if (character >= 0xf09b8082 && character <= 0xf09b83bf) {
            return f_false;
          }

          // Shorthand Format Controls: U+1BCA4 to U+1BCAF.
          if (character >= 0xf09bb2a4 && character <= 0xf09bb2af) {
            return f_false;
          }
        }
        else if (byte_second == 0x9d) {
          // Byzantine Musical Symbols: U+1D0F6 to U+1D0FF.
          if (character >= 0xf09d83b6 && character <= 0xf09d83bf) {
            return f_false;
          }

          // Counting Rod Numerals: U+1D372 to U+1D37F.
          if (character >= 0xf09d8db2 && character <= 0xf09d8dbf) {
            return f_false;
          }

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

          // Musical Symbols: U+1D127, U+1D128.
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
          // Glagolitic Supplement: U+1E02B to U+1E02F.
          if (character >= 0xf09e80ab && character <= 0xf09e80af) {
            return f_false;
          }

          // Glagolitic Supplement: U+1E007, U+1E019, U+1E01A.
          if (character == 0xf09e8087 || character == 0xf09e8099 || character == 0xf09e809a) {
            return f_false;
          }

          // Glagolitic Supplement: U+1E022, U+1E025.
          if (character == 0xf09e80a2 || character == 0xf09e80a5) {
            return f_false;
          }

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
          // Domino Tiles: U+1F094 to U+1F09F.
          if (character >= 0xf09f8294 && character <= 0xf09f829f) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F10D to U+1F10F.
          if (character >= 0xf09f848d && character <= 0xf09f848f) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F16C to U+1F16F.
          if (character >= 0xf09f85ac && character <= 0xf09f85af) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F1AD to U+1F1E5.
          if (character >= 0xf09f86ad && character <= 0xf09f87a5) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F12F.
          if (character == 0xf09f84af) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F203 to U+1F20F.
          if (character >= 0xf09f8883 && character <= 0xf09f888f) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F23C to U+1F23F.
          if (character >= 0xf09f88bc && character <= 0xf09f88bf) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F249 to U+1F24F.
          if (character >= 0xf09f8989 && character <= 0xf09f898f) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F252 to U+1F2FF.
          if (character >= 0xf09f8992 && character <= 0xf09f8bbf) {
            return f_false;
          }

          // Geometric Shapes Extended: U+1F7D5 to U+1F7FF.
          if (character >= 0xf09f9f95 && character <= 0xf09f9fbf) {
            return f_false;
          }

          // Mahjong Tiles: U+1F02C to U+1F02F.
          if (character >= 0xf09f80ac && character <= 0xf09f80af) {
            return f_false;
          }

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
        else if (byte_second == 0xaa) {
          // CJK Unified Ideographs Extension B: U+2A6D7 to U+2A6DF.
          if (character >= 0xf0aa9b97 && character <= 0xf0aa9b9f) {
            return f_false;
          }
        }
        else if (byte_second == 0xab) {
          // CJK Unified Ideographs Extension C: U+2B735 to U+2B73F.
          if (character >= 0xf0ab9cb5 && character <= 0xf0ab9cbf) {
            return f_false;
          }

          // CJK Unified Ideographs Extension D: U+2B81E to U+2B81F.
          if (character >= 0xf0aba09e && character <= 0xf0aba09f) {
            return f_false;
          }
        }
        else if (byte_second == 0xac) {
          // CJK Unified Ideographs Extension E: U+2CF92 to U+2CF9F.
          if (character >= 0xf0acbe92 && character <= 0xf0acbe9f) {
            return f_false;
          }
        }
        else if (byte_second == 0xaf) {
          // CJK Compatibility Ideographs Supplement: U+2FA1E to U+2FA1F.
          if (character >= 0xf0afa89e && character <= 0xf0afa89f) {
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
      memcpy(*character, &utf_character, width);
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

      memcpy(*character, &utf, width);
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

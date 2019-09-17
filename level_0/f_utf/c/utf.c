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
      else if (byte_first == 0xd8) {
        // Arabic: U+061D.
        if (byte == 0x9d) {
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
      uint16_t bytes = (uint16_t) ((character & 0x00ffff00) >> 4);

      if (byte_first == 0xe0) {
        // Arabic Extended-A: U+08B5, U+08BE to U+08D3.
        if (bytes == 0xa2b5 || bytes >= 0xa2be && bytes <= 0xa393) {
          return f_false;
        }

        // Bengali: U+09B3 to U+09B5.
        if (bytes >= 0xa6b3 && bytes <= 0xa6b5) {
          return f_false;
        }

        // Bengali: U+09CF to U+09D6.
        if (bytes >= 0xa78f && bytes <= 0xa796) {
          return f_false;
        }

        // Bengali: U+09D8 to U+09DB.
        if (bytes >= 0xa798 && bytes <= 0xa79b) {
          return f_false;
        }

        // Bengali: U+09FC to U+09FF.
        if (bytes >= 0xa7bc && bytes <= 0xa7bf) {
          return f_false;
        }

        // Bengali: U+0984, U+098D, U+098E, U+0991.
        if (bytes == 0xa684 || bytes == 0xa68d || bytes == 0xa68e || bytes == 0xa691) {
          return f_false;
        }

        // Bengali: U+0992, U+09A9, U+09B1, U+09BA.
        if (bytes == 0xa692 || bytes == 0xa6a9 || bytes == 0xa6b1 || bytes == 0xa6ba) {
          return f_false;
        }

        // Bengali: U+09BB, U+09C5, U+09C6, U+09C9.
        if (bytes == 0xa6bb || bytes == 0xa785 || bytes == 0xa786 || bytes == 0xa789) {
          return f_false;
        }

        // Bengali: U+09CA, U+09DE, U+09E4, U+09E5.
        if (bytes == 0xa78a || bytes == 0xe79e || bytes == 0xa7a4 || bytes == 0xa7a5) {
          return f_false;
        }

        // Gujarati: U+0AD1 to U+0ADF.
        if (bytes >= 0xab91 && bytes <= 0xab94) {
          return f_false;
        }

        // Gujarati: U+0AF2 to U+0AF8.
        if (bytes >= 0xabb2 && bytes <= 0xabb8) {
          return f_false;
        }

        // Gujarati: U+0AFA to U+0AFF.
        if (bytes >= 0xabba && bytes <= 0xabbf) {
          return f_false;
        }

        // Gujarati: U+0A80, U+0A84, U+0A8E, U+0A92.
        if (bytes == 0xaa80 || bytes == 0xaa84 || bytes == 0xaa8e || bytes == 0xaa92) {
          return f_false;
        }

        // Gujarati: U+0AA9, U+0AB1, U+0AB4, U+0ABA.
        if (bytes == 0xaaa9 || bytes == 0xaab1 || bytes == 0xaab4 || bytes == 0xaaba) {
          return f_false;
        }

        // Gujarati: U+0ABB, U+0AC6, U+0ACA, U+0ACE.
        if (bytes == 0xaabb || bytes == 0xab86 || bytes == 0xab8a || bytes == 0xab8e) {
          return f_false;
        }

        // Gujarati: U+0ACF, U+0AE4, U+0AE5.
        if (bytes == 0xab8f || bytes == 0xaba4 || bytes == 0xaba5) {
          return f_false;
        }

        // Gurmukhi: U+0A0B to U+0A0E.
        if (bytes >= 0xa88b && bytes <= 0xa88e) {
          return f_false;
        }

        // Gurmukhi: U+0A43 to U+0A46.
        if (bytes >= 0xa983 && bytes <= 0xa986) {
          return f_false;
        }

        // Gurmukhi: U+0A4E to U+0A50.
        if (bytes >= 0xa98e && bytes <= 0xa990) {
          return f_false;
        }

        // Gurmukhi: U+0A52 to U+0A58.
        if (bytes >= 0xa992 && bytes <= 0xa998) {
          return f_false;
        }

        // Gurmukhi: U+0A5F to U+0A65.
        if (bytes >= 0xa99f && bytes <= 0xa9a5) {
          return f_false;
        }

        // Gurmukhi: U+0A76 to U+0A7F.
        if (bytes >= 0xa9b6 && bytes <= 0xa9bf) {
          return f_false;
        }

        // Gurmukhi: U+0A00, U+0A04, U+0A11, U+0A12.
        if (bytes == 0xa880 || bytes == 0xa884 || bytes == 0xa891 || bytes == 0xa892) {
          return f_false;
        }

        // Gurmukhi: U+0A29, U+0A31, U+0A34, U+0A37.
        if (bytes == 0xa8a9 || bytes == 0xa8b1 || bytes == 0xa8b4 || bytes == 0xa8b7) {
          return f_false;
        }

        // Gurmukhi: U+0A3A, U+0A3B, U+0A3D, U+0A49.
        if (bytes == 0xa8ba || bytes == 0xa8bb || bytes == 0xa8bd || bytes == 0xa989) {
          return f_false;
        }

        // Gurmukhi: U+0A4A, U+0A5D.
        if (bytes == 0xa98a || bytes == 0xa99d) {
          return f_false;
        }

        // Kannada: U+0CCE to U+0CD4.
        if (bytes >= 0xb38e && bytes <= 0xe394) {
          return f_false;
        }

        // Kannada: U+0CD7 to U+0CDD.
        if (bytes >= 0xb397 && bytes <= 0xb39d) {
          return f_false;
        }

        // Kannada: U+0CF3 to U+0CFF.
        if (bytes >= 0xb3b3 && bytes <= 0xb3bf) {
          return f_false;
        }

        // Kannada: U+0C84, U+0C8D, U+0C91, U+0CA9.
        if (bytes == 0xb284 || bytes == 0xb28d || bytes == 0xb291 || bytes == 0xb2a9) {
          return f_false;
        }

        // Kannada: U+0CB4, U+0CBA, U+0CBB, U+0CC5.
        if (bytes == 0xb284 || bytes == 0xb2ba || bytes == 0xb2bb || bytes == 0xb385) {
          return f_false;
        }

        // Kannada: U+0CC9, U+0CDF, U+0CE4, U+0CE5.
        if (bytes == 0xb389 || bytes == 0xb39f || bytes == 0xb3a4 || bytes == 0xb3a5) {
          return f_false;
        }

        // Kannada: U+0CF0.
        if (bytes == 0xb3b0) {
          return f_false;
        }

        // Lao: U+0E90 to U+0E93.
        if (bytes >= 0xba90 && bytes <= 0xba93) {
          return f_false;
        }

        // Lao: U+0EE0 to U+0EFF.
        if (bytes >= 0xbba0 && bytes <= 0xbbbf) {
          return f_false;
        }

        // Lao: U+0E80, U+0E83, U+0E85, U+0E86.
        if (bytes == 0xba80 || bytes == 0xba83 || bytes == 0xba85 || bytes == 0xba86) {
          return f_false;
        }

        // Lao: U+0E89, U+0E8B, U+0E8C, U+0E8E.
        if (bytes == 0xba89 || bytes == 0xba8b || bytes == 0xba8c || bytes == 0xba8e) {
          return f_false;
        }

        // Lao: U+0E8F, U+0E98, U+0EA0, U+0EA4.
        if (bytes == 0xba8f || bytes == 0xba98 || bytes == 0xbaa0 || bytes == 0xbaa4) {
          return f_false;
        }

        // Lao: U+0EA6, U+0EA8, U+0EA9, U+0EAC.
        if (bytes == 0xba86 || bytes == 0xba88 || bytes == 0xbaa9 || bytes == 0xbaac) {
          return f_false;
        }

        // Lao: U+0EBA, U+0EBE, U+0EBF, U+0EC5.
        if (bytes == 0xbaba || bytes == 0xbabe || bytes == 0xbabf || bytes == 0xbb85) {
          return f_false;
        }

        // Lao: U+0EC7, U+0ECE, U+0ECF, U+0EDA.
        if (bytes == 0xbb87 || bytes == 0xbb8e || bytes == 0xbb8f || bytes == 0xbb9a) {
          return f_false;
        }

        // Lao: U+0EDB.
        if (bytes == 0xbb9b) {
          return f_false;
        }

        // Malayalam: U+0D50 to U+0D53.
        if (bytes >= 0xb590 && bytes <= 0xb593) {
          return f_false;
        }

        // Malayalam: U+0D00, U+0D04, U+0D0D, U+0D11.
        if (bytes == 0xb480 || bytes == 0xb484 || bytes == 0xb48d || bytes == 0xb491) {
          return f_false;
        }

        // Malayalam: U+0D3B, U+0D3C, U+0D45, U+0D49.
        if (bytes == 0xb4bb || bytes == 0xb4bc || bytes == 0xb585 || bytes == 0xb589) {
          return f_false;
        }

        // Malayalam: U+0D64, U+0D65.
        if (bytes == 0xb5a4 || bytes == 0xb5a5) {
          return f_false;
        }

        // Mandaic: U+085C, U+085D, U+085F.
        if (bytes == 0xa19c || bytes == 0xa19d || bytes == 0xa19f) {
          return f_false;
        }

        // Oriya: U+0B50 to U+0B55.
        if (bytes >= 0xad90 && bytes <= 0xad95) {
          return f_false;
        }

        // Oriya: U+0B58 to U+0B5B.
        if (bytes >= 0xad98 && bytes <= 0xad9b) {
          return f_false;
        }

        // Oriya: U+0B78 to U+0B7F.
        if (bytes >= 0xadb8 && bytes <= 0xadbf) {
          return f_false;
        }

        // Oriya: U+0B00, U+0B04, U+0B0D.
        if (bytes == 0xac80 || bytes == 0xac84 || bytes == 0xac8d) {
          return f_false;
        }

        // Oriya: U+0B0E, U+0B11, U+0B29.
        if (bytes == 0xac8e || bytes == 0xac91 || bytes == 0xaca9) {
          return f_false;
        }

        // Oriya: U+0B31, U+0B34, U+0B3A.
        if (bytes == 0xacb1 || bytes == 0xacb4 || bytes == 0xacba) {
          return f_false;
        }

        // Oriya: U+0B3B, U+0B45, U+0B46.
        if (bytes == 0xacbb || bytes == 0xad85 || bytes == 0xad86) {
          return f_false;
        }

        // Oriya: U+0B49, U+0B4A, U+0B4E.
        if (bytes == 0xad89 || bytes == 0xad8a || bytes == 0xad8e) {
          return f_false;
        }

        // Oriya: U+0B4F, U+0B5E, U+0B64.
        if (bytes == 0xad8f || bytes == 0xad9e || bytes == 0xada4) {
          return f_false;
        }

        // Oriya: U+0B65.
        if (bytes == 0xada5) {
          return f_false;
        }

        // Sinhala: U+0D97 to U+0D99.
        if (bytes >= 0xb697 && bytes <= 0xb699) {
          return f_false;
        }

        // Sinhala: U+0DC7 to U+0DC9.
        if (bytes >= 0xb787 && bytes <= 0xb789) {
          return f_false;
        }

        // Sinhala: U+0DCB to U+0DCE.
        if (bytes >= 0xb78b && bytes <= 0xb78e) {
          return f_false;
        }

        // Sinhala: U+0DE0 to U+0DE5.
        if (bytes >= 0xb7a0 && bytes <= 0xb7a5) {
          return f_false;
        }

        // Sinhala: U+0DF5 to U+0DFF.
        if (bytes >= 0xb7b5 && bytes <= 0xb7bf) {
          return f_false;
        }

        // Sinhala: U+0D80, U+0D81, U+0D84.
        if (bytes == 0xb680 || bytes == 0xb681 || bytes == 0xb684) {
          return f_false;
        }

        // Sinhala: U+0DB2, U+0DBC, U+0DBE.
        if (bytes == 0xb6b2 || bytes == 0xb6bc || bytes == 0xb6be) {
          return f_false;
        }

        // Sinhala: U+0DBF, U+0DD5, U+0DD7.
        if (bytes == 0xb6bf || bytes == 0xb795 || bytes == 0xb797) {
          return f_false;
        }

        // Sinhala: U+0DF0, U+0DF1.
        if (bytes == 0xb7b0 || bytes == 0xb7b1) {
          return f_false;
        }

        // Samaritan: U+082E, U+082F, U+083F.
        if (bytes == 0xa0ae || bytes == 0xa0af || bytes == 0xa0bf) {
          return f_false;
        }

        // Tamil: U+0B80, U+0B81.
        if (bytes == 0xae80 || bytes == 0xae81) {
          return f_false;
        }

        // Tamil: U+0B8B to U+0B8D.
        if (bytes >= 0xae8b && bytes <= 0xae8d0) {
          return f_false;
        }

        // Tamil: U+0B96 to U+0B98.
        if (bytes >= 0xae96 && bytes <= 0xae98) {
          return f_false;
        }

        // Tamil: U+0BA0 to U+0BA2.
        if (bytes >= 0xaea0 && bytes <= 0xaea2) {
          return f_false;
        }

        // Tamil: U+0BA5 to U+0BA7.
        if (bytes >= 0xaea5 && bytes <= 0xaea7) {
          return f_false;
        }

        // Tamil: U+0BAB to U+0BAD.
        if (bytes >= 0xaeab && bytes <= 0xaead) {
          return f_false;
        }

        // Tamil: U+0BBA to U+0BBD.
        if (bytes >= 0xaeba && bytes <= 0xaebd) {
          return f_false;
        }

        // Tamil: U+0BC3 to U+0BC5.
        if (bytes >= 0xaf83 && bytes <= 0xaf85) {
          return f_false;
        }

        // Tamil: U+0BCE, U+0BCF.
        if (bytes == 0xaf8e || bytes == 0xaf8f) {
          return f_false;
        }

        // Tamil: U+0BD1 to U+0BD6.
        if (bytes >= 0xaf91 && bytes <= 0xaf96) {
          return f_false;
        }

        // Tamil: U+0BD8 to U+0BE5.
        if (bytes >= 0xaf98 && bytes <= 0xaf98) {
          return f_false;
        }

        // Tamil: U+0BFB to U+0BFF.
        if (bytes >= 0xafbb && bytes <= 0xafbf) {
          return f_false;
        }

        // Tamil: U+0B84, U+0B91, U+0BC9.
        if (bytes == 0xae84 || bytes == 0xae91 || bytes == 0xaf89) {
          return f_false;
        }

        // Telugu: U+0C3A to U+0C3C.
        if (bytes >= 0xb0ba && bytes <= 0xb0bc) {
          return f_false;
        }

        // Telugu: U+0C4E to U+0C54.
        if (bytes >= 0xb18e && bytes <= 0xb194) {
          return f_false;
        }

        // Telugu: U+0C5B to U+0C5F.
        if (bytes >= 0xb19b && bytes <= 0xb19f) {
          return f_false;
        }

        // Telugu: U+0C64, U+0C65.
        if (bytes == 0xb1a4 || bytes == 0xb1a5) {
          return f_false;
        }

        // Telugu: U+0C70 to U+0C77.
        if (bytes >= 0xb1b0 && bytes <= 0xb1b7) {
          return f_false;
        }

        // Telugu: U+0C04, U+0C0D, U+0C29.
        if (bytes == 0xb084 || bytes == 0xb08d || bytes == 0xb0a9) {
          return f_false;
        }

        // Telugu: U+0C45, U+0C49, U+0C57.
        if (bytes == 0xb185 || bytes == 0xb189 || bytes == 0xb197) {
          return f_false;
        }

        // Thai: U+0E5C to U+0E7F.
        if (bytes >= 0xb99c && bytes <= 0xb9bf) {
          return f_false;
        }

        // Thai: U+0E3B to U+0E3E.
        if (bytes >= 0xb8bb && bytes <= 0xb8be) {
          return f_false;
        }

        // Thai: U+0E00.
        if (bytes == 0xb880) {
          return f_false;
        }

        // Tibetan: U+0FDB to U+0FFF.
        if (bytes >= 0xbf9b && bytes <= 0xbfbf) {
          return f_false;
        }

        // Tibetan: U+0F6D to U+0F70.
        if (bytes >= 0xbdad && bytes <= 0xbdb0) {
          return f_false;
        }

        // Tibetan: U+0F48, U+0F98, U+0FBD, U+0FCD.
        if (bytes == 0xbd88 || bytes == 0xbe98 || bytes == 0xbebd || bytes == 0xbf8d) {
          return f_false;
        }
      }
      else if (byte_first == 0xe1) {
        // Batak: U+1BF4 to U+1BFB.
        if (bytes >= 0xafb4 && bytes <= 0xafbb) {
          return f_false;
        }

        // Buginese: U+1A1C to U+1A1D.
        if (bytes >= 0xa89c && bytes <= 0xa89d) {
          return f_false;
        }

        // Buhid: U+1754 to U+175F.
        if (bytes >= 0x9d94 && bytes <= 0x9d9f) {
          return f_false;
        }

        // Cherokee: U+13F6, U+13F7, U+13FE, U+13FF.
        if (bytes == 0x8fb6 || bytes <= 0x8fb7 || bytes <= 0x8fbe || bytes <= 0x8fbf) {
          return f_false;
        }

        // Combining Diacritical Marks Supplement: U+1ABF to U+1AFF.
        if (bytes >= 0xaabf && bytes <= 0xabbf) {
          return f_false;
        }

        // Cyrillic Extended-C: U+1C89 to U+1C8F.
        if (bytes >= 0xb289 && bytes <= 0xb28f) {
          return f_false;
        }

        // Ethiopic: U+137D to U+137F.
        if (bytes >= 0x8dbd && bytes <= 0x8dbf) {
          return f_false;
        }

        // Ethiopic: U+1249, U+124E, U+124F, U+1257.
        if (bytes == 0x8989 || bytes == 0x898e || bytes == 0x898f || bytes == 0x8997) {
          return f_false;
        }

        // Ethiopic: U+1259, U+125E, U+125F, U+1289.
        if (bytes == 0x8999 || bytes == 0x899e || bytes == 0x899f || bytes == 0x8a89) {
          return f_false;
        }

        // Ethiopic: U+128E, U+128F, U+12B1, U+12B6.
        if (bytes == 0x8a8e || bytes == 0x8a8f || bytes == 0x8ab1 || bytes == 0x8ab6) {
          return f_false;
        }

        // Ethiopic: U+12B7, U+12BF, U+12C1, U+12C6.
        if (bytes == 0x8ab7 || bytes == 0x8abf || bytes == 0x8b81 || bytes == 0x8b86) {
          return f_false;
        }

        // Ethiopic: U+12C7, U+12D7, U+1311, U+1316.
        if (bytes == 0x8b87 || bytes == 0x8b97 || bytes == 0x8c91 || bytes == 0x8c96) {
          return f_false;
        }

        // Ethiopic: U+1317, U+135B, U+135C.
        if (bytes == 0x8c97 || bytes == 0x8d9b || bytes == 0x8d9c) {
          return f_false;
        }

        // Ethiopic Supplement: U+139A to U+139F.
        if (bytes >= 0x8e9a && bytes <= 0x8e9f) {
          return f_false;
        }

        // Georgian: U+10C8 to U+10CC.
        if (bytes >= 0x8388 && bytes <= 0x838c) {
          return f_false;
        }

        // Georgian: U+10C6, U+10CE, U+10CF.
        if (bytes == 0x8386 || bytes == 0x838e || bytes == 0x838f) {
          return f_false;
        }

        // Greek Extended: U+1F16, U+1F17, U+1F1E, U+1F1F.
        if (bytes == 0xbc96 || bytes == 0xbc97 || bytes == 0xbc9e || bytes == 0xbc9f) {
          return f_false;
        }

        // Greek Extended: U+1F46, U+1F47, U+1F4E, U+1F4F.
        if (bytes == 0xbd86 || bytes == 0xbd87 || bytes == 0xbd8e || bytes == 0xbd8f) {
          return f_false;
        }

        // Greek Extended: U+1F58, U+1F5A, U+1F5C, U+1F5E.
        if (bytes == 0xbd98 || bytes == 0xbd9a || bytes == 0xbd9c || bytes == 0xbd9e) {
          return f_false;
        }

        // Greek Extended: U+1F7E, U+1F7F, U+1FB5, U+1FC5.
        if (bytes == 0xbdbe || bytes == 0xbdbf || bytes == 0xbeb5 || bytes == 0xbf85) {
          return f_false;
        }

        // Greek Extended: U+1FD4, U+1FD5, U+1FDC, U+1FF0.
        if (bytes == 0xbf94 || bytes == 0xbf95 || bytes == 0xbf9c || bytes == 0xbfb0) {
          return f_false;
        }

        // Greek Extended: U+1FF1, U+1FF5, U+1FFF.
        if (bytes == 0xbfb1 || bytes == 0xbfb5 || bytes == 0xbfbf) {
          return f_false;
        }

        // Hanunoo: U+1737 to U+173F.
        if (bytes >= 0x9cb7 && bytes <= 0x9cbf) {
          return f_false;
        }

        // Khmer: U+17EA to U+17EF.
        if (bytes >= 0x9faa && bytes <= 0x9faf) {
          return f_false;
        }

        // Khmer: U+17FA to U+17FF.
        if (bytes >= 0x9fba && bytes <= 0x9fbf) {
          return f_false;
        }

        // Khmer: U+17DE, U+17DF.
        if (bytes == 0x9f9e || bytes == 0x9f9f) {
          return f_false;
        }

        // Lepcha: U+1C38 to U+1C3A.
        if (bytes >= 0xb0b8 && bytes <= 0xb0ba) {
          return f_false;
        }

        // Lepcha: U+1C4A to U+1C4C.
        if (bytes >= 0xb18a && bytes <= 0xb18c) {
          return f_false;
        }

        // Limbu: U+192C to U+192F.
        if (bytes >= 0xa4ac && bytes <= 0xa4af) {
          return f_false;
        }

        // Limbu: U+193C to U+193F.
        if (bytes >= 0xa4bc && bytes <= 0xa4bf) {
          return f_false;
        }

        // Limbu: U+1941 to U+1943.
        if (bytes >= 0xa581 && bytes <= 0xa583) {
          return f_false;
        }

        // Limbu: U+191F.
        if (bytes == 0xa49f) {
          return f_false;
        }

        // New Tai Lue: U+19AC to U+19AF.
        if (bytes >= 0xa6ac && bytes <= 0xa6af) {
          return f_false;
        }

        // New Tai Lue: U+19CA to U+19CF.
        if (bytes >= 0xa78a && bytes <= 0xa78f) {
          return f_false;
        }

        // New Tai Lue: U+19DB to U+19DD.
        if (bytes >= 0xa79b && bytes <= 0xa79d) {
          return f_false;
        }

        // Ogham: U+169D to U+169F.
        if (bytes >= 0x9a9d && bytes <= 0x9a9f) {
          return f_false;
        }

        // Runic: U+16F9 to U+16FF.
        if (bytes >= 0x9bb9 && bytes <= 0x9bbf) {
          return f_false;
        }

        // Sundanese Supplement: U+1CC8 to U+1CCF.
        if (bytes >= 0xb388 && bytes <= 0xb38f) {
          return f_false;
        }

        // Tagalog: U+1715 to U+171f.
        if (bytes >= 0x9c95 && bytes <= 0x9c9f) {
          return f_false;
        }

        // Tagalog: U+170D
        if (bytes == 0x9c8d) {
          return f_false;
        }

        // Tagbanwa: U+1774 to U+177f.
        if (bytes >= 0x9db4 && bytes <= 0x9dbf) {
          return f_false;
        }

        // Tagbanwa: U+176D, U+1771
        if (bytes == 0x9dad || bytes == 0x9db1) {
          return f_false;
        }

        // Tai Lee: U+196E, U+196F.
        if (bytes == 0xa5ae || bytes == 0xa5ef) {
          return f_false;
        }

        // Tai Lee: U+1975 to U+197F.
        if (bytes >= 0xa5b5 && bytes <= 0xa5bf) {
          return f_false;
        }

        // Tai Tham: U+1A7D to U+1A7E.
        if (bytes >= 0xa9bd && bytes <= 0xa9be) {
          return f_false;
        }

        // Tai Tham: U+1A8A to U+1A8F.
        if (bytes >= 0xaa8a && bytes <= 0xaa8f) {
          return f_false;
        }

        // Tai Tham: U+1A9A to U+1A9F.
        if (bytes >= 0xaa9a && bytes <= 0xaa9f) {
          return f_false;
        }

        // Tai Tham: U+1AAE to U+1AAF.
        if (bytes >= 0xaaae && bytes <= 0xaaaf) {
          return f_false;
        }

        // Tai Tham: U+1A5F.
        if (bytes == 0xa99f) {
          return f_false;
        }

        // Unified Canadian Aboriginal Syllabics Extended: U+18F6 to U+18FF.
        if (bytes >= 0xa3b6 && bytes <= 0xa3bf) {
          return f_false;
        }

        // Vedic Extensions: U+1CF7 and U+1CFA to U+1CFF.
        if (bytes == 0xb3b7 || bytes >= 0xb3ba && bytes <= 0xb3bf) {
          return f_false;
        }
      }
      else if (byte_first == 0xe2) {
        // CJK Radicals Supplement: U+2E9A, U+2EF4 to U+2EFF.
        if (bytes == 0xba9a || bytes >= 0xbbb4 && bytes <= 0xbbbf) {
          return f_false;
        }

        // Combining Diacritical Marks for Symbols: U+20F1 to U+20FF.
        if (bytes >= 0x83b1 && bytes <= 0x83bf) {
          return f_false;
        }

        // Control Pictures: U+2427 to U+243F.
        if (bytes >= 0x90a7 && bytes <= 0x90bf) {
          return f_false;
        }

        // Coptic: U+2CF4 to U+2CF8.
        if (bytes >= 0xb3b4 && bytes <= 0xb3b8) {
          return f_false;
        }

        // Currency Symbols: U+20BF to U+20CF.
        if (bytes >= 0x82bf && bytes <= 0x838f) {
          return f_false;
        }

        // Ethiopic Extended: U+2D97 to U+2D9F.
        if (bytes >= 0xb697 && bytes <= 0xb69f) {
          return f_false;
        }

        // Ethiopic Extended: U+2DA7, U+2DAF, U+2DB7, U+2DBF.
        if (bytes == 0xb6a7 || bytes == 0xb6af || bytes == 0xb6b7 || bytes == 0xb6bf) {
          return f_false;
        }

        // Ethiopic Extended: U+2DC7, U+2DCF, U+2DD7, U+2DDF.
        if (bytes == 0xb787 || bytes == 0xb78f || bytes == 0xb797 || bytes == 0xb79f) {
          return f_false;
        }

        // General Punctuation: U+2065.
        if (bytes == 0x81a5) {
          return f_false;
        }

        // Georgian Supplement: U+2D28 to U+2D2C.
        if (bytes >= 0xb4a8 && bytes <= 0xb4ac) {
          return f_false;
        }

        // Georgian Supplement: U+2D26, U+2D2E, U+2D2F.
        if (bytes == 0xb4a6 || bytes == 0xb4ae || bytes == 0xb4af) {
          return f_false;
        }

        // Glagolitic: U+2C2F, U+2C5F.
        if (bytes == 0xb0af || bytes == 0xb19f) {
          return f_false;
        }

        // Ideographic Description Characters: U+2FFC to U+2FFF.
        if (bytes >= 0xbfbc && bytes <= 0xbfbf) {
          return f_false;
        }

        // Kangxi Radicals: U+2FD6 to U+2FDF.
        if (bytes >= 0xbf96 && bytes <= 0xbf9f) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2BBA to U+2BBC.
        if (bytes >= 0xaeba && bytes <= 0xaebc) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2BD2 to U+2BEB.
        if (bytes >= 0xaf92 && bytes <= 0xafab) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2BF0 to U+2BFF.
        if (bytes >= 0xafb0 && bytes <= 0xafbf) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2B74, U+2B75, U+2B96.
        if (bytes == 0xadb4 || bytes == 0xadb5 || bytes == 0xae96) {
          return f_false;
        }

        // Miscellaneous Symbols and Arrows: U+2B97, U+2BC9.
        if (bytes == 0xae97 || bytes == 0xaf89) {
          return f_false;
        }

        // Miscellaneous Technical: U+23FF.
        if (bytes == 0x8fbf) {
          return f_false;
        }

        // Number Forms: U+218C to U+218F.
        if (bytes >= 0x868c && bytes <= 0x868f) {
          return f_false;
        }

        // Optical Character Recognition: U+244B to U+245F.
        if (bytes >= 0x918b && bytes <= 0x919f) {
          return f_false;
        }

        // Superscripts and Subscripts: U+2072, U+2073, U+208F.
        if (bytes == 0x81b2 || bytes == 0x81b3 || bytes == 0x828f) {
          return f_false;
        }

        // Superscripts and Subscripts: U+209D to U+209F.
        if (bytes >= 0x829d && bytes <= 0x829f) {
          return f_false;
        }

        // Supplemental Punctuation: U+2E45 to U+2E7F.
        if (bytes >= 0xb985 && bytes <= 0xb9bf) {
          return f_false;
        }

        // Tifinagh: U+2D68 to U+2D6E.
        if (bytes >= 0xb5a8 && bytes <= 0xb5ae) {
          return f_false;
        }

        // Tifinagh: U+2D71 to U+2D7E.
        if (bytes >= 0xb5b1 && bytes <= 0xb5be) {
          return f_false;
        }
      }
      else if (byte_first == 0xe3) {
        // Bopomofo: U+3100 to U+3104.
        if (bytes >= 0x8480 && bytes <= 0x8484) {
          return f_false;
        }

        // Bopomofo: U+312E, U+312F.
        if (bytes == 0x84ae || bytes == 0x84af) {
          return f_false;
        }

        // Bopomofo Extended: U+31BB to U+31BF.
        if (bytes >= 0x86bb && bytes <= 0x86bf) {
          return f_false;
        }

        // CJK Strokes: U+31E4 to U+31EF.
        if (bytes >= 0x87a4 && bytes <= 0x87af) {
          return f_false;
        }

        // Enclosed CJK Letters and Months: U+321F, U+32FF.
        if (bytes == 0x889f || bytes == 0x8bbf) {
          return f_false;
        }

        // Hangul Compatibility Jamo: U+3130, U+318F.
        if (bytes == 0x84b0 || bytes == 0x868f) {
          return f_false;
        }

        // Hiragana: U+3040, U+3097, U+3098.
        if (bytes == 0x8180 || bytes == 0x8297 || bytes == 0x8298) {
          return f_false;
        }
      }
      else if (byte_first == 0xe4) {
        // CJK Unified Ideographs Extension A: U+4DB6, U+4DBF.
        if (bytes >= 0xb6b6 && bytes <= 0xb6bf) {
          return f_false;
        }
      }
      else if (byte_first == 0xe9) {
        // CJK Unified Ideographs: U+9FD6, U+9FFF.
        if (bytes >= 0xbf96 && bytes <= 0xbfbf) {
          return f_false;
        }
      }
      else if (byte_first == 0xea) {
        // Balinese: U+1B4C to U+1B4F.
        if (bytes >= 0xad8c && bytes <= 0xad8f) {
          return f_false;
        }

        // Balinese: U+1B7D to U+1B7F.
        if (bytes >= 0xadbd && bytes <= 0xadbf) {
          return f_false;
        }

        // Bamum: U+A6F8 to U+A6FF.
        if (bytes >= 0x9bb8 && bytes <= 0x9bbf) {
          return f_false;
        }

        // Cham: U+AA37 to U+AA3F.
        if (bytes >= 0xa8b7 && bytes <= 0xa8bf) {
          return f_false;
        }

        // Cham: U+AA4E, U+AA4F, U+AA5A, U+AA5B.
        if (bytes == 0xa98e || bytes == 0xa98f || bytes == 0xa99a || bytes == 0xa99b) {
          return f_false;
        }

        // Common Indic Number Forms: U+A83A, U+A83F.
        if (bytes == 0xa0ba || bytes == 0xa0bf) {
          return f_false;
        }

        // Ethiopic Extended-A: U+AB17 to U+AB1F.
        if (bytes >= 0xac97 && bytes <= 0xac9f) {
          return f_false;
        }

        // Ethiopic Extended-A: U+AB00, U+AB07, U+AB08, U+AB0F.
        if (bytes == 0xac80 || bytes == 0xac87 || bytes == 0xac88 || bytes == 0xac8f) {
          return f_false;
        }

        // Ethiopic Extended-A: U+AB10, U+AB27, U+AB2F.
        if (bytes == 0xac90 || bytes == 0xaca7 || bytes == 0xacaf) {
          return f_false;
        }

        // Hangul Jamo Extended-A: U+A97D to U+A97F.
        if (bytes >= 0xa5bd && bytes <= 0xa5bf) {
          return f_false;
        }

        // Javanese: U+A9CE, U+A9DA to U+A9DD.
        if (bytes == 0xa78e || bytes >= 0xa79a && bytes <= 0xa79d) {
          return f_false;
        }

        // Latin Extended-D: U+A7AF, U+A7B8 to U+A7F6.
        if (bytes == 0x9eaf || bytes >= 0x9eb8 && bytes <= 0x9fb6) {
          return f_false;
        }

        // Latin Extended-E: U+AB66 to U+AB6F.
        if (bytes >= 0xada6 && bytes <= 0xadaf) {
          return f_false;
        }

        // Meetei Mayek: U+ABFA to U+ABFF.
        if (bytes >= 0xafba && bytes <= 0xafbf) {
          return f_false;
        }

        // Meetei Mayek: U+ABEE, U+ABEF.
        if (bytes == 0xafae || bytes == 0xafaf) {
          return f_false;
        }

        // Meetei Mayek Extensions: U+AAF7 to U+AAFF.
        if (bytes >= 0xabb7 && bytes <= 0xabbf) {
          return f_false;
        }

        // Myanmar Extended-B: U+A9FF.
        if (bytes == 0xa7bf) {
          return f_false;
        }

        // Phags-pa: U+A878, U+A87F.
        if (bytes >= 0xa1b8 && bytes <= 0xa1bf) {
          return f_false;
        }

        // Rejang: U+A954 to U+A95E.
        if (bytes >= 0xa594 && bytes <= 0xa59e) {
          return f_false;
        }

        // Syloti Nagri: U+A82C to U+A82F.
        if (bytes >= 0xa0ac && bytes <= 0xa0af) {
          return f_false;
        }

        // Saurashtra: U+A8C6 to U+A8CD.
        if (bytes >= 0xa386 && bytes <= 0xa38d) {
          return f_false;
        }

        // Saurashtra: U+A8DA to U+A8DF.
        if (bytes >= 0xa39a && bytes <= 0xa39f) {
          return f_false;
        }

        // Tai Viet: U+AAC3 to U+AADA.
        if (bytes >= 0xab83 && bytes <= 0xab9a) {
          return f_false;
        }

        // Vai: U+A62C to U+A63F.
        if (bytes >= 0x98ac && bytes <= 0x98bf) {
          return f_false;
        }

        // Yi Radicals: U+A4C7 to U+A4CF.
        if (bytes >= 0x9387 && bytes <= 0x938f) {
          return f_false;
        }

        // Yi Syllables: U+A48D to U+A48F.
        if (bytes >= 0x928d && bytes <= 0x928f) {
          return f_false;
        }
      }
      else if (byte_first == 0xed) {
        // Hangul Jamo Extended-B: U+D7C7 to U+D7CA.
        if (bytes >= 0x9f87 && bytes <= 0x9f8a) {
          return f_false;
        }

        // Hangul Jamo Extended-B: U+D7FC to U+D7FF.
        if (bytes >= 0x9fbc && bytes <= 0x9fbf) {
          return f_false;
        }

        // Hangul Syllables: U+D7A4 to U+D7AF.
        if (bytes >= 0x9ea4 && bytes <= 0x9eaf) {
          return f_false;
        }

        // Low Surrogates: U+DC00 to U+DFFF.
        if (bytes >= 0xbfb0 && bytes <= 0xbfbf) {
          return f_false;
        }

        // High Surrogates: U+D800 to U+DB7F.
        if (bytes >= 0xa080 && bytes <= 0xadbf) {
          return f_false;
        }

        // High Private Use Surrogates: U+DB80 to U+DBFF.
        if (bytes >= 0xae80 && bytes <= 0xafbf) {
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

        // Alphabetic Presentation Forms: U+FB07 to U+FB12.
        if (bytes >= 0xac87 && bytes <= 0xac92) {
          return f_false;
        }

        // Alphabetic Presentation Forms: U+FB18 to U+FB1C.
        if (bytes >= 0xac98 && bytes <= 0xac9c) {
          return f_false;
        }

        // Arabic Presentation Forms: U+FB37, U+FB3D, U+FB3F.
        if (bytes == 0xacb7 || bytes == 0xacbd || bytes == 0xacbf) {
          return f_false;
        }

        // Arabic Presentation Forms: U+FB42, U+FB45.
        if (bytes == 0xad82 || bytes == 0xad85) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FBC2 to U+FBD2.
        if (bytes >= 0xaf82 && bytes <= 0xaf92) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FD40 to U+FD4F.
        if (bytes >= 0xb580 && bytes <= 0xb58f) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FDC8 to U+FDEF.
        if (bytes >= 0xb788 && bytes <= 0xb7af) {
          return f_false;
        }

        // Arabic Presentation Forms-A: U+FD90, U+FD91, U+FDFE, U+FDFF.
        if (bytes == 0xb690 || bytes == 0xb691 || bytes == 0xb7be || bytes == 0xb7bf) {
          return f_false;
        }

        // Arabic Presentation Forms-B: U+FE75, U+FEFD, U+FEFE.
        if (bytes == 0xb9b5 || bytes == 0xbbbd || bytes == 0xbbbe) {
          return f_false;
        }

        // CJK Compatibility Ideographs: U+FADA to U+FAFF.
        if (bytes >= 0xab9a && bytes <= 0xabbf) {
          return f_false;
        }

        // CJK Compatibility Ideographs: U+FA6E, U+FA6F.
        if (bytes == 0xa9ae || bytes == 0xa9af) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FFDD to U+FFDF.
        if (bytes >= 0xbf9d && bytes <= 0xbf9f) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FF00, U+FFBF, U+FFC0, U+FFC1.
        if (bytes == 0xbc80 || bytes == 0xbebf || bytes == 0xbf80 || bytes == 0xbf81) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FFC8, U+FFC9, U+FFD0, U+FFD1.
        if (bytes == 0xbf88 || bytes == 0xbf89 || bytes == 0xbf90 || bytes == 0xbf91) {
          return f_false;
        }

        // Halfwidth and Fullwidth Forms: U+FFD8, U+FFD9, U+FFE7, U+FFEF.
        if (bytes == 0xbf98 || bytes == 0xbf99 || bytes == 0xbfa7 || bytes == 0xbfaf) {
          return f_false;
        }

        // Small Form Variants: U+FE6C to U+FE6F.
        if (bytes >= 0xb9ac && bytes <= 0xb9af) {
          return f_false;
        }

        // Small Form Variants: U+FE53, U+FE67.
        if (bytes == 0xb993 || bytes == 0xb9a7) {
          return f_false;
        }

        // Vertical Forms: U+FE10 to U+FE1F.
        if (bytes >= 0xb890 && bytes <= 0xb89f) {
          return f_false;
        }

        // Specials: U+FFF0 to U+FFF8.
        if (bytes >= 0xbfb0 && bytes <= 0xbfb8) {
          return f_false;
        }

        // Specials: U+FFFE to U+FFFF.
        if (bytes >= 0xbfbe && bytes <= 0xbfbf) {
          return f_false;
        }
      }
    }
    else if (width == 4) {
      uint16_t bytes = (uint16_t) (character & 0x0000ffff);
      uint8_t byte_second = f_macro_utf_character_to_char_2(character);

      if (byte_first == 0xf0) {
        if (byte_second == 0x90) {
          // Aegean Numbers: U+10103 to U+10106.
          if (bytes >= 0x8483 && bytes <= 0x8486) {
            return f_false;
          }

          // Aegean Numbers: U+10134 to U+10136.
          if (bytes >= 0x84b4 && bytes <= 0x84b6) {
            return f_false;
          }

          // Ancient Greek Numbers: U+1018F.
          if (bytes == 0x868f) {
            return f_false;
          }

          // Ancient Symbols: U+1019C to U+1019F.
          if (bytes >= 0x869c && bytes <= 0x869f) {
            return f_false;
          }

          // Ancient Symbols: U+101A1 to U+101CF.
          if (bytes >= 0x86a1 && bytes <= 0x878f) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE3C to U+1EE41.
          if (bytes >= 0xb8bc && bytes <= 0xb981) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE43 to U+1EE46.
          if (bytes >= 0xb983 && bytes <= 0xb986) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE9C to U+1EE9F.
          if (bytes >= 0xba9c && bytes <= 0xba9f) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EEBC to U+1EEEF.
          if (bytes >= 0xbabc && bytes <= 0xbbaf) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EEF2 to U+1EEFF.
          if (bytes >= 0xbbb2 && bytes <= 0xbbbf) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE04, U+1EE20, U+1EE23, U+1EE25.
          if (bytes == 0xb884 || bytes == 0xb8a0 || bytes == 0xb8a3 || bytes == 0xb8a5) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE26, U+1EE28, U+1EE33, U+1EE38.
          if (bytes == 0xb8a6 || bytes == 0xb8a8 || bytes == 0xb8b3 || bytes == 0xb8b8) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE3A, U+1EE48, U+1EE4A, U+1EE4C.
          if (bytes == 0xb8ba || bytes == 0xb988 || bytes == 0xb98a || bytes == 0xb98c) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE50, U+1EE53, U+1EE55, U+1EE56.
          if (bytes == 0xb990 || bytes == 0xb993 || bytes == 0xb995 || bytes == 0xb996) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE58, U+1EE5A, U+1EE5C, U+1EE5E.
          if (bytes == 0xb998 || bytes == 0xb99a || bytes == 0xb99c || bytes == 0xb99e) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE60, U+1EE63, U+1EE65, U+1EE66.
          if (bytes == 0xb9a0 || bytes == 0xb9a3 || bytes == 0xb9a5 || bytes == 0xb9a6) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE6B, U+1EE73, U+1EE78, U+1EE7D.
          if (bytes == 0xb9ab || bytes == 0xb9b3 || bytes == 0xb9b8 || bytes == 0xb9bd) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EE7F, U+1EE8A, U+1EEA0, U+1EEA4.
          if (bytes == 0xb9bf || bytes == 0xba8a || bytes == 0xbaa0 || bytes == 0xbaa4) {
            return f_false;
          }

          // Arabic Mathematical Alphabetic Symbols: U+1EEAA.
          if (bytes == 0xbaaa) {
            return f_false;
          }

          // Avestan: U+10B36 to U+10B38.
          if (bytes >= 0xacb6 && bytes <= 0xacb8) {
            return f_false;
          }

          // Carian: U+102D1 to U+102DF.
          if (bytes >= 0x8b91 && bytes <= 0x8b9f) {
            return f_false;
          }

          // Caucasian Albanian: U+10564 to U+1056E.
          if (bytes >= 0x95a4 && bytes <= 0x95ae) {
            return f_false;
          }

          // Coptic Epact Numbers: U+102FC to U+102FF.
          if (bytes >= 0x8bbc && bytes <= 0x8bbf) {
            return f_false;
          }

          // Cypriot Syllabary: U+10839 to U+1083B.
          if (bytes >= 0xa0b9 && bytes <= 0xa0bb) {
            return f_false;
          }

          // Cypriot Syllabary: U+10806, U+10807, U+10809.
          if (bytes == 0xa086 || bytes == 0xa087 || bytes == 0xa089) {
            return f_false;
          }

          // Cypriot Syllabary: U+10836, U+1083D, U+1083E.
          if (bytes == 0xa0b6 || bytes == 0xa0bd || bytes == 0xa0be) {
            return f_false;
          }

          // Elbasan: U+10528 to U+1052F.
          if (bytes >= 0x94a8 && bytes <= 0x94af) {
            return f_false;
          }

          // Gothic: U+1034B to U+1034F.
          if (bytes >= 0x8d8b && bytes <= 0x8d8f) {
            return f_false;
          }

          // Hatran: U+108F3.
          if (bytes == 0xa3b3) {
            return f_false;
          }

          // Hatran: U+108F6 to U+108FA.
          if (bytes >= 0xa3b6 && bytes <= 0xa3ba) {
            return f_false;
          }

          // Imperial Aramaic: U+10856.
          if (bytes == 0xa196) {
            return f_false;
          }

          // Inscriptional Pahlavi: U+10B73 to U+10B77.
          if (bytes >= 0xadb3 && bytes <= 0xadb7) {
            return f_false;
          }

          // Inscriptional Parthian: U+10B56 to U+10B57.
          if (bytes >= 0xad96 && bytes <= 0xad97) {
            return f_false;
          }

          // Kharoshthi: U+10A07 to U+10A0B.
          if (bytes >= 0xa887 && bytes <= 0xa88b) {
            return f_false;
          }

          // Kharoshthi: U+10A34 to U+10A37.
          if (bytes >= 0xa8b4 && bytes <= 0xa8b7) {
            return f_false;
          }

          // Kharoshthi: U+10A3B to U+10A3E.
          if (bytes >= 0xa8bb && bytes <= 0xa8be) {
            return f_false;
          }

          // Kharoshthi: U+10A48 to U+10A4F.
          if (bytes >= 0xa988 && bytes <= 0xa98f) {
            return f_false;
          }

          // Kharoshthi: U+10A59 to U+10A5F.
          if (bytes >= 0xa999 && bytes <= 0xa99f) {
            return f_false;
          }

          // Kharoshthi: U+10A04, U+10A14, U+10A18.
          if (bytes == 0xa884 || bytes == 0xa894 || bytes == 0xa898) {
            return f_false;
          }

          // Linear A: U+10737 to U+1073F.
          if (bytes >= 0x9cb7 && bytes <= 0x9cbf) {
            return f_false;
          }

          // Linear A: U+10756 to U+1075F.
          if (bytes >= 0x9d96 && bytes <= 0x9d9f) {
            return f_false;
          }

          // Linear A: U+10768 to U+1077F.
          if (bytes >= 0x9da8 && bytes <= 0x9dbf) {
            return f_false;
          }

          // Linear B Ideograms: U+100FB to U+100FF.
          if (bytes >= 0x83bb && bytes <= 0x83bf) {
            return f_false;
          }

          // Linear B Syllabary: U+1005E to U+1007F.
          if (bytes >= 0x819e && bytes <= 0x81bf) {
            return f_false;
          }

          // Linear B Syllabary: U+1000C, U+10027, U+1003B.
          if (bytes == 0x808c || bytes == 0x80a7 || bytes == 0x80bb) {
            return f_false;
          }

          // Linear B Syllabary: U+1003E, U+1004E, U+1004F.
          if (bytes == 0x80be || bytes == 0x818e || bytes == 0x818f) {
            return f_false;
          }

          // Lycian: U+1029D to U+1029F.
          if (bytes >= 0x8a9d && bytes <= 0x8a9f) {
            return f_false;
          }

          // Lydian: U+1093A to U+1093E.
          if (bytes >= 0xa4ba && bytes <= 0xa4be) {
            return f_false;
          }

          // Manichaean: U+10AE7 to U+10AEA.
          if (bytes >= 0xaba7 && bytes <= 0xabaa) {
            return f_false;
          }

          // Manichaean: U+10AF7 to U+10AFF.
          if (bytes >= 0xabb7 && bytes <= 0xabbf) {
            return f_false;
          }

          // Meroitic Cursive: U+109B8 to U+109BB.
          if (bytes >= 0xa6b8 && bytes <= 0xa6bb) {
            return f_false;
          }

          // Meroitic Cursive: U+109D0, U+109D1.
          if (bytes == 0xa790 || bytes == 0xa791) {
            return f_false;
          }

          // Nabataean: U+1089F to U+108A6.
          if (bytes >= 0xa29f && bytes <= 0xa2a6) {
            return f_false;
          }

          // Old Hungarian: U+10CB3 to U+10CBF.
          if (bytes >= 0xb2b3 && bytes <= 0xb2bf) {
            return f_false;
          }

          // Old Hungarian: U+10CF3 to U+10CF9.
          if (bytes >= 0xb3b3 && bytes <= 0xb3b9) {
            return f_false;
          }

          // Old Italic: U+10324 to U+1032F.
          if (bytes >= 0x8ca4 && bytes <= 0x8caf) {
            return f_false;
          }

          // Old Permic: U+1037B to U+1037F.
          if (bytes >= 0x8dbb && bytes <= 0x8dbf) {
            return f_false;
          }

          // Old Persian: U+103C4 to U+103C7.
          if (bytes >= 0x8f84 && bytes <= 0x8f87) {
            return f_false;
          }

          // Old Persian: U+103D6 to U+103DF.
          if (bytes >= 0x8f96 && bytes <= 0x8f9f) {
            return f_false;
          }

          // Old Turkic: U+10C49 to U+10C4F.
          if (bytes >= 0xb189 && bytes <= 0xb18f) {
            return f_false;
          }

          // Osage: U+104D4 to U+104D7.
          if (bytes >= 0x9394 && bytes <= 0x9397) {
            return f_false;
          }

          // Osage: U+104FC to U+104FF.
          if (bytes >= 0x93bc && bytes <= 0x93bf) {
            return f_false;
          }

          // Osmanya: U+104AA to U+104AF.
          if (bytes >= 0x92aa && bytes <= 0x92af) {
            return f_false;
          }

          // Osmanya: U+1049E to U+1049F.
          if (bytes == 0x929e || bytes == 0x929f) {
            return f_false;
          }

          // Phaistos Disc: U+101FE, U+101FF.
          if (bytes == 0x87be || bytes == 0x87bf) {
            return f_false;
          }

          // Phoenician: U+1091C to U+1091E.
          if (bytes >= 0xa49c && bytes <= 0xa49e) {
            return f_false;
          }

          // Psalter Pahlavi: U+10B92 to U+10B98.
          if (bytes >= 0xae92 && bytes <= 0xae98) {
            return f_false;
          }

          // Psalter Pahlavi: U+10B9D to U+10BA8.
          if (bytes >= 0xae9d && bytes <= 0xaea8) {
            return f_false;
          }

          // Rumi Numeral Symbols: U+10E7F.
          if (bytes == 0xb9bf) {
            return f_false;
          }

          // Ugaritic: U+1039E.
          if (bytes == 0x8e9e) {
            return f_false;
          }
        }
        else if (byte_second == 0x91) {
          // Ahom: U+1172C to U+1172F.
          if (bytes >= 0x9cac && bytes <= 0x9caf) {
            return f_false;
          }

          // Ahom: U+1171A to U+1171C.
          if (bytes >= 0x9c9a && bytes <= 0x9c9c) {
            return f_false;
          }

          // Bhaiksuki: U+11C46 to U+11C4F.
          if (bytes >= 0xb186 && bytes <= 0xb18f) {
            return f_false;
          }

          // Bhaiksuki: U+11C6D to U+11C6F.
          if (bytes >= 0xb1ad && bytes <= 0xb1af) {
            return f_false;
          }

          // Bhaiksuki: U+11C09, U+11C37.
          if (bytes == 0xb089 || bytes == 0xb0b7) {
            return f_false;
          }

          // Brahmi: U+1104E to U+11051.
          if (bytes >= 0x818e && bytes <= 0x8191) {
            return f_false;
          }

          // Brahmi: U+11070 to U+1107E.
          if (bytes >= 0x81b0 && bytes <= 0x81be) {
            return f_false;
          }

          // Chakma: U+11135, U+11144 to U+1114F.
          if (bytes == 0x84b5 || bytes >= 0x8584 && bytes <= 0x858f) {
            return f_false;
          }

          // Grantha: U+11351 to U+11356.
          if (bytes >= 0x8d91 && bytes <= 0x8d96) {
            return f_false;
          }

          // Grantha: U+11358 to U+1135C.
          if (bytes >= 0x8d98 && bytes <= 0x8d9c) {
            return f_false;
          }

          // Grantha: U+1136D to U+1136F.
          if (bytes >= 0x8dad && bytes <= 0x8daf) {
            return f_false;
          }

          // Grantha: U+11375 to U+1137F.
          if (bytes >= 0x8db5 && bytes <= 0x8dbf) {
            return f_false;
          }

          // Grantha: U+11304, U+1130D, U+1130E, U+11311.
          if (bytes == 0x8c84 || bytes == 0x8c8d || bytes == 0x8c8e || bytes == 0x8c91) {
            return f_false;
          }

          // Grantha: U+11312, U+11329, U+11331, U+11334.
          if (bytes == 0x8c92 || bytes == 0x8ca9 || bytes == 0x8cb1 || bytes == 0x8cb4) {
            return f_false;
          }

          // Grantha: U+1133A, U+1133B, U+11345, U+11346.
          if (bytes == 0x8cba || bytes == 0x8cbb || bytes == 0x8d85 || bytes == 0x8d86) {
            return f_false;
          }

          // Grantha: U+11349, U+1134A, U+1134E, U+1134F.
          if (bytes == 0x8d89 || bytes == 0x8d8a || bytes == 0x8d8e || bytes == 0x8d8f) {
            return f_false;
          }

          // Grantha: U+11364, U+11365.
          if (bytes == 0x8da4 || bytes == 0x8da5) {
            return f_false;
          }

          // Kaithi: U+110C2 to U+110CF.
          if (bytes >= 0x8382 && bytes <= 0x838f) {
            return f_false;
          }

          // Khojki: U+1123F to U+1124F.
          if (bytes >= 0x88bf && bytes <= 0x898f) {
            return f_false;
          }

          // Khojki: U+11212.
          if (bytes == 0x8892) {
            return f_false;
          }

          // Khudawadi: U+112EB to U+112EF.
          if (bytes >= 0x8bab && bytes <= 0x8baf) {
            return f_false;
          }

          // Khudawadi: U+112FA to U+112FF.
          if (bytes >= 0x8bba && bytes <= 0x8bbf) {
            return f_false;
          }

          // Mahajani: U+11177 to U+1117F.
          if (bytes >= 0x85b7 && bytes <= 0x85bf) {
            return f_false;
          }

          // Marchen: U+11CB7 to U+11CBF.
          if (bytes >= 0xb2b7 && bytes <= 0xb2bf) {
            return f_false;
          }

          // Marchen: U+11C90, U+11C91, U+11CA8.
          if (bytes == 0xb290 || bytes == 0xb291 || bytes == 0xb2a8) {
            return f_false;
          }

          // Modi: U+11645 to U+1164F.
          if (bytes >= 0x9985 && bytes <= 0x998f) {
            return f_false;
          }

          // Modi: U+1165A to U+1165F.
          if (bytes >= 0x999a && bytes <= 0x999f) {
            return f_false;
          }

          // Mongolian Supplement: U+1166D to U+1167F.
          if (bytes >= 0x99ad && bytes <= 0x99bf) {
            return f_false;
          }

          // Multani: U+112AA to U+112AF.
          if (bytes >= 0x8aaa && bytes <= 0x8aaf) {
            return f_false;
          }

          // Multani: U+11287, U+11289, U+1128E, U+1129E.
          if (bytes == 0x8a87 || bytes == 0x8a89 || bytes == 0x8a8e || bytes == 0x8a9e) {
            return f_false;
          }

          // Newa: U+1145E to U+1147F.
          if (bytes >= 0x919e && bytes <= 0x91bf) {
            return f_false;
          }

          // Newa: U+1145A, U+1145C.
          if (bytes == 0x919a || bytes == 0x919c) {
            return f_false;
          }

          // Pau Cin Hau: U+11AF9, U+11AFF.
          if (bytes >= 0xabbf && bytes <= 0xabbf) {
            return f_false;
          }

          // Sharada: U+111CE, U+111CF.
          if (bytes == 0x878e || bytes == 0x878f) {
            return f_false;
          }

          // Siddham: U+115DE to U+115FF.
          if (bytes >= 0x979e && bytes <= 0x97bf) {
            return f_false;
          }

          // Siddham: U+115B6, U+115B7.
          if (bytes == 0x96b6 || bytes == 0x96b7) {
            return f_false;
          }

          // Sinhala Archaic Numbers: U+111F5 to U+111FF.
          if (bytes >= 0x87b5 && bytes <= 0x87bf) {
            return f_false;
          }

          // Sinhala Archaic Numbers: U+1F93F.
          if (bytes == 0x87a0) {
            return f_false;
          }

          // Sora Sompeng: U+110E9 to U+110EF.
          if (bytes >= 0x83a9 && bytes <= 0x83af) {
            return f_false;
          }

          // Sora Sompeng: U+110FA to U+110FF.
          if (bytes >= 0x83ba && bytes <= 0x83bf) {
            return f_false;
          }

          // Takri: U+116B8 to U+116BF.
          if (bytes >= 0x9ab8 && bytes <= 0x9abf) {
            return f_false;
          }

          // Takri: U+116CA to U+116CF.
          if (bytes >= 0x9b8a && bytes <= 0x9b8f) {
            return f_false;
          }

          // Tirhuta: U+114C8 to U+114CF.
          if (bytes >= 0x9388 && bytes <= 0x938f) {
            return f_false;
          }

          // Tirhuta: U+114DA to U+114DF.
          if (bytes >= 0x939a && bytes <= 0x939f) {
            return f_false;
          }

          // Warang Citi: U+118F3 to U+118FE.
          if (bytes >= 0xa3b3 && bytes <= 0xa3be) {
            return f_false;
          }
        }
        else if (byte_second == 0x92) {
          // Cuneiform: U+1239A to U+123FF.
          if (bytes >= 0x8e9a && bytes <= 0x8fbf) {
            return f_false;
          }

          // Cuneiform Numbers and Punctuation: U+1246F, U+12475 to U+1247F.
          if (bytes == 0x91af || bytes >= 0x91b5 && bytes <= 0x91bf) {
            return f_false;
          }

          // Early Dynastic Cuneiform: U+12544 to U+1254F.
          if (bytes >= 0x9584 && bytes <= 0x958f) {
            return f_false;
          }
        }
        else if (byte_second == 0x93) {
          // Egyptian Hieroglyphs: U+1342F.
          if (bytes == 0x90af) {
            return f_false;
          }
        }
        else if (byte_second == 0x94) {
          // Anatolian Hieroglyphs: U+14647 to U+1467F.
          if (bytes >= 0x9987 && bytes <= 0x99bf) {
            return f_false;
          }
        }
        else if (byte_second == 0x96) {
          // Bamum Supplement: U+16A39 to U+16A3F.
          if (bytes >= 0xa8b9 && bytes <= 0xa8bf) {
            return f_false;
          }

          // Bassa Vah: U+16AF6 to U+16AFF.
          if (bytes >= 0xabb6 && bytes <= 0xabbf) {
            return f_false;
          }

          // Bassa Vah: U+16AEE, U+16AEF.
          if (bytes == 0xabae || bytes == 0xabaf) {
            return f_false;
          }

          // Ideographic Symbols and Punctuation: U+16FE1 to U+16FFF.
          if (bytes >= 0xbfa1 && bytes <= 0xbfbf) {
            return f_false;
          }

          // Miao: U+16F45 to U+16F4F.
          if (bytes >= 0xbd85 && bytes <= 0xbd8f) {
            return f_false;
          }

          // Miao: U+16F7F to U+16F8E.
          if (bytes >= 0xbdbf && bytes <= 0xbe8e) {
            return f_false;
          }

          // Mro: U+16A6A to U+16A6D.
          if (bytes >= 0xa9aa && bytes <= 0xa9ad) {
            return f_false;
          }

          // Mro: U+16A5F.
          if (bytes == 0xa99f) {
            return f_false;
          }

          // Pahawh Hmong: U+16B46 to U+16B4F.
          if (bytes >= 0xad86 && bytes <= 0xad8f) {
            return f_false;
          }

          // Pahawh Hmong: U+16B78 to U+16B7C.
          if (bytes >= 0xadb8 && bytes <= 0xadbc) {
            return f_false;
          }

          // Pahawh Hmong: U+16B5A, U+16B62.
          if (bytes == 0xad9a || bytes == 0xada2) {
            return f_false;
          }
        }
        else if (byte_second == 0x9b) {
          // Duployan: U+1BC6B to U+1BC6F.
          if (bytes >= 0xb1ab && bytes <= 0xb1af) {
            return f_false;
          }

          // Duployan: U+1BC7D to U+1BC7F.
          if (bytes >= 0xb1bd && bytes <= 0xb1bf) {
            return f_false;
          }

          // Duployan: U+1BC89 to U+1BC8F.
          if (bytes >= 0xb289 && bytes <= 0xb28f) {
            return f_false;
          }

          // Duployan: U+1BC9A to U+1BC9B.
          if (bytes == 0xb29a || bytes == 0xb29b) {
            return f_false;
          }

          // Kana Supplement: U+1B002 to U+1B0FF.
          if (bytes >= 0x8082 && bytes <= 0x83bf) {
            return f_false;
          }

          // Shorthand Format Controls: U+1BCA4 to U+1BCAF.
          if (bytes >= 0xb2a4 && bytes <= 0xb2af) {
            return f_false;
          }
        }
        else if (byte_second == 0x9d) {
          // Ancient Greek Musical Notation: U+1D246 to U+1D24F.
          if (bytes >= 0x8986 && bytes <= 0x898f) {
            return f_false;
          }

          // Byzantine Musical Symbols: U+1D0F6 to U+1D0FF.
          if (bytes >= 0x83b6 && bytes <= 0x83bf) {
            return f_false;
          }

          // Counting Rod Numerals: U+1D372 to U+1D37F.
          if (bytes >= 0x8db2 && bytes <= 0x8dbf) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D547 to U+1D549.
          if (bytes >= 0x9587 && bytes <= 0x9589) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D455, U+1D49D, U+1D4A0, U+1D4A1.
          if (bytes == 0x9195 || bytes == 0x929d || bytes == 0x92a0 || bytes == 0x92a1) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D4A3, U+1D4A4, U+1D4A7, U+1D4A8.
          if (bytes == 0x92a3 || bytes == 0x92a4 || bytes == 0x92a7 || bytes == 0x92a8) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D4AD, U+1D4BA, U+1D4BC, U+1D4C4.
          if (bytes == 0x92ad || bytes == 0x92ba || bytes == 0x92bc || bytes == 0x9384) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D506, U+1D50B, U+1D50C, U+1D515.
          if (bytes == 0x9486 || bytes == 0x948b || bytes == 0x948c || bytes == 0x9495) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D51D, U+1D53A, U+1D53F, U+1D545.
          if (bytes == 0x949d || bytes == 0x94ba || bytes == 0x94bf || bytes == 0x9585) {
            return f_false;
          }

          // Mathematical Alphanumeric Symbols: U+1D551, U+1D6A6, U+1D7CC, U+1D7CD.
          if (bytes == 0x9591 || bytes == 0x9aa6 || bytes == 0x9aa7 || bytes == 0x9f8c || bytes == 0x9f8d) {
            return f_false;
          }

          // Musical Symbols: U+1D1E9 to U+1D1FF.
          if (bytes >= 0x87a9 && bytes <= 0x87bf) {
            return f_false;
          }

          // Musical Symbols: U+1D127, U+1D128.
          if (bytes == 0x84a7 || bytes == 0x84a8) {
            return f_false;
          }

          // Sutton SignWriting: U+1DA8C to U+1DA9A.
          if (bytes >= 0xaa8c && bytes <= 0xaa9a) {
            return f_false;
          }

          // Tai Xuan Jing Symbols: U+1D357 to U+1D35F.
          if (bytes >= 0x8d97 && bytes <= 0x8d9f) {
            return f_false;
          }
        }
        else if (byte_second == 0x9e) {
          // Adlam: U+1E94B to U+1E94F.
          if (bytes >= 0xa58b && bytes <= 0xa58f) {
            return f_false;
          }

          // Adlam: U+1E95A to U+1E95D.
          if (bytes >= 0xa59a && bytes <= 0xa59d) {
            return f_false;
          }

          // Glagolitic Supplement: U+1E02B to U+1E02F.
          if (bytes >= 0x80ab && bytes <= 0x80af) {
            return f_false;
          }

          // Glagolitic Supplement: U+1E007, U+1E019, U+1E01A.
          if (bytes == 0x8087 || bytes == 0x8099 || bytes == 0x809a) {
            return f_false;
          }

          // Glagolitic Supplement: U+1E022, U+1E025.
          if (bytes == 0x80a2 || bytes == 0x80a5) {
            return f_false;
          }

          // Mende Kikakui: U+1E8D7 to U+1E8DF.
          if (bytes >= 0xa397 && bytes <= 0xa39f) {
            return f_false;
          }

          // Mende Kikakui: U+1E8C5, U+1E8C6.
          if (bytes == 0xa385 || bytes == 0xa386) {
            return f_false;
          }
        }
        else if (byte_second == 0x9f) {
          // Alchemical Symbols: U+1F774 to U+1F77F.
          if (bytes >= 0x9db4 && bytes <= 0x9dbf) {
            return f_false;
          }

          // Domino Tiles: U+1F094 to U+1F09F.
          if (bytes >= 0x8294 && bytes <= 0x829f) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F10D to U+1F10F.
          if (bytes >= 0x848d && bytes <= 0x848f) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F16C to U+1F16F.
          if (bytes >= 0x85ac && bytes <= 0x85af) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F1AD to U+1F1E5.
          if (bytes >= 0x86ad && bytes <= 0x87a5) {
            return f_false;
          }

          // Enclosed Alphanumeric Supplement: U+1F12F.
          if (bytes == 0x84af) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F203 to U+1F20F.
          if (bytes >= 0x8883 && bytes <= 0x888f) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F23C to U+1F23F.
          if (bytes >= 0x88bc && bytes <= 0x88bf) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F249 to U+1F24F.
          if (bytes >= 0x8989 && bytes <= 0x898f) {
            return f_false;
          }

          // Enclosed Ideographic Supplement: U+1F252 to U+1F2FF.
          if (bytes >= 0x8992 && bytes <= 0x8bbf) {
            return f_false;
          }

          // Geometric Shapes Extended: U+1F7D5 to U+1F7FF.
          if (bytes >= 0x9f95 && bytes <= 0x9fbf) {
            return f_false;
          }

          // Mahjong Tiles: U+1F02C to U+1F02F.
          if (bytes >= 0x80ac && bytes <= 0x80af) {
            return f_false;
          }

          // Playing Cards: U+1F0AF, U+1F0C0, U+1F0D0.
          if (bytes == 0x82af || bytes == 0x8380 || bytes == 0x8390) {
            return f_false;
          }

          // Playing Cards: U+1F0F6 to U+1F0FF.
          if (bytes >= 0x83b6 && bytes <= 0x83bf) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F80C to U+1F80F.
          if (bytes >= 0xa08c && bytes <= 0xa08f) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F848 to U+1F84F.
          if (bytes >= 0xa188 && bytes <= 0xa18f) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F85A to U+1F85F.
          if (bytes >= 0xa19a && bytes <= 0xa19f) {
            return f_false;
          }

          // Supplemental Arrows-C: U+1F8AE to U+1F8FF.
          if (bytes >= 0xa2ae && bytes <= 0xa3bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F900 to U+1F90F.
          if (bytes >= 0xa480 && bytes <= 0xa48f) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F928 to U+1F92F.
          if (bytes >= 0xa4a8 && bytes <= 0xa4af) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F94C to U+1F94F.
          if (bytes >= 0xa58c && bytes <= 0xa58f) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F960 to U+1F97F.
          if (bytes >= 0xa5a0 && bytes <= 0xa5bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F992 to U+1F9BF.
          if (bytes >= 0xa692 && bytes <= 0xa6bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F9C1 to U+1F9FF.
          if (bytes >= 0xa781 && bytes <= 0xa7bf) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F91F, U+1F931, U+1F932.
          if (bytes == 0xa49f || bytes == 0xa4b1 || bytes == 0xa4b2) {
            return f_false;
          }

          // Supplemental Symbols and Pictographs: U+1F93F, U+1F95F.
          if (bytes == 0xa4bf || bytes == 0xa59f) {
            return f_false;
          }

          // Transport and Map Symbols: U+1F6D3 to U+1F6DF.
          if (bytes >= 0x9b93 && bytes <= 0x9b9f) {
            return f_false;
          }

          // Transport and Map Symbols: U+1F6ED to U+1F6EF.
          if (bytes >= 0x9bad && bytes <= 0x9baf) {
            return f_false;
          }

          // Transport and Map Symbols: U+1F6F7 to U+1F6FF.
          if (bytes >= 0x9bb7 && bytes <= 0x9bbf) {
            return f_false;
          }
        }
        else if (byte_second == 0x98) {
          // Tangut: U+187ED to U+187FF.
          if (bytes >= 0x9fad && bytes <= 0x9fbf) {
            return f_false;
          }

          // Tangut Components: U+18AF3 to U+18AFF.
          if (bytes >= 0xabb3 && bytes <= 0xabbf) {
            return f_false;
          }
        }
        else if (byte_second == 0xaa) {
          // CJK Unified Ideographs Extension B: U+2A6D7 to U+2A6DF.
          if (bytes >= 0x9b97 && bytes <= 0x9b9f) {
            return f_false;
          }
        }
        else if (byte_second == 0xab) {
          // CJK Unified Ideographs Extension C: U+2B735 to U+2B73F.
          if (bytes >= 0x9cb5 && bytes <= 0x9cbf) {
            return f_false;
          }

          // CJK Unified Ideographs Extension D: U+2B81E to U+2B81F.
          if (bytes >= 0xa09e && bytes <= 0xa09f) {
            return f_false;
          }
        }
        else if (byte_second == 0xac) {
          // CJK Unified Ideographs Extension E: U+2CF92 to U+2CF9F.
          if (bytes >= 0xbe92 && bytes <= 0xbe9f) {
            return f_false;
          }
        }
        else if (byte_second == 0xaf) {
          // CJK Compatibility Ideographs Supplement: U+2FA1E to U+2FA1F.
          if (bytes >= 0xa89e && bytes <= 0xa89f) {
            return f_false;
          }
        }
      }
      else if (byte_first == 0xf3) {
        // Consider all private use codes as valid, U+F0000 to U+FFFFF.
        if (bytes >= 0x8080 && bytes <= 0xbfbf) {
          return f_true;
        }

        // Tags: U+E0000, U+E0002 to U+E001F.
        if (bytes == 0x8080 || bytes >= 0x8082 && bytes <= 0x81bf) {
          return f_false;
        }
      }
      else if (byte_first == 0xf4) {
        // Consider all private use codes as valid, U+100000 to U+10FFFF.
        if (bytes >= 0x8080 && bytes <= 0xbfbf) {
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

#include "utf.h"
#include "private-utf.h"
#include "private-utf_control.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)
  f_status_t private_f_utf_character_is_control(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      // Control Codes.

      // Latin-1 Supplement: U+0080 to U+009F.
      if (character >= 0xc2800000 && character <= 0xc29f0000) {
        return F_true;
      }

      // Control Formats.

      // Latin-1 Supplement: U+00AD.
      if (character == 0xc2ad0000) {
        return F_true;
      }

      // Arabic: U+0600 to U+0605.
      if (character >= 0xd8800000 && character <= 0xd8850000) {
        return F_true;
      }

      // Arabic: U+061C, U+06DD.
      if (character == 0xd89c0000 || character == 0xdb9d0000) {
        return F_true;
      }

      // Syriac: U+070F.
      if (character == 0xdc8f0000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // Control Formats.

      // Arabic Extended-A: U+08E2.
      if (character == 0xe0a3a200) {
        return F_true;
      }

      // Mongolian: U+180E.
      if (character == 0xe1a08e00) {
        return F_true;
      }

      // General Punctuation: U+200B to U+200F.
      if (character >= 0xe2808b00 && character <= 0xe2808f00) {
        return F_true;
      }

      // General Punctuation: U+202A to U+202E.
      if (character >= 0xe280aa00 && character <= 0xe280ae00) {
        return F_true;
      }

      // General Punctuation: U+2060 to U+2064.
      if (character >= 0xe281a000 && character <= 0xe281a400) {
        return F_true;
      }

      // General Punctuation: U+2066 to U+206F.
      if (character >= 0xe281a600 && character <= 0xe281af00) {
        return F_true;
      }

      // Arabic Presentation Forms-B: U+FEFF.
      if (character == 0xefbbbf00) {
        return F_true;
      }

      // Specials: U+FFF9 to U+FFFB.
      if (character >= 0xefbfb900 && character <= 0xefbfbb00) {
        return F_true;
      }

      return F_false;
    }

    // Control Formats.

    // Kaithi: U+110BD, U+110CD.
    if (character == 0xf09182bd || character == 0xf091838d) {
      return F_true;
    }

    // Egyptian Hieroglyphics: U+13430 to U+13438.
    if (character >= 0xf09390b0 && character <= 0xf09390b8) {
      return F_true;
    }

    // Shorthand Format Controls: U+1BCA0 to U+1BCA3.
    if (character >= 0xf09bb2a0 && character <= 0xf09bb2a3) {
      return F_true;
    }

    // Music Symbols: U+1D173 to U+1D17A.
    if (character >= 0xf09d85b3 && character <= 0xf09d85ba) {
      return F_true;
    }

    // Tags: U+E0001.
    if (character == 0xf3a08081) {
      return F_true;
    }

    // Tags: U+E0020 to U+E007F.
    if (character >= 0xf3a080a0 && character <= 0xf3a081bf) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)

#if !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_control_code_)
  f_status_t private_f_utf_character_is_control_code(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+0080 to U+009F.
      if (character >= 0xc2800000 && character <= 0xc29f0000) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_contro_codel_)

#if !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)
  f_status_t private_f_utf_character_is_control_format(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      // Latin-1 Supplement: U+00AD.
      if (character == 0xc2ad0000) {
        return F_true;
      }

      // Arabic: U+0600 to U+0605.
      if (character >= 0xd8800000 && character <= 0xd8850000) {
        return F_true;
      }

      // Arabic: U+061C, U+06DD.
      if (character == 0xd89c0000 || character == 0xdb9d0000) {
        return F_true;
      }

      // Syriac: U+070F.
      if (character == 0xdc8f0000) {
        return F_true;
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // Arabic Extended-A: U+08E2.
      if (character == 0xe0a3a200) {
        return F_true;
      }

      // Mongolian: U+180E.
      if (character == 0xe1a08e00) {
        return F_true;
      }

      // General Punctuation: U+200B to U+200F.
      if (character >= 0xe2808b00 && character <= 0xe2808f00) {
        return F_true;
      }

      // General Punctuation: U+202A to U+202E.
      if (character >= 0xe280aa00 && character <= 0xe280ae00) {
        return F_true;
      }

      // General Punctuation: U+2060 to U+2064.
      if (character >= 0xe281a000 && character <= 0xe281a400) {
        return F_true;
      }

      // General Punctuation: U+2066 to U+206F.
      if (character >= 0xe281a600 && character <= 0xe281af00) {
        return F_true;
      }

      // Arabic Presentation Forms-B: U+FEFF.
      if (character == 0xefbbbf00) {
        return F_true;
      }

      // Specials: U+FFF9 to U+FFFB.
      if (character >= 0xefbfb900 && character <= 0xefbfbb00) {
        return F_true;
      }

      return F_false;
    }

    // Kaithi: U+110BD, U+110CD.
    if (character == 0xf09182bd || character == 0xf091838d) {
      return F_true;
    }

    // Egyptian Hieroglyphics: U+13430 to U+13438.
    if (character >= 0xf09390b0 && character <= 0xf09390b8) {
      return F_true;
    }

    // Shothand Format Controls: U+1BCA0 to U+1BCA3.
    if (character >= 0xf09bb2a0 && character <= 0xf09bb2a3) {
      return F_true;
    }

    // Music Symbols: U+1D173 to U+1D17A.
    if (character >= 0xf09d85b3 && character <= 0xf09d85ba) {
      return F_true;
    }

    // Tags: U+E0001.
    if (character == 0xf3a08081) {
      return F_true;
    }

    // Tags: U+E0020 to U+E007F.
    if (character >= 0xf3a080a0 && character <= 0xf3a081bf) {
      return F_true;
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)

#if !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)
  f_status_t private_f_utf_character_is_control_picture(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // Control Pictures: U+2400 to U+2426.
      if (character >= 0xe2908000 && character <= 0xe290a600) {
        return F_true;
      }

      // Specials: U+FFFC to U+FFFD.
      if (character == 0xefbfbc00 || character == 0xefbfbd00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)

#ifdef __cplusplus
} // extern "C"
#endif

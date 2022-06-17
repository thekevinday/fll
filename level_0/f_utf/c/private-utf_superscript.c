#include "utf.h"
#include "private-utf.h"
#include "private-utf_superscript.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_superscript_) || !defined(_di_f_utf_is_superscript_)
  f_status_t private_f_utf_character_is_superscript(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 2) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xc2) {

        // Latin-1 Supplement: U+00A8, U+00AA, U+00B2, U+00B3.
        if (character == 0xc2a80000 || character == 0xc2aa0000 || character == 0xc2b20000 || character == 0xc2b30000) {
          return F_true;
        }

        // Latin-1 Supplement: U+00B9, U+00BA.
        if (character == 0xc2b90000 || character == 0xc2ba0000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xca) {

        // Spacing Modifier Letters: U+02B0 to U+02B8.
        if (character >= 0xcab00000 && character <= 0xcab80000) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xcb) {

        // Spacing Modifier Letters: U+02E0 to U+02E4.
        if (character >= 0xcba00000 && character <= 0xcba40000) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(character) == 3) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xe1) {

        // Georgian: U+10FC.
        if (character == 0xe183bc00) {
          return F_true;
        }

        if (macro_f_utf_char_t_to_char_2(character) >= 0x90 && macro_f_utf_char_t_to_char_2(character) <= 0x99) {

          // Unified Canadian Aboriginal Syllabics: U+141C to U+142A.
          if (character >= 0xe1909c00 && character <= 0xe190aa00) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+1449 to U+144B.
          if (character >= 0xe1918900 && character <= 0xe1918b00) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics:  U+1483, U+1484, U+14A1, U+14A2.
          if (character == 0xe1928300 || character == 0xe1928400 || character == 0xe192a100 || character == 0xe192a200) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+14BB to U+14BE.
          if (character >= 0xe192bb00 && character <= 0xe192be00) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+14D0 to U+14D2.
          if (character >= 0xe1939000 && character <= 0xe1939200) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+14EA, U+14EB.
          if (character == 0xe193aa00 || character == 0xe193ab00) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+1505 to U+150B.
          if (character >= 0xe1948500 && character <= 0xe1948b00) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+1525.
          if (character == 0xe194a500) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+153E to U+1541.
          if (character >= 0xe194be00 && character <= 0xe1958100) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+1550, U+1551, U+155D, U+156A.
          if (character == 0xe1959000 || character == 0xe1959100 || character == 0xe1959d00 || character == 0xe195aa00) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+157B, U+156F, U+157D, U+1585.
          if (character == 0xe195bb00 || character == 0xe195af00 || character == 0xe195bd00 || character == 0xe1968500) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+1595, U+1596, U+159F, U+15A6.
          if (character == 0xe1969500 || character == 0xe1969600 || character == 0xe1969f00 || character == 0xe196a600) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+15AE, U+15EE, U+1601, U+1646.
          if (character == 0xe196ae00 || character == 0xe197ae00 || character == 0xe1988100 || character == 0xe1998600) {
            return F_true;
          }

          // Unified Canadian Aboriginal Syllabics: U+1647, U+165A, U+167E, U+167F.
          if (character == 0xe1998700 || character == 0xe1999a00 || character == 0xe199be00 || character == 0xe199bf00) {
            return F_true;
          }
        }
        else {

          // Phonetic Extensions: U+1D2C to U+1D61.
          if (character >= 0xe1b4ac00 && character <= 0xe1b5a100) {
            return F_true;
          }

          // Phonetic Extensions: U+1D78.
          if (character == 0xe1b5b800) {
            return F_true;
          }

          // Phonetic Extensions Supplement: U+1D9B to U+1DBF.
          if (character >= 0xe1b69b00 && character <= 0xe1b6bf00) {
            return F_true;
          }
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe2) {

        // Superscripts and Subscripts: U+2070, U+2071.
        if (character == 0xe281b000 || character == 0xe281b100) {
          return F_true;
        }

        // Superscripts and Subscripts: U+2074 to U+207F.
        if (character >= 0xe281b400 && character <= 0xe281bf00) {
          return F_true;
        }

        // Latin Extended-C: U+2C7D.
        if (character == 0xe2b1bd00) {
          return F_true;
        }

        // Tifinagh: U+2D6F.
        if (character == 0xe2b5af00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xe3) {

        // Kanbun: U+3191 to U+319F.
        if (character >= 0xe3869100 && character <= 0xe3869f00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(character) == 0xea) {

        // Cyrillic Extended-B: U+A69C, U+A69D.
        if (character == 0xea9a9c00 || character == 0xea9a9d00) {
          return F_true;
        }

        // Latin Extended-D: U+A770.
        if (character == 0xea9db000) {
          return F_true;
        }

        // Latin Extended-D: U+A7F2 to U+A7F4.
        if (character >= 0xea9fb200 && character <= 0xea9fb400) {
          return F_true;
        }

        // Latin Extended-D: U+A7F8, U+A7F9.
        if (character == 0xea9fb800 || character == 0xea9fb900) {
          return F_true;
        }

        // Latin Extended-E: U+AB5C to U+AB5F.
        if (character >= 0xeaad9c00 && character <= 0xeaad9f00) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(character) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(character) == 0x90) {

        // Latin Extended-F: U+10780 to U+10785.
        if (character >= 0xf0909e80 && character <= 0xf0909e85) {
          return F_true;
        }

        // Latin Extended-F: U+10787 to U+107B0.
        if (character >= 0xf0909e87 && character <= 0xf0909eb0) {
          return F_true;
        }

        // Latin Extended-F: U+107B2 to U+107BA.
        if (character >= 0xf0909eb2 && character <= 0xf0909eba) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_superscript_) || !defined(_di_f_utf_is_superscript_)

#ifdef __cplusplus
} // extern "C"
#endif

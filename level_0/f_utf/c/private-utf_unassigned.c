#include "utf.h"
#include "private-utf.h"
#include "private-utf_unassigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_unassigned_) || !defined(_di_f_utf_is_unassigned_)
  f_status_t private_f_utf_character_is_unassigned(const f_utf_char_t sequence) {

    if (macro_f_utf_char_t_width_is(sequence) < 2) {
      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 2) {

      if (macro_f_utf_char_t_to_char_1(sequence) < 0xd7) {

        // Greek and Coptic: U+0378 to U+0379.
        if (sequence >= 0xcdb80000 && sequence <= 0xcdb90000) {
          return F_true;
        }

        // Greek and Coptic: U+0380 to U+0383.
        if (sequence >= 0xce800000 && sequence <= 0xce830000) {
          return F_true;
        }

        // Greek and Coptic: U+038B, U+038D, U+03A2.
        if (sequence == 0xce8b0000 || sequence == 0xce8d0000 || sequence == 0xcea20000) {
          return F_true;
        }

        // Armenian: U+0530.
        if (sequence == 0xd4b00000) {
          return F_true;
        }

        // Armenian: U+0557 to U+0558.
        if (sequence >= 0xd5970000 && sequence <= 0xd5980000) {
          return F_true;
        }

        // Armenian: U+058B, U+058C.
        if (sequence == 0xd68b0000 || sequence == 0xd68c0000) {
          return F_true;
        }

        // Hebrew: U+0590.
        if (sequence == 0xd6900000) {
          return F_true;
        }
      }
      else {

        // Hebrew: U+05C8 to U+05CF.
        if (sequence >= 0xd7880000 && sequence <= 0xd78f0000) {
          return F_true;
        }

        // Hebrew: U+05EB to U+05EE.
        if (sequence >= 0xd7ab0000 && sequence <= 0xd7ae0000) {
          return F_true;
        }

        // Hebrew: U+05F5 to U+05FF.
        if (sequence >= 0xd7b50000 && sequence <= 0xd7bf0000) {
          return F_true;
        }

        // Syriac: U+074B to U+074C.
        if (sequence >= 0xdd8b0000 && sequence <= 0xdd8c0000) {
          return F_true;
        }

        // Thaana: U+07B2 to U+07BF.
        if (sequence >= 0xdeb20000 && sequence <= 0xdebf0000) {
          return F_true;
        }

        // Nko: U+07FB to U+07FC.
        if (sequence >= 0xdfbb0000 && sequence <= 0xdfbc0000) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_width_is(sequence) == 3) {

      if (macro_f_utf_char_t_to_char_1(sequence) < 0xe0) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe0) {

        // Samaritan: U+082E, U+082F, U+083F.
        if (sequence == 0xe0a0ae00 || sequence == 0xe0a0af00 || sequence == 0xe0a0bf00) {
          return F_true;
        }

        // Mandaic: U+085C, U+085D, U+085F.
        if (sequence == 0xe0a19c00 || sequence == 0xe0a19d00 || sequence == 0xe0a19f00) {
          return F_true;
        }

        // Syriac Supplement: U+086B to U+086F.
        if (sequence >= 0xe0a1ab00 && sequence <= 0xe0a1af00) {
          return F_true;
        }

        // Arabic Extended B: U+088F.
        if (sequence == 0xe0a28f00) {
          return F_true;
        }

        // Arabic Extended B: U+0892 to U+0897.
        if (sequence >= 0xe0a29200 && sequence <= 0xe0a29700) {
          return F_true;
        }

        // Bengali: U+0984, U+098D, U+098E, U+0991.
        if (sequence == 0xe0a68400 || sequence == 0xe0a68d00 || sequence == 0xe0a68e00 || sequence == 0xe0a69100) {
          return F_true;
        }

        // Bengali: U+0992, U+09A9, U+09B1.
        if (sequence == 0xe0a69200 || sequence == 0xe0a6a900 || sequence == 0xe0a6b100) {
          return F_true;
        }

        // Bengali: U+09B3 to U+09B5.
        if (sequence >= 0xe0a6b300 && sequence <= 0xe0a6b500) {
          return F_true;
        }

        // Bengali: U+09BA to U+09BB.
        if (sequence >= 0xe0a6ba00 && sequence <= 0xe0a6bb00) {
          return F_true;
        }

        // Bengali: U+09C5 to U+09C6.
        if (sequence >= 0xe0a78500 && sequence <= 0xe0a78600) {
          return F_true;
        }

        // Bengali: U+09C9 to U+09CA.
        if (sequence >= 0xe0a78900 && sequence <= 0xe0a78a00) {
          return F_true;
        }

        // Bengali: U+09CF to U+09D6.
        if (sequence >= 0xe0a78f00 && sequence <= 0xe0a79600) {
          return F_true;
        }

        // Bengali: U+09D8 to U+09DB.
        if (sequence >= 0xe0a79800 && sequence <= 0xe0a79b00) {
          return F_true;
        }

        // Bengali: U+09DE, U+09E4, U+09E5, U+09FF.
        if (sequence == 0xe0a79e00 || sequence == 0xe0a7a400 || sequence == 0xe0a7a500 || sequence == 0xe0a7bf00) {
          return F_true;
        }

        // Gurmukhi: U+0A00, U+0A04.
        if (sequence == 0xe0a88000 || sequence == 0xe0a88400) {
          return F_true;
        }

        // Gurmukhi: U+0A0B to U+0A0E.
        if (sequence >= 0xe0a88b00 && sequence <= 0xe0a88e00) {
          return F_true;
        }

        // Gurmukhi: U+0A11 to U+0A12.
        if (sequence >= 0xe0a89100 && sequence <= 0xe0a89200) {
          return F_true;
        }

        // Gurmukhi: U+0A29, U+0A31, U+0A34, U+0A37.
        if (sequence == 0xe0a8a900 || sequence == 0xe0a8b100 || sequence == 0xe0a8b400 || sequence == 0xe0a8b700) {
          return F_true;
        }

        // Gurmukhi: U+0A3A, U+0A3B, U+0A3D.
        if (sequence == 0xe0a8ba00 || sequence == 0xe0a8bb00 || sequence == 0xe0a8bd00) {
          return F_true;
        }

        // Gurmukhi: U+0A43 to U+0A46.
        if (sequence >= 0xe0a98300 && sequence <= 0xe0a98600) {
          return F_true;
        }

        // Gurmukhi: U+0A49 to U+0A4A.
        if (sequence >= 0xe0a98900 && sequence <= 0xe0a98a00) {
          return F_true;
        }

        // Gurmukhi: U+0A4E to U+0A50.
        if (sequence >= 0xe0a98e00 && sequence <= 0xe0a99000) {
          return F_true;
        }

        // Gurmukhi: U+0A52 to U+0A58.
        if (sequence >= 0xe0a99200 && sequence <= 0xe0a99800) {
          return F_true;
        }

        // Gurmukhi: U+0A5D.
        if (sequence == 0xe0a99d00) {
          return F_true;
        }

        // Gurmukhi: U+0A5F to U+0A65.
        if (sequence >= 0xe0a99f00 && sequence <= 0xe0a9a500) {
          return F_true;
        }

        // Gurmukhi: U+0A77 to U+0A7F.
        if (sequence >= 0xe0a9b700 && sequence <= 0xe0a9bf00) {
          return F_true;
        }

        // Gujarati: U+0A80, U+0A84, U+0A8E, U+0A92.
        if (sequence == 0xe0aa8000 || sequence == 0xe0aa8400 || sequence == 0xe0aa8e00 || sequence == 0xe0aa9200) {
          return F_true;
        }

        // Gujarati: U+0AA9, U+0AB1, U+0AB4, U+0ABA.
        if (sequence == 0xe0aaa900 || sequence == 0xe0aab100 || sequence == 0xe0aab400 || sequence == 0xe0aaba00) {
          return F_true;
        }

        // Gujarati: U+0ABB, U+0AC6, U+0ACA.
        if (sequence == 0xe0aabb00 || sequence == 0xe0ab8600 || sequence == 0xe0ab8a00) {
          return F_true;
        }

        // Gujarati: U+0ACE to U+0ACF.
        if (sequence >= 0xe0ab8e00 && sequence <= 0xe0ab8f00) {
          return F_true;
        }

        // Gujarati: U+0AD1 to U+0ADF.
        if (sequence >= 0xe0ab9100 && sequence <= 0xe0ab9f00) {
          return F_true;
        }

        // Gujarati: U+0AE4 to U+0AE5.
        if (sequence >= 0xe0aba400 && sequence <= 0xe0aba500) {
          return F_true;
        }

        // Gujarati: U+0AF2 to U+0AF8.
        if (sequence >= 0xe0abb200 && sequence <= 0xe0abb800) {
          return F_true;
        }

        // Oriya: U+0B00, U+0B04, U+0B0D, U+0B0E.
        if (sequence == 0xe0ac8000 || sequence == 0xe0ac8400 || sequence == 0xe0ac8d00 || sequence == 0xe0ac8e00) {
          return F_true;
        }

        // Oriya: U+0B11, U+0B12, U+0B29, U+0B31.
        if (sequence == 0xe0ac9100 || sequence == 0xe0ac9200 || sequence == 0xe0aca900 || sequence == 0xe0acb100) {
          return F_true;
        }

        // Oriya: U+0B34, U+0B3A, U+0B3B, U+0B45.
        if (sequence == 0xe0acb400 || sequence == 0xe0acba00 || sequence == 0xe0acbb00 || sequence == 0xe0ad8500) {
          return F_true;
        }

        // Oriya: U+0B46, U+0B49, U+0B4A.
        if (sequence == 0xe0ad8600 || sequence == 0xe0ad8900 || sequence == 0xe0ad8a00) {
          return F_true;
        }

        // Oriya: U+0B4E to U+0B55.
        if (sequence >= 0xe0ad8e00 && sequence <= 0xe0ad9500) {
          return F_true;
        }

        // Oriya: U+0B58 to U+0B5B.
        if (sequence >= 0xe0ad9800 && sequence <= 0xe0ad9b00) {
          return F_true;
        }

        // Oriya: U+0B5E, U+0B64, U+0B65.
        if (sequence == 0xe0ad9e00 || sequence == 0xe0ada400 || sequence == 0xe0ada500) {
          return F_true;
        }

        // Oriya: U+0B78 to U+0B7F.
        if (sequence >= 0xe0adb800 && sequence <= 0xe0adbf00) {
          return F_true;
        }

        // Tamil: U+0B80, U+0B81, U+0B84.
        if (sequence == 0xe0ae8000 || sequence == 0xe0ae8100 || sequence == 0xe0ae8400) {
          return F_true;
        }

        // Tamil: U+0B8B to U+0B8D.
        if (sequence >= 0xe0ae8b00 && sequence <= 0xe0ae8d00) {
          return F_true;
        }

        // Tamil: U+0B91.
        if (sequence == 0xe0ae9100) {
          return F_true;
        }

        // Tamil: U+0B96 to U+0B98.
        if (sequence >= 0xe0ae9600 && sequence <= 0xe0ae9800) {
          return F_true;
        }

        // Tamil: U+0B9B, U+0B9D.
        if (sequence == 0xe0ae9b00 || sequence == 0xe0ae9d00) {
          return F_true;
        }

        // Tamil: U+0BA0 to U+0BA2.
        if (sequence >= 0xe0aea000 && sequence <= 0xe0aea200) {
          return F_true;
        }

        // Tamil: U+0BA5 to U+0BA7.
        if (sequence >= 0xe0aea500 && sequence <= 0xe0aea700) {
          return F_true;
        }

        // Tamil: U+0BAB to U+0BAD.
        if (sequence >= 0xe0aeab00 && sequence <= 0xe0aead00) {
          return F_true;
        }

        // Tamil: U+0BBA to U+0BBD.
        if (sequence >= 0xe0aeba00 && sequence <= 0xe0aebd00) {
          return F_true;
        }

        // Tamil: U+0BC3 to U+0BC5.
        if (sequence >= 0xe0af8300 && sequence <= 0xe0af8500) {
          return F_true;
        }

        // Tamil: U+0BC9, U+0BCE, U+0BCF.
        if (sequence == 0xe0af8900 || sequence == 0xe0af8e00 || sequence == 0xe0af8f00) {
          return F_true;
        }

        // Tamil: U+0BD1 to U+0BD6.
        if (sequence >= 0xe0af9100 && sequence <= 0xe0af9600) {
          return F_true;
        }

        // Tamil: U+0BD8 to U+0BE5.
        if (sequence >= 0xe0af9800 && sequence <= 0xe0afa500) {
          return F_true;
        }

        // Tamil: U+0BFB to U+0BFF.
        if (sequence >= 0xe0afbb00 && sequence <= 0xe0afbf00) {
          return F_true;
        }

        // Telegu: U+0C04, U+0C0D, U+0C11, U+0C29.
        if (sequence == 0xe0b08400 || sequence == 0xe0b08d00 || sequence == 0xe0b09100 || sequence == 0xe0b0a900) {
          return F_true;
        }

        // Telegu: U+0C3A to U+0C3C.
        if (sequence >= 0xe0b0ba00 && sequence <= 0xe0b0bc00) {
          return F_true;
        }

        // Telegu: U+0C45, U+0C49.
        if (sequence == 0xe0b18500 || sequence == 0xe0b18900) {
          return F_true;
        }

        // Telegu: U+0C4E to U+0C54.
        if (sequence >= 0xe0b18e00 && sequence <= 0xe0b19400) {
          return F_true;
        }

        // Telegu: U+0C5B to U+0C5F.
        if (sequence >= 0xe0b19b00 && sequence <= 0xe0b19f00) {
          return F_true;
        }

        // Telegu: U+0C64 to U+0C65.
        if (sequence >= 0xe0b1a400 && sequence <= 0xe0b1a500) {
          return F_true;
        }

        // Telegu: U+0C70 to U+0C77.
        if (sequence >= 0xe0b1b000 && sequence <= 0xe0b1b700) {
          return F_true;
        }

        // Kannada: U+0C80, U+0C84, U+0C8D, U+0C91.
        if (sequence == 0xe0b28000 || sequence == 0xe0b28400 || sequence == 0xe0b28d00 || sequence == 0xe0b29100) {
          return F_true;
        }

        // Kannada: U+0CA9, U+0CB4, U+0CBA, U+0CBB.
        if (sequence == 0xe0b2a900 || sequence == 0xe0b2b400 || sequence == 0xe0b2ba00 || sequence == 0xe0b2bb00) {
          return F_true;
        }

        // Kannada: U+0CC5, U+0CC9.
        if (sequence == 0xe0b38500 || sequence == 0xe0b38900) {
          return F_true;
        }

        // Kannada: U+0CCE to U+0CD4.
        if (sequence >= 0xe0b38e00 && sequence <= 0xe0b39400) {
          return F_true;
        }

        // Kannada: U+0CD7 to U+0CDD.
        if (sequence >= 0xe0b39700 && sequence <= 0xe0b39d00) {
          return F_true;
        }

        // Kannada: U+0CDF, U+0CE4, U+0CE5, U+0CF0.
        if (sequence == 0xe0b39f00 || sequence == 0xe0b3a400 || sequence == 0xe0b3a500 || sequence == 0xe0b3b000) {
          return F_true;
        }

        // Kannada: U+0CF4 to U+0CFF.
        if (sequence >= 0xe0b3b400 && sequence <= 0xe0b3bf00) {
          return F_true;
        }

        // Malayalam: U+0D00, U+0D04, U+0D0D, U+0D11.
        if (sequence == 0xe0b48000 || sequence == 0xe0b48400 || sequence == 0xe0b48d00 || sequence == 0xe0b49100) {
          return F_true;
        }

        // Malayalam: U+0D3B, U+0D3C, U+0D45, U+0D49.
        if (sequence == 0xe0b4bb00 || sequence == 0xe0b4bc00 || sequence == 0xe0b58500 || sequence == 0xe0b58900) {
          return F_true;
        }

        // Malayalam: U+0D4F to U+0D56.
        if (sequence >= 0xe0b58f00 && sequence <= 0xe0b59600) {
          return F_true;
        }

        // Malayalam: U+0D58 to U+0D5E.
        if (sequence >= 0xe0b59800 && sequence <= 0xe0b59e00) {
          return F_true;
        }

        // Malayalam: U+0D64, U+0D65.
        if (sequence == 0xe0b5a400 || sequence == 0xe0b5a500) {
          return F_true;
        }

        // Malayalam: U+0D76 to U+0D78.
        if (sequence >= 0xe0b5b600 && sequence <= 0xe0b5b800) {
          return F_true;
        }

        // Sinhala: U+0D80, U+0D81, U+0D84.
        if (sequence == 0xe0b68000 || sequence == 0xe0b68100 || sequence == 0xe0b68400) {
          return F_true;
        }

        // Sinhala: U+0D97 to U+0D99.
        if (sequence >= 0xe0b69700 && sequence <= 0xe0b69900) {
          return F_true;
        }

        // Sinhala: U+0DB2, U+0DBC, U+0DBE, U+0DBF.
        if (sequence == 0xe0b6b200 || sequence == 0xe0b6bc00 || sequence == 0xe0b6be00 || sequence == 0xe0b6bf00) {
          return F_true;
        }

        // Sinhala: U+0DC7 to U+0DC9.
        if (sequence >= 0xe0b78700 && sequence <= 0xe0b78900) {
          return F_true;
        }

        // Sinhala: U+0DCB to U+0DCE.
        if (sequence >= 0xe0b78b00 && sequence <= 0xe0b78e00) {
          return F_true;
        }

        // Sinhala: U+0DD5, U+0DD7.
        if (sequence == 0xe0b79500 || sequence == 0xe0b79700) {
          return F_true;
        }

        // Sinhala: U+0DE0 to U+0DE5.
        if (sequence >= 0xe0b7a000 && sequence <= 0xe0b7a500) {
          return F_true;
        }

        // Sinhala: U+0DF0 to U+0DF1.
        if (sequence >= 0xe0b7b000 && sequence <= 0xe0b7b100) {
          return F_true;
        }

        // Sinhala: U+0DF5 to U+0DFF.
        if (sequence >= 0xe0b7b500 && sequence <= 0xe0b7bf00) {
          return F_true;
        }

        // Thai: U+0E00.
        if (sequence == 0xe0b88000) {
          return F_true;
        }

        // Thai: U+0E3B to U+0E3E.
        if (sequence >= 0xe0b8bb00 && sequence <= 0xe0b8be00) {
          return F_true;
        }

        // Thai: U+0E5C to U+0E7F.
        if (sequence >= 0xe0b99c00 && sequence <= 0xe0b9bf00) {
          return F_true;
        }

        // Lao: U+0E80, U+0E83, U+0E85, U+0E86.
        if (sequence == 0xe0ba8000 || sequence == 0xe0ba8300 || sequence == 0xe0ba8500 || sequence == 0xe0ba8600) {
          return F_true;
        }

        // Lao: U+0E89, U+0E8B, U+0E8C.
        if (sequence == 0xe0ba8900 || sequence == 0xe0ba8b00 || sequence == 0xe0ba8c00) {
          return F_true;
        }

        // Lao: U+0E8E to U+0E93.
        if (sequence >= 0xe0ba8e00 && sequence <= 0xe0ba9300) {
          return F_true;
        }

        // Lao: U+0E98, U+0EA0, U+0EA4, U+0EA6.
        if (sequence == 0xe0ba9800 || sequence == 0xe0baa000 || sequence == 0xe0baa400 || sequence == 0xe0baa600) {
          return F_true;
        }

        // Lao: U+0EA8, U+0EA9, U+0EAC, U+0EBA.
        if (sequence == 0xe0baa800 || sequence == 0xe0baa900 || sequence == 0xe0baac00 || sequence == 0xe0baba00) {
          return F_true;
        }

        // Lao: U+0EBE, U+0EBF, U+0EC5, U+0EC7.
        if (sequence == 0xe0babe00 || sequence == 0xe0babf00 || sequence == 0xe0bb8500 || sequence == 0xe0bb8700) {
          return F_true;
        }

        // Lao: U+0ECF, U+0EDA, U+0EDB.
        if (sequence == 0xe0bb8f00 || sequence == 0xe0bb9a00 || sequence == 0xe0bb9b00) {
          return F_true;
        }

        // Lao: U+0EE0 to U+0EFF.
        if (sequence >= 0xe0bba000 && sequence <= 0xe0bbbf00) {
          return F_true;
        }

        // Tibetan: U+0F48.
        if (sequence == 0xe0bd8800) {
          return F_true;
        }

        // Tibetan: U+0F6D to U+0F70.
        if (sequence >= 0xe0bdad00 && sequence <= 0xe0bdb000) {
          return F_true;
        }

        // Tibetan: U+0F98, U+0FBD, U+0FCD.
        if (sequence == 0xe0be9800 || sequence == 0xe0bebd00 || sequence == 0xe0bf8d00) {
          return F_true;
        }

        // Tibetan: U+0FDB to U+0FFF.
        if (sequence >= 0xe0bf9b00 && sequence <= 0xe0bfbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe1) {

        // Georgian: U+10C6.
        if (sequence == 0xe1838600) {
          return F_true;
        }

        // Georgian: U+10C8 to U+10CC.
        if (sequence >= 0xe1838800 && sequence <= 0xe1838c00) {
          return F_true;
        }

        // Georgian: U+10CE to U+10CF.
        if (sequence >= 0xe1838e00 && sequence <= 0xe1838f00) {
          return F_true;
        }

        // Ethiopic: U+1249, U+124E, U+124F, U+1257.
        if (sequence == 0xe1898900 || sequence == 0xe1898e00 || sequence == 0xe1898f00 || sequence == 0xe1899700) {
          return F_true;
        }

        // Ethiopic: U+1259, U+125E, U+125F, U+1289.
        if (sequence == 0xe1899900 || sequence == 0xe1899e00 || sequence == 0xe1899f00 || sequence == 0xe18a8900) {
          return F_true;
        }

        // Ethiopic: U+128E, U+128F, U+12B1, U+12B6.
        if (sequence == 0xe18a8e00 || sequence == 0xe18a8f00 || sequence == 0xe18ab100 || sequence == 0xe18ab600) {
          return F_true;
        }

        // Ethiopic: U+12B7, U+12BF, U+12C1, U+12C6.
        if (sequence == 0xe18ab700 || sequence == 0xe18abf00 || sequence == 0xe18b8100 || sequence == 0xe18b8600) {
          return F_true;
        }

        // Ethiopic: U+12C7, U+12D7, U+1311, U+1316.
        if (sequence == 0xe18b8700 || sequence == 0xe18b9700 || sequence == 0xe18c9100 || sequence == 0xe18c9600) {
          return F_true;
        }

        // Ethiopic: U+1317, U+135B, U+135C.
        if (sequence == 0xe18c9700 || sequence == 0xe18d9b00 || sequence == 0xe18d9c00) {
          return F_true;
        }

        // Ethiopic: U+137D to U+137F.
        if (sequence >= 0xe18dbd00 && sequence <= 0xe18dbf00) {
          return F_true;
        }

        // Ethiopic Supplement: U+139A to U+139F.
        if (sequence >= 0xe18e9a00 && sequence <= 0xe18e9f00) {
          return F_true;
        }

        // Cherokee: U+13F6 to U+13F7.
        if (sequence >= 0xe18fb600 && sequence <= 0xe18fb700) {
          return F_true;
        }

        // Cherokee: U+13FE to U+13FF.
        if (sequence >= 0xe18fbe00 && sequence <= 0xe18fbf00) {
          return F_true;
        }

        // Ogham: U+169D to U+169F.
        if (sequence >= 0xe19a9d00 && sequence <= 0xe19a9f00) {
          return F_true;
        }

        // Runic: U+16F9 to U+16FF.
        if (sequence >= 0xe19bb900 && sequence <= 0xe19bbf00) {
          return F_true;
        }

        // Tagalog: U+170D.
        if (sequence == 0xe19c8d00) {
          return F_true;
        }

        // Tagalog: U+1715 to U+171F.
        if (sequence >= 0xe19c9500 && sequence <= 0xe19c9f00) {
          return F_true;
        }

        // Hanunoo: U+1737 to U+173F.
        if (sequence >= 0xe19cb700 && sequence <= 0xe19cbf00) {
          return F_true;
        }

        // Buhid: U+1754 to U+175F.
        if (sequence >= 0xe19d9400 && sequence <= 0xe19d9f00) {
          return F_true;
        }

        // Tagbanwa: U+176D, U+1771.
        if (sequence == 0xe19dad00 || sequence == 0xe19db100) {
          return F_true;
        }

        // Tagbanwa: U+1774 to U+177F.
        if (sequence >= 0xe19db400 && sequence <= 0xe19dbf00) {
          return F_true;
        }

        // Khmer: U+17DE to U+17DF.
        if (sequence >= 0xe19f9e00 && sequence <= 0xe19f9f00) {
          return F_true;
        }

        // Khmer: U+17EA to U+17EF.
        if (sequence >= 0xe19faa00 && sequence <= 0xe19faf00) {
          return F_true;
        }

        // Khmer: U+17FA to U+17FF.
        if (sequence >= 0xe19fba00 && sequence <= 0xe19fbf00) {
          return F_true;
        }

        // Mongolian: U+180F.
        if (sequence == 0xe1a08f00) {
          return F_true;
        }

        // Mongolian: U+181A to U+181F.
        if (sequence >= 0xe1a09a00 && sequence <= 0xe1a09f00) {
          return F_true;
        }

        // Mongolian: U+1878 to U+187F.
        if (sequence >= 0xe1a1b800 && sequence <= 0xe1a1bf00) {
          return F_true;
        }

        // Mongolian: U+18AB to U+18AF.
        if (sequence >= 0xe1a2ab00 && sequence <= 0xe1a2af00) {
          return F_true;
        }

        // Unified Canadian Aboriginal Syllabics Extended: U+18F6 to U+18FF.
        if (sequence >= 0xe1a3b600 && sequence <= 0xe1a3bf00) {
          return F_true;
        }

        // Limbu: U+191F.
        if (sequence == 0xe1a49f00) {
          return F_true;
        }

        // Limbu: U+192C to U+192F.
        if (sequence >= 0xe1a4ac00 && sequence <= 0xe1a4af00) {
          return F_true;
        }

        // Limbu: U+193C to U+193F.
        if (sequence >= 0xe1a4bc00 && sequence <= 0xe1a4bf00) {
          return F_true;
        }

        // Limbu: U+1941 to U+1943.
        if (sequence >= 0xe1a58100 && sequence <= 0xe1a58300) {
          return F_true;
        }

        // Tai Le: U+196E to U+196F.
        if (sequence >= 0xe1a5ae00 && sequence <= 0xe1a5af00) {
          return F_true;
        }

        // Tai Le: U+1975 to U+197F.
        if (sequence >= 0xe1a5b500 && sequence <= 0xe1a5bf00) {
          return F_true;
        }

        // New Tai Lue: U+19AC to U+19AF.
        if (sequence >= 0xe1a6ac00 && sequence <= 0xe1a6af00) {
          return F_true;
        }

        // New Tai Lue: U+19CA to U+19CF.
        if (sequence >= 0xe1a78a00 && sequence <= 0xe1a78f00) {
          return F_true;
        }

        // New Tai Lue: U+19DB to U+19DD.
        if (sequence >= 0xe1a79b00 && sequence <= 0xe1a79d00) {
          return F_true;
        }

        // Buginese: U+1A1C to U+1A1D.
        if (sequence >= 0xe1a89c00 && sequence <= 0xe1a89d00) {
          return F_true;
        }

        // Tai Tham: U+1A5F.
        if (sequence == 0xe1a99f00) {
          return F_true;
        }

        // Tai Tham: U+1A7D to U+1A7E.
        if (sequence >= 0xe1a9bd00 && sequence <= 0xe1a9be00) {
          return F_true;
        }

        // Tai Tham: U+1A8A to U+1A8F.
        if (sequence >= 0xe1aa8a00 && sequence <= 0xe1aa8f00) {
          return F_true;
        }

        // Tai Tham: U+1A9A to U+1A9F.
        if (sequence >= 0xe1aa9a00 && sequence <= 0xe1aa9f00) {
          return F_true;
        }

        // Tai Tham: U+1AAE to U+1AAF.
        if (sequence >= 0xe1aaae00 && sequence <= 0xe1aaaf00) {
          return F_true;
        }

        // Combining Diacritical Marks Extended: U+1ACF to U+1AFF.
        if (sequence >= 0xe1ab8f00 && sequence <= 0xe1abbf00) {
          return F_true;
        }

        // Balinese: U+1B4C to U+1B4F.
        if (sequence >= 0xe1ad8c00 && sequence <= 0xe1ad8f00) {
          return F_true;
        }

        // Balinese: U+1B7D to U+1B7F.
        if (sequence >= 0xe1adbd00 && sequence <= 0xe1adbf00) {
          return F_true;
        }

        // Batak: U+1BF4 to U+1BFB.
        if (sequence >= 0xe1afb400 && sequence <= 0xe1afbb00) {
          return F_true;
        }

        // Lepcha: U+1C38 to U+1C3A.
        if (sequence >= 0xe1b0b800 && sequence <= 0xe1b0ba00) {
          return F_true;
        }

        // Lepcha: U+1C4A to U+1C4C.
        if (sequence >= 0xe1b18a00 && sequence <= 0xe1b18c00) {
          return F_true;
        }

        // Sundanese Supplement: U+1CC8 to U+1CCF.
        if (sequence >= 0xe1b38800 && sequence <= 0xe1b38f00) {
          return F_true;
        }

        // Vedic Extensions: U+1CF7.
        if (sequence == 0xe1b3b700) {
          return F_true;
        }

        // Vedic Extensions: U+1CFA to U+1CFF.
        if (sequence >= 0xe1b3ba00 && sequence <= 0xe1b3bf00) {
          return F_true;
        }

        // Combining Diacritical Marks Supplement: U+1DF6 to U+1DFB.
        if (sequence >= 0xe1b7b600 && sequence <= 0xe1b7bb00) {
          return F_true;
        }

        // Greek Extended: U+1F16, U+1F17, U+1F1E, U+1F1F.
        if (sequence == 0xe1bc9600 || sequence == 0xe1bc9700 || sequence == 0xe1bc9e00 || sequence == 0xe1bc9f00) {
          return F_true;
        }

        // Greek Extended: U+1F46, U+1F47, U+1F4E, U+1F4F.
        if (sequence == 0xe1bd8600 || sequence == 0xe1bd8700 || sequence == 0xe1bd8e00 || sequence == 0xe1bd8f00) {
          return F_true;
        }

        // Greek Extended: U+1F58, U+1F5A, U+1F5C, U+1F5E.
        if (sequence == 0xe1bd9800 || sequence == 0xe1bd9a00 || sequence == 0xe1bd9c00 || sequence == 0xe1bd9e00) {
          return F_true;
        }

        // Greek Extended: U+1F7E, U+1F7F, U+1FB5, U+1FC5.
        if (sequence == 0xe1bdbe00 || sequence == 0xe1bdbf00 || sequence == 0xe1beb500 || sequence == 0xe1bf8500) {
          return F_true;
        }

        // Greek Extended: U+1FD4, U+1FD5, U+1FDC, U+1FF0.
        if (sequence == 0xe1bf9400 || sequence == 0xe1bf9500 || sequence == 0xe1bf9c00 || sequence == 0xe1bfb000) {
          return F_true;
        }

        // Greek Extended: U+1FF1, U+1FF5, U+1FFF.
        if (sequence == 0xe1bfb100 || sequence == 0xe1bfb500 || sequence == 0xe1bfbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe2) {

        // General Punctuation: U+2065.
        if (sequence == 0xe281a500) {
          return F_true;
        }

        // Superscripts and Subscripts: U+2072, U+2073, U+208F.
        if (sequence == 0xe281b200 || sequence == 0xe281b300 || sequence == 0xe2828f00) {
          return F_true;
        }

        // Superscripts and Subscripts: U+209D to U+209F.
        if (sequence >= 0xe2829d00 && sequence <= 0xe2829f00) {
          return F_true;
        }

        // Currency Symbols: U+20BF to U+20CF.
        if (sequence >= 0xe282bf00 && sequence <= 0xe2838f00) {
          return F_true;
        }

        // Combining Diacritical Marks for Symbols: U+20F1 to U+20FF.
        if (sequence >= 0xe283b100 && sequence <= 0xe283bf00) {
          return F_true;
        }

        // Number Forms: U+218C to U+218F.
        if (sequence >= 0xe2868c00 && sequence <= 0xe2868f00) {
          return F_true;
        }

        // Miscellaneous Technical: U+23FB to U+23FF.
        if (sequence >= 0xe28fbb00 && sequence <= 0xe28fbf00) {
          return F_true;
        }

        // Control Pictures: U+2427 to U+243F.
        if (sequence >= 0xe290a700 && sequence <= 0xe290bf00) {
          return F_true;
        }

        // Optical Character Recognition: U+244B to U+245F.
        if (sequence >= 0xe2918b00 && sequence <= 0xe2919f00) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2B74, U+2B75, U+2B96, U+2B97.
        if (sequence == 0xe2adb400 || sequence == 0xe2adb500 || sequence == 0xe2ae9600 || sequence == 0xe2ae9700) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2BBA to U+2BBC.
        if (sequence >= 0xe2aeba00 && sequence <= 0xe2aebc00) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2BC9.
        if (sequence == 0xe2af8900) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2BD2 to U+2BEB.
        if (sequence >= 0xe2af9200 && sequence <= 0xe2afab00) {
          return F_true;
        }

        // Miscellaneous Symbols and Arrows: U+2BF0 to U+2BFF.
        if (sequence >= 0xe2afb000 && sequence <= 0xe2afbf00) {
          return F_true;
        }

        // Glagolitic: U+2C5F.
        if (sequence == 0xe2b19f00) {
          return F_true;
        }

        // Coptic: U+2CF4 to U+2CF8.
        if (sequence >= 0xe2b3b400 && sequence <= 0xe2b3b800) {
          return F_true;
        }

        // Georgian Supplement: U+2D26.
        if (sequence == 0xe2b4a600) {
          return F_true;
        }

        // Georgian Supplement: U+2D28 to U+2D2C.
        if (sequence >= 0xe2b4a800 && sequence <= 0xe2b4ac00) {
          return F_true;
        }

        // Georgian Supplement: U+2D2E to U+2D2F.
        if (sequence >= 0xe2b4ae00 && sequence <= 0xe2b4af00) {
          return F_true;
        }

        // Tifinagh: U+2D68 to U+2D6E.
        if (sequence >= 0xe2b5a800 && sequence <= 0xe2b5ae00) {
          return F_true;
        }

        // Tifinagh: U+2D71 to U+2D7E.
        if (sequence >= 0xe2b5b100 && sequence <= 0xe2b5be00) {
          return F_true;
        }

        // Ethiopic Extended: U+2D97 to U+2D9F.
        if (sequence >= 0xe2b69700 && sequence <= 0xe2b69f00) {
          return F_true;
        }

        // Ethiopic Extended: U+2DA7, U+2DAF, U+2DB7, U+2DBF.
        if (sequence == 0xe2b6a700 || sequence == 0xe2b6af00 || sequence == 0xe2b6b700 || sequence == 0xe2b6bf00) {
          return F_true;
        }

        // Ethiopic Extended: U+2DC7, U+2DCF, U+2DD7, U+2DDF.
        if (sequence == 0xe2b78700 || sequence == 0xe2b78f00 || sequence == 0xe2b79700 || sequence == 0xe2b79f00) {
          return F_true;
        }

        // Supplemental Punctuation: U+2E43 to U+2E7F.
        if (sequence >= 0xe2b98300 && sequence <= 0xe2b9bf00) {
          return F_true;
        }

        // CJK Radicals Supplement: U+2E9A.
        if (sequence == 0xe2ba9a00) {
          return F_true;
        }

        // CJK Radicals Supplement: U+2EF4 to U+2EFF.
        if (sequence >= 0xe2bbb400 && sequence <= 0xe2bbbf00) {
          return F_true;
        }

        // Kangxi Radicals: U+2FD6 to U+2FDF.
        if (sequence >= 0xe2bf9600 && sequence <= 0xe2bf9f00) {
          return F_true;
        }

        // Ideographic Description Characters: U+2FFC to U+2FFF.
        if (sequence >= 0xe2bfbc00 && sequence <= 0xe2bfbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xe3) {

        // Hiragana: U+3040, U+3097, U+3098.
        if (sequence == 0xe3818000 || sequence == 0xe3829700 || sequence == 0xe3829800) {
          return F_true;
        }

        // Bopomofo: U+3100 to U+3104.
        if (sequence >= 0xe3848000 && sequence <= 0xe3848400) {
          return F_true;
        }

        // Bopomofo: U+312E to U+312F.
        if (sequence >= 0xe384ae00 && sequence <= 0xe384af00) {
          return F_true;
        }

        // Hangul Compatibility Jamo: U+3130 or U+318F.
        if (sequence == 0xe384b000 || sequence == 0xe3868f00) {
          return F_true;
        }

        // Bopomofo Extended: U+31BB to U+31BF.
        if (sequence >= 0xe386bb00 && sequence <= 0xe386bf00) {
          return F_true;
        }

        // CJK Strokes: U+31E4 to U+31EF.
        if (sequence >= 0xe387a400 && sequence <= 0xe387af00) {
          return F_true;
        }

        // Enclosed CJK Letters and Months: U+321F, U+32FF.
        if (sequence == 0xe3889f00 || sequence == 0xe38bbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) < 0xea) {

        // CJK Unified Ideographs Extension A: U+4DB6 to U+4DBF.
        if (sequence >= 0xe4b6b600 && sequence <= 0xe4b6bf00) {
          return F_true;
        }

        // CJK Unified Ideographs: U+9FD6 to U+9FFF.
        if (sequence >= 0xe9bf9600 && sequence <= 0xe9bfbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xea) {

        // Yi Syllables: U+A48D to U+A48F.
        if (sequence >= 0xea928d00 && sequence <= 0xea928f00) {
          return F_true;
        }

        // Yi Radicals: U+A4C7 to U+A4CF.
        if (sequence >= 0xea938700 && sequence <= 0xea938f00) {
          return F_true;
        }

        // Vai: U+A62C to U+A63F.
        if (sequence >= 0xea98ac00 && sequence <= 0xea98bf00) {
          return F_true;
        }

        // Bamum: U+A6F8 to U+A6FF.
        if (sequence >= 0xea9bb800 && sequence <= 0xea9bbf00) {
          return F_true;
        }

        // Latin Extended-D: U+A7AE to U+A7AF.
        if (sequence >= 0xea9eae00 && sequence <= 0xea9eaf00) {
          return F_true;
        }

        // Latin Extended-D: U+A7CB to U+A7CF.
        if (sequence >= 0xea9f8b00 && sequence <= 0xea9f8f00) {
          return F_true;
        }

        // Latin Extended-D: U+A7D2, U+A7D4.
        if (sequence == 0xea9f9200 || sequence == 0xea9f9400) {
          return F_true;
        }

        // Latin Extended-D: U+A7DA to U+A7F1.
        if (sequence >= 0xea9f9a00 && sequence <= 0xea9fb100) {
          return F_true;
        }

        // Syloti Nagri: U+A82C to U+A82F.
        if (sequence >= 0xeaa0ac00 && sequence <= 0xeaa0af00) {
          return F_true;
        }

        // Common Indic Number Forms: U+A83A to U+A83F.
        if (sequence >= 0xeaa0ba00 && sequence <= 0xeaa0bf00) {
          return F_true;
        }

        // Phags-pa: U+A878 to U+A87F.
        if (sequence >= 0xeaa1b800 && sequence <= 0xeaa1bf00) {
          return F_true;
        }

        // Saurashtra: U+A8C5 to U+A8CD.
        if (sequence >= 0xeaa38500 && sequence <= 0xeaa38d00) {
          return F_true;
        }

        // Saurashtra: U+A8DA to U+A8DF.
        if (sequence >= 0xeaa39a00 && sequence <= 0xeaa39f00) {
          return F_true;
        }

        // Devanagari Extended: U+A8FE to U+A8FF.
        if (sequence >= 0xeaa3be00 && sequence <= 0xeaa3bf00) {
          return F_true;
        }

        // Rejang: U+A954 to U+A95E.
        if (sequence >= 0xeaa59400 && sequence <= 0xeaa59e00) {
          return F_true;
        }

        // Hangul Jamo Extended-A: U+A97D to U+A97F.
        if (sequence >= 0xeaa5bd00 && sequence <= 0xeaa5bf00) {
          return F_true;
        }

        // Javanese: U+A9CE.
        if (sequence == 0xeaa78e00) {
          return F_true;
        }

        // Javanese: U+A9DA to U+A9DD.
        if (sequence >= 0xeaa79a00 && sequence <= 0xeaa79d00) {
          return F_true;
        }

        // Myanmar Extended-B: U+A9FF.
        if (sequence == 0xeaa7bf00) {
          return F_true;
        }

        // Cham: U+AA37 to U+AA3F.
        if (sequence >= 0xeaa8b700 && sequence <= 0xeaa8bf00) {
          return F_true;
        }

        // Cham: U+AA4E to U+AA4F.
        if (sequence >= 0xeaa98e00 && sequence <= 0xeaa98f00) {
          return F_true;
        }

        // Cham: U+AA5A to U+AA5B.
        if (sequence >= 0xeaa99a00 && sequence <= 0xeaa99b00) {
          return F_true;
        }

        // Tai Viet: U+AAC3 to U+AADA.
        if (sequence >= 0xeaab8300 && sequence <= 0xeaab9a00) {
          return F_true;
        }

        // Meetei Mayek Extensions: U+AAF7 to U+AAFF.
        if (sequence >= 0xeaabb700 && sequence <= 0xeaabbf00) {
          return F_true;
        }

        // Ethiopic Extended-A: U+AB00, U+AB07, U+AB08, U+AB0F.
        if (sequence == 0xeaac8000 || sequence == 0xeaac8700 || sequence == 0xeaac8800 || sequence == 0xeaac8f00) {
          return F_true;
        }

        // Ethiopic Extended-A: U+AB10.
        if (sequence == 0xeaac9000) {
          return F_true;
        }

        // Ethiopic Extended-A: U+AB17 to U+AB1F.
        if (sequence >= 0xeaac9700 && sequence <= 0xeaac9f00) {
          return F_true;
        }

        // Ethiopic Extended-A: U+AB27, U+AB2F.
        if (sequence == 0xeaaca700 || sequence == 0xeaacaf00) {
          return F_true;
        }

        // Latin Extended-E: U+AB66 to U+AB6F.
        if (sequence >= 0xeaada600 && sequence <= 0xeaadaf00) {
          return F_true;
        }

        // Meetei Mayek: U+ABEE to U+ABEF.
        if (sequence >= 0xeaafae00 && sequence <= 0xeaafaf00) {
          return F_true;
        }

        // Meetei Mayek: U+ABFA to U+ABFF.
        if (sequence >= 0xeaafba00 && sequence <= 0xeaafbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) < 0xed) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xed) {

        // Hangul Syllables: U+D7A4 to U+D7AF.
        if (sequence >= 0xed9ea400 && sequence <= 0xed9eaf00) {
          return F_true;
        }

        // Hangul Jamo Extended-B: U+D7C7 to U+D7CA.
        if (sequence >= 0xed9f8700 && sequence <= 0xed9f8a00) {
          return F_true;
        }

        // Hangul Jamo Extended-B: U+D7FC to U+D7FF.
        if (sequence >= 0xed9fbc00 && sequence <= 0xed9fbf00) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) < 0xef) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_1(sequence) == 0xef) {

        // CJK Compatibility Ideographs: U+FA6E to U+FA6F.
        if (sequence >= 0xefa9ae00 && sequence <= 0xefa9af00) {
          return F_true;
        }

        // CJK Compatibility Ideographs: U+FADA to U+FAFF.
        if (sequence >= 0xefab9a00 && sequence <= 0xefabbf00) {
          return F_true;
        }

        // Alphabetic Presentation Forms: U+FB07 to U+FB12.
        if (sequence >= 0xefac8700 && sequence <= 0xefac9200) {
          return F_true;
        }

        // Alphabetic Presentation Forms: U+FB18 to U+FB1C.
        if (sequence >= 0xefac9800 && sequence <= 0xefac9c00) {
          return F_true;
        }

        // Alphabetic Presentation Forms: U+FB37, U+FB3D, U+FB3F, U+FB42.
        if (sequence == 0xefacb700 || sequence == 0xefacbd00 || sequence == 0xefacbf00 || sequence == 0xefad8200) {
          return F_true;
        }

        // Alphabetic Presentation Forms: U+FB45.
        if (sequence == 0xefad8500) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FBC2 to U+FBD2.
        if (sequence >= 0xefaf8200 && sequence <= 0xefaf9200) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FD40 to U+FD4F.
        if (sequence >= 0xefb58000 && sequence <= 0xefb58f00) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FD90 to U+FD91.
        if (sequence >= 0xefb69000 && sequence <= 0xefb69100) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FDC8 to U+FDCF.
        if (sequence >= 0xefb78800 && sequence <= 0xefb78f00) {
          return F_true;
        }

        // Arabic Presentation Forms-A: U+FDFE to U+FDFF.
        if (sequence >= 0xefb7be00 && sequence <= 0xefb7bf00) {
          return F_true;
        }

        // Vertical Forms: U+FE1A to U+FE1F.
        if (sequence >= 0xefb89a00 && sequence <= 0xefb89f00) {
          return F_true;
        }

        // Small Form Variants: U+FE53, U+FE67.
        if (sequence == 0xefb99300 || sequence == 0xefb9a700) {
          return F_true;
        }

        // Small Form Variants: U+FE6C to U+FE6F.
        if (sequence >= 0xefb9ac00 && sequence <= 0xefb9af00) {
          return F_true;
        }

        // Arabic Presentation Forms-B: U+FE75, U+FEFD, U+FEFE.
        if (sequence == 0xefb9b500 || sequence == 0xefbbbd00 || sequence == 0xefbbbe00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FF00.
        if (sequence == 0xefbc8000) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFBF to U+FFC1.
        if (sequence >= 0xefbebf00 && sequence <= 0xefbf8100) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFC8 to U+FFC9.
        if (sequence >= 0xefbf8800 && sequence <= 0xefbf8900) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFD0 to U+FFD1.
        if (sequence >= 0xefbf9000 && sequence <= 0xefbf9100) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFD8 to U+FFD9.
        if (sequence >= 0xefbf9800 && sequence <= 0xefbf9900) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFDD to U+FFDF.
        if (sequence >= 0xefbf9d00 && sequence <= 0xefbf9f00) {
          return F_true;
        }

        // Halfwidth and Fullwidth Forms: U+FFE7, U+FFEF.
        if (sequence == 0xefbfa700 || sequence == 0xefbfaf00) {
          return F_true;
        }

        // Specials: U+FFF0 to U+FFF8.
        if (sequence >= 0xefbfb000 && sequence <= 0xefbfb800) {
          return F_true;
        }
      }

      return F_false;
    }

    if (macro_f_utf_char_t_to_char_1(sequence) < 0xf0) {
      // Do nothing.
    }
    else if (macro_f_utf_char_t_to_char_1(sequence) == 0xf0) {

      if (macro_f_utf_char_t_to_char_2(sequence) < 0x90) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x90) {

        // Linear B Syllabary: U+1000C, U+10027, U+1003B, U+1003E.
        if (sequence == 0xf090808c || sequence == 0xf09080a7 || sequence == 0xf09080bb || sequence == 0xf09080be) {
          return F_true;
        }

        // Linear B Syllabary: U+1004E, U+1004F.
        if (sequence == 0xf090818e || sequence == 0xf090818f) {
          return F_true;
        }

        // Linear B Syllabary: U+1005E to U+1007F.
        if (sequence >= 0xf090819e && sequence <= 0xf09081bf) {
          return F_true;
        }

        // Linear B Ideograms: U+100FB to U+100FF.
        if (sequence >= 0xf09083bb && sequence <= 0xf09083bf) {
          return F_true;
        }

        // Aegean Numbers: U+10103 to U+10106.
        if (sequence >= 0xf0908483 && sequence <= 0xf0908486) {
          return F_true;
        }

        // Aegean Numbers: U+10134 to U+10136.
        if (sequence >= 0xf09084b4 && sequence <= 0xf09084b6) {
          return F_true;
        }

        // Ancient Greek Numbers: U+1018D to U+1018F.
        if (sequence >= 0xf090868d && sequence <= 0xf090868f) {
          return F_true;
        }

        // Ancient Symbols: U+1019C to U+1019F.
        if (sequence >= 0xf090869c && sequence <= 0xf090869f) {
          return F_true;
        }

        // Ancient Symbols: U+101A1 to U+101CF.
        if (sequence >= 0xf09086a1 && sequence <= 0xf090878f) {
          return F_true;
        }

        // Phaistos Disc: U+101FE to U+101FF.
        if (sequence >= 0xf09087be && sequence <= 0xf09087bf) {
          return F_true;
        }

        // Lycian: U+1029D to U+1029F.
        if (sequence >= 0xf0908a9d && sequence <= 0xf0908a9f) {
          return F_true;
        }

        // Carian: U+102D1 to U+102DF.
        if (sequence >= 0xf0908b91 && sequence <= 0xf0908b9f) {
          return F_true;
        }

        // Coptic Epact Numbers: U+102FC to U+102FF.
        if (sequence >= 0xf0908bbc && sequence <= 0xf0908bbf) {
          return F_true;
        }

        // Old Italic: U+10324 to U+1032F.
        if (sequence >= 0xf0908ca4 && sequence <= 0xf0908caf) {
          return F_true;
        }

        // Old Permic: U+1037B to U+1037F.
        if (sequence >= 0xf0908dbb && sequence <= 0xf0908dbf) {
          return F_true;
        }

        // Gothic: U+1034B to U+1034F.
        if (sequence >= 0xf0908d8b && sequence <= 0xf0908d8f) {
          return F_true;
        }

        // Ugaritic: U+1039E.
        if (sequence == 0xf0908e9e) {
          return F_true;
        }

        // Old Persian: U+103C4 to U+103C7.
        if (sequence >= 0xf0908f84 && sequence <= 0xf0908f87) {
          return F_true;
        }

        // Old Persian: U+103D6 to U+103DF.
        if (sequence >= 0xf0908f96 && sequence <= 0xf0908f9f) {
          return F_true;
        }

        // Osmanya: U+104AA to U+104AF.
        if (sequence >= 0xf09092aa && sequence <= 0xf09092af) {
          return F_true;
        }

        // Elbasan: U+10528 to U+1052F.
        if (sequence >= 0xf09094a8 && sequence <= 0xf09094af) {
          return F_true;
        }

        // Caucasian Albanian: U+10564 to U+1056E.
        if (sequence >= 0xf09095a4 && sequence <= 0xf09095ae) {
          return F_true;
        }

        // Linear A: U+10737 to U+1077F.
        if (sequence >= 0xf0909cb7 && sequence <= 0xf0909dbf) {
          return F_true;
        }

        // Cypriot Syllabary: U+10806, U+10807, U+10809, U+10836.
        if (sequence == 0xf090a086 || sequence == 0xf090a087 || sequence == 0xf090a089 || sequence == 0xf090a0b6) {
          return F_true;
        }

        // Cypriot Syllabary: U+10839 to U+1083B.
        if (sequence >= 0xf090a0b9 && sequence <= 0xf090a0bb) {
          return F_true;
        }

        // Cypriot Syllabary: U+10839 to U+1083B.
        if (sequence >= 0xf090a0b9 && sequence <= 0xf090a0bb) {
          return F_true;
        }

        // Cypriot Syllabary: U+1083D to U+1083E.
        if (sequence >= 0xf090a0bd && sequence <= 0xf090a0be) {
          return F_true;
        }

        // Nabataean: U+1089F to U+108A6.
        if (sequence >= 0xf090a29f && sequence <= 0xf090a2a6) {
          return F_true;
        }

        // Hatran: U+108F3.
        if (sequence == 0xf090a3b3) {
          return F_true;
        }

        // Hatran: U+108F6 to U+108FA.
        if (sequence >= 0xf090a3b6 && sequence <= 0xf090a3ba) {
          return F_true;
        }

        // Phoenician: U+1091C to U+1091E.
        if (sequence >= 0xf090a49c && sequence <= 0xf090a49e) {
          return F_true;
        }

        // Lydian: U+1093A to U+1093E.
        if (sequence >= 0xf090a4ba && sequence <= 0xf090a4be) {
          return F_true;
        }

        // Meroitic Cursive: U+109B8 to U+109BB.
        if (sequence >= 0xf090a6b8 && sequence <= 0xf090a6bb) {
          return F_true;
        }

        // Meroitic Cursive: U+109D0 to U+109D1.
        if (sequence >= 0xf090a790 && sequence <= 0xf090a791) {
          return F_true;
        }

        // Kharoshthi: U+10A04.
        if (sequence == 0xf090a884) {
          return F_true;
        }

        // Kharoshthi: U+10A07 to U+10A0B.
        if (sequence >= 0xf090a887 && sequence <= 0xf090a88b) {
          return F_true;
        }

        // Kharoshthi: U+10A18.
        if (sequence == 0xf090a898) {
          return F_true;
        }

        // Kharoshthi: U+10A34 to U+10A37.
        if (sequence >= 0xf090a8b4 && sequence <= 0xf090a8b7) {
          return F_true;
        }

        // Kharoshthi: U+10A3B to U+10A3E.
        if (sequence >= 0xf090a8bb && sequence <= 0xf090a8be) {
          return F_true;
        }

        // Kharoshthi: U+10A48 to U+10A4F.
        if (sequence >= 0xf090a988 && sequence <= 0xf090a98f) {
          return F_true;
        }

        // Kharoshthi: U+10A59 to U+10A5F.
        if (sequence >= 0xf090a999 && sequence <= 0xf090a99f) {
          return F_true;
        }

        // Manichaean: U+10A5F to U+10AEA.
        if (sequence >= 0xf090a99f && sequence <= 0xf090abaa) {
          return F_true;
        }

        // Manichaean: U+10A5F to U+10AEA.
        if (sequence >= 0xf090a99f && sequence <= 0xf090abaa) {
          return F_true;
        }

        // Manichaean: U+10AF7 to U+10AFF.
        if (sequence >= 0xf090abb7 && sequence <= 0xf090abbf) {
          return F_true;
        }

        // Avestan: U+10B36 to U+10B38.
        if (sequence >= 0xf090acb6 && sequence <= 0xf090acb8) {
          return F_true;
        }

        // Inscriptional Parthian: U+10B56 to U+10B57.
        if (sequence >= 0xf090ad96 && sequence <= 0xf090ad97) {
          return F_true;
        }

        // Inscriptional Pahlavi: U+10B73 to U+10B77.
        if (sequence >= 0xf090adb3 && sequence <= 0xf090adb7) {
          return F_true;
        }

        // Psalter Pahlavi: U+10B92 to U+10B98.
        if (sequence >= 0xf090ae92 && sequence <= 0xf090ae98) {
          return F_true;
        }

        // Psalter Pahlavi: U+10B9D to U+10BA8.
        if (sequence >= 0xf090ae9d && sequence <= 0xf090aea8) {
          return F_true;
        }

        // Old Turkic: U+10C49 to U+10C4F.
        if (sequence >= 0xf090b189 && sequence <= 0xf090b18f) {
          return F_true;
        }

        // Old Hungarian: U+10CB3 to U+10CBF.
        if (sequence >= 0xf090b2b3 && sequence <= 0xf090b2bf) {
          return F_true;
        }

        // Old Hungarian: U+10CF3 to U+10CF9.
        if (sequence >= 0xf090b3b3 && sequence <= 0xf090b3b9) {
          return F_true;
        }

        // Rumi Numeral Symbols: U+10E7F.
        if (sequence == 0xf090b9bf) {
          return F_true;
        }

        // Arabic Extended-C: U+10EC0 to U+10EFC.
        if (sequence >= 0xf090bb80 && sequence <= 0xf090bbbc) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Brahmi: U+1104E to U+11051.
        if (sequence >= 0xf091818e && sequence <= 0xf0918191) {
          return F_true;
        }

        // Brahmi: U+11070 to U+1107E.
        if (sequence >= 0xf09181b0 && sequence <= 0xf09181be) {
          return F_true;
        }

        // Kaithi: U+110C2 to U+110CF.
        if (sequence >= 0xf0918382 && sequence <= 0xf091838f) {
          return F_true;
        }

        // Sora Sompeng: U+110E9 to U+110EF.
        if (sequence >= 0xf09183a9 && sequence <= 0xf09183af) {
          return F_true;
        }

        // Sora Sompeng: U+110FA to U+110FF.
        if (sequence >= 0xf09183ba && sequence <= 0xf09183bf) {
          return F_true;
        }

        // Devanagari Extended A: U+11B0A to U+11B5F.
        if (sequence >= 0xf091ac8a && sequence <= 0xf091ad9f) {
          return F_true;
        }

        // Kawi: U+11F11.
        if (sequence == 0xf091bc91) {
          return F_true;
        }

        // Kawi: U+11F3B to U+11F3D.
        if (sequence >= 0xf091bcbb && sequence <= 0xf091bcbd) {
          return F_true;
        }

        // Kawi: U+11F5A to U+11F5F.
        if (sequence >= 0xf091bd9a && sequence <= 0xf091bd9f) {
          return F_true;
        }

        // Chakma: U+11135.
        if (sequence == 0xf09184b5) {
          return F_true;
        }

        // Chakma: U+11144 to U+1114F.
        if (sequence >= 0xf0918584 && sequence <= 0xf091858f) {
          return F_true;
        }

        // Mahajani: U+11177 to U+1117F.
        if (sequence >= 0xf09185b7 && sequence <= 0xf09185bf) {
          return F_true;
        }

        // Sharada: U+111CE to U+111CF.
        if (sequence >= 0xf091878e && sequence <= 0xf091878f) {
          return F_true;
        }

        // Sinhala Archaic Numbers: U+111E0.
        if (sequence == 0xf09187a0) {
          return F_true;
        }

        // Sinhala Archaic Numbers: U+111F5 to U+111FF.
        if (sequence >= 0xf09187b5 && sequence <= 0xf09187bf) {
          return F_true;
        }

        // Khojki: U+11212.
        if (sequence == 0xf0918892) {
          return F_true;
        }

        // Khojki: U+11242 to U+1124F.
        if (sequence >= 0xf0918982 && sequence <= 0xf091898f) {
          return F_true;
        }

        // Multani: U+11287, U+11289, U+1128E, U+1129E.
        if (sequence == 0xf0918a87 || sequence == 0xf0918a89 || sequence == 0xf0918a8e || sequence == 0xf0918a9e) {
          return F_true;
        }

        // Multani: U+112AA to U+112AF.
        if (sequence >= 0xf0918aaa && sequence <= 0xf0918aaf) {
          return F_true;
        }

        // Khudawadi: U+112EB to U+112EF.
        if (sequence >= 0xf0918bab && sequence <= 0xf0918baf) {
          return F_true;
        }

        // Khudawadi: U+112FA to U+112FF.
        if (sequence >= 0xf0918bba && sequence <= 0xf0918bbf) {
          return F_true;
        }

        // Grantha: U+11304.
        if (sequence == 0xf0918c84) {
          return F_true;
        }

        // Grantha: U+1130D to U+1130E.
        if (sequence >= 0xf0918c8d && sequence <= 0xf0918c8e) {
          return F_true;
        }

        // Grantha: U+11311 to U+11312.
        if (sequence >= 0xf0918c91 && sequence <= 0xf0918c92) {
          return F_true;
        }

        // Grantha: U+11329, U+11331, U+11334.
        if (sequence == 0xf0918ca9 || sequence == 0xf0918cb1 || sequence == 0xf0918cb4) {
          return F_true;
        }

        // Grantha: U+1133A to U+1133B.
        if (sequence >= 0xf0918cb4 && sequence <= 0xf0918cbb) {
          return F_true;
        }

        // Grantha: U+11345 to U+11346.
        if (sequence >= 0xf0918d85 && sequence <= 0xf0918d86) {
          return F_true;
        }

        // Grantha: U+11349 to U+1134A.
        if (sequence >= 0xf0918d89 && sequence <= 0xf0918d8a) {
          return F_true;
        }

        // Grantha: U+1134E to U+1134F.
        if (sequence >= 0xf0918d8e && sequence <= 0xf0918d8f) {
          return F_true;
        }

        // Grantha: U+11351 to U+11356.
        if (sequence >= 0xf0918d91 && sequence <= 0xf0918d96) {
          return F_true;
        }

        // Grantha: U+11358 to U+1135C.
        if (sequence >= 0xf0918d98 && sequence <= 0xf0918d9c) {
          return F_true;
        }

        // Grantha: U+11364 to U+11365.
        if (sequence >= 0xf0918da4 && sequence <= 0xf0918da5) {
          return F_true;
        }

        // Grantha: U+1136D to U+1136F.
        if (sequence >= 0xf0918dad && sequence <= 0xf0918daf) {
          return F_true;
        }

        // Grantha: U+11375 to U+1137F.
        if (sequence >= 0xf0918db5 && sequence <= 0xf0918dbf) {
          return F_true;
        }

        // Tirhuta: U+114C8 to U+114CF.
        if (sequence >= 0xf0919388 && sequence <= 0xf091938f) {
          return F_true;
        }

        // Tirhuta: U+114DA to U+114DF.
        if (sequence >= 0xf091939a && sequence <= 0xf091939f) {
          return F_true;
        }

        // Siddham: U+115B6 to U+115B7.
        if (sequence >= 0xf09196b6 && sequence <= 0xf09196b7) {
          return F_true;
        }

        // Siddham: U+115DE to U+115FF.
        if (sequence >= 0xf091979e && sequence <= 0xf09197bf) {
          return F_true;
        }

        // Modi: U+11645 to U+1164F.
        if (sequence >= 0xf0919985 && sequence <= 0xf091998f) {
          return F_true;
        }

        // Modi: U+1165A to U+1165F.
        if (sequence >= 0xf091999a && sequence <= 0xf091999f) {
          return F_true;
        }

        // Takri: U+116B8 to U+116BF.
        if (sequence >= 0xf0919ab8 && sequence <= 0xf0919abf) {
          return F_true;
        }

        // Takri: U+116CA to U+116CF.
        if (sequence >= 0xf0919b8a && sequence <= 0xf0919b8f) {
          return F_true;
        }

        // Ahom: U+1171A to U+1171C.
        if (sequence >= 0xf0919c9a && sequence <= 0xf0919c9c) {
          return F_true;
        }

        // Ahom: U+1172C to U+1172F.
        if (sequence >= 0xf0919cac && sequence <= 0xf0919caf) {
          return F_true;
        }

        // Warang Citi: U+118F3 to U+118FE.
        if (sequence >= 0xf091a3b3 && sequence <= 0xF091A3BE) {
          return F_true;
        }

        // Pau Cin Hau: U+11AF9 to U+11AFF.
        if (sequence >= 0xf091abb9 && sequence <= 0xf091abbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x91) {

        // Cuneiform: U+1239A to U+123FF.
        if (sequence >= 0xf0928e9a && sequence <= 0xf0928fbf) {
          return F_true;
        }

        // Cuneiform Numbers and Punctuation: U+1246F to U+1247F.
        if (sequence >= 0xf09291af && sequence <= 0xf09291bf) {
          return F_true;
        }

        // Early Dynastic Cuneiform: U+12544 to U+1254F.
        if (sequence >= 0xf0929584 && sequence <= 0xf092958f) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x93) {

        // Egyptian Hieroglyph Format Controls: U+13456 to U+1345F.
        if (sequence >= 0xf0939196 && sequence <= 0xf093919f) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x94) {

        // Anatolian Hieroglyphs: U+14647 to U+1467F.
        if (sequence >= 0xf0949987 && sequence <= 0xf09499bf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x95) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x96) {

        // Bamum Supplement: U+16A39 to U+16A3F.
        if (sequence >= 0xf096a8b9 && sequence <= 0xf096a8bf) {
          return F_true;
        }

        // Mro: U+16A5F.
        if (sequence == 0xf096a99f) {
          return F_true;
        }

        // Mro: U+16A6A to U+16A6D.
        if (sequence >= 0xf096a9aa && sequence <= 0xf096a9ad) {
          return F_true;
        }

        // Bassa Vah: U+16AEE to U+16AEF.
        if (sequence >= 0xf096abae && sequence <= 0xf096abaf) {
          return F_true;
        }

        // Bassa Vah: U+16AF6 to U+16AFF.
        if (sequence >= 0xf096abb6 && sequence <= 0xf096abb6) {
          return F_true;
        }

        // Pahawh Hmong: U+16B46 to U+16B4F.
        if (sequence >= 0xf096ad86 && sequence <= 0xf096ad8f) {
          return F_true;
        }

        // Pahawh Hmong: U+16B5A, U+16B62.
        if (sequence == 0xf096ad9a || sequence == 0xf096ada2) {
          return F_true;
        }

        // Pahawh Hmong: U+16B78 to U+16B7C.
        if (sequence >= 0xf096adb8 && sequence <= 0xf096adbc) {
          return F_true;
        }

        // Miao: U+16F45 to U+16F4F.
        if (sequence >= 0xf096bd85 && sequence <= 0xf096bd8f) {
          return F_true;
        }

        // Miao: U+16F7F to U+16F8E.
        if (sequence >= 0xf096bdbf && sequence <= 0xf096be8e) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) < 0x9b) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9b) {

        // Kana Supplement: U+1B002 to U+1B0FF.
        if (sequence >= 0xf09b8082 && sequence <= 0xf09b83bf) {
          return F_true;
        }

        // Small Kana Extension: U+1B130, U+1B131.
        if (sequence == 0xf09b84b0 || sequence == 0xf09b84b1) {
          return F_true;
        }

        // Small Kana Extension: U+1B133 to U+1B14F.
        if (sequence >= 0xf09b84b3 && sequence <= 0xf09b858f) {
          return F_true;
        }

        // Small Kana Extension: U+1B153, U+1B154.
        if (sequence == 0xf09b8593 || sequence == 0xf09b8594) {
          return F_true;
        }

        // Small Kana Extension: U+1B156 to U+1B163.
        if (sequence >= 0xf09b8596 && sequence <= 0xf09b85a3) {
          return F_true;
        }

        // Small Kana Extension: U+1B168 to U+1B16F.
        if (sequence >= 0xf09b85a8 && sequence <= 0xf09b85af) {
          return F_true;
        }

        // Duployan: U+1BC6B to U+1BC6F.
        if (sequence >= 0xf09bb1ab && sequence <= 0xf09bb1af) {
          return F_true;
        }

        // Duployan: U+1BC7D to U+1BC7F.
        if (sequence >= 0xf09bb1bd && sequence <= 0xf09bb1bf) {
          return F_true;
        }

        // Duployan: U+1BC89 to U+1BC8F.
        if (sequence >= 0xf09bb289 && sequence <= 0xf09bb28f) {
          return F_true;
        }

        // Duployan: U+1BC9A to U+1BC9B.
        if (sequence >= 0xf09bb29a && sequence <= 0xf09bb29b) {
          return F_true;
        }

        // Shorthand Format Controls: U+1BCA4 to U+1BCAF.
        if (sequence >= 0xf09bb2a4 && sequence <= 0xf09bb2af) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) < 0x9d) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9d) {

        // Byzantine Musical Symbols: U+1D0F6 to U+1D0FF.
        if (sequence >= 0xf09d83b6 && sequence <= 0xf09d83bf) {
          return F_true;
        }

        // Musical Symbols: U+1D127 to U+1D128.
        if (sequence >= 0xf09d84a7 && sequence <= 0xf09d84a8) {
          return F_true;
        }

        // Musical Symbols: U+1D1E9 to U+1D1FF.
        if (sequence >= 0xf09d87a9 && sequence <= 0xf09d87bf) {
          return F_true;
        }

        // Ancient Greek Musical Notation: U+1D246 to U+1D24F.
        if (sequence >= 0xf09d8986 && sequence <= 0xf09d898f) {
          return F_true;
        }

        // Tai Xuan Jing Symbols: U+1D357 to U+1D35F.
        if (sequence >= 0xf09d8d97 && sequence <= 0xf09d8d9f) {
          return F_true;
        }

        // Kaktovik Numerals: U+1D2D4 to U+1D2DF.
        if (sequence >= 0xf09d8b94 && sequence <= 0xf09d8b9f) {
          return F_true;
        }

        // Counting Rod Numerals: U+1D372 to U+1D37F.
        if (sequence >= 0xf09d8db2 && sequence <= 0xf09d8dbf) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D506.
        if (sequence == 0xf09d9486) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D50B to U+1D50C.
        if (sequence >= 0xf09d948b && sequence <= 0xf09d948c) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D515, U+1D51D, U+1D53A, U+1D53F.
        if (sequence == 0xf09d9495 || sequence == 0xf09d949d || sequence == 0xf09d94ba || sequence == 0xf09d94bf) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D515.
        if (sequence == 0xf09d9495) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D547 to U+1D549.
        if (sequence >= 0xf09d9587 && sequence <= 0xf09d9589) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D551, U+1D6A6, U+1D6A7.
        if (sequence == 0xf09d9591 || sequence == 0xf09d9aa6 || sequence == 0xf09d9aa7) {
          return F_true;
        }

        // Mathematical Alphanumeric Symbols: U+1D7CC to U+1D7CD.
        if (sequence >= 0xf09d9f8c && sequence <= 0xf09d9f8d) {
          return F_true;
        }

        // Sutton SignWriting: U+1DA8C to U+1DA9A.
        if (sequence >= 0xf09daa8c && sequence <= 0xf09daa9a) {
          return F_true;
        }

        // Sutton SignWriting: U+1DAA0.
        if (sequence == 0xf09daaa0) {
          return F_true;
        }

        // Latin Extended-G: U+1DF1F to U+1DF24.
        if (sequence >= 0xf09dbc9f && sequence <= 0xf09dbca4) {
          return F_true;
        }

        // Latin Extended-G: U+1DF2B to U+1DFFF.
        if (sequence >= 0xf09dbcab && sequence <= 0xf09dbfbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9e) {

        // Cyrillic Extended-D: U+1E06E to U+1E08E.
        if (sequence >= 0xf09e81ae && sequence <= 0xf09e828e) {
          return F_true;
        }

        // Nag Mundari: U+1E4FA to U+1E4FF.
        if (sequence >= 0xf09e93ba && sequence <= 0xf09e93bf) {
          return F_true;
        }

        // Mende Kikakui: U+1E8C5 to U+1E8C6.
        if (sequence >= 0xf09ea385 && sequence <= 0xf09ea386) {
          return F_true;
        }

        // Mende Kikakui: U+1E8D7 to U+1E8DF.
        if (sequence >= 0xf09ea397 && sequence <= 0xf09ea39f) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE04, U+1EE20, U+1EE23.
        if (sequence == 0xf09eb884 || sequence == 0xf09eb8a0 || sequence == 0xf09eb8a3) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE25 to U+1EE26.
        if (sequence >= 0xf09eb8a5 && sequence <= 0xf09eb8a6) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE28, U+1EE33, U+1EE38, U+1EE3A.
        if (sequence == 0xf09eb8a8 || sequence == 0xf09eb8b3 || sequence == 0xf09eb8b8 || sequence == 0xf09eb8ba) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE3C to U+1EE41.
        if (sequence >= 0xf09eb8bc && sequence <= 0xf09eb981) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE43 to U+1EE46.
        if (sequence >= 0xf09eb983 && sequence <= 0xf09eb986) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE48, U+1EE4A, U+1EE4C, U+1EE50.
        if (sequence == 0xf09eb988 || sequence == 0xf09eb98a || sequence == 0xf09eb98c || sequence == 0xf09eb990) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE53, U+1EE55, U+1EE56, U+1EE58.
        if (sequence == 0xf09eb993 || sequence == 0xf09eb995 || sequence == 0xf09eb996 || sequence == 0xf09eb998) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE5A, U+1EE5C, U+1EE5E, U+1EE60.
        if (sequence == 0xf09eb99a || sequence == 0xf09eb99c || sequence == 0xf09eb99e || sequence == 0xf09eb9a0) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE63, U+1EE65, U+1EE66, U+1EE6B.
        if (sequence == 0xf09eb9a3 || sequence == 0xf09eb9a5 || sequence == 0xf09eb9a6 || sequence == 0xf09eb9ab) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE73, U+1EE78, U+1EE7D, U+1EE7F.
        if (sequence == 0xf09eb9b3 || sequence == 0xf09eb9b8 || sequence == 0xf09eb9bd || sequence == 0xf09eb9bf) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE8A.
        if (sequence == 0xf09eba8a) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EE9C to U+1EEA0.
        if (sequence >= 0xf09eba9c && sequence <= 0xf09ebaa0) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EEA4, U+1EEAA.
        if (sequence == 0xf09ebaa4 || sequence == 0xf09ebaaa) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EEBC to U+1EEEF.
        if (sequence >= 0xf09ebabc && sequence <= 0xf09ebbaf) {
          return F_true;
        }

        // Arabic Mathematical Alphabetic Symbols: U+1EEF2 to U+1EEFF.
        if (sequence >= 0xf09ebbb2 && sequence <= 0xf09ebbbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0x9f) {

        // Mahjong Tiles: U+1F02C to U+1F02F.
        if (sequence >= 0xf09f80ac && sequence <= 0xf09f80af) {
          return F_true;
        }

        // Domino Tiles: U+1F094 to U+1F09F.
        if (sequence >= 0xf09f8294 && sequence <= 0xf09f829f) {
          return F_true;
        }

        // Playing Cards: U+1F0AF to U+1F0B0.
        if (sequence >= 0xf09f82af && sequence <= 0xf09f82b0) {
          return F_true;
        }

        // Playing Cards: U+1F0C0, U+1F0D0.
        if (sequence == 0xf09f8380 || sequence == 0xf09f8390) {
          return F_true;
        }

        // Playing Cards: U+1F0F6 to U+1F0FF.
        if (sequence >= 0xf09f83b6 && sequence <= 0xf09f83bf) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F10D to U+1F10F.
        if (sequence >= 0xf09f848d && sequence <= 0xf09f848f) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F12F.
        if (sequence == 0xf09f84af) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F16C to U+1F16F.
        if (sequence >= 0xf09f85ac && sequence <= 0xf09f85af) {
          return F_true;
        }

        // Enclosed Alphanumeric Supplement: U+1F19B to U+1F1E5.
        if (sequence >= 0xf09f869b && sequence <= 0xf09f87a5) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F203 to U+1F20F.
        if (sequence >= 0xf09f8883 && sequence <= 0xf09f888f) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F23B to U+1F23F.
        if (sequence >= 0xf09f88bb && sequence <= 0xf09f88bf) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F249 to U+1F24F.
        if (sequence >= 0xf09f8989 && sequence <= 0xf09f898f) {
          return F_true;
        }

        // Enclosed Ideographic Supplement: U+1F252 to U+1F2FF.
        if (sequence >= 0xf09f8992 && sequence <= 0xf09f8bbf) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6D8 to U+1F6DB.
        if (sequence >= 0xf09f9b98 && sequence <= 0xf09f9b9b) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6ED to U+1F6EF.
        if (sequence >= 0xf09f9bad && sequence <= 0xf09f9baf) {
          return F_true;
        }

        // Transport and Map Symbols: U+1F6FD to U+1F6FF.
        if (sequence >= 0xf09f9bbd && sequence <= 0xf09f9bbf) {
          return F_true;
        }

        // Alchemical Symbols: U+1F777 to U+1F77A.
        if (sequence >= 0xf09f9db7 && sequence <= 0xf09f9dba) {
          return F_true;
        }

        // Geometric Shapes Extended: U+1F7DA to U+1F7DF.
        if (sequence >= 0xf09f9f9a && sequence <= 0xf09f9f9f) {
          return F_true;
        }

        // Geometric Shapes Extended: U+1F7EC to U+1F7EF.
        if (sequence >= 0xf09f9fac && sequence <= 0xf09f9faf) {
          return F_true;
        }

        // Geometric Shapes Extended: U+1F7F1 to U+1F7FF.
        if (sequence >= 0xf09f9fb1 && sequence <= 0xf09f9fbf) {
          return F_true;
        }

        // Supplemental Arrows C: U+1F80C to U+1F80F.
        if (sequence >= 0xf09fa08c && sequence <= 0xf09fa08f) {
          return F_true;
        }

        // Supplemental Arrows C: U+1F848 to U+1F84F.
        if (sequence >= 0xf09fa188 && sequence <= 0xf09fa18f) {
          return F_true;
        }

        // Supplemental Arrows C: U+1F85A to U+1F85F.
        if (sequence >= 0xf09fa19a && sequence <= 0xf09fa19f) {
          return F_true;
        }

        // Supplemental Arrows C: U+1F888 to U+1F88F.
        if (sequence >= 0xf09fa288 && sequence <= 0xf09fa28f) {
          return F_true;
        }

        // Supplemental Arrows C: U+1F8AE to U+1F8FF.
        if (sequence >= 0xf09fa2ae && sequence <= 0xf09fa3bf) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs: U+1F900 to U+1F90F.
        if (sequence >= 0xf09fa480 && sequence <= 0xf09fa48f) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs: U+1F919 to U+1F97F.
        if (sequence >= 0xf09fa499 && sequence <= 0xf09fa5bf) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs: U+1F985 to U+1F9BF.
        if (sequence >= 0xf09fa685 && sequence <= 0xf09fa6bf) {
          return F_true;
        }

        // Supplemental Symbols and Pictographs: U+1F9C1 to U+1F9FF.
        if (sequence >= 0xf09fa781 && sequence <= 0xf09fa7bf) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA7D to U+1FA7F.
        if (sequence >= 0xf09fa9bd && sequence <= 0xf09fa9bf) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FA89 to U+1FA8F.
        if (sequence >= 0xf09faa89 && sequence <= 0xf09faa8f) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FABE.
        if (sequence == 0xf09faabe) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAC6 to U+1FACD.
        if (sequence >= 0xf09fab86 && sequence <= 0xf09fab8d) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FADC to U+1FADF.
        if (sequence >= 0xf09fab9c && sequence <= 0xf09fab9f) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAE9 to U+1FAEF.
        if (sequence >= 0xf09faba9 && sequence <= 0xf09fabaf) {
          return F_true;
        }

        // Symbols and Pictographs Extended-A: U+1FAF9 to U+1FAFF.
        if (sequence >= 0xf09fabb9 && sequence <= 0xf09fabbf) {
          return F_true;
        }

        // Not Assigned: U+1FB00 to U+1FFFF.
        if (sequence >= 0xf09fac80 && sequence <= 0xf09fbfbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) < 0xaa) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) < 0xb0) {

        // CJK Unified Ideographs Extension B: U+2A6D7 to U+2A6FF.
        if (sequence >= 0xf0aa9b97 && sequence <= 0xf0aa9bbf) {
          return F_true;
        }

        // CJK Unified Ideographs Extension C: U+2B735 to U+2B73F.
        if (sequence >= 0xf0ab9cb5 && sequence <= 0xf0ab9cbf) {
          return F_true;
        }

        // CJK Unified Ideographs Extension D: U+2B81E to U+2B81F.
        if (sequence >= 0xf0aba09e && sequence <= 0xf0aba09f) {
          return F_true;
        }

        // CJK Unified Ideographs Extension E: U+2CEA2 to U+2CEAF.
        if (sequence >= 0xf0acbaa2 && sequence <= 0xf0acbaaf) {
          return F_true;
        }

        // CJK Unified Ideographs Extension F: U+2EBE1 to U+2EBEF.
        if (sequence >= 0xf0aeafa1 && sequence <= 0xf0aeafaf) {
          return F_true;
        }

        // Not Assigned: U+2FF80 to U+2FFFF.
        if (sequence >= 0xf0afbe80 && sequence <= 0xf0afbfbf) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) < 0xb1) {
        // Do nothing.
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0xb1) {

        // CJK Unified Ideographs Extension G: U+3134B to U+3134F.
        if (sequence >= 0xf0b18d8b && sequence <= 0xf0b18d8f) {
          return F_true;
        }

        // Tertiary Ideographic Plane: U+30000 to U+3134F.
        if (sequence >= 0xf0b08080 && sequence <= 0xf0b18d8f) {
          return F_true;
        }
      }
      else if (macro_f_utf_char_t_to_char_2(sequence) == 0xbf) {

        // Tertiary Ideographic Plane: U+323AF to U+3FFFD.
        if (sequence >= 0xf0b28eaf && sequence <= 0xf0bfbfbd) {
          return F_true;
        }

        // Not Assigned: U+3FF80 to U+3FFFF.
        if (sequence >= 0xf0bfbe80 && sequence <= 0xf0bfbfbf) {
          return F_true;
        }
      }
    }
    else if (macro_f_utf_char_t_to_char_1(sequence) < 0xf1) {

      // Plane 5: U+40000 to U+4FFFF.
      if (sequence >= 0xf1808080 && sequence <= 0xf18fbfbf) {
        return F_true;
      }

      // Plane 6: U+50000 to U+5FFFF.
      if (sequence >= 0xf1908080 && sequence <= 0xf19fbfbf) {
        return F_true;
      }

      // Plane 7: U+60000 to U+6FFFF.
      if (sequence >= 0xf1a08080 && sequence <= 0xf1afbfbf) {
        return F_true;
      }

      // Plane 8: U+70000 to U+7FFFF.
      if (sequence >= 0xf1b08080 && sequence <= 0xf1bfbfbf) {
        return F_true;
      }
    }
    else if (macro_f_utf_char_t_to_char_1(sequence) < 0xf2) {

      // Plane 9: U+80000 to U+8FFFF.
      if (sequence >= 0xf2808080 && sequence <= 0xf28fbfbf) {
        return F_true;
      }

      // Plane 10: U+90000 to U+9FFFF.
      if (sequence >= 0xf2908080 && sequence <= 0xf29fbfbf) {
        return F_true;
      }

      // Plane 11: U+A0000 to U+AFFFF.
      if (sequence >= 0xf2a08080 && sequence <= 0xf2afbfbf) {
        return F_true;
      }

      // Plane 12: U+B0000 to U+BFFFF.
      if (sequence >= 0xf2b08080 && sequence <= 0xf2bfbfbf) {
        return F_true;
      }
    }
    else if (macro_f_utf_char_t_to_char_1(sequence) < 0xf3) {

      // Plane 13: U+C0000 to U+CFFFF.
      if (sequence >= 0xf3808080 && sequence <= 0xf38fbfbf) {
        return F_true;
      }

      // Plane 14: U+D0000 to U+DFFFF.
      if (sequence >= 0xf3908080 && sequence <= 0xf39fbfbf) {
        return F_true;
      }

      // Supplementary Special Purpose, Tags: U+E0000.
      if (sequence == 0xf3a08080) {
        return F_true;
      }

      // Supplementary Special Purpose, Tags: U+E0002 to U+E001F.
      if (sequence >= 0xf3a08082 && sequence <= 0xf3a0809f) {
        return F_true;
      }

      // Supplementary Special Purpose, between Tags and Variation Selectors Supplement: U+E0080 to U+E00FF.
      if (sequence >= 0xf3a08280 && sequence <= 0xf3a083bf) {
        return F_true;
      }

      // Supplementary Special Purpose, after Variation Selectors Supplement: U+E01F0 to U+EFFFD.
      if (sequence >= 0xf3a087b0 && sequence <= 0xf3afbfbd) {
        return F_true;
      }

      // Not Assigned: U+EFF80 to U+EFFFF.
      if (sequence >= 0xf3afbe80 && sequence <= 0xf3afbfbf) {
        return F_true;
      }

      // Not Assigned: U+EFFFE to U+EFFFF.
      if (sequence >= 0xf3bfbfbe && sequence <= 0xf3bfbfbf) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_unassigned_) || !defined(_di_f_utf_is_unassigned_)

#ifdef __cplusplus
} // extern "C"
#endif

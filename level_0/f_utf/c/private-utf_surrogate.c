#include "utf.h"
#include "private-utf.h"
#include "private-utf_surrogate.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_surrogate_) || !defined(_di_f_utf_is_surrogate_)
  f_status_t private_f_utf_character_is_surrogate(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 3) {

      if (macro_f_utf_char_t_to_char_1(character) == 0xed) {

        // High Surrogates: U+D800 to U+DB7F.
        if (character >= 0xeda08000 && character <= 0xedadbf00) {
          return F_true;
        }

        // High Private Use Surrogates: U+DB80 to U+DBFF.
        if (character >= 0xedae8000 && character <= 0xedafbf00) {
          return F_true;
        }

        // Low Surrogates: U+DC00 to U+DFFF.
        if (character >= 0xedb08000 && character <= 0xedbfbf00) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_surrogate_) || !defined(_di_f_utf_is_surrogate_)

#ifdef __cplusplus
} // extern "C"
#endif

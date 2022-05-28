#include "utf.h"
#include "private-utf.h"
#include "private-utf_phonetic.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)
  f_status_t private_f_utf_character_is_phonetic(const f_utf_char_t character) {

    if (macro_f_utf_char_t_width_is(character) == 3) {

      // Phonetic Extensions: U+1D00 to U+1D7F.
      if (character >= 0xe1b48000 && character <= 0xe1b5bf00) {
        return F_true;
      }

      // Phonetic Extensions Supplement: U+1D80 to U+1DBF.
      if (character >= 0xe1b6bf00 && character <= 0xe1b6bf00) {
        return F_true;
      }
    }

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)

#ifdef __cplusplus
} // extern "C"
#endif

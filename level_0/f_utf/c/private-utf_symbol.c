#include "utf.h"
#include "private-utf.h"
#include "private-utf_symbol.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)
  f_status_t private_f_utf_character_is_symbol(const f_utf_char_t character) {

    // @todo handle all Unicode "symbol".

    return F_false;
  }
#endif // !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)

#ifdef __cplusplus
} // extern "C"
#endif

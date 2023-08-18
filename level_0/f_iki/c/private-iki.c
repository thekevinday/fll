#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)
  f_status_t private_f_iki_content_partial_is(const f_string_t buffer, const f_number_unsigned_t length, const f_char_t quote) {

    f_number_unsigned_t delimits = 0;

    for (f_number_unsigned_t i = 0; i < length; i += macro_f_utf_byte_width(buffer[i])) {

      if (buffer[i] == quote) {
        if (delimits && delimits % 2) {
          delimits = 0;

          continue;
        }

        return F_false;
      }

      if (buffer[i] == f_iki_syntax_slash_s.string[0]) {
        ++delimits;
      }
      else {
        delimits = 0;
      }
    } // for

    return F_true;
  }
#endif // !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)

#if !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)
  f_status_t private_f_iki_object_partial_is(const f_string_t buffer, const f_number_unsigned_t length) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = 0; i < length; i += macro_f_utf_byte_width(buffer[i])) {

      status = f_utf_is_word_dash_plus(buffer + i, length - i, F_false);
      if (F_status_is_error(status)) return status;

      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)

#ifdef __cplusplus
} // extern "C"
#endif

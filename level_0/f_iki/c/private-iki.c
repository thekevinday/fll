#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)
  f_status_t private_f_iki_content_partial_is(const f_string_static_t buffer, const f_string_range_t range, const uint8_t quote) {
    f_string_length_t delimits = 0;

    for (f_string_length_t i = 0; i < buffer.used; i++) {

      if (buffer.string[i] == quote) {
        if (delimits && delimits % 2) {
          delimits = 0;
          continue;
        }

        return F_false;
      }
      else if (buffer.string[i] == f_iki_syntax_slash) {
        delimits++;
      }
      else {
        delimits = 0;
      }
    } // for

    return F_true;
  }
#endif // !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)

#if !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)
  f_status_t private_f_iki_object_partial_is(const f_string_static_t buffer, const f_string_range_t range) {
    f_status_t status = F_none;

    for (f_string_length_t i = 0; i < buffer.used; i++) {

      status = f_utf_is_word(buffer.string + i, buffer.used - i, F_false);
      if (F_status_is_error(status)) return status;

      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)

#ifdef __cplusplus
} // extern "C"
#endif

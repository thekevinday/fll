#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_read_)
  f_status_t private_f_iki_seek_special(const f_string_static_t buffer, f_string_range_t *range) {

    f_status_t status = F_none;
    f_array_length_t width_max = 0;

    while (range->start <= range->stop && range->start < buffer.used) {

      if (buffer.string[range->start] == f_iki_syntax_separator_s[0]) {
        break;
      }

      if (buffer.string[range->start] == F_iki_syntax_quote_double_s[0]) {
        break;
      }

      if (buffer.string[range->start] == F_iki_syntax_quote_single_s[0]) {
        break;
      }

      if (buffer.string[range->start] == F_iki_syntax_slash_s[0]) {
        break;
      }

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }

      status = f_utf_is_word_dash_plus(buffer.string + range->start, width_max, F_false);
      if (F_status_is_error(status)) return status;
      if (status == F_true) return status;

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    return F_false;
  }
#endif // !defined(_di_f_iki_read_)

#if !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)
  f_status_t private_f_iki_content_partial_is(const f_string_static_t buffer, const f_string_range_t range, const uint8_t quote) {

    f_array_length_t delimits = 0;

    for (f_array_length_t i = 0; i < buffer.used; ++i) {

      if (buffer.string[i] == quote) {
        if (delimits && delimits % 2) {
          delimits = 0;

          continue;
        }

        return F_false;
      }
      else if (buffer.string[i] == f_iki_syntax_slash_s[0]) {
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
  f_status_t private_f_iki_object_partial_is(const f_string_static_t buffer, const f_string_range_t range) {

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < buffer.used; ++i) {

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

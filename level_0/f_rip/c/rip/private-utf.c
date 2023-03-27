#include "../rip.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_rip_utf_) || !defined(_di_f_rip_utf_dynamic_) || !defined(_di_f_rip_utf_nulless_) || !defined(_di_f_rip_utf_dynamic_nulless_)
  f_status_t private_f_rip_utf_find_range(const f_utf_string_t source, f_array_length_t *start, f_array_length_t *stop) {

    f_status_t status = F_none;

    // Skip past leading whitespace.
    for (; *start <= *stop; ++(*start)) {

      // Skip past NULL.
      while (*start < *stop && !source[*start]) ++(*start);
      if (*start > *stop) break;

      status = f_utf_character_is_whitespace(source[*start], F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf_not);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; *stop > *start; --(*stop)) {

      // Skip past NULL.
      while (*stop > *start && !source[*stop]) --(*stop);

      if (!source[*stop]) continue;
      if (*stop == *start) break;

      status = f_utf_character_is_whitespace(source[*stop], F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf_not);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    if (*stop == *start) {
      status = f_utf_character_is_whitespace(source[*stop], F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf_not);
        }

        return status;
      }

      if (status == F_true) {
        return F_data_not;
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_rip_utf_) || !defined(_di_f_rip_utf_dynamic_) || !defined(_di_f_rip_utf_nulless_) || !defined(_di_f_rip_utf_dynamic_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

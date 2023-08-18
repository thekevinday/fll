#include "rip.h"
#include "private-rip.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_rip_dynamic_partial_) || !defined(_di_f_rip_dynamic_partial_nulless_) || !defined(_di_f_rip_dynamic_)  || !defined(_di_f_rip_) || !defined(_di_f_rip_nulless_)
  f_status_t private_f_rip_find_range(const f_string_t string, f_number_unsigned_t * const start, f_number_unsigned_t * const stop) {

    const f_number_unsigned_t stop_original = *stop;
    f_number_unsigned_t previous = 0;
    f_status_t status = F_okay;

    // Skip past leading whitespace.
    for (; *start <= *stop; *start += macro_f_utf_byte_width(string[*start])) {

      // Skip past NULL.
      while (*start < *stop && !string[*start]) ++(*start);
      if (*start > *stop) break;

      status = f_utf_is_whitespace(string + *start, (*stop - *start) + 1, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      status = f_utf_is_combining(string + *start, (*stop - *start) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      // This is a combining character, so the previous character is no longer considered a space.
      if (status == F_true) {
        *start = previous;

        break;
      }

      previous = *start;
    } // for

    // Use previous as boolean here to designate that a combining is found in a previous character.
    for (previous = F_false; *stop > *start; --(*stop)) {

      // Skip past NULL.
      while (*stop > *start && !string[*stop]) --(*stop);

      if (!string[*stop]) continue;
      if (*stop == *start) break;

      // Go left until either width is 0 (ASCII, or > 1) to determine the character.
      for (;;) {

        if (macro_f_utf_byte_width_is(string[*stop]) == 1) {
          --(*stop);

          if (*stop == *start) break;
        }
        else {
          break;
        }
      } // for

      if (*stop == *start) break;

      status = f_utf_is_whitespace(string + *stop, (stop_original - *stop) + 1, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;
      if (status == F_true && previous == F_true) break;

      previous = F_false;

      status = f_utf_is_combining(string + *stop, (stop_original - *stop) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      // This is a combining character, so the next character is no longer considered a space.
      if (status == F_true) {
        previous = F_true;
      }
    } // for

    if (*stop == *start) {
      status = f_utf_is_whitespace(string + *stop, (stop_original - *stop) + 1, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;
      }

      if (status == F_true) {
        return F_data_not;
      }
    }

    return F_okay;
  }
#endif // !defined(_di_f_rip_dynamic_partial_) || !defined(_di_f_rip_dynamic_partial_nulless_) || !defined(_di_f_rip_dynamic_)  || !defined(_di_f_rip_) || !defined(_di_f_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

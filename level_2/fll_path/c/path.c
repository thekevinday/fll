#include "path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_path_canonical_
  f_status_t fll_path_canonical(const f_string_static_t path, f_string_dynamic_t *canonical) {
    #ifndef _di_level_2_parameter_checking_
      if (!canonical) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    if (!path.used) {
      status = f_path_current(F_true, canonical);
      if (F_status_is_error(status)) return status;

      return F_none;
    }

    f_array_length_t at = 0;

    uint8_t previous_1 = f_path_separator_s.string[0];
    uint8_t previous_2 = 0;

    f_array_length_t size_chunk = 0;
    f_array_length_t position = 0;

    canonical->used = 0;

    if (path.string[0] == f_path_separator_s.string[0]) {
      at = 1;
    }
    else {
      status = f_path_current(F_true, canonical);
      if (F_status_is_error(status)) return status;

      if (!path.string[0] || path.used == 1) {
        return F_none;
      }

      at = 0;
    }

    status = f_string_dynamic_append_assure(f_path_separator_s, canonical);
    if (F_status_is_error(status)) return status;

    for (; at < path.used && path.string[at]; ++at) {

      if (!size_chunk && path.string[at] == f_path_separator_current_s.string[0]) {
        if (!previous_1 || previous_1 == f_path_separator_s.string[0]) {
          previous_1 = f_path_separator_current_s.string[0];
          previous_2 = 0;

          continue;
        }

        if (previous_1 == f_path_separator_current_s.string[0]) {
          if (previous_2) {
            previous_1 = 0;
            previous_2 = 0;
            size_chunk = 3;
            position = at - 2;
          }
          else {
            previous_2 = f_path_separator_current_s.string[0];
          }
        }
      }
      else if (path.string[at] == f_path_separator_s.string[0]) {
        if (previous_1 == f_path_separator_s.string[0]) {
          size_chunk = 0;
          position = 0;

          continue;
        }

        if (previous_1 == f_path_separator_current_s.string[0]) {
          if (previous_2 == f_path_separator_current_s.string[0]) {
            if (canonical->used > 1) {
              for (--canonical->used; canonical->used > 0; --canonical->used) {
                if (canonical->string[canonical->used - 1] == f_path_separator_s.string[0]) break;
              } // for
            }
          }
        }
        else {
          if (++size_chunk) {
            status = f_string_append(path.string + position, size_chunk, canonical);
            if (F_status_is_error(status)) return status;
          }
        }

        previous_1 = f_path_separator_s.string[0];
        previous_2 = 0;
        size_chunk = 0;
        position = 0;
      }
      else {
        if (!size_chunk) {
          position = at;

          if (previous_2) {
            position -= 2;
            size_chunk = 2;
          }
          else if (previous_1 && previous_1 != f_path_separator_s.string[0]) {
            --position;
            size_chunk = 1;
          }
        }

        if (previous_1) {
          previous_1 = 0;
          previous_2 = 0;
        }

        ++size_chunk;
      }
    } // for

    if (previous_2 == f_path_separator_current_s.string[0]) {
      if (canonical->used > 1) {
        for (--canonical->used; canonical->used > 0; --canonical->used) {
          if (canonical->string[canonical->used - 1] == f_path_separator_s.string[0]) break;
        } // for
      }
    }
    else if (!(previous_1 == f_path_separator_current_s.string[0] || previous_1 == f_path_separator_s.string[0])) {
      if (size_chunk) {
        status = f_string_append(path.string + position, size_chunk, canonical);
        if (F_status_is_error(status)) return status;
      }
    }

    // Assure there is no trailing forward slash, unless it is the first slash.
    if (canonical->used > 1 && canonical->string[canonical->used - 1] == f_path_separator_s.string[0]) {
      --canonical->used;
    }

    status = f_string_dynamic_terminate_after(canonical);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_path_canonical_

#ifdef __cplusplus
} // extern "C"
#endif

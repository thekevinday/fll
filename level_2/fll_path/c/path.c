#include "path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_path_canonical_
  f_return_status fll_path_canonical(const f_string_t path, f_string_dynamic_t *canonical) {
    #ifndef _di_level_2_parameter_checking_
      if (canonical == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    f_string_length_t at = 0;

    uint8_t previous_1 = '/';
    uint8_t previous_2 = 0;

    f_string_length_t size_chunk = 0;
    f_string_length_t position = 0;

    canonical->used = 0;

    if (path[0] == '/') {
      at = 1;
    }
    else {
      status = f_path_current(F_true, canonical);
      if (F_status_is_error(status)) return status;

      if (!path[0]) {
        return F_none;
      }
      at = 0;
    }

    status = fl_string_append_assure("/", 1, canonical);
    if (F_status_is_error(status)) return status;

    for (; path[at]; at++) {

      if (!size_chunk && path[at] == '.') {
        if (!previous_1 || previous_1 == '/') {
          previous_1 = '.';
          previous_2 = 0;
          continue;
        }

        if (previous_1 == '.') {
          if (previous_2) {
            previous_1 = 0;
            previous_2 = 0;
            size_chunk = 3;
            position = at - 2;
          }
          else {
            previous_2 = '.';
          }
        }
      }
      else if (path[at] == '/') {
        if (previous_1 == '/') {
          size_chunk = 0;
          position = 0;
          continue;
        }

        if (previous_1 == '.') {
          if (previous_2 == '.') {
            if (canonical->used > 1) {
              for (canonical->used--; canonical->used > 0; canonical->used--) {
                if (canonical->string[canonical->used - 1] == '/') break;
              } // for
            }
          }
        }
        else {
          size_chunk++;

          if (size_chunk) {
            status = fl_string_append(path + position, size_chunk, canonical);
            if (F_status_is_error(status)) return status;
          }
        }

        previous_1 = '/';
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
          else if (previous_1 && previous_1 != '/') {
            position--;
            size_chunk = 1;
          }
        }

        if (previous_1) {
          previous_1 = 0;
          previous_2 = 0;
        }

        size_chunk++;
      }
    } // for

    if (previous_2 == '.') {
      if (canonical->used > 1) {
        for (canonical->used--; canonical->used > 0; canonical->used--) {
          if (canonical->string[canonical->used - 1] == '/') break;
        } // for
      }
    }
    else if (!(previous_1 == '.' || previous_1 == '/')) {
      if (size_chunk) {
        status = fl_string_append(path + position, size_chunk, canonical);
        if (F_status_is_error(status)) return status;
      }
    }

    // assure there is no trailing forward slash, unless it is the first slash.
    if (canonical->used > 1 && canonical->string[canonical->used - 1] == '/') {
      canonical->used--;
    }

    status = fl_string_dynamic_terminate_after(canonical);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_path_canonical_

#ifdef __cplusplus
} // extern "C"
#endif

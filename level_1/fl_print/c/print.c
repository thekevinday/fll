#include "print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_print_trim_string_
  f_return_status fl_print_trim_string(FILE *output, const f_string_t string, const f_string_length_t length) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
      if (length < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_string_length_t i = 0;
    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < length; i += f_macro_utf_byte_width(string[i])) {

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; i += f_macro_utf_byte_width(string[i])) {
      if (!string[i]) continue;

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_true) {
        f_string_length_t j = i + f_macro_utf_byte_width(string[i]);

        if (j == length) return F_none;

        for (; j < length; j += f_macro_utf_byte_width(string[j])) {
          width_max = (length - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; i++) {
              if (!string[i]) continue;

              if (!fputc(string[i], output)) return F_status_set_error(F_output);
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      if (!fputc(string[i], output)) return F_status_set_error(F_output);
    } // for

    return F_none;
  }
#endif // _di_fl_print_trim_string_

#ifndef _di_fl_print_trim_string_dynamic_
  f_return_status fl_print_trim_string_dynamic(FILE *output, const f_string_static_t buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_string_length_t i = 0;
    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < buffer.used; i += f_macro_utf_byte_width(buffer.string[i])) {
      width_max = (buffer.used - i) + 1;
      status = f_utf_is_whitespace(buffer.string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < buffer.used; i += f_macro_utf_byte_width(buffer.string[i])) {
      if (!buffer.string[i]) continue;

      width_max = (buffer.used - i) + 1;
      status = f_utf_is_whitespace(buffer.string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_true) {
        f_string_length_t j = i + f_macro_utf_byte_width(buffer.string[i]);

        if (j == buffer.used) return F_none;

        for (; j < buffer.used; j += f_macro_utf_byte_width(buffer.string[j])) {
          width_max = (buffer.used - j) + 1;
          status = f_utf_is_whitespace(buffer.string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; i++) {
              if (!buffer.string[i]) continue;

              if (!fputc(buffer.string[i], output)) return F_status_set_error(F_output);
            } // for

            break;
          }
        } // for

        if (status == F_true) {
          break;
        }
      }

      if (!fputc(buffer.string[i], output)) return F_status_set_error(F_output);
    } // for

    return F_none;
  }
#endif // _di_fl_print_trim_string_dynamic_

#ifndef _di_fl_print_trim_string_dynamic_partial_
  f_return_status fl_print_trim_string_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range) {
    #ifndef _di_level_1_parameter_checking_
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (!buffer.used) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
      if (range.stop >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_string_length_t i = range.start;
    f_status_t status = F_none;

    uint8_t width_max = 0;

    for (; i <= range.stop; i += f_macro_utf_byte_width(buffer.string[i])) {
      width_max = (range.stop - i) + 1;
      status = f_utf_is_whitespace(buffer.string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    for (uint8_t width_i = f_macro_utf_byte_width(buffer.string[i]); i <= range.stop; i += width_i) {
      if (!buffer.string[i]) {
        width_i = 1;
        continue;
      }

      width_i = f_macro_utf_byte_width(buffer.string[i]);
      width_max = (range.stop - i) + 1;
      status = f_utf_is_whitespace(buffer.string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        f_string_length_t j = i + width_i;

        if (j == range.stop) return F_none;

        for (uint8_t width_j = f_macro_utf_byte_width(buffer.string[j]); j <= range.stop; j += width_j) {
          width_j = f_macro_utf_byte_width(buffer.string[j]);
          width_max = (range.stop - j) + 1;
          status = f_utf_is_whitespace(buffer.string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i <= j; i += width_i) {
              if (!buffer.string[i]) {
                width_i = 1;
                continue;
              }

              width_i = f_macro_utf_byte_width(buffer.string[i]);

              for (uint8_t k = 0; k < width_i; k++) {
                if (!fputc(buffer.string[i + k], output)) return F_status_set_error(F_output);
              } // for
            } // for

            break;
          }
        } // for

        if (status == F_true) {
          break;
        }
      }

      for (uint8_t k = 0; k < width_i; k++) {
        if (!fputc(buffer.string[i + k], output)) return F_status_set_error(F_output);
      } // for
    } // for

    return F_none;
  }
#endif // _di_fl_print_trim_string_dynamic_partial_

#ifndef _di_fl_print_trim_utf_string_
  f_return_status fl_print_trim_utf_string(FILE *output, const f_utf_string_t string, const f_utf_string_length_t length) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
      if (length < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_string_length_t i = 0;
    f_status_t status = F_none;

    for (; i < length; i++) {
      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; i++) {
      if (!string[i]) continue;

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_true) {
        f_string_length_t j = i + 1;

        if (j == length) return F_none;

        for (; j < length; j++) {
          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; i++) {
              if (!string[i]) continue;

              if (!fputc(string[i], output)) return F_status_set_error(F_output);
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      if (!fputc(string[i], output)) return F_status_set_error(F_output);
    } // for

    return F_none;
  }
#endif // _di_fl_print_trim_utf_string_

#ifndef _di_fl_print_trim_utf_string_dynamic_
  f_return_status fl_print_trim_utf_string_dynamic(FILE *output, const f_utf_string_static_t buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_utf_string_length_t i = 0;
    f_status_t status = F_none;

    for (; i < buffer.used; i++) {
      status = f_utf_character_is_whitespace(buffer.string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < buffer.used; i++) {
      if (!buffer.string[i]) continue;

      status = f_utf_character_is_whitespace(buffer.string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_true) {
        f_string_length_t j = i + 1;

        if (j == buffer.used) return F_none;

        for (; j < buffer.used; j++) {
          status = f_utf_character_is_whitespace(buffer.string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; i++) {
              if (!buffer.string[i]) continue;

              if (!fputc(buffer.string[i], output)) return F_status_set_error(F_output);
            } // for

            break;
          }
        } // for

        if (status == F_true) {
          break;
        }
      }

      if (!fputc(buffer.string[i], output)) return F_status_set_error(F_output);
    } // for

    return F_none;
  }
#endif // _di_fl_print_trim_utf_string_dynamic_

#ifndef _di_fl_print_trim_utf_string_dynamic_partial_
  f_return_status fl_print_trim_utf_string_dynamic_partial(FILE *output, const f_utf_string_static_t buffer, const f_utf_string_range_t range) {
    #ifndef _di_level_1_parameter_checking_
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (!buffer.used) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
      if (range.stop >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_string_length_t i = range.start;
    f_status_t status = F_none;

    for (; i <= range.stop; i++) {
      status = f_utf_character_is_whitespace(buffer.string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i <= range.stop; i++) {
      if (!buffer.string[i]) continue;

      status = f_utf_character_is_whitespace(buffer.string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_true) {
        f_string_length_t j = i + 1;

        if (j == range.stop) return F_none;

        for (; j <= range.stop; j++) {
          status = f_utf_character_is_whitespace(buffer.string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i <= j; i++) {
              if (!buffer.string[i]) continue;

              if (!fputc(buffer.string[i], output)) return F_status_set_error(F_output);
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      if (!fputc(buffer.string[i], output)) return F_status_set_error(F_output);
    } // for

    return F_none;
  }
#endif // _di_fl_print_trim_utf_string_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif

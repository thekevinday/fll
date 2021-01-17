#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_)
  f_status_t private_fl_print_trim_except(FILE *output, const f_string_t string, const f_string_length_t start, const f_string_length_t stop, const f_string_lengths_t except) {
    register f_string_length_t i = start;

    f_string_length_t j = 0;
    f_string_length_t e = 0;
    f_string_length_t ej = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    while (i < stop) {

      for (; e < except.used && except.array[e] < i; ++e) {
        // do nothing.
      } // for

      if (e < except.used && except.array[e] == i) {
        i++;
        continue;
      }

      width_max = (stop - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      i += f_macro_utf_byte_width(string[i]);
    } // while

    while (i < stop) {

      if (!string[i]) continue;

      for (; e < except.used && except.array[e] < i; ++e) {
        // do nothing.
      } // for

      if (e < except.used && except.array[e] == i) {
        i++;
        continue;
      }

      width_max = (stop - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + f_macro_utf_byte_width(string[i]);

        if (j == stop) return F_none;

        ej = e;

        while (j < stop) {

          for (; ej < except.used && except.array[ej] < j; ++ej) {
            // do nothing.
          } // for

          if (ej < except.used && except.array[ej] == j) {
            j++;
            continue;
          }

          width_max = (stop - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; i++) {
              if (!string[i]) continue;

              for (; e < except.used && except.array[e] < i; ++e) {
                // do nothing.
              } // for

              if (e < except.used && except.array[e] == i) continue;

              if (!fputc(string[i], output)) return F_status_set_error(F_output);
            } // for

            break;
          }

          j += f_macro_utf_byte_width(string[j]);
        } // while

        if (status == F_true) break;
      }

      if (!fputc(string[i], output)) return F_status_set_error(F_output);

      i += f_macro_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_)

#if !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)
  f_status_t private_fl_print_trim_except_utf(FILE *output, const f_utf_string_t string, const f_string_length_t start, const f_string_length_t stop, const f_string_lengths_t except) {
    register f_string_length_t i = start;

    f_string_length_t j = 0;
    f_string_length_t e = 0;
    f_string_length_t ej = 0;

    f_status_t status = F_none;

    for (; i < stop; ++i) {

      for (; e < except.used && except.array[e] < i; ++e) {
        // do nothing.
      } // for

      if (e < except.used && except.array[e] == i) continue;

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < stop; ++i) {
      if (!string[i]) continue;

      for (; e < except.used && except.array[e] < i; ++e) {
        // do nothing.
      } // for

      if (e < except.used && except.array[e] == i) continue;

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == stop) return F_none;

        for (ej = e; j < stop; j++) {

          for (; ej < except.used && except.array[ej] < j; ++ej) {
            // do nothing.
          } // for

          if (ej < except.used && except.array[ej] == j) continue;

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; i++) {
              if (!string[i]) continue;

              for (; e < except.used && except.array[e] < i; ++e) {
                // do nothing.
              } // for

              if (e < except.used && except.array[e] == i) continue;

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
#endif // !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)

#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  f_status_t private_fl_print_trim(FILE *output, const f_string_t string, const f_string_length_t length) {
    register f_string_length_t i = 0;

    f_string_length_t j = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < length; i += f_macro_utf_byte_width(string[i])) {

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; i += f_macro_utf_byte_width(string[i])) {
      if (!string[i]) continue;

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + f_macro_utf_byte_width(string[i]);

        if (j == length) return F_none;

        for (; j < length; j += f_macro_utf_byte_width(string[j])) {

          width_max = (length - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

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
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

#if !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)
  f_status_t private_fl_print_trim_utf(FILE *output, const f_utf_string_t string, const f_string_length_t length) {
    register f_string_length_t i = 0;

    f_string_length_t j = 0;

    f_status_t status = F_none;

    for (; i < length; i++) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

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
        j = i + 1;

        if (j == length) return F_none;

        for (; j < length; j++) {

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

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
#endif // !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)

#ifdef __cplusplus
} // extern "C"
#endif

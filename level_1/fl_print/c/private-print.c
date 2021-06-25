#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)
  f_status_t private_fl_print_trim_except_in(FILE *output, const f_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    // skip past leading whitespace.
    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

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

      i += macro_f_utf_byte_width(string[i]);
    } // while

    while (i < stop) {

      if (!string[i]) continue;

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

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
        j = i + macro_f_utf_byte_width(string[i]);

        if (j == stop) {
          return F_none;
        }

        at2 = at;

        while (j < stop) {

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop <= j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

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
            while (i < j) {

              if (!string[i]) {
                ++i;

                continue;
              }

              while (at < except_at.used && except_at.array[at] < i) {
                ++at;
              } // while

              if (at < except_at.used && except_at.array[at] == i) {
                ++i;

                continue;
              }

              while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
                ++in;
              } // while

              if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
                i = except_in.array[in].stop + 1;

                continue;
              }

              if (!fputc(string[i], output)) {
                return F_status_set_error(F_output);
              }

              ++i;
            } // while

            break;
          }

          j += macro_f_utf_byte_width(string[j]);
        } // while

        if (status == F_true) break;
      }

      width_max = macro_f_utf_byte_width(string[i]);

      for (j = 0; j < width_max; ++j) {

        if (!fputc(string[i + j], output)) {
          return F_status_set_error(F_output);
        }
      } // for

      i += width_max;
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)

#if !defined(_di_fl_print_trim_except_in_utf_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_) || !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)
  f_status_t private_fl_print_trim_except_in_utf(FILE *output, const f_utf_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      ++i;
    } // while

    while (i < stop) {

      if (!string[i]) {
        ++i;

        continue;
      }

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == stop) {
          return F_none;
        }

        at2 = at;

        while (j < stop) {

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop <= j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            while (i < j) {

              if (!string[i]) {
                ++i;

                continue;
              }

              while (at < except_at.used && except_at.array[at] < i) {
                ++at;
              } // while

              if (at < except_at.used && except_at.array[at] == i) {
                ++i;

                continue;
              }

              if (!fputc(string[i], output)) {
                return F_status_set_error(F_output);
              }

              ++i;
            } // while

            break;
          }

          ++j;
        } // while

        if (status == F_true) break;
      }

      if (!fputc(string[i], output)) {
        return F_status_set_error(F_output);
      }

      ++i;
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_in_utf_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_) || !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)

#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  f_status_t private_fl_print_trim(FILE *output, const f_string_t string, const f_array_length_t length) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

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

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

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
        j = i + macro_f_utf_byte_width(string[i]);

        if (j == length) {
          return F_none;
        }

        for (; j < length; j += macro_f_utf_byte_width(string[j])) {

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
            for (; i < j; ++i) {

              if (!string[i]) continue;

              if (!fputc(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      width_max = macro_f_utf_byte_width(string[i]);

      for (j = 0; j < width_max; ++j) {

        if (!fputc(string[i + j], output)) {
          return F_status_set_error(F_output);
        }
      } // for
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

#if !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)
  f_status_t private_fl_print_trim_utf(FILE *output, const f_utf_string_t string, const f_array_length_t length) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    for (; i < length; ++i) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; ++i) {

      if (!string[i]) continue;

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == length) {
          return F_none;
        }

        for (; j < length; ++j) {

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {

              if (!string[i]) continue;

              if (!fputc(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      if (!fputc(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)

#ifdef __cplusplus
} // extern "C"
#endif

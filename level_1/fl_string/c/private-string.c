#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)
  f_status_t private_fl_string_compare(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    for (; i1 < stop1 && i2 < stop2; ++i1, ++i2) {

      // skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      // skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      if (string1[i1] != string2[i2]) return F_equal_to_not;
    } // for

    // only return F_equal_to if all remaining characters are NULL.
    for (; i1 < stop1; ++i1) {
      if (string1[i1] != 0) return F_equal_to_not;
    } // for

    for (; i2 < stop2; ++i2) {
      if (string2[i2] != 0) return F_equal_to_not;
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)

#if !defined(_di_fl_string_compare_except_) || !defined(_di_fl_string_dynamic_compare_except_) || !defined(_di_fl_string_dynamic_partial_compare_except_)
  f_status_t private_fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    f_array_length_t e1 = 0;
    f_array_length_t e2 = 0;

    while (i1 < stop1 && i2 < stop2) {

      // skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      // skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      // skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;
      if (e1 < except1.used && except1.array[e1] == i1) {
        ++i1;

        continue;
      }

      // skip past except characters in string2.
      while (e2 < except2.used && except2.array[e2] < i2) ++e2;
      if (e2 < except2.used && except2.array[e2] == i2) {
        ++i2;

        continue;
      }

      if (string1[i1] != string2[i2]) {
        return F_equal_to_not;
      }

      ++i1;
      ++i2;
    } // while

    // only return F_equal_to if all remaining characters are NULL or are designated to be ignored.
    for (; i1 < stop1; i1++) {

      // skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;
      if (e1 < except1.used && except1.array[e1] == i1) continue;

      if (string1[i1] != 0) {
        return F_equal_to_not;
      }
    } // for

    for (; i2 < stop2; ++i2) {

      // skip past except characters in string2.
      while (e2 < except2.used && except2.array[e2] < i2) ++e2;
      if (e2 < except2.used && except2.array[e2] == i2) continue;

      if (string2[i2] != 0) {
        return F_equal_to_not;
      }
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_fl_string_compare_except_) || !defined(_di_fl_string_dynamic_compare_except_) || !defined(_di_fl_string_dynamic_partial_compare_except_)

#if !defined(_di_fl_string_compare_except_trim_) || !defined(_di_fl_string_dynamic_compare_except_trim_) || !defined(_di_fl_string_dynamic_partial_compare_except_trim_)
  f_status_t private_fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    f_array_length_t e1 = 0;
    f_array_length_t e2 = 0;

    uint8_t width = 0;
    f_array_length_t width_max = 0;

    f_status_t status = F_none;

    // skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += width) {

      // skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      // skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;
      if (e1 < except1.used && except1.array[e1] == i1) {
        width = 1;

        continue;
      }

      width_max = (stop1 - i1) + 1;
      status = f_utf_is_whitespace(string1 + i1, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(string1[i1]);
    } // for

    // skip past leading whitespace in string2.
    for (; i2 < stop2; i2 += width) {

      // skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      // skip past except characters in string2.
      while (e2 < except2.used && except2.array[e2] < i2) ++e2;
      if (e2 < except2.used && except2.array[e2] == i2) {
        width = 1;

        continue;
      }

      width_max = (stop2 - i2) + 1;
      status = f_utf_is_whitespace(string2 + i2, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(string2[i2]);
    } // for

    f_array_length_t last1 = i1;
    f_array_length_t last2 = i2;

    {
      // size1 and size2 are to represent to total number of characters after trim that are not ignored via "except".
      f_array_length_t size1 = 0;
      f_array_length_t size2 = 0;

      f_array_length_t j = 0;
      f_array_length_t ej = e1;

      // determine where the last non-whitespace is in string1.
      for (j = i1; j < stop1; j += width) {

        // skip past NULL in string1.
        while (j < stop1 && !string1[j]) ++j;
        if (j == stop1) break;

        // skip past except characters in string1.
        while (ej < except1.used && except1.array[ej] < j) ++ej;

        if (ej < except1.used && except1.array[ej] == j) {
          width = 1;

          continue;
        }

        width_max = (stop1 - j) + 1;
        status = f_utf_is_whitespace(string1 + j, width_max);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) {
            return F_status_set_error(F_utf);
          }

          return status;
        }

        width = macro_f_utf_byte_width(string1[j]);

        if (status == F_false) {
          last1 = j;
          size1 += width;
        }
      } // for

      ej = e2;

      // determine where the last non-whitespace is in string2.
      for (j = i2; j < stop2; j += width) {

        // skip past NULL in string2.
        while (j < stop2 && !string2[j]) ++j;
        if (j == stop2) break;

        // skip past except characters in string2.
        while (ej < except2.used && except2.array[ej] < j) ++ej;
        if (ej < except2.used && except2.array[ej] == j) {
          width = 1;
          continue;
        }

        width_max = (stop2 - j) + 1;
        status = f_utf_is_whitespace(string2 + j, width_max);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) {
            return F_status_set_error(F_utf);
          }

          return status;
        }

        width = macro_f_utf_byte_width(string2[j]);

        if (status == F_false) {
          last2 = j;
          size2 += width;
        }
      } // for

      if (size1 != size2) {
        return F_equal_to_not;
      }
    }

    while (i1 <= last1 && i2 <= last2) {

      // skip past NULL in string1.
      while (i1 <= last1 && !string1[i1]) ++i1;
      if (i1 > last1) break;

      // skip past NULL in string2.
      while (i2 <= last2 && !string2[i2]) ++i2;
      if (i2 > last2) break;

      // skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;

      if (e1 < except1.used && except1.array[e1] == i1) {
        ++i1;

        continue;
      }

      // skip past except characters in string2.
      while (e2 < except2.used && except2.array[e2] < i2) ++e2;

      if (e2 < except2.used && except2.array[e2] == i2) {
        ++i2;

        continue;
      }

      if (string1[i1] != string2[i2]) {
        return F_equal_to_not;
      }

      ++i1;
      ++i2;
    } // while

    // only return F_equal_to if all remaining characters are NULL.
    for (; i1 <= last1; ++i1) {

      if (string1[i1] != 0) {

        // skip past except characters in string1.
        while (e1 < except1.used && except1.array[e1] < i1) ++e1;
        if (e1 < except1.used && except1.array[e1] == i1) continue;

        return F_equal_to_not;
      }
    } // for

    for (; i2 <= last2; ++i2) {

      if (string2[i2] != 0) {

        // skip past except characters in string1.
        while (e2 < except2.used && except2.array[e2] < i2) ++e2;
        if (e2 < except2.used && except2.array[e2] == i2) continue;

        return F_equal_to_not;
      }
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_fl_string_compare_except_trim_) || !defined(_di_fl_string_dynamic_compare_except_trim_) || !defined(_di_fl_string_dynamic_partial_compare_except_trim_)

#if !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)
  f_status_t private_fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    f_string_static_t debug1;
    debug1.string = string1 + offset1;
    debug1.used = (stop1 - offset1) + 1;

    f_string_static_t debug2;
    debug2.string = string2 + offset2;
    debug2.used = (stop2 - offset2) + 1;

    uint8_t width = 0;
    f_array_length_t width_max = 0;
    f_status_t status = F_none;

    // Skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += width) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      width_max = (stop1 - i1) + 1;
      status = f_utf_is_whitespace(string1 + i1, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(string1[i1]);
    } // for

    // Skip past leading whitespace in string2.
    for (; i2 < stop2; i2 += width) {

      // Skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      width_max = (stop2 - i2) + 1;
      status = f_utf_is_whitespace(string2 + i2, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(string2[i2]);
    } // for

    f_array_length_t last1 = i1;
    f_array_length_t last2 = i2;

    {
      // Size1 and size2 are to represent to total number of characters after trim.
      f_array_length_t size1 = 0;
      f_array_length_t size2 = 0;

      // Determine where the last non-whitespace is in string1.
      for (f_array_length_t j = i1; j < stop1; j += width) {

        // Skip past NULL in string1.
        while (j < stop1 && !string1[j]) ++j;
        if (j == stop1) break;

        width_max = (stop1 - j) + 1;
        status = f_utf_is_whitespace(string1 + j, width_max);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) {
            return F_status_set_error(F_utf);
          }

          return status;
        }

        width = macro_f_utf_byte_width(string1[j]);

        if (status == F_false) {
          last1 = j;
          ++size1;
        }
      } // for

      // Determine where the last non-whitespace is in string2.
      for (f_array_length_t j = i2; j < stop2; j += width) {

        // Skip past NULL in string2.
        while (j < stop2 && !string2[j]) ++j;
        if (j == stop2) break;

        width_max = (stop2 - j) + 1;
        status = f_utf_is_whitespace(string2 + j, width_max);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) {
            return F_status_set_error(F_utf);
          }

          return status;
        }

        width = macro_f_utf_byte_width(string2[j]);

        if (status == F_false) {
          last2 = j;
          ++size2;
        }
      } // for

      if (size1 != size2) {
        return F_equal_to_not;
      }
    }

    for (; i1 < last1 && i2 < last2; ++i1, ++i2) {

      // Skip past NULL in string1.
      while (i1 < last1 && !string1[i1]) ++i1;
      if (i1 == last1) break;

      // Skip past NULL in string2.
      while (i2 < last2 && !string2[i2]) ++i2;
      if (i2 == last2) break;

      if (string1[i1] != string2[i2]) {
        return F_equal_to_not;
      }
    } // for

    // Only return F_equal_to if all remaining characters are NULL.
    for (; i1 < last1; ++i1) {
      if (string1[i1] != 0) return F_equal_to_not;
    } // for

    for (; i2 < last2; ++i2) {
      if (string2[i2] != 0) return F_equal_to_not;
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)

#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)
  f_status_t private_fl_string_rip_find_range(const f_string_t source, f_array_length_t *start, f_array_length_t *stop) {

    const f_array_length_t stop_original = *stop;

    f_status_t status = F_none;

    uint8_t width = 0;

    // Skip past leading whitespace.
    for (; *start <= *stop; *start += width) {

      // skip past NULL.
      while (*start < *stop && !source[*start]) ++(*start);
      if (*start > *stop) break;

      status = f_utf_is_whitespace(source + *start, (*stop - *start) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(source[*start]);
    } // for

    for (; *stop > *start; --(*stop)) {

      // skip past NULL.
      while (*stop > *start && !source[*stop]) --(*stop);

      if (!source[*stop]) continue;
      if (*stop == *start) break;

      // each UTF-8 character of width 1 is an incomplete part.
      // go left until either width is 0 (ascii, or > 1) to determine the character.
      for (;;) {

        width = macro_f_utf_byte_width_is(source[*stop]);

        if (width == 1) {
          --(*stop);

          if (*stop == *start) break;
        }
        else {
          break;
        }
      } // for

      if (*stop == *start) break;

      status = f_utf_is_whitespace(source + *stop, (stop_original - *stop) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    if (*stop == *start) {
      status = f_utf_is_whitespace(source + *stop, (stop_original - *stop) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        return F_data_not;
      }
    }

    return F_none;
  }
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

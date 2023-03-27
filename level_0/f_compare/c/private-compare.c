#include "compare.h"
#include "private-compare.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_compare_) || !defined(_di_f_compare_dynamic_) || !defined(_di_f_compare_dynamic_string_) || !defined(_di_f_compare_dynamic_partial_) || !defined(_di_f_compare_dynamic_partial_dynamic_)
  f_status_t private_f_compare(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    for (; i1 < stop1 && i2 < stop2; ++i1, ++i2) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      // Skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      if (string1[i1] != string2[i2]) return F_equal_to_not;
    } // for

    // Only return F_equal_to if all remaining characters are NULL.
    for (; i1 < stop1; ++i1) {
      if (string1[i1] != 0) return F_equal_to_not;
    } // for

    for (; i2 < stop2; ++i2) {
      if (string2[i2] != 0) return F_equal_to_not;
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_f_compare_) || !defined(_di_f_compare_dynamic_) || !defined(_di_f_compare_dynamic_string_) || !defined(_di_f_compare_dynamic_partial_) || !defined(_di_f_compare_dynamic_partial_dynamic_)

#if !defined(_di_f_compare_except_) || !defined(_di_f_compare_dynamic_except_) || !defined(_di_f_compare_dynamic_partial_except_)
  f_status_t private_f_compare_except(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    f_array_length_t e1 = 0;
    f_array_length_t e2 = 0;

    while (i1 < stop1 && i2 < stop2) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      // Skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      // Skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;
      if (e1 < except1.used && except1.array[e1] == i1) {
        ++i1;

        continue;
      }

      // Skip past except characters in string2.
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

    // Only return F_equal_to if all remaining characters are NULL or are designated to be ignored.
    for (; i1 < stop1; i1++) {

      // Skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;
      if (e1 < except1.used && except1.array[e1] == i1) continue;

      if (string1[i1] != 0) {
        return F_equal_to_not;
      }
    } // for

    for (; i2 < stop2; ++i2) {

      // Skip past except characters in string2.
      while (e2 < except2.used && except2.array[e2] < i2) ++e2;
      if (e2 < except2.used && except2.array[e2] == i2) continue;

      if (string2[i2] != 0) {
        return F_equal_to_not;
      }
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_f_compare_except_) || !defined(_di_f_compare_dynamic_except_) || !defined(_di_f_compare_dynamic_partial_except_)

#if !defined(_di_f_compare_except_trim_) || !defined(_di_f_compare_dynamic_except_trim_) || !defined(_di_f_compare_dynamic_partial_except_trim_)
  f_status_t private_f_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    f_array_length_t e1 = 0;
    f_array_length_t e2 = 0;

    uint8_t width = 0;
    f_array_length_t width_max = 0;
    f_array_length_t previous = 0;

    f_status_t status = F_none;

    // Skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += width) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      // Skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;
      if (e1 < except1.used && except1.array[e1] == i1) {
        width = 1;

        continue;
      }

      width_max = (stop1 - i1) + 1;

      status = f_utf_is_whitespace(string1 + i1, width_max, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(string1[i1]);
      width_max = (stop1 - i1) + 1;

      status = f_utf_is_combining(string1 + i1, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      // This is a combining character, so the previous character is no longer considered a space.
      if (status == F_true) {
        i1 = previous;

        break;
      }

      previous = i1;
    } // for

    // Skip past leading whitespace in string2.
    for (; i2 < stop2; i2 += width) {

      // Skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      // Skip past except characters in string2.
      while (e2 < except2.used && except2.array[e2] < i2) ++e2;
      if (e2 < except2.used && except2.array[e2] == i2) {
        width = 1;

        continue;
      }

      width_max = (stop2 - i2) + 1;

      status = f_utf_is_whitespace(string2 + i2, width_max, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(string2[i2]);
      width_max = (stop2 - i2) + 1;

      status = f_utf_is_combining(string2 + i2, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      // This is a combining character, so the previous character is no longer considered a space.
      if (status == F_true) {
        i2 = previous;

        break;
      }

      previous = i2;
    } // for

    f_array_length_t last1 = i1;
    f_array_length_t last2 = i2;

    {
      // The size1 and size2 are to represent to total number of characters after trim that are not ignored via "except".
      f_array_length_t size1 = 0;
      f_array_length_t size2 = 0;

      f_array_length_t j = 0;
      f_array_length_t ej = e1;

      // Determine where the last non-whitespace is in string1.
      for (j = i1; j < stop1; j += width) {

        // Skip past NULL in string1.
        while (j < stop1 && !string1[j]) ++j;
        if (j == stop1) break;

        // Skip past except characters in string1.
        while (ej < except1.used && except1.array[ej] < j) ++ej;

        if (ej < except1.used && except1.array[ej] == j) {
          width = 1;

          continue;
        }

        width_max = (stop1 - j) + 1;

        status = f_utf_is_whitespace(string1 + j, width_max, F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_parameter) return status;
        }

        width = macro_f_utf_byte_width(string1[j]);

        if (status == F_false) {
          status = f_utf_is_combining(string1 + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_parameter) return status;
          }

          // This is a combining character, so the previous character is no longer considered a space.
          if (status == F_true) {
            if (last1 != previous) {
              size1 -= macro_f_utf_byte_width(string1[last1]);
              last1 = previous;
            }
          }
          else {
            last1 = j;
            size1 += width;
            previous = j;
          }
        }
        else if (F_status_is_error(status)) {
          last1 = j;
          size1 += width;
          previous = j;
        }
        else {
          previous = j;
        }
      } // for

      ej = e2;

      // Determine where the last non-whitespace is in string2.
      for (j = i2; j < stop2; j += width) {

        // Skip past NULL in string2.
        while (j < stop2 && !string2[j]) ++j;
        if (j == stop2) break;

        // Skip past except characters in string2.
        while (ej < except2.used && except2.array[ej] < j) ++ej;
        if (ej < except2.used && except2.array[ej] == j) {
          width = 1;

          continue;
        }

        width_max = (stop2 - j) + 1;

        status = f_utf_is_whitespace(string2 + j, width_max, F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) {
            return F_status_set_error(F_utf_not);
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

      // Skip past NULL in string1.
      while (i1 <= last1 && !string1[i1]) ++i1;
      if (i1 > last1) break;

      // Skip past NULL in string2.
      while (i2 <= last2 && !string2[i2]) ++i2;
      if (i2 > last2) break;

      // Skip past except characters in string1.
      while (e1 < except1.used && except1.array[e1] < i1) ++e1;

      if (e1 < except1.used && except1.array[e1] == i1) {
        ++i1;

        continue;
      }

      // Skip past except characters in string2.
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

    // Only return F_equal_to if all remaining characters are NULL.
    for (; i1 <= last1; ++i1) {

      if (string1[i1] != 0) {

        // Skip past except characters in string1.
        while (e1 < except1.used && except1.array[e1] < i1) ++e1;
        if (e1 < except1.used && except1.array[e1] == i1) continue;

        return F_equal_to_not;
      }
    } // for

    for (; i2 <= last2; ++i2) {

      if (string2[i2] != 0) {

        // Skip past except characters in string1.
        while (e2 < except2.used && except2.array[e2] < i2) ++e2;
        if (e2 < except2.used && except2.array[e2] == i2) continue;

        return F_equal_to_not;
      }
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_f_compare_except_trim_) || !defined(_di_f_compare_dynamic_except_trim_) || !defined(_di_f_compare_dynamic_partial_except_trim_)

#if !defined(_di_f_compare_trim_) || !defined(_di_f_compare_dynamic_trim_) || !defined(_di_f_compare_dynamic_partial_trim_)
  f_status_t private_f_compare_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;
    f_array_length_t previous = 0;
    f_status_t status = F_none;

    // Skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += macro_f_utf_byte_width(string1[i1])) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      status = f_utf_is_whitespace(string1 + i1, (stop1 - i1) + 1, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      status = f_utf_is_combining(string1 + i1, (stop1 - i1) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      // This is a combining character, so the previous character is no longer considered a space.
      if (status == F_true) {
        i1 = previous;

        break;
      }

      previous = i1;
    } // for

    // Skip past leading whitespace in string2.
    for (; i2 < stop2; i2 += macro_f_utf_byte_width(string2[i2])) {

      // Skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      status = f_utf_is_whitespace(string2 + i2, (stop2 - i2) + 1, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      status = f_utf_is_combining(string2 + i2, (stop2 - i2) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      // This is a combining character, so the previous character is no longer considered a space.
      if (status == F_true) {
        i2 = previous;

        break;
      }

      previous = i2;
    } // for

    f_array_length_t last1 = i1;
    f_array_length_t last2 = i2;

    {
      // Size1 and size2 are to represent to total number of characters after trim.
      f_array_length_t size1 = 0;
      f_array_length_t size2 = 0;

      previous = i1;

      // Determine where the last non-whitespace is in string1.
      for (f_array_length_t j = i1; j < stop1; j += macro_f_utf_byte_width(string1[j])) {

        // Skip past NULL in string1.
        while (j < stop1 && !string1[j]) ++j;
        if (j == stop1) break;

        status = f_utf_is_whitespace(string1 + j, (stop1 - j) + 1, F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_parameter) return status;

          break;
        }

        if (status == F_false) {
          status = f_utf_is_combining(string1 + j, (stop1 - j) + 1);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_parameter) return status;
          }

          // This is a combining character, so the previous character is no longer considered a space.
          if (status == F_true) {
            if (last1 != previous) {
              size1 -= macro_f_utf_byte_width(string1[last1]);
              last1 = previous;
            }
          }
          else {
            last1 = j;
            size1 += macro_f_utf_byte_width(string1[last1]);
            previous = j;
          }
        }
        else if (F_status_is_error(status)) {
          last1 = j;
          size1 += macro_f_utf_byte_width(string1[last1]);
          previous = j;
        }
        else {
          previous = j;
        }
      } // for

      previous = i2;

      // Determine where the last non-whitespace is in string2.
      for (f_array_length_t j = i2; j < stop2; j += macro_f_utf_byte_width(string2[j])) {

        // Skip past NULL in string2.
        while (j < stop2 && !string2[j]) ++j;
        if (j == stop2) break;

        status = f_utf_is_whitespace(string2 + j, (stop2 - j) + 1, F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_parameter) return status;

          break;
        }

        if (status == F_false) {
          status = f_utf_is_combining(string2 + j, (stop2 - j) + 1);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_parameter) return status;
          }

          // This is a combining character, so the previous character is no longer considered a space.
          if (status == F_true) {
            if (last2 != previous) {
              size2 -= macro_f_utf_byte_width(string2[last2]);
              last2 = previous;
            }
          }
          else {
            last2 = j;
            size2 += macro_f_utf_byte_width(string2[last2]);
            previous = j;
          }
        }
        else if (F_status_is_error(status)) {
          last2 = j;
          size2 += macro_f_utf_byte_width(string2[last2]);
          previous = j;
        }
        else {
          previous = j;
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
#endif // !defined(_di_f_compare_trim_) || !defined(_di_f_compare_dynamic_trim_) || !defined(_di_f_compare_dynamic_partial_trim_)

#ifdef __cplusplus
} // extern "C"
#endif

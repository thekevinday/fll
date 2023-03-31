#include "utf.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_utf_string_compare_) || !defined(_di_fl_utf_string_dynamic_compare_) || !defined(_di_fl_utf_string_dynamic_partial_compare_)
  f_status_t private_fl_utf_string_compare(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

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
#endif // !defined(_di_fl_utf_string_compare_) || !defined(_di_fl_utf_string_dynamic_compare_) || !defined(_di_fl_utf_string_dynamic_partial_compare_)

#if !defined(_di_fl_utf_string_compare_trim_) || !defined(_di_fl_utf_string_dynamic_compare_trim_) || !defined(_di_fl_utf_string_dynamic_partial_compare_trim_)
  f_status_t private_fl_utf_string_compare_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;
    f_array_length_t previous = 0;
    f_status_t status = F_none;

    // Skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += macro_f_utf_byte_width(string1[i1])) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      status = f_utf_character_is_whitespace(string1[i1], F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      status = f_utf_character_is_combining(string1[i1]);

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

      status = f_utf_character_is_whitespace(string2[i2], F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_parameter) return status;

        break;
      }

      if (status == F_false) break;

      status = f_utf_character_is_combining(string2[i2]);

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

        status = f_utf_character_is_whitespace(string1[j], F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_parameter) return status;

          break;
        }

        if (status == F_false) {
          status = f_utf_character_is_combining(string1[j]);

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

        status = f_utf_character_is_whitespace(string2[j], F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_parameter) return status;

          break;
        }

        if (status == F_false) {
          status = f_utf_character_is_combining(string2[j]);

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

      if (size1 != size2) return F_equal_to_not;
    }

    if (last1 < stop1 && last2 < stop2) {
      for (; i1 < last1 && i2 < last2; ++i1, ++i2) {

        // Skip past NULL in string1.
        while (i1 < last1 && !string1[i1]) ++i1;
        if (i1 == last1) break;

        // Skip past NULL in string2.
        while (i2 < last2 && !string2[i2]) ++i2;
        if (i2 == last2) break;

        if (string1[i1] != string2[i2]) return F_equal_to_not;
      } // for
    }

    // Only return F_equal_to if all remaining characters are NULL.
    if (last1 < stop1) {
      for (; i1 < last1; ++i1) {
        if (string1[i1] != 0) return F_equal_to_not;
      } // for
    }

    if (last2 < stop2) {
      for (; i2 < last2; ++i2) {
        if (string2[i2] != 0) return F_equal_to_not;
      } // for
    }

    return F_equal_to;
  }
#endif // !defined(_di_fl_utf_string_compare_trim_) || !defined(_di_fl_utf_string_dynamic_compare_trim_) || !defined(_di_fl_utf_string_dynamic_partial_compare_trim_)

#if !defined(_di_fl_utf_string_rip_) || !defined(_di_fl_utf_string_dynamic_rip_) || !defined(_di_fl_utf_string_rip_nulless_) || !defined(_di_fl_utf_string_dynamic_rip_nulless_)
  f_status_t private_fl_utf_string_rip_find_range(const f_utf_string_t source, f_array_length_t *start, f_array_length_t *stop) {

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
#endif // !defined(_di_fl_utf_string_rip_) || !defined(_di_fl_utf_string_dynamic_rip_) || !defined(_di_fl_utf_string_rip_nulless_) || !defined(_di_fl_utf_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

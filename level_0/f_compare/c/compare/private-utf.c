#include "../compare.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_compare_utf_) || !defined(_di_f_compare_utf_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_)
  f_status_t private_f_compare_utf(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

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
#endif // !defined(_di_f_compare_utf_) || !defined(_di_f_compare_utf_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_)

#if !defined(_di_f_compare_utf_trim_) || !defined(_di_f_compare_utf_dynamic_trim_) || !defined(_di_f_compare_utf_dynamic_partial_trim_)
  f_status_t private_f_compare_utf_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) {

    f_array_length_t i1 = offset1;
    f_array_length_t i2 = offset2;

    f_status_t status = F_none;

    // Skip past leading whitespace in string1.
    for (; i1 < stop1; ++i1) {

      // Skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) ++i1;
      if (i1 == stop1) break;

      status = f_utf_character_is_whitespace(string1[i1], F_false);

      if (F_status_is_error(status)) {

        // Ignore possibly invalid UTF-8 codes.
        if (F_status_set_fine(status) != F_maybe) {
          return status;
        }
      }

      if (status == F_false) break;
    } // for

    // Skip past leading whitespace in string2.
    for (; i2 < stop2; i2++) {

      // Skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) ++i2;
      if (i2 == stop2) break;

      status = f_utf_character_is_whitespace(string2[i2], F_false);

      if (F_status_is_error(status)) {

        // Ignore possibly invalid UTF-8 codes.
        if (F_status_set_fine(status) != F_maybe) {
          return status;
        }
      }

      if (status == F_false) break;
    } // for

    f_array_length_t last1 = i1;
    f_array_length_t last2 = i2;

    {
      // The size1 and size2 are to represent to total number of characters after trim.
      f_array_length_t size1 = 0;
      f_array_length_t size2 = 0;
      f_array_length_t j = 0;

      // Determine where the last non-whitespace is in string1.
      for (j = i1; j < stop1; ++j) {

        // Skip past NULL in string1.
        while (j < stop1 && !string1[j]) ++j;
        if (j == stop1) break;

        status = f_utf_character_is_whitespace(string1[j], F_false);

        if (F_status_is_error(status)) {
          // ignore possibly invalid UTF-8 codes.
          if (F_status_set_fine(status) != F_maybe) {
            return status;
          }
        }

        if (status == F_false) {
          last1 = j;
          ++size1;
        }
      } // for

      // Determine where the last non-whitespace is in string2.
      for (j = i2; j < stop2; ++j) {

        // Skip past NULL in string2.
        while (j < stop2 && !string2[j]) ++j;
        if (j == stop2) break;

        status = f_utf_character_is_whitespace(string2[j], F_false);

        if (F_status_is_error(status)) {

          // Ignore possibly invalid UTF-8 codes.
          if (F_status_set_fine(status) != F_maybe) {
            return status;
          }
        }

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

      if (string1[i1] != string2[i2]) return F_equal_to_not;
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
#endif // !defined(_di_f_compare_utf_trim_) || !defined(_di_f_compare_utf_dynamic_trim_) || !defined(_di_f_compare_utf_dynamic_partial_trim_)

#ifdef __cplusplus
} // extern "C"
#endif

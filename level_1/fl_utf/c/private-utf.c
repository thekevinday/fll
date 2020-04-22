#include <level_1/utf.h>
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_utf_string_compare_) || !defined(_di_fl_utf_string_dynamic_compare_) || !defined(_di_fl_utf_string_dynamic_partial_compare_)
  f_return_status private_fl_utf_string_compare(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length offset1, const f_utf_string_length offset2, const f_utf_string_length stop1, const f_utf_string_length stop2) {
    f_utf_string_length i1 = offset1;
    f_utf_string_length i2 = offset2;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      // skip past NULL in string1.
      while (i1 < stop1 && string1[i1] == f_string_eos) i1++;
      if (i1 == stop1) break;

      // skip past NULL in string2.
      while (i2 < stop2 && string2[i2] == f_string_eos) i2++;
      if (i2 == stop2) break;

      if (string1[i1] != string2[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    for (; i1 < stop1; i1++) {
      if (string1[i1] != f_string_eos) return f_not_equal_to;
    } // for

    for (; i2 < stop2; i2++) {
      if (string2[i2] != f_string_eos) return f_not_equal_to;
    } // for
  }
#endif // !defined(_di_fl_utf_string_compare_) || !defined(_di_fl_utf_string_dynamic_compare_) || !defined(_di_fl_utf_string_dynamic_partial_compare_)

#if !defined(_di_fl_utf_string_compare_trim_) || !defined(_di_fl_utf_string_dynamic_compare_trim_) || !defined(_di_fl_utf_string_dynamic_partial_compare_trim_)
  f_return_status private_fl_utf_string_compare_trim(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length offset1, const f_utf_string_length offset2, const f_utf_string_length stop1, const f_utf_string_length stop2) {
    f_utf_string_length i1 = offset1;
    f_utf_string_length i2 = offset2;

    f_status status = f_none;

    // skip past leading whitespace in string1.
    for (; i1 < stop1; i1++) {
      // skip past NULL in string1.
      while (i1 < stop1 && string1[i1] == f_string_eos) i1++;
      if (i1 == stop1) break;

      status = f_utf_character_is_whitespace(string1[i1]);
      if (f_status_is_error(status)) {
        // ignore possibly invalid UTF-8 codes.
        if (f_status_set_fine(status) != f_maybe) {
          return status;
        }
      }

      if (status == f_false) break;
    } // for

    // skip past leading whitespace in string2.
    for (; i2 < stop2; i2++) {
      // skip past NULL in string2.
      while (i2 < stop2 && string2[i2] == f_string_eos) i2++;
      if (i2 == stop2) break;

      status = f_utf_character_is_whitespace(string2[i2]);
      if (f_status_is_error(status)) {
        // ignore possibly invalid UTF-8 codes.
        if (f_status_set_fine(status) != f_maybe) {
          return status;
        }
      }

      if (status == f_false) break;
    } // for

    f_utf_string_length last1 = i1;
    f_utf_string_length last2 = i2;

    {
      // size1 and size2 are to represent to total number of characters after trim.
      f_utf_string_length size1 = 0;
      f_utf_string_length size2 = 0;

      // determine where the last non-whitespace is in string1.
      for (f_utf_string_length j = i1; j < stop1; j++) {
        // skip past NULL in string1.
        while (j < stop1 && string1[j] == f_string_eos) j++;
        if (j == stop1) break;

        status = f_utf_character_is_whitespace(string1[j]);
        if (f_status_is_error(status)) {
          // ignore possibly invalid UTF-8 codes.
          if (f_status_set_fine(status) != f_maybe) {
            return status;
          }
        }

        if (status == f_false) {
          last1 = j;
          size1++;
        }
      } // for

      // determine where the last non-whitespace is in string2.
      for (f_utf_string_length j = i2; j < stop2; j++) {
        // skip past NULL in string2.
        while (j < stop2 && string2[j] == f_string_eos) j++;
        if (j == stop2) break;

        status = f_utf_character_is_whitespace(string2[j]);
        if (f_status_is_error(status)) {
          // ignore possibly invalid UTF-8 codes.
          if (f_status_set_fine(status) != f_maybe) {
            return status;
          }
        }

        if (status == f_false) {
          last2 = j;
          size2++;
        }
      } // for

      if (size1 != size2) return f_not_equal_to;
    }

    for (; i1 < last1 && i2 < last2; i1++, i2++) {
      // skip past NULL in string1.
      while (i1 < last1 && string1[i1] == f_string_eos) i1++;
      if (i1 == last1) break;

      // skip past NULL in string2.
      while (i2 < last2 && string2[i2] == f_string_eos) i2++;
      if (i2 == last2) break;

      if (string1[i1] != string2[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    for (; i1 < last1; i1++) {
      if (string1[i1] != f_string_eos) return f_not_equal_to;
    } // for

    for (; i2 < last2; i2++) {
      if (string2[i2] != f_string_eos) return f_not_equal_to;
    } // for

    return f_equal_to;
  }
#endif // !defined(_di_fl_utf_string_compare_trim_) || !defined(_di_fl_utf_string_dynamic_compare_trim_) || !defined(_di_fl_utf_string_dynamic_partial_compare_trim_)

#if !defined(_di_fl_utf_string_rip_) || !defined(_di_fl_utf_string_dynamic_rip_)
  f_return_status private_fl_utf_string_rip(const f_utf_string string, const f_utf_string_length start, const f_utf_string_length stop, f_utf_string_dynamic *result) {
    // The start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations.
    f_utf_string_length size = (stop - start) + 1;

    if (size == 0) return f_no_data;

    f_status status = f_none;

    if (result == 0) {
      f_macro_string_dynamic_new(status, (*result), size);
    }
    else {
      f_macro_string_dynamic_resize(status, (*result), size);
    }

    if (f_status_is_error(status)) {
      return status;
    }

    memcpy(result->string, string + start, size);
    result->used = size;

    return f_none;
  }
#endif // !defined(_di_fl_utf_string_rip_) || !defined(_di_fl_utf_string_dynamic_rip_)

#if !defined(_di_fl_utf_string_rip_trim_) || !defined(_di_fl_utf_string_dynamic_rip_trim_)
  f_return_status private_fl_utf_string_rip_trim(const f_utf_string string, const f_utf_string_length start, const f_utf_string_length stop, f_utf_string_dynamic *result) {
    // The start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations.
    f_utf_string_length size = (stop - start) + 1;

    if (size == 0) return f_no_data;

    f_status status = f_none;

    if (result == 0) {
      f_macro_string_dynamic_new(status, (*result), size);
    }
    else {
      f_macro_string_dynamic_resize(status, (*result), size);
    }

    if (f_status_is_error(status)) {
      return status;
    }

    f_utf_string_length begin = start;
    f_utf_string_length end = stop;

    // skip past leading whitespace.
    for (; begin <= end; begin++) {
      // skip past NULL.
      while (begin < size && string[begin] == f_string_eos) begin++;
      if (begin > end) break;

      status = f_utf_character_is_whitespace(string[begin]);
      if (f_status_is_error(status)) {
        // ignore possibly invalid UTF-8 codes.
        if (f_status_set_fine(status) != f_maybe) {
          return status;
        }
      }

      if (status == f_false) break;
    } // for

    for (; end > begin; end--) {
      // skip past NULL.
      if (string[end] == f_string_eos) continue;
      if (end == begin) break;

      status = f_utf_character_is_whitespace(string[end]);
      if (f_status_is_error(status)) {
        // ignore possibly invalid UTF-8 codes.
        if (f_status_set_fine(status) != f_maybe) {
          return status;
        }
      }

      if (status == f_false) break;
    } // for

    memcpy(result->string, string + begin, (end - begin) + 1);
    result->used = (end - begin) + 1;

    return f_none;
  }
#endif // !defined(_di_fl_utf_string_rip_trim_) || !defined(_di_fl_utf_string_dynamic_rip_trim_)

#ifdef __cplusplus
} // extern "C"
#endif

#include <level_1/string.h>
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_)
  f_return_status private_fl_string_append(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    if (destination->used + length > f_string_length_size) return F_status_set_error(F_string_too_large);

    f_status status = F_none;

    const f_string_length total = destination->used + length;

    if (total > destination->size) {
      f_macro_string_dynamic_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source, length);
    destination->used = total;

    return F_none;
  }
#endif // !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_)

#if !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_)
  f_return_status private_fl_string_append_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    if (destination->used + length > f_string_length_size) return F_status_set_error(F_string_too_large);

    f_status status = F_none;

    f_string_length first = 0;

    for (f_string_length i = 0; i <= length; i++) {
      if (i == length) {
        if (i > first) {
          f_string_length size = i - first;

          if (destination->used + size > f_string_length_size) return F_status_set_error(F_string_too_large);

          f_string_length total = destination->used + size;

          if (total > destination->size) {
            f_macro_string_dynamic_resize(status, (*destination), total);
            if (F_status_is_error(status)) return status;
          }

          memcpy(destination->string + destination->used, source + first, size);
          destination->used = total;
        }

        break;
      }

      if (source[i] == 0) {
        if (i > 0) {
          if (i > first) {
            f_string_length size = i - first;

            if (destination->used + size > f_string_length_size) return F_status_set_error(F_string_too_large);

            f_string_length total = destination->used + size;

            if (total > destination->size) {
              f_macro_string_dynamic_resize(status, (*destination), total);
              if (F_status_is_error(status)) return status;
            }

            memcpy(destination->string + destination->used, source + first, size);
            destination->used = total;
          }
        }

        while (i + 1 < length && source[i + 1] == 0) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_)

#if !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)
  f_return_status private_fl_string_compare(const f_string string1, const f_string string2, const f_string_length offset1, const f_string_length offset2, const f_string_length stop1, const f_string_length stop2) {
    f_string_length i1 = offset1;
    f_string_length i2 = offset2;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      // skip past NULL in string1.
      while (i1 < stop1 && string1[i1] == 0) i1++;
      if (i1 == stop1) break;

      // skip past NULL in string2.
      while (i2 < stop2 && string2[i2] == 0) i2++;
      if (i2 == stop2) break;

      if (string1[i1] != string2[i2]) return F_equal_to_not;
    } // for

    // only return F_equal_to if all remaining characters are NULL.
    for (; i1 < stop1; i1++) {
      if (string1[i1] != 0) return F_equal_to_not;
    } // for

    for (; i2 < stop2; i2++) {
      if (string2[i2] != 0) return F_equal_to_not;
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)

#if !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)
  f_return_status private_fl_string_compare_trim(const f_string string1, const f_string string2, const f_string_length offset1, const f_string_length offset2, const f_string_length stop1, const f_string_length stop2) {
    f_string_length i1 = offset1;
    f_string_length i2 = offset2;

    uint8_t width = 0;
    uint8_t width_max = 0;
    f_status status = F_none;

    // skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += width) {
      // skip past NULL in string1.
      while (i1 < stop1 && string1[i1] == 0) i1++;
      if (i1 == stop1) break;

      width_max = (stop1 - i1) + 1;
      status = f_utf_is_whitespace(string1 + i1, width_max);
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;

      width = f_macro_utf_byte_width(string1[i1]);
    } // for

    // skip past leading whitespace in string2.
    for (; i2 < stop2; i2 += width) {
      // skip past NULL in string2.
      while (i2 < stop2 && string2[i2] == 0) i2++;
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

      width = f_macro_utf_byte_width(string2[i2]);
    } // for

    f_string_length last1 = i1;
    f_string_length last2 = i2;

    {
      // size1 and size2 are to represent to total number of characters after trim.
      f_string_length size1 = 0;
      f_string_length size2 = 0;

      // determine where the last non-whitespace is in string1.
      for (f_string_length j = i1; j < stop1; j += width) {
        // skip past NULL in string1.
        while (j < stop1 && string1[j] == 0) j++;
        if (j == stop1) break;

        width_max = (stop1 - j) + 1;
        status = f_utf_is_whitespace(string1 + j, width_max);
        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

          return status;
        }

        width = f_macro_utf_byte_width(string1[j]);

        if (status == F_false) {
          last1 = j;
          size1++;
        }
      } // for

      // determine where the last non-whitespace is in string2.
      for (f_string_length j = i2; j < stop2; j += width) {
        // skip past NULL in string2.
        while (j < stop2 && string2[j] == 0) j++;
        if (j == stop2) break;

        width_max = (stop2 - j) + 1;
        status = f_utf_is_whitespace(string2 + j, width_max);
        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

          return status;
        }

        width = f_macro_utf_byte_width(string2[j]);

        if (status == F_false) {
          last2 = j;
          size2++;
        }
      } // for

      if (size1 != size2) return F_equal_to_not;
    }

    for (; i1 < last1 && i2 < last2; i1++, i2++) {
      // skip past NULL in string1.
      while (i1 < last1 && string1[i1] == 0) i1++;
      if (i1 == last1) break;

      // skip past NULL in string2.
      while (i2 < last2 && string2[i2] == 0) i2++;
      if (i2 == last2) break;

      if (string1[i1] != string2[i2]) return F_equal_to_not;
    } // for

    // only return F_equal_to if all remaining characters are NULL.
    while (i1 < last1) {
      if (string1[i1] != 0) return F_equal_to_not;
      i1++;
    } // while

    while (i2 < last2) {
      if (string2[i2] != 0) return F_equal_to_not;
      i2++;
    } // while

    return F_equal_to;
  }
#endif // !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)

#if !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_)
  f_return_status private_fl_string_prepend(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    if (destination->used + length > f_string_length_size) return F_status_set_error(F_string_too_large);

    f_status status = F_none;

    const f_string_length total = destination->used + length;

    if (total > destination->size) {
      f_macro_string_dynamic_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used > 0) {
      memmove(destination->string + length, destination->string, destination->used);
      memcpy(destination->string, source, length);
    }
    else {
      memcpy(destination->string, source, length);
    }

    destination->used = total;
    return F_none;
  }
#endif // !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_)

#if !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_)
  f_return_status private_fl_string_prepend_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    if (destination->used + length > f_string_length_size) return F_status_set_error(F_string_too_large);

    f_status status = F_none;

    f_string_length first = 0;
    f_string_length offset = 0;

    for (f_string_length i = 0; i <= length; i++) {
      if (i == length) {
        if (i > first) {
          f_string_length size = i - first;

          if (destination->used + size > f_string_length_size) return F_status_set_error(F_string_too_large);

          f_string_length total = destination->used + size;

          if (total > destination->size) {
            f_macro_string_dynamic_resize(status, (*destination), total);
            if (F_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
          memcpy(destination->string + offset, source + first, size);

          destination->used = total;
          offset += size;
        }

        break;
      }

      if (source[i] == 0) {
        if (i > 0) {
          if (i > first) {
            f_string_length size = i - first;

            if (destination->used + size > f_string_length_size) return F_status_set_error(F_string_too_large);

            f_string_length total = destination->used + size;

            if (total > destination->size) {
              f_macro_string_dynamic_resize(status, (*destination), total);

              if (F_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
            memcpy(destination->string + offset, source + first, size);

            destination->used = total;
            offset += size;
          }
        }

        while (i + 1 < length && source[i + 1] == 0) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_)

#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)
  f_return_status private_fl_string_rip_find_range(const f_string source, f_string_length *start, f_string_length *stop) {
    f_string_length stop_original = *stop;

    f_status status = F_none;

    uint8_t width = 0;

    // skip past leading whitespace.
    for (; *start <= *stop; *start += width) {
      // skip past NULL.
      while (*start < *stop && source[*start] == 0) (*start)++;
      if (*start > *stop) break;

      status = f_utf_is_whitespace(source + *start, (*stop - *start) + 1);
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;

      width = f_macro_utf_byte_width(source[*start]);
    } // for

    for (; *stop > *start; (*stop)--) {

      // skip past NULL.
      while (*stop > *start && source[*stop] == 0) (*stop)--;

      if (source[*stop] == 0) continue;
      if (*stop == *start) break;

      // each UTF-8 character of width 1 is an incomplete part.
      // go left until either width is 0 (ascii, or > 1) to determine the character.
      for (;;) {
        width = f_macro_utf_byte_width_is(source[*stop]);

        if (width == 1) {
          (*stop)--;

          if (*stop == *start) break;
        }
        else break;
      } // for

      if (*stop == *start) break;

      status = f_utf_is_whitespace(source + *stop, (stop_original - *stop) + 1);
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_false) break;
    } // for

    if (*stop == *start) {
      status = f_utf_is_whitespace(source + *stop, (stop_original - *stop) + 1);
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_utf);

        return status;
      }

      if (status == F_true) return F_data_not;
    }

    return F_none;
  }
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#include <level_1/string.h>
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_)
  f_return_status private_fl_string_append(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) {
    // The start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations.
    f_string_length source_length = (stop - start) + 1;

    if (destination->used + source_length > f_string_max_size) return f_status_set_error(f_string_too_large);

    f_status status = f_none;

    const f_string_length total = destination->used + source_length;

    if (total > destination->size) {
      f_macro_string_dynamic_resize(status, (*destination), total);
      if (f_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source + start, source_length);
    destination->used = total;

    return f_none;
  }
#endif // !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_)

#if !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_)
  f_return_status private_fl_string_append_nulless(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) {
    // The start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations.
    f_string_length source_length = (stop - start) + 1;

    if (destination->used + source_length > f_string_max_size) return f_status_set_error(f_string_too_large);

    f_status status = f_none;

    f_string_length first = 0;

    for (f_string_length i = 0; i <= source_length; i++) {
      if (i == source_length) {
        if (i > first) {
          f_string_length length = i - first;

          if (destination->used + length > f_string_max_size) return f_status_set_error(f_string_too_large);

          f_string_length total = destination->used + length;

          if (total > destination->size) {
            f_macro_string_dynamic_resize(status, (*destination), total);
            if (f_status_is_error(status)) return status;
          }

          memcpy(destination->string + destination->used, source + first, length);
          destination->used = total;
        }

        break;
      }

      if (source[i] == f_string_eos) {
        if (i > 0) {
          if (i > first) {
            f_string_length length = i - first;

            if (destination->used + length > f_string_max_size) return f_status_set_error(f_string_too_large);

            f_string_length total = destination->used + length;

            if (total > destination->size) {
              f_macro_string_dynamic_resize(status, (*destination), total);
              if (f_status_is_error(status)) return status;
            }

            memcpy(destination->string + destination->used, source + first, length);
            destination->used = total;
          }
        }

        while (i + 1 < source_length && source[i + 1] == f_string_eos) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return f_none;
  }
#endif // !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_)

#if !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)
  f_return_status private_fl_string_compare(const f_string string1, const f_string string2, const f_string_length offset1, const f_string_length offset2, const f_string_length stop1, const f_string_length stop2) {
    f_string_length i1 = offset1;
    f_string_length i2 = offset2;

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
#endif // !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)

#if !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)
  f_return_status private_fl_string_compare_trim(const f_string string1, const f_string string2, const f_string_length offset1, const f_string_length offset2, const f_string_length stop1, const f_string_length stop2) {
    f_string_length i1 = offset1;
    f_string_length i2 = offset2;

    uint8_t width = 0;
    uint8_t width_max = 0;
    f_status status = f_none;

    // skip past leading whitespace in string1.
    for (; i1 < stop1; i1 += width) {
      // skip past NULL in string1.
      while (i1 < stop1 && string1[i1] == f_string_eos) i1++;
      if (i1 == stop1) break;

      width_max = (stop1 - i1) + 1;
      status = f_utf_is_whitespace(string1 + i1, width_max);
      if (f_status_is_error(status)) {
        if (f_status_set_fine(status) == f_maybe) return f_status_set_error(f_invalid_utf);

        return status;
      }

      if (status == f_false) break;

      width = f_macro_utf_byte_width(string1[i1]);
    } // for

    // skip past leading whitespace in string2.
    for (; i2 < stop2; i2 += width) {
      // skip past NULL in string2.
      while (i2 < stop2 && string2[i2] == f_string_eos) i2++;
      if (i2 == stop2) break;

      width_max = (stop2 - i2) + 1;
      status = f_utf_is_whitespace(string2 + i2, width_max);
      if (f_status_is_error(status)) {
        if (f_status_set_fine(status) == f_maybe) {
          return f_status_set_error(f_invalid_utf);
        }

        return status;
      }

      if (status == f_false) break;

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
        while (j < stop1 && string1[j] == f_string_eos) j++;
        if (j == stop1) break;

        width_max = (stop1 - j) + 1;
        status = f_utf_is_whitespace(string1 + j, width_max);
        if (f_status_is_error(status)) {
          if (f_status_set_fine(status) == f_maybe) return f_status_set_error(f_invalid_utf);

          return status;
        }

        width = f_macro_utf_byte_width(string1[j]);

        if (status == f_false) {
          last1 = j;
          size1++;
        }
      } // for

      // determine where the last non-whitespace is in string2.
      for (f_string_length j = i2; j < stop2; j += width) {
        // skip past NULL in string2.
        while (j < stop2 && string2[j] == f_string_eos) j++;
        if (j == stop2) break;

        width_max = (stop2 - j) + 1;
        status = f_utf_is_whitespace(string2 + j, width_max);
        if (f_status_is_error(status)) {
          if (f_status_set_fine(status) == f_maybe) return f_status_set_error(f_invalid_utf);

          return status;
        }

        width = f_macro_utf_byte_width(string2[j]);

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
    while (i1 < last1) {
      if (string1[i1] != f_string_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < last2) {
      if (string2[i2] != f_string_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)

#if !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_)
  f_return_status private_fl_string_prepend(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) {
    // The start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations.
    f_string_length source_length = (stop - start) + 1;

    if (destination->used + source_length > f_string_max_size) return f_status_set_error(f_string_too_large);

    f_status status = f_none;

    const f_string_length total = destination->used + source_length;

    if (total > destination->size) {
      f_macro_string_dynamic_resize(status, (*destination), total);
      if (f_status_is_error(status)) return status;
    }

    if (destination->used > 0) {
      memmove(destination->string + source_length, destination->string, destination->used);
      memcpy(destination->string, source + start, source_length);
    }
    else {
      memcpy(destination->string, source + start, source_length);
    }

    destination->used = total;
    return f_none;
  }
#endif // !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_)

#if !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_)
  f_return_status private_fl_string_prepend_nulless(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) {
    // The start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations.
    f_string_length source_length = (stop - start) + 1;

    if (destination->used + source_length > f_string_max_size) return f_status_set_error(f_string_too_large);

    f_status status = f_none;

    f_string_length first = 0;
    f_string_length offset = 0;

    for (f_string_length i = 0; i <= source_length; i++) {
      if (i == source_length) {
        if (i > first) {
          f_string_length length = i - first;

          if (destination->used + length > f_string_max_size) return f_status_set_error(f_string_too_large);

          f_string_length total = destination->used + length;

          if (total > destination->size) {
            f_macro_string_dynamic_resize(status, (*destination), total);
            if (f_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + length, destination->string + offset, destination->used - offset);
          memcpy(destination->string + offset, source + first, length);

          destination->used = total;
          offset += length;
        }

        break;
      }

      if (source[i] == f_string_eos) {
        if (i > 0) {
          if (i > first) {
            f_string_length length = i - first;

            if (destination->used + length > f_string_max_size) return f_status_set_error(f_string_too_large);

            f_string_length total = destination->used + length;

            if (total > destination->size) {
              f_macro_string_dynamic_resize(status, (*destination), total);

              if (f_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + length, destination->string + offset, destination->used - offset);
            memcpy(destination->string + offset, source + first, length);

            destination->used = total;
            offset += length;
          }
        }

        while (i + 1 < source_length && source[i + 1] == f_string_eos) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return f_none;
  }
#endif // !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_)

#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)
  f_return_status private_fl_string_rip_find_range(const f_string source, f_string_length *start, f_string_length *stop) {
    f_string_length stop_original = *stop;

    f_status status = f_none;

    uint8_t width = 0;

    // skip past leading whitespace.
    for (; *start <= *stop; *start += width) {
      // skip past NULL.
      while (*start < *stop && source[*start] == f_string_eos) (*start)++;
      if (*start > *stop) break;

      status = f_utf_is_whitespace(source + *start, (*stop - *start) + 1);
      if (f_status_is_error(status)) {
        if (f_status_set_fine(status) == f_maybe) return f_status_set_error(f_invalid_utf);

        return status;
      }

      if (status == f_false) break;

      width = f_macro_utf_byte_width(source[*start]);
    } // for

    for (; *stop > *start; (*stop)--) {

      // skip past NULL.
      while (*stop > *start && source[*stop] == f_string_eos) (*stop)--;

      if (source[*stop] == f_string_eos) continue;
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
      if (f_status_is_error(status)) {
        if (f_status_set_fine(status) == f_maybe) return f_status_set_error(f_invalid_utf);

        return status;
      }

      if (status == f_false) break;
    } // for

    return f_none;
  }
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

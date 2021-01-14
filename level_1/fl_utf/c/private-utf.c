#include "utf.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_utf_string_append_) || !defined(_di_fl_utf_string_dynamic_append_) || !defined(_di_fl_utf_string_append_mash_) || !defined(_di_fl_utf_string_dynamic_mash_)
  f_status_t private_fl_utf_string_append(const f_utf_string_t source, const f_utf_string_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > f_utf_string_t_size_max) return F_status_set_error(F_string_too_large);

    f_status_t status = F_none;

    const f_utf_string_length_t total = destination->used + length;

    if (total > destination->size) {
      f_macro_utf_string_dynamic_t_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source, length);
    destination->used = total;

    return F_none;
  }
#endif // !defined(_di_fl_utf_string_append_) || !defined(_di_fl_utf_string_dynamic_append_) || !defined(_di_fl_utf_string_append_mash_) || !defined(_di_fl_utf_string_dynamic_mash_)

#if !defined(_di_fl_utf_string_append_nulless_) || !defined(_di_fl_utf_string_dynamic_append_nulless_) || !defined(_di_fl_utf_string_mash_nulless_) || !defined(_di_fl_utf_string_dynamic_mash_nulless_)
  f_status_t private_fl_utf_string_append_nulless(const f_utf_string_t source, const f_utf_string_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > f_utf_string_t_size_max) return F_status_set_error(F_string_too_large);

    f_status_t status = F_none;

    f_utf_string_length_t first = 0;

    for (f_utf_string_length_t i = 0; i <= length; i++) {

      if (i == length) {
        if (i > first) {
          f_utf_string_length_t size = i - first;

          if (destination->used + size > f_utf_string_t_size_max) {
            return F_status_set_error(F_string_too_large);
          }

          f_utf_string_length_t total = destination->used + size;

          if (total > destination->size) {
            f_macro_utf_string_dynamic_t_resize(status, (*destination), total);
            if (F_status_is_error(status)) return status;
          }

          memcpy(destination->string + destination->used, source + first, size);
          destination->used = total;
        }

        break;
      }

      if (source[i] == f_utf_character_t_eos) {
        if (i > 0) {
          if (i > first) {
            f_utf_string_length_t size = i - first;

            if (destination->used + size > f_utf_string_t_size_max) {
              return F_status_set_error(F_string_too_large);
            }

            f_utf_string_length_t total = destination->used + size;

            if (total > destination->size) {
              f_macro_utf_string_dynamic_t_resize(status, (*destination), total);
              if (F_status_is_error(status)) return status;
            }

            memcpy(destination->string + destination->used, source + first, size);
            destination->used = total;
          }
        }

        while (i + 1 < length && source[i + 1] == f_utf_character_t_eos) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_utf_string_append_nulless_) || !defined(_di_fl_utf_string_dynamic_append_nulless_) || !defined(_di_fl_utf_string_mash_nulless_) || !defined(_di_fl_utf_string_dynamic_mash_nulless_)

#if !defined(_di_fl_utfl_string_compare_) || !defined(_di_fl_utfl_string_dynamic_compare_) || !defined(_di_fl_utfl_string_dynamic_partial_compare_)
  f_status_t private_fl_utfl_string_compare(const f_utf_string_t string1, const f_utf_string_t string2, const f_utf_string_length_t offset1, const f_utf_string_length_t offset2, const f_utf_string_length_t stop1, const f_utf_string_length_t stop2) {
    f_utf_string_length_t i1 = offset1;
    f_utf_string_length_t i2 = offset2;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {

      // skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) i1++;
      if (i1 == stop1) break;

      // skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) i2++;
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
#endif // !defined(_di_fl_utfl_string_compare_) || !defined(_di_fl_utfl_string_dynamic_compare_) || !defined(_di_fl_utfl_string_dynamic_partial_compare_)

#if !defined(_di_fl_utfl_string_compare_trim_) || !defined(_di_fl_utfl_string_dynamic_compare_trim_) || !defined(_di_fl_utfl_string_dynamic_partial_compare_trim_)
  f_status_t private_fl_utfl_string_compare_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_utf_string_length_t offset1, const f_utf_string_length_t offset2, const f_utf_string_length_t stop1, const f_utf_string_length_t stop2) {
    f_utf_string_length_t i1 = offset1;
    f_utf_string_length_t i2 = offset2;

    f_status_t status = F_none;

    // skip past leading whitespace in string1.
    for (; i1 < stop1; i1++) {

      // skip past NULL in string1.
      while (i1 < stop1 && !string1[i1]) i1++;
      if (i1 == stop1) break;

      status = f_utf_character_is_whitespace(string1[i1]);

      if (F_status_is_error(status)) {
        // ignore possibly invalid UTF-8 codes.
        if (F_status_set_fine(status) != F_maybe) {
          return status;
        }
      }

      if (status == F_false) break;
    } // for

    // skip past leading whitespace in string2.
    for (; i2 < stop2; i2++) {

      // skip past NULL in string2.
      while (i2 < stop2 && !string2[i2]) i2++;
      if (i2 == stop2) break;

      status = f_utf_character_is_whitespace(string2[i2]);

      if (F_status_is_error(status)) {
        // ignore possibly invalid UTF-8 codes.
        if (F_status_set_fine(status) != F_maybe) {
          return status;
        }
      }

      if (status == F_false) break;
    } // for

    f_utf_string_length_t last1 = i1;
    f_utf_string_length_t last2 = i2;

    {
      // size1 and size2 are to represent to total number of characters after trim.
      f_utf_string_length_t size1 = 0;
      f_utf_string_length_t size2 = 0;

      // determine where the last non-whitespace is in string1.
      for (f_utf_string_length_t j = i1; j < stop1; j++) {

        // skip past NULL in string1.
        while (j < stop1 && !string1[j]) j++;
        if (j == stop1) break;

        status = f_utf_character_is_whitespace(string1[j]);

        if (F_status_is_error(status)) {
          // ignore possibly invalid UTF-8 codes.
          if (F_status_set_fine(status) != F_maybe) {
            return status;
          }
        }

        if (status == F_false) {
          last1 = j;
          size1++;
        }
      } // for

      // determine where the last non-whitespace is in string2.
      for (f_utf_string_length_t j = i2; j < stop2; j++) {

        // skip past NULL in string2.
        while (j < stop2 && !string2[j]) j++;
        if (j == stop2) break;

        status = f_utf_character_is_whitespace(string2[j]);

        if (F_status_is_error(status)) {
          // ignore possibly invalid UTF-8 codes.
          if (F_status_set_fine(status) != F_maybe) {
            return status;
          }
        }

        if (status == F_false) {
          last2 = j;
          size2++;
        }
      } // for

      if (size1 != size2) return F_equal_to_not;
    }

    for (; i1 < last1 && i2 < last2; i1++, i2++) {

      // skip past NULL in string1.
      while (i1 < last1 && !string1[i1]) i1++;
      if (i1 == last1) break;

      // skip past NULL in string2.
      while (i2 < last2 && !string2[i2]) i2++;
      if (i2 == last2) break;

      if (string1[i1] != string2[i2]) return F_equal_to_not;
    } // for

    // only return F_equal_to if all remaining characters are NULL.
    for (; i1 < last1; i1++) {
      if (string1[i1] != 0) return F_equal_to_not;
    } // for

    for (; i2 < last2; i2++) {
      if (string2[i2] != 0) return F_equal_to_not;
    } // for

    return F_equal_to;
  }
#endif // !defined(_di_fl_utfl_string_compare_trim_) || !defined(_di_fl_utfl_string_dynamic_compare_trim_) || !defined(_di_fl_utfl_string_dynamic_partial_compare_trim_)

#if !defined(_di_fl_utf_string_prepend_) || !defined(_di_fl_utf_string_dynamic_prepend_)
  f_status_t private_fl_utf_string_prepend(const f_utf_string_t source, const f_utf_string_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > f_utf_string_t_size_max) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    const f_utf_string_length_t total = destination->used + length;

    if (total > destination->size) {
      f_macro_utf_string_dynamic_t_resize(status, (*destination), total);
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
#endif // !defined(_di_fl_utf_string_prepend_) || !defined(_di_fl_utf_string_dynamic_prepend_)

#if !defined(_di_fl_utf_string_prepend_nulless_) || !defined(_di_fl_utf_string_dynamic_prepend_nulless_)
  f_status_t private_fl_utf_string_prepend_nulless(const f_utf_string_t source, const f_utf_string_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > f_utf_string_t_size_max) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    f_utf_string_length_t first = 0;
    f_utf_string_length_t offset = 0;

    for (f_utf_string_length_t i = 0; i <= length; i++) {

      if (i == length) {
        if (i > first) {
          const f_utf_string_length_t size = i - first;

          if (destination->used + size > f_utf_string_t_size_max) {
            return F_status_set_error(F_string_too_large);
          }

          const f_utf_string_length_t total = destination->used + size;

          if (total > destination->size) {
            f_macro_utf_string_dynamic_t_resize(status, (*destination), total);
            if (F_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
          memcpy(destination->string + offset, source + first, size);

          destination->used = total;
          offset += size;
        }

        break;
      }

      if (source[i] == f_utf_character_t_eos) {
        if (i > 0) {
          if (i > first) {
            const f_utf_string_length_t size = i - first;

            if (destination->used + size > f_utf_string_t_size_max) {
              return F_status_set_error(F_string_too_large);
            }

            const f_utf_string_length_t total = destination->used + size;

            if (total > destination->size) {
              f_macro_utf_string_dynamic_t_resize(status, (*destination), total);

              if (F_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
            memcpy(destination->string + offset, source + first, size);

            destination->used = total;
            offset += size;
          }
        }

        while (i + 1 < length && source[i + 1] == f_utf_character_t_eos) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_utf_string_prepend_nulless_) || !defined(_di_fl_utf_string_dynamic_prepend_nulless_)

#if !defined(_di_fl_utfl_string_rip_) || !defined(_di_fl_utfl_string_dynamic_rip_) || !defined(_di_fl_utfl_string_rip_nulless_) || !defined(_di_fl_utfl_string_dynamic_rip_nulless_)
  f_status_t private_fl_utfl_string_rip_find_range(const f_utf_string_t source, f_utf_string_length_t *start, f_utf_string_length_t *stop) {

    f_status_t status = F_none;

    // skip past leading whitespace.
    for (; *start <= *stop; (*start)++) {

      // skip past NULL.
      while (*start < *stop && !source[*start]) (*start)++;
      if (*start > *stop) break;

      status = f_utf_character_is_whitespace(source[*start]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; *stop > *start; (*stop)--) {

      // skip past NULL.
      while (*stop > *start && !source[*stop]) (*stop)--;

      if (!source[*stop]) continue;
      if (*stop == *start) break;

      status = f_utf_character_is_whitespace(source[*stop]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    if (*stop == *start) {
      status = f_utf_character_is_whitespace(source[*stop]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) return F_data_not;
    }

    return F_none;
  }
#endif // !defined(_di_fl_utfl_string_rip_) || !defined(_di_fl_utfl_string_dynamic_rip_) || !defined(_di_fl_utfl_string_rip_nulless_) || !defined(_di_fl_utfl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

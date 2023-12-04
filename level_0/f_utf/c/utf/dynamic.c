#include "../utf.h"
#include "../private-utf.h"
#include "static.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_dynamic_append_
  f_status_t f_utf_string_dynamic_append(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_append_

#ifndef _di_f_utf_string_dynamic_append_assure_
  f_status_t f_utf_string_dynamic_append_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (destination->used < source.used) {
      return private_f_utf_string_append(source.string, source.used, destination);
    }

    f_number_unsigned_t i = 1;
    f_number_unsigned_t j = 1;

    while (i <= source.used && j <= destination->used) {

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_append_assure_

#ifndef _di_f_utf_string_dynamic_append_assure_nulless_
  f_status_t f_utf_string_dynamic_append_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (!destination->used) {
      return private_f_utf_string_append_nulless(source.string, source.used, destination);
    }

    {
      f_number_unsigned_t i = 1;
      f_number_unsigned_t j = 1;

      while (i <= source.used && j <= destination->used) {

        if (!source.string[source.used - i]) {
          ++i;

          continue;
        }

        if (!destination->string[destination->used - j]) {
          ++j;

          continue;
        }

        if (source.string[source.used - i] != destination->string[destination->used - j]) {
          return private_f_utf_string_append_nulless(source.string, source.used, destination);
        }

        ++i;
        ++j;
      } // while
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

#ifndef _di_f_utf_string_dynamic_append_nulless_
  f_status_t f_utf_string_dynamic_append_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_append_nulless_

#ifndef _di_f_utf_string_dynamic_mash_
  f_status_t f_utf_string_dynamic_mash(const f_utf_string_static_t glue, const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_append(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mash_

#ifndef _di_f_utf_string_dynamic_mash_nulless_
  f_status_t f_utf_string_dynamic_mash_nulless(const f_utf_string_static_t glue, const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_append_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mash_nulless_

#ifndef _di_f_utf_string_dynamic_mish_
  f_status_t f_utf_string_dynamic_mish(const f_utf_string_static_t glue, const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_prepend(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mish_

#ifndef _di_f_utf_string_dynamic_mish_nulless_
  f_status_t f_utf_string_dynamic_mish_nulless(const f_utf_string_static_t glue, const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_prepend_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mish_nulless_

#ifndef _di_f_utf_string_dynamic_partial_append_
  f_status_t f_utf_string_dynamic_partial_append(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (range.stop >= source.used) {
      return private_f_utf_string_append(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_append_

#ifndef _di_f_utf_string_dynamic_partial_append_assure_
  f_status_t f_utf_string_dynamic_partial_append_assure(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    {
      const f_number_unsigned_t length = range.stop >= source.used ? source.used - range.start : (range.stop - range.start) + 1;

      if (destination->used < length) {
        return private_f_utf_string_append(source.string + range.start, length, destination);
      }

      const f_number_unsigned_t stop = range.stop >= source.used ? source.used : range.stop + 1;
      f_number_unsigned_t i = 1;
      f_number_unsigned_t j = 1;

      while (i <= length && j <= destination->used) {

        if (source.string[stop - i] != destination->string[destination->used - j]) {
          return private_f_utf_string_append(source.string + range.start, length, destination);
        }

        ++i;
        ++j;
      } // while
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_partial_append_assure_

#ifndef _di_f_utf_string_dynamic_partial_append_assure_nulless_
  f_status_t f_utf_string_dynamic_partial_append_assure_nulless(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    {
      const f_number_unsigned_t length = range.stop >= source.used ? source.used - range.start : (range.stop - range.start) + 1;

      if (!destination->used) {
        return private_f_utf_string_append_nulless(source.string + range.start, length, destination);
      }

      const f_number_unsigned_t stop = range.stop >= source.used ? source.used : range.stop + 1;
      f_number_unsigned_t i = 1;
      f_number_unsigned_t j = 1;

      while (i <= length && j <= destination->used) {

        if (!source.string[stop - i]) {
          ++i;

          continue;
        }

        if (!destination->string[destination->used - j]) {
          ++j;

          continue;
        }

        if (source.string[stop - i] != destination->string[destination->used - j]) {
          return private_f_utf_string_append_nulless(source.string + range.start, length, destination);
        }

        ++i;
        ++j;
      } // while
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

#ifndef _di_f_utf_string_dynamic_partial_append_nulless_
  f_status_t f_utf_string_dynamic_partial_append_nulless(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (range.stop >= source.used) {
      return private_f_utf_string_append_nulless(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_append_nulless_

#ifndef _di_f_utf_string_dynamic_partial_mash_
  f_status_t f_utf_string_dynamic_partial_mash(const f_utf_string_static_t glue, const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_append(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    if (range.stop >= source.used) {
      return private_f_utf_string_append(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mash_

#ifndef _di_f_utf_string_dynamic_partial_mash_nulless_
  f_status_t f_utf_string_dynamic_partial_mash_nulless(const f_utf_string_static_t glue, const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_append_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    if (range.stop >= source.used) {
      return private_f_utf_string_append(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mash_nulless_

#ifndef _di_f_utf_string_dynamic_partial_mish_
  f_status_t f_utf_string_dynamic_partial_mish(const f_utf_string_static_t glue, const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_prepend(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    if (range.stop >= source.used) {
      return private_f_utf_string_append(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mish_

#ifndef _di_f_utf_string_dynamic_partial_mish_nulless_
  f_status_t f_utf_string_dynamic_partial_mish_nulless(const f_utf_string_static_t glue, const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (glue.used && destination->used) {
      const f_status_t status = private_f_utf_string_prepend_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    if (range.stop >= source.used) {
      return private_f_utf_string_append(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mish_nulless_

#ifndef _di_f_utf_string_dynamic_partial_prepend_
  f_status_t f_utf_string_dynamic_partial_prepend(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    if (range.stop >= source.used) {
      return private_f_utf_string_append(source.string + range.start, source.used - range.start, destination);
    }

    return private_f_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_

#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_
  f_status_t f_utf_string_dynamic_partial_prepend_assure(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    {
      const f_number_unsigned_t length = range.stop >= source.used ? source.used - range.start : (range.stop - range.start) + 1;

      if (destination->used < length) {
        return private_f_utf_string_prepend(source.string + range.start, length, destination);
      }

      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;

      while (i < length && j < destination->used) {

        if (source.string[i + range.start] != destination->string[j]) {
          return private_f_utf_string_prepend(source.string + range.start, length, destination);
        }

        ++i;
        ++j;
      } // while
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_

#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_nulless_
  f_status_t f_utf_string_dynamic_partial_prepend_assure_nulless(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    {
      const f_number_unsigned_t length = range.stop >= source.used ? source.used - range.start : (range.stop - range.start) + 1;

      if (!destination->used) {
        return private_f_utf_string_prepend_nulless(source.string + range.start, length, destination);
      }

      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;

      while (i < length && j < destination->used) {

        if (!source.string[i + range.start]) {
          ++i;

          continue;
        }

        if (!destination->string[j]) {
          ++j;

          continue;
        }

        if (source.string[i + range.start] != destination->string[j]) {
          return private_f_utf_string_prepend_nulless(source.string + range.start, length, destination);
        }

        ++i;
        ++j;
      } // while
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_nulless

#ifndef _di_f_utf_string_dynamic_partial_prepend_nulless_
  f_status_t f_utf_string_dynamic_partial_prepend_nulless(const f_utf_string_static_t source, const f_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;
    if (range.start >= source.used) return F_data_not_eos;

    return private_f_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_nulless

#ifndef _di_f_utf_string_dynamic_prepend_
  f_status_t f_utf_string_dynamic_prepend(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_prepend_

#ifndef _di_f_utf_string_dynamic_prepend_assure_
  f_status_t f_utf_string_dynamic_prepend_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (destination->used < source.used) {
      return private_f_utf_string_prepend(source.string, source.used, destination);
    }

    {
      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;

      for (; i < source.used && j < destination->used; ++i, ++j) {

        if (source.string[i] != destination->string[j]) {
          return private_f_utf_string_prepend(source.string, source.used, destination);
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_prepend_assure_

#ifndef _di_f_utf_string_dynamic_prepend_assure_nulless_
  f_status_t f_utf_string_dynamic_prepend_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    if (!destination->used) {
      return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    while (i < source.used && j < destination->used) {

      if (!source.string[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i] != destination->string[j]) {
        return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_prepend_assure_nulless_

#ifndef _di_f_utf_string_dynamic_prepend_nulless_
  f_status_t f_utf_string_dynamic_prepend_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_prepend_nulless_

#ifndef _di_f_utf_string_dynamic_seek_line_
  f_status_t f_utf_string_dynamic_seek_line(const f_utf_string_static_t buffer, f_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != f_utf_char_eol_s) {

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) return F_status_set_error(F_utf_fragment);

      ++range->start;

      if (range->start >= buffer.used) return F_okay_eos;
      if (range->start > range->stop) return F_okay_stop;
    } // while

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_seek_line_

#ifndef _di_f_utf_string_dynamic_seek_line_to_
  f_status_t f_utf_string_dynamic_seek_line_to(const f_utf_string_static_t buffer, const f_utf_char_t seek_to_this, f_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != seek_to_this) {

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) return F_status_set_error(F_utf_fragment);
      if (buffer.string[range->start] == f_utf_char_eol_s) return F_okay_eol;

      ++range->start;

      if (range->start >= buffer.used) return F_okay_eos;
      if (range->start > range->stop) return F_okay_stop;
    } // while

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_seek_line_to_

#ifndef _di_f_utf_string_dynamic_seek_to_
  f_status_t f_utf_string_dynamic_seek_to(const f_utf_string_static_t buffer, const f_utf_char_t seek_to_this, f_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != seek_to_this) {

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) return F_status_set_error(F_utf_fragment);

      ++range->start;

      if (range->start >= buffer.used) return F_okay_eos;
      if (range->start > range->stop) return F_okay_stop;
    } // while

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_seek_to_

#ifndef _di_f_utf_string_dynamic_terminate_
  f_status_t f_utf_string_dynamic_terminate(f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used && !destination->string[destination->used - 1]) return F_okay;
    if (destination->used == F_string_t_size_d) return F_status_set_error(F_string_too_large);

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_utf_char_t), (void **) &destination->string, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used++] = 0;

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_terminate_

#ifndef _di_f_utf_string_dynamic_terminate_after_
  f_status_t f_utf_string_dynamic_terminate_after(f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used < destination->size && !destination->string[destination->used]) return F_okay;
    if (destination->used == F_string_t_size_d) return F_status_set_error(F_string_too_large);

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_utf_char_t), (void **) &destination->string, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;

    return F_okay;
  }
#endif // _di_f_utf_string_dynamic_terminate_after_

#ifdef __cplusplus
} // extern "C"
#endif

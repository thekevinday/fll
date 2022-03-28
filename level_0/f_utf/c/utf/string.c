#include "../utf.h"
#include "private-dynamic.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_append_
  f_status_t f_utf_string_append(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    return private_f_utf_string_append(source, length, destination);
  }
#endif // _di_f_utf_string_append_

#ifndef _di_f_utf_string_append_assure_
  f_status_t f_utf_string_append_assure(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (destination->used < length) {
      return private_f_utf_string_append(source, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source[length - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_append_assure_

#ifndef _di_f_utf_string_append_assure_nulless_
  f_status_t f_utf_string_append_assure_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (!destination->used) {
      return private_f_utf_string_append_nulless(source, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source[length - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append_nulless(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_append_assure_nulless_

#ifndef _di_f_utf_string_append_nulless_
  f_status_t f_utf_string_append_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    return private_f_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_append_nulless_

#ifndef _di_f_utf_string_mash_
  f_status_t f_utf_string_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) {
      return F_data_not;
    }

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source, length, destination);
  }
#endif // _di_f_utf_string_mash_

#ifndef _di_f_utf_string_mash_nulless_
  f_status_t f_utf_string_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_mash_nulless_

#ifndef _di_f_utf_string_mish_
  f_status_t f_utf_string_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source, length, destination);
  }
#endif // _di_f_utf_string_mish_

#ifndef _di_f_utf_string_mish_nulless_
  f_status_t f_utf_string_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_mish_nulless_

#ifndef _di_f_utf_string_prepend_
  f_status_t f_utf_string_prepend(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    return private_f_utf_string_prepend(source, length, destination);
  }
#endif // _di_f_utf_string_prepend_

#ifndef _di_f_utf_string_prepend_assure_
  f_status_t f_utf_string_prepend_assure(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (destination->used < length) {
      return private_f_utf_string_prepend(source, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source[i] != destination->string[j]) {
        return private_f_utf_string_prepend(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_prepend_assure_

#ifndef _di_f_utf_string_prepend_assure_nulless_
  f_status_t f_utf_string_prepend_assure_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    if (!destination->used) {
      return private_f_utf_string_prepend_nulless(source, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source[i] != destination->string[j]) {
        return private_f_utf_string_prepend_nulless(source, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_prepend_assure_nulless_

#ifndef _di_f_utf_string_prepend_nulless_
  f_status_t f_utf_string_prepend_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not;

    return private_f_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_f_utf_string_prepend_nulless_

#ifndef _di_f_utf_string_seek_line_
  f_status_t f_utf_string_seek_line(const f_utf_string_t string, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    while (string[range->start] != F_utf_character_t_eol_d) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      ++range->start;

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_line_

#ifndef _di_f_utf_string_seek_line_to_
  f_status_t f_utf_string_seek_line_to(const f_utf_string_t string, const f_char_t seek_to, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    while (string[range->start] != seek_to) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (string[range->start] == F_utf_character_t_eol_d) {
        return F_none_eol;
      }

      ++range->start;

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_line_to_

#ifndef _di_f_utf_string_seek_to_
  f_status_t f_utf_string_seek_to(const f_utf_string_t string, const f_char_t seek_to, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    while (string[range->start] != seek_to) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      ++range->start;

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_seek_to_

#ifdef __cplusplus
} // extern "C"
#endif

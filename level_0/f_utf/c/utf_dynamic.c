#include "utf.h"
#include "private-utf.h"
#include "private-utf_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_static_empty_s_
  const f_utf_string_static_t f_utf_string_static_empty_s = macro_f_utf_string_static_t_initialize(0, 0);
#endif // _di_f_utf_string_static_empty_s_

#ifndef _di_f_utf_string_dynamic_adjust_
  f_status_t f_utf_string_dynamic_adjust(const f_array_length_t length, f_utf_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamic_adjust(length, dynamic);
  }
#endif // _di_f_utf_string_dynamic_adjust_

#ifndef _di_f_utf_string_dynamic_append_
  f_status_t f_utf_string_dynamic_append(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    return private_f_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_append_

#ifndef _di_f_utf_string_dynamic_append_assure_
  f_status_t f_utf_string_dynamic_append_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_append(source.string, source.used, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

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
        return private_f_utf_string_append(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_append_assure_

#ifndef _di_f_utf_string_dynamic_append_assure_nulless_
  f_status_t f_utf_string_dynamic_append_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_append_nulless(source.string, source.used, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

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

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

#ifndef _di_f_utf_string_dynamic_append_nulless_
  f_status_t f_utf_string_dynamic_append_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_append_nulless_

#ifndef _di_f_utf_string_dynamic_decimate_by_
  f_status_t f_utf_string_dynamic_decimate_by(const f_array_length_t amount, f_utf_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->size - amount > 0) {
      return private_f_utf_string_dynamic_adjust(dynamic->size - amount, dynamic);
    }

    return private_f_utf_string_dynamic_adjust(0, dynamic);
  }
#endif // _di_f_utf_string_dynamic_decimate_by_

#ifndef _di_f_utf_string_dynamic_decrease_by_
  f_status_t f_utf_string_dynamic_decrease_by(const f_array_length_t amount, f_utf_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->size - amount > 0) {
      return private_f_utf_string_dynamic_resize(dynamic->size - amount, dynamic);
    }

    return private_f_utf_string_dynamic_resize(0, dynamic);
  }
#endif // _di_f_utf_string_dynamic_decrease_by_

#ifndef _di_f_utf_string_dynamic_increase_
  f_status_t f_utf_string_dynamic_increase(const uint16_t step, f_utf_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->used + 1 > dynamic->size) {
      f_array_length_t size = dynamic->used + step;

      if (size > F_string_t_size_d) {
        if (dynamic->used + 1 > F_string_t_size_d) {
          return F_status_set_error(F_string_too_large);
        }

        size = F_string_t_size_d;
      }

      return private_f_utf_string_dynamic_resize(size, dynamic);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_dynamic_increase_

#ifndef _di_f_utf_string_dynamic_increase_by_
  f_status_t f_utf_string_dynamic_increase_by(const f_array_length_t amount, f_utf_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamic_increase_by(amount, dynamic);
  }
#endif // _di_f_utf_string_dynamic_increase_by_

#ifndef _di_f_utf_string_dynamic_mash_
  f_status_t f_utf_string_dynamic_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mash_

#ifndef _di_f_utf_string_dynamic_mash_nulless_
  f_status_t f_utf_string_dynamic_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mash_nulless_

#ifndef _di_f_utf_string_dynamic_mish_
  f_status_t f_utf_string_dynamic_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mish_

#ifndef _di_f_utf_string_dynamic_mish_nulless_
  f_status_t f_utf_string_dynamic_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue_length && destination->used) {
      const f_status_t status = private_f_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_mish_nulless_

#ifndef _di_f_utf_string_dynamic_partial_append_
  f_status_t f_utf_string_dynamic_partial_append(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_append_

#ifndef _di_f_utf_string_dynamic_partial_append_assure_
  f_status_t f_utf_string_dynamic_partial_append_assure(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_append(source.string + range.start, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source.string[range.stop - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_partial_append_assure_

#ifndef _di_f_utf_string_dynamic_partial_append_assure_nulless_
  f_status_t f_utf_string_dynamic_partial_append_assure_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_append_nulless(source.string + range.start, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source.string[range.stop - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_f_utf_string_append_nulless(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

#ifndef _di_f_utf_string_dynamic_partial_append_nulless_
  f_status_t f_utf_string_dynamic_partial_append_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_append_nulless_

#ifndef _di_f_utf_string_dynamic_partial_mash_
  f_status_t f_utf_string_dynamic_partial_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mash_

#ifndef _di_f_utf_string_dynamic_partial_mash_nulless_
  f_status_t f_utf_string_dynamic_partial_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mash_nulless_

#ifndef _di_f_utf_string_dynamic_partial_mish_
  f_status_t f_utf_string_partial_dynamic_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mish_

#ifndef _di_f_utf_string_dynamic_partial_mish_nulless_
  f_status_t f_utf_string_dynamic_partial_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue_length && destination->used) {
      f_status_t status = private_f_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_mish_nulless_

#ifndef _di_f_utf_string_dynamic_partial_prepend_
  f_status_t f_utf_string_dynamic_partial_prepend(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_

#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_
  f_status_t f_utf_string_dynamic_partial_prepend_assure(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_prepend(source.string + range.start, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source.string[i + range.start]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_f_utf_string_prepend(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_

#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_nulless_
  f_status_t f_utf_string_dynamic_partial_prepend_assure_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_utf_string_prepend_nulless(source.string + range.start, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source.string[i + range.start]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_f_utf_string_prepend_nulless(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_nulless

#ifndef _di_f_utf_string_dynamic_partial_prepend_nulless_
  f_status_t f_utf_string_dynamic_partial_prepend_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_f_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_utf_string_dynamic_partial_prepend_nulless

#ifndef _di_f_utf_string_dynamic_prepend_
  f_status_t f_utf_string_dynamic_prepend(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_prepend_

#ifndef _di_f_utf_string_dynamic_prepend_assure_
  f_status_t f_utf_string_dynamic_prepend_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_f_utf_string_prepend(source.string, source.used, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < source.used && j < destination->used) {

      if (!source.string[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_f_utf_string_prepend(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_prepend_assure_

#ifndef _di_f_utf_string_dynamic_prepend_assure_nulless_
  f_status_t f_utf_string_dynamic_prepend_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (destination->used < source.used) {
      return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < source.used && j < destination->used) {

      if (!source.string[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_prepend_assure_nulless_

#ifndef _di_f_utf_string_dynamic_prepend_nulless_
  f_status_t f_utf_string_dynamic_prepend_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_utf_string_dynamic_prepend_nulless_

#ifndef _di_f_utf_string_dynamic_resize_
  f_status_t f_utf_string_dynamic_resize(const f_array_length_t length, f_utf_string_dynamic_t *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamic_resize(length, buffer);
  }
#endif // _di_f_utf_string_dynamic_resize_

#ifndef _di_f_utf_string_dynamic_seek_line_
  f_status_t f_utf_string_dynamic_seek_line(const f_utf_string_static_t buffer, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != F_utf_character_t_eol_d) {

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      ++range->start;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_seek_line_

#ifndef _di_f_utf_string_dynamic_seek_line_to_
  f_status_t f_utf_string_dynamic_seek_line_to(const f_utf_string_static_t buffer, const char seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != seek_to_this) {

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (buffer.string[range->start] == F_utf_character_t_eol_d) return F_none_eol;

      ++range->start;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_seek_line_to_

#ifndef _di_f_utf_string_dynamic_seek_to_
  f_status_t f_utf_string_dynamic_seek_to(const f_utf_string_static_t buffer, const char seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != seek_to_this) {

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      ++range->start;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_seek_to_

#ifndef _di_f_utf_string_dynamic_terminate_
  f_status_t f_utf_string_dynamic_terminate(f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!destination->used && destination->size && !destination->string[destination->used - 1]) {
      return F_none;
    }

    if (destination->used == F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    const f_array_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total;

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_terminate_

#ifndef _di_f_utf_string_dynamic_terminate_after_
  f_status_t f_utf_string_dynamic_terminate_after(f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used) {
      for (; destination->used; --destination->used) {

        if (!destination->string[destination->used - 1]) continue;
        break;
      } // for
    }

    if (destination->used == F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    const f_array_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total - 1;

    return F_none;
  }
#endif // _di_f_utf_string_dynamic_terminate_after_

#ifndef _di_f_utf_string_dynamics_adjust_
  f_status_t f_utf_string_dynamics_adjust(const f_array_length_t length, f_utf_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamics_adjust(length, dynamics);
  }
#endif // _di_f_utf_string_dynamics_adjust_

#ifndef _di_f_utf_string_dynamics_append_
  f_status_t f_utf_string_dynamics_append(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_dynamics_append(source, destination);
  }
#endif // _di_f_utf_string_dynamics_append_

#ifndef _di_f_utf_string_dynamics_decimate_by_
  f_status_t f_utf_string_dynamics_decimate_by(const f_array_length_t amount, f_utf_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->size - amount > 0) {
      return private_f_utf_string_dynamics_adjust(dynamics->size - amount, dynamics);
    }

    return private_f_utf_string_dynamics_adjust(0, dynamics);
  }
#endif // _di_f_utf_string_dynamics_decimate_by_

#ifndef _di_f_utf_string_dynamics_decrease_by_
  f_status_t f_utf_string_dynamics_decrease_by(const f_array_length_t amount, f_utf_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->size - amount > 0) {
      return private_f_utf_string_dynamics_resize(dynamics->size - amount, dynamics);
    }

    return private_f_utf_string_dynamics_resize(0, dynamics);
  }
#endif // _di_f_utf_string_dynamics_decrease_by_

#ifndef _di_f_utf_string_dynamics_increase_
  f_status_t f_utf_string_dynamics_increase(const uint16_t step, f_utf_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + 1 > dynamics->size) {
      f_array_length_t size = dynamics->used + step;

      if (size > F_array_length_t_size_d) {
        if (dynamics->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_utf_string_dynamics_resize(size, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_dynamics_increase_

#ifndef _di_f_utf_string_dynamics_increase_by_
  f_status_t f_utf_string_dynamics_increase_by(const f_array_length_t amount, f_utf_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + amount > dynamics->size) {
      if (dynamics->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_utf_string_dynamics_resize(dynamics->used + amount, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_dynamics_increase_by_

#ifndef _di_f_utf_string_dynamics_resize_
  f_status_t f_utf_string_dynamics_resize(const f_array_length_t length, f_utf_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamics_resize(length, dynamics);
  }
#endif // _di_f_utf_string_dynamics_resize_

#ifdef __cplusplus
} // extern "C"
#endif

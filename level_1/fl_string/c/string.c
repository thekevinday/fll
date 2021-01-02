#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_string_append_
  f_return_status fl_string_append(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_fl_string_append(source, length, destination);
  }
#endif // _di_fl_string_append_

#ifndef _di_fl_string_append_assure_
  f_return_status fl_string_append_assure(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_fl_string_append(source, length, destination);

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source[length - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_fl_string_append(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_append_assure_

#ifndef _di_fl_string_append_assure_nulless_
  f_return_status fl_string_append_assure_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    if (destination->used < length) {
      return private_fl_string_append_nulless(source, length, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source[length - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_fl_string_append_nulless(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_append_assure_nulless_

#ifndef _di_fl_string_append_nulless_
  f_return_status fl_string_append_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_fl_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_string_append_nulless_

#ifndef _di_fl_string_compare_
  f_return_status fl_string_compare(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2) {
    return private_fl_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_

#ifndef _di_fl_string_compare_except_
  f_return_status fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    return private_fl_string_compare_except(string1, string2, 0, 0, length1, length2, except1, except2);
  }
#endif // _di_fl_string_compare_except_

#ifndef _di_fl_string_compare_except_trim_
  f_return_status fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    return private_fl_string_compare_except_trim(string1, string2, 0, 0, length1, length2, except1, except2);
  }
#endif // _di_fl_string_compare_except_trim_

#ifndef _di_fl_string_compare_trim_
  f_return_status fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2) {
    return private_fl_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_trim_

#ifndef _di_fl_string_dynamic_append_
  f_return_status fl_string_dynamic_append(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_fl_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_append_

#ifndef _di_fl_string_dynamic_append_assure_
  f_return_status fl_string_dynamic_append_assure(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_string_append(source.string, source.used, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= source.used && j <= destination->used) {
      if (!source.string[source.used - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_fl_string_append(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_append_assure_

#ifndef _di_fl_string_dynamic_append_assure_nulless_
  f_return_status fl_string_dynamic_append_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_string_append_nulless(source.string, source.used, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= source.used && j <= destination->used) {
      if (!source.string[source.used - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_fl_string_append_nulless(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_append_assure_nulless_

#ifndef _di_fl_string_dynamic_append_nulless_
  f_return_status fl_string_dynamic_append_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_fl_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_append_nulless_

#ifndef _di_fl_string_dynamic_compare_
  f_return_status fl_string_dynamic_compare(const f_string_static_t string1, const f_string_static_t string2) {
    return private_fl_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_

#ifndef _di_fl_string_dynamic_compare_except_
  f_return_status fl_string_dynamic_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    return private_fl_string_compare_except(string1.string, string2.string, 0, 0, string1.used, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_

#ifndef _di_fl_string_dynamic_compare_except_string_
  f_return_status fl_string_dynamic_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    return private_fl_string_compare_except(string1, string2.string, 0, 0, length1, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_string_

#ifndef _di_fl_string_dynamic_compare_except_trim_
  f_return_status fl_string_dynamic_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    return private_fl_string_compare_except_trim(string1.string, string2.string, 0, 0, string1.used, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_trim_

#ifndef _di_fl_string_dynamic_compare_except_trim_string_
  f_return_status fl_string_dynamic_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    return private_fl_string_compare_except_trim(string1, string2.string, 0, 0, length1, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_trim_string_

#ifndef _di_fl_string_dynamic_compare_string_
  f_return_status fl_string_dynamic_compare_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1) {
    return private_fl_string_compare(string1, string2.string, 0, 0, length1, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_string_

#ifndef _di_fl_string_dynamic_compare_trim_
  f_return_status fl_string_dynamic_compare_trim(const f_string_static_t string1, const f_string_static_t string2) {
    return private_fl_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_trim_

#ifndef _di_fl_string_dynamic_compare_trim_string_
  f_return_status fl_string_dynamic_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1) {
    return private_fl_string_compare_trim(string1, string2.string, 0, 0, length1, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_trim_string_

#ifndef _di_fl_string_dynamic_decrease_
  f_return_status fl_string_dynamic_decrease(f_string_dynamic_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (string->size > 1) {
      return private_fl_string_dynamic_resize(string->size - 1, string);
    }

    private_fl_string_dynamic_delete(string);

    return F_none;
  }
#endif // _di_fl_string_dynamic_decrease_

#ifndef _di_fl_string_dynamic_decrease_by_
  f_return_status fl_string_dynamic_decrease_by(const f_string_length_t amount, f_string_dynamic_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (string->size - amount > 0) {
      return private_fl_string_dynamic_resize(string->size - amount, string);
    }

    private_fl_string_dynamic_delete(string);

    return F_none;
  }
#endif // _di_fl_string_dynamic_decrease_by_

#ifndef _di_fl_string_dynamic_delete_
  f_return_status fl_string_dynamic_delete(f_string_dynamic_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_string_dynamic_delete(string);

    return F_none;
  }
#endif // _di_fl_string_dynamic_delete_

#ifndef _di_fl_string_dynamic_mash_
  f_return_status fl_string_dynamic_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_fl_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mash_

#ifndef _di_fl_string_dynamic_mash_nulless_
  f_return_status fl_string_dynamic_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_fl_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mash_nulless_

#ifndef _di_fl_string_dynamic_mish_
  f_return_status fl_string_dynamic_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_fl_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mish_

#ifndef _di_fl_string_dynamic_mish_nulless_
  f_return_status fl_string_dynamic_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (glue_length && destination->used) {
      const f_status_t status = private_fl_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mish_nulless_

#ifndef _di_fl_string_dynamic_partial_append_
  f_return_status fl_string_dynamic_partial_append(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_append_

#ifndef _di_fl_string_dynamic_partial_append_assure_
  f_return_status fl_string_dynamic_partial_append_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_append(source.string + range.start, length, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source.string[range.stop - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_fl_string_append(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while
  }
#endif // _di_fl_string_dynamic_partial_append_assure_

#ifndef _di_fl_string_dynamic_partial_append_assure_nulless_
  f_return_status fl_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_append_nulless(source.string + range.start, length, destination);
    }

    f_string_length_t i = 1;
    f_string_length_t j = 1;

    while (i <= length && j <= destination->used) {
      if (!source.string[range.stop - i]) {
        i++;
        continue;
      }

      if (!destination->string[destination->used - j]) {
        j++;
        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_fl_string_append_nulless(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while
  }
#endif // _di_fl_string_dynamic_append_assure_nulless_

#ifndef _di_fl_string_dynamic_partial_append_nulless_
  f_return_status fl_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_append_nulless_

#ifndef _di_fl_string_dynamic_partial_compare_
  f_return_status fl_string_dynamic_partial_compare(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifndef _di_fl_string_dynamic_partial_compare_dynamic_
  f_return_status fl_string_dynamic_partial_compare_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_string_
  f_return_status fl_string_dynamic_partial_compare_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1, string2.string, 0, range2.start, length1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_string_

#ifndef _di_fl_string_dynamic_partial_compare_except_
  f_return_status fl_string_dynamic_partial_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_

#ifndef _di_fl_string_dynamic_partial_compare_except_dynamic_
  f_return_status fl_string_dynamic_partial_compare_except_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_except_string_
  f_return_status fl_string_dynamic_partial_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except(string1, string2.string, 0, range2.start, length1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_string_

#ifndef _di_fl_string_dynamic_partial_compare_except_trim_
  f_return_status fl_string_dynamic_partial_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_trim_

#ifndef _di_fl_string_dynamic_partial_compare_except_trim_dynamic_
  f_return_status fl_string_dynamic_partial_compare_except_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except_trim(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_trim_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_except_trim_string_
  f_return_status fl_string_dynamic_partial_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except_trim(string1, string2.string, 0, range2.start, length1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_trim_string_

#ifndef _di_fl_string_dynamic_partial_compare_trim_
  f_return_status fl_string_dynamic_partial_compare_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_

#ifndef _di_fl_string_dynamic_partial_compare_trim_dynamic_
  f_return_status fl_string_dynamic_partial_compare_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_trim_string_
  f_return_status fl_string_dynamic_partial_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1, string2.string, 0, range2.start, length1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_string_

#ifndef _di_fl_string_dynamic_partial_mash_
  f_return_status fl_string_dynamic_partial_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mash_

#ifndef _di_fl_string_dynamic_partial_mash_nulless_
  f_return_status fl_string_dynamic_partial_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mash_nulless_

#ifndef _di_fl_string_dynamic_partial_mish_
  f_return_status fl_string_partial_dynamic_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mish_

#ifndef _di_fl_string_dynamic_partial_mish_nulless_
  f_return_status fl_string_dynamic_partial_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mish_nulless_

#ifndef _di_fl_string_dynamic_partial_prepend_
  f_return_status fl_string_dynamic_partial_prepend(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_prepend_

#ifndef _di_fl_string_dynamic_partial_prepend_assure_
  f_return_status fl_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_prepend(source.string + range.start, length, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source.string[i + range.start]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_fl_string_prepend(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_partial_prepend_assure_

#ifndef _di_fl_string_dynamic_partial_prepend_assure_nulless_
  f_return_status fl_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_string_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_prepend_nulless(source.string + range.start, length, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source.string[i + range.start]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_fl_string_prepend_nulless(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_partial_prepend_assure_nulless

#ifndef _di_fl_string_dynamic_partial_prepend_nulless_
  f_return_status fl_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_prepend_nulless

#ifndef _di_fl_string_dynamic_prepend_
  f_return_status fl_string_dynamic_prepend(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_fl_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_prepend_

#ifndef _di_fl_string_dynamic_prepend_assure_
  f_return_status fl_string_dynamic_prepend_assure(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_string_prepend(source.string, source.used, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < source.used && j < destination->used) {
      if (!source.string[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_fl_string_prepend(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_prepend_assure_

#ifndef _di_fl_string_dynamic_prepend_assure_nulless_
  f_return_status fl_string_dynamic_prepend_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_string_prepend_nulless(source.string, source.used, destination);
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < source.used && j < destination->used) {
      if (!source.string[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_fl_string_prepend_nulless(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_prepend_assure_nulless_

#ifndef _di_fl_string_dynamic_prepend_nulless_
  f_return_status fl_string_dynamic_prepend_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_fl_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_prepend_nulless_

#ifndef _di_fl_string_dynamic_rip_
  f_return_status fl_string_dynamic_rip(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    f_string_length_t begin = range.start;
    f_string_length_t end = range.stop;

    const f_status_t status = private_fl_string_rip_find_range(source.string, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_string_append(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_dynamic_rip_

#ifndef _di_fl_string_dynamic_rip_nulless_
  f_return_status fl_string_dynamic_rip_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    f_string_length_t begin = range.start;
    f_string_length_t end = range.stop;

    const f_status_t status = private_fl_string_rip_find_range(source.string, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_string_append_nulless(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_dynamic_rip_nulless_

#ifndef _di_fl_string_dynamic_increase_
  f_return_status fl_string_dynamic_increase(f_string_dynamic_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (string->used + 1 > string->size) {
      f_array_length_t size = string->used + f_memory_default_allocation_step;

      if (size > f_string_length_t_size) {
        if (string->used + 1 > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        size = f_string_length_t_size;
      }

      return private_fl_string_dynamic_resize(size, string);
    }

    return F_none;
  }
#endif // _di_fl_string_dynamic_increase_

#ifndef _di_fl_string_dynamic_increase_by_
  f_return_status fl_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_dynamic_increase_by(amount, string);
  }
#endif // _di_fl_string_dynamic_increase_by_

#ifndef _di_fl_string_dynamic_seek_line_
  f_return_status fl_string_dynamic_seek_line(const f_string_t string, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    while (string[range->start] != f_string_eol_s[0]) {
      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_

#ifndef _di_fl_string_dynamic_seek_line_to_
  f_return_status fl_string_dynamic_seek_line_to(const f_string_t string, const int8_t seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    while (string[range->start] != seek_to_this) {

      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_to_

#ifndef _di_fl_string_dynamic_seek_line_to_utf_character_
  f_return_status fl_string_dynamic_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = f_macro_utf_character_t_width(seek_to_this);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_string_length_t width_max = 0;

    while (range->start <= range->stop) {
      width_max = (range->stop - range->start) + 1;
      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;

        if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

        if (seek_width == width) {
          if (string[range->start] == seek_to_this) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);

        if (width == seek_width) {
          f_utf_character_t character = 0;

          status = f_utf_char_to_character(string + range->start, width_max, &character);

          if (F_status_is_error(status)) return status;
          if (character == seek_to_this) return F_none;
        }
      }

      range->start += width;

      if (range->start >= range->stop) return F_none_stop;
    } // while

    return F_none_eos;
  }
#endif // _di_fl_string_dynamic_seek_line_to_utf_character_

#ifndef _di_fl_string_dynamic_seek_line_until_graph_
  f_return_status fl_string_dynamic_seek_line_until_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_string_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_graph(string + range->start, width_max)) == F_false) {

      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
      }

      range->start += width;

      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_until_graph_

#ifndef _di_fl_string_dynamic_seek_line_until_non_graph_
  f_return_status fl_string_dynamic_seek_line_until_non_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_string_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_whitespace(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
      }

      range->start += width;

      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_until_non_graph_

#ifndef _di_fl_string_dynamic_seek_to_
  f_return_status fl_string_dynamic_seek_to(const f_string_t string, const int8_t seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    while (string[range->start] != seek_to_this) {
      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_to_

#ifndef _di_fl_string_dynamic_seek_to_utf_character_
  f_return_status fl_string_dynamic_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = f_macro_utf_character_t_width(seek_to_this);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_string_length_t width_max = 0;

    while (range->start <= range->stop) {
      width_max = (range->stop - range->start) + 1;
      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;

        if (seek_width == width) {
          if (string[range->start] == seek_to_this) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);

        if (width == seek_width) {
          f_utf_character_t character = 0;
          status = f_utf_char_to_character(string + range->start, width_max, &character);

          if (F_status_is_error(status)) return status;
          if (character == seek_to_this) return F_none;
        }
      }

      range->start += width;

      if (range->start >= range->stop) return F_none_stop;
    } // while

    return F_none_eos;
  }
#endif // _di_fl_string_dynamic_seek_to_utf_character_

#ifndef _di_fl_string_dynamic_terminate_
  f_return_status fl_string_dynamic_terminate(f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!destination->used && destination->size && !destination->string[destination->used - 1]) {
      return F_none;
    }

    if (destination->used == f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    const f_string_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_fl_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total;

    return F_none;
  }
#endif // _di_fl_string_dynamic_terminate_

#ifndef _di_fl_string_dynamic_terminate_after_
  f_return_status fl_string_dynamic_terminate_after(f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (destination->used) {
      for (; destination->used; destination->used--) {
        if (!destination->string[destination->used - 1]) continue;
        break;
      } // for
    }

    if (destination->used == f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    const f_string_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_fl_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total - 1;

    return F_none;
  }
#endif // _di_fl_string_dynamic_terminate_after_

#ifndef _di_fl_string_dynamics_decrease_
  f_return_status fl_string_dynamics_decrease(f_string_dynamics_t *strings) {
    #ifndef _di_level_1_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (strings->size > 1) {
      return private_fl_string_dynamics_resize(strings->size - 1, strings);
    }

    private_fl_string_dynamics_delete(strings);

    return F_none;
  }
#endif // _di_fl_string_dynamics_decrease_

#ifndef _di_fl_string_dynamics_decrease_by_
  f_return_status fl_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t *strings) {
    #ifndef _di_level_1_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (strings->size - amount > 0) {
      return private_fl_string_dynamics_resize(strings->size - amount, strings);
    }

    private_fl_string_dynamics_delete(strings);

    return F_none;
  }
#endif // _di_fl_string_dynamics_decrease_by_

#ifndef _di_fl_string_dynamics_delete_
  f_return_status fl_string_dynamics_delete(f_string_dynamics_t *strings) {
    #ifndef _di_level_1_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_string_dynamics_delete(strings);

    return F_none;
  }
#endif // _di_fl_string_dynamics_delete_

#ifndef _di_fl_string_dynamics_increase_
  f_return_status fl_string_dynamics_increase(f_string_dynamics_t *strings) {
    #ifndef _di_level_1_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (strings->used + 1 > strings->size) {
      f_array_length_t size = strings->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (strings->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_fl_string_dynamics_resize(size, strings);
    }

    return F_none;
  }
#endif // _di_fl_string_dynamics_increase_

#ifndef _di_fl_string_dynamics_increase_by_
  f_return_status fl_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t *strings) {
    #ifndef _di_level_1_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (strings->used + amount > strings->size) {
      if (strings->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_fl_string_dynamics_resize(strings->used + amount, strings);
    }

    return F_none;
  }
#endif // _di_fl_string_dynamics_increase_by_

#ifndef _di_fl_string_lengths_decrease_
  f_return_status fl_string_lengths_decrease(f_string_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (lengths->size > 1) {
      return private_fl_string_lengths_resize(lengths->size - 1, lengths);
    }

    private_fl_string_lengths_delete(lengths);

    return F_none;
  }
#endif // _di_fl_string_lengths_decrease_

#ifndef _di_fl_string_lengths_decrease_by_
  f_return_status fl_string_lengths_decrease_by(const f_array_length_t amount, f_string_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (lengths->size - amount > 0) {
      return private_fl_string_lengths_resize(lengths->size - amount, lengths);
    }

    private_fl_string_lengths_delete(lengths);

    return F_none;
  }
#endif // _di_fl_string_lengths_decrease_by_

#ifndef _di_fl_string_lengths_delete_
  f_return_status fl_string_lengths_delete(f_string_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_string_lengths_delete(lengths);

    return F_none;
  }
#endif // _di_fl_string_lengths_delete_

#ifndef _di_fl_string_lengths_increase_
  f_return_status fl_string_lengths_increase(f_string_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (lengths->used + 1 > lengths->size) {
      f_array_length_t size = lengths->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (lengths->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_fl_string_lengths_resize(size, lengths);
    }

    return F_none;
  }
#endif // _di_fl_string_lengths_increase_

#ifndef _di_fl_string_lengths_increase_by_
  f_return_status fl_string_lengths_increase_by(const f_array_length_t amount, f_string_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (lengths->used + amount > lengths->size) {
      if (lengths->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_fl_string_lengths_resize(lengths->used + amount, lengths);
    }

    return F_none;
  }
#endif // _di_fl_string_lengths_increase_by_

#ifndef _di_fl_string_maps_decrease_
  f_return_status fl_string_maps_decrease(f_string_maps_t *maps) {
    #ifndef _di_level_1_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (maps->size > 1) {
      return private_fl_string_maps_resize(maps->size - 1, maps);
    }

    private_fl_string_maps_delete(maps);

    return F_none;
  }
#endif // _di_fl_string_maps_decrease_

#ifndef _di_fl_string_maps_decrease_by_
  f_return_status fl_string_maps_decrease_by(const f_array_length_t amount, f_string_maps_t *maps) {
    #ifndef _di_level_1_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (maps->size - amount > 0) {
      return private_fl_string_maps_resize(maps->size - amount, maps);
    }

    private_fl_string_maps_delete(maps);

    return F_none;
  }
#endif // _di_fl_string_maps_decrease_by_

#ifndef _di_fl_string_maps_delete_
  f_return_status fl_string_maps_delete(f_string_maps_t *maps) {
    #ifndef _di_level_1_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_string_maps_delete(maps);

    return F_none;
  }
#endif // _di_fl_string_maps_delete_

#ifndef _di_fl_string_maps_increase_
  f_return_status fl_string_maps_increase(f_string_maps_t *maps) {
    #ifndef _di_level_1_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (maps->used + 1 > maps->size) {
      f_array_length_t size = maps->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (maps->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_fl_string_maps_resize(size, maps);
    }

    return F_none;
  }
#endif // _di_fl_string_maps_increase_

#ifndef _di_fl_string_maps_increase_by_
  f_return_status fl_string_maps_increase_by(const f_array_length_t amount, f_string_maps_t *maps) {
    #ifndef _di_level_1_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (maps->used + amount > maps->size) {
      if (maps->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_fl_string_maps_resize(maps->used + amount, maps);
    }

    return F_none;
  }
#endif // _di_fl_string_maps_increase_by_

#ifndef _di_fl_string_mash_
  f_return_status fl_string_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append(source, length, destination);
  }
#endif // _di_fl_string_mash_

#ifndef _di_fl_string_mash_nulless_
  f_return_status fl_string_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_string_mash_nulless_

#ifndef _di_fl_string_mish_
  f_return_status fl_string_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend(source, length, destination);
  }
#endif // _di_fl_string_mish_

#ifndef _di_fl_string_mish_nulless_
  f_return_status fl_string_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    if (glue_length && destination->used) {
      f_status_t status = private_fl_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_string_mish_nulless_

#ifndef _di_fl_string_prepend_
  f_return_status fl_string_prepend(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_fl_string_prepend(source, length, destination);
  }
#endif // _di_fl_string_prepend_

#ifndef _di_fl_string_prepend_assure_
  f_return_status fl_string_prepend_assure(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_fl_string_prepend(source, length, destination);

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) return private_fl_string_prepend(source, length, destination);

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_prepend_assure_

#ifndef _di_fl_string_prepend_assure_nulless_
  f_return_status fl_string_prepend_assure_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;
    if (destination->used < length) return private_fl_string_prepend_nulless(source, length, destination);

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    while (i < length && j < destination->used) {
      if (!source[i]) {
        i++;
        continue;
      }

      if (!destination->string[j]) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) return private_fl_string_prepend_nulless(source, length, destination);

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_prepend_assure_nulless_

#ifndef _di_fl_string_prepend_nulless_
  f_return_status fl_string_prepend_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    return private_fl_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_string_prepend_nulless_

#ifndef _di_fl_string_rip_
  f_return_status fl_string_rip(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    f_string_length_t begin = 0;
    f_string_length_t end = length - 1;

    const f_status_t status = private_fl_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return private_fl_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_rip_

#ifndef _di_fl_string_rip_nulless_
  f_return_status fl_string_rip_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    f_string_length_t begin = 0;
    f_string_length_t end = length - 1;

    const f_status_t status = private_fl_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return private_fl_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_rip_nulless_

#ifndef _di_fl_string_seek_line_to_
  f_return_status fl_string_seek_line_to(const f_string_t string, const int8_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    while (string[range->start] != seek_to) {
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_seek_line_to_

#ifndef _di_fl_string_seek_line_to_utf_character_
  f_return_status fl_string_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = f_macro_utf_character_t_width(seek_to);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_string_length_t width_max = (range->stop - range->start) + 1;

    for (; range->start <= range->stop; range->start += width) {
      width_max = (range->stop - range->start) + 1;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;

        if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

        if (seek_width == width) {
          if (string[range->start] == seek_to) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_eos);

        if (width == seek_width) {
          f_utf_character_t character = 0;
          status = f_utf_char_to_character(string + range->start, width_max, &character);

          if (F_status_is_error(status)) return status;
          if (character == seek_to) return F_none;
        }
      }
    } // for

    return F_none_stop;
  }
#endif // _di_fl_string_seek_line_to_utf_character_

#ifndef _di_fl_string_seek_line_until_graph_
  f_return_status fl_string_seek_line_until_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_string_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_graph(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
      }

      range->start += width;

      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_string_seek_line_until_graph_

#ifndef _di_fl_string_seek_line_until_non_graph_
  f_return_status fl_string_seek_line_until_non_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_string_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_whitespace(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
      }

      range->start += width;

      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_string_seek_line_until_non_graph_

#ifndef _di_fl_string_seek_to_
  f_return_status fl_string_seek_to(const f_string_t string, const int8_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    while (string[range->start] != seek_to) {
      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_seek_to_

#ifndef _di_fl_string_seek_to_utf_character_
  f_return_status fl_string_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = f_macro_utf_character_t_width(seek_to);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_string_length_t width_max = 0;

    for (; range->start <= range->stop; range->start += width) {
      width_max = (range->stop - range->start) + 1;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;

        if (seek_width == width) {
          if (string[range->start] == seek_to) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);

        if (width == seek_width) {
          f_utf_character_t character = 0;
          status = f_utf_char_to_character(string + range->start, width_max, &character);

          if (F_status_is_error(status)) return status;
          if (character == seek_to) return F_none;
        }
      }
    } // for

    return F_none_stop;
  }
#endif // _di_fl_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

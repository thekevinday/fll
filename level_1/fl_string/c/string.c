#include <level_1/string.h>
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_string_append_
  f_return_status fl_string_append(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    return private_fl_string_append(source, length, destination);
  }
#endif // _di_fl_string_append_

#ifndef _di_fl_string_append_assure_
  f_return_status fl_string_append_assure(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (destination->used < length) {
      return private_fl_string_append(source, length, destination);
    }

    f_string_length i = 1;
    f_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source[length - i] == 0) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == 0) {
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
  f_return_status fl_string_append_assure_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (destination->used < length) {
      return private_fl_string_append_nulless(source, length, destination);
    }

    f_string_length i = 1;
    f_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source[length - i] == 0) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == 0) {
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
  f_return_status fl_string_append_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    return private_fl_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_string_append_nulless_

#ifndef _di_fl_string_compare_
  f_return_status fl_string_compare(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2) {
    return private_fl_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_

#ifndef _di_fl_string_compare_trim_
  f_return_status fl_string_compare_trim(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2) {
    return private_fl_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_trim_

#ifndef _di_fl_string_dynamic_compare_
  f_return_status fl_string_dynamic_compare(const f_string_static string1, const f_string_static string2) {
    return private_fl_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_

#ifndef _di_fl_string_dynamic_compare_trim_
  f_return_status fl_string_dynamic_compare_trim(const f_string_static string1, const f_string_static string2) {
    return private_fl_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_trim_

#ifndef _di_fl_string_dynamic_append_
  f_return_status fl_string_dynamic_append(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    return private_fl_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_append_

#ifndef _di_fl_string_dynamic_append_assure_
  f_return_status fl_string_dynamic_append_assure(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (destination->used < source.used) {
      return private_fl_string_append(source.string, source.used, destination);
    }

    f_string_length i = 1;
    f_string_length j = 1;

    while (i <= source.used && j <= destination->used) {
      if (source.string[source.used - i] == 0) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == 0) {
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
  f_return_status fl_string_dynamic_append_assure_nulless(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (destination->used < source.used) {
      return private_fl_string_append_nulless(source.string, source.used, destination);
    }

    f_string_length i = 1;
    f_string_length j = 1;

    while (i <= source.used && j <= destination->used) {
      if (source.string[source.used - i] == 0) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == 0) {
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
  f_return_status fl_string_dynamic_append_nulless(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    return private_fl_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_append_nulless_

#ifndef _di_fl_string_dynamic_mash_
  f_return_status fl_string_dynamic_mash(const f_string glue, const f_string_length glue_length, const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_append(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mash_

#ifndef _di_fl_string_dynamic_mash_nulless_
  f_return_status fl_string_dynamic_mash_nulless(const f_string glue, const f_string_length glue_length, const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_append_nulless(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mash_nulless_

#ifndef _di_fl_string_dynamic_mish_
  f_return_status fl_string_dynamic_mish(const f_string glue, const f_string_length glue_length, const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_prepend(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mish_

#ifndef _di_fl_string_dynamic_mish_nulless_
  f_return_status fl_string_dynamic_mish_nulless(const f_string glue, const f_string_length glue_length, const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_prepend_nulless(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_mish_nulless_

#ifndef _di_fl_string_dynamic_partial_append_
  f_return_status fl_string_dynamic_partial_append(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    return private_fl_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_append_

#ifndef _di_fl_string_dynamic_partial_append_assure_
  f_return_status fl_string_dynamic_partial_append_assure(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    f_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_append(source.string + range.start, length, destination);
    }

    f_string_length i = 1;
    f_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source.string[range.stop - i] == 0) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == 0) {
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
  f_return_status fl_string_dynamic_partial_append_assure_nulless(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    f_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_append_nulless(source.string + range.start, length, destination);
    }

    f_string_length i = 1;
    f_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source.string[range.stop - i] == 0) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == 0) {
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
  f_return_status fl_string_dynamic_partial_append_nulless(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    return private_fl_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_append_nulless_

#ifndef _di_fl_string_dynamic_partial_compare_
  f_return_status fl_string_dynamic_partial_compare(const f_string_static string1, const f_string_static string2, const f_string_range range1, const f_string_range range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifndef _di_fl_string_dynamic_partial_compare_trim_
  f_return_status fl_string_dynamic_partial_compare_trim(const f_string_static string1, const f_string_static string2, const f_string_range range1, const f_string_range range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_

#ifndef _di_fl_string_dynamic_partial_mash_
  f_return_status fl_string_dynamic_partial_mash(const f_string glue, const f_string_length glue_length, const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_append(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mash_

#ifndef _di_fl_string_dynamic_partial_mash_nulless_
  f_return_status fl_string_dynamic_partial_mash_nulless(const f_string glue, const f_string_length glue_length, const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_append_nulless(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mash_nulless_

#ifndef _di_fl_string_dynamic_partial_mish_
  f_return_status fl_string_partial_dynamic_mish(const f_string glue, const f_string_length glue_length, const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_prepend(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mish_

#ifndef _di_fl_string_dynamic_partial_mish_nulless_
  f_return_status fl_string_dynamic_partial_mish_nulless(const f_string glue, const f_string_length glue_length, const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_prepend_nulless(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_mish_nulless_

#ifndef _di_fl_string_dynamic_partial_prepend_
  f_return_status fl_string_dynamic_partial_prepend(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    f_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_prepend(source.string + range.start, length, destination);
    }

    f_string_length i = 0;
    f_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source.string[i + range.start] == 0) {
        i++;
        continue;
      }

      if (destination->string[j] == 0) {
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
#endif // _di_fl_string_dynamic_partial_prepend_

#ifndef _di_fl_string_dynamic_partial_prepend_assure_
  f_return_status fl_string_dynamic_partial_prepend_assure(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    f_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_string_prepend_nulless(source.string + range.start, length, destination);
    }

    f_string_length i = 0;
    f_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source.string[i + range.start] == 0) {
        i++;
        continue;
      }

      if (destination->string[j] == 0) {
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
#endif // _di_fl_string_dynamic_partial_prepend_assure_

#ifndef _di_fl_string_dynamic_partial_prepend_assure_nulless_
  f_return_status fl_string_dynamic_partial_prepend_assure_nulless(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    return private_fl_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_prepend_assure_nulless

#ifndef _di_fl_string_dynamic_partial_prepend_nulless_
  f_return_status fl_string_dynamic_partial_prepend_nulless(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    return private_fl_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_partial_prepend_nulless

#ifndef _di_fl_string_dynamic_prepend_
  f_return_status fl_string_dynamic_prepend(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    return private_fl_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_prepend_

#ifndef _di_fl_string_dynamic_prepend_assure_
  f_return_status fl_string_dynamic_prepend_assure(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (destination->used < source.used) {
      return private_fl_string_prepend(source.string, source.used, destination);
    }

    f_string_length i = 0;
    f_string_length j = 0;

    while (i < source.used && j < destination->used) {
      if (source.string[i] == 0) {
        i++;
        continue;
      }

      if (destination->string[j] == 0) {
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
  f_return_status fl_string_dynamic_prepend_assure_nulless(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    if (destination->used < source.used) {
      return private_fl_string_prepend_nulless(source.string, source.used, destination);
    }

    f_string_length i = 0;
    f_string_length j = 0;

    while (i < source.used && j < destination->used) {
      if (source.string[i] == 0) {
        i++;
        continue;
      }

      if (destination->string[j] == 0) {
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
  f_return_status fl_string_dynamic_prepend_nulless(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;

    return private_fl_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_string_dynamic_prepend_nulless_

#ifndef _di_fl_string_dynamic_rip_
  f_return_status fl_string_dynamic_rip(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    return private_fl_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_rip_

#ifndef _di_fl_string_dynamic_rip_nulless_
  f_return_status fl_string_dynamic_rip_nulless(const f_string_static source, const f_string_range range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not;
    if (range.start > range.stop) return F_data_not;

    return private_fl_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_string_dynamic_rip_nulless_

#ifndef _di_fl_string_dynamic_seek_line_to_
  f_return_status fl_string_dynamic_seek_line_to(const f_string_static buffer, f_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_none_eos;
    if (range->start > range->stop) return F_none_stop;

    while (buffer.string[range->start] != seek_to_this) {
      if (buffer.string[range->start] == f_string_eol[0]) return F_none_eol;

      range->start++;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_to_

#ifndef _di_fl_string_dynamic_seek_line_to_utf_character_
  f_return_status fl_string_dynamic_seek_line_to_utf_character(const f_string_static buffer, f_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_none_eos;
    if (range->start > range->stop) return F_none_stop;

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = F_none;

    unsigned short width = 0;

    f_string_length width_max = 0;

    while (range->start < buffer.used) {
      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }

      width = f_macro_utf_byte_width_is(buffer.string[range->start]);

      if (width == 0) {
        width = 1;

        if (buffer.string[range->start] == f_string_eol[0]) return F_none_eol;

        if (seek_width == width) {
          if (buffer.string[range->start] == seek_to_this) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width >= buffer.used) return F_status_set_error(F_incomplete_utf_eos);
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(buffer.string + range->start, width_max, &character);

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
  f_return_status fl_string_dynamic_seek_line_until_graph(const f_string_static buffer, f_string_range *range, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_none_eos;
    if (range->start > range->stop) return F_none_stop;

    f_status status = F_none;
    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    if (width_max > buffer.used - range->start) {
      width_max = buffer.used - range->start;
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_is_graph(buffer.string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_string_eol[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(buffer.string[range->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width >= buffer.used) return F_status_set_error(F_incomplete_utf_eos);
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);
      }

      range->start += width;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_until_graph_

#ifndef _di_fl_string_dynamic_seek_line_until_non_graph_
  f_return_status fl_string_dynamic_seek_line_until_non_graph(const f_string_static buffer, f_string_range *range, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_none_eos;
    if (range->start > range->stop) return F_none_stop;

    f_status status = F_none;
    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    if (width_max > buffer.used - range->start) {
      width_max = buffer.used - range->start;
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_is_whitespace(buffer.string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_string_eol[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(buffer.string[range->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width >= buffer.used) return F_status_set_error(F_incomplete_utf_eos);
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);
      }

      range->start += width;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_line_until_non_graph_

#ifndef _di_fl_string_dynamic_seek_to_
  f_return_status fl_string_dynamic_seek_to(const f_string_static buffer, f_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_none_eos;
    if (range->start > range->stop) return F_none_stop;

    while (buffer.string[range->start] != seek_to_this) {
      range->start++;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_dynamic_seek_to_

#ifndef _di_fl_string_dynamic_seek_to_utf_character_
  f_return_status fl_string_dynamic_seek_to_utf_character(const f_string_static buffer, f_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_none_eos;
    if (range->start > range->stop) return F_none_stop;

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = F_none;

    unsigned short width = 0;

    f_string_length width_max = 0;

    while (range->start < buffer.used) {
      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }

      width = f_macro_utf_byte_width_is(buffer.string[range->start]);

      if (width == 0) {
        width = 1;

        if (seek_width == width) {
          if (buffer.string[range->start] == seek_to_this) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width >= buffer.used) return F_status_set_error(F_incomplete_utf_eos);
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(buffer.string + range->start, width_max, &character);

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
  f_return_status fl_string_dynamic_terminate(f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (destination->used > 0 && destination->string[destination->used - 1] == 0) return F_none;

    if (destination->used + 1 > f_string_length_size) return F_status_set_error(F_string_too_large);

    const f_string_length total = destination->used + 1;

    if (total > destination->size) {
      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total;

    return F_none;
  }
#endif // _di_fl_string_dynamic_terminate_

#ifndef _di_fl_string_dynamic_terminate_after_
  f_return_status fl_string_dynamic_terminate_after(f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (destination->used > 0) {
      for (; destination->used > 0; destination->used--) {
        if (destination->string[destination->used - 1] == 0) continue;
        break;
      } // for
    }

    if (destination->used + 1 > f_string_length_size) return F_status_set_error(F_string_too_large);

    const f_string_length total = destination->used + 1;

    if (total > destination->size) {
      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total - 1;

    return F_none;
  }
#endif // _di_fl_string_dynamic_terminate_after_

#ifndef _di_fl_string_mash_
  f_return_status fl_string_mash(const f_string glue, const f_string_length glue_length, const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_append(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append(source, length, destination);
  }
#endif // _di_fl_string_mash_

#ifndef _di_fl_string_mash_nulless_
  f_return_status fl_string_mash_nulless(const f_string glue, const f_string_length glue_length, const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_append_nulless(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_string_mash_nulless_

#ifndef _di_fl_string_mish_
  f_return_status fl_string_mish(const f_string glue, const f_string_length glue_length, const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_prepend(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend(source, length, destination);
  }
#endif // _di_fl_string_mish_

#ifndef _di_fl_string_mish_nulless_
  f_return_status fl_string_mish_nulless(const f_string glue, const f_string_length glue_length, const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_string_prepend_nulless(glue, glue_length, destination);

      if (F_status_is_error(status)) return status;
    }

    return private_fl_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_string_mish_nulless_

#ifndef _di_fl_string_prepend_
  f_return_status fl_string_prepend(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    return private_fl_string_prepend(source, length, destination);
  }
#endif // _di_fl_string_prepend_

#ifndef _di_fl_string_prepend_nulless_
  f_return_status fl_string_prepend_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    return private_fl_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_string_prepend_nulless_

#ifndef _di_fl_string_prepend_assure_
  f_return_status fl_string_prepend_assure(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (destination->used < length) {
      return private_fl_string_prepend(source, length, destination);
    }

    f_string_length i = 0;
    f_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source[i] == 0) {
        i++;
        continue;
      }

      if (destination->string[j] == 0) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) {
        return private_fl_string_prepend(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_prepend_assure_

#ifndef _di_fl_string_prepend_assure_nulless_
  f_return_status fl_string_prepend_assure_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    if (destination->used < length) {
      return private_fl_string_prepend_nulless(source, length, destination);
    }

    f_string_length i = 0;
    f_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source[i] == 0) {
        i++;
        continue;
      }

      if (destination->string[j] == 0) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) {
        return private_fl_string_prepend_nulless(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_string_prepend_assure_nulless_

#ifndef _di_fl_string_rip_
  f_return_status fl_string_rip(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    f_string_length begin = 0;
    f_string_length end = length - 1;

    f_status status = private_fl_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return private_fl_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_rip_

#ifndef _di_fl_string_rip_nulless_
  f_return_status fl_string_rip_nulless(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not;

    f_string_length begin = 0;
    f_string_length end = length - 1;

    f_status status = private_fl_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return private_fl_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_rip_nulless_

#ifndef _di_fl_string_seek_line_to_
  f_return_status fl_string_seek_line_to(const f_string string, f_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_none_stop;

    while (string[range->start] != seek_to_this) {
      if (string[range->start] == f_string_eol[0]) return F_none_eol;

      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_seek_line_to_

#ifndef _di_fl_string_seek_line_to_utf_character_
  f_return_status fl_string_seek_line_to_utf_character(const f_string string, f_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_none_stop;

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = F_none;

    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    for (; range->start <= range->stop; range->start += width) {
      width_max = (range->stop - range->start) + 1;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (width == 0) {
        width = 1;

        if (string[range->start] == f_string_eol[0]) return F_none_eol;

        if (seek_width == width) {
          if (string[range->start] == seek_to_this) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_eos);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(string + range->start, width_max, &character);

          if (F_status_is_error(status)) return status;
          if (character == seek_to_this) return F_none;
        }
      }
    } // for

    return F_none_stop;
  }
#endif // _di_fl_string_seek_line_to_utf_character_

#ifndef _di_fl_string_seek_line_until_graph_
  f_return_status fl_string_seek_line_until_graph(const f_string string, f_string_range *range, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_none_stop;

    f_status status = F_none;
    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_graph(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);
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
  f_return_status fl_string_seek_line_until_non_graph(const f_string string, f_string_range *range, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_none_stop;

    f_status status = F_none;
    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_whitespace(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start] == f_string_eol[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);
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
  f_return_status fl_string_seek_to(const f_string string, f_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_none_stop;

    while (string[range->start] != seek_to_this) {
      range->start++;

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_string_seek_to_

#ifndef _di_fl_string_seek_to_utf_character_
  f_return_status fl_string_seek_to_utf_character(const f_string string, f_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_none_stop;

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = F_none;

    unsigned short width = 0;

    f_string_length width_max = 0;

    for (; range->start <= range->stop; range->start += width) {
      width_max = (range->stop - range->start) + 1;

      width = f_macro_utf_byte_width_is(string[range->start]);

      if (width == 0) {
        width = 1;

        if (seek_width == width) {
          if (string[range->start] == seek_to_this) return F_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(string + range->start, width_max, &character);

          if (F_status_is_error(status)) return status;
          if (character == seek_to_this) return F_none;
        }
      }
    } // for

    return F_none_stop;
  }
#endif // _di_fl_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

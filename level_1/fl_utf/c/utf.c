#include <level_1/utf.h>
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_string_append_
  f_return_status fl_utf_string_append(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    return private_fl_utf_string_append(source, length, destination);
  }
#endif // _di_fl_utf_string_append_

#ifndef _di_fl_utf_string_append_assure_
  f_return_status fl_utf_string_append_assure(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (destination->used < length) {
      return private_fl_utf_string_append(source, length, destination);
    }

    f_utf_string_length i = 1;
    f_utf_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source[length - i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_fl_utf_string_append(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_append_assure_

#ifndef _di_fl_utf_string_append_assure_nulless_
  f_return_status fl_utf_string_append_assure_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (destination->used < length) {
      return private_fl_utf_string_append_nulless(source, length, destination);
    }

    f_utf_string_length i = 1;
    f_utf_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source[length - i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source[length - i] != destination->string[destination->used - j]) {
        return private_fl_utf_string_append_nulless(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_append_assure_nulless_

#ifndef _di_fl_utf_string_append_nulless_
  f_return_status fl_utf_string_append_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    return private_fl_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_append_nulless_

#ifndef _di_fl_utf_string_compare_
  f_return_status fl_utf_string_compare(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    return private_fl_utf_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_

#ifndef _di_fl_utf_string_compare_trim_
  f_return_status fl_utf_string_compare_trim(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    return private_fl_utf_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_trim_

#ifndef _di_fl_utf_string_dynamic_append_
  f_return_status fl_utf_string_dynamic_append(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    return private_fl_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_append_

#ifndef _di_fl_utf_string_dynamic_append_assure_
  f_return_status fl_utf_string_dynamic_append_assure(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_utf_string_append(source.string, source.used, destination);
    }

    f_utf_string_length i = 1;
    f_utf_string_length j = 1;

    while (i <= source.used && j <= destination->used) {
      if (source.string[source.used - i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_fl_utf_string_append(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_append_assure_

#ifndef _di_fl_utf_string_dynamic_append_assure_nulless_
  f_return_status fl_utf_string_dynamic_append_assure_nulless(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_utf_string_append_nulless(source.string, source.used, destination);
    }

    f_utf_string_length i = 1;
    f_utf_string_length j = 1;

    while (i <= source.used && j <= destination->used) {
      if (source.string[source.used - i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_fl_utf_string_append_nulless(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_append_assure_nulless_

#ifndef _di_fl_utf_string_dynamic_append_nulless_
  f_return_status fl_utf_string_dynamic_append_nulless(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    return private_fl_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_append_nulless_

#ifndef _di_fl_utf_string_dynamic_compare_
  f_return_status fl_utf_string_dynamic_compare(const f_utf_string_static string1, const f_utf_string_static string2) {
    return private_fl_utf_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_utf_string_dynamic_compare_

#ifndef _di_f_utf_string_dynamic_compare_trim_
  f_return_status f_utf_string_dynamic_compare_trim(const f_utf_string_static string1, const f_utf_string_static string2) {
    return private_fl_utf_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_utf_string_dynamic_compare_trim_

#ifndef _di_fl_utf_string_dynamic_mash_
  f_return_status fl_utf_string_dynamic_mash(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      const f_status status = private_fl_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mash_

#ifndef _di_fl_utf_string_dynamic_mash_nulless_
  f_return_status fl_utf_string_dynamic_mash_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      const f_status status = private_fl_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mash_nulless_

#ifndef _di_fl_utf_string_dynamic_mish_
  f_return_status fl_utf_string_dynamic_mish(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      const f_status status = private_fl_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mish_

#ifndef _di_fl_utf_string_dynamic_mish_nulless_
  f_return_status fl_utf_string_dynamic_mish_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      const f_status status = private_fl_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mish_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_append_
  f_return_status fl_utf_string_dynamic_partial_append(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_append_

#ifndef _di_fl_utf_string_dynamic_partial_append_assure_
  f_return_status fl_utf_string_dynamic_partial_append_assure(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_utf_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_utf_string_append(source.string + range.start, length, destination);
    }

    f_utf_string_length i = 1;
    f_utf_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source.string[range.stop - i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_fl_utf_string_append(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while
  }
#endif // _di_fl_utf_string_dynamic_partial_append_assure_

#ifndef _di_fl_utf_string_dynamic_partial_append_assure_nulless_
  f_return_status fl_utf_string_dynamic_partial_append_assure_nulless(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_utf_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_utf_string_append_nulless(source.string + range.start, length, destination);
    }

    f_utf_string_length i = 1;
    f_utf_string_length j = 1;

    while (i <= length && j <= destination->used) {
      if (source.string[range.stop - i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[destination->used - j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_fl_utf_string_append_nulless(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while
  }
#endif // _di_fl_utf_string_dynamic_partial_append_assure_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_append_nulless_
  f_return_status fl_utf_string_dynamic_partial_append_nulless(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_append_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_compare_
  f_return_status fl_utf_string_dynamic_partial_compare(const f_utf_string_static string1, const f_utf_string_static string2, const f_utf_string_range range1, const f_utf_string_range range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_utf_string_dynamic_partial_compare_

#ifndef _di_fl_utf_string_dynamic_partial_compare_trim_
  f_return_status fl_utf_string_dynamic_partial_comparetrim(const f_utf_string_static string1, const f_utf_string_static string2, const f_utf_string_range range1, const f_utf_string_range range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_utf_string_dynamic_partial_compare_trim_

#ifndef _di_fl_utf_string_dynamic_partial_mash_
  f_return_status fl_utf_string_dynamic_partial_mash(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mash_

#ifndef _di_fl_utf_string_dynamic_partial_mash_nulless_
  f_return_status fl_utf_string_dynamic_partial_mash_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mash_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_mish_
  f_return_status fl_utf_string_dynamic_partial_mish(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mish_

#ifndef _di_fl_utf_string_dynamic_partial_mish_nulless_
  f_return_status fl_utf_string_dynamic_partial_mish_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mish_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_prepend_
  f_return_status fl_utf_string_dynamic_partial_prepend(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_prepend_

#ifndef _di_fl_utf_string_dynamic_partial_prepend_assure_
  f_return_status fl_utf_string_dynamic_partial_prepend_assure(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_utf_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_utf_string_prepend(source.string + range.start, length, destination);
    }

    f_utf_string_length i = 0;
    f_utf_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source.string[i + range.start] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_fl_utf_string_prepend(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_partial_prepend_assure_

#ifndef _di_fl_utf_string_dynamic_partial_prepend_assure_nulless_
  f_return_status fl_utf_string_dynamic_partial_prepend_assure_nulless(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    const f_utf_string_length length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_fl_utf_string_prepend_nulless(source.string + range.start, length, destination);
    }

    f_utf_string_length i = 0;
    f_utf_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source.string[i + range.start] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_fl_utf_string_prepend_nulless(source.string + range.start, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_partial_prepend_assure_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_prepend_nulless_
  f_return_status fl_utf_string_dynamic_partial_prepend_nulless(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_prepend_nulless_

#ifndef _di_fl_utf_string_dynamic_prepend_
  f_return_status fl_utf_string_dynamic_prepend(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    return private_fl_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_prepend_

#ifndef _di_fl_utf_string_dynamic_prepend_assure_
  f_return_status fl_utf_string_dynamic_prepend_assure(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_utf_string_prepend(source.string, source.used, destination);
    }

    f_utf_string_length i = 0;
    f_utf_string_length j = 0;

    while (i < source.used && j < destination->used) {
      if (source.string[i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_fl_utf_string_prepend(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_prepend_assure_

#ifndef _di_fl_utf_string_dynamic_prepend_assure_nulless_
  f_return_status fl_utf_string_dynamic_prepend_assure_nulless(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    if (destination->used < source.used) {
      return private_fl_utf_string_prepend_nulless(source.string, source.used, destination);
    }

    f_utf_string_length i = 0;
    f_utf_string_length j = 0;

    while (i < source.used && j < destination->used) {
      if (source.string[i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_fl_utf_string_prepend_nulless(source.string, source.used, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_prepend_assure_nulless_

#ifndef _di_fl_utf_string_dynamic_prepend_nulless_
  f_return_status fl_utf_string_dynamic_prepend_nulless(const f_utf_string_static source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;

    return private_fl_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_prepend_nulless_

#ifndef _di_fl_utf_string_dynamic_rip_
  f_return_status fl_utf_string_dynamic_rip(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_rip_

#ifndef _di_fl_utf_string_dynamic_rip_nulless_
  f_return_status fl_utf_string_dynamic_rip_nulless(const f_utf_string_static source, const f_utf_string_range range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return private_fl_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_rip_nulless_

#ifndef _di_fl_utf_string_dynamic_seek_line_to_
  f_return_status fl_utf_string_dynamic_seek_line_to(const f_utf_string_static buffer, f_utf_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_this) {
      if (buffer.string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) return F_status_set_error(F_utf);

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_to_

#ifndef _di_fl_utf_string_dynamic_seek_line_to_char_
  f_return_status fl_utf_string_dynamic_seek_line_to_char(const f_utf_string_static buffer, f_utf_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_character) {
      if (buffer.string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_to_character_

#ifndef _di_fl_utf_string_dynamic_seek_line_until_graph_
  f_return_status fl_utf_string_dynamic_seek_line_until_graph(const f_utf_string_static buffer, f_utf_string_range *range, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    f_status status = F_none;

    if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_character_is_graph(buffer.string[range->start])) == F_false) {
      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_until_graph_

#ifndef _di_fl_utf_string_dynamic_seek_line_until_non_graph_
  f_return_status fl_utf_string_dynamic_seek_line_until_non_graph(const f_utf_string_static buffer, f_utf_string_range *range, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    f_status status = F_none;

    if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_character_is_whitespace(buffer.string[range->start])) == F_false) {
      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_until_non_graph_

#ifndef _di_fl_utf_string_dynamic_seek_to_
  f_return_status fl_utf_string_dynamic_seek_to(const f_utf_string_static buffer, f_utf_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_this) {
      range->start++;

      if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_to_

#ifndef _di_fl_utf_string_dynamic_seek_to_char_
  f_return_status fl_utf_string_dynamic_seek_to_char(const f_utf_string_static buffer, f_utf_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
      if (buffer.used <= range->stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_character) {
      range->start++;

      if (f_macro_utf_character_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_to_char_

#ifndef _di_fl_utf_string_dynamic_terminate_
  f_return_status fl_utf_string_dynamic_terminate(f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (destination->used > 0 && destination->string[destination->used - 1] == f_utf_character_eos) {
      return F_none;
    }

    if (destination->used + 1 > f_utf_string_length_size) {
      return F_status_set_error(F_string_too_large);
    }

    const f_utf_string_length total = destination->used + 1;

    if (total > destination->size) {
      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = f_utf_character_eos;
    destination->used = total;

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_terminate_

#ifndef _di_fl_utf_string_dynamic_terminate_after_
  f_return_status fl_utf_string_dynamic_terminate_after(f_utf_string_dynamic *destination) {
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

    if (destination->used + 1 > f_utf_string_length_size) {
      return F_status_set_error(F_string_too_large);
    }

    const f_utf_string_length total = destination->used + 1;

    if (total > destination->size) {
      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*destination), total);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total - 1;

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_terminate_after_

#ifndef _di_fl_utf_string_mash_
  f_return_status fl_utf_string_mash(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_append(source, length, destination);
  }
#endif // _di_fl_utf_string_mash_

#ifndef _di_fl_utf_string_mash_nulless_
  f_return_status fl_utf_string_mash_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_mash_nulless_

#ifndef _di_fl_utf_string_mish_
  f_return_status fl_utf_string_mish(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_prepend(source, length, destination);
  }
#endif // _di_fl_utf_string_mish_

#ifndef _di_fl_utf_string_mish_nulless_
  f_return_status fl_utf_string_mish_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend_nulless(glue, glue_length, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_fl_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_mish_nulless_

#ifndef _di_fl_utf_string_prepend_
  f_return_status fl_utf_string_prepend(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    return private_fl_utf_string_prepend(source, length, destination);
  }
#endif // _di_fl_utf_string_prepend_

#ifndef _di_fl_utf_string_prepend_assure_
  f_return_status fl_utf_string_prepend_assure(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (destination->used < length) {
      return private_fl_utf_string_prepend(source, length, destination);
    }

    f_utf_string_length i = 0;
    f_utf_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source[i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) {
        return private_fl_utf_string_prepend(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_prepend_assure_

#ifndef _di_fl_utf_string_prepend_assure_nulless_
  f_return_status fl_utf_string_prepend_assure_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    if (destination->used < length) {
      return private_fl_utf_string_prepend_nulless(source, length, destination);
    }

    f_utf_string_length i = 0;
    f_utf_string_length j = 0;

    while (i < length && j < destination->used) {
      if (source[i] == f_utf_character_eos) {
        i++;
        continue;
      }

      if (destination->string[j] == f_utf_character_eos) {
        j++;
        continue;
      }

      if (source[i] != destination->string[i]) {
        return private_fl_utf_string_prepend_nulless(source, length, destination);
      }

      i++;
      j++;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_prepend_assure_nulless_

#ifndef _di_fl_utf_string_prepend_nulless_
  f_return_status fl_utf_string_prepend_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    return private_fl_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_prepend_nulless_

#ifndef _di_fl_utf_string_rip_
  f_return_status fl_utf_string_rip(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    f_utf_string_length begin = 0;
    f_utf_string_length end = length - 1;

    f_status status = private_fl_utf_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return private_fl_utf_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_utf_string_rip_

#ifndef _di_fl_utf_string_rip_nulless_
  f_return_status fl_utf_string_rip_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return F_data_not_eos;

    f_utf_string_length begin = 0;
    f_utf_string_length end = length - 1;

    f_status status = private_fl_utf_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return private_fl_utf_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_utf_string_rip_nulless_

#ifndef _di_fl_utf_string_seek_line_to_
  f_return_status fl_utf_string_seek_line_to(const f_utf_string string, f_utf_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] != seek_to_this) {
      if (string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_seek_line_to_

#ifndef _di_fl_utf_string_seek_line_to_char_
  f_return_status fl_utf_string_seek_line_to_char(const f_utf_string string, f_utf_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    for (; range->start <= range->stop; range->start++) {
      if (f_macro_utf_character_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (string[range->start] == f_utf_character_eol) return F_none_eol;
      if (string[range->start] == seek_to_character) return F_none;
    } // for

    return F_none_stop;
  }
#endif // _di_fl_utf_string_seek_line_to_char_

#ifndef _di_fl_utf_string_seek_line_until_graph_
  f_return_status fl_utf_string_seek_line_until_graph(const f_utf_string string, f_utf_string_range *range, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status status = F_none;

    if (f_macro_utf_character_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] == placeholder || (status = f_utf_character_is_graph(string[range->start])) == F_false) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) return F_none_stop;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_utf_string_seek_line_until_graph_

#ifndef _di_fl_utf_string_seek_line_until_non_graph_
  f_return_status fl_utf_string_seek_line_until_non_graph(const f_utf_string string, f_utf_string_range *range, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status status = F_none;

    if (f_macro_utf_character_width_is(string[range->start]) == 1) return F_status_set_error(F_utf);

    while (string[range->start] == placeholder || (status = f_utf_character_is_graph(string[range->start])) == F_true) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_utf_character_eol) return F_none_eol;

      range->start++;

      if (f_macro_utf_character_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) return F_none_stop;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_utf_string_seek_line_until_non_graph_

#ifndef _di_fl_utf_string_seek_to_
  f_return_status fl_utf_string_seek_to(const f_utf_string string, f_utf_string_range *range, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    if (f_macro_utf_character_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] != seek_to_this) {
      range->start++;

      if (f_macro_utf_character_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_seek_to_

#ifndef _di_fl_utf_string_seek_to_char_
  f_return_status fl_utf_string_seek_to_char(const f_utf_string string, f_utf_string_range *range, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const f_utf_character seek_to_character = seek_to_this << 24;

    if (f_macro_utf_character_width_is(string[0]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (range->start <= range->stop) {
      if (string[range->start] == seek_to_character) return F_none;

      range->start++;

      if (f_macro_utf_character_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }
    } // while

    return F_none_stop;
  }
#endif // _di_fl_utf_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

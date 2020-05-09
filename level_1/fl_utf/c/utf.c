#include <level_1/utf.h>
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_string_append_
  f_return_status fl_utf_string_append(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    return private_fl_utf_string_append(source, length, destination);
  }
#endif // _di_fl_utf_string_append_

#ifndef _di_fl_utf_string_append_nulless_
  f_return_status fl_utf_string_append_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    return private_fl_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_append_nulless_

#ifndef _di_fl_utf_string_compare_
  f_return_status fl_utf_string_compare(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 == 0) return f_status_set_error(f_invalid_parameter);
      if (length2 == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_

#ifndef _di_fl_utf_string_compare_trim_
  f_return_status fl_utf_string_compare_trim(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 == 0) return f_status_set_error(f_invalid_parameter);
      if (length2 == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_trim_

#ifndef _di_fl_utf_string_dynamic_append_
  f_return_status fl_utf_string_dynamic_append(const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    return private_fl_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_append_

#ifndef _di_fl_utf_string_dynamic_append_nulless_
  f_return_status fl_utf_string_dynamic_append_nulless(const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    return private_fl_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_append_nulless_

#ifndef _di_fl_utf_string_dynamic_mash_
  f_return_status fl_utf_string_dynamic_mash(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_append(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mash_

#ifndef _di_fl_utf_string_dynamic_mash_nulless_
  f_return_status fl_utf_string_dynamic_mash_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append_nulless(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mash_nulless_

#ifndef _di_fl_utf_string_dynamic_mish_
  f_return_status fl_utf_string_dynamic_mish(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mish_

#ifndef _di_fl_utf_string_dynamic_mish_nulless_
  f_return_status fl_utf_string_dynamic_mish_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend_nulless(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_mish_nulless_

#ifndef _di_fl_utf_string_dynamic_compare_
  f_return_status fl_utf_string_dynamic_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2) {
    return private_fl_utf_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_utf_string_dynamic_compare_

#ifndef _di_f_utf_string_dynamic_compare_trim_
  f_return_status f_utf_string_dynamic_compare_trim(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2) {
    return private_fl_utf_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_utf_string_dynamic_compare_trim_

#ifndef _di_fl_utf_string_dynamic_partial_append_
  f_return_status fl_utf_string_dynamic_partial_append(const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    return private_fl_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_append_

#ifndef _di_fl_utf_string_dynamic_partial_append_nulless_
  f_return_status fl_utf_string_dynamic_partial_append_nulless(const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    return private_fl_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_append_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_compare_
  f_return_status fl_utf_string_dynamic_partial_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2, const f_utf_string_location range1, const f_utf_string_location range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= range2.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_utf_string_dynamic_partial_compare_

#ifndef _di_fl_utf_string_dynamic_partial_compare_trim_
  f_return_status fl_utf_string_dynamic_partial_comparetrim(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2, const f_utf_string_location range1, const f_utf_string_location range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= range2.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_utf_string_dynamic_partial_compare_trim_

#ifndef _di_fl_utf_string_dynamic_partial_mash_
  f_return_status fl_utf_string_dynamic_partial_mash(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mash_

#ifndef _di_fl_utf_string_dynamic_partial_mash_nulless_
  f_return_status fl_utf_string_dynamic_partial_mash_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append_nulless(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mash_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_mish_
  f_return_status fl_utf_string_dynamic_partial_mish(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mish_

#ifndef _di_fl_utf_string_dynamic_partial_mish_nulless_
  f_return_status fl_utf_string_dynamic_partial_mish_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend_nulless(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_mish_nulless_

#ifndef _di_fl_utf_string_dynamic_partial_prepend_
  f_return_status fl_utf_string_dynamic_partial_prepend(const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    return private_fl_utf_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_prepend_

#ifndef _di_fl_utf_string_dynamic_partial_prepend_nulless_
  f_return_status fl_utf_string_dynamic_partial_prepend_nulless(const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    return private_fl_utf_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_partial_prepend_nulless_

#ifndef _di_fl_utf_string_dynamic_prepend_
  f_return_status fl_utf_string_dynamic_prepend(const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    return private_fl_utf_string_prepend(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_prepend_

#ifndef _di_fl_utf_string_dynamic_prepend_nulless_
  f_return_status fl_utf_string_dynamic_prepend_nulless(const f_utf_string_dynamic source, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;

    return private_fl_utf_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_fl_utf_string_dynamic_prepend_nulless_

#ifndef _di_fl_utf_string_dynamic_rip_
  f_return_status fl_utf_string_dynamic_rip(const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return f_status_set_error(f_invalid_parameter);
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    return private_fl_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_rip_

#ifndef _di_fl_utf_string_dynamic_rip_nulless_
  f_return_status fl_utf_string_dynamic_rip_nulless(const f_utf_string_dynamic source, const f_utf_string_location range, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return f_status_set_error(f_invalid_parameter);
      if (source.used <= range.stop) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (source.used == 0) return f_no_data;
    if (range.start > range.stop) return f_no_data;

    return private_fl_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_rip_nulless_

#ifndef _di_fl_utf_string_dynamic_seek_line_to_
  f_return_status fl_utf_string_dynamic_seek_line_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return f_none_on_eos;
    if (location->start > location->stop) return f_none_on_stop;

    if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (buffer.string[location->start] != seek_to_this) {
      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_to_

#ifndef _di_fl_utf_string_dynamic_seek_line_to_char_
  f_return_status fl_utf_string_dynamic_seek_line_to_char(const f_utf_string_dynamic buffer, f_utf_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return f_none_on_eos;
    if (location->start > location->stop) return f_none_on_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (buffer.string[location->start] != seek_to_character) {
      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_to_character_

#ifndef _di_fl_utf_string_dynamic_seek_line_until_graph_
  f_return_status fl_utf_string_dynamic_seek_line_until_graph(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return f_none_on_eos;
    if (location->start > location->stop) return f_none_on_stop;

    f_status status = f_none;

    if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (buffer.string[location->start] == placeholder || (status = f_utf_character_is_graph(buffer.string[location->start])) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_until_graph_

#ifndef _di_fl_utf_string_dynamic_seek_line_until_non_graph_
  f_return_status fl_utf_string_dynamic_seek_line_until_non_graph(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return f_none_on_eos;
    if (location->start > location->stop) return f_none_on_stop;

    f_status status = f_none;

    if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (buffer.string[location->start] == placeholder || (status = f_utf_character_is_whitespace(buffer.string[location->start])) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_until_non_graph_

#ifndef _di_fl_utf_string_dynamic_seek_to_
  f_return_status fl_utf_string_dynamic_seek_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return f_none_on_eos;
    if (location->start > location->stop) return f_none_on_stop;

    if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (buffer.string[location->start] != seek_to_this) {
      location->start++;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_to_

#ifndef _di_fl_utf_string_dynamic_seek_to_char_
  f_return_status fl_utf_string_dynamic_seek_to_char(const f_utf_string_dynamic buffer, f_utf_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (buffer.used == 0) return f_none_on_eos;
    if (location->start > location->stop) return f_none_on_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (buffer.string[location->start] != seek_to_character) {
      location->start++;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_to_char_

#ifndef _di_fl_utf_string_dynamic_terminate_
  f_return_status fl_utf_string_dynamic_terminate(f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
      if (destination->used > destination->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (destination->used > 0 && destination->string[destination->used - 1] == f_utf_character_eos) return f_none;

    if (destination->used + 1 > f_utf_string_max_size) return f_status_set_error(f_string_too_large);

    const f_utf_string_length total = destination->used + 1;

    if (total > destination->size) {
      f_status status = f_none;

      f_macro_string_dynamic_resize(status, (*destination), total);
      if (f_status_is_error(status)) return status;
    }

    destination->string[destination->used] = f_string_eos;
    destination->used = total;

    return f_none;
  }
#endif // _di_fl_utf_string_dynamic_terminate_

#ifndef _di_fl_utf_string_mash_
  f_return_status fl_utf_string_mash(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_append(source, length, destination);
  }
#endif // _di_fl_utf_string_mash_

#ifndef _di_fl_utf_string_mash_nulless_
  f_return_status fl_utf_string_mash_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_append_nulless(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_append_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_mash_nulless_

#ifndef _di_fl_utf_string_mish_
  f_return_status fl_utf_string_mish(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_prepend(source, length, destination);
  }
#endif // _di_fl_utf_string_mish_

#ifndef _di_fl_utf_string_mish_nulless_
  f_return_status fl_utf_string_mish_nulless(const f_utf_string glue, const f_utf_string_length glue_length, const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    if (glue_length > 0 && destination->used > 0) {
      f_status status = private_fl_utf_string_prepend_nulless(glue, glue_length, destination);

      if (f_status_is_error(status)) {
        return status;
      }
    }

    return private_fl_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_mish_nulless_

#ifndef _di_fl_utf_string_prepend_
  f_return_status fl_utf_string_prepend(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    return private_fl_utf_string_prepend(source, length, destination);
  }
#endif // _di_fl_utf_string_prepend_

#ifndef _di_fl_utf_string_prepend_nulless_
  f_return_status fl_utf_string_prepend_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    return private_fl_utf_string_prepend_nulless(source, length, destination);
  }
#endif // _di_fl_utf_string_prepend_nulless_

#ifndef _di_fl_utf_string_rip_
  f_return_status fl_utf_string_rip(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    f_utf_string_length begin = 0;
    f_utf_string_length end = length - 1;

    f_status status = private_fl_utf_string_rip_find_range(source, &begin, &end);

    if (f_status_is_error(status)) return status;
    if (status == f_no_data) return status;

    return private_fl_utf_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_utf_string_rip_

#ifndef _di_fl_utf_string_rip_nulless_
  f_return_status fl_utf_string_rip_nulless(const f_utf_string source, const f_utf_string_length length, f_utf_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (length == 0) return f_no_data;

    f_utf_string_length begin = 0;
    f_utf_string_length end = length - 1;

    f_status status = private_fl_utf_string_rip_find_range(source, &begin, &end);

    if (f_status_is_error(status)) return status;
    if (status == f_no_data) return status;

    return private_fl_utf_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_utf_string_rip_nulless_

#ifndef _di_fl_utf_string_seek_line_to_
  f_return_status fl_utf_string_seek_line_to(const f_utf_string string, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start > location->stop) return f_none_on_stop;

    if (f_macro_utf_character_width_is(string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (string[location->start] != seek_to_this) {
      if (string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_seek_line_to_

#ifndef _di_fl_utf_string_seek_line_to_char_
  f_return_status fl_utf_string_seek_line_to_char(const f_utf_string string, f_utf_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start > location->stop) return f_none_on_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    f_status status = f_none;

    for (; location->start <= location->stop; location->start++) {
      if (f_macro_utf_character_width_is(string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (string[location->start] == f_utf_character_eol) return f_none_on_eol;
      if (string[location->start] == seek_to_character) return f_none;
    } // for

    return f_none_on_stop;
  }
#endif // _di_fl_utf_string_seek_line_to_char_

#ifndef _di_fl_utf_string_seek_line_until_graph_
  f_return_status fl_utf_string_seek_line_until_graph(const f_utf_string string, f_utf_string_location *location, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start > location->stop) return f_none_on_stop;

    f_status status = f_none;

    if (f_macro_utf_character_width_is(string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (string[location->start] == placeholder || (status = f_utf_character_is_graph(string[location->start])) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start > location->stop) return f_none_on_stop;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_utf_string_seek_line_until_graph_

#ifndef _di_fl_utf_string_seek_line_until_non_graph_
  f_return_status fl_utf_string_seek_line_until_non_graph(const f_utf_string string, f_utf_string_location *location, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start > location->stop) return f_none_on_stop;

    f_status status = f_none;

    if (f_macro_utf_character_width_is(string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (string[location->start] == placeholder || (status = f_utf_character_is_whitespace(string[location->start])) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (string[location->start] == f_utf_character_eol) return f_none_on_eol;

      location->start++;

      if (f_macro_utf_character_width_is(string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start > location->stop) return f_none_on_stop;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_utf_string_seek_line_until_non_graph_

#ifndef _di_fl_utf_string_seek_to_
  f_return_status fl_utf_string_seek_to(const f_utf_string string, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start > location->stop) return f_none_on_stop;

    if (f_macro_utf_character_width_is(string[location->start]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (string[location->start] != seek_to_this) {
      location->start++;

      if (f_macro_utf_character_width_is(string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_seek_to_

#ifndef _di_fl_utf_string_seek_to_char_
  f_return_status fl_utf_string_seek_to_char(const f_utf_string string, f_utf_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start > location->stop) return f_none_on_stop;

    f_utf_character seek_to_character = seek_to_this << 24;

    f_status status = f_none;

    if (f_macro_utf_character_width_is(string[0]) == 1) {
      return f_status_set_error(f_invalid_utf);
    }

    while (location->start <= location->stop) {
      if (string[location->start] == seek_to_character) return f_none;

      location->start++;

      if (f_macro_utf_character_width_is(string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }
    } // while

    return f_none_on_stop;
  }
#endif // _di_fl_utf_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

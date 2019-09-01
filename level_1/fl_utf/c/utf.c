#include <level_1/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_seek_line_until_graph_
  f_return_status fl_utf_seek_line_until_graph(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    while (buffer.string[location->start] == placeholder || (status = f_utf_is_graph_character(buffer.string[location->start])) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_utf_seek_line_until_graph_

#ifndef _di_fl_utf_seek_line_until_non_graph_
  f_return_status fl_utf_seek_line_until_non_graph(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    while (buffer.string[location->start] == placeholder || (status = f_utf_is_space_character(buffer.string[location->start])) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_utf_seek_line_until_non_graph_

#ifndef _di_fl_utf_seek_line_to_
  f_return_status fl_utf_seek_line_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[location->start] != seek_to_this) {
      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_seek_line_to_

#ifndef _di_fl_utf_seek_line_to_char_
  f_return_status fl_utf_seek_line_to_char(const f_utf_string_dynamic buffer, f_utf_string_location *location, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_utf_character seek_to_character = seek_to_this << 24;

    while (buffer.string[location->start] != seek_to_character) {
      if (buffer.string[location->start] == f_utf_character_eol) return f_none_on_eol;

      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_seek_line_to_character_

#ifndef _di_fl_utf_string_rip_
  f_return_status fl_utf_string_rip(const f_utf_string_dynamic buffer, const f_utf_string_location location, f_utf_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    // the start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations
    f_utf_string_length size = (location.stop - location.start) + 1;

    if (size > 0) {
      f_status status = f_none;

      if (result == 0) {
        f_macro_utf_string_dynamic_new(status, (*result), size);
      }
      else {
        f_macro_utf_string_dynamic_resize(status, (*result), size);
      }

      if (f_status_is_error(status)) {
        return status;
      }

      memcpy(result->string, buffer.string + location.start, sizeof(f_utf_character) * size);
      result->used = size;

      return f_none;
    }

    return f_no_data;
  }
#endif // _di_fl_utf_string_rip_

#ifndef _di_fl_utf_string_seek_to_
  f_return_status fl_utf_string_seek_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[location->start] != seek_to_this) {
      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_seek_to_

#ifndef _di_fl_utf_string_seek_to_char_
  f_return_status fl_utf_string_seek_to_char(const f_utf_string_dynamic buffer, f_utf_string_location *location, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_utf_character seek_to_character = seek_to_this << 24;

    while (buffer.string[location->start] != seek_to_character) {
      if (f_macro_utf_character_width_is(buffer.string[location->start]) == 1) {
        return f_status_set_error(f_invalid_utf);
      }

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_utf_string_seek_to_char_

#ifndef _di_fl_utf_string_compare_
  f_return_status fl_utf_string_compare(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_status_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_utf_string_length i1 = 0;
    f_utf_string_length i2 = 0;

    for (; i1 < length1 && i2 < length2; i1++, i2++) {
      // skip past newlines in string1.
      while (i1 < length1 && string1[i1] == f_utf_character_eos) i1++;
      if (i1 == length1) break;

      // skip past newlines in string2.
      while (i2 < length2 && string2[i2] == f_utf_character_eos) i2++;
      if (i2 == length2) break;

      if (string1[i1] != string2[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    while (i1 < length1) {
      if (string1[i1] != f_utf_character_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < length2) {
      if (string2[i2] != f_utf_character_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_utf_string_compare_

#ifndef _di_fl_utf_string_dynamic_compare_
  f_return_status fl_utf_string_dynamic_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_utf_string_length i1 = 0;
    f_utf_string_length i2 = 0;

    for (; i1 < string1.used && i2 < string2.used; i1++, i2++) {
      // skip past newlines in string1.
      while (i1 < string1.used && string1.string[i1] == f_utf_character_eos) i1++;
      if (i1 == string1.used) break;

      // skip past newlines in string2.
      while (i2 < string2.used && string2.string[i2] == f_utf_character_eos) i2++;
      if (i2 == string2.used) break;

      if (string1.string[i1] != string2.string[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    while (i1 < string1.used) {
      if (string1.string[i1] != f_utf_character_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < string2.used) {
      if (string2.string[i2] != f_utf_character_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_utf_string_dynamic_compare_

#ifndef _di_fl_string_dynamic_partial_compare_
  f_return_status fl_utf_string_dynamic_partial_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2, const f_utf_string_location offset1, const f_utf_string_location offset2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);

      if (offset1.start > offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (offset2.start > offset2.stop) return f_status_set_error(f_invalid_parameter);

      if (string1.used <= offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= offset2.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_utf_string_length i1 = offset1.start;
    f_utf_string_length i2 = offset2.start;

    const f_utf_string_length stop1 = offset1.stop + 1;
    const f_utf_string_length stop2 = offset2.stop + 1;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      // skip past newlines in string1.
      while (i1 < stop1 && string1.string[i1] == f_utf_character_eos) i1++;
      if (i1 == stop1) break;

      // skip past newlines in string2.
      while (i2 < stop2 && string2.string[i2] == f_utf_character_eos) i2++;
      if (i2 == stop2) break;

      if (string1.string[i1] != string2.string[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    while (i1 < stop1) {
      if (string1.string[i1] != f_utf_character_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < stop2) {
      if (string2.string[i2] != f_utf_character_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifdef __cplusplus
} // extern "C"
#endif

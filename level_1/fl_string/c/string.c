#include <level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_string_rip_
  f_return_status fl_string_rip(const f_string_dynamic buffer, const f_string_location location, f_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    // the start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations
    f_string_length size = (location.stop - location.start) + 1;

    if (size > 0) {
      f_status status = f_none;

      if (result == 0) {
        f_macro_string_dynamic_new(status, (*result), size);
      }
      else {
        f_macro_string_dynamic_resize(status, (*result), size);
      }

      if (f_status_is_error(status)) {
        return status;
      }

      memcpy(result->string, buffer.string + location.start, sizeof(int8_t) * size);
      result->used = size;

      return f_none;
    }

    return f_no_data;
  }
#endif // _di_fl_string_rip_

#ifndef _di_fl_string_seek_line_until_graph_
  f_return_status fl_string_seek_line_until_graph(const f_string_dynamic buffer, f_string_location *location, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length max_width = (location->stop - location->start) + 1;

    if (max_width > buffer.used - location->start) {
      max_width = buffer.used - location->start;
    }

    while (buffer.string[location->start] == placeholder || (status = f_utf_is_graph(buffer.string + location->start, max_width)) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_string_eol) return f_none_on_eol;

      width = f_macro_utf_byte_width_is(buffer.string[location->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      location->start += width;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;

      max_width = (location->stop - location->start) + 1;

      if (max_width > buffer.used - location->start) {
        max_width = buffer.used - location->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_string_seek_line_until_graph_

#ifndef _di_fl_string_seek_line_until_non_graph_
  f_return_status fl_string_seek_line_until_non_graph(const f_string_dynamic buffer, f_string_location *location, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length max_width = (location->stop - location->start) + 1;

    if (max_width > buffer.used - location->start) {
      max_width = buffer.used - location->start;
    }

    while (buffer.string[location->start] == placeholder || (status = f_utf_is_space(buffer.string + location->start, max_width)) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_string_eol) return f_none_on_eol;

      width = f_macro_utf_byte_width_is(buffer.string[location->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      location->start += width;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;

      max_width = (location->stop - location->start) + 1;

      if (max_width > buffer.used - location->start) {
        max_width = buffer.used - location->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_string_seek_line_until_non_graph_

#ifndef _di_fl_string_seek_line_to_
  f_return_status fl_string_seek_line_to(const f_string_dynamic buffer, f_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[location->start] != seek_to_this) {
      if (buffer.string[location->start] == f_string_eol) return f_none_on_eol;

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_string_seek_line_to_

#ifndef _di_fl_string_seek_line_to_utf_character_
  f_return_status fl_string_seek_line_to_utf_character(const f_string_dynamic buffer, f_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = f_none;

    unsigned short width = 0;

    f_string_length max_width = 0;

    while (location->start < buffer.used) {
      max_width = (location->stop - location->start) + 1;

      if (max_width > buffer.used - location->start) {
        max_width = buffer.used - location->start;
      }

      width = f_macro_utf_byte_width_is(buffer.string[location->start]);

      if (width == 0) {
        width = 1;

        if (buffer.string[location->start] == f_string_eol) return f_none_on_eol;

        if (seek_width == width) {
          if (buffer.string[location->start] == seek_to_this) return f_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(buffer.string + location->start, max_width, &character);

          if (f_status_is_error(status)) {
            return status;
          }

          if (character == seek_to_this) {
            return f_none;
          }
        }
      }

      location->start += width;

      if (location->start >= location->stop) return f_none_on_stop;
    } // while

    return f_none_on_eos;
  }
#endif // _di_fl_string_seek_line_to_utf_character_

#ifndef _di_fl_string_seek_to_
  f_return_status fl_string_seek_to(const f_string_dynamic buffer, f_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[location->start] != seek_to_this) {
      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_string_seek_to_

#ifndef _di_fl_string_seek_to_utf_character_
  f_return_status fl_string_seek_to_utf_character(const f_string_dynamic buffer, f_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = f_none;

    unsigned short width = 0;

    f_string_length max_width = 0;

    while (location->start < buffer.used) {
      max_width = (location->stop - location->start) + 1;

      if (max_width > buffer.used - location->start) {
        max_width = buffer.used - location->start;
      }

      width = f_macro_utf_byte_width_is(buffer.string[location->start]);

      if (width == 0) {
        width = 1;

        if (seek_width == width) {
          if (buffer.string[location->start] == seek_to_this) return f_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(buffer.string + location->start, max_width, &character);

          if (f_status_is_error(status)) {
            return status;
          }

          if (character == seek_to_this) {
            return f_none;
          }
        }
      }

      location->start += width;

      if (location->start >= location->stop) return f_none_on_stop;
    } // while

    return f_none_on_eos;
  }
#endif // _di_fl_string_seek_to_utf_character_

#ifndef _di_fl_string_compare_
  f_return_status fl_string_compare(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_status_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i1 = 0;
    f_string_length i2 = 0;

    for (; i1 < length1 && i2 < length2; i1++, i2++) {
      // skip past newlines in string1.
      while (i1 < length1 && string1[i1] == f_string_eos) i1++;
      if (i1 == length1) break;

      // skip past newlines in string2.
      while (i2 < length2 && string2[i2] == f_string_eos) i2++;
      if (i2 == length2) break;

      if (string1[i1] != string2[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    while (i1 < length1) {
      if (string1[i1] != f_string_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < length2) {
      if (string2[i2] != f_string_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_string_compare_

#ifndef _di_fl_string_dynamics_compare_
  f_return_status fl_string_dynamics_compare(const f_string_dynamic string1, const f_string_dynamic string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i1 = 0;
    f_string_length i2 = 0;

    for (; i1 < string1.used && i2 < string2.used; i1++, i2++) {
      // skip past newlines in string1.
      while (i1 < string1.used && string1.string[i1] == f_string_eos) i1++;
      if (i1 == string1.used) break;

      // skip past newlines in string2.
      while (i2 < string2.used && string2.string[i2] == f_string_eos) i2++;
      if (i2 == string2.used) break;

      if (string1.string[i1] != string2.string[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    while (i1 < string1.used) {
      if (string1.string[i1] != f_string_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < string2.used) {
      if (string2.string[i2] != f_string_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_string_dynamics_compare_

#ifndef _di_fl_string_dynamic_partial_compare_
  f_return_status fl_string_dynamic_partial_compare(const f_string_dynamic string1, const f_string_dynamic string2, const f_string_location offset1, const f_string_location offset2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);

      if (offset1.start > offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (offset2.start > offset2.stop) return f_status_set_error(f_invalid_parameter);

      if (string1.used <= offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= offset2.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i1 = offset1.start;
    f_string_length i2 = offset2.start;

    const f_string_length stop1 = offset1.stop + 1;
    const f_string_length stop2 = offset2.stop + 1;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      // skip past newlines in string1.
      while (i1 < stop1 && string1.string[i1] == f_string_eos) i1++;
      if (i1 == stop1) break;

      // skip past newlines in string2.
      while (i2 < stop2 && string2.string[i2] == f_string_eos) i2++;
      if (i2 == stop2) break;

      if (string1.string[i1] != string2.string[i2]) return f_not_equal_to;
    } // for

    // only return f_equal_to if all remaining characters are NULL.
    while (i1 < stop1) {
      if (string1.string[i1] != f_string_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < stop2) {
      if (string2.string[i2] != f_string_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifdef __cplusplus
} // extern "C"
#endif

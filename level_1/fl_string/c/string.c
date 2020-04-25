#include <level_1/string.h>
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_string_compare_
  f_return_status fl_string_compare(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_status_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_

#ifndef _di_fl_string_compare_trim_
  f_return_status fl_string_compare_trim(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_status_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_trim_

#ifndef _di_fl_string_dynamic_compare_
  f_return_status fl_string_dynamic_compare(const f_string_dynamic string1, const f_string_dynamic string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_

#ifndef _di_fl_string_dynamic_compare_trim_
  f_return_status fl_string_dynamic_compare_trim(const f_string_dynamic string1, const f_string_dynamic string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_trim_

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

    return private_fl_string_compare(string1.string, string2.string, offset1.start, offset2.start, offset1.stop + 1, offset2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifndef _di_fl_string_dynamic_partial_compare_trim_
  f_return_status fl_string_dynamic_partial_compare_trim(const f_string_dynamic string1, const f_string_dynamic string2, const f_string_location offset1, const f_string_location offset2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);

      if (offset1.start > offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (offset2.start > offset2.stop) return f_status_set_error(f_invalid_parameter);

      if (string1.used <= offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= offset2.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, offset1.start, offset2.start, offset1.stop + 1, offset2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_

#ifndef _di_fl_string_dynamic_rip_
  f_return_status fl_string_dynamic_rip(const f_string_dynamic buffer, const f_string_location location, f_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_rip(buffer.string, location.start, location.stop, result);
  }
#endif // _di_fl_string_dynamic_rip_

#ifndef _di_fl_string_dynamic_rip_trim_
  f_return_status fl_string_dynamic_rip_trim(const f_string_dynamic buffer, const f_string_location location, f_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_rip_trim(buffer.string, location.start, location.stop, result);
  }
#endif // _di_fl_string_dynamic_rip_trim_

#ifndef _di_fl_string_dynamic_seek_line_to_
  f_return_status fl_string_dynamic_seek_line_to(const f_string_dynamic buffer, f_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[location->start] != seek_to_this) {
      if (buffer.string[location->start] == f_string_eol) return f_none_on_eol;

      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_string_dynamic_seek_line_to_

#ifndef _di_fl_string_dynamic_seek_line_to_utf_character_
  f_return_status fl_string_dynamic_seek_line_to_utf_character(const f_string_dynamic buffer, f_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = f_none;

    unsigned short width = 0;

    f_string_length width_max = 0;

    while (location->start < buffer.used) {
      width_max = (location->stop - location->start) + 1;

      if (width_max > buffer.used - location->start) {
        width_max = buffer.used - location->start;
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
          status = f_utf_char_to_character(buffer.string + location->start, width_max, &character);

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
#endif // _di_fl_string_dynamic_seek_line_to_utf_character_

#ifndef _di_fl_string_dynamic_seek_line_until_graph_
  f_return_status fl_string_dynamic_seek_line_until_graph(const f_string_dynamic buffer, f_string_location *location, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length width_max = (location->stop - location->start) + 1;

    if (width_max > buffer.used - location->start) {
      width_max = buffer.used - location->start;
    }

    while (buffer.string[location->start] == placeholder || (status = f_utf_is_graph(buffer.string + location->start, width_max)) == f_false) {
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

      width_max = (location->stop - location->start) + 1;

      if (width_max > buffer.used - location->start) {
        width_max = buffer.used - location->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_string_dynamic_seek_line_until_graph_

#ifndef _di_fl_string_dynamic_seek_line_until_non_graph_
  f_return_status fl_string_dynamic_seek_line_until_non_graph(const f_string_dynamic buffer, f_string_location *location, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length width_max = (location->stop - location->start) + 1;

    if (width_max > buffer.used - location->start) {
      width_max = buffer.used - location->start;
    }

    while (buffer.string[location->start] == placeholder || (status = f_utf_is_whitespace(buffer.string + location->start, width_max)) == f_false) {
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

      width_max = (location->stop - location->start) + 1;

      if (width_max > buffer.used - location->start) {
        width_max = buffer.used - location->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_string_dynamic_seek_line_until_non_graph_

#ifndef _di_fl_string_dynamic_seek_to_
  f_return_status fl_string_dynamic_seek_to(const f_string_dynamic buffer, f_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[location->start] != seek_to_this) {
      location->start++;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_string_dynamic_seek_to_

#ifndef _di_fl_string_dynamic_seek_to_utf_character_
  f_return_status fl_string_dynamic_seek_to_utf_character(const f_string_dynamic buffer, f_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = f_none;

    unsigned short width = 0;

    f_string_length width_max = 0;

    while (location->start < buffer.used) {
      width_max = (location->stop - location->start) + 1;

      if (width_max > buffer.used - location->start) {
        width_max = buffer.used - location->start;
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
          status = f_utf_char_to_character(buffer.string + location->start, width_max, &character);

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
#endif // _di_fl_string_dynamic_seek_to_utf_character_

#ifndef _di_fl_string_rip_
  f_return_status fl_string_rip(const f_string string, const f_string_length start, const f_string_length stop, f_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (start > stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_rip(string, start, stop, result);
  }
#endif // _di_fl_string_rip_

#ifndef _di_fl_string_rip_trim_
  f_return_status fl_string_rip_trim(const f_string string, const f_string_length start, const f_string_length stop, f_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (start > stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_rip_trim(string, start, stop, result);
  }
#endif // _di_fl_string_rip_trim_

#ifndef _di_fl_string_seek_line_to_
  f_return_status fl_string_seek_line_to(const f_string string, f_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (string[location->start] != seek_to_this) {
      if (string[location->start] == f_string_eol) return f_none_on_eol;

      location->start++;

      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_string_seek_line_to_

#ifndef _di_fl_string_seek_line_to_utf_character_
  f_return_status fl_string_seek_line_to_utf_character(const f_string string, f_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = f_none;

    unsigned short width = 0;

    f_string_length width_max = (location->stop - location->start) + 1;

    for (; location->start <= location->stop; location->start += width) {
      width_max = (location->stop - location->start) + 1;

      width = f_macro_utf_byte_width_is(string[location->start]);

      if (width == 0) {
        width = 1;

        if (string[location->start] == f_string_eol) return f_none_on_eol;

        if (seek_width == width) {
          if (string[location->start] == seek_to_this) return f_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_eos);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(string + location->start, width_max, &character);

          if (f_status_is_error(status)) {
            return status;
          }

          if (character == seek_to_this) {
            return f_none;
          }
        }
      }
    } // for

    return f_none_on_stop;
  }
#endif // _di_fl_string_seek_line_to_utf_character_

#ifndef _di_fl_string_seek_line_until_graph_
  f_return_status fl_string_seek_line_until_graph(const f_string string, f_string_location *location, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length width_max = (location->stop - location->start) + 1;

    while (string[location->start] == placeholder || (status = f_utf_is_graph(string + location->start, width_max)) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (string[location->start] == f_string_eol) return f_none_on_eol;

      width = f_macro_utf_byte_width_is(string[location->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      location->start += width;

      if (location->start > location->stop) return f_none_on_stop;

      width_max = (location->stop - location->start) + 1;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_string_seek_line_until_graph_

#ifndef _di_fl_string_seek_line_until_non_graph_
  f_return_status fl_string_seek_line_until_non_graph(const f_string string, f_string_location *location, const int8_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length width_max = (location->stop - location->start) + 1;

    while (string[location->start] == placeholder || (status = f_utf_is_whitespace(string + location->start, width_max)) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (string[location->start] == f_string_eol) return f_none_on_eol;

      width = f_macro_utf_byte_width_is(string[location->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      location->start += width;

      if (location->start > location->stop) return f_none_on_stop;

      width_max = (location->stop - location->start) + 1;
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_string_seek_line_until_non_graph_

#ifndef _di_fl_string_seek_to_
  f_return_status fl_string_seek_to(const f_string string, f_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (string[location->start] != seek_to_this) {
      location->start++;

      if (location->start > location->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_string_seek_to_

#ifndef _di_fl_string_seek_to_utf_character_
  f_return_status fl_string_seek_to_utf_character(const f_string string, f_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    const unsigned short seek_width = f_macro_utf_character_width(seek_to_this);

    f_status status = f_none;

    unsigned short width = 0;

    f_string_length width_max = 0;

    for (; location->start <= location->stop; location->start += width) {
      width_max = (location->stop - location->start) + 1;

      width = f_macro_utf_byte_width_is(string[location->start]);

      if (width == 0) {
        width = 1;

        if (seek_width == width) {
          if (string[location->start] == seek_to_this) return f_none;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);

        if (width == seek_width) {
          f_utf_character character = 0;
          status = f_utf_char_to_character(string + location->start, width_max, &character);

          if (f_status_is_error(status)) {
            return status;
          }

          if (character == seek_to_this) {
            return f_none;
          }
        }
      }
    } // for

    return f_none_on_stop;
  }
#endif // _di_fl_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

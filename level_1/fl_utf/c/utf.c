#include <level_1/utf.h>
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_string_compare_
  f_return_status fl_utf_string_compare(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_status_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_

#ifndef _di_fl_utf_string_compare_trim_
  f_return_status fl_utf_string_compare_trim(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_status_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_trim_

#ifndef _di_fl_utf_string_dynamic_compare_
  f_return_status fl_utf_string_dynamic_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_utf_string_dynamic_compare_

#ifndef _di_f_utf_string_dynamic_compare_trim_
  f_return_status f_utf_string_dynamic_compare_trim(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_utf_string_dynamic_compare_trim_

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

    return private_fl_utf_string_compare(string1.string, string2.string, offset1.start, offset2.start, offset1.stop + 1, offset2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifndef _di_fl_string_dynamic_partial_compare_trim_
  f_return_status fl_utf_string_dynamic_partial_comparetrim(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2, const f_utf_string_location offset1, const f_utf_string_location offset2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_status_set_error(f_invalid_parameter);

      if (offset1.start > offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (offset2.start > offset2.stop) return f_status_set_error(f_invalid_parameter);

      if (string1.used <= offset1.stop) return f_status_set_error(f_invalid_parameter);
      if (string2.used <= offset2.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1.string, string2.string, offset1.start, offset2.start, offset1.stop + 1, offset2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_comparetrim_

#ifndef _di_fl_utf_string_dynamic_rip_
  f_return_status fl_utf_string_dynamic_rip(const f_utf_string_dynamic buffer, const f_utf_string_location location, f_utf_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_rip(buffer.string, location.start, location.stop, result);
  }
#endif // _di_fl_utf_string_dynamic_rip_

#ifndef _di_fl_utf_string_dynamic_rip_trim_
  f_return_status fl_utf_string_dynamic_rip_trim(const f_utf_string_dynamic buffer, const f_utf_string_location location, f_utf_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_rip_trim(buffer.string, location.start, location.stop, result);
  }
#endif // _di_fl_utf_string_dynamic_rip_trim_

#ifndef _di_fl_utf_string_dynamic_seek_line_to_
  f_return_status fl_utf_string_dynamic_seek_line_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= location->stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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

#ifndef _di_fl_utf_string_rip_
  f_return_status fl_utf_string_rip(const f_utf_string string, const f_string_length start, const f_string_length stop, f_utf_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (start > stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_rip(string, start, stop, result);
  }
#endif // _di_fl_utf_string_rip_

#ifndef _di_fl_utf_string_rip_trim_
  f_return_status fl_utf_string_rip_trim(const f_utf_string string, const f_string_length start, const f_string_length stop, f_utf_string_dynamic *result) {
    #ifndef _di_level_1_parameter_checking_
      if (start > stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_rip_trim(string, start, stop, result);
  }
#endif // _di_fl_utf_string_rip_trim_

#ifndef _di_fl_utf_string_seek_line_to_
  f_return_status fl_utf_string_seek_line_to(const f_utf_string string, f_utf_string_location *location, const f_utf_character seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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
#endif // _di_fl_string_seek_to_

#ifndef _di_fl_utf_string_seek_to_char_
  f_return_status fl_utf_string_seek_to_char(const f_utf_string string, f_utf_string_location *location, const int8_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

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

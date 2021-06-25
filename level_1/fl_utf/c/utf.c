#include "utf.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_string_compare_
  f_status_t fl_utf_string_compare(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2) {
    return private_fl_utf_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_

#ifndef _di_fl_utf_string_compare_trim_
  f_status_t fl_utf_string_compare_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2) {
    return private_fl_utf_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_utf_string_compare_trim_

#ifndef _di_fl_utf_string_dynamic_compare_
  f_status_t fl_utf_string_dynamic_compare(const f_utf_string_static_t string1, const f_utf_string_static_t string2) {
    return private_fl_utf_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_utf_string_dynamic_compare_

#ifndef _di_fl_utf_string_dynamic_compare_trim_
  f_status_t fl_utf_string_dynamic_compare_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2) {
    return private_fl_utf_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_utf_string_dynamic_compare_trim_

#ifndef _di_fl_utf_string_dynamic_partial_compare_
  f_status_t fl_utf_string_dynamic_partial_compare(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_utf_string_dynamic_partial_compare_

#ifndef _di_fl_utf_string_dynamic_partial_compare_trim_
  f_status_t fl_utf_string_dynamic_partial_compare_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_utf_string_compare_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_utf_string_dynamic_partial_compare_trim_

#ifndef _di_fl_utf_string_dynamic_rip_
  f_status_t fl_utf_string_dynamic_rip(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_rip_

#ifndef _di_fl_utf_string_dynamic_rip_nulless_
  f_status_t fl_utf_string_dynamic_rip_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_fl_utf_string_dynamic_rip_nulless_

#ifndef _di_fl_utf_string_dynamic_seek_line_to_char_
  f_status_t fl_utf_string_dynamic_seek_line_to_char(const f_utf_string_static_t buffer, f_string_range_t *range, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not_eos;
    }

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_utf_character_t seek_to_character = seek_to_this << 24;

    if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_character) {

      if (buffer.string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      ++range->start;

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) {
        return F_none_eos;
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_to_char_

#ifndef _di_fl_utf_string_dynamic_seek_line_until_graph_
  f_status_t fl_utf_string_dynamic_seek_line_until_graph(const f_utf_string_static_t buffer, f_string_range_t *range, const f_utf_character_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not_eos;
    }

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_status_t status = F_none;

    if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_character_is_graph(buffer.string[range->start])) == F_false) {

      if (F_status_is_error(status)) {
        return status;
      }

      if (buffer.string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      ++range->start;

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) {
        return F_none_eos;
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_until_graph_

#ifndef _di_fl_utf_string_dynamic_seek_line_until_graph_non_
  f_status_t fl_utf_string_dynamic_seek_line_until_graph_non(const f_utf_string_static_t buffer, f_string_range_t *range, const f_utf_character_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;

    if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_character_is_whitespace(buffer.string[range->start])) == F_false) {

      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_utf_character_t_eol) return F_none_eol;

      ++range->start;

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_line_until_graph_non_

#ifndef _di_fl_utf_string_dynamic_seek_to_char_
  f_status_t fl_utf_string_dynamic_seek_to_char(const f_utf_string_static_t buffer, f_string_range_t *range, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not_eos;
    }

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_utf_character_t seek_to_character = seek_to_this << 24;

    if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (buffer.string[range->start] != seek_to_character) {

      ++range->start;

      if (macro_f_utf_character_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start >= buffer.used) {
        return F_none_eos;
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    return F_none;
  }
#endif // _di_fl_utf_string_dynamic_seek_to_char_

#ifndef _di_fl_utf_string_rip_
  f_status_t fl_utf_string_rip(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) {
      return F_data_not_eos;
    }

    f_array_length_t begin = 0;
    f_array_length_t end = length - 1;

    f_status_t status = private_fl_utf_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_data_not) {
      return status;
    }

    return f_utf_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_utf_string_rip_

#ifndef _di_fl_utf_string_rip_nulless_
  f_status_t fl_utf_string_rip_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) {
      return F_data_not_eos;
    }

    f_array_length_t begin = 0;
    f_array_length_t end = length - 1;

    f_status_t status = private_fl_utf_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_data_not) {
      return status;
    }

    return f_utf_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_utf_string_rip_nulless_

#ifndef _di_fl_utf_string_seek_line_to_char_
  f_status_t fl_utf_string_seek_line_to_char(const f_utf_string_t string, f_string_range_t *range, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_utf_character_t seek_to_character = seek_to_this << 24;

    for (; range->start <= range->stop; ++range->start) {

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      if (string[range->start] == seek_to_character) {
        return F_none;
      }
    } // for

    return F_none_stop;
  }
#endif // _di_fl_utf_string_seek_line_to_char_

#ifndef _di_fl_utf_string_seek_line_until_graph_
  f_status_t fl_utf_string_seek_line_until_graph(const f_utf_string_t string, f_string_range_t *range, const f_utf_character_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_status_t status = F_none;

    if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] == placeholder || (status = f_utf_character_is_graph(string[range->start])) == F_false) {

      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      ++range->start;

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_fl_utf_string_seek_line_until_graph_

#ifndef _di_fl_utf_string_seek_line_until_graph_non_
  f_status_t fl_utf_string_seek_line_until_graph_non(const f_utf_string_t string, f_string_range_t *range, const f_utf_character_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_status_t status = F_none;

    if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (string[range->start] == placeholder || (status = f_utf_character_is_graph(string[range->start])) == F_true) {

      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start] == f_utf_character_t_eol) {
        return F_none_eol;
      }

      ++range->start;

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }
    } // while

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_fl_utf_string_seek_line_until_graph_non_

#ifndef _di_fl_utf_string_seek_to_char_
  f_status_t fl_utf_string_seek_to_char(const f_utf_string_t string, f_string_range_t *range, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const f_utf_character_t seek_to_character = seek_to_this << 24;

    if (macro_f_utf_character_t_width_is(string[0]) == 1) {
      return F_status_set_error(F_utf);
    }

    while (range->start <= range->stop) {

      if (string[range->start] == seek_to_character) {
        return F_none;
      }

      ++range->start;

      if (macro_f_utf_character_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf);
      }
    } // while

    return F_none_stop;
  }
#endif // _di_fl_utf_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

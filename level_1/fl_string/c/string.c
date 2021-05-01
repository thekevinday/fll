#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_string_compare_
  f_status_t fl_string_compare(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2) {
    return private_fl_string_compare(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_

#ifndef _di_fl_string_compare_except_
  f_status_t fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    return private_fl_string_compare_except(string1, string2, 0, 0, length1, length2, except1, except2);
  }
#endif // _di_fl_string_compare_except_

#ifndef _di_fl_string_compare_except_trim_
  f_status_t fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    return private_fl_string_compare_except_trim(string1, string2, 0, 0, length1, length2, except1, except2);
  }
#endif // _di_fl_string_compare_except_trim_

#ifndef _di_fl_string_compare_trim_
  f_status_t fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2) {
    return private_fl_string_compare_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_fl_string_compare_trim_

#ifndef _di_fl_string_dynamic_compare_
  f_status_t fl_string_dynamic_compare(const f_string_static_t string1, const f_string_static_t string2) {
    return private_fl_string_compare(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_

#ifndef _di_fl_string_dynamic_compare_except_
  f_status_t fl_string_dynamic_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    return private_fl_string_compare_except(string1.string, string2.string, 0, 0, string1.used, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_

#ifndef _di_fl_string_dynamic_compare_except_string_
  f_status_t fl_string_dynamic_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    return private_fl_string_compare_except(string1, string2.string, 0, 0, length1, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_string_

#ifndef _di_fl_string_dynamic_compare_except_trim_
  f_status_t fl_string_dynamic_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    return private_fl_string_compare_except_trim(string1.string, string2.string, 0, 0, string1.used, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_trim_

#ifndef _di_fl_string_dynamic_compare_except_trim_string_
  f_status_t fl_string_dynamic_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    return private_fl_string_compare_except_trim(string1, string2.string, 0, 0, length1, string2.used, except1, except2);
  }
#endif // _di_fl_string_dynamic_compare_except_trim_string_

#ifndef _di_fl_string_dynamic_compare_string_
  f_status_t fl_string_dynamic_compare_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1) {
    return private_fl_string_compare(string1, string2.string, 0, 0, length1, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_string_

#ifndef _di_fl_string_dynamic_compare_trim_
  f_status_t fl_string_dynamic_compare_trim(const f_string_static_t string1, const f_string_static_t string2) {
    return private_fl_string_compare_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_trim_

#ifndef _di_fl_string_dynamic_compare_trim_string_
  f_status_t fl_string_dynamic_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1) {
    return private_fl_string_compare_trim(string1, string2.string, 0, 0, length1, string2.used);
  }
#endif // _di_fl_string_dynamic_compare_trim_string_

#ifndef _di_fl_string_dynamic_partial_compare_
  f_status_t fl_string_dynamic_partial_compare(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_

#ifndef _di_fl_string_dynamic_partial_compare_dynamic_
  f_status_t fl_string_dynamic_partial_compare_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_string_
  f_status_t fl_string_dynamic_partial_compare_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare(string1, string2.string, 0, range2.start, length1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_string_

#ifndef _di_fl_string_dynamic_partial_compare_except_
  f_status_t fl_string_dynamic_partial_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_

#ifndef _di_fl_string_dynamic_partial_compare_except_dynamic_
  f_status_t fl_string_dynamic_partial_compare_except_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_except_string_
  f_status_t fl_string_dynamic_partial_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except(string1, string2.string, 0, range2.start, length1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_string_

#ifndef _di_fl_string_dynamic_partial_compare_except_trim_
  f_status_t fl_string_dynamic_partial_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_trim_

#ifndef _di_fl_string_dynamic_partial_compare_except_trim_dynamic_
  f_status_t fl_string_dynamic_partial_compare_except_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except_trim(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_trim_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_except_trim_string_
  f_status_t fl_string_dynamic_partial_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_except_trim(string1, string2.string, 0, range2.start, length1, range2.stop + 1, except1, except2);
  }
#endif // _di_fl_string_dynamic_partial_compare_except_trim_string_

#ifndef _di_fl_string_dynamic_partial_compare_trim_
  f_status_t fl_string_dynamic_partial_compare_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_

#ifndef _di_fl_string_dynamic_partial_compare_trim_dynamic_
  f_status_t fl_string_dynamic_partial_compare_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1.string, string2.string, 0, range2.start, string1.used, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_dynamic_

#ifndef _di_fl_string_dynamic_partial_compare_trim_string_
  f_status_t fl_string_dynamic_partial_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2) {
    #ifndef _di_level_1_parameter_checking_
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_string_compare_trim(string1, string2.string, 0, range2.start, length1, range2.stop + 1);
  }
#endif // _di_fl_string_dynamic_partial_compare_trim_string_

#ifndef _di_fl_string_dynamic_rip_
  f_status_t fl_string_dynamic_rip(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    f_array_length_t begin = range.start;
    f_array_length_t end = range.stop;

    const f_status_t status = private_fl_string_rip_find_range(source.string, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return f_string_append(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_dynamic_rip_

#ifndef _di_fl_string_dynamic_rip_nulless_
  f_status_t fl_string_dynamic_rip_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not_eos;

    f_array_length_t begin = range.start;
    f_array_length_t end = range.stop;

    const f_status_t status = private_fl_string_rip_find_range(source.string, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    return f_string_append_nulless(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_dynamic_rip_nulless_

#ifndef _di_fl_string_dynamic_seek_line_to_utf_character_
  f_status_t fl_string_dynamic_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = macro_f_utf_character_t_width(seek_to_this);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_array_length_t width_max = 0;

    while (range->start <= range->stop) {
      width_max = (range->stop - range->start) + 1;
      width = macro_f_utf_byte_width_is(string[range->start]);

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
  f_status_t fl_string_dynamic_seek_line_until_graph(const f_string_t string, const uint8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_graph(string + range->start, width_max)) == F_false) {

      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = macro_f_utf_byte_width_is(string[range->start]);

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

#ifndef _di_fl_string_dynamic_seek_line_until_graph_non_
  f_status_t fl_string_dynamic_seek_line_until_graph_non(const f_string_t string, const uint8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_whitespace(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = macro_f_utf_byte_width_is(string[range->start]);

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
#endif // _di_fl_string_dynamic_seek_line_until_graph_non_

#ifndef _di_fl_string_dynamic_seek_to_utf_character_
  f_status_t fl_string_dynamic_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = macro_f_utf_character_t_width(seek_to_this);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_array_length_t width_max = 0;

    while (range->start <= range->stop) {
      width_max = (range->stop - range->start) + 1;
      width = macro_f_utf_byte_width_is(string[range->start]);

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

#ifndef _di_fl_string_rip_
  f_status_t fl_string_rip(const f_string_t source, const f_array_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    f_array_length_t begin = 0;
    f_array_length_t end = length - 1;

    const f_status_t status = private_fl_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return f_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_rip_

#ifndef _di_fl_string_rip_nulless_
  f_status_t fl_string_rip_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not_eos;

    f_array_length_t begin = 0;
    f_array_length_t end = length - 1;

    const f_status_t status = private_fl_string_rip_find_range(source, &begin, &end);

    if (F_status_is_error(status)) return status;
    if (status == F_data_not) return status;

    return f_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_fl_string_rip_nulless_

#ifndef _di_fl_string_seek_line_to_utf_character_
  f_status_t fl_string_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = macro_f_utf_character_t_width(seek_to);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;

    for (; range->start <= range->stop; range->start += width) {
      width_max = (range->stop - range->start) + 1;

      width = macro_f_utf_byte_width_is(string[range->start]);

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
  f_status_t fl_string_seek_line_until_graph(const f_string_t string, const uint8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_graph(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = macro_f_utf_byte_width_is(string[range->start]);

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

#ifndef _di_fl_string_seek_line_until_graph_non_
  f_status_t fl_string_seek_line_until_graph_non(const f_string_t string, const uint8_t placeholder, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_none;
    unsigned short width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_whitespace(string + range->start, width_max)) == F_false) {
      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start] == f_string_eol_s[0]) return F_none_eol;

      width = macro_f_utf_byte_width_is(string[range->start]);

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
#endif // _di_fl_string_seek_line_until_graph_non_

#ifndef _di_fl_string_seek_to_utf_character_
  f_status_t fl_string_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = macro_f_utf_character_t_width(seek_to);

    f_status_t status = F_none;

    unsigned short width = 0;

    f_array_length_t width_max = 0;

    for (; range->start <= range->stop; range->start += width) {
      width_max = (range->stop - range->start) + 1;

      width = macro_f_utf_byte_width_is(string[range->start]);

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

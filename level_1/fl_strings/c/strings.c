#include <level_1/strings.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_rip_string_
  f_return_status fl_rip_string(const f_dynamic_string buffer, const f_string_location position, f_dynamic_string *results) {
    #ifndef _di_level_1_parameter_checking_
      if (results == 0) return f_error_set_error(f_invalid_parameter);
      if (position.start < 0) return f_error_set_error(f_invalid_parameter);
      if (position.stop < position.start) return f_error_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_error_set_error(f_invalid_parameter);
      if (position.start >= buffer.used) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    // the start and stop point are inclusive locations, and therefore start - stop is actually 1 too few locations
    f_string_length size = position.stop - position.start + 1;

    if (size > 0) {
      f_status status = f_none;

      f_resize_dynamic_string(status, (*results), size);

      if (f_error_is_error(status)) {
        return status;
      }

      memcpy(results->string, buffer.string + position.start, sizeof(char) * size);
      results->used = size;

      return f_none;
    }

    return f_no_data;
  }
#endif // _di_fl_rip_string_

#ifndef _di_fl_seek_line_past_non_graph_
  f_return_status fl_seek_line_past_non_graph(const f_dynamic_string buffer, f_string_location *position, const char placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (position == 0) return f_error_set_error(f_invalid_parameter);
      if (position->start < 0) return f_error_set_error(f_invalid_parameter);
      if (position->stop < position->start) return f_error_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_error_set_error(f_invalid_parameter);
      if (position->start >= buffer.used) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (!isgraph(buffer.string[position->start]) || buffer.string[position->start] == placeholder) {
      if (buffer.string[position->start] == f_eol) return f_none;

      ++position->start;

      if (position->start >= buffer.used) return f_none_on_eos;
      if (position->start > position->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_seek_line_past_non_graph_

#ifndef _di_fl_seek_line_until_non_graph_
  f_return_status fl_seek_line_until_non_graph(const f_dynamic_string buffer, f_string_location *position, const char placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (position->start < 0) return f_error_set_error(f_invalid_parameter);
      if (position->stop < position->start) return f_error_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_error_set_error(f_invalid_parameter);
      if (position->start >= buffer.used) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (isgraph(buffer.string[position->start]) || buffer.string[position->start] == placeholder) {
      if (buffer.string[position->start] == f_eol) return f_none;

      ++position->start;

      if (position->start >= buffer.used) return f_none_on_eos;
      if (position->start > position->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_seek_line_until_non_graph_

#ifndef _di_fl_seek_to_
  f_return_status fl_seek_to(const f_dynamic_string buffer, f_string_location *position, const char seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (position->start < 0) return f_error_set_error(f_invalid_parameter);
      if (position->stop < position->start) return f_error_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_error_set_error(f_invalid_parameter);
      if (position->start >= buffer.used) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    while (buffer.string[position->start] != seek_to_this) {
      if (buffer.string[position->start] == f_eol) return f_none;

      ++position->start;

      if (position->start >= buffer.used) return f_none_on_eos;
      if (position->start > position->stop) return f_none_on_stop;
    } // while

    return f_none;
  }
#endif // _di_fl_seek_to_

#ifndef _di_fl_compare_strings_
  f_return_status fl_compare_strings(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2) {
    #ifndef _di_level_1_parameter_checking_
      if (length1 <= 0) return f_error_set_error(f_invalid_parameter);
      if (length2 <= 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i1 = 0;
    f_string_length i2 = 0;

    f_string_length stop1 = length1;
    f_string_length stop2 = length2;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      while (i1 < stop1 && string1[i1] == f_eos) i1++;
      while (i2 < stop2 && string2[i2] == f_eos) i2++;

      if (string1[i1] != string2[i2]) return f_not_equal_to;
    } // for()

    while (i1 < stop1) {
      if (string1[i1] != f_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < stop2) {
      if (string2[i2] != f_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_compare_strings_

#ifndef _di_fl_compare_dynamic_strings_
  f_return_status fl_compare_dynamic_strings(const f_dynamic_string string1, const f_dynamic_string string2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_error_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i1 = 0;
    f_string_length i2 = 0;

    f_string_length stop1 = string1.used;
    f_string_length stop2 = string2.used;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      while (i1 < stop1 && string1.string[i1] == f_eos) i1++;
      while (i2 < stop2 && string2.string[i2] == f_eos) i2++;

      if (string1.string[i1] != string2.string[i2]) return f_not_equal_to;
    } // for()

    while (i1 < stop1) {
      if (string1.string[i1] != f_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < stop2) {
      if (string2.string[i2] != f_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_compare_dynamic_strings_

#ifndef _di_fl_compare_partial_dynamic_strings_
  f_return_status fl_compare_partial_dynamic_strings(const f_dynamic_string string1, const f_dynamic_string string2, const f_string_location offset1, const f_string_location offset2) {
    #ifndef _di_level_1_parameter_checking_
      if (string1.used <= 0) return f_error_set_error(f_invalid_parameter);
      if (string2.used <= 0) return f_error_set_error(f_invalid_parameter);

      if (offset1.start > offset1.stop) return f_error_set_error(f_invalid_parameter);
      if (offset2.start > offset2.stop) return f_error_set_error(f_invalid_parameter);

      if (string1.used <= offset1.stop) return f_error_set_error(f_invalid_parameter);
      if (string2.used <= offset2.stop) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i1 = offset1.start;
    f_string_length i2 = offset2.start;

    f_string_length stop1 = offset1.stop + 1;
    f_string_length stop2 = offset2.stop + 1;

    for (; i1 < stop1 && i2 < stop2; i1++, i2++) {
      while (i1 < stop1 && string1.string[i1] == f_eos) i1++;
      while (i2 < stop2 && string2.string[i2] == f_eos) i2++;

      if (string1.string[i1] != string2.string[i2]) return f_not_equal_to;
    } // for()

    while (i1 < stop1) {
      if (string1.string[i1] != f_eos) return f_not_equal_to;
      i1++;
    } // while

    while (i2 < stop2) {
      if (string2.string[i2] != f_eos) return f_not_equal_to;
      i2++;
    } // while

    return f_equal_to;
  }
#endif // _di_fl_compare_partial_dynamic_strings_

#ifdef __cplusplus
} // extern "C"
#endif

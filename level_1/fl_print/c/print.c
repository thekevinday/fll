#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_print_trim_except_
  f_status_t fl_print_trim_except(FILE *output, const f_string_t string, const f_array_length_t length, const f_array_lengths_t except) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except(output, string, 0, length, except);
  }
#endif // _di_fl_print_trim_except_

#ifndef _di_fl_print_trim_except_dynamic_
  f_status_t fl_print_trim_except_dynamic(FILE *output, const f_string_static_t buffer, const f_array_lengths_t except) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except(output, buffer.string, 0, buffer.used, except);
  }
#endif // _di_fl_print_trim_except_dynamic_

#ifndef _di_fl_print_trim_except_dynamic_partial_
  f_status_t fl_print_trim_except_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except(output, buffer.string, range.start, range.start + length, except);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_

#ifndef _di_fl_print_trim_except_utf_
  f_status_t fl_print_trim_except_utf(FILE *output, const f_utf_string_t string, const f_array_length_t length, const f_array_lengths_t except) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_utf(output, string, 0, length, except);
  }
#endif // _di_fl_print_trim_except_utf_

#ifndef _di_fl_print_trim_except_utf_dynamic_
  f_status_t fl_print_trim_except_utf_dynamic(FILE *output, const f_utf_string_static_t buffer, const f_array_lengths_t except) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_utf(output, buffer.string, 0, buffer.used, except);
  }
#endif // _di_fl_print_trim_except_utf_dynamic_

#ifndef _di_fl_print_trim_except_utf_dynamic_partial_
  f_status_t fl_print_trim_except_utf_dynamic_partial(FILE *output, const f_utf_string_static_t buffer, const f_utf_string_range_t range, const f_array_lengths_t except) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_utf(output, buffer.string, range.start, range.start + length, except);
  }
#endif // _di_fl_print_trim_except_utf_dynamic_partial_

#ifndef _di_fl_print_trim_
  f_status_t fl_print_trim(FILE *output, const f_string_t string, const f_array_length_t length) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim(output, string, length);
  }
#endif // _di_fl_print_trim_

#ifndef _di_fl_print_trim_dynamic_
  f_status_t fl_print_trim_dynamic(FILE *output, const f_string_static_t buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim(output, buffer.string, buffer.used);
  }
#endif // _di_fl_print_trim_dynamic_

#ifndef _di_fl_print_trim_dynamic_partial_
  f_status_t fl_print_trim_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim(output, buffer.string + range.start, length);
  }
#endif // _di_fl_print_trim_dynamic_partial_

#ifndef _di_fl_print_trim_utf_
  f_status_t fl_print_trim_utf(FILE *output, const f_utf_string_t string, const f_array_length_t length) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_utf(output, string, length);
  }
#endif // _di_fl_print_trim_utf_

#ifndef _di_fl_print_trim_utf_dynamic_
  f_status_t fl_print_trim_utf_dynamic(FILE *output, const f_utf_string_static_t buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_utf(output, buffer.string, buffer.used);
  }
#endif // _di_fl_print_trim_utf_dynamic_

#ifndef _di_fl_print_trim_utf_dynamic_partial_
  f_status_t fl_print_trim_utf_dynamic_partial(FILE *output, const f_utf_string_static_t buffer, const f_utf_string_range_t range) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_utf(output, buffer.string + range.start, length);
  }
#endif // _di_fl_print_trim_utf_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif

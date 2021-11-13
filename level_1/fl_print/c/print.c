#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_print_format_
  f_status_t fl_print_format(const f_string_t string, FILE *stream, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return 0;
      if (!stream) return 0;
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    va_list ap;

    va_start(ap, stream);

    for (f_string_t current = string; *current; current += 1) {

      if (*current == f_string_ascii_percent_s[0]) {
        current += 1;

        current = private_fl_print_format_convert(current, stream, &ap, &status);
        if (F_status_is_error(status)) break;
      }
      else {
        if (!fputc_unlocked(*current, stream)) {
          break;
        }
      }
    } // for

    va_end(ap);

    return status;
  }
#endif // _di_fl_print_format_

#ifndef _di_fl_print_format_convert_
  f_string_t fl_print_format_convert(const f_string_t string, FILE *stream, va_list *ap, f_status_t *status) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return 0;
      if (!ap) return 0;
    #endif // _di_level_1_parameter_checking_

    return private_fl_print_format_convert(string, stream, ap, status);
  }
#endif // _di_fl_print_format_convert_

#ifndef _di_fl_print_string_va_
  f_status_t fl_print_string_va(const f_string_t string, FILE *stream, va_list *ap) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return 0;
      if (!stream) return 0;
      if (!ap) return 0;
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    for (f_string_t current = string; *current; current += 1) {

      if (*current == f_string_ascii_percent_s[0]) {
        current += 1;

        current = private_fl_print_format_convert(current, stream, ap, &status);
        if (F_status_is_error(status)) break;
      }
      else {
        if (!fputc_unlocked(*current, stream)) {
          break;
        }
      }
    } // for

    return status;
  }
#endif // _di_fl_print_string_va_

#ifndef _di_fl_print_trim_
  f_status_t fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim(string, length, stream);
  }
#endif // _di_fl_print_trim_

#ifndef _di_fl_print_trim_raw_
  f_status_t fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_raw(string, length, stream);
  }
#endif // _di_fl_print_trim_raw_

#ifndef _di_fl_print_trim_safely_
  f_status_t fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_safely(string, length, stream);
  }
#endif // _di_fl_print_trim_safely_

#ifndef _di_fl_print_trim_dynamic_
  f_status_t fl_print_trim_dynamic(const f_string_static_t buffer, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim(buffer.string, buffer.used, stream);
  }
#endif // _di_fl_print_trim_dynamic_

#ifndef _di_fl_print_trim_dynamic_raw_
  f_status_t fl_print_trim_dynamic_raw(const f_string_static_t buffer, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_raw(buffer.string, buffer.used, stream);
  }
#endif // _di_fl_print_trim_dynamic_raw_

#ifndef _di_fl_print_trim_dynamic_safely_
  f_status_t fl_print_trim_dynamic_safely(const f_string_static_t buffer, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_safely(buffer.string, buffer.used, stream);
  }
#endif // _di_fl_print_trim_dynamic_safely_

#ifndef _di_fl_print_trim_dynamic_partial_
  f_status_t fl_print_trim_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim(buffer.string + range.start, length, stream);
  }
#endif // _di_fl_print_trim_dynamic_partial_

#ifndef _di_fl_print_trim_dynamic_partial_raw_
  f_status_t fl_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_raw(buffer.string + range.start, length, stream);
  }
#endif // _di_fl_print_trim_dynamic_partial_raw_

#ifndef _di_fl_print_trim_dynamic_partial_safely_
  f_status_t fl_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_safely(buffer.string + range.start, length, stream);
  }
#endif // _di_fl_print_trim_dynamic_partial_safely_

#ifndef _di_fl_print_trim_except_
  f_status_t fl_print_trim_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in(string, offset, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_

#ifndef _di_fl_print_trim_except_raw_
  f_status_t fl_print_trim_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(string, offset, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_raw_

#ifndef _di_fl_print_trim_except_safely_
  f_status_t fl_print_trim_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(string, offset, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_safely_

#ifndef _di_fl_print_trim_except_dynamic_
  f_status_t fl_print_trim_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in(buffer.string, 0, buffer.used, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_dynamic_

#ifndef _di_fl_print_trim_except_dynamic_raw_
  f_status_t fl_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(buffer.string, 0, buffer.used, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_dynamic_raw_

#ifndef _di_fl_print_trim_except_dynamic_safely_
  f_status_t fl_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(buffer.string, 0, buffer.used, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_dynamic_safely_

#ifndef _di_fl_print_trim_except_in_
  f_status_t fl_print_trim_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in(string, offset, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_

#ifndef _di_fl_print_trim_except_in_raw_
  f_status_t fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_raw(string, offset, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_raw_

#ifndef _di_fl_print_trim_except_in_safely_
  f_status_t fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_safely(string, offset, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_
  f_status_t fl_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in(buffer.string, 0, buffer.used, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_dynamic_

#ifndef _di_fl_print_trim_except_in_dynamic_raw_
  f_status_t fl_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_raw(buffer.string, 0, buffer.used, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_dynamic_raw_

#ifndef _di_fl_print_trim_except_in_dynamic_safely_
  f_status_t fl_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_safely(buffer.string, 0, buffer.used, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_dynamic_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_
  f_status_t fl_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in(buffer.string, range.start, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_raw_
  f_status_t fl_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_raw(buffer.string, range.start, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_raw_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_safely_
  f_status_t fl_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_safely(buffer.string, range.start, length, except_at, except_in, stream);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_safely_

#ifndef _di_fl_print_trim_except_dynamic_partial_
  f_status_t fl_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in(buffer.string, range.start, length, except, except_in, stream);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_

#ifndef _di_fl_print_trim_except_dynamic_partial_raw_
  f_status_t fl_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(buffer.string, range.start, length, except, except_in, stream);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_raw_

#ifndef _di_fl_print_trim_except_dynamic_partial_safely_
  f_status_t fl_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *stream) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(buffer.string, range.start, length, except, except_in, stream);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

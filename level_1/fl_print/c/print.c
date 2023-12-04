#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_print_format_
  f_status_t fl_print_format(const f_string_t string, const f_file_t file, ...) {

    if (!file.stream) return F_stream_not;
    if (!string) return F_data_not;

    f_status_t status = F_okay;

    va_list ap;

    va_start(ap, file);

    private_fl_print_format_convert(string, file, ap, &status);

    va_end(ap);

    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_fl_print_format_

#ifndef _di_fl_print_format_convert_
  f_string_t fl_print_format_convert(const f_string_t string, const f_file_t file, va_list ap, f_status_t * const status) {

    if (!file.stream) {
      if (status) *status = F_stream_not;

      return 0;
    }

    if (!string) {
      if (status) *status = F_data_not;

      return 0;
    }

    if (status) {
      return private_fl_print_format_convert(string, file, ap, status);
    }

    f_status_t status_local = F_okay;

    return private_fl_print_format_convert(string, file, ap, &status_local);
  }
#endif // _di_fl_print_format_convert_

#ifndef _di_fl_print_string_va_
  f_status_t fl_print_string_va(const f_string_t string, const f_file_t file, va_list ap) {

    if (!file.stream) return F_stream_not;
    if (!string) return F_data_not;

    f_status_t status = F_okay;

    private_fl_print_format_convert(string, file, ap, &status);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_fl_print_string_va_

#ifndef _di_fl_print_trim_
  f_status_t fl_print_trim(const f_string_t string, const f_number_unsigned_t length, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim(string, length, file);
  }
#endif // _di_fl_print_trim_

#ifndef _di_fl_print_trim_raw_
  f_status_t fl_print_trim_raw(const f_string_t string, const f_number_unsigned_t length, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_raw(string, length, file);
  }
#endif // _di_fl_print_trim_raw_

#ifndef _di_fl_print_trim_raw_safely_
  f_status_t fl_print_trim_raw_safely(const f_string_t string, const f_number_unsigned_t length, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_raw_safely(string, length, file);
  }
#endif // _di_fl_print_trim_raw_safely_

#ifndef _di_fl_print_trim_safely_
  f_status_t fl_print_trim_safely(const f_string_t string, const f_number_unsigned_t length, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_safely(string, length, file);
  }
#endif // _di_fl_print_trim_safely_

#ifndef _di_fl_print_trim_dynamic_
  f_status_t fl_print_trim_dynamic(const f_string_static_t buffer, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim(buffer.string, buffer.used, file);
  }
#endif // _di_fl_print_trim_dynamic_

#ifndef _di_fl_print_trim_dynamic_raw_
  f_status_t fl_print_trim_dynamic_raw(const f_string_static_t buffer, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_raw(buffer.string, buffer.used, file);
  }
#endif // _di_fl_print_trim_dynamic_raw_

#ifndef _di_fl_print_trim_dynamic_raw_safely_
  f_status_t fl_print_trim_dynamic_raw_safely(const f_string_static_t buffer, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_raw_safely(buffer.string, buffer.used, file);
  }
#endif // _di_fl_print_trim_dynamic_raw_safely_

#ifndef _di_fl_print_trim_dynamic_safely_
  f_status_t fl_print_trim_dynamic_safely(const f_string_static_t buffer, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_safely(buffer.string, buffer.used, file);
  }
#endif // _di_fl_print_trim_dynamic_safely_

#ifndef _di_fl_print_trim_dynamic_partial_
  f_status_t fl_print_trim_dynamic_partial(const f_string_static_t buffer, const f_range_t range, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim(buffer.string + range.start, length, file);
  }
#endif // _di_fl_print_trim_dynamic_partial_

#ifndef _di_fl_print_trim_dynamic_partial_raw_
  f_status_t fl_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_range_t range, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_raw(buffer.string + range.start, length, file);
  }
#endif // _di_fl_print_trim_dynamic_partial_raw_

#ifndef _di_fl_print_trim_dynamic_partial_raw_safely_
  f_status_t fl_print_trim_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_range_t range, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_raw_safely(buffer.string + range.start, length, file);
  }
#endif // _di_fl_print_trim_dynamic_partial_raw_safely_

#ifndef _di_fl_print_trim_dynamic_partial_safely_
  f_status_t fl_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_range_t range, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_safely(buffer.string + range.start, length, file);
  }
#endif // _di_fl_print_trim_dynamic_partial_safely_

#ifndef _di_fl_print_trim_except_
  f_status_t fl_print_trim_except(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_

#ifndef _di_fl_print_trim_except_raw_
  f_status_t fl_print_trim_except_raw(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_raw_

#ifndef _di_fl_print_trim_except_raw_safely_
  f_status_t fl_print_trim_except_raw_safely(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw_safely(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_raw_safely_

#ifndef _di_fl_print_trim_except_safely_
  f_status_t fl_print_trim_except_safely(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_safely_

#ifndef _di_fl_print_trim_except_dynamic_
  f_status_t fl_print_trim_except_dynamic(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_

#ifndef _di_fl_print_trim_except_dynamic_raw_
  f_status_t fl_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_raw_

#ifndef _di_fl_print_trim_except_dynamic_raw_safely_
  f_status_t fl_print_trim_except_dynamic_raw_safely(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw_safely(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_raw_safely_

#ifndef _di_fl_print_trim_except_dynamic_safely_
  f_status_t fl_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_safely_

#ifndef _di_fl_print_trim_except_in_
  f_status_t fl_print_trim_except_in(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_except_in(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_

#ifndef _di_fl_print_trim_except_in_raw_
  f_status_t fl_print_trim_except_in_raw(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_except_in_raw(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_raw_

#ifndef _di_fl_print_trim_except_in_raw_safely_
  f_status_t fl_print_trim_except_in_raw_safely(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_except_in_raw_safely(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_raw_safely_

#ifndef _di_fl_print_trim_except_in_safely_
  f_status_t fl_print_trim_except_in_safely(const f_string_t string, const f_number_unsigned_t offset, const f_number_unsigned_t length, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!string || !length) return F_data_not;

    return private_fl_print_trim_except_in_safely(string, offset, offset + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_
  f_status_t fl_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_except_in(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_

#ifndef _di_fl_print_trim_except_in_dynamic_raw_
  f_status_t fl_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_except_in_raw(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_raw_

#ifndef _di_fl_print_trim_except_in_dynamic_raw_safely_
  f_status_t fl_print_trim_except_in_dynamic_raw_safely(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_except_in_raw_safely(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_raw_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_safely_
  f_status_t fl_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used) return F_data_not;

    return private_fl_print_trim_except_in_safely(buffer.string, 0, buffer.used, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_
  f_status_t fl_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in(buffer.string, range.start, range.start + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_raw_
  f_status_t fl_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_raw(buffer.string, range.start, range.start + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_raw_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_raw_safely_
  f_status_t fl_print_trim_except_in_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_raw_safely(buffer.string, range.start, range.start + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_raw_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_safely_
  f_status_t fl_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except_at, const f_ranges_t except_in, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_safely(buffer.string, range.start, range.start + length, except_at, except_in, file);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_safely_

#ifndef _di_fl_print_trim_except_dynamic_partial_
  f_status_t fl_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in(buffer.string, range.start, range.start + length, except, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_

#ifndef _di_fl_print_trim_except_dynamic_partial_raw_
  f_status_t fl_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(buffer.string, range.start, range.start + length, except, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_raw_

#ifndef _di_fl_print_trim_except_dynamic_partial_raw_safely_
  f_status_t fl_print_trim_except_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw_safely(buffer.string, range.start, range.start + length, except, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_raw_safely_

#ifndef _di_fl_print_trim_except_dynamic_partial_safely_
  f_status_t fl_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_range_t range, const f_number_unsigneds_t except, const f_file_t file) {

    if (!file.stream) return F_stream_not;
    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) return F_data_not;

    f_number_unsigned_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_ranges_t except_in = f_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(buffer.string, range.start, range.start + length, except, except_in, file);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

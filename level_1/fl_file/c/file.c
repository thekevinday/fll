#include <level_1/file.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_file_read_
  f_return_status fl_file_read(f_file *file, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    const f_number_unsigned bytes_total = file->size_block * file->size_chunk;

    f_status status = f_none;
    f_string_length size = 0;

    size = file->size_block;

    for (;;) {
      if (buffer->used + bytes_total > buffer->size) {
        if (buffer->used + bytes_total > f_string_max_size) return f_status_set_error(f_string_too_large);

        f_macro_string_dynamic_resize(status, (*buffer), buffer->used + bytes_total);

        if (f_status_is_error(status)) return status;
      }

      status = f_file_read(file, buffer);

      if (f_status_is_error(status)) return status;
      if (status == f_none_on_eof) break;

      size += file->size_block;
    } // for

    return status;
  }
#endif // _di_fl_file_read_

#ifndef _di_fl_file_read_position
  f_return_status fl_file_read_position(f_file *file, f_string_dynamic *buffer, const f_file_position position) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (position.buffer_start < 0) return f_status_set_error(f_invalid_parameter);
      if (position.file_start < 0) return f_status_set_error(f_invalid_parameter);
      if (position.total_elements < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;
    bool infinite = f_false;

    f_number_unsigned bytes_total;

    // when total_elements is 0, this means the file read will until EOF is reached.
    if (position.total_elements == 0) {
      infinite = f_true;
      bytes_total = file->size_block * file->size_chunk;
    }
    else {
      bytes_total = position.total_elements * file->size_chunk;
    }

    do {
      if (buffer->used + bytes_total > buffer->size) {
        if (buffer->used + bytes_total > f_string_max_size) return f_status_set_error(f_string_too_large);

        f_macro_string_dynamic_resize(status, (*buffer), buffer->used + bytes_total);

        if (f_status_is_error(status)) return status;
      }

      status = f_file_read_at(file, buffer, position);

      if (f_status_is_error(status)) return status;
      if (status == f_none_on_eof) break;
    } while (infinite);

    return status;
  }
#endif // _di_fl_file_read_position

#ifndef _di_fl_file_write_
  f_return_status fl_file_write(f_file *file, const f_string_dynamic buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    size_t size = 0;

    size = fwrite(buffer.string, file->size_chunk, buffer.used, file->address);

    if (size < buffer.used * file->size_chunk) return f_status_set_error(f_file_error_write);

    return f_none;
  }
#endif // _di_fl_file_write_

#ifndef _di_fl_file_write_position_
  f_return_status fl_file_write_position(f_file *file, const f_string_dynamic buffer, const f_string_location position) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (position.start < position.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_file_not_open;

    size_t size = 0;

    f_string_length total = buffer.used - (position.stop - position.start + 1);

    size = fwrite(buffer.string + position.start, file->size_chunk, total, file->address);

    if (size < total * file->size_chunk) return f_status_set_error(f_file_error_write);

    return f_none;
  }
#endif // _di_fl_file_write_position_

#ifdef __cplusplus
} // extern "C"
#endif

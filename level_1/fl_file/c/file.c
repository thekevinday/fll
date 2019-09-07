#include <level_1/file.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_file_read_
  f_return_status fl_file_read(f_file file, const f_file_position position, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);

      if (position.buffer_start < 0) return f_status_set_error(f_invalid_parameter);
      if (position.file_start < 0) return f_status_set_error(f_invalid_parameter);
      if (position.total_elements < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.address == 0) return f_status_set_warning(f_file_not_open);

    f_status status = f_none;
    f_string_length size = 0;
    f_bool infinite = f_false;

    // when total_elements is 0, this means the file read will until EOF is reached
    if (position.total_elements == 0) {
      infinite = f_true;
      size = f_file_default_read_size;
    }
    else {
      size = position.total_elements;
    }

    // populate the buffer
    do {
      if (buffer->size <= size) {
        f_macro_string_dynamic_resize(status, (*buffer), size);

        if (f_status_is_error(status)) {
          return status;
        }
      }

      status = f_file_read(&file, buffer, position);

      if (status == f_none_on_eof) {
        break;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      if (infinite) {
        if (size + f_file_default_read_size > f_string_max_size) {
          return f_status_set_error(f_overflow);
        }

        size += f_file_default_read_size;
      }
    } while (infinite);

    return f_none;
  }
#endif // _di_fl_file_read_

#ifndef _di_fl_file_read_fifo_
  f_return_status fl_file_read_fifo(f_file file, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.address == 0) return f_status_set_warning(f_file_not_open);

    f_status status = f_none;
    f_string_length size = 0;

    size = f_file_default_read_size;

    // populate the buffer
    do {
      if (buffer->size <= size) {
        f_macro_string_dynamic_resize(status, (*buffer), size);

        if (f_status_is_error(status)) {
          return status;
        }
      }

      status = f_file_read_fifo(&file, buffer);

      if (status == f_none_on_eof) {
        break;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      if (size + f_file_default_read_size > f_string_max_size) {
        return f_status_set_error(f_overflow);
      }

      size += f_file_default_read_size;
    } while (f_true);

    return f_none;
  }
#endif // _di_fl_file_read_fifo_

#ifndef _di_fl_file_write_
  f_return_status fl_file_write(f_file file, const f_string_dynamic buffer) {
    if (file.address == 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;
    size_t size = 0;

    size = fwrite(buffer.string, file.byte_size, buffer.used, file.address);

    if (size < buffer.used * file.byte_size) {
      return f_status_set_error(f_file_write_error);
    }

    return f_none;
  }
#endif // _di_fl_file_write_

#ifndef _di_fl_file_write_partial_
  f_return_status fl_file_write_partial(f_file file, const f_string_dynamic buffer, const f_string_location position) {
    #ifndef _di_level_1_parameter_checking_
      if (position.start < position.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.address == 0) return f_file_not_open;

    f_status status = f_none;
    size_t size = 0;

    f_string_length total = buffer.used - (position.stop - position.start + 1);

    size = fwrite(buffer.string + position.start, file.byte_size, total, file.address);

    if (size < total * file.byte_size) {
      return f_status_set_error(f_file_write_error);
    }

    return f_none;
  }
#endif // _di_fl_file_write_partial_

#ifdef __cplusplus
} // extern "C"
#endif

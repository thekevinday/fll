#include "utf_file.h"
#include "private-utf_file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_file_read_
  f_status_t fl_utf_file_read(const f_file_t file, f_utf_string_dynamic_t *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
      if (buffer->used > buffer->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    f_status_t status = F_none;

    ssize_t size_read = 0;
    uint8_t width = 0;
    int8_t width_last = -1;

    char buffer_read[file.size_read];
    char buffer_char[4] = { 0, 0, 0, 0 };

    memset(&buffer_read, 0, sizeof(file.size_read));

    while ((size_read = read(file.id, buffer_read, file.size_read)) > 0) {

      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_utf_string_dynamic_t_resize(status, (*buffer), buffer->size + size_read);
        if (F_status_is_error(status)) return status;
      }

      private_fl_utf_file_process_read_buffer(buffer_read, size_read, buffer, buffer_char, &width, &width_last);
    } // while

    if (!size_read) {
      if (width != 0) {
        return F_status_set_error(F_complete_not_utf_eof);
      }

      return F_none_eof;
    }
    else if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }
    else if (width != 0) {
      return F_status_set_error(F_complete_not_utf_stop);
    }

    return F_none;
  }
#endif // _di_fl_utf_file_read_

#ifndef _di_fl_utf_file_read_block_
  f_status_t fl_utf_file_read_block(const f_file_t file, f_utf_string_dynamic_t *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
      if (buffer->used > buffer->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    f_status_t status = F_none;

    ssize_t size_read = 0;
    uint8_t width = 0;
    int8_t width_last = -1;

    char buffer_read[file.size_read];
    char buffer_char[4] = { 0, 0, 0, 0 };

    memset(&buffer_read, 0, sizeof(file.size_read));

    if ((size_read = read(file.id, buffer_read, file.size_read)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_utf_string_dynamic_t_resize(status, (*buffer), buffer->size + size_read);
        if (F_status_is_error(status)) return status;
      }

      private_fl_utf_file_process_read_buffer(buffer_read, size_read, buffer, buffer_char, &width, &width_last);
    }

    if (!size_read) {
      if (width) {
        return F_status_set_error(F_complete_not_utf_eof);
      }

      return F_none_eof;
    }
    else if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }
    else if (width != 0) {
      return F_status_set_error(F_complete_not_utf_stop);
    }

    return F_none;
  }
#endif // _di_fl_utf_file_read_block_

#ifndef _di_fl_utf_file_read_until_
  f_status_t fl_utf_file_read_until(const f_file_t file, const f_string_length_t total, f_utf_string_dynamic_t *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
      if (buffer->used > buffer->size) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    f_status_t status = F_none;

    ssize_t size_read = 0;
    uint8_t width = 0;
    int8_t width_last = -1;

    f_string_length_t buffer_size = file.size_read;
    f_string_length_t buffer_count = 0;

    if (total < buffer_size) {
      buffer_size = total;
    }

    char buffer_read[buffer_size];
    char buffer_char[4] = { 0, 0, 0, 0 };

    memset(&buffer_read, 0, sizeof(buffer_size));

    while (buffer_count < total && (size_read = read(file.id, buffer_read, buffer_size)) > 0) {

      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_utf_string_dynamic_t_resize(status, (*buffer), buffer->size + size_read);
        if (F_status_is_error(status)) return status;
      }

      private_fl_utf_file_process_read_buffer(buffer_read, size_read, buffer, buffer_char, &width, &width_last);
    } // while

    if (!size_read) {
      if (width != 0) {
        return F_status_set_error(F_complete_not_utf_eof);
      }

      return F_none_eof;
    }
    else if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }
    else if (width != 0) {
      return F_status_set_error(F_complete_not_utf_stop);
    }

    return F_none;
  }
#endif // _di_fl_utf_file_read_until_

#ifndef _di_fl_utf_file_write_
  f_status_t fl_utf_file_write(const f_file_t file, const f_utf_string_static_t buffer, f_string_length_t *written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    if (!buffer.used) {
      *written = 0;
      return F_data_not;
    }

    const f_status_t status = private_fl_utf_file_write_until(file, buffer.string, buffer.used, written);
    if (F_status_is_error(status)) return F_status_set_error(status);

    if (status == F_none && *written == buffer.used) return F_none_eos;

    return status;
  }
#endif // _di_fl_utf_file_write_

#ifndef _di_fl_utf_file_write_block_
  f_status_t fl_utf_file_write_block(const f_file_t file, const f_utf_string_static_t buffer, f_string_length_t *written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    if (!buffer.used) {
      *written = 0;
      return F_data_not;
    }

    f_string_length_t write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    const f_status_t status = private_fl_utf_file_write_until(file, buffer.string, write_max, written);
    if (F_status_is_error(status)) return F_status_set_error(status);

    if (status == F_none && *written == buffer.used) return F_none_eos;

    return status;
  }
#endif // _di_fl_utf_file_write_block_

#ifndef _di_fl_utf_file_write_until_
  f_status_t fl_utf_file_write_until(const f_file_t file, const f_utf_string_static_t buffer, const f_string_length_t total, f_string_length_t *written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    if (!buffer.used || !total) {
      *written = 0;
      return F_data_not;
    }

    f_string_length_t write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    const f_status_t status = private_fl_utf_file_write_until(file, buffer.string, write_max, written);
    if (F_status_is_error(status)) return F_status_set_error(status);

    if (status == F_none && *written == buffer.used) return F_none_eos;

    return status;
  }
#endif // _di_fl_utf_file_write_until_

#ifndef _di_fl_utf_file_write_range_
  f_status_t fl_utf_file_write_range(const f_file_t file, const f_utf_string_static_t buffer, const f_utf_string_range_t range, f_string_length_t *written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (!file.id) return F_status_set_error(F_file_closed);

    if (!buffer.used) {
      *written = 0;
      return F_data_not;
    }

    const f_string_length_t total = (range.stop - range.start) + 1;
    f_string_length_t write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    const f_status_t status = private_fl_utf_file_write_until(file, buffer.string + range.start, write_max, written);
    if (F_status_is_error(status)) return F_status_set_error(status);

    if (status == F_none) {
      if (range.start + *written == total) return F_none_stop;
      if (range.start + *written == buffer.used) return F_none_eos;
    }

    return status;
  }
#endif // _di_fl_utf_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif

#include <level_1/utf_file.h>
#include "private-utf_file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_file_read_
  f_return_status fl_utf_file_read(const f_file file, f_utf_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (file.size_read == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used > buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;

    ssize_t size_read = 0;
    uint8_t width = 0;

    f_utf_string_length i = 0;
    f_utf_character character = 0;

    char buffer_read[file.size_read];

    memset(&buffer_read, 0, sizeof(file.size_read));

    while ((size_read = read(file.id, buffer_read, file.size_read)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return f_status_set_error(f_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (f_status_is_error(status)) return status;
      }

      for (i = 0; i < size_read; i += width) {
        width = f_macro_utf_byte_width(buffer_read[i]);

        // @fixme this needs to properly validate the UTF-8 width available and also carry ove the count across the outer loop.

        character = f_macro_utf_character_from_char_1(buffer_read[i]);

        if (width > 1 && i + 1 < size_read) {
          character |= f_macro_utf_character_from_char_2(buffer_read[i]);

          if (width > 2 && i + 2 < size_read) {
          character |= f_macro_utf_character_from_char_3(buffer_read[i]);

            if (width > 3 && i + 3 < size_read) {
              character |= f_macro_utf_character_from_char_4(buffer_read[i]);
            }
          }
        }

        buffer->string[i] = character;
        buffer->used++;
      } // for
    } // while

    if (size_read == 0) {
      return f_none_on_eof;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return f_status_set_error(f_block);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_fl_utf_file_read_

#ifndef _di_fl_utf_file_read_block_
  f_return_status fl_utf_file_read_block(const f_file file, f_utf_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (file.size_read == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used > buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;

    ssize_t size_read = 0;
    uint8_t width = 0;

    f_utf_string_length i = 0;
    f_utf_character character = 0;

    char buffer_read[file.size_read];

    memset(&buffer_read, 0, sizeof(file.size_read));

    if ((size_read = read(file.id, buffer_read, file.size_read)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return f_status_set_error(f_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (f_status_is_error(status)) return status;
      }

      for (i = 0; i < size_read; i += width) {
        width = f_macro_utf_byte_width(buffer_read[i]);

        // @fixme this needs to properly validate the UTF-8 width available and also carry ove the count across the outer loop.

        character = f_macro_utf_character_from_char_1(buffer_read[i]);

        if (width > 1 && i + 1 < size_read) {
          character |= f_macro_utf_character_from_char_2(buffer_read[i]);

          if (width > 2 && i + 2 < size_read) {
          character |= f_macro_utf_character_from_char_3(buffer_read[i]);

            if (width > 3 && i + 3 < size_read) {
              character |= f_macro_utf_character_from_char_4(buffer_read[i]);
            }
          }
        }

        buffer->string[i] = character;
        buffer->used++;
      } // for
    }

    if (size_read == 0) {
      return f_none_on_eof;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return f_status_set_error(f_block);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_fl_utf_file_read_block_

#ifndef _di_fl_utf_file_read_until_
  f_return_status fl_utf_file_read_until(const f_file file, f_utf_string_dynamic *buffer, const f_utf_string_length total) {
    #ifndef _di_level_1_parameter_checking_
      if (file.size_read == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used > buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;

    ssize_t size_read = 0;
    uint8_t width = 0;

    f_utf_string_length i = 0;
    f_utf_character character = 0;

    f_utf_string_length buffer_size = file.size_read;
    f_utf_string_length buffer_count = 0;

    if (total < buffer_size) {
      buffer_size = total;
    }

    char buffer_read[buffer_size];

    memset(&buffer_read, 0, sizeof(buffer_size));

    while (buffer_count < total && (size_read = read(file.id, buffer_read, buffer_size)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return f_status_set_error(f_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (f_status_is_error(status)) return status;
      }

      for (i = 0; i < size_read; i += width) {
        width = f_macro_utf_byte_width(buffer_read[i]);

        // @fixme this needs to properly validate the UTF-8 width available and also carry ove the count across the outer loop.

        character = f_macro_utf_character_from_char_1(buffer_read[i]);

        if (width > 1 && i + 1 < total) {
          character |= f_macro_utf_character_from_char_2(buffer_read[i]);

          if (width > 2 && i + 2 < total) {
          character |= f_macro_utf_character_from_char_3(buffer_read[i]);

            if (width > 3 && i + 3 < total) {
              character |= f_macro_utf_character_from_char_4(buffer_read[i]);
            }
          }
        }

        buffer->string[i] = character;
        buffer->used++;
        buffer_count++;
      } // for
    } // while

    if (size_read == 0) {
      return f_none_on_eof;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return f_status_set_error(f_block);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_fl_utf_file_read_until_

#ifndef _di_fl_utf_file_write_
  f_return_status fl_utf_file_write(const f_file file, const f_utf_string_dynamic buffer, f_utf_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used >= buffer.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    if (buffer.used == 0) {
      *written = 0;
      return f_no_data;
    }

    f_status status = private_fl_utf_file_write_until(file, buffer.string, buffer.used, written);
    if (f_status_is_error(status)) return f_status_set_error(status);

    if (status == f_none && *written == buffer.used) return f_none_on_eos;

    return status;
  }
#endif // _di_fl_utf_file_write_

#ifndef _di_fl_utf_file_write_block_
  f_return_status fl_utf_file_write_block(const f_file file, const f_utf_string_dynamic buffer, f_utf_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used >= buffer.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    if (buffer.used == 0) {
      *written = 0;
      return f_no_data;
    }

    f_utf_string_length write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status status = private_fl_utf_file_write_until(file, buffer.string, write_max, written);
    if (f_status_is_error(status)) return f_status_set_error(status);

    if (status == f_none && *written == buffer.used) return f_none_on_eos;

    return status;
  }
#endif // _di_fl_utf_file_write_block_

#ifndef _di_fl_utf_file_write_until_
  f_return_status fl_utf_file_write_until(const f_file file, const f_utf_string_dynamic buffer, const f_utf_string_length total, f_utf_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used >= buffer.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    if (buffer.used == 0 || total == 0) {
      *written = 0;
      return f_no_data;
    }

    f_utf_string_length write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status status = private_fl_utf_file_write_until(file, buffer.string, write_max, written);
    if (f_status_is_error(status)) return f_status_set_error(status);

    if (status == f_none && *written == buffer.used) return f_none_on_eos;

    return status;
  }
#endif // _di_fl_utf_file_write_until_

#ifndef _di_fl_utf_file_write_range_
  f_return_status fl_utf_file_write_range(const f_file file, const f_utf_string_dynamic buffer, const f_utf_string_range range, f_utf_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used >= buffer.size) return f_status_set_error(f_invalid_parameter);
      if (range.stop < range.start) return f_status_set_error(f_invalid_parameter);
      if (range.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id <= 0) return f_status_set_error(f_file_not_open);

    if (buffer.used == 0) {
      *written = 0;
      return f_no_data;
    }

    // @todo consider adding a custom status return for when an invalid UTF-8 is written due to range limitations.

    const f_utf_string_length total = (range.stop - range.start) + 1;
    f_utf_string_length write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status status = private_fl_utf_file_write_until(file, buffer.string + range.start, write_max, written);
    if (f_status_is_error(status)) return f_status_set_error(status);

    if (status == f_none) {
      if (range.start + *written == total) return f_none_on_stop;
      if (range.start + *written == buffer.used) return f_none_on_eos;
    }

    return status;
  }
#endif // _di_fl_utf_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif

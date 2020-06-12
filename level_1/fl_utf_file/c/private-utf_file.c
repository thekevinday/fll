#include <level_1/utf_file.h>
#include "private-utf_file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(fl_utf_file_read) || !defined(fl_utf_file_read_until) || !defined(fl_utf_file_read_range)
  void private_fl_utf_file_process_read_buffer(const char *buffer_read, const ssize_t size_read, f_utf_string_dynamic *buffer, char buffer_char[], uint8_t *width, int8_t *width_last) {
    f_utf_character character = 0;
    f_string_length i = 0;
    uint8_t increment_by = 0;

    for (; i < size_read; i += increment_by) {
      increment_by = 0;

      if (*width == 0) {
        *width = f_macro_utf_byte_width(buffer_read[i]);
        *width_last = -1;
      }

      if (*width_last < *width) {
        buffer_char[0] = buffer_read[i];
        *width_last = 1;
        increment_by++;
      }

      if (*width > 1 && i + 1 < size_read) {
        if (*width_last < *width) {
          buffer_char[1] = buffer_read[i];
          *width_last = 2;
          increment_by++;
        }

        if (*width > 2 && i + 2 < size_read) {
          if (*width_last < *width) {
            buffer_char[2] = buffer_read[i];
            *width_last = 3;
            increment_by++;
          }

          if (*width > 3 && i + 3 < size_read) {
            buffer_char[3] = buffer_read[i];
            *width_last = 4;
            increment_by++;
          }
        }
      }

      if (*width_last == *width) {
        buffer->string[buffer->used] = f_macro_utf_character_from_char_1((buffer_char[0]));

        if (*width > 1) {
          buffer->string[buffer->used] |= f_macro_utf_character_from_char_2((buffer_char[1]));

          if (*width > 2) {
            buffer->string[buffer->used] |= f_macro_utf_character_from_char_3((buffer_char[2]));

            if (*width > 3) {
              buffer->string[buffer->used] |= f_macro_utf_character_from_char_4((buffer_char[3]));
            }
          }
        }

        buffer->used++;
        *width = 0;
      }
    } // for
  }
#endif // !defined(fl_utf_file_read) || !defined(fl_utf_file_read_until) || !defined(fl_utf_file_read_range)

#if !defined(fl_utf_file_write) || !defined(fl_utf_file_write_until) || !defined(fl_utf_file_write_range)
  f_return_status private_fl_utf_file_write_until(const f_file file, const f_utf_string string, const f_utf_string_length total, f_utf_string_length *written) {
    *written = 0;

    f_status status = F_none;
    f_utf_string_length write_size = file.size_write > 4 ? file.size_write : 4;
    f_utf_string_length write_max = total;
    f_utf_string_length i = 0;

    if (write_size > write_max) {
      write_size = write_max;
    }

    f_string_length last = 0;
    f_string_length used = 0;

    ssize_t size_write = 0;
    uint8_t buffer_write[write_size];
    uint8_t width = 0;
    uint8_t width_written = 0;

    // @todo this needs to identify an invalid UTF-8 string before writing and return an error if invalid.

    do {
      memset(buffer_write, 0, write_size);

      for (i = 0, used = 0; used < write_size && *written + i < write_max; i++, used += width) {
        if (width_written < width) {
          if (width_written < 2) {
            buffer_write[used] = f_macro_utf_character_to_char_2(string[*written + i]);
            width_written++;
            used++;
          }

          if (width > 2 && width_written < 3) {
            buffer_write[used + 1] = f_macro_utf_character_to_char_3(string[*written + i]);
            width_written++;
            used++;
          }

          if (width == 4 && width_written < 4) {
            buffer_write[used + 2] = f_macro_utf_character_to_char_4(string[*written + i]);
            width_written++;
            used++;
          }

          width = 0;
        }
        else {
          width = f_macro_utf_character_width(string[*written + i]);
          width_written = width;

          if (*written + width > write_max) {
            return F_incomplete_utf_stop;
          }

          buffer_write[used] = f_macro_utf_character_to_char_1(string[*written + i]);

          if (width > 1) {
            if (used + 1 > write_size) {
              width_written = 1;
              used += 1;
              break;
            }

            buffer_write[used + 1] = f_macro_utf_character_to_char_2(string[*written + i]);

            if (width > 2) {
              if (used + 2 > write_size) {
                width_written = 2;
                used += 2;
                break;
              }

              buffer_write[used + 2] = f_macro_utf_character_to_char_3(string[*written + i]);

              if (width == 4) {
                if (used + 3 > write_size) {
                  width_written = 3;
                  used += 3;
                  break;
                }

                buffer_write[used + 3] = f_macro_utf_character_to_char_4(string[*written + i]);
              }
            }
          }
        }
      } // for

      size_write = write(file.id, buffer_write, used);

      if (size_write == 0) {
        return F_none_stop;
      }

      if (size_write < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupted);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_failure);
      }

      *written += i;
      last += used;

      if (*written + write_size > write_max) {
        write_size = write_max - *written;
      }
    } while (*written < write_max);

    return F_none;
  }
#endif // !defined(fl_utf_file_write) || !defined(fl_utf_file_write_until) || !defined(fl_utf_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif

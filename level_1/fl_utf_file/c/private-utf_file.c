#include <level_1/utf_file.h>
#include "private-utf_file.h"

#ifdef __cplusplus
extern "C" {
#endif

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

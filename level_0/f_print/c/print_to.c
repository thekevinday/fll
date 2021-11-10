#include "print.h"
#include "private-print.h"
#include "private-print_to.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Inline helper function to reduce amount of code typed.
 *
 * This will process errno based on a write() error.
 *
 * @return
 *   The appropriate status.
 */
static inline f_status_t private_inline_f_print_to_error() {
  if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
  if (errno == EBADF) return F_status_set_error(F_file_descriptor);
  if (errno == EDESTADDRREQ) return F_status_set_error(F_socket_not);
  if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
  if (errno == EFBIG) return F_status_set_error(F_number_overflow);
  if (errno == EFAULT) return F_status_set_error(F_buffer);
  if (errno == EINTR) return F_status_set_error(F_interrupt);
  if (errno == EINVAL) return F_status_set_error(F_parameter);
  if (errno == EIO) return F_status_set_error(F_input_output);
  if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
  if (errno == ENOSPC) return F_status_set_error(F_space_not);
  if (errno == EPIPE) return F_status_set_error(F_pipe);

  return F_status_set_error(F_output);
}

#ifndef _di_f_print_to_
  f_status_t f_print_to(const f_string_t string, const f_array_length_t length, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to(string, length, id);
  }
#endif // _di_f_print_to_

#ifndef _di_f_print_to_character_
  f_status_t f_print_to_character(const char character, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (write(id, &character, 1) == -1) {
      return private_inline_f_print_to_error();
    }

    return F_none;
  }
#endif // _di_f_print_to_character_

#ifndef _di_f_print_to_character_safely_
  f_status_t f_print_to_character_safely(const char character, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_print_to_character_safely(character, id);
  }
#endif // _di_f_print_to_character_safely_

#ifndef _di_f_print_to_dynamic_
  f_status_t f_print_to_dynamic(const f_string_static_t buffer, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_to(buffer.string, buffer.used, id);
  }
#endif // _di_f_print_to_dynamic_

#ifndef _di_f_print_to_dynamic_partial_
  f_status_t f_print_to_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to(buffer.string + range.start, length, id);
  }
#endif // _di_f_print_to_dynamic_partial_

#ifndef _di_f_print_to_dynamic_partial_raw_
  f_status_t f_print_to_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_raw(buffer.string + range.start, length, id);
  }
#endif // _di_f_print_to_dynamic_partial_raw_

#ifndef _di_f_print_to_dynamic_partial_safely_
  f_status_t f_print_to_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_safely(buffer.string + range.start, length, id);
  }
#endif // _di_f_print_to_dynamic_partial_safely_

#ifndef _di_f_print_to_dynamic_raw_
  f_status_t f_print_to_dynamic_raw(const f_string_static_t buffer, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_to_raw(buffer.string, buffer.used, id);
  }
#endif // _di_f_print_to_dynamic_raw_

#ifndef _di_f_print_to_dynamic_safely_
  f_status_t f_print_to_dynamic_safely(const f_string_static_t buffer, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_to_safely(buffer.string, buffer.used, id);
  }
#endif // _di_f_print_to_dynamic_safely_

#ifndef _di_f_print_to_except_
  f_status_t f_print_to_except(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_except(string, 0, length, except, id);
  }
#endif // _di_f_print_to_except_

#ifndef _di_f_print_to_except_dynamic_
  f_status_t f_print_to_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_to_except(buffer.string, 0, buffer.used, except, id);
  }
#endif // _di_f_print_to_except_dynamic_

#ifndef _di_f_print_to_except_dynamic_partial_
  f_status_t f_print_to_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except(buffer.string, range.start, range.start + length, except, id);
  }
#endif // _di_f_print_to_except_dynamic_partial_

#ifndef _di_f_print_to_except_dynamic_partial_raw_
  f_status_t f_print_to_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except_raw(buffer.string, range.start, range.start + length, except, id);
  }
#endif // _di_f_print_to_except_dynamic_partial_raw_

#ifndef _di_f_print_to_except_dynamic_partial_safely_
  f_status_t f_print_to_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except_safely(buffer.string, range.start, range.start + length, except, id);
  }
#endif // _di_f_print_to_except_dynamic_partial_safely_

#ifndef _di_f_print_to_except_dynamic_raw_
  f_status_t f_print_to_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_to_except_raw(buffer.string, 0, buffer.used, except, id);
  }
#endif // _di_f_print_to_except_dynamic_raw_

#ifndef _di_f_print_to_except_dynamic_safely_
  f_status_t f_print_to_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_to_except_safely(buffer.string, 0, buffer.used, except, id);
  }
#endif // _di_f_print_to_except_dynamic_safely_

#ifndef _di_f_print_to_except_in_
  f_status_t f_print_to_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_except_in(string, offset, length, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_

#ifndef _di_f_print_to_except_in_dynamic_
  f_status_t f_print_to_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_to_except_in(buffer.string, 0, buffer.used, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_dynamic_

#ifndef _di_f_print_to_except_in_dynamic_partial_
  f_status_t f_print_to_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except_in(buffer.string, range.start, range.start + length, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_dynamic_partial_

#ifndef _di_f_print_to_except_in_dynamic_partial_raw_
  f_status_t f_print_to_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except_in_raw(buffer.string, range.start, range.start + length, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_dynamic_partial_raw_

#ifndef _di_f_print_to_except_in_dynamic_partial_safely_
  f_status_t f_print_to_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except_in_safely(buffer.string, range.start, range.start + length, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_dynamic_partial_safely_

#ifndef _di_f_print_to_except_in_dynamic_raw_
  f_status_t f_print_to_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_to_except_in_raw(buffer.string, 0, buffer.used, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_dynamic_raw_

#ifndef _di_f_print_to_except_in_dynamic_safely_
  f_status_t f_print_to_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_to_except_in_safely(buffer.string, 0, buffer.used, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_dynamic_safely_

#ifndef _di_f_print_to_except_in_raw_
  f_status_t f_print_to_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_except_in_raw(string, offset, length, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_raw_

#ifndef _di_f_print_to_except_in_safely_
  f_status_t f_print_to_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_except_in_safely(string, offset, length, except_at, except_in, id);
  }
#endif // _di_f_print_to_except_in_safely_

#ifndef _di_f_print_to_except_raw_
  f_status_t f_print_to_except_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_except_raw(string, 0, length, except, id);
  }
#endif // _di_f_print_to_except_raw_

#ifndef _di_f_print_to_except_safely_
  f_status_t f_print_to_except_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_except_safely(string, 0, length, except, id);
  }
#endif // _di_f_print_to_except_safely_

#ifndef _di_f_print_to_raw_
  f_status_t f_print_to_raw(const f_string_t string, const f_array_length_t length, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_raw(string, length, id);
  }
#endif // _di_f_print_to_raw_

#ifndef _di_f_print_to_raw_terminated_
  f_status_t f_print_to_raw_terminated(const f_string_t string, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string) {
      return F_data_not;
    }

    // The f_print_raw_terminated() and f_print_terminated() are functionality identical due to being NULL terminated.
    return private_f_print_to_terminated(string, id);
  }
#endif // _di_f_print_raw_terminated_

#ifndef _di_f_print_to_safely_
  f_status_t f_print_to_safely(const f_string_t string, const f_array_length_t length, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_to_safely(string, length, id);
  }
#endif // _di_f_print_to_safely_

#ifndef _di_f_print_to_safely_terminated_
  f_status_t f_print_to_safely_terminated(const f_string_t string, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string) {
      return F_data_not;
    }

    f_status_t status = F_none;

    f_array_length_t start = 0;
    f_array_length_t total = 0;

    f_string_t safe = 0;

    uint8_t width = 0;

    for (register f_array_length_t i = 0; string[i]; ) {

      width = macro_f_utf_character_t_width_is(string[i]);

      if (width) {
        if (width > 1) {
          if (string[i + 1]) {
            if (width > 2) {
              if (string[i + 2]) {
                if (width > 3) {
                  if (string[i + 3]) {
                    status = f_utf_is_control(string + i, 4);
                  }
                  else {
                    status = F_utf;
                  }
                }
                else {
                  status = f_utf_is_control(string + i, 3);
                }
              }
              else {
                status = F_utf;
              }
            }
            else {
              status = f_utf_is_control(string + i, 2);
            }
          }
          else {
            status = F_utf;
          }
        }
        else {
          status = f_utf_is_control(string + i, 1);
        }

        if (status == F_false && total + width < F_print_write_max_d) {
          total += width;
          i += width;

          continue;
        }
      }
      else {
        if ((string[i] > 0x1f && string[i] != 0x7f) && total < F_print_write_max_d) {
          ++total;
          ++i;

          continue;
        }

        status = F_none;
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
      }

      if (status == F_true || F_status_set_fine(status) == F_utf) {
        if (write(id, f_print_sequence_unknown_s, 3) == -1) {
          return private_inline_f_print_to_error();
        }

        for (start = 0; string[start] && start < width; ) {
          ++start;
        } // while

        if (start != width) break;

        i += width;
      }
      else if (status == F_false) {
        if (write(id, string + start, width) == -1) {
          return private_inline_f_print_to_error();
        }

        for (start = 0; string[start] && start < width; ) {
          ++start;
        } // while

        if (start != width) break;

        i += width;
      }
      else {
        safe = private_f_print_character_safely_get(string[i]);

        if (safe) {
          if (write(id, safe, 3) == -1) {
            return private_inline_f_print_to_error();
          }
        }
        else {
          status = f_utf_is_valid(string + i, width);

          if (F_status_is_error(status) || status == F_false) {
            if (write(id, f_print_sequence_unknown_s, 3) == -1) {
              return private_inline_f_print_to_error();
            }

            for (start = 0; string[start] && start < width; ) {
              ++start;
            } // while

            if (start != width) break;
          }
          else {
            for (start = 0; string[start] && start < width; ) {
              ++start;
            } // while

            if (start != width) break;

            total = width;
            start = i;
            i += width;
            continue;
          }
        }

        i += width;
      }

      start = i;
    } // for

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // _di_f_print_to_safely_terminated_

#ifndef _di_f_print_to_terminated_
  f_status_t f_print_to_terminated(const f_string_t string, const int id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string) {
      return F_data_not;
    }

    return private_f_print_to_terminated(string, id);
  }
#endif // _di_f_print_to_terminated_

#ifdef __cplusplus
} // extern "C"
#endif

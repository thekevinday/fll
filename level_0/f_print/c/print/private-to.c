#include "../print.h"
#include "../private-print.h"
#include "private-to.h"

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
static inline f_status_t private_inline_f_print_to_error(void) {
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

#if !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)
  f_status_t private_f_print_to(const f_string_t string, const f_array_length_t length, const int id) {

    f_array_length_t total = 0;

    for (register f_array_length_t i = 0; i < length; ) {

      total = strnlen((string + i), length - i);

      if (total) {
        if (total > F_print_write_max_d) {
          total = F_print_write_max_d;
        }

        if (write(id, string + i, total) == -1) {
          return private_inline_f_print_to_error();
        }

        i += total;
        total = 0;
      }

      if (!string[i]) {
        do {
          ++i;
        } while (i < length && !string[i]);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)

#if !defined(_di_f_print_to_character_safely_) || !defined(_di_f_print_to_safely_) || !defined(_di_f_print_to_safely_dynamic_) || !defined(_di_f_print_to_safely_dynamic_partial_) || !defined(_di_f_print_to_safely_terminated_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)
  f_status_t private_f_print_to_character_safely(const f_char_t character, const int id) {

    if (character == 0x7f) {
      if (write(id, f_print_sequence_delete_s.string, f_print_sequence_delete_s.used) != -1) {
        return F_none;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 1) {
      if (write(id, f_print_sequence_unknown_s.string, f_print_sequence_unknown_s.used) != -1) {
        return F_none;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) > 1 || character > 0x1f) {
      if (write(id, &character, 1) != -1) {
        return F_none;
      }
    }
    else {
      if (write(id, f_print_sequence_set_control_s[character].string, f_print_sequence_set_control_s[character].used) != -1) {
        return F_none;
      }
    }

    return private_inline_f_print_to_error();
  }
#endif // !defined(_di_f_print_to_character_safely_) || !defined(_di_f_print_to_safely_) || !defined(_di_f_print_to_safely_dynamic_) || !defined(_di_f_print_to_safely_dynamic_partial_) || !defined(_di_f_print_to_safely_terminated_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)

#if !defined(_di_f_print_to_except_) || !defined(_di_f_print_to_except_dynamic_) || !defined(_di_f_print_to_except_dynamic_partial_)
  f_status_t private_f_print_to_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = offset;
    f_array_length_t total = 0;

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j >= except.used || except.array[j] != i) {
        if (string[i] && total < F_print_write_max_d) {
          ++total;
          ++i;

          continue;
        }
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }
      }

      if ((j >= except.used || except.array[j] != i) && string[i]) {
        start = i++;
        total = 1;
      }
      else {
        start = ++i;
        total = 0;
      }
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_) || !defined(_di_f_print_to_except_dynamic_) || !defined(_di_f_print_to_except_dynamic_partial_)

#if !defined(_di_f_print_to_except_raw_) || !defined(_di_f_print_to_except_dynamic_raw_) || !defined(_di_f_print_to_except_dynamic_partial_raw_)
  f_status_t private_f_print_to_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = offset;
    f_array_length_t total = 0;

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j >= except.used || except.array[j] != i) {
        if (total < F_print_write_max_d) {
          ++total;
          ++i;

          continue;
        }
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }
      }

      if (j >= except.used || except.array[j] != i) {
        start = i++;
        total = 1;
      }
      else {
        start = ++i;
        total = 0;
      }
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_raw_) || !defined(_di_f_print_to_except_dynamic_raw_) || !defined(_di_f_print_to_except_dynamic_partial_raw_)

#if !defined(_di_f_print_to_except_dynamic_raw_safely_) || !defined(_di_f_print_to_except_dynamic_partial_raw_safely_) || !defined(_di_f_print_to_except_raw_safely_)
  f_status_t private_f_print_to_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = offset;
    f_array_length_t total = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_empty_s;

    uint8_t width = 0;

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        ++i;

        continue;
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        width = 1;
        safe.used = 0;
      }

      if (safe.used) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        if (write(id, safe.string, safe.used) == -1) {
          return private_inline_f_print_to_error();
        }

        start = ++i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_dynamic_raw_safely_) || !defined(_di_f_print_to_except_dynamic_partial_raw_safely_) || !defined(_di_f_print_to_except_raw_safely_)

#if !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_)
  f_status_t private_f_print_to_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = offset;
    f_array_length_t total = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_empty_s;

    uint8_t width = 0;

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        ++i;

        continue;
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (safe.used) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        if (write(id, safe.string, safe.used) == -1) {
          return private_inline_f_print_to_error();
        }

        start = ++i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_)

#if !defined(_di_f_print_to_except_in_) || !defined(_di_f_print_to_except_in_dynamic_) || !defined(_di_f_print_to_except_in_dynamic_partial_)
  f_status_t private_f_print_to_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            if (write(id, string + start, total) == -1) {
              return private_inline_f_print_to_error();
            }

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      if (string[i]) {
        ++total;
      }

      if (!string[i] || i + 1 == stop || total == F_print_write_max_d) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;
      }
      else {
        ++i;
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_in_) || !defined(_di_f_print_to_except_in_dynamic_) || !defined(_di_f_print_to_except_in_dynamic_partial_)

#if !defined(_di_f_print_to_except_in_raw_) || !defined(_di_f_print_to_except_in_dynamic_raw_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_)
  f_status_t private_f_print_to_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            if (write(id, string + start, total) == -1) {
              return private_inline_f_print_to_error();
            }

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      ++total;

      if (i + 1 == stop || total == F_print_write_max_d) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;
      }
      else {
        ++i;
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_in_raw_) || !defined(_di_f_print_to_except_in_dynamic_raw_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_)

#if !defined(_di_f_print_to_except_in_raw_safely_) || !defined(_di_f_print_to_except_in_dynamic_raw_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_safely_)
  f_status_t private_f_print_to_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_empty_s;

    uint8_t width = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            if (write(id, string + start, total) == -1) {
              return private_inline_f_print_to_error();
            }

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        width = 1;
        safe.used = 0;
      }

      if (safe.used) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        if (write(id, safe.string, safe.used) == -1) {
          return private_inline_f_print_to_error();
        }

        start = ++i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_in_raw_safely_) || !defined(_di_f_print_to_except_in_dynamic_raw_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_safely_)

#if !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)
  f_status_t private_f_print_to_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const int id) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_empty_s;

    uint8_t width = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            if (write(id, string + start, total) == -1) {
              return private_inline_f_print_to_error();
            }

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (safe.used) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        if (write(id, safe.string, safe.used) == -1) {
          return private_inline_f_print_to_error();
        }

        start = ++i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)

#if !defined(_di_f_print_to_raw_) || !defined(_di_f_print_dynamic_to_raw_) || !defined(_di_f_print_dynamic_partial_to_raw_)
  f_status_t private_f_print_to_raw(const f_string_t string, const f_array_length_t length, const int id) {

    f_array_length_t start = 0;
    f_array_length_t total = 0;

    for (register f_array_length_t i = 0; i < length; ) {

      total = strnlen((string + i), length - i);

      if (total) {
        if (total > F_print_write_max_d) {
          total = F_print_write_max_d;
        }

        if (write(id, string + i, total) == -1) {
          return private_inline_f_print_to_error();
        }

        i += total;
        total = 0;
      }

      // Print all NULL characters.
      if (!string[i]) {
        start = i;

        do {
          ++i;
          ++total;

        } while (i < length && !string[i] && total < F_print_write_max_d);

        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_to_raw_) || !defined(_di_f_print_dynamic_to_raw_) || !defined(_di_f_print_dynamic_partial_to_raw_)

#if !defined(_di_f_print_to_dynamic_raw_safely_) || !defined(_di_f_print_to_dynamic_partial_raw_safely_) || !defined(_di_f_print_to_raw_safely_)
  f_status_t private_f_print_to_raw_safely(const f_string_t string, const f_array_length_t length, const int id) {

    f_status_t status = F_none;

    register f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;

    f_string_static_t safe = f_string_empty_s;

    uint8_t width = 0;

    while (i < length) {

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        width = 1;
        safe.used = 0;
      }

      if (safe.used) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        if (write(id, safe.string, safe.used) == -1) {
          return private_inline_f_print_to_error();
        }

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_dynamic_raw_safely_) || !defined(_di_f_print_dynamic_partial_to_raw_safely_) || !defined(_di_f_print_to_raw_safely_)

#if !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_safely_)
  f_status_t private_f_print_to_safely(const f_string_t string, const f_array_length_t length, const int id) {

    f_status_t status = F_none;

    register f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;

    f_string_static_t safe = f_string_empty_s;

    uint8_t width = 0;

    while (i < length) {

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (safe.used) {
        if (total) {
          if (write(id, string + start, total) == -1) {
            return private_inline_f_print_to_error();
          }

          total = 0;
        }

        if (write(id, safe.string, safe.used) == -1) {
          return private_inline_f_print_to_error();
        }

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        if (write(id, string + start, total) == -1) {
          return private_inline_f_print_to_error();
        }

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        return private_inline_f_print_to_error();
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_safely_)

#if !defined(_di_f_print_to_terminated_) || !defined(_di_f_print_to_raw_terminated_)
  f_status_t private_f_print_to_terminated(const f_string_t string, const int id) {

    if (write(id, string, strlen(string)) == -1) {
      return private_inline_f_print_to_error();
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_terminated_) || !defined(_di_f_print_to_raw_terminated_)

#ifdef __cplusplus
} // extern "C"
#endif

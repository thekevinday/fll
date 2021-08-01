#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  f_status_t private_f_print(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t start = 0;
    f_array_length_t total = 0;

    for (register f_array_length_t i = 0; i < length; ) {

      total = strlen(string + start);

      if (total) {
        if (fwrite_unlocked(string + start, 1, total, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }

        i += total;
      }

      start = i;

      if (start < length && !string[start]) {
        total = 0;

        do {
          ++i;
          ++total;

        } while (i < length && !string[i]);

        start = i;
      }
    } // for

    if (total) {
      if (fwrite_unlocked(string + start, 1, total, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

#if !defined(_di_f_print_character_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)
  f_status_t private_f_print_character_safely(const char character, FILE *output) {

    if (character > 0x1f && character != 0x7f) {
      if (fputc_unlocked(character, output)) {
        return F_none;
      }

      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_output);
    }

    if (fwrite_unlocked(character == 0x7f ? f_print_sequence_delete_s : f_print_sequence_set_control_s[character], 1, 3, output) == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_output);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_character_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)

#if !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_to_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)
  f_string_t private_f_print_character_safely_get(const char character) {

    if (character > 0x1f && character != 0x7f) {
      return 0;
    }

    return character == 0x7f ? f_print_sequence_delete_s : (f_string_t) f_print_sequence_set_control_s[character];
  }
#endif // !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_to_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)

#if !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)
  f_status_t private_f_print_raw(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t start = 0;
    f_array_length_t total = 0;

    for (register f_array_length_t i = 0; i < length; ) {

      total = strlen(string + start);

      if (total) {
        if (fwrite_unlocked(string + start, 1, total, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }

        i += total;
      }

      start = i;

      if (start < length && !string[start]) {
        total = 0;

        do {
          ++i;
          ++total;

        } while (i < length && !string[i]);

        if (fwrite_unlocked(string + start, 1, total, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }

        start = i;
      }
    } // for

    if (total) {
      if (fwrite_unlocked(string + start, 1, total, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)

#if !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)
  f_status_t private_f_print_safely(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_status_t status = F_none;

    f_array_length_t start = 0;
    f_array_length_t total = 0;

    for (register f_array_length_t i = 0; i < length; ) {

      if ((string[i] > 0x1f && string[i] != 0x7f) && total < f_print_write_max) {
        ++total;
        ++i;

        continue;
      }

      if (total) {
        if (fwrite_unlocked(string + start, 1, total, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      for (; i < length && (string[i] < 32 || string[i] == 0x7f); ++i) {

        status = private_f_print_character_safely(string[i], output);
        if (F_status_is_error(status)) return status;
      } // for

      start = i;
    } // for

    if (total) {
      if (fwrite_unlocked(string + start, 1, total, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)

#if !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)
  f_status_t private_f_print_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE *output) {

    // @todo update logic to use fwrite()
    f_array_length_t i = offset;
    f_array_length_t j = 0;

    for (; i < stop; ++i) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) continue;

      if (string[i]) {
        if (!fputc_unlocked(string[i], output)) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)

#if !defined(_di_f_print_except_raw_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)
  f_status_t private_f_print_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE *output) {

    // @todo update logic to use fwrite()
    f_array_length_t i = offset;
    f_array_length_t j = 0;

    for (; i < stop; ++i) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) continue;

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_except_raw_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)

#if !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_)
  f_status_t private_f_print_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE *output) {

    // @todo update logic to use fwrite()
    f_array_length_t i = offset;
    f_array_length_t j = 0;

    f_status_t status = F_none;
    f_string_t s = 0;

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        ++i;

        continue;
      }

      s = private_f_print_character_safely_get(string[i]);

      if (s) {
        if (!fputc_unlocked(s[i], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(s[i + 1], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(s[i + 2], output)) {
          return F_status_set_error(F_output);
        }

        ++i;
      }
      else {
        status = f_utf_is_valid(string + i, stop - i);

        if (F_status_is_error(status) || status == F_false) {
          if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
            return F_status_set_error(F_output);
          }

          i += macro_f_utf_byte_width(string[i]);
          continue;
        }

        if (i + macro_f_utf_byte_width(string[i]) >= stop) {
          if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
            return F_status_set_error(F_output);
          }

          i = stop;
          continue;
        }

        if (!fputc_unlocked(string[i], output)) {
          return F_status_set_error(F_output);
        }

        if (macro_f_utf_byte_width(string[i]) > 1) {
          if (!fputc_unlocked(string[i + 1], output)) {
            return F_status_set_error(F_output);
          }

          if (macro_f_utf_byte_width(string[i]) > 2) {
            if (!fputc_unlocked(string[i + 2], output)) {
              return F_status_set_error(F_output);
            }

            if (macro_f_utf_byte_width(string[i]) > 3) {
              if (!fputc_unlocked(string[i + 3], output)) {
                return F_status_set_error(F_output);
              }
            }
          }
        }

        i += macro_f_utf_byte_width(string[i]);
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_)

#if !defined(_di_f_print_except_in_) || !defined(_di_f_print_except_in_dynamic_) || !defined(_di_f_print_except_in_dynamic_partial_)
  f_status_t private_f_print_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    // @todo update logic to use fwrite()
    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          i = except_in.array[in].stop + 1;

          continue;
        }
      }

      if (string[i]) {
        if (!fputc_unlocked(string[i], output)) {
          return F_status_set_error(F_output);
        }
      }

      ++i;
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_) || !defined(_di_f_print_except_in_dynamic_) || !defined(_di_f_print_except_in_dynamic_partial_)

#if !defined(_di_f_print_except_in_raw_) || !defined(_di_f_print_except_in_dynamic_raw_) || !defined(_di_f_print_except_in_dynamic_partial_raw_)
  f_status_t private_f_print_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    // @todo update logic to use fwrite()
    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          i = except_in.array[in].stop + 1;

          continue;
        }
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }

      ++i;
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_raw_) || !defined(_di_f_print_except_in_dynamic_raw_) || !defined(_di_f_print_except_in_dynamic_partial_raw_)

#if !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)
  f_status_t private_f_print_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    // @todo update logic to use fwrite()
    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;

    f_status_t status = F_none;
    f_string_t s = 0;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          i = except_in.array[in].stop + 1;

          continue;
        }
      }

      s = private_f_print_character_safely_get(string[i]);

      if (s) {
        if (!fputc_unlocked(s[i], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(s[i + 1], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(s[i + 2], output)) {
          return F_status_set_error(F_output);
        }

        ++i;
      }
      else {
        status = f_utf_is_valid(string + i, stop - i);

        if (F_status_is_error(status) || status == F_false) {
          if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
            return F_status_set_error(F_output);
          }

          i += macro_f_utf_byte_width(string[i]);
          continue;
        }

        if (i + macro_f_utf_byte_width(string[i]) >= stop) {
          if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
            return F_status_set_error(F_output);
          }

          i = stop;
          continue;
        }

        if (!fputc_unlocked(string[i], output)) {
          return F_status_set_error(F_output);
        }

        if (macro_f_utf_byte_width(string[i]) > 1) {
          if (!fputc_unlocked(string[i + 1], output)) {
            return F_status_set_error(F_output);
          }

          if (macro_f_utf_byte_width(string[i]) > 2) {
            if (!fputc_unlocked(string[i + 2], output)) {
              return F_status_set_error(F_output);
            }

            if (macro_f_utf_byte_width(string[i]) > 3) {
              if (!fputc_unlocked(string[i + 3], output)) {
                return F_status_set_error(F_output);
              }
            }
          }
        }

        i += macro_f_utf_byte_width(string[i]);
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)

#if !defined(_di_f_print_terminated_) || !defined(_di_f_print_raw_terminated_)
  f_status_t private_f_print_terminated(const f_string_t string, FILE *output) {

    if (fwrite_unlocked(string, 1, strlen(string), output) == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_output);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_terminated_) || !defined(_di_f_print_raw_terminated_)

#if !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)
  f_status_t private_f_print_to(const f_string_t string, const f_array_length_t length, const int id) {

    f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;

    while (i < length) {

      if (string[i] && total < f_print_write_max) {
        ++total;
        ++i;

        continue;
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      if (string[i]) {
        start = i++;
        total = 1;
      }
      else {
        start = ++i;
        total = 0;
      }
    } // for

    if (total) {
      if (write(id, string + start, total) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)

#if !defined(_di_f_print_to_raw_) || !defined(_di_f_print_dynamic_to_raw_) || !defined(_di_f_print_dynamic_partial_to_raw_)
  f_status_t private_f_print_to_raw(const f_string_t string, const f_array_length_t length, const int id) {

    f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;

    while (i < length) {

      if (total < f_print_write_max) {
        ++total;
        ++i;

        continue;
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      start = ++i;
      total = 0;
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_raw_) || !defined(_di_f_print_dynamic_to_raw_) || !defined(_di_f_print_dynamic_partial_to_raw_)

#if !defined(_di_f_print_dynamic_to_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_safely_)
  f_status_t private_f_print_to_safely(const f_string_t string, const f_array_length_t length, const int id) {

    f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;

    f_status_t status = F_none;
    f_string_t s = 0;

    while (i < length) {

      s = private_f_print_character_safely_get(string[i]);

      if (s) {
        if (total < f_print_write_max) {
          ++total;
          ++i;

          continue;
        }
      }
      else {
        if (total + macro_f_utf_byte_width(string[i]) < f_print_write_max) {
          total += macro_f_utf_byte_width(string[i]);
          i += macro_f_utf_byte_width(string[i]);

          continue;
        }
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      if (s) {
        if (write(id, s, 3) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }

        start = ++i;
        total = 0;
      }
      else {
        status = f_utf_is_valid(string + i, length - i);

        if (F_status_is_error(status) || status == F_false) {
          if (write(id, f_print_sequence_unknown_s, 3) == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
            if (errno == EBADF) return F_status_set_error(F_file_descriptor);
            if (errno == EFAULT) return F_status_set_error(F_buffer);
            if (errno == EINTR) return F_status_set_error(F_interrupt);
            if (errno == EINVAL) return F_status_set_error(F_parameter);
            if (errno == EIO) return F_status_set_error(F_input_output);
            if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

            return F_status_set_error(F_output);
          }

          i += macro_f_utf_byte_width(string[i]);
          start = i;
          total = 0;

          continue;
        }

        if (i + macro_f_utf_byte_width(string[i]) >= length) {
          if (write(id, f_print_sequence_unknown_s, 3) == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
            if (errno == EBADF) return F_status_set_error(F_file_descriptor);
            if (errno == EFAULT) return F_status_set_error(F_buffer);
            if (errno == EINTR) return F_status_set_error(F_interrupt);
            if (errno == EINVAL) return F_status_set_error(F_parameter);
            if (errno == EIO) return F_status_set_error(F_input_output);
            if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

            return F_status_set_error(F_output);
          }

          i = length;
          start = length;
          total = 0;

          continue;
        }

        total = macro_f_utf_byte_width(string[i]);
        start = i;
        i += total;
      }
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_dynamic_to_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_safely_)

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
        if (string[i] && total < f_print_write_max) {
          ++total;
          ++i;

          continue;
        }
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
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
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
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
        if (total < f_print_write_max) {
          ++total;
          ++i;

          continue;
        }
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
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
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_raw_) || !defined(_di_f_print_to_except_dynamic_raw_) || !defined(_di_f_print_to_except_dynamic_partial_raw_)

#if !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_)
  f_status_t private_f_print_to_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = offset;
    f_array_length_t total = 0;

    f_status_t status = F_none;
    f_string_t s = 0;

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        ++i;
        continue;
      }

      s = private_f_print_character_safely_get(string[i]);

      if (!s && total < f_print_write_max) {
        ++total;
        ++i;

        continue;
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      if (s) {
        if (write(id, s, 3) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }

        start = ++i;
        total = 0;
      }
      else {
        status = f_utf_is_valid(string + i, stop - i);

        if (F_status_is_error(status) || status == F_false) {
          if (write(id, f_print_sequence_unknown_s, 3) == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
            if (errno == EBADF) return F_status_set_error(F_file_descriptor);
            if (errno == EFAULT) return F_status_set_error(F_buffer);
            if (errno == EINTR) return F_status_set_error(F_interrupt);
            if (errno == EINVAL) return F_status_set_error(F_parameter);
            if (errno == EIO) return F_status_set_error(F_input_output);
            if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

            return F_status_set_error(F_output);
          }

          i += macro_f_utf_byte_width(string[i]);
          start = i;
          total = 0;

          continue;
        }

        if (i + macro_f_utf_byte_width(string[i]) >= stop) {
          if (write(id, f_print_sequence_unknown_s, 3) == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
            if (errno == EBADF) return F_status_set_error(F_file_descriptor);
            if (errno == EFAULT) return F_status_set_error(F_buffer);
            if (errno == EINTR) return F_status_set_error(F_interrupt);
            if (errno == EINVAL) return F_status_set_error(F_parameter);
            if (errno == EIO) return F_status_set_error(F_input_output);
            if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

            return F_status_set_error(F_output);
          }

          i = stop;
          start = stop;
          total = 0;

          continue;
        }

        total = macro_f_utf_byte_width(string[i]);
        start = i;
        i += total;
      }
    } // while

    if (total) {
      if (write(id, string + start, total) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_)

#ifdef __cplusplus
} // extern "C"
#endif

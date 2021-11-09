#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_
  f_status_t f_print(const f_string_t string, const f_array_length_t length, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print(string, length, output);
  }
#endif // _di_f_print_

#ifndef _di_f_print_character_
  f_status_t f_print_character(const char character, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (fwrite_unlocked(&character, 1, 1, output) == -1) {
      return F_status_set_error(F_output);
    }

    return F_none;
  }
#endif // _di_f_print_character_

#ifndef _di_f_print_character_safely_
  f_status_t f_print_character_safely(const char character, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (character == 0x7f) {
      if (fwrite_unlocked(f_print_sequence_delete_s, 1, 3, output) != -1) {
        return F_none;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) == 1) {
      if (fwrite_unlocked(f_print_sequence_unknown_s, 1, 3, output) != -1) {
        return F_none;
      }
    }
    else if (macro_f_utf_character_t_width_is(character) > 1 || character > 0x1f) {
      if (fwrite_unlocked(&character, 1, 1, output) != -1) {
        return F_none;
      }
    }
    else {
      if (fwrite_unlocked(f_print_sequence_set_control_s[character], 1, 3, output) != -1) {
        return F_none;
      }
    }

    return F_status_set_error(F_output);
  }
#endif // _di_f_print_character_safely_

#ifndef _di_f_print_character_safely_get_
  f_string_t f_print_character_safely_get(const char character) {
    return private_f_print_character_safely_get(character);
  }
#endif // _di_f_print_character_safely_get_

#ifndef _di_f_print_dynamic_
  f_status_t f_print_dynamic(const f_string_static_t buffer, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print(buffer.string, buffer.used, output);
  }
#endif // _di_f_print_dynamic_

#ifndef _di_f_print_dynamic_partial_
  f_status_t f_print_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print(buffer.string + range.start, length, output);
  }
#endif // _di_f_print_dynamic_partial_

#ifndef _di_f_print_dynamic_partial_raw_
  f_status_t f_print_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_raw(buffer.string + range.start, length, output);
  }
#endif // _di_f_print_dynamic_partial_raw_

#ifndef _di_f_print_dynamic_partial_safely_
  f_status_t f_print_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_safely(buffer.string + range.start, length, output);
  }
#endif // _di_f_print_dynamic_partial_safely_

#ifndef _di_f_print_dynamic_raw_
  f_status_t f_print_dynamic_raw(const f_string_static_t buffer, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_raw(buffer.string, buffer.used, output);
  }
#endif // _di_f_print_dynamic_raw_

#ifndef _di_f_print_dynamic_safely_
  f_status_t f_print_dynamic_safely(const f_string_static_t buffer, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) {
      return F_data_not;
    }

    return private_f_print_safely(buffer.string, buffer.used, output);
  }
#endif // _di_f_print_dynamic_safely_

#ifndef _di_f_print_except_
  f_status_t f_print_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_except(string, offset, length, except, output);
  }
#endif // _di_f_print_except_

#ifndef _di_f_print_except_dynamic_
  f_status_t f_print_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_except(buffer.string, 0, buffer.used, except, output);
  }
#endif // _di_f_print_except_dynamic_

#ifndef _di_f_print_except_dynamic_partial_
  f_status_t f_print_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except(buffer.string, range.start, range.start + length, except, output);
  }
#endif // _di_f_print_except_dynamic_partial_

#ifndef _di_f_print_except_dynamic_partial_raw_
  f_status_t f_print_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except_raw(buffer.string, range.start, range.start + length, except, output);
  }
#endif // _di_f_print_except_dynamic_partial_raw_

#ifndef _di_f_print_except_dynamic_partial_safely_
  f_status_t f_print_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except_safely(buffer.string, range.start, range.start + length, except, output);
  }
#endif // _di_f_print_except_dynamic_partial_safely_

#ifndef _di_f_print_except_dynamic_raw_
  f_status_t f_print_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_except_raw(buffer.string, 0, buffer.used, except, output);
  }
#endif // _di_f_print_except_dynamic_raw_

#ifndef _di_f_print_except_dynamic_safely_
  f_status_t f_print_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_except_safely(buffer.string, 0, buffer.used, except, output);
  }
#endif // _di_f_print_except_dynamic_safely_

#ifndef _di_f_print_except_in_
  f_status_t f_print_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_except_in(string, offset, length, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_

#ifndef _di_f_print_except_in_dynamic_
  f_status_t f_print_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_except_in(buffer.string, 0, buffer.used, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_dynamic_

#ifndef _di_f_print_except_in_dynamic_partial_
  f_status_t f_print_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except_in(buffer.string, range.start, range.start + length, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_dynamic_partial_

#ifndef _di_f_print_except_in_dynamic_partial_raw_
  f_status_t f_print_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except_in_raw(buffer.string, range.start, range.start + length, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_dynamic_partial_raw_

#ifndef _di_f_print_except_in_dynamic_partial_safely_
  f_status_t f_print_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except_in_safely(buffer.string, range.start, range.start + length, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_dynamic_partial_safely_

#ifndef _di_f_print_except_in_dynamic_raw_
  f_status_t f_print_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_except_in_raw(buffer.string, 0, buffer.used, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_dynamic_raw_

#ifndef _di_f_print_except_in_dynamic_safely_
  f_status_t f_print_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.string || !buffer.used) return F_data_not;

    return private_f_print_except_in_safely(buffer.string, 0, buffer.used, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_dynamic_safely_

#ifndef _di_f_print_except_in_raw_
  f_status_t f_print_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_except_in_raw(string, offset, length, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_raw_

#ifndef _di_f_print_except_in_safely_
  f_status_t f_print_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_except_in_safely(string, offset, length, except_at, except_in, output);
  }
#endif // _di_f_print_except_in_safely_

#ifndef _di_f_print_except_raw_
  f_status_t f_print_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_except_raw(string, offset, length, except, output);
  }
#endif // _di_f_print_except_raw_

#ifndef _di_f_print_except_safely_
  f_status_t f_print_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_except_safely(string, offset, length, except, output);
  }
#endif // _di_f_print_except_safely_

#ifndef _di_f_print_raw_
  f_status_t f_print_raw(const f_string_t string, const f_array_length_t length, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_raw(string, length, output);
  }
#endif // _di_f_print_raw_

#ifndef _di_f_print_raw_terminated_
  f_status_t f_print_raw_terminated(const f_string_t string, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string) {
      return F_data_not;
    }

    // The f_print_raw_terminated() and f_print_terminated() are functionality identical due to being NULL terminated.
    return private_f_print_terminated(string, output);
  }
#endif // _di_f_print_raw_terminated_

#ifndef _di_f_print_safely_
  f_status_t f_print_safely(const f_string_t string, const f_array_length_t length, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print_safely(string, length, output);
  }
#endif // _di_f_print_safely_

#ifndef _di_f_print_safely_terminated_
  f_status_t f_print_safely_terminated(const f_string_t string, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
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
        if (fwrite_unlocked(string + start, 1, total, output) == -1) {
          return F_status_set_error(F_output);
        }

        total = 0;
      }

      if (status == F_true || F_status_set_fine(status) == F_utf) {
        if (fwrite_unlocked(f_print_sequence_unknown_s, 1, 3, output) != -1) {
          return F_status_set_error(F_output);
        }

        for (start = 0; string[start] && start < width; ) {
          ++start;
        } // while

        if (start != width) break;

        i += width;
      }
      else if (status == F_false) {
        if (fwrite_unlocked(string + start, 1, width, output) == -1) {
          return F_status_set_error(F_output);
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
          if (fwrite_unlocked(safe, 1, 3, output) == -1) {
            return F_status_set_error(F_output);
          }
        }
        else {
          status = f_utf_is_valid(string + i, width);

          if (F_status_is_error(status) || status == F_false) {
            if (fwrite_unlocked(f_print_sequence_unknown_s, 1, 3, output) == -1) {
              return F_status_set_error(F_output);
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
      if (fwrite_unlocked(string + start, 1, total, output) == -1) {
        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // _di_f_print_safely_terminated_

#ifndef _di_f_print_terminated_
  f_status_t f_print_terminated(const f_string_t string, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string) {
      return F_data_not;
    }

    return private_f_print_terminated(string, output);
  }
#endif // _di_f_print_terminated_

#ifdef __cplusplus
} // extern "C"
#endif

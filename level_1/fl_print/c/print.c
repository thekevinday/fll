#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_print_string_
  f_status_t fl_print_string(const f_string_t string, FILE *output, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    va_list ap;

    va_start(ap, output);

    for (char *current = string; *current; current = current + 1) {

      if (*current == f_string_ascii_percent_s[0]) {
        current = current + 1;

        status = private_fl_print_string_convert(current, output, &ap);
        if (F_status_is_error(status)) break;

        if (!*current) break;
      }
      else if (!fputc_unlocked(*current, output)) {
        return F_status_set_error(F_output);
      }
    } // for

    va_end(ap);

    return status;
  }
#endif // _di_fl_print_string_

#ifndef _di_fl_print_string_convert_
  f_status_t fl_print_string_convert(char *current, FILE *output, va_list *ap) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
      if (!ap) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_print_string_convert(current, output, ap);
  }
#endif // _di_fl_print_string_convert_

#ifndef _di_fl_print_string_va_
  f_status_t fl_print_string_va(const f_string_t string, FILE *output, va_list *ap) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
      if (!output) return F_status_set_error(F_parameter);
      if (!ap) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    uint8_t i = 0;

    char *current = string;
    char replace = *current;

    while (*current) {

      if (macro_f_utf_byte_width_is(*current)) {
        if (macro_f_utf_byte_width_is(*current) == 1) {
          if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
            return F_status_set_error(F_output);
          }
        }
        else {
          for (i = 0; i < macro_f_utf_byte_width_is(*current) && current[i]; ++i) {
            // do nothing.
          } // for

          if (i < macro_f_utf_byte_width_is(*current)) {
            if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
              return F_status_set_error(F_output);
            }

            break;
          }

          for (i = 0; i < macro_f_utf_byte_width_is(*current); ++i) {

            if (!fputc_unlocked(current[i], output)) {
              return F_status_set_error(F_output);
            }
          } // for

          current = current + (macro_f_utf_byte_width_is(*current) - 1);
        }
      }
      else {
        if (*current > 32 && *current != 127) {
          replace = *current;
        }
        else if (replace == 1) {
          replace = f_print_sequence_start_of_header_s[0];
        }
        else if (replace == 2) {
          replace = f_print_sequence_start_of_text_s[0];
        }
        else if (replace == 3) {
          replace = f_print_sequence_end_of_text_s[0];
        }
        else if (replace == 4) {
          replace = f_print_sequence_end_of_transmission_s[0];
        }
        else if (replace == 5) {
          replace = f_print_sequence_end_of_enquiry_s[0];
        }
        else if (replace == 6) {
          replace = f_print_sequence_acknowledge_s[0];
        }
        else if (replace == 7) {
          replace = f_print_sequence_bell_s[0];
        }
        else if (replace == 8) {
          replace = f_print_sequence_backspace_s[0];
        }
        else if (replace == 9) {
          replace = f_print_sequence_tab_s[0];
        }
        else if (replace == 10) {
          replace = f_print_sequence_new_line_s[0];
        }
        else if (replace == 11) {
          replace = f_print_sequence_tab_vertical_s[0];
        }
        else if (replace == 12) {
          replace = f_print_sequence_form_feed_s[0];
        }
        else if (replace == 13) {
          replace = f_print_sequence_carriage_return_s[0];
        }
        else if (replace == 14) {
          replace = f_print_sequence_shift_out_s[0];
        }
        else if (replace == 15) {
          replace = f_print_sequence_shift_in_s[0];
        }
        else if (replace == 16) {
          replace = f_print_sequence_data_link_escape_s[0];
        }
        else if (replace == 17) {
          replace = f_print_sequence_device_control_1_s[0];
        }
        else if (replace == 18) {
          replace = f_print_sequence_device_control_2_s[0];
        }
        else if (replace == 19) {
          replace = f_print_sequence_device_control_3_s[0];
        }
        else if (replace == 20) {
          replace = f_print_sequence_device_control_4_s[0];
        }
        else if (replace == 21) {
          replace = f_print_sequence_negative_acknowledge_s[0];
        }
        else if (replace == 22) {
          replace = f_print_sequence_synchronous_idle_s[0];
        }
        else if (replace == 23) {
          replace = f_print_sequence_end_of_transmission_block_s[0];
        }
        else if (replace == 24) {
          replace = f_print_sequence_cancel_s[0];
        }
        else if (replace == 25) {
          replace = f_print_sequence_end_of_medium_s[0];
        }
        else if (replace == 26) {
          replace = f_print_sequence_substitute_s[0];
        }
        else if (replace == 27) {
          replace = f_print_sequence_escape_s[0];
        }
        else if (replace == 28) {
          replace = f_print_sequence_file_separator_s[0];
        }
        else if (replace == 29) {
          replace = f_print_sequence_group_separator_s[0];
        }
        else if (replace == 30) {
          replace = f_print_sequence_record_separator_s[0];
        }
        else if (replace == 31) {
          replace = f_print_sequence_unit_separator_s[0];
        }
        else if (replace == 32) {
          replace = f_print_sequence_space_s[0];
        }
        else if (replace == 127) {
          replace = f_print_sequence_delete_s[0];
        }

        if (!fputc_unlocked(replace, output)) {
          return F_status_set_error(F_output);
        }
      }

      current = current + 1;
    } // while

    return F_none;
  }
#endif // _di_fl_print_string_va_

#ifndef _di_fl_print_trim_
  f_status_t fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim(string, length, output);
  }
#endif // _di_fl_print_trim_

#ifndef _di_fl_print_trim_raw_
  f_status_t fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_raw(string, length, output);
  }
#endif // _di_fl_print_trim_raw_

#ifndef _di_fl_print_trim_safely_
  f_status_t fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_safely(string, length, output);
  }
#endif // _di_fl_print_trim_safely_

#ifndef _di_fl_print_trim_dynamic_
  f_status_t fl_print_trim_dynamic(const f_string_static_t buffer, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim(buffer.string, buffer.used, output);
  }
#endif // _di_fl_print_trim_dynamic_

#ifndef _di_fl_print_trim_dynamic_raw_
  f_status_t fl_print_trim_dynamic_raw(const f_string_static_t buffer, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_raw(buffer.string, buffer.used, output);
  }
#endif // _di_fl_print_trim_dynamic_raw_

#ifndef _di_fl_print_trim_dynamic_safely_
  f_status_t fl_print_trim_dynamic_safely(const f_string_static_t buffer, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_safely(buffer.string, buffer.used, output);
  }
#endif // _di_fl_print_trim_dynamic_safely_

#ifndef _di_fl_print_trim_dynamic_partial_
  f_status_t fl_print_trim_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim(buffer.string + range.start, length, output);
  }
#endif // _di_fl_print_trim_dynamic_partial_

#ifndef _di_fl_print_trim_dynamic_partial_raw_
  f_status_t fl_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_raw(buffer.string + range.start, length, output);
  }
#endif // _di_fl_print_trim_dynamic_partial_raw_

#ifndef _di_fl_print_trim_dynamic_partial_safely_
  f_status_t fl_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_safely(buffer.string + range.start, length, output);
  }
#endif // _di_fl_print_trim_dynamic_partial_safely_

#ifndef _di_fl_print_trim_except_
  f_status_t fl_print_trim_except(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in(string, length, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_

#ifndef _di_fl_print_trim_except_raw_
  f_status_t fl_print_trim_except_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(string, length, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_raw_

#ifndef _di_fl_print_trim_except_safely_
  f_status_t fl_print_trim_except_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(string, length, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_safely_

#ifndef _di_fl_print_trim_except_dynamic_
  f_status_t fl_print_trim_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in(buffer.string, buffer.used, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_dynamic_

#ifndef _di_fl_print_trim_except_dynamic_raw_
  f_status_t fl_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(buffer.string, buffer.used, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_dynamic_raw_

#ifndef _di_fl_print_trim_except_dynamic_safely_
  f_status_t fl_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(buffer.string, buffer.used, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_dynamic_safely_

#ifndef _di_fl_print_trim_except_in_
  f_status_t fl_print_trim_except_in(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in(string, length, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_

#ifndef _di_fl_print_trim_except_in_raw_
  f_status_t fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_raw(string, length, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_raw_

#ifndef _di_fl_print_trim_except_in_safely_
  f_status_t fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_safely(string, length, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_
  f_status_t fl_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in(buffer.string, buffer.used, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_dynamic_

#ifndef _di_fl_print_trim_except_in_dynamic_raw_
  f_status_t fl_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_raw(buffer.string, buffer.used, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_dynamic_raw_

#ifndef _di_fl_print_trim_except_in_dynamic_safely_
  f_status_t fl_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_print_trim_except_in_safely(buffer.string, buffer.used, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_dynamic_safely_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_
  f_status_t fl_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in(buffer.string + range.start, length, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_raw_
  f_status_t fl_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_raw(buffer.string + range.start, length, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_raw_

#ifndef _di_fl_print_trim_except_in_dynamic_partial_safely_
  f_status_t fl_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_fl_print_trim_except_in_safely(buffer.string + range.start, length, except_at, except_in, output);
  }
#endif // _di_fl_print_trim_except_in_dynamic_partial_safely_

#ifndef _di_fl_print_trim_except_dynamic_partial_
  f_status_t fl_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in(buffer.string + range.start, length, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_

#ifndef _di_fl_print_trim_except_dynamic_partial_raw_
  f_status_t fl_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_raw(buffer.string + range.start, length, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_raw_

#ifndef _di_fl_print_trim_except_dynamic_partial_safely_
  f_status_t fl_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output) {
    #ifndef _di_level_1_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    const f_string_ranges_t except_in = f_string_ranges_t_initialize;

    return private_fl_print_trim_except_in_safely(buffer.string + range.start, length, except, except_in, output);
  }
#endif // _di_fl_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

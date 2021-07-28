#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  f_status_t private_f_print(const f_string_t string, const f_array_length_t length, FILE *output) {

    for (register f_array_length_t i = 0; i < length; ++i) {

      if (string[i]) {
        if (!fputc_unlocked(string[i], output)) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

#if !defined(_di_f_print_character_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)
  f_status_t private_f_print_character_safely(const char character, FILE *output) {

    if (character > 31 && character != 127) {
      if (!fputc_unlocked(character, output)) {
        return F_status_set_error(F_output);
      }
    }

    f_string_t string = 0;

    if (character == 0) {
      string = f_print_sequence_null_s;
    }
    else if (character == 1) {
      string = f_print_sequence_start_of_header_s;
    }
    else if (character == 2) {
      string = f_print_sequence_start_of_text_s;
    }
    else if (character == 3) {
      string = f_print_sequence_end_of_text_s;
    }
    else if (character == 4) {
      string = f_print_sequence_end_of_transmission_s;
    }
    else if (character == 5) {
      string = f_print_sequence_end_of_enquiry_s;
    }
    else if (character == 6) {
      string = f_print_sequence_acknowledge_s;
    }
    else if (character == 7) {
      string = f_print_sequence_bell_s;
    }
    else if (character == 8) {
      string = f_print_sequence_backspace_s;
    }
    else if (character == 9) {
      string = f_print_sequence_tab_s;
    }
    else if (character == 10) {
      string = f_print_sequence_new_line_s;
    }
    else if (character == 11) {
      string = f_print_sequence_tab_vertical_s;
    }
    else if (character == 12) {
      string = f_print_sequence_form_feed_s;
    }
    else if (character == 13) {
      string = f_print_sequence_carriage_return_s;
    }
    else if (character == 14) {
      string = f_print_sequence_shift_out_s;
    }
    else if (character == 15) {
      string = f_print_sequence_shift_in_s;
    }
    else if (character == 16) {
      string = f_print_sequence_data_link_escape_s;
    }
    else if (character == 17) {
      string = f_print_sequence_device_control_1_s;
    }
    else if (character == 18) {
      string = f_print_sequence_device_control_2_s;
    }
    else if (character == 19) {
      string = f_print_sequence_device_control_3_s;
    }
    else if (character == 20) {
      string = f_print_sequence_device_control_4_s;
    }
    else if (character == 21) {
      string = f_print_sequence_negative_acknowledge_s;
    }
    else if (character == 22) {
      string = f_print_sequence_synchronous_idle_s;
    }
    else if (character == 23) {
      string = f_print_sequence_end_of_transmission_block_s;
    }
    else if (character == 24) {
      string = f_print_sequence_cancel_s;
    }
    else if (character == 25) {
      string = f_print_sequence_end_of_medium_s;
    }
    else if (character == 26) {
      string = f_print_sequence_substitute_s;
    }
    else if (character == 27) {
      string = f_print_sequence_escape_s;
    }
    else if (character == 28) {
      string = f_print_sequence_file_separator_s;
    }
    else if (character == 29) {
      string = f_print_sequence_group_separator_s;
    }
    else if (character == 30) {
      string = f_print_sequence_record_separator_s;
    }
    else if (character == 31) {
      string = f_print_sequence_unit_separator_s;
    }
    else {

      // character == 127.
      string = f_print_sequence_delete_s;
    }

    if (!fputc_unlocked(character, output)) {
      return F_status_set_error(F_output);
    }

    if (!fputc_unlocked(character, output)) {
      return F_status_set_error(F_output);
    }

    if (!fputc_unlocked(character, output)) {
      return F_status_set_error(F_output);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_character_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)

#if !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_to_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)
  f_string_t private_f_print_character_safely_get(const char character) {

    if (character > 31 && character != 127) {
      return 0;
    }

    if (character == 0) {
      return f_print_sequence_null_s;
    }

    if (character == 1) {
      return f_print_sequence_start_of_header_s;
    }

    if (character == 2) {
      return f_print_sequence_start_of_text_s;
    }

    if (character == 3) {
      return f_print_sequence_end_of_text_s;
    }

    if (character == 4) {
      return f_print_sequence_end_of_transmission_s;
    }

    if (character == 5) {
      return f_print_sequence_end_of_enquiry_s;
    }

    if (character == 6) {
      return f_print_sequence_acknowledge_s;
    }

    if (character == 7) {
      return f_print_sequence_bell_s;
    }

    if (character == 8) {
      return f_print_sequence_backspace_s;
    }

    if (character == 9) {
      return f_print_sequence_tab_s;
    }

    if (character == 10) {
      return f_print_sequence_new_line_s;
    }

    if (character == 11) {
      return f_print_sequence_tab_vertical_s;
    }

    if (character == 12) {
      return f_print_sequence_form_feed_s;
    }

    if (character == 13) {
      return f_print_sequence_carriage_return_s;
    }

    if (character == 14) {
      return f_print_sequence_shift_out_s;
    }

    if (character == 15) {
      return f_print_sequence_shift_in_s;
    }

    if (character == 16) {
      return f_print_sequence_data_link_escape_s;
    }

    if (character == 17) {
      return f_print_sequence_device_control_1_s;
    }

    if (character == 18) {
      return f_print_sequence_device_control_2_s;
    }

    if (character == 19) {
      return f_print_sequence_device_control_3_s;
    }

    if (character == 20) {
      return f_print_sequence_device_control_4_s;
    }

    if (character == 21) {
      return f_print_sequence_negative_acknowledge_s;
    }

    if (character == 22) {
      return f_print_sequence_synchronous_idle_s;
    }

    if (character == 23) {
      return f_print_sequence_end_of_transmission_block_s;
    }

    if (character == 24) {
      return f_print_sequence_cancel_s;
    }

    if (character == 25) {
      return f_print_sequence_end_of_medium_s;
    }

    if (character == 26) {
      return f_print_sequence_substitute_s;
    }

    if (character == 27) {
      return f_print_sequence_escape_s;
    }

    if (character == 28) {
      return f_print_sequence_file_separator_s;
    }

    if (character == 29) {
      return f_print_sequence_group_separator_s;
    }

    if (character == 30) {
      return f_print_sequence_record_separator_s;
    }

    if (character == 31) {
      return f_print_sequence_unit_separator_s;
    }

    // character == 127.
    return f_print_sequence_delete_s;
  }
#endif // !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_to_safely_) || !defined(_di_f_print_dynamic_partial_to_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)

#if !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)
  f_status_t private_f_print_raw(const f_string_t string, const f_array_length_t length, FILE *output) {

    for (register f_array_length_t i = 0; i < length; ++i) {

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)

#if !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)
  f_status_t private_f_print_safely(const f_string_t string, const f_array_length_t length, FILE *output) {

    register f_array_length_t i = 0;

    f_status_t status = F_none;
    f_string_t s = 0;

    while (i < length) {

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
        status = f_utf_is_valid(string + i, length - i);

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

        if (i + macro_f_utf_byte_width(string[i]) >= length) {
          if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
            return F_status_set_error(F_output);
          }

          if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
            return F_status_set_error(F_output);
          }

          i = length;
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
#endif // !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)

#if !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)
  f_status_t private_f_print_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE *output) {

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

    for (char *current = string; *current; current = current + 1) {

      if (!fputc_unlocked(*current, output)) {
        return F_status_set_error(F_output);
      }
    } // for

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

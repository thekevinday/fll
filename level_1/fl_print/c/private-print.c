#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)
  f_status_t private_fl_print_string_convert(char *current, va_list *ap, FILE *output) {

    // An unpaired '%' character must not be at the end of the string.
    if (!*current) {
      return F_status_set_error(F_valid_not);
    }

    uint8_t base = 10;
    uint16_t flag = 0;
    uint8_t type = 0;

    unsigned int width = 1;
    unsigned int precision = 1;

    for (; *current; current = current + 1) {

      if (*current == f_string_ascii_minus_s[0]) {
        flag |= f_print_format_flag_align_left;
      }
      else if (*current == f_string_ascii_pound_s[0]) {
        flag |= f_print_format_flag_convert;
      }
      else if (*current == f_string_ascii_parenthesis_open_s[0]) {
        flag |= f_print_format_flag_ignore_index; // @todo
      }
      else if (*current == f_string_ascii_parenthesis_close_s[0]) {
        flag |= f_print_format_flag_ignore_range; // @todo
      }
      else if (*current == f_string_ascii_plus_s[0]) {
        flag |= f_print_format_flag_sign_always;
      }
      else if (*current == f_string_ascii_space_s[0]) {
        flag |= f_print_format_flag_sign_pad;
      }
      else if (*current == f_string_ascii_equal_s[0]) {
        flag |= f_print_format_flag_trim;
      }
      else if (*current == f_string_ascii_0_s[0] || *current == f_string_ascii_1_s[0] || *current == f_string_ascii_2_s[0] || *current == f_string_ascii_3_s[0] || *current == f_string_ascii_4_s[0] || *current == f_string_ascii_5_s[0] || *current == f_string_ascii_6_s[0] || *current == f_string_ascii_7_s[0] || *current == f_string_ascii_8_s[0] || *current == f_string_ascii_9_s[0]) {

        if (!(flag & f_print_format_flag_width)) {
          if (*current == f_string_ascii_0_s[0]) {
            flag |= f_print_format_flag_zeros_leading;
          }
          else {
            flag |= f_print_format_flag_width;

            if (private_fl_print_convert_number(current, ap, &width)) {
              break;
            }
          }
        }
        else {
          return F_status_set_error(F_valid_not);
        }
      }
      else if (*current == f_string_ascii_dollar_s[0]) {
        // If followed immediately by a '$' this is ignored.
        // Use '%$' to separate, such as '%l%$l' would allow for '0l' to be printed where '%ll' would interpret the 'l', resulting in a long long.
        return F_none;
      }
      else if (*current == f_string_ascii_exclamation_s[0]) {
        base = 2;
      }
      else if (*current == f_string_ascii_sign_at_s[0]) {
        base = 8;
      }
      else if (*current == f_string_ascii_caret_s[0]) {
        base = 10;
      }
      else if (*current == f_string_ascii_ampersand_s[0]) {
        base = 12;
      }
      else if (*current == f_string_ascii_underscore_s[0]) {
        base = 16;
      }
      else if (*current == f_string_ascii_period_s[0]) {
        if (!*(current + 1)) {
          return F_status_set_error(F_valid_not);
        }

        if (private_fl_print_convert_number(current, ap, &precision)) {
          break;
        }

        continue;
      }
      else {
        if (*current == f_string_ascii_c_s[0]) {

          // char.
          const char value = (char) va_arg(*ap, int);

          if (!fputc_unlocked(value, output)) {
            return F_status_set_error(F_output);
          }

          return F_none;
        }
        else if (*current == f_string_ascii_C_s[0]) {

          // safe character.
          char value[1] = { (char) va_arg(*ap, int) };

          return f_print_safely(value, 1, output);
        }
        else if (*current == f_string_ascii_i_s[0]) {
          type = f_print_format_type_signed;

          if (*(current + 1) == f_string_ascii_i_s[0]) {
            if (*(current + 2) == f_string_ascii_i_s[0]) {
              type = f_print_format_type_signed_8;
              current = current + 2;
            }
            else {
              type = f_print_format_type_signed_16;
              current = current + 1;
            }
          }
        }
        else if (*current == f_string_ascii_I_s[0]) {
          type = f_print_format_type_signed;
          flag |= f_print_format_flag_uppercase;

          if (*(current + 1) == f_string_ascii_I_s[0]) {
            if (*(current + 2) == f_string_ascii_I_s[0]) {
              type = f_print_format_type_signed_8;
              current = current + 2;
            }
            else {
              type = f_print_format_type_signed_16;
              current = current + 1;
            }
          }
        }
        else if (*current == f_string_ascii_l_s[0]) {
          type = f_print_format_type_long;

          if (*(current + 1) == f_string_ascii_l_s[0]) {
            type = f_print_format_type_long_long;
            current = current + 1;
          }
        }
        else if (*current == f_string_ascii_L_s[0]) {
          type = f_print_format_type_long;
          flag |= f_print_format_flag_uppercase;

          if (*(current + 1) == f_string_ascii_L_s[0]) {
            type = f_print_format_type_long_long;
            current = current + 1;
          }
        }
        else if (*current == f_string_ascii_n_s[0]) {
          type = f_print_format_type_number;
        }
        else if (*current == f_string_ascii_N_s[0]) {
          type = f_print_format_type_number;
          flag |= f_print_format_flag_uppercase;
        }
        else if (*current == f_string_ascii_q_s[0]) {

          // static/dynamic string.
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            return private_fl_print_trim(value.string, value.used, output);
          }

          return f_print_dynamic(value, output);
        }
        else if (*current == f_string_ascii_Q_s[0]) {

          // safe static/dynamic string.
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            return private_fl_print_trim(value.string, value.used, output);
          }

          return f_print_dynamic_safely(value, output);
        }
        else if (*current == f_string_ascii_r_s[0]) {

          // raw static/dynamic string.
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            return private_fl_print_trim(value.string, value.used, output);
          }

          return f_print_dynamic_raw(value, output);
        }
        else if (*current == f_string_ascii_s_s[0]) {

          // NULL terminated string.
          const f_string_t value = va_arg(*ap, f_string_t);

          if (flag & f_print_format_flag_trim) {
            // @todo: implement a: private_fl_print_trim_teminated().
            //return private_fl_print_trim_teminated(value, output);
          }

          return f_print_terminated(value, output);
        }
        else if (*current == f_string_ascii_S_s[0]) {

          // NULL terminated static/dynamic string.
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            return private_fl_print_trim(value.string, value.used, output);
          }

          return f_print_dynamic(value, output);
        }
        else if (*current == f_string_ascii_u_s[0]) {
          type = f_print_format_type_unsigned;

          if (*(current + 1)) {
            if (*(current + 1) == f_string_ascii_i_s[0]) {
              if (*(current + 2) == f_string_ascii_i_s[0]) {
                type = f_print_format_type_unsigned_8;
                current = current + 2;
              }
              else {
                type = f_print_format_type_unsigned_16;
                current = current + 1;
              }
            }
            else if (*(current + 1) == f_string_ascii_n_s[0]) {
              if (*(current + 2) == f_string_ascii_l_s[0]) {
                type = f_print_format_type_unsigned_long_long;
                current = current + 2;
              }
              else {
                type = f_print_format_type_unsigned_long;
                current = current + 1;
              }
            }
            else if (*(current + 1) == f_string_ascii_n_s[0]) {
              type = f_print_format_type_unsigned_number;
              current = current + 1;
            }
          }
        }
        else if (*current == f_string_ascii_U_s[0]) {
          type = f_print_format_type_unsigned;
          flag |= f_print_format_flag_uppercase;

          if (*(current + 1)) {
            if (*(current + 1) == f_string_ascii_I_s[0]) {
              if (*(current + 2) == f_string_ascii_I_s[0]) {
                type = f_print_format_type_unsigned_8;
                current = current + 2;
              }
              else {
                type = f_print_format_type_unsigned_16;
                current = current + 1;
              }
            }
            else if (*(current + 1) == f_string_ascii_N_s[0]) {
              if (*(current + 2) == f_string_ascii_L_s[0]) {
                type = f_print_format_type_unsigned_long_long;
                current = current + 2;
              }
              else {
                type = f_print_format_type_unsigned_long;
                current = current + 1;
              }
            }
            else if (*(current + 1) == f_string_ascii_N_s[0]) {
              type = f_print_format_type_unsigned_number;
              current = current + 1;
            }
          }
        }
        else if (*current == f_string_ascii_z_s[0]) {
          type = f_print_format_type_size;
        }
        else if (*current == f_string_ascii_Z_s[0]) {
          type = f_print_format_type_size;
          flag |= f_print_format_flag_uppercase;
        }
        else {
          return F_status_set_error(F_valid_not);
        }

        f_conversion_data_t conversion_data = macro_f_conversion_data_t_initialize(base, 0, 1);

        if (flag & f_print_format_flag_align_left) {
          conversion_data.flag |= f_conversion_data_flag_align_left;
        }

        if (flag & f_print_format_flag_convert) {
          conversion_data.flag |= f_conversion_data_flag_base_prepend;
        }

        if (flag & f_print_format_flag_sign_always) {
          conversion_data.flag |= f_conversion_data_flag_sign_always;
        }

        if (flag & f_print_format_flag_sign_pad) {
          conversion_data.flag |= f_conversion_data_flag_sign_pad;
        }

        if (flag & f_print_format_flag_uppercase) {
          conversion_data.flag |= f_conversion_data_flag_base_upper;
        }

        if (flag & f_print_format_flag_zeros_leading) {
          conversion_data.flag |= f_conversion_data_flag_zeros_leading;
        }

        if (flag & f_print_format_flag_width) {
          conversion_data.width = width;
        }
        else if (flag & f_print_format_flag_precision) {
          conversion_data.width = precision;
        }

        f_status_t status = F_none;

        if (type == f_print_format_type_long) {
          status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, long), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_long_long) {
          status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, long), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_number) {
          status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, f_number_signed_t), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_signed) {
          status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, int), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_signed_16) {
          // @todo research this: 'short int' is promoted to 'int' when passed through '...'.
          const int16_t value = (int16_t) va_arg(*ap, int);

          status = f_conversion_number_signed_to_file((f_number_signed_t) value, conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_signed_8) {
          // @todo research this: 'signed char' is promoted to 'int' when passed through '...'.
          const int8_t value = (int8_t) va_arg(*ap, int);

          status = f_conversion_number_signed_to_file((f_number_signed_t) value, conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_size) {
          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, size_t), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_unsigned) {
          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, unsigned int), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_unsigned_16) {
          // @todo research this: 'short unsigned int' is promoted to 'int' when passed through '...'.
          const uint16_t value = (uint16_t) va_arg(*ap, int);

          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) value, conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_unsigned_8) {
          // @todo research this: 'unsigned char' is promoted to 'int' when passed through '...'.
          const uint8_t value = (uint8_t) va_arg(*ap, int);

          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) value, conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_unsigned_long) {
          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, unsigned long), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_unsigned_long_long) {
          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, unsigned long long), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }
        else if (type == f_print_format_type_unsigned_number) {
          status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, f_number_unsigned_t), conversion_data, output);
          if (F_status_is_error(status)) return status;
        }

        return F_none;
      }
    } // for

    if (*current) {
      return F_none;
    }

    return F_status_set_error(F_valid_not);
  }
#endif // !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)

#if !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)
  f_status_t private_fl_print_convert_number(char *current, va_list *ap, unsigned int *number) {

    *number = 0;

    for (current = current + 1; *current; current = current + 1) {

      if (*current == f_string_ascii_0_s[0]) {
        *number *= 10;
      }
      else if (*current == f_string_ascii_1_s[0]) {
        *number *= 10;
        *number += 1;
      }
      else if (*current == f_string_ascii_2_s[0]) {
        *number *= 10;
        *number += 2;
      }
      else if (*current == f_string_ascii_3_s[0]) {
        *number *= 10;
        *number += 3;
      }
      else if (*current == f_string_ascii_4_s[0]) {
        *number *= 10;
        *number += 4;
      }
      else if (*current == f_string_ascii_5_s[0]) {
        *number *= 10;
        *number += 5;
      }
      else if (*current == f_string_ascii_6_s[0]) {
        *number *= 10;
        *number += 6;
      }
      else if (*current == f_string_ascii_7_s[0]) {
        *number *= 10;
        *number += 7;
      }
      else if (*current == f_string_ascii_8_s[0]) {
        *number *= 10;
        *number += 8;
      }
      else if (*current == f_string_ascii_9_s[0]) {
        *number *= 10;
        *number += 9;
      }
      else if (*current == f_string_ascii_asterisk_s[0]) {
        *number = va_arg(*ap, unsigned int);

        break;
      }
      else {
        break;
      }
    } // for

    if (!*current) return F_false;

    return F_true;
  }
#endif // !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)

#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)
  f_status_t private_fl_print_trim_except_in(const f_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    // @todo resume converting this function.
    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    // skip past leading whitespace.
    while (i < stop) {

      if (!string[i]) {
        ++i;

        continue;
      }

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (stop - i) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    f_string_t s = 0;

    while (i < stop) {

      if (!string[i]) {
        ++i;

        continue;
      }

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

      status = f_utf_is_whitespace(string + i, (stop - i) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + macro_f_utf_byte_width(string[i]);

        while (j < stop) {

          if (!string[j]) {
            ++j;

            continue;
          }

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop < j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          status = f_utf_is_whitespace(string + j, (stop - j) + 1);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          if (status == F_false) break;
        } // while

        if (j == stop || status == F_true) break;

        // print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (!string[i]) {
            ++i;

            continue;
          }

          while (at < except_at.used && except_at.array[at] < i) {
            ++at;
          } // while

          if (at < except_at.used && except_at.array[at] == i) {
            ++i;

            continue;
          }

          while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
            ++in;
          } // while

          if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
            i = except_in.array[in].stop + 1;

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
            status = F_none;
            break;
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
        } // while

        if (i >= stop) break;
      }

      status = f_utf_is_valid(string + i, stop - i);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

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
    } // while
  }
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)

#if !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    // skip past leading whitespace.
    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      width_max = (stop - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      width_max = (stop - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + macro_f_utf_byte_width(string[i]);

        if (j == stop) {
          return F_none;
        }

        at2 = at;

        while (j < stop) {

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop <= j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          width_max = (stop - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            while (i < j) {

              while (at < except_at.used && except_at.array[at] < i) {
                ++at;
              } // while

              if (at < except_at.used && except_at.array[at] == i) {
                ++i;

                continue;
              }

              while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
                ++in;
              } // while

              if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
                i = except_in.array[in].stop + 1;

                continue;
              }

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }

              ++i;
            } // while

            break;
          }

          j += macro_f_utf_byte_width(string[j]);
        } // while

        if (status == F_true) break;
      }

      width_max = macro_f_utf_byte_width(string[i]);

      for (j = 0; j < width_max; ++j) {

        if (!fputc_unlocked(string[i + j], output)) {
          return F_status_set_error(F_output);
        }
      } // for

      i += width_max;
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    // skip past leading whitespace.
    while (i < stop) {

      // Consider NULL whitespace for the purposes of trimming (@todo update documentation to describe this behavior).
      if (!string[i]) {
        ++i;

        continue;
      }

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (stop - i) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

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

      status = f_utf_is_whitespace(string + i, (stop - i) + 1);

      // invalid UTF-8 characters will be considered non-whitespace.
      if (F_status_is_error(status)) {
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

      if (status == F_true) { // @todo: update to handle NULL as whitespace in this condition.
        j = i + macro_f_utf_byte_width(string[i]);

        while (j < stop) {

          // Consider NULL whitespace for the purposes of trimming (@todo update documentation to describe this behavior).
          if (!string[i]) {
            ++j;

            continue;
          }

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop < j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          status = f_utf_is_whitespace(string + j, (stop - j) + 1);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;
        } // while

        if (j == stop || status == F_true) break;

        // print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          while (at < except_at.used && except_at.array[at] < i) {
            ++at;
          } // while

          if (at < except_at.used && except_at.array[at] == i) {
            ++i;

            continue;
          }

          while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
            ++in;
          } // while

          if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
            i = except_in.array[in].stop + 1;

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
            status = F_none;
            break;
          }

          if (string[i]) {
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
          else {
            if (!fputc_unlocked(f_print_sequence_null_s[0], output)) {
              return F_status_set_error(F_output);
            }

            if (!fputc_unlocked(f_print_sequence_null_s[1], output)) {
              return F_status_set_error(F_output);
            }

            if (!fputc_unlocked(f_print_sequence_null_s[2], output)) {
              return F_status_set_error(F_output);
            }

            ++i;
          }
        } // while

        // at this point the invalid character found while looping with j shall be safely printed.
        if (F_status_is_error(status)) {
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

        if (i >= stop) break;
      }

      s = f_print_character_safely_get(string[i]);

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
#endif // !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)

#if !defined(_di_fl_print_trim_except_in_utf_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_) || !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)
  f_status_t private_fl_print_trim_except_in_utf(const f_utf_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      ++i;
    } // while

    while (i < stop) {

      if (!string[i]) {
        ++i;

        continue;
      }

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == stop) {
          return F_none;
        }

        at2 = at;

        while (j < stop) {

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop <= j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            while (i < j) {

              if (!string[i]) {
                ++i;

                continue;
              }

              while (at < except_at.used && except_at.array[at] < i) {
                ++at;
              } // while

              if (at < except_at.used && except_at.array[at] == i) {
                ++i;

                continue;
              }

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }

              ++i;
            } // while

            break;
          }

          ++j;
        } // while

        if (status == F_true) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }

      ++i;
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_in_utf_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_) || !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)

#if !defined(_di_fl_print_trim_except_in_utf_raw_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_utf_raw_) || !defined(_di_fl_print_trim_except_utf_dynamic_raw_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_except_in_utf_raw(const f_utf_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      ++i;
    } // while

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == stop) {
          return F_none;
        }

        at2 = at;

        while (j < stop) {

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop <= j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            while (i < j) {

              while (at < except_at.used && except_at.array[at] < i) {
                ++at;
              } // while

              if (at < except_at.used && except_at.array[at] == i) {
                ++i;

                continue;
              }

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }

              ++i;
            } // while

            break;
          }

          ++j;
        } // while

        if (status == F_true) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }

      ++i;
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_in_utf_raw_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_utf_raw_) || !defined(_di_fl_print_trim_except_utf_dynamic_raw_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_except_in_utf_safely_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_utf_safely_) || !defined(_di_fl_print_trim_except_utf_dynamic_safely_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_except_in_utf_safely(const f_utf_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = start;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
        ++in;
      } // while

      if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
        i = except_in.array[in].stop + 1;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;

      ++i;
    } // while

    while (i < stop) {

      if (!string[i]) { // @todo each of these needs to be replaced with a get safe check.
        ++i;

        continue;
      }

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        ++i;

        continue;
      }

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == stop) {
          return F_none;
        }

        at2 = at;

        while (j < stop) {

          while (at2 < except_at.used && except_at.array[at2] < j) {
            ++at2;
          } // while

          if (at2 < except_at.used && except_at.array[at2] == j) {
            ++j;

            continue;
          }

          while (in2 < except_in.used && except_in.array[in2].start < j && except_in.array[in2].stop <= j) {
            ++in2;
          } // while

          if (in2 < except_in.used && except_in.array[in2].start <= j && except_in.array[in2].stop >= j) {
            j = except_in.array[in2].stop + 1;

            continue;
          }

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            while (i < j) {

              if (!string[i]) {
                ++i;

                continue;
              }

              while (at < except_at.used && except_at.array[at] < i) {
                ++at;
              } // while

              if (at < except_at.used && except_at.array[at] == i) {
                ++i;

                continue;
              }

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }

              ++i;
            } // while

            break;
          }

          ++j;
        } // while

        if (status == F_true) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }

      ++i;
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_in_utf_safely_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_utf_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_utf_safely_) || !defined(_di_fl_print_trim_except_utf_dynamic_safely_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_safely_)

#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  f_status_t private_fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

      if (!string[i]) continue;

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + macro_f_utf_byte_width(string[i]);

        if (j == length) {
          return F_none;
        }

        for (; j < length; j += macro_f_utf_byte_width(string[j])) {

          width_max = (length - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {

              if (!string[i]) continue;

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      width_max = macro_f_utf_byte_width(string[i]);

      for (j = 0; j < width_max; ++j) {

        if (!fputc_unlocked(string[i + j], output)) {
          return F_status_set_error(F_output);
        }
      } // for
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

#if !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + macro_f_utf_byte_width(string[i]);

        if (j == length) {
          return F_none;
        }

        for (; j < length; j += macro_f_utf_byte_width(string[j])) {

          width_max = (length - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      width_max = macro_f_utf_byte_width(string[i]);

      for (j = 0; j < width_max; ++j) {

        if (!fputc_unlocked(string[i + j], output)) {
          return F_status_set_error(F_output);
        }
      } // for
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;
    uint8_t width_max = 0;

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; i += macro_f_utf_byte_width(string[i])) {

      if (!string[i]) continue; // @todo each of these needs to be replaced with a get safe check.

      width_max = (length - i) + 1;
      status = f_utf_is_whitespace(string + i, width_max);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + macro_f_utf_byte_width(string[i]);

        if (j == length) {
          return F_none;
        }

        for (; j < length; j += macro_f_utf_byte_width(string[j])) {

          width_max = (length - j) + 1;
          status = f_utf_is_whitespace(string + j, width_max);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {

              if (!string[i]) continue;

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      width_max = macro_f_utf_byte_width(string[i]);

      for (j = 0; j < width_max; ++j) {

        if (!fputc_unlocked(string[i + j], output)) {
          return F_status_set_error(F_output);
        }
      } // for
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)

#if !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)
  f_status_t private_fl_print_trim_utf(const f_utf_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    for (; i < length; ++i) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; ++i) {

      if (!string[i]) continue;

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == length) {
          return F_none;
        }

        for (; j < length; ++j) {

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {

              if (!string[i]) continue;

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)

#if !defined(_di_fl_print_trim_utf_raw_) || !defined(_di_fl_print_trim_utf_dynamic_raw_) || !defined(_di_fl_print_trim_utf_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_utf_raw(const f_utf_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    for (; i < length; ++i) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; ++i) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == length) {
          return F_none;
        }

        for (; j < length; ++j) {

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_utf_raw_) || !defined(_di_fl_print_trim_utf_dynamic_raw_) || !defined(_di_fl_print_trim_utf_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_utf_safely_) || !defined(_di_fl_print_trim_utf_dynamic_safely_) || !defined(_di_fl_print_trim_utf_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_utf_safely(const f_utf_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    for (; i < length; ++i) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false) break;
    } // for

    for (; i < length; ++i) {

      status = f_utf_character_is_whitespace(string[i]);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_true) {
        j = i + 1;

        if (j == length) {
          return F_none;
        }

        for (; j < length; ++j) {

          status = f_utf_character_is_whitespace(string[j]);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          // all whitespaces found so far must be printed when a non-whitespace is found.
          if (status == F_false) {
            for (; i < j; ++i) {


              /* @todo
              s = f_print_character_safely_get(string[i]); // @todo: in addition to this, the width of the character at string[i] needs to be taken into consideration.

              if (s) {
                //
                status = F_false;
              }
              */

              if (!string[i]) continue;

              if (!fputc_unlocked(string[i], output)) {
                return F_status_set_error(F_output);
              }
            } // for

            break;
          }
        } // for

        if (status == F_true) break;
      }

      s = f_print_character_safely_get(string[i]); // @todo: in addition to this, the width of the character at string[i] needs to be taken into consideration.

      if (s) {
        //
        status = F_false;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_utf_safely_) || !defined(_di_fl_print_trim_utf_dynamic_safely_) || !defined(_di_fl_print_trim_utf_dynamic_partial_safely_)

#ifdef __cplusplus
} // extern "C"
#endif

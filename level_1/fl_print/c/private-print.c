#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)
  f_string_t private_fl_print_string_convert(f_string_t string, FILE *output, va_list *ap, f_status_t *status) {

    const f_string_t start = string;

    // An unpaired '%' character must not be at the end of the string.
    if (!*string) {
      *status = F_status_set_error(F_valid_not);
      return string;
    }

    *status = F_none;

    uint8_t base = 10;
    uint16_t flag = 0;
    uint8_t type = 0;

    unsigned int width = 1;
    unsigned int precision = 1;

    for (; *string; string += 1) {

      if (*string < 0x2c) {
        if (*string == f_string_ascii_space_s[0]) {
          flag |= f_print_format_flag_sign_pad;

          continue;
        }
        else if (*string == f_string_ascii_exclamation_s[0]) {
          base = 2;

          continue;
        }
        else if (*string == f_string_ascii_pound_s[0]) {
          flag |= f_print_format_flag_convert;

          continue;
        }
        else if (*string == f_string_ascii_dollar_s[0]) {

          // If followed immediately by a '$' this is ignored.
          // Use '%$' to separate, such as '%l%$l' would allow for '0l' to be printed where '%ll' would interpret the 'l', resulting in a long long.
          return string;
        }
        else if (*string == f_string_ascii_percent_s[0]) {

          // The first percent found represents a literal '%' to be printed, otherwise return as invalid.
          if (string == start) {
            if (!fputc_unlocked(f_string_ascii_percent_s[0], output)) {
              return string;
            }
          }

          *status = F_status_set_error(F_valid_not);
          return string;
        }
        else if (*string == f_string_ascii_ampersand_s[0]) {
          base = 12;

          continue;
        }
        else if (*string == f_string_ascii_asterisk_s[0]) {
          // @fixme: what should I do here? review the fprintf() docs.
          continue;
        }
        else if (*string == f_string_ascii_plus_s[0]) {
          flag |= f_print_format_flag_sign_always;

          continue;
        }
        else {
          *status = F_status_set_error(F_valid_not);
          return string;
        }
      }
      else if (*string < 0x41) {
        if (*string == f_string_ascii_minus_s[0]) {
          flag |= f_print_format_flag_align_left;

          continue;
        }
        else if (*string == f_string_ascii_period_s[0]) {
          if (!*(string + 1)) {
            *status = F_status_set_error(F_valid_not);
            return string;
          }

          string += 1;

          if (*string < 0x30 || *string > 0x39) {
            *status = F_status_set_error(F_valid_not);
            return string;
          }

          string = private_fl_print_convert_number(string, ap, &precision, status);
          if (F_status_is_error(*status)) return string;

          --string;

          continue;
        }
        else if (*string > 0x2f && *string < 0x3a) {
          if (!(flag & f_print_format_flag_width)) {
            if (*string == f_string_ascii_0_s[0]) {
              flag |= f_print_format_flag_zeros_leading;

              continue;
            }

            flag |= f_print_format_flag_width;

            string = private_fl_print_convert_number(string, ap, &width, status);
            if (F_status_is_error(*status)) return string;

            --string;

            continue;
          }
          else {
            *status = F_status_set_error(F_valid_not);
            return string;
          }
        }
        else if (*string == f_string_ascii_colon_s[0]) {
          flag |= f_print_format_flag_ignore_range;

          continue;
        }
        else if (*string == f_string_ascii_colon_semi_s[0]) {
          flag |= f_print_format_flag_ignore_index;

          continue;
        }
        else if (*string == f_string_ascii_equal_s[0]) {
          flag |= f_print_format_flag_trim;

          continue;
        }
        else if (*string == f_string_ascii_sign_at_s[0]) {
          base = 8;

          continue;
        }
        else {
          *status = F_status_set_error(F_valid_not);
          return string;
        }
      }
      else if (*string < 0x56) {
        if (*string == f_string_ascii_C_s[0]) {
          char value[1] = { (char) va_arg(*ap, int) };

          *status = f_print_safely(value, 1, output);

          return string;
        }
        else if (*string == f_string_ascii_I_s[0]) {
          type = f_print_format_type_signed_32;
          flag |= f_print_format_flag_uppercase;

          if (*(string + 1) == f_string_ascii_I_s[0]) {
            if (*(string + 2) == f_string_ascii_I_s[0]) {
              type = f_print_format_type_signed_8;
              string = string + 2;
            }
            else {
              type = f_print_format_type_signed_16;
              string += 1;
            }
          }
          else if (*(string + 1) == f_string_ascii_L_s[0]) {
            if (*(string + 2) == f_string_ascii_L_s[0]) {
              type = f_print_format_type_signed_128;
              string = string + 2;
            }
            else {
              type = f_print_format_type_signed_64;
              string += 1;
            }
          }
        }
        else if (*string == f_string_ascii_N_s[0]) {
          type = f_print_format_type_number;
          flag |= f_print_format_flag_uppercase;
        }
        else if (*string == f_string_ascii_Q_s[0]) {
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            if (flag & f_print_format_flag_ignore_index) {
              if (flag & f_print_format_flag_ignore_range) {
                f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
                f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

                *status = private_fl_print_trim_except_in_safely(value.string, value.used, except_at, except_in, output);

                return string;
              }

              f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              *status = private_fl_print_trim_except_in_safely(value.string, value.used, except_at, except_in, output);

              return string;
            }

            if (flag & f_print_format_flag_ignore_range) {
              f_array_lengths_t except_at = f_array_lengths_t_initialize;
              f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              *status = private_fl_print_trim_except_in_safely(value.string, value.used, except_at, except_in, output);

              return string;
            }

            *status = private_fl_print_trim_safely(value.string, value.used, output);

            return string;
          }

          if (flag & f_print_format_flag_ignore_index) {
            if (flag & f_print_format_flag_ignore_range) {
              f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              *status = f_print_except_in_safely(value.string, value.used, except_at, except_in, output);

              return string;
            }

            f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            *status = f_print_except_in_safely(value.string, value.used, except_at, except_in, output);

            return string;
          }

          if (flag & f_print_format_flag_ignore_range) {
            f_array_lengths_t except_at = f_array_lengths_t_initialize;
            f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            *status = f_print_except_in_safely(value.string, value.used, except_at, except_in, output);

            return string;
          }

          *status = f_print_dynamic_safely(value, output);

          return string;
        }
        else if (*string == f_string_ascii_S_s[0]) {
          const f_string_t value = va_arg(*ap, f_string_t);

          *status = f_print_safely_terminated(value, output);

          return string;
        }
        else if (*string == f_string_ascii_U_s[0]) {
          type = f_print_format_type_unsigned_32;
          flag |= f_print_format_flag_uppercase;

          if (*(string + 1) == f_string_ascii_I_s[0]) {
            if (*(string + 2) == f_string_ascii_I_s[0]) {
              type = f_print_format_type_unsigned_8;
              string = string + 2;
            }
            else {
              type = f_print_format_type_unsigned_16;
              string += 1;
            }
          }
          else if (*(string + 1) == f_string_ascii_L_s[0]) {
            if (*(string + 2) == f_string_ascii_L_s[0]) {
              type = f_print_format_type_unsigned_128;
              string = string + 2;
            }
            else {
              type = f_print_format_type_unsigned_64;
              string += 1;
            }
          }
          else if (*(string + 1) == f_string_ascii_N_s[0]) {
            type = f_print_format_type_unsigned_number;
            string += 1;
          }
        }
        else {
          *status = F_status_set_error(F_valid_not);
          return string;
        }
      }
      else if (*string < 0x60) {
        if (*string == f_string_ascii_Z_s[0]) {
          type = f_print_format_type_size;
          flag |= f_print_format_flag_uppercase;
        }
        else if (*string == f_string_ascii_bracket_open_s[0]) {
          const f_color_set_t value = va_arg(*ap, f_color_set_t);

          if (value.before) {
            *status = f_print_terminated(value.before->string, output);
          }

          return string;
        }
        else if (*string == f_string_ascii_bracket_close_s[0]) {
          const f_color_set_t value = va_arg(*ap, f_color_set_t);

          if (value.after) {
            *status = f_print_terminated(value.after->string, output);
          }

          return string;
        }
        else if (*string == f_string_ascii_caret_s[0]) {
          base = 10;

          continue;
        }
        else if (*string == f_string_ascii_underscore_s[0]) {
          base = 16;

          continue;
        }
        else {
          *status = F_status_set_error(F_valid_not);
          return string;
        }
      }
      else if (*string < 0x72) {
        if (*string == f_string_ascii_c_s[0]) {
          const char value = (char) va_arg(*ap, uint32_t);

          if (!fputc_unlocked(value, output)) {
            *status = F_status_set_error(F_output);
          }

          return string;
        }
        else if (*string == f_string_ascii_i_s[0]) {
          type = f_print_format_type_signed_32;

          if (*(string + 1) == f_string_ascii_i_s[0]) {
            if (*(string + 2) == f_string_ascii_i_s[0]) {
              type = f_print_format_type_signed_8;
              string = string + 2;
            }
            else {
              type = f_print_format_type_signed_16;
              string += 1;
            }
          }
          else if (*(string + 1) == f_string_ascii_l_s[0]) {
            if (*(string + 2) == f_string_ascii_l_s[0]) {
              type = f_print_format_type_signed_128;
              string = string + 2;
            }
            else {
              type = f_print_format_type_signed_64;
              string += 1;
            }
          }
        }
        else if (*string == f_string_ascii_n_s[0]) {
          type = f_print_format_type_number;
        }
        else if (*string == f_string_ascii_q_s[0]) {
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            if (flag & f_print_format_flag_ignore_index) {
              if (flag & f_print_format_flag_ignore_range) {
                f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
                f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

                *status = private_fl_print_trim_except_in(value.string, value.used, except_at, except_in, output);

                return string;
              }

              f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              *status = private_fl_print_trim_except_in(value.string, value.used, except_at, except_in, output);

              return string;
            }

            if (flag & f_print_format_flag_ignore_range) {
              f_array_lengths_t except_at = f_array_lengths_t_initialize;
              f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              *status = private_fl_print_trim_except_in(value.string, value.used, except_at, except_in, output);

              return string;
            }

            *status = private_fl_print_trim(value.string, value.used, output);

            return string;
          }

          if (flag & f_print_format_flag_ignore_index) {
            if (flag & f_print_format_flag_ignore_range) {
              f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              *status = f_print_except_in(value.string, value.used, except_at, except_in, output);

              return string;
            }

            f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            *status = f_print_except_in(value.string, value.used, except_at, except_in, output);

            return string;
          }

          if (flag & f_print_format_flag_ignore_range) {
            f_array_lengths_t except_at = f_array_lengths_t_initialize;
            f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            *status = f_print_except_in(value.string, value.used, except_at, except_in, output);

            return string;
          }

          *status = f_print_dynamic(value, output);

          return string;
        }
        else {
          *status = F_status_set_error(F_valid_not);
          return string;
        }
      }
      else {
        if (*string == f_string_ascii_r_s[0]) {

          // raw static/dynamic string.
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & f_print_format_flag_trim) {
            if (flag & f_print_format_flag_ignore_index) {
              if (flag & f_print_format_flag_ignore_range) {
                f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
                f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

                *status = private_fl_print_trim_except_in_raw(value.string, value.used, except_at, except_in, output);

                return string;
              }

              f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              *status = private_fl_print_trim_except_in_raw(value.string, value.used, except_at, except_in, output);

              return string;
            }

            if (flag & f_print_format_flag_ignore_range) {
              f_array_lengths_t except_at = f_array_lengths_t_initialize;
              f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              *status = private_fl_print_trim_except_in_raw(value.string, value.used, except_at, except_in, output);

              return string;
            }

            *status = private_fl_print_trim_raw(value.string, value.used, output);

            return string;
          }

          if (flag & f_print_format_flag_ignore_index) {
            if (flag & f_print_format_flag_ignore_range) {
              f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              *status = f_print_except_in_raw(value.string, value.used, except_at, except_in, output);

              return string;
            }

            f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            *status = f_print_except_in_raw(value.string, value.used, except_at, except_in, output);

            return string;
          }

          if (flag & f_print_format_flag_ignore_range) {
            f_array_lengths_t except_at = f_array_lengths_t_initialize;
            f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            *status = f_print_except_in_raw(value.string, value.used, except_at, except_in, output);

            return string;
          }

          *status = f_print_dynamic_raw(value, output);

          return string;
        }
        else if (*string == f_string_ascii_s_s[0]) {
          const f_string_t value = va_arg(*ap, f_string_t);

          *status = f_print_terminated(value, output);

          return string;
        }
        else if (*string == f_string_ascii_u_s[0]) {
          type = f_print_format_type_unsigned_32;

          if (*(string + 1) == f_string_ascii_i_s[0]) {
            if (*(string + 2) == f_string_ascii_i_s[0]) {
              type = f_print_format_type_unsigned_8;
              string = string + 2;
            }
            else {
              type = f_print_format_type_unsigned_16;
              string += 1;
            }
          }
          else if (*(string + 1) == f_string_ascii_l_s[0]) {
            if (*(string + 2) == f_string_ascii_l_s[0]) {
              type = f_print_format_type_unsigned_128;
              string = string + 2;
            }
            else {
              type = f_print_format_type_unsigned_64;
              string += 1;
            }
          }
          else if (*(string + 1) == f_string_ascii_n_s[0]) {
            type = f_print_format_type_unsigned_number;
            string += 1;
          }
        }
        else if (*string == f_string_ascii_z_s[0]) {
          type = f_print_format_type_size;
        }
        else {
          *status = F_status_set_error(F_valid_not);
          return string;
        }
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

      if (type == f_print_format_type_number) {
        *status = f_conversion_number_signed_to_file(va_arg(*ap, f_number_signed_t), conversion_data, output);
      }
      else if (type == f_print_format_type_signed_64) {
        *status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, int64_t), conversion_data, output);
      }
      else if (type == f_print_format_type_signed_128) {
        *status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, f_int_128_t), conversion_data, output);
      }
      else if (type == f_print_format_type_signed_32) {
        *status = f_conversion_number_signed_to_file((f_number_signed_t) va_arg(*ap, int32_t), conversion_data, output);
      }
      else if (type == f_print_format_type_signed_16) {
        const int16_t value = (int16_t) va_arg(*ap, int);

        *status = f_conversion_number_signed_to_file((f_number_signed_t) value, conversion_data, output);
      }
      else if (type == f_print_format_type_signed_8) {
        const int8_t value = (int8_t) va_arg(*ap, int);

        *status = f_conversion_number_signed_to_file((f_number_signed_t) value, conversion_data, output);
      }
      else if (type == f_print_format_type_size) {
        *status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, size_t), conversion_data, output);
      }
      else if (type == f_print_format_type_unsigned_32) {
        *status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, uint32_t), conversion_data, output);
      }
      else if (type == f_print_format_type_unsigned_16) {
        const uint16_t value = (uint16_t) va_arg(*ap, unsigned);

        *status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) value, conversion_data, output);
      }
      else if (type == f_print_format_type_unsigned_8) {
        const uint8_t value = (uint8_t) va_arg(*ap, unsigned);

        *status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) value, conversion_data, output);
      }
      else if (type == f_print_format_type_unsigned_64) {
        *status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, uint64_t), conversion_data, output);
      }
      else if (type == f_print_format_type_unsigned_128) {
        *status = f_conversion_number_unsigned_to_file((f_number_unsigned_t) va_arg(*ap, f_uint_128_t), conversion_data, output);
      }
      else if (type == f_print_format_type_unsigned_number) {
        *status = f_conversion_number_unsigned_to_file(va_arg(*ap, f_number_unsigned_t), conversion_data, output);
      }

      return string;
    } // for

    *status = F_status_set_error(F_valid_not);
    return string;
  }
#endif // !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)

#if !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)
  f_string_t private_fl_print_convert_number(f_string_t string, va_list *ap, unsigned int *number, f_status_t *status) {

    for (*number = 0; *string; string += 1) {

      if (*string == f_string_ascii_0_s[0]) {
        *number *= 10;
      }
      else if (*string == f_string_ascii_1_s[0]) {
        *number *= 10;
        *number += 1;
      }
      else if (*string == f_string_ascii_2_s[0]) {
        *number *= 10;
        *number += 2;
      }
      else if (*string == f_string_ascii_3_s[0]) {
        *number *= 10;
        *number += 3;
      }
      else if (*string == f_string_ascii_4_s[0]) {
        *number *= 10;
        *number += 4;
      }
      else if (*string == f_string_ascii_5_s[0]) {
        *number *= 10;
        *number += 5;
      }
      else if (*string == f_string_ascii_6_s[0]) {
        *number *= 10;
        *number += 6;
      }
      else if (*string == f_string_ascii_7_s[0]) {
        *number *= 10;
        *number += 7;
      }
      else if (*string == f_string_ascii_8_s[0]) {
        *number *= 10;
        *number += 8;
      }
      else if (*string == f_string_ascii_9_s[0]) {
        *number *= 10;
        *number += 9;
      }
      else if (*string == f_string_ascii_asterisk_s[0]) {
        *number = va_arg(*ap, unsigned int);

        break;
      }
      else {
        break;
      }
    } // for

    return string;
  }
#endif // !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)

#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)
  f_status_t private_fl_print_trim_except_in(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    // skip past leading whitespace.
    while (i < length) {

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

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

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

    while (i < length) {

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

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      // determine if this is an end of string whitespace that needs to be trimmed.
      if (status == F_true || !string[i]) {
        j = i + macro_f_utf_byte_width(string[i]);
        status = F_none;

        while (j < length) {

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

          status = f_utf_is_whitespace(string + j, (length - j) + 1);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          if (status == F_false && string[i]) break;
        } // while

        if (j == length) break;

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

          if (i + macro_f_utf_byte_width(string[i]) >= length) {
            return F_status_set_error(F_complete_not_utf_stop);
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

        if (i >= length) break;

        if (!string[i]) {
          ++i;

          continue;
        }
      }

      status = f_utf_is_valid(string + i, length - i);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (i + macro_f_utf_byte_width(string[i]) >= length) {
        return F_status_set_error(F_complete_not_utf_stop);
      }

      if (status == F_false) {
        return F_status_set_error(F_utf_not);
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

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)

#if !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    // skip past leading whitespace.
    while (i < length) {

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

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // consider invalid data not-whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    f_string_t s = 0;

    while (i < length) {

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

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // determine if this is an end of string whitespace that needs to be trimmed.
      if (status == F_true || !string[i]) {
        j = i + macro_f_utf_byte_width(string[i]);
        status = F_none;

        while (j < length) {

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

          status = f_utf_is_whitespace(string + j, (length - j) + 1);

          if (F_status_is_error(status) || status == F_false && string[i]) break;
        } // while

        if (j == length) break;

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

          if (!fputc_unlocked(string[i], output)) {
            return F_status_set_error(F_output);
          }

          if (macro_f_utf_byte_width(string[i]) > 1 && i + 1 < length) {
            if (!fputc_unlocked(string[i + 1], output)) {
              return F_status_set_error(F_output);
            }

            if (macro_f_utf_byte_width(string[i]) > 2 && i + 2 < length) {
              if (!fputc_unlocked(string[i + 2], output)) {
                return F_status_set_error(F_output);
              }

              if (macro_f_utf_byte_width(string[i]) > 3 && i + 3 < length) {
                if (!fputc_unlocked(string[i + 3], output)) {
                  return F_status_set_error(F_output);
                }
              }
            }
          }

          i += macro_f_utf_byte_width(string[i]);
        } // while

        if (i >= length) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }

      if (macro_f_utf_byte_width(string[i]) > 1 && i + 1 < length) {
        if (!fputc_unlocked(string[i + 1], output)) {
          return F_status_set_error(F_output);
        }

        if (macro_f_utf_byte_width(string[i]) > 2 && i + 2 < length) {
          if (!fputc_unlocked(string[i + 2], output)) {
            return F_status_set_error(F_output);
          }

          if (macro_f_utf_byte_width(string[i]) > 3 && i + 3 < length) {
            if (!fputc_unlocked(string[i + 3], output)) {
              return F_status_set_error(F_output);
            }
          }
        }
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    // skip past leading whitespace.
    while (i < length) {

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

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // invalid UTF will not be treated as whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    while (i < length) {

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

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // determine if this is an end of string whitespace that needs to be trimmed.
      if (status == F_true || !string[i]) {
        j = i + macro_f_utf_byte_width(string[i]);
        status = F_none;

        while (j < length) {

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

          status = f_utf_is_whitespace(string + j, (length - j) + 1);

          if (F_status_is_error(status) || status == F_false && string[i]) break;
        } // while

        if (j == length || status == F_true || !string[i]) break;

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
            status = F_none;
            break;
          }

          if (!string[i]) {
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
            continue;
          }

          status = f_utf_is_valid(string + i, length - i);

          if (status == F_true) {
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
          }
          else {
            if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
              return F_status_set_error(F_output);
            }

            if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
              return F_status_set_error(F_output);
            }

            if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
              return F_status_set_error(F_output);
            }
          }

          i += macro_f_utf_byte_width(string[i]);
        } // while

        if (i >= length) break;
      }

      status = f_utf_is_valid(string + i, length - i);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false || i + macro_f_utf_byte_width(string[i]) >= length) {
        if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
          return F_status_set_error(F_output);
        }

        if (status == F_false) {
          i += macro_f_utf_byte_width(string[i]);
        }
        else {
          i = length;
        }

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

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)

#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  f_status_t private_fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    // skip past leading whitespace.
    while (i < length) {

      if (!string[i]) {
        ++i;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

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

    while (i < length) {

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      // determine if this is an end of string whitespace that needs to be trimmed.
      if (status == F_true || !string[i]) {
        j = i + macro_f_utf_byte_width(string[i]);
        status = F_none;

        while (j < length) {

          if (!string[j]) {
            ++j;

            continue;
          }

          status = f_utf_is_whitespace(string + j, (length - j) + 1);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_maybe) {
              return F_status_set_error(F_utf);
            }

            return status;
          }

          if (status == F_false && string[i]) break;
        } // while

        if (j == length) break;

        // print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (!string[i]) {
            ++i;

            continue;
          }

          if (i + macro_f_utf_byte_width(string[i]) >= length) {
            return F_status_set_error(F_complete_not_utf_stop);
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

        if (i >= length) break;

        if (!string[i]) {
          ++i;

          continue;
        }
      }

      status = f_utf_is_valid(string + i, length - i);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (i + macro_f_utf_byte_width(string[i]) >= length) {
        return F_status_set_error(F_complete_not_utf_stop);
      }

      if (status == F_false) {
        return F_status_set_error(F_utf_not);
      }

      // @todo: change logic to use single fwrite() based on byte width rather than multiple fputc...
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

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

#if !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    // skip past leading whitespace.
    while (i < length) {

      if (!string[i]) {
        ++i;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // consider invalid data not-whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    f_string_t s = 0;

    while (i < length) {

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // determine if this is an end of string whitespace that needs to be trimmed.
      if (status == F_true || !string[i]) {
        j = i + macro_f_utf_byte_width(string[i]);
        status = F_none;

        while (j < length) {

          if (!string[j]) {
            ++j;

            continue;
          }

          status = f_utf_is_whitespace(string + j, (length - j) + 1);

          if (F_status_is_error(status) || status == F_false && string[i]) break;
        } // while

        if (j == length) break;

        // print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (!fputc_unlocked(string[i], output)) {
            return F_status_set_error(F_output);
          }

          if (macro_f_utf_byte_width(string[i]) > 1 && i + 1 < length) {
            if (!fputc_unlocked(string[i + 1], output)) {
              return F_status_set_error(F_output);
            }

            if (macro_f_utf_byte_width(string[i]) > 2 && i + 2 < length) {
              if (!fputc_unlocked(string[i + 2], output)) {
                return F_status_set_error(F_output);
              }

              if (macro_f_utf_byte_width(string[i]) > 3 && i + 3 < length) {
                if (!fputc_unlocked(string[i + 3], output)) {
                  return F_status_set_error(F_output);
                }
              }
            }
          }

          i += macro_f_utf_byte_width(string[i]);
        } // while

        if (i >= length) break;
      }

      if (!fputc_unlocked(string[i], output)) {
        return F_status_set_error(F_output);
      }

      if (macro_f_utf_byte_width(string[i]) > 1 && i + 1 < length) {
        if (!fputc_unlocked(string[i + 1], output)) {
          return F_status_set_error(F_output);
        }

        if (macro_f_utf_byte_width(string[i]) > 2 && i + 2 < length) {
          if (!fputc_unlocked(string[i + 2], output)) {
            return F_status_set_error(F_output);
          }

          if (macro_f_utf_byte_width(string[i]) > 3 && i + 3 < length) {
            if (!fputc_unlocked(string[i + 3], output)) {
              return F_status_set_error(F_output);
            }
          }
        }
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *output) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    // skip past leading whitespace.
    while (i < length) {

      if (!string[i]) {
        ++i;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // invalid UTF will not be treated as whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    while (i < length) {

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // determine if this is an end of string whitespace that needs to be trimmed.
      if (status == F_true || !string[i]) {
        j = i + macro_f_utf_byte_width(string[i]);
        status = F_none;

        while (j < length) {

          if (!string[j]) {
            ++j;

            continue;
          }

          status = f_utf_is_whitespace(string + j, (length - j) + 1);

          if (F_status_is_error(status) || status == F_false && string[i]) break;
        } // while

        if (j == length || status == F_true || !string[i]) break;

        // print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

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
            status = F_none;
            break;
          }

          if (!string[i]) {
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
            continue;
          }

          status = f_utf_is_valid(string + i, length - i);

          if (status == F_true) {
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
          }
          else {
            if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
              return F_status_set_error(F_output);
            }

            if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
              return F_status_set_error(F_output);
            }

            if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
              return F_status_set_error(F_output);
            }
          }

          i += macro_f_utf_byte_width(string[i]);
        } // while

        if (i >= length) break;
      }

      status = f_utf_is_valid(string + i, length - i);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) {
          return F_status_set_error(F_utf);
        }

        return status;
      }

      if (status == F_false || i + macro_f_utf_byte_width(string[i]) >= length) {
        if (!fputc_unlocked(f_print_sequence_unknown_s[0], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(f_print_sequence_unknown_s[1], output)) {
          return F_status_set_error(F_output);
        }

        if (!fputc_unlocked(f_print_sequence_unknown_s[2], output)) {
          return F_status_set_error(F_output);
        }

        if (status == F_false) {
          i += macro_f_utf_byte_width(string[i]);
        }
        else {
          i = length;
        }

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

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_)
  f_string_t private_fl_print_format_convert(f_string_t string, FILE * const stream, va_list * const ap, f_status_t * const status) {

    const f_string_t start = string;

    // An unpaired '%' character must not be at the end of the string.
    if (!*string) {
      *status = F_status_set_error(F_eos);

      return string;
    }

    *status = F_none;

    uint8_t base = 10;
    uint32_t flag = 0;
    uint8_t type = 0;

    unsigned int width = 1;
    unsigned int precision = 1;

    for (; *string; string += 1) {

      if (*string < 0x2c) {
        if (*string == f_string_ascii_space_s.string[0]) {
          flag |= F_print_format_flag_sign_pad_d;

          continue;
        }
        else if (*string == f_string_ascii_exclamation_s.string[0]) {
          base = 2;

          continue;
        }
        else if (*string == f_string_ascii_pound_s.string[0]) {
          flag |= F_print_format_flag_convert_d;

          continue;
        }
        else if (*string == f_string_ascii_dollar_s.string[0]) {

          // If followed immediately by a '$' this is ignored.
          // Use '%$' to separate, such as '%l%$l' would allow for '0l' to be printed where '%ll' would interpret the 'l', resulting in a long long.
          return string;
        }
        else if (*string == f_string_ascii_percent_s.string[0]) {

          // The first percent found represents a literal '%' to be printed, otherwise return as invalid.
          if (string == start) {
            if (fwrite_unlocked(f_string_ascii_percent_s.string, 1, f_string_ascii_percent_s.used, stream) < f_string_ascii_percent_s.used) {
              *status = F_status_set_error(F_output);
            }
          }
          else {
            *status = F_status_set_error(F_valid_not);
          }

          return string;
        }
        else if (*string == f_string_ascii_ampersand_s.string[0]) {
          base = 12;

          continue;
        }
        else if (*string == f_string_ascii_asterisk_s.string[0]) {
          flag |= F_print_format_flag_width_d | F_print_format_flag_width_value_d;
          continue;
        }
        else if (*string == f_string_ascii_plus_s.string[0]) {
          flag |= F_print_format_flag_sign_always_d;

          continue;
        }
        else {
          *status = F_status_set_error(F_valid_not);

          return string;
        }
      }
      else if (*string < 0x41) {
        if (*string == f_string_ascii_minus_s.string[0]) {
          flag |= F_print_format_flag_align_left_d;

          continue;
        }
        else if (*string == f_string_ascii_period_s.string[0]) {
          if (!*(string + 1)) {
            *status = F_status_set_error(F_eos);

            return string;
          }

          ++string;

          if (*string == f_string_ascii_asterisk_s.string[0]) {
            flag |= F_print_format_flag_precision_d | F_print_format_flag_precision_value_d;
          }
          else if (*string < 0x30 || *string > 0x39) {
            *status = F_status_set_error(F_valid_not);

            return string;
          }
          else {
            string = private_fl_print_convert_number(string, ap, &precision, status);
            if (F_status_is_error(*status)) return string;

            --string;

            flag |= F_print_format_flag_precision_d;
          }

          continue;
        }
        else if (*string == f_string_ascii_slash_forward_s.string[0]) {
          flag |= F_print_format_flag_range_d;

          continue;
        }
        else if (*string > 0x2f && *string < 0x3a) {
          if (!(flag & F_print_format_flag_width_d)) {
            if (*string == f_string_ascii_0_s.string[0]) {
              flag |= F_print_format_flag_zeros_leading_d;

              continue;
            }

            flag |= F_print_format_flag_width_d;

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
        else if (*string == f_string_ascii_colon_s.string[0]) {
          flag |= F_print_format_flag_ignore_range_d;

          continue;
        }
        else if (*string == f_string_ascii_colon_semi_s.string[0]) {
          flag |= F_print_format_flag_ignore_index_d;

          continue;
        }
        else if (*string == f_string_ascii_equal_s.string[0]) {
          flag |= F_print_format_flag_trim_d;

          continue;
        }
        else if (*string == f_string_ascii_sign_at_s.string[0]) {
          base = 8;

          continue;
        }
        else {
          *status = F_status_set_error(F_valid_not);

          return string;
        }
      }
      else if (*string < 0x56) {
        if (*string == f_string_ascii_C_s.string[0]) {
          char value[1] = { (char) va_arg(*ap, int) };

          *status = f_print_safely(value, 1, stream);

          return string;
        }
        else if (*string == f_string_ascii_D_s.string[0]) {
          type = f_print_format_type_double_32_e;
          flag |= F_print_format_flag_uppercase_d;

          if (*(string + 1)) {
            if (*(string + 1) == f_string_ascii_L_s.string[0]) {
              type = f_print_format_type_double_64_e;

              if (*(string + 2) == f_string_ascii_e_s.string[0]) {
                flag |= F_print_format_flag_exponent_d;
                string += 2;
              }
              else if (*(string + 2) == f_string_ascii_E_s.string[0]) {
                flag |= F_print_format_flag_exponent_d | F_print_format_flag_exponent_upper_d;
                string += 2;
              }
              else if (*(string + 2) == f_string_ascii_g_s.string[0]) {
                flag |= F_print_format_flag_exponent_either_d;
                string += 2;
              }
              else if (*(string + 2) == f_string_ascii_G_s.string[0]) {
                flag |= F_print_format_flag_exponent_either_d | F_print_format_flag_exponent_upper_d;
                string += 2;
              }
              else {
                ++string;
              }
            }
            else if (*(string + 1) == f_string_ascii_e_s.string[0]) {
              flag |= F_print_format_flag_exponent_d;
              ++string;
            }
            else if (*(string + 1) == f_string_ascii_E_s.string[0]) {
              flag |= F_print_format_flag_exponent_d | F_print_format_flag_exponent_upper_d;
              ++string;
            }
            else if (*(string + 1) == f_string_ascii_g_s.string[0]) {
              flag |= F_print_format_flag_exponent_either_d;
              ++string;
            }
            else if (*(string + 1) == f_string_ascii_G_s.string[0]) {
              flag |= F_print_format_flag_exponent_either_d | F_print_format_flag_exponent_upper_d;
              ++string;
            }
          }
        }
        else if (*string == f_string_ascii_I_s.string[0]) {
          type = f_print_format_type_signed_32_e;
          flag |= F_print_format_flag_uppercase_d;

          if (*(string + 1) == f_string_ascii_I_s.string[0]) {
            if (*(string + 2) == f_string_ascii_I_s.string[0]) {
              type = f_print_format_type_signed_8_e;
              string += 2;
            }
            else {
              type = f_print_format_type_signed_16_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_L_s.string[0]) {
            if (*(string + 2) == f_string_ascii_L_s.string[0]) {
              type = f_print_format_type_signed_128_e;
              string += 2;
            }
            else {
              type = f_print_format_type_signed_64_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_N_s.string[0]) {
            type = f_print_format_type_signed_number_e;
            flag |= F_print_format_flag_uppercase_d;
            ++string;
          }
        }
        else if (*string == f_string_ascii_Q_s.string[0]) {
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & F_print_format_flag_range_d) {
            const f_string_range_t partial = va_arg(*ap, f_string_range_t);

            if (flag & F_print_format_flag_ignore_index_d) {
              const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              if (flag & F_print_format_flag_ignore_range_d) {
                except_in = va_arg(*ap, f_string_ranges_t);
              }

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else if (flag & F_print_format_flag_ignore_range_d) {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = f_string_ranges_t_initialize;

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_safely(value.string + partial.start, length, stream);
              }
              else {
                *status = f_print_safely(value.string + partial.start, length, stream);
              }
            }
          }
          else if (flag & F_print_format_flag_ignore_index_d) {
            const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            if (flag & F_print_format_flag_ignore_range_d) {
              except_in = va_arg(*ap, f_string_ranges_t);
            }

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in_safely(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic_safely(value, except_at, except_in, stream);
            }
          }
          else if (flag & F_print_format_flag_ignore_range_d) {
            const f_array_lengths_t except_at = f_array_lengths_t_initialize;
            const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in_safely(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic_safely(value, except_at, except_in, stream);
            }
          }
          else {
            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_safely(value.string, value.used, stream);
            }
            else {
              *status = f_print_dynamic_safely(value, stream);
            }
          }

          return string;
        }
        else if (*string == f_string_ascii_R_s.string[0]) {
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & F_print_format_flag_range_d) {
            const f_string_range_t partial = va_arg(*ap, f_string_range_t);

            if (flag & F_print_format_flag_ignore_index_d) {
              const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              if (flag & F_print_format_flag_ignore_range_d) {
                except_in = va_arg(*ap, f_string_ranges_t);
              }

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in_raw_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in_raw_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else if (flag & F_print_format_flag_ignore_range_d) {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in_raw_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in_raw_safely(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = f_string_ranges_t_initialize;

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_raw_safely(value.string + partial.start, length, stream);
              }
              else {
                *status = f_print_raw_safely(value.string + partial.start, length, stream);
              }
            }
          }
          else if (flag & F_print_format_flag_ignore_index_d) {
            const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            if (flag & F_print_format_flag_ignore_range_d) {
              except_in = va_arg(*ap, f_string_ranges_t);
            }

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in_raw_safely(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic_raw_safely(value, except_at, except_in, stream);
            }
          }
          else if (flag & F_print_format_flag_ignore_range_d) {
            const f_array_lengths_t except_at = f_array_lengths_t_initialize;
            const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in_raw_safely(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic_raw_safely(value, except_at, except_in, stream);
            }
          }
          else {
            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_raw_safely(value.string, value.used, stream);
            }
            else {
              *status = f_print_dynamic_raw_safely(value, stream);
            }
          }

          return string;
        }
        else if (*string == f_string_ascii_S_s.string[0]) {
          const f_string_t value = va_arg(*ap, f_string_t);

          *status = f_print_safely_terminated(value, stream);

          return string;
        }
        else if (*string == f_string_ascii_U_s.string[0]) {
          type = f_print_format_type_unsigned_32_e;
          flag |= F_print_format_flag_uppercase_d;

          if (*(string + 1) == f_string_ascii_I_s.string[0]) {
            if (*(string + 2) == f_string_ascii_I_s.string[0]) {
              type = f_print_format_type_unsigned_8_e;
              string += 2;
            }
            else {
              type = f_print_format_type_unsigned_16_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_L_s.string[0]) {
            if (*(string + 2) == f_string_ascii_L_s.string[0]) {
              type = f_print_format_type_unsigned_128_e;
              string += 2;
            }
            else {
              type = f_print_format_type_unsigned_64_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_N_s.string[0]) {
            type = f_print_format_type_unsigned_number_e;
            ++string;
          }
        }
        else {
          *status = F_status_set_error(F_valid_not);

          return string;
        }
      }
      else if (*string < 0x60) {
        if (*string == f_string_ascii_Z_s.string[0]) {
          type = f_print_format_type_size_e;
          flag |= F_print_format_flag_uppercase_d;
        }
        else if (*string == f_string_ascii_bracket_open_s.string[0]) {
          const f_color_set_t value = va_arg(*ap, f_color_set_t);

          if (value.before) {
            *status = f_print_dynamic_raw(*value.before, stream);
          }

          return string;
        }
        else if (*string == f_string_ascii_bracket_close_s.string[0]) {
          const f_color_set_t value = va_arg(*ap, f_color_set_t);

          if (value.after) {
            *status = f_print_dynamic_raw(*value.after, stream);
          }

          return string;
        }
        else if (*string == f_string_ascii_caret_s.string[0]) {
          base = 10;

          continue;
        }
        else if (*string == f_string_ascii_underscore_s.string[0]) {
          base = 16;

          continue;
        }
        else {
          *status = F_status_set_error(F_valid_not);

          return string;
        }
      }
      else if (*string < 0x72) {
        if (*string == f_string_ascii_c_s.string[0]) {
          const char value = (char) va_arg(*ap, uint32_t);

          if (!fputc_unlocked(value, stream)) {
            *status = F_status_set_error(F_output);
          }

          return string;
        }
        else if (*string == f_string_ascii_d_s.string[0]) {
          type = f_print_format_type_double_32_e;

          if (*(string + 1)) {
            if (*(string + 1) == f_string_ascii_L_s.string[0]) {
              type = f_print_format_type_double_64_e;

              if (*(string + 2) == f_string_ascii_e_s.string[0]) {
                flag |= F_print_format_flag_exponent_d;
                string += 2;
              }
              else if (*(string + 2) == f_string_ascii_E_s.string[0]) {
                flag |= F_print_format_flag_exponent_d | F_print_format_flag_exponent_upper_d;
                string += 2;
              }
              else if (*(string + 2) == f_string_ascii_g_s.string[0]) {
                flag |= F_print_format_flag_exponent_either_d;
                string += 2;
              }
              else if (*(string + 2) == f_string_ascii_G_s.string[0]) {
                flag |= F_print_format_flag_exponent_either_d | F_print_format_flag_exponent_upper_d;
                string += 2;
              }
              else {
                ++string;
              }
            }
            else if (*(string + 1) == f_string_ascii_e_s.string[0]) {
              flag |= F_print_format_flag_exponent_d;
              ++string;
            }
            else if (*(string + 1) == f_string_ascii_E_s.string[0]) {
              flag |= F_print_format_flag_exponent_d | F_print_format_flag_exponent_upper_d;
              ++string;
            }
            else if (*(string + 1) == f_string_ascii_g_s.string[0]) {
              flag |= F_print_format_flag_exponent_either_d;
              ++string;
            }
            else if (*(string + 1) == f_string_ascii_G_s.string[0]) {
              flag |= F_print_format_flag_exponent_either_d | F_print_format_flag_exponent_upper_d;
              ++string;
            }
          }
        }
        else if (*string == f_string_ascii_i_s.string[0]) {
          type = f_print_format_type_signed_32_e;

          if (*(string + 1) == f_string_ascii_i_s.string[0]) {
            if (*(string + 2) == f_string_ascii_i_s.string[0]) {
              type = f_print_format_type_signed_8_e;
              string += 2;
            }
            else {
              type = f_print_format_type_signed_16_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_l_s.string[0]) {
            if (*(string + 2) == f_string_ascii_l_s.string[0]) {
              type = f_print_format_type_signed_128_e;
              string += 2;
            }
            else {
              type = f_print_format_type_signed_64_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_n_s.string[0]) {
            type = f_print_format_type_signed_number_e;
            ++string;
          }
        }
        else if (*string == f_string_ascii_q_s.string[0]) {
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & F_print_format_flag_range_d) {
            const f_string_range_t partial = va_arg(*ap, f_string_range_t);

            if (flag & F_print_format_flag_ignore_index_d) {
              const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              if (flag & F_print_format_flag_ignore_range_d) {
                except_in = va_arg(*ap, f_string_ranges_t);
              }

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else if (flag & F_print_format_flag_ignore_range_d) {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim(value.string + partial.start, length, stream);
              }
              else {
                *status = f_print(value.string + partial.start, length, stream);
              }
            }
          }
          else if (flag & F_print_format_flag_ignore_index_d) {
            const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            if (flag & F_print_format_flag_ignore_range_d) {
              except_in = va_arg(*ap, f_string_ranges_t);
            }

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic(value, except_at, except_in, stream);
            }
          }
          else if (flag & F_print_format_flag_ignore_range_d) {
            const f_array_lengths_t except_at = f_array_lengths_t_initialize;
            const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic(value, except_at, except_in, stream);
            }
          }
          else {
            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim(value.string, value.used, stream);
            }
            else {
              *status = f_print_dynamic(value, stream);
            }
          }

          return string;
        }
        else {
          *status = F_status_set_error(F_valid_not);

          return string;
        }
      }
      else {
        if (*string == f_string_ascii_r_s.string[0]) {
          const f_string_static_t value = va_arg(*ap, f_string_static_t);

          if (flag & F_print_format_flag_range_d) {
            const f_string_range_t partial = va_arg(*ap, f_string_range_t);

            if (flag & F_print_format_flag_ignore_index_d) {
              const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
              f_string_ranges_t except_in = f_string_ranges_t_initialize;

              if (flag & F_print_format_flag_ignore_range_d) {
                except_in = va_arg(*ap, f_string_ranges_t);
              }

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in_raw(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in_raw(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else if (flag & F_print_format_flag_ignore_range_d) {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_except_in_raw(value.string, partial.start, length, except_at, except_in, stream);
              }
              else {
                *status = f_print_except_in_raw(value.string, partial.start, length, except_at, except_in, stream);
              }
            }
            else {
              const f_array_lengths_t except_at = f_array_lengths_t_initialize;
              const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

              if (partial.start > partial.stop) {
                *status = F_data_not;

                return string;
              }

              f_array_length_t length = (partial.stop - partial.start) + 1;

              if (length + partial.start > value.used) {
                length = value.used - partial.start;
              }

              if (flag & F_print_format_flag_trim_d) {
                *status = private_fl_print_trim_raw(value.string + partial.start, length, stream);
              }
              else {
                *status = f_print_raw(value.string + partial.start, length, stream);
              }
            }
          }
          else if (flag & F_print_format_flag_ignore_index_d) {
            const f_array_lengths_t except_at = va_arg(*ap, f_array_lengths_t);
            f_string_ranges_t except_in = f_string_ranges_t_initialize;

            if (flag & F_print_format_flag_ignore_range_d) {
              except_in = va_arg(*ap, f_string_ranges_t);
            }

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in_raw(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic_raw(value, except_at, except_in, stream);
            }
          }
          else if (flag & F_print_format_flag_ignore_range_d) {
            const f_array_lengths_t except_at = f_array_lengths_t_initialize;
            const f_string_ranges_t except_in = va_arg(*ap, f_string_ranges_t);

            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_except_in_raw(value.string, 0, value.used, except_at, except_in, stream);
            }
            else {
              *status = f_print_except_in_dynamic_raw(value, except_at, except_in, stream);
            }
          }
          else {
            if (flag & F_print_format_flag_trim_d) {
              *status = private_fl_print_trim_raw(value.string, value.used, stream);
            }
            else {
              *status = f_print_dynamic_raw(value, stream);
            }
          }

          return string;
        }
        else if (*string == f_string_ascii_s_s.string[0]) {
          const f_string_t value = va_arg(*ap, f_string_t);

          *status = f_print_terminated(value, stream);

          return string;
        }
        else if (*string == f_string_ascii_u_s.string[0]) {
          type = f_print_format_type_unsigned_32_e;

          if (*(string + 1) == f_string_ascii_i_s.string[0]) {
            if (*(string + 2) == f_string_ascii_i_s.string[0]) {
              type = f_print_format_type_unsigned_8_e;
              string += 2;
            }
            else {
              type = f_print_format_type_unsigned_16_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_l_s.string[0]) {
            if (*(string + 2) == f_string_ascii_l_s.string[0]) {
              type = f_print_format_type_unsigned_128_e;
              string += 2;
            }
            else {
              type = f_print_format_type_unsigned_64_e;
              ++string;
            }
          }
          else if (*(string + 1) == f_string_ascii_n_s.string[0]) {
            type = f_print_format_type_unsigned_number_e;
            ++string;
          }
        }
        else if (*string == f_string_ascii_z_s.string[0]) {
          type = f_print_format_type_size_e;
        }
        else {
          *status = F_status_set_error(F_valid_not);

          return string;
        }
      }

      f_conversion_data_t conversion_data = macro_f_conversion_data_t_initialize(base, 0, 1);

      if (flag & F_print_format_flag_align_left_d) {
        conversion_data.flag |= F_conversion_data_flag_align_left_d;
      }

      if (flag & F_print_format_flag_convert_d) {
        conversion_data.flag |= F_conversion_data_flag_base_prepend_d;
      }

      if (flag & F_print_format_flag_sign_always_d) {
        conversion_data.flag |= F_conversion_data_flag_sign_always_d;
      }

      if (flag & F_print_format_flag_sign_pad_d) {
        conversion_data.flag |= F_conversion_data_flag_sign_pad_d;
      }

      if (flag & F_print_format_flag_uppercase_d) {
        conversion_data.flag |= F_conversion_data_flag_base_upper_d;
      }

      if (flag & F_print_format_flag_zeros_leading_d) {
        conversion_data.flag |= F_conversion_data_flag_zeros_leading_d;
      }

      if (flag & F_print_format_flag_width_value_d) {
        width = va_arg(*ap, int);
      }

      if (flag & F_print_format_flag_precision_value_d) {
        precision = va_arg(*ap, int);
      }

      // @fixme precision and width can be used together, see: "'%10.2f'".
      if (flag & F_print_format_flag_width_d) {
        conversion_data.width = width;
      }
      else if (flag & F_print_format_flag_precision_d) {
        conversion_data.width = precision;
      }

      if (type == f_print_format_type_signed_number_e) {
        *status = f_conversion_number_signed_print(va_arg(*ap, f_number_signed_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_signed_64_e) {
        *status = f_conversion_number_signed_print((f_number_signed_t) va_arg(*ap, int64_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_signed_128_e) {
        *status = f_conversion_number_signed_print((f_number_signed_t) va_arg(*ap, f_int_128_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_signed_32_e) {
        *status = f_conversion_number_signed_print((f_number_signed_t) va_arg(*ap, int32_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_signed_16_e) {
        const int16_t value = (int16_t) va_arg(*ap, int);

        *status = f_conversion_number_signed_print((f_number_signed_t) value, conversion_data, stream);
      }
      else if (type == f_print_format_type_signed_8_e) {
        const int8_t value = (int8_t) va_arg(*ap, int);

        *status = f_conversion_number_signed_print((f_number_signed_t) value, conversion_data, stream);
      }
      else if (type == f_print_format_type_size_e) {
        *status = f_conversion_number_unsigned_print((f_number_unsigned_t) va_arg(*ap, size_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_unsigned_32_e) {
        *status = f_conversion_number_unsigned_print((f_number_unsigned_t) va_arg(*ap, uint32_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_unsigned_16_e) {
        const uint16_t value = (uint16_t) va_arg(*ap, unsigned);

        *status = f_conversion_number_unsigned_print((f_number_unsigned_t) value, conversion_data, stream);
      }
      else if (type == f_print_format_type_unsigned_8_e) {
        const uint8_t value = (uint8_t) va_arg(*ap, unsigned);

        *status = f_conversion_number_unsigned_print((f_number_unsigned_t) value, conversion_data, stream);
      }
      else if (type == f_print_format_type_unsigned_64_e) {
        *status = f_conversion_number_unsigned_print((f_number_unsigned_t) va_arg(*ap, uint64_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_unsigned_128_e) {
        *status = f_conversion_number_unsigned_print((f_number_unsigned_t) va_arg(*ap, f_uint_128_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_unsigned_number_e) {
        *status = f_conversion_number_unsigned_print(va_arg(*ap, f_number_unsigned_t), conversion_data, stream);
      }
      else if (type == f_print_format_type_double_32_e || type == f_print_format_type_double_64_e) {
        int f = 0;
        char format[33];
        char buffer[129];

        memset(format, 0, 33);
        memset(buffer, 0, 129);

        format[f++] = f_string_ascii_percent_s.string[0];

        if (flag & F_print_format_flag_sign_always_d) {
          format[f++] = f_string_ascii_plus_s.string[0];
        }
        else if (flag & F_print_format_flag_sign_pad_d) {
          format[f++] = f_string_ascii_space_s.string[0];
        }

        if (flag & F_print_format_flag_align_left_d) {
          format[f++] = f_string_ascii_minus_s.string[0];
        }

        if (flag & F_print_format_flag_zeros_leading_d) {
          format[f++] = f_string_ascii_0_s.string[0];
        }

        if (flag & F_print_format_flag_width_d) {
          format[f++] = f_string_ascii_asterisk_s.string[0];
        }

        if (flag & F_print_format_flag_precision_d) {
          format[f++] = f_string_ascii_period_s.string[0];
          format[f++] = f_string_ascii_asterisk_s.string[0];
        }

        if (flag & F_print_format_flag_exponent_d) {
          if (flag & F_print_format_flag_exponent_upper_d) {
            format[f++] = f_string_ascii_E_s.string[0];
          }
          else {
            format[f++] = f_string_ascii_e_s.string[0];
          }
        }
        else if (flag & F_print_format_flag_exponent_either_d) {
          if (flag & F_print_format_flag_exponent_upper_d) {
            format[f++] = f_string_ascii_G_s.string[0];
          }
          else {
            format[f++] = f_string_ascii_g_s.string[0];
          }
        }
        else {
          format[f++] = f_string_ascii_f_s.string[0];
        }

        format[f] = 0;

        if (type == f_print_format_type_double_32_e) {
          const double value = va_arg(*ap, double);

          if (flag & F_print_format_flag_width_d) {
            if (flag & F_print_format_flag_precision_d) {
              snprintf(buffer, 128, format, width, precision, value);
            }
            else {
              snprintf(buffer, 128, format, width, value);
            }
          }
          else if (flag & F_print_format_flag_precision_d) {
            snprintf(buffer, 128, format, precision, value);
          }
          else {
            snprintf(buffer, 128, format, value);
          }
        }
        else {
          const long double value = va_arg(*ap, long double);

          if (flag & F_print_format_flag_width_d) {
            if (flag & F_print_format_flag_precision_d) {
              snprintf(buffer, 128, format, width, precision, value);
            }
            else {
              snprintf(buffer, 128, format, width, value);
            }
          }
          else if (flag & F_print_format_flag_precision_d) {
            snprintf(buffer, 128, format, precision, value);
          }
          else {
            snprintf(buffer, 128, format, value);
          }
        }

        *status = f_print_terminated(buffer, stream);
      }

      return string;
    } // for

    *status = F_status_set_error(F_valid_not);

    return string;
  }
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_)

#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_)
  f_string_t private_fl_print_convert_number(f_string_t string, va_list *ap, unsigned int * const number, f_status_t * const status) {

    for (*number = 0; *string; string += 1) {

      if (*string > 0x2f && *string < 0x3a) {
        *number *= 10;
        *number += 0xf & *string;
      }
      else if (*string == f_string_ascii_asterisk_s.string[0]) {
        *number = va_arg(*ap, unsigned int);

        break;
      }
      else {
        break;
      }
    } // for

    return string;
  }
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_)

#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)
  f_status_t private_fl_print_trim_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    // Skip past leading whitespace.
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

          if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
            return F_status_set_error(F_output);
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

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)

#if !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    // Skip past leading whitespace.
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

      // Consider invalid data not-whitespace.
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

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

          if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
            return F_status_set_error(F_output);
          }

          i += macro_f_utf_byte_width(string[i]);
        } // while

        if (i >= length) break;
      }

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_except_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_safely_) || !defined(_di_fl_print_trim_except_in_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_safely_)
  f_status_t private_fl_print_trim_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    // Skip past leading whitespace.
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

      // Invalid UTF will not be treated as whitespace.
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

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

        if (j == length || status == F_true) break;

        // Print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
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
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
              return F_status_set_error(F_output);
            }

            i = length;
            status = F_none;

            break;
          }

          if (!string[i]) {
            if (!fputc_unlocked(string[i], stream)) {
              return F_status_set_error(F_output);
            }

            ++i;

            continue;
          }

          status = f_utf_is_valid(string + i, length - i);

          if (status == F_true) {
            if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
              return F_status_set_error(F_output);
            }
          }
          else {
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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
        if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_safely_) || !defined(_di_fl_print_trim_except_in_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_safely_)

#if !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t at = 0;
    f_array_length_t at2 = 0;
    f_array_length_t in = 0;
    f_array_length_t in2 = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    // Skip past leading whitespace.
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

      // Invalid UTF will not be treated as whitespace.
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

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

        // Print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
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
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
              return F_status_set_error(F_output);
            }

            i = length;
            status = F_none;

            break;
          }

          if (!string[i]) {
            ++i;

            continue;
          }

          status = f_utf_is_valid(string + i, length - i);

          if (status == F_true) {
            if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
              return F_status_set_error(F_output);
            }
          }
          else {
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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
        if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)

#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  f_status_t private_fl_print_trim(const f_string_t string, const f_array_length_t length, FILE * const stream) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    // Skip past leading whitespace.
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

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

        // Print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (!string[i]) {
            ++i;

            continue;
          }

          if (i + macro_f_utf_byte_width(string[i]) >= length) {
            return F_status_set_error(F_complete_not_utf_stop);
          }

          if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
            return F_status_set_error(F_output);
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

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

#if !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)
  f_status_t private_fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE * const stream) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    // Skip past leading whitespace.
    while (i < length) {

      if (!string[i]) {
        ++i;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // Consider invalid data not-whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    f_string_t s = 0;

    while (i < length) {

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

        // Print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
            return F_status_set_error(F_output);
          }

          i += macro_f_utf_byte_width(string[i]);
        } // while

        if (i >= length) break;
      }

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)

#if !defined(_di_fl_print_trim_raw_safely_) || !defined(_di_fl_print_trim_dynamic_raw_safely_) || !defined(_di_fl_print_trim_dynamic_partial_raw_safely_)
  f_status_t private_fl_print_trim_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const stream) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    // Skip past leading whitespace.
    while (i < length) {

      if (!string[i]) {
        ++i;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // Invalid UTF will not be treated as whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    while (i < length) {

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

        if (j == length || status == F_true) break;

        // Print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (i + macro_f_utf_byte_width(string[i]) >= length) {
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
              return F_status_set_error(F_output);
            }

            i = length;
            status = F_none;

            break;
          }

          if (!string[i]) {
            if (!fputc_unlocked(string[i], stream)) {
              return F_status_set_error(F_output);
            }

            ++i;

            continue;
          }

          status = f_utf_is_valid(string + i, length - i);

          if (status == F_true) {
            if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
              return F_status_set_error(F_output);
            }
          }
          else {
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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
        if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_raw_safely_) || !defined(_di_fl_print_trim_dynamic_raw_safely_) || !defined(_di_fl_print_trim_dynamic_partial_raw_safely_)

#if !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)
  f_status_t private_fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE * const stream) {

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    f_string_t s = 0;

    // Skip past leading whitespace.
    while (i < length) {

      if (!string[i]) {
        ++i;

        continue;
      }

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // Invalid UTF will not be treated as whitespace.
      if (F_status_is_error(status) || status == F_false) break;

      i += macro_f_utf_byte_width(string[i]);
    } // while

    while (i < length) {

      status = f_utf_is_whitespace(string + i, (length - i) + 1);

      // Determine if this is an end of string whitespace that needs to be trimmed.
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

        // Print all processed whitespace (note: control characters are not whitespace so no checks for this are needed).
        while (i < j) {

          if (i + macro_f_utf_byte_width(string[i]) >= length) {
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
              return F_status_set_error(F_output);
            }

            i = length;
            status = F_none;

            break;
          }

          if (!string[i]) {
            ++i;

            continue;
          }

          status = f_utf_is_valid(string + i, length - i);

          if (status == F_true) {
            if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
              return F_status_set_error(F_output);
            }
          }
          else {
            if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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
        if (!fwrite_unlocked(f_print_sequence_unknown_s.string, 1, f_print_sequence_unknown_s.used, stream) < f_print_sequence_unknown_s.used) {
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

      if (fwrite_unlocked(string + i, 1, macro_f_utf_byte_width(string[i]), stream) < macro_f_utf_byte_width(string[i])) {
        return F_status_set_error(F_output);
      }

      i += macro_f_utf_byte_width(string[i]);
    } // while

    return F_none;
  }
#endif // !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)

#ifdef __cplusplus
} // extern "C"
#endif

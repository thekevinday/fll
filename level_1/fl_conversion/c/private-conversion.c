#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_conversion_dynamic_partial_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)
  f_status_t private_fl_conversion_dynamic_to_binary_signed(const uint16_t flag, const f_string_t string, const f_array_length_t length, f_number_signed_t * const number) {

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = 0; i < length; ++i) {

      if (string[i] == f_string_ascii_period_s.string[0]) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_binary(string[i], &digit) == F_none) {
        if (digits) {
          ++digits;

          if (flag & FL_conversion_data_flag_negative_d) {
            if (digits > F_conversion_digits_binary_signed_d) {
              return F_status_set_error(F_number_underflow);
            }

            if (flag & FL_conversion_data_flag_endian_big_d) {
              converted >>= 1;
            }
            else if (flag & FL_conversion_data_flag_endian_little_d) {
              converted <<= 1;
            }
            else {
              #ifdef _is_F_endian_big
                converted >>= 1;
              #else
                converted <<= 1;
              #endif // _is_F_endian_big
            }

            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_binary_signed_d) {
              return F_status_set_error(F_number_overflow);
            }

            if (flag & FL_conversion_data_flag_endian_big_d) {
              converted >>= 1;
            }
            else if (flag & FL_conversion_data_flag_endian_little_d) {
              converted <<= 1;
            }
            else {
              #ifdef _is_F_endian_big
                converted >>= 1;
              #else
                converted <<= 1;
              #endif // _is_F_endian_big
            }

            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (flag & FL_conversion_data_flag_negative_d) {
            converted = (f_number_unsigned_t) (0 - digit);
          }
          else {
            converted = (f_number_unsigned_t) digit;
          }
        }
      }
      else if (string[i]) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;

    return F_none;
  }
#endif // !defined(_di_fl_conversion_dynamic_partial_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)

#if !defined(_di_fl_conversion_dynamic_partial_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)
  f_status_t private_fl_conversion_dynamic_to_binary_unsigned(const uint16_t flag, const f_string_t string, const f_array_length_t length, f_number_unsigned_t * const number) {

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = 0; i < length; ++i) {

      if (string[i] == f_string_ascii_period_s.string[0]) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_binary(string[i], &digit) == F_none) {
        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_binary_unsigned_d) {
            return F_status_set_error(F_number_overflow);
          }

          if (flag & FL_conversion_data_flag_endian_big_d) {
            converted >>= 1;
          }
          else if (flag & FL_conversion_data_flag_endian_little_d) {
            converted <<= 1;
          }
          else {
            #ifdef _is_F_endian_big
              converted >>= 1;
            #else
              converted <<= 1;
            #endif // _is_F_endian_big
          }

          converted += digit;
        }
        else if (digit) {
          digits = 1;
          converted = (f_number_unsigned_t) digit;
        }
      }
      else if (string[i]) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;

    return F_none;
  }
#endif // !defined(_di_fl_conversion_dynamic_partial_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)

#if !defined(_di_fl_conversion_dynamic_partial_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)
  f_status_t private_fl_conversion_dynamic_to_base_signed(const fl_conversion_data_t data, const f_string_t string, const f_array_length_t length, f_number_signed_t * const number) {

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    f_status_t (*character_to_digit)(const f_char_t character, uint8_t * const number) = 0;

    if (data.base == 10) {
      character_to_digit = f_conversion_character_to_decimal;
    }
    else if (data.base == 16) {
      character_to_digit = f_conversion_character_to_hexidecimal;
    }
    else if (data.base == 12) {
      character_to_digit = f_conversion_character_to_duodecimal;
    }
    else if (data.base == 8) {
      character_to_digit = f_conversion_character_to_octal;
    }

    for (f_array_length_t i = 0; i < length; ++i) {

      if (string[i] == f_string_ascii_period_s.string[0]) {
        return F_status_set_error(F_number_decimal);
      }

      if (character_to_digit(string[i], &digit) == F_none) {
        if (digits) {
          ++digits;

          if (data.flag & FL_conversion_data_flag_negative_d) {
            if (digits > F_conversion_digits_decimal_signed_d) {
              if ((converted * data.base) - digit < F_number_t_size_negative_d || (converted * data.base) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted *= data.base;
            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_decimal_signed_d) {
              if ((converted * data.base) + digit > F_number_t_size_positive_d || (converted * data.base) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted *= data.base;
            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (data.flag & FL_conversion_data_flag_negative_d) {
            converted = (f_number_unsigned_t) (0 - digit);
          }
          else {
            converted = (f_number_unsigned_t) digit;
          }
        }
      }
      else if (string[i]) {
        return F_status_set_error(F_number);
      }
    } // for

    // Ensure bytes are in correct order by reversing bytes if requested byte order is different than the host byte order.
    #ifdef _is_F_endian_big
      if (data.flag & FL_conversion_data_flag_endian_little_d) {
        *number = macro_f_utf_char_t_from_char_1_le(macro_f_utf_char_t_to_char_1_be(converted))
                | macro_f_utf_char_t_from_char_2_le(macro_f_utf_char_t_to_char_2_be(converted))
                | macro_f_utf_char_t_from_char_3_le(macro_f_utf_char_t_to_char_3_be(converted))
                | macro_f_utf_char_t_from_char_4_le(macro_f_utf_char_t_to_char_4_be(converted));

        return F_none;
      }
    #else
      if (data.flag & FL_conversion_data_flag_endian_big_d) {
        *number = macro_f_utf_char_t_from_char_1_be(macro_f_utf_char_t_to_char_1_le(converted))
                | macro_f_utf_char_t_from_char_2_be(macro_f_utf_char_t_to_char_2_le(converted))
                | macro_f_utf_char_t_from_char_3_be(macro_f_utf_char_t_to_char_3_le(converted))
                | macro_f_utf_char_t_from_char_4_be(macro_f_utf_char_t_to_char_4_le(converted));

        return F_none;
      }
    #endif // _is_F_endian_big

    *number = converted;

    return F_none;
  }
#endif // !defined(_di_fl_conversion_dynamic_partial_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)

#if !defined(_di_fl_conversion_dynamic_partial_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)
  f_status_t private_fl_conversion_dynamic_to_base_unsigned(const fl_conversion_data_t data, const f_string_t string, const f_array_length_t length, f_number_unsigned_t * const number) {

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    f_status_t (*character_to_digit)(const f_char_t character, uint8_t * const number) = 0;

    if (data.base == 10) {
      character_to_digit = f_conversion_character_to_decimal;
    }
    else if (data.base == 16) {
      character_to_digit = f_conversion_character_to_hexidecimal;
    }
    else if (data.base == 12) {
      character_to_digit = f_conversion_character_to_duodecimal;
    }
    else if (data.base == 8) {
      character_to_digit = f_conversion_character_to_octal;
    }

    for (f_array_length_t i = 0; i < length; ++i) {

      if (string[i] == f_string_ascii_period_s.string[0]) {
        return F_status_set_error(F_number_decimal);
      }

      if (character_to_digit(string[i], &digit) == F_none) {
        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_decimal_unsigned_d) {
            if ((converted * data.base) + digit > F_number_t_size_unsigned_d || (converted * data.base) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted *= data.base;
          converted += digit;
        }
        else if (digit) {
          digits = 1;
          converted = (f_number_unsigned_t) digit;
        }
      }
      else if (string[i]) {
        return F_status_set_error(F_number);
      }
    } // for

    // Ensure bytes are in correct order by reversing bytes if requested byte order is different than the host byte order.
    #ifdef _is_F_endian_big
      if (data.flag & FL_conversion_data_flag_endian_little_d) {
        *number = macro_f_utf_char_t_from_char_1_le(macro_f_utf_char_t_to_char_1_be(converted))
                | macro_f_utf_char_t_from_char_2_le(macro_f_utf_char_t_to_char_2_be(converted))
                | macro_f_utf_char_t_from_char_3_le(macro_f_utf_char_t_to_char_3_be(converted))
                | macro_f_utf_char_t_from_char_4_le(macro_f_utf_char_t_to_char_4_be(converted));

        return F_none;
      }
    #else
      if (data.flag & FL_conversion_data_flag_endian_big_d) {
        *number = macro_f_utf_char_t_from_char_1_be(macro_f_utf_char_t_to_char_1_le(converted))
                | macro_f_utf_char_t_from_char_2_be(macro_f_utf_char_t_to_char_2_le(converted))
                | macro_f_utf_char_t_from_char_3_be(macro_f_utf_char_t_to_char_3_le(converted))
                | macro_f_utf_char_t_from_char_4_be(macro_f_utf_char_t_to_char_4_le(converted));

        return F_none;
      }
    #endif // _is_F_endian_big

    *number = converted;

    return F_none;
  }
#endif // !defined(_di_fl_conversion_dynamic_partial_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)

#if !defined(_di_fl_conversion_dynamic_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_)
  f_status_t private_fl_conversion_dynamic_to_signed_detect(const uint16_t flag, const f_string_t string, const f_array_length_t length, f_number_signed_t * const number) {

    uint8_t width = 0;
    f_array_length_t width_max = 0;
    uint8_t mode = 0;
    int8_t vector = 0; // 0 for assumed positive, 1 for explicit positive, -1 for negative.
    f_array_length_t j = 0;
    f_array_length_t offset = 0;
    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < length; ++i) {

      width = macro_f_utf_byte_width_is(string[i]);

      if (!width) {
        if (isspace(string[i])) {
          if (!mode && !vector) {
            ++offset;

            continue;
          }

          return F_status_set_error(F_number);
        }
      }
      else {
        if (!mode && !vector) {
          width_max = length - i;

          status = f_utf_is_whitespace(string + i, width_max);

          if (status == F_true) {
            offset = i + 1;

            continue;
          }

          if (F_status_is_error(status)) {
            if (status == F_status_set_error(F_maybe)) {
              status = F_status_set_error(F_complete_not_utf);
            }

            return status;
          }
        }

        return F_status_set_error(F_number);
      }

      if (string[i] == f_string_ascii_0_s.string[0]) {

        // Skip past all NULLs.
        for (j = i + 1; j < length; ++j) {
          if (string[j]) break;
        } // for

        // Immediate next value must be either a number, 't', 'T', 'x', 'X', 'd', 'D', 'o', 'O', 'b', or 'B'.
        if (j >= length) {
          *number = 0;

          return F_none;
        }

        if (string[j] > f_string_ascii_slash_backward_s.string[0] && string[j] < f_string_ascii_colon_s.string[0]) {
          mode = 10;
        }
        else if (string[j] == f_string_ascii_t_s.string[0] || string[j] == f_string_ascii_t_s.string[0]) {
          mode = 10;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_x_s.string[0] || string[j] == f_string_ascii_X_s.string[0]) {
          mode = 16;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_d_s.string[0] || string[j] == f_string_ascii_D_s.string[0]) {
          mode = 12;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_o_s.string[0] || string[j] == f_string_ascii_O_s.string[0]) {
          mode = 8;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_b_s.string[0] || string[j] == f_string_ascii_B_s.string[0]) {
          mode = 2;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_period_s.string[0]) {
          return F_status_set_error(F_number_decimal);
        }
        else {
          return F_status_set_error(F_number);
        }

        break;
      }

      // Plus sign is only allowed as the first non-whitespace character.
      if (string[i] == f_string_ascii_plus_s.string[0]) {
        if (!mode && !vector) {
          vector = 1;
          ++offset;
        }
        else {
          return F_status_set_error(F_number);
        }
      }

      // Negative sign is not allowed.
      if (string[i] == f_string_ascii_minus_s.string[0]) {
        if (!mode && !vector) {
          vector = -1;
          ++offset;
        }
        else {
          return F_status_set_error(F_number);
        }
      }

      if (f_conversion_character_is_decimal(string[i]) == F_true) {
        mode = 10;

        break;
      }

      return F_status_set_error(F_number);
    } // for

    if (!mode) {
      return F_status_set_error(F_number);
    }

    if (offset >= length) {
      return F_status_set_error(F_number);
    }

    fl_conversion_data_t data = macro_fl_conversion_data_t_initialize(mode, flag);

    if (vector == -1) {
      data.flag |= FL_conversion_data_flag_negative_d;
    }
    else if (data.flag & FL_conversion_data_flag_negative_d) {
      data.flag -= FL_conversion_data_flag_negative_d;
    }

    if (mode == 10 || mode == 16 || mode == 12 || mode == 8) {
      return private_fl_conversion_dynamic_to_base_signed(data, string + offset, length - offset, number);
    }

    if (mode == 2) {
      return private_fl_conversion_dynamic_to_binary_signed(data.flag, string + offset, length - offset, number);
    }

    return F_status_set_error(F_base_not);
  }
#endif // !defined(_di_fl_conversion_dynamic_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_)

#if !defined(_di_fl_conversion_dynamic_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_)
  f_status_t private_fl_conversion_dynamic_to_unsigned_detect(const uint16_t flag, const f_string_t string, const f_array_length_t length, f_number_unsigned_t * const number) {

    uint8_t width = 0;
    f_array_length_t width_max = 0;
    uint8_t mode = 0;
    f_array_length_t j = 0;
    f_array_length_t offset = 0;
    f_status_t status = F_none;
    int8_t sign_found = 0;

    for (f_array_length_t i = 0; i < length; ++i) {

      width = macro_f_utf_byte_width_is(string[i]);

      if (!width) {
        if (isspace(string[i])) {
          if (!mode) {
            ++offset;

            continue;
          }

          return F_status_set_error(F_number);
        }
      }
      else {
        if (!mode) {
          width_max = length - i;

          status = f_utf_is_whitespace(string + i, width_max);

          if (status == F_true) {
            offset = i + 1;

            continue;
          }

          if (F_status_is_error(status)) {
            if (status == F_status_set_error(F_maybe)) {
              status = F_status_set_error(F_complete_not_utf);
            }

            return status;
          }
        }

        return F_status_set_error(F_number);
      }

      if (string[i] == f_string_ascii_0_s.string[0]) {

        // Skip past all NULLs.
        for (j = i + 1; j < length; ++j) {
          if (string[j]) break;
        } // for

        // Immediate next value must be either a number, 't', 'T', 'x', 'X', 'd', 'D', 'o', 'O', 'b', or 'B'.
        if (j >= length) {
          *number = 0;

          return F_none;
        }
        else if (string[j] > f_string_ascii_slash_backward_s.string[0] && string[j] < f_string_ascii_colon_s.string[0]) {
          mode = 10;
        }
        else if (string[j] == f_string_ascii_t_s.string[0] || string[j] == f_string_ascii_t_s.string[0]) {
          mode = 10;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_x_s.string[0] || string[j] == f_string_ascii_X_s.string[0]) {
          mode = 16;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_d_s.string[0] || string[j] == f_string_ascii_D_s.string[0]) {
          mode = 12;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_o_s.string[0] || string[j] == f_string_ascii_O_s.string[0]) {
          mode = 8;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_b_s.string[0] || string[j] == f_string_ascii_B_s.string[0]) {
          mode = 2;
          offset += 2;
        }
        else if (string[j] == f_string_ascii_period_s.string[0]) {
          return F_status_set_error(F_number_decimal);
        }
        else {
          return F_status_set_error(F_number);
        }

        break;
      }

      if (string[i] == f_string_ascii_plus_s.string[0]) {
        ++offset;
        sign_found = 1;
      }

      if (string[i] == f_string_ascii_minus_s.string[0]) {
        ++offset;
        sign_found = -1;
      }

      if (f_conversion_character_is_decimal(string[i]) == F_true) {
        mode = 10;

        break;
      }

      return F_status_set_error(F_number);
    } // for

    if (!mode) {
      return F_status_set_error(F_number);
    }

    if (offset >= length) {
      return F_status_set_error(F_number);
    }

    fl_conversion_data_t data = macro_fl_conversion_data_t_initialize(mode, flag);

    if (data.flag & FL_conversion_data_flag_negative_d) {
      data.flag -= FL_conversion_data_flag_negative_d;
    }

    if (mode == 10 || mode == 16 || mode == 12 || mode == 8) {
      status = private_fl_conversion_dynamic_to_base_unsigned(data, string + offset, length - offset, number);
    }
    else if (mode == 2) {
      status = private_fl_conversion_dynamic_to_binary_unsigned(data.flag, string + offset, length - offset, number);
    }
    else {
      return F_status_set_error(F_base_not);
    }

    // The +/- signs are not allowed.
    if (sign_found) {
      if (status == F_none) {
        if (sign_found == -1) {
          return F_status_set_error(F_number_negative);
        }

        return F_status_set_error(F_number_positive);
      }

      return F_status_set_error(F_number);
    }

    return status;
  }
#endif // !defined(_di_fl_conversion_dynamic_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_)

#ifdef __cplusplus
} // extern "C"
#endif

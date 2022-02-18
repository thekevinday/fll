#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative, FILE * const output) {

    int digits = 0;

    for (register f_number_unsigned_t remaining = number; remaining; ++digits) {
      remaining /= data.base;
    } // for

    // A zero value should always show at least 1 zero when width is not 0.
    if (data.width && !number) {
      ++digits;
    }

    if (data.width > digits) {
      if (data.flag & F_conversion_data_flag_zeros_leading_d) {
        if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_0_s, data.width - digits, output))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
          return F_status_set_error(F_output);
        }
      }
      else if (number) {
        if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_space_s, data.width - digits, output))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
          return F_status_set_error(F_output);
        }
      }
      else {
        if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_space_s, data.width - digits, output))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
          return F_status_set_error(F_output);
        }
      }
    }
    else if (number) {
      if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
        return F_status_set_error(F_output);
      }

      if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
        return F_status_set_error(F_output);
      }
    }
    else if (data.width) {
      if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
        return F_status_set_error(F_output);
      }

      if (fwrite_unlocked(f_string_ascii_0_s.string, 1, f_string_ascii_0_s.used, output) < f_string_ascii_0_s.used) {
        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, FILE * const output) {

    f_number_unsigned_t power = 1;

    for (register uint8_t i = 1; i < digits; ++i) {
      power *= data.base;
    } // for

    if (data.base == 2) {
      f_number_unsigned_t work = 0x1 << (digits - 1);

      while (digits--) {

        if (work & number) {
          if (fwrite_unlocked(f_string_ascii_1_s.string, 1, f_string_ascii_1_s.used, output) < f_string_ascii_1_s.used) {
            return F_status_set_error(F_output);
          }
        }
        else {
          if (fwrite_unlocked(f_string_ascii_0_s.string, 1, f_string_ascii_0_s.used, output) < f_string_ascii_0_s.used) {
            return F_status_set_error(F_output);
          }
        }

        #ifdef _is_F_endian_big
          work <<= 1; // @todo review this and see if there is more that needs to be done.
        #else
          work >>= 1;
        #endif // _is_F_endian_big
      } // while

      return F_none;
    }

    f_number_unsigned_t current = number;
    f_number_unsigned_t work = 0;

    for (char c = 0; digits; --digits) {

      work = current / power;
      current -= work * power;
      power /= data.base;

      if (work < 0xa) {
        c = 0x30 + work;
      }
      else {
        if (data.flag & F_conversion_data_flag_base_upper_d) {
          c = 0x37 + work;
        }
        else {
          c = 0x57 + work;
        }
      }

      if (!fwrite_unlocked(&c, 1, 1, output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_pad(const f_conversion_data_t data, const f_string_static_t pad, int total, FILE * const output) {

    for (; total; --total) {

      if (fwrite_unlocked(pad.string, 1, pad.used, output) < pad.used) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_prefix(const f_conversion_data_t data, const uint8_t negative, FILE * const output) {

    if (negative) {
      if (negative == 1) {
        if (fwrite_unlocked(f_string_ascii_minus_s.string, 1, f_string_ascii_minus_s.used, output) < f_string_ascii_minus_s.used) {
          return F_status_set_error(F_output);
        }
      }
    }
    else if (data.flag & F_conversion_data_flag_sign_always_d) {
      if (fwrite_unlocked(f_string_ascii_plus_s.string, 1, f_string_ascii_plus_s.used, output) < f_string_ascii_plus_s.used) {
        return F_status_set_error(F_output);
      }
    }
    else if (data.flag & F_conversion_data_flag_sign_pad_d) {
      if (fwrite_unlocked(f_string_ascii_space_s.string, 1, f_string_ascii_space_s.used, output) < f_string_ascii_space_s.used) {
        return F_status_set_error(F_output);
      }
    }

    if (data.flag & F_conversion_data_flag_base_prepend_d) {
      if (fwrite_unlocked(f_string_ascii_0_s.string, 1, f_string_ascii_0_s.used, output) < f_string_ascii_0_s.used) {
        return F_status_set_error(F_output);
      }

      char c = 0;

      switch (data.base) {
        case 2:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_B_s.string[0] : f_string_ascii_b_s.string[0];
          break;

        case 8:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_O_s.string[0] : f_string_ascii_o_s.string[0];
          break;

        case 10:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_T_s.string[0] : f_string_ascii_t_s.string[0];
          break;

        case 12:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_D_s.string[0] : f_string_ascii_d_s.string[0];
          break;

        case 16:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_X_s.string[0] : f_string_ascii_x_s.string[0];
          break;

        default:
          break;
      }

      if (c) {
        if (!fwrite_unlocked(&c, 1, 1, output)) {
          return F_status_set_error(F_output);
        }
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  f_status_t private_f_conversion_digit_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative, f_string_dynamic_t * const destination) {

    int digits = 0;

    for (register f_number_unsigned_t remaining = number; remaining; ++digits) {
      remaining /= data.base;
    } // for

    // A zero value should always show at least 1 zero when width is not 0.
    if (data.width && !number) {
      ++digits;
    }

    // Ensure there is enough space for pad, adding the sign (1) and the prepend units (2).
    {
      long max = 3;

      if (digits > data.width) {
        max += digits;
      }
      else {
        max += data.width;
      }

      const f_status_t status = f_string_dynamic_increase_by(max, destination);
      if (F_status_is_error(status)) return status;
    }

    if (data.width > digits) {
      if (data.flag & F_conversion_data_flag_zeros_leading_d) {
        private_f_conversion_digit_to_string_prefix(data, negative, destination);
        private_f_conversion_digit_to_string_pad(data, f_string_ascii_0_s.string[0], data.width - digits, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
      else if (number) {
        private_f_conversion_digit_to_string_pad(data, f_string_ascii_space_s.string[0], data.width - digits, destination);
        private_f_conversion_digit_to_string_prefix(data, negative, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
      else {
        private_f_conversion_digit_to_string_pad(data, f_string_ascii_space_s.string[0], data.width - digits, destination);
        private_f_conversion_digit_to_string_prefix(data, negative, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
    }
    else if (number) {
      private_f_conversion_digit_to_string_prefix(data, negative, destination);
      private_f_conversion_digit_to_string_number(data, number, digits, destination);
    }
    else if (data.width) {
      private_f_conversion_digit_to_string_prefix(data, negative, destination);

      destination->string[destination->used++] = f_string_ascii_0_s.string[0];
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  void private_f_conversion_digit_to_string_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, f_string_dynamic_t * const destination) {

    f_number_unsigned_t power = 1;

    for (register uint8_t i = 1; i < digits; ++i) {
      power *= data.base;
    } // for

    if (data.base == 2) {
      f_number_unsigned_t work = 0x1 << (digits - 1);

      while (digits--) {

        if (work & number) {
          destination->string[destination->used++] = f_string_ascii_1_s.string[0];
        }
        else {
          destination->string[destination->used++] = f_string_ascii_0_s.string[1];
        }

        #ifdef _is_F_endian_big
          work <<= 1; // @todo review this and see if there is more that needs to be done.
        #else
          work >>= 1;
        #endif // _is_F_endian_big
      } // while

      return;
    }

    f_number_unsigned_t current = number;
    f_number_unsigned_t work = 0;

    for (char c = 0; digits; --digits) {

      work = current / power;
      current -= work * power;
      power /= data.base;

      if (work < 0xa) {
        c = 0x30 + work;
      }
      else {
        if (data.flag & F_conversion_data_flag_base_upper_d) {
          c = 0x37 + work;
        }
        else {
          c = 0x57 + work;
        }
      }

      destination->string[destination->used++] = c;
    } // for
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  void private_f_conversion_digit_to_string_pad(const f_conversion_data_t data, const char pad, int total, f_string_dynamic_t * const destination) {

    for (; total; --total) {
      destination->string[destination->used++] = pad;
    } // for
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  void private_f_conversion_digit_to_string_prefix(const f_conversion_data_t data, const uint8_t negative, f_string_dynamic_t * const destination) {

    if (negative) {
      if (negative == 1) {
        destination->string[destination->used++] = f_string_ascii_minus_s.string[0];
      }
      else if (data.flag & (F_conversion_data_flag_sign_always_d | F_conversion_data_flag_sign_pad_d)) {
        destination->string[destination->used++] = f_string_ascii_space_s.string[0];
      }
    }
    else if (data.flag & F_conversion_data_flag_sign_always_d) {
      destination->string[destination->used++] = f_string_ascii_plus_s.string[0];
    }
    else if (data.flag & F_conversion_data_flag_sign_pad_d) {
      destination->string[destination->used++] = f_string_ascii_space_s.string[0];
    }

    if (data.flag & F_conversion_data_flag_base_prepend_d) {
      destination->string[destination->used++] = f_string_ascii_0_s.string[0];

      char c = 0;

      switch (data.base) {
        case 2:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_B_s.string[0] : f_string_ascii_b_s.string[0];
          break;

        case 8:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_O_s.string[0] : f_string_ascii_o_s.string[0];
          break;

        case 10:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_T_s.string[0] : f_string_ascii_t_s.string[0];
          break;

        case 12:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_D_s.string[0] : f_string_ascii_d_s.string[0];
          break;

        case 16:
          c = data.flag & F_conversion_data_flag_base_upper_d ? f_string_ascii_X_s.string[0] : f_string_ascii_x_s.string[0];
          break;

        default:
          break;
      }

      if (c) {
        destination->string[destination->used++] = c;
      }
    }
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#ifdef __cplusplus
} // extern "C"
#endif

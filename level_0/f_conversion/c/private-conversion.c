#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative_or_zero, FILE * const stream) {

    int digits = 0;

    // A zero value should always show at least 1 zero when width is not 0.
    if (data.width && !number) {
      digits = 1;
    }
    else {
      for (register f_number_unsigned_t remaining = number; remaining; ++digits) {
        remaining /= data.base;
      } // for
    }

    if (data.width > digits) {
      if (data.flag & F_conversion_data_flag_zeros_leading_d) {
        if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative_or_zero, stream))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_0_s, data.width - digits, stream))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, stream))) {
          return F_status_set_error(F_output);
        }
      }
      else if (number) {
        if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_space_s, data.width - digits, stream))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative_or_zero, stream))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, stream))) {
          return F_status_set_error(F_output);
        }
      }
      else {
        if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_space_s, data.width - digits, stream))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative_or_zero, stream))) {
          return F_status_set_error(F_output);
        }

        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, stream))) {
          return F_status_set_error(F_output);
        }
      }
    }
    else if (number) {
      if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative_or_zero, stream))) {
        return F_status_set_error(F_output);
      }

      if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, stream))) {
        return F_status_set_error(F_output);
      }
    }
    else if (data.width) {
      if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative_or_zero, stream))) {
        return F_status_set_error(F_output);
      }

      if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, stream))) {
        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, FILE * const stream) {

    f_number_unsigned_t current = 0;
    f_number_unsigned_t power = 1;
    f_number_unsigned_t work = 0;

    for (register uint8_t i = 1; i < digits; ++i) {
      power *= data.base;
    } // for

    if (data.base == 2) {
      #ifdef _is_F_endian_big
        work = 0x1 >> (digits - 1);
      #else
        work = 0x1 << (digits - 1);
      #endif // _is_F_endian_big

      while (digits--) {

        current = 0;

        if (work & number) {
          do {
            current += fwrite_unlocked(f_string_ascii_1_s.string + current, sizeof(f_char_t), f_string_ascii_1_s.used - current, stream);
            if (ferror_unlocked(stream)) return F_status_set_error(F_output);

          } while (current < f_string_ascii_1_s.used);
        }
        else {
          do {
            current += fwrite_unlocked(f_string_ascii_0_s.string + current, sizeof(f_char_t), f_string_ascii_0_s.used - current, stream);
            if (ferror_unlocked(stream)) return F_status_set_error(F_output);

          } while (current < f_string_ascii_0_s.used);
        }

        if (data.flag & F_conversion_data_flag_endian_big_d) {
          work <<= 1;
        }
        else if (data.flag & F_conversion_data_flag_endian_big_d) {
          work >>= 1;
        }
        else {
          #ifdef _is_F_endian_big
            work <<= 1;
          #else
            work >>= 1;
          #endif // _is_F_endian_big
        }
      } // while

      return F_none;
    }

    f_char_t c = 0;
    size_t count = 0;

    current = number;

    for (int i = 0; i < digits; ++i) {

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

      count = 0;

      do {
        count += fwrite_unlocked(&c, 1, sizeof(f_char_t), stream);
        if (ferror_unlocked(stream)) return F_status_set_error(F_output);

      } while (count < sizeof(f_char_t));
    } // for

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_pad(const f_conversion_data_t data, const f_string_static_t pad, int total, FILE * const stream) {

    for (int count; total; --total) {

      count = 0;

      do {
        count += fwrite_unlocked(pad.string + count, sizeof(f_char_t), pad.used - count, stream);
        if (ferror_unlocked(stream)) return F_status_set_error(F_output);

      } while (count < pad.used);
    } // for

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_prefix(const f_conversion_data_t data, const uint8_t negative_or_zero, FILE * const stream) {

    if (negative_or_zero) {
      if (negative_or_zero == 1) {
        {
          int count = 0;

          do {
            count += fwrite_unlocked(f_string_ascii_minus_s.string + count, sizeof(f_char_t), f_string_ascii_minus_s.used - count, stream);
            if (ferror_unlocked(stream)) return F_status_set_error(F_output);

          } while (count < f_string_ascii_minus_s.used);
        }
      }
    }
    else if (data.flag & F_conversion_data_flag_sign_always_d) {
      int count = 0;

      do {
        count += fwrite_unlocked(f_string_ascii_plus_s.string + count, sizeof(f_char_t), f_string_ascii_plus_s.used - count, stream);
        if (ferror_unlocked(stream)) return F_status_set_error(F_output);

      } while (count < f_string_ascii_plus_s.used);
    }
    else if (data.flag & F_conversion_data_flag_sign_pad_d) {
      int count = 0;

      do {
        count += fwrite_unlocked(f_string_ascii_space_s.string + count, sizeof(f_char_t), f_string_ascii_space_s.used - count, stream);
        if (ferror_unlocked(stream)) return F_status_set_error(F_output);

      } while (count < f_string_ascii_space_s.used);
    }

    if (data.flag & F_conversion_data_flag_base_prepend_d) {
      {
        int count = 0;

        do {
          count += fwrite_unlocked(f_string_ascii_0_s.string + count, sizeof(f_char_t), f_string_ascii_0_s.used - count, stream);
          if (ferror_unlocked(stream)) return F_status_set_error(F_output);

        } while (count < f_string_ascii_0_s.used);
      }

      f_char_t c = 0;

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
        int count = 0;

        do {
          count += fwrite_unlocked(&c, sizeof(f_char_t), sizeof(f_char_t) - count, stream);
          if (ferror_unlocked(stream)) return F_status_set_error(F_output);

        } while (count < sizeof(f_char_t));
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  f_status_t private_f_conversion_digit_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative_or_zero, f_string_dynamic_t * const destination) {

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
        private_f_conversion_digit_to_string_prefix(data, negative_or_zero, destination);
        private_f_conversion_digit_to_string_pad(data, f_string_ascii_0_s.string[0], data.width - digits, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
      else if (number) {
        private_f_conversion_digit_to_string_pad(data, f_string_ascii_space_s.string[0], data.width - digits, destination);
        private_f_conversion_digit_to_string_prefix(data, negative_or_zero, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
      else {
        private_f_conversion_digit_to_string_pad(data, f_string_ascii_space_s.string[0], data.width - digits, destination);
        private_f_conversion_digit_to_string_prefix(data, negative_or_zero, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
    }
    else if (number) {
      private_f_conversion_digit_to_string_prefix(data, negative_or_zero, destination);
      private_f_conversion_digit_to_string_number(data, number, digits, destination);
    }
    else if (data.width) {
      private_f_conversion_digit_to_string_prefix(data, negative_or_zero, destination);

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
      #ifdef _is_F_endian_big
        f_number_unsigned_t work = 0x1 >> (digits - 1);
      #else
        f_number_unsigned_t work = 0x1 << (digits - 1);
      #endif // _is_F_endian_big

      while (digits--) {

        if (work & number) {
          destination->string[destination->used++] = f_string_ascii_1_s.string[0];
        }
        else {
          destination->string[destination->used++] = f_string_ascii_0_s.string[1];
        }

        if (data.flag & F_conversion_data_flag_endian_big_d) {
          work <<= 1;
        }
        else if (data.flag & F_conversion_data_flag_endian_big_d) {
          work >>= 1;
        }
        else {
          #ifdef _is_F_endian_big
            work <<= 1;
          #else
            work >>= 1;
          #endif // _is_F_endian_big
        }
      } // while

      return;
    }

    f_number_unsigned_t current = number;
    f_number_unsigned_t work = 0;

    for (f_char_t c = 0; digits; --digits) {

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
  void private_f_conversion_digit_to_string_pad(const f_conversion_data_t data, const f_char_t pad, int total, f_string_dynamic_t * const destination) {

    for (; total; --total) {
      destination->string[destination->used++] = pad;
    } // for
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  void private_f_conversion_digit_to_string_prefix(const f_conversion_data_t data, const uint8_t negative_or_zero, f_string_dynamic_t * const destination) {

    if (negative_or_zero) {
      if (negative_or_zero == 1) {
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

      f_char_t c = 0;

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

#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative, FILE *output) {

    int digits = 0;

    if (number) {
      for (register f_number_unsigned_t remaining = number; remaining; ++digits) {
        remaining /= data.base;
      } // for
    }
    else {
      digits = 1;
    }

    if (data.flag & f_conversion_data_flag_base_prepend) {
      const int used = digits + 2 + (data.flag & f_conversion_data_flag_sign_always & f_conversion_data_flag_sign_pad ? 1 : 0);

      if (data.width > used) {
        if (data.flag & f_conversion_data_flag_zeros_leading) {
          if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
            return F_status_set_error(F_output);
          }

          if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_0_s[0], data.width - used, output))) {
            return F_status_set_error(F_output);
          }

          if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
            return F_status_set_error(F_output);
          }
        }
        else {
          if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_space_s[0], data.width - used, output))) {
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

        if (fwrite_unlocked(f_string_ascii_0_s, 1, 1, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }
    }
    else {
      const int used = digits + (data.flag & (f_conversion_data_flag_sign_always | f_conversion_data_flag_sign_pad) ? 1 : 0);

      if (data.width > used) {
        if (data.flag & f_conversion_data_flag_zeros_leading) {
          if (F_status_is_error(private_f_conversion_digit_to_file_prefix(data, negative, output))) {
            return F_status_set_error(F_output);
          }

          if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_0_s[0], data.width - used, output))) {
            return F_status_set_error(F_output);
          }

          if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
            return F_status_set_error(F_output);
          }
        }
        else {
          if (F_status_is_error(private_f_conversion_digit_to_file_pad(data, f_string_ascii_space_s[0], data.width - used, output))) {
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
        if (F_status_is_error(private_f_conversion_digit_to_file_number(data, number, digits, output))) {
          return F_status_set_error(F_output);
        }
      }
      else if (data.width) {
        if (fwrite_unlocked(f_string_ascii_0_s, 1, 1, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, FILE *output) {

    f_number_unsigned_t power = 1;

    for (register uint8_t i = 1; i < digits; ++i) {
      power *= data.base;
    } // for

    if (data.base == 2) {
      f_number_unsigned_t work = 0x1 << (digits - 1);

      while (digits--) {

        if (fwrite_unlocked((work & number) ? f_string_ascii_1_s : f_string_ascii_0_s, 1, 1, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }

        work >>= 1;
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
        if (data.flag & f_conversion_data_flag_base_upper) {
          c = 0x37 + work;
        }
        else {
          c = 0x57 + work;
        }
      }

      if (fwrite_unlocked(&c, 1, 1, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_pad(const f_conversion_data_t data, const char pad, int total, FILE *output) {

    for (; total; --total) {

      if (fwrite_unlocked(&pad, 1, 1, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  f_status_t private_f_conversion_digit_to_file_prefix(const f_conversion_data_t data, const uint8_t negative, FILE *output) {

    if (negative) {
      if (negative == 1) {
        if (fwrite_unlocked(f_string_ascii_minus_s, 1, 1, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }
    }
    else if (data.flag & f_conversion_data_flag_sign_always) {
      if (fwrite_unlocked(f_string_ascii_plus_s, 1, 1, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }
    else if (data.flag & f_conversion_data_flag_sign_pad) {
      if (fwrite_unlocked(f_string_ascii_space_s, 1, 1, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    if (data.flag & f_conversion_data_flag_base_prepend) {
      if (fwrite_unlocked(f_string_ascii_0_s, 1, 1, output) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }

      char c = 0;

      switch (data.base) {
        case 2:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_B_s[0] : f_string_ascii_b_s[0];
          break;

        case 8:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_O_s[0] : f_string_ascii_o_s[0];
          break;

        case 10:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_T_s[0] : f_string_ascii_t_s[0];
          break;

        case 12:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_D_s[0] : f_string_ascii_d_s[0];
          break;

        case 16:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_X_s[0] : f_string_ascii_x_s[0];
          break;

        default:
          break;
      }

      if (c) {
        if (fwrite_unlocked(&c, 1, 1, output) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupt);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  f_status_t private_f_conversion_digit_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative, f_string_dynamic_t *destination) {

    int digits = 0;

    for (register f_number_unsigned_t remaining = number; remaining; ++digits) {
      remaining /= data.base;
    } // for

    // Ensure there is enough space for pad, adding the sign (1) and the prepend units (2).
    {
      long max = 3;

      if (digits > data.width) {
        max += digits;
      }
      else {
        max += data.width;
      }

      if (destination->used + max > destination->size) {
        const f_status_t status = f_string_dynamic_resize(destination->used + max, destination);
        if (F_status_is_error(status)) return status;
      }
    }

    if (data.flag & f_conversion_data_flag_base_prepend) {
      const int used = digits + 2 + (data.flag & f_conversion_data_flag_sign_always & f_conversion_data_flag_sign_pad ? 1 : 0);

      if (data.width > used) {
        if (data.flag & f_conversion_data_flag_zeros_leading) {
          private_f_conversion_digit_to_string_prefix(data, negative, destination);
          private_f_conversion_digit_to_string_pad(data, f_string_ascii_0_s[0], data.width - used, destination);
          private_f_conversion_digit_to_string_number(data, number, digits, destination);
        }
        else {
          private_f_conversion_digit_to_string_pad(data, f_string_ascii_space_s[0], data.width - used, destination);
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

        destination->string[destination->used++] = f_string_ascii_0_s[0];
      }
    }
    else {
      const int used = digits + (data.flag & (f_conversion_data_flag_sign_always | f_conversion_data_flag_sign_pad) ? 1 : 0);

      if (data.width > used) {
        if (data.flag & f_conversion_data_flag_zeros_leading) {
          private_f_conversion_digit_to_string_prefix(data, negative, destination);
          private_f_conversion_digit_to_string_pad(data, f_string_ascii_0_s[0], data.width - used, destination);
          private_f_conversion_digit_to_string_number(data, number, digits, destination);
        }
        else {
          private_f_conversion_digit_to_string_pad(data, f_string_ascii_space_s[0], data.width - used, destination);
          private_f_conversion_digit_to_string_prefix(data, negative, destination);
          private_f_conversion_digit_to_string_number(data, number, digits, destination);
        }
      }
      else if (number) {
        private_f_conversion_digit_to_string_prefix(data, negative, destination);
        private_f_conversion_digit_to_string_number(data, number, digits, destination);
      }
      else if (data.width) {
        destination->string[destination->used++] = f_string_ascii_0_s[0];
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  void private_f_conversion_digit_to_string_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, f_string_dynamic_t *destination) {

    f_number_unsigned_t power = 1;

    for (register uint8_t i = 1; i < digits; ++i) {
      power *= data.base;
    } // for

    if (data.base == 2) {
      f_number_unsigned_t work = 0x1 << (digits - 1);

      while (digits--) {

        destination->string[destination->used++] = (work & number) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[1];
        work >>= 1;
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
        if (data.flag & f_conversion_data_flag_base_upper) {
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
  void private_f_conversion_digit_to_string_pad(const f_conversion_data_t data, const char pad, int total, f_string_dynamic_t *destination) {

    for (; total; --total) {
      destination->string[destination->used++] = pad;
    } // for
  }
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  void private_f_conversion_digit_to_string_prefix(const f_conversion_data_t data, const uint8_t negative, f_string_dynamic_t *destination) {

    if (negative) {
      if (negative == 1) {
        destination->string[destination->used++] = f_string_ascii_minus_s[0];
      }
    }
    else if (data.flag & f_conversion_data_flag_sign_always) {
      destination->string[destination->used++] = f_string_ascii_plus_s[0];
    }
    else if (data.flag & f_conversion_data_flag_sign_pad) {
      destination->string[destination->used++] = f_string_ascii_space_s[0];
    }

    if (data.flag & f_conversion_data_flag_base_prepend) {
      destination->string[destination->used++] = f_string_ascii_0_s[0];

      char c = 0;

      switch (data.base) {
        case 2:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_B_s[0] : f_string_ascii_b_s[0];
          break;

        case 8:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_O_s[0] : f_string_ascii_o_s[0];
          break;

        case 10:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_T_s[0] : f_string_ascii_t_s[0];
          break;

        case 12:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_D_s[0] : f_string_ascii_d_s[0];
          break;

        case 16:
          c = data.flag & f_conversion_data_flag_base_upper ? f_string_ascii_X_s[0] : f_string_ascii_x_s[0];
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

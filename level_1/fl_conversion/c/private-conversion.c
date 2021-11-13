#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_number_unsigned_)
  f_status_t private_fl_conversion_string_to_binary_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_binary(string[i], &digit) == F_none) {
        if (digits) {
          ++digits;

          if (negative) {
            if (digits > F_conversion_digits_binary_signed_d) {
              return F_status_set_error(F_number_underflow);
            }

            converted <<= 1;
            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_binary_signed_d) {
              return F_status_set_error(F_number_overflow);
            }

            converted <<= 1;
            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (negative) {
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_binary_signed_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_binary_unsigned_)
  f_status_t private_fl_conversion_string_to_binary_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_binary(string[i], &digit) == F_none) {
        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_binary_unsigned_d) {
            return F_status_set_error(F_number_overflow);
          }

          converted <<= 1;
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_binary_unsigned_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_decimal_signed_)
  f_status_t private_fl_conversion_string_to_decimal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_decimal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (negative) {
            if (digits > F_conversion_digits_decimal_signed_d) {
              if ((converted * 10) - digit < F_number_t_size_negative_d || (converted * 10) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted *= 10;
            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_decimal_signed_d) {
              if ((converted * 10) + digit > F_number_t_size_positive_d || (converted * 10) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted *= 10;
            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (negative) {
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_decimal_signed_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_decimal_unsigned_)
  f_status_t private_fl_conversion_string_to_decimal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_decimal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_decimal_unsigned_d) {
            if ((converted * 10) + digit > F_number_t_size_unsigned_d || (converted * 10) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted *= 10;
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_decimal_unsigned_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_duodecimal_signed_)
  f_status_t private_fl_conversion_string_to_duodecimal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_duodecimal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (negative) {
            if (digits > F_conversion_digits_duodecimal_signed_d) {
              if ((converted * 12) - digit < F_number_t_size_negative_d || (converted * 12) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted *= 12;
            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_duodecimal_signed_d) {
              if ((converted * 12) + digit > F_number_t_size_positive_d || (converted * 12) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted *= 12;
            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (negative) {
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_duodecimal_signed_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_duodecimal_unsigned_)
  f_status_t private_fl_conversion_string_to_duodecimal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_duodecimal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_duodecimal_unsigned_d) {
            if ((converted * 12) + digit > F_number_t_size_unsigned_d || (converted * 12) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted *= 12;
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_duodecimal_unsigned_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_hexidecimal_signed_)
  f_status_t private_fl_conversion_string_to_hexidecimal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_hexidecimal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (negative) {
            if (digits > F_conversion_digits_hexidecimal_signed_d) {
              if ((converted << 4) - digit < F_number_t_size_negative_d || (converted << 4) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted <<= 4;
            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_hexidecimal_signed_d) {
              if ((converted << 4) + digit > F_number_t_size_positive_d || (converted << 4) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted <<= 4;
            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (negative) {
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_hexidecimal_signed_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_hexidecimal_unsigned_)
  f_status_t private_fl_conversion_string_to_hexidecimal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_hexidecimal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_hexidecimal_unsigned_d) {
            if ((converted << 4) + digit > F_number_t_size_unsigned_d || (converted << 4) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted <<= 4;
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_hexidecimal_unsigned_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_octal_signed_)
  f_status_t private_fl_conversion_string_to_octal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_octal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (negative) {
            if (digits > F_conversion_digits_octal_signed_d) {
              if ((converted << 3) - digit < F_number_t_size_negative_d || (converted << 3) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted <<= 3;
            converted -= digit;
          }
          else {
            if (digits > F_conversion_digits_octal_signed_d) {
              if ((converted << 3) + digit > F_number_t_size_positive_d || (converted << 3) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted <<= 3;
            converted += digit;
          }
        }
        else if (digit) {
          digits = 1;

          if (negative) {
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_octal_signed_)

#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_octal_unsigned_)
  f_status_t private_fl_conversion_string_to_octal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number) {

    if (!string[0]) {
      return F_data_not;
    }

    uint8_t digits = 0;
    uint8_t digit = 0;
    f_number_unsigned_t converted = 0;

    for (f_array_length_t i = range.start; i <= range.stop; ++i) {

      if (string[i] == 0x2e) {
        return F_status_set_error(F_number_decimal);
      }

      if (f_conversion_character_to_octal(string[i], &digit) == F_none) {

        if (digits) {
          ++digits;

          if (digits > F_conversion_digits_octal_unsigned_d) {
            if ((converted << 3) + digit > F_number_t_size_unsigned_d || (converted << 3) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted <<= 3;
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
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !defined(_di_fl_conversion_string_to_octal_unsigned_)

#ifdef __cplusplus
} // extern "C"
#endif

#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_conversion_character_is_binary_
  f_return_status f_conversion_character_is_binary(const int8_t character) {

    if (character == 0x30 || character == 0x31) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_binary_

#ifndef _di_f_conversion_character_is_decimal_
  f_return_status f_conversion_character_is_decimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_decimal_

#ifndef _di_f_conversion_character_is_duodecimal_
  f_return_status f_conversion_character_is_duodecimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return F_true;
    }

    if (character == 0x41 || character == 0x42) {
      return F_true;
    }

    if (character == 0x61 || character == 0x62) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_duodecimal_

#ifndef _di_f_conversion_character_is_hexidecimal_
  f_return_status f_conversion_character_is_hexidecimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return F_true;
    }
    else if (character > 0x40 && character < 0x47) {
      return F_true;
    }
    else if (character > 0x60 && character < 0x67) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_hexidecimal_

#ifndef _di_f_conversion_character_is_octal_
  f_return_status f_conversion_character_is_octal(const int8_t character) {

    if (character > 0x29 && character < 0x38) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_octal_

#ifndef _di_f_conversion_character_to_binary_
  f_return_status f_conversion_character_to_binary(const int8_t character, f_number_unsigned *number) {
    #ifndef _di_level_0_parameter_checking_
      if (number == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *number = 0; break;
      case 0x31: *number = 1; break;
      default:
        return F_status_set_error(F_number);
    }

    return F_none;
  }
#endif // _di_f_conversion_character_to_binary_

#ifndef _di_f_conversion_character_to_decimal_
  f_return_status f_conversion_character_to_decimal(const int8_t character, f_number_unsigned *number) {
    #ifndef _di_level_0_parameter_checking_
      if (number == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *number = 0; break;
      case 0x31: *number = 1; break;
      case 0x32: *number = 2; break;
      case 0x33: *number = 3; break;
      case 0x34: *number = 4; break;
      case 0x35: *number = 5; break;
      case 0x36: *number = 6; break;
      case 0x37: *number = 7; break;
      case 0x38: *number = 8; break;
      case 0x39: *number = 9; break;
      default:
        return F_status_set_error(F_number);
    }

    return F_none;
  }
#endif // _di_f_conversion_character_to_decimal_

#ifndef _di_f_conversion_character_to_duodecimal_
  f_return_status f_conversion_character_to_duodecimal(const int8_t character, f_number_unsigned *decimal) {
    #ifndef _di_level_0_parameter_checking_
      if (decimal == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *decimal = 0; break;
      case 0x31: *decimal = 1; break;
      case 0x32: *decimal = 2; break;
      case 0x33: *decimal = 3; break;
      case 0x34: *decimal = 4; break;
      case 0x35: *decimal = 5; break;
      case 0x36: *decimal = 6; break;
      case 0x37: *decimal = 7; break;
      case 0x38: *decimal = 8; break;
      case 0x39: *decimal = 9; break;
      case 0x41: *decimal = 10; break;
      case 0x42: *decimal = 11; break;
      case 0x61: *decimal = 10; break;
      case 0x62: *decimal = 11; break;
      default:
        return F_status_set_error(F_number);
    }

    return F_none;
  }
#endif // _di_f_conversion_character_to_duodecimal_

#ifndef _di_f_conversion_character_to_hexidecimal_
  f_return_status f_conversion_character_to_hexidecimal(const int8_t character, f_number_unsigned *decimal) {
    #ifndef _di_level_0_parameter_checking_
      if (decimal == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *decimal = 0; break;
      case 0x31: *decimal = 1; break;
      case 0x32: *decimal = 2; break;
      case 0x33: *decimal = 3; break;
      case 0x34: *decimal = 4; break;
      case 0x35: *decimal = 5; break;
      case 0x36: *decimal = 6; break;
      case 0x37: *decimal = 7; break;
      case 0x38: *decimal = 8; break;
      case 0x39: *decimal = 9; break;
      case 0x41: *decimal = 10; break;
      case 0x42: *decimal = 11; break;
      case 0x43: *decimal = 12; break;
      case 0x44: *decimal = 13; break;
      case 0x45: *decimal = 14; break;
      case 0x46: *decimal = 15; break;
      case 0x61: *decimal = 10; break;
      case 0x62: *decimal = 11; break;
      case 0x63: *decimal = 12; break;
      case 0x64: *decimal = 13; break;
      case 0x65: *decimal = 14; break;
      case 0x66: *decimal = 15; break;
      default:
        return F_status_set_error(F_number);
    }

    return F_none;
  }
#endif // _di_f_conversion_character_to_hexidecimal_

#ifndef _di_f_conversion_character_to_octal_
  f_return_status f_conversion_character_to_octal(const int8_t character, f_number_unsigned *number) {
    #ifndef _di_level_0_parameter_checking_
      if (number == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *number = 0; break;
      case 0x31: *number = 1; break;
      case 0x32: *number = 2; break;
      case 0x33: *number = 3; break;
      case 0x34: *number = 4; break;
      case 0x35: *number = 5; break;
      case 0x36: *number = 6; break;
      case 0x37: *number = 7; break;
      default:
        return F_status_set_error(F_number);
    }

    return F_none;
  }
#endif // _di_f_conversion_character_to_octal_

#ifndef _di_f_conversion_string_to_binary_signed_
  f_return_status f_conversion_string_to_binary_signed(const f_string string, f_number_signed *number, const f_string_range range, const bool negative) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_binary(string[i], &digit) == F_none) {
        if (scale) {
          scale++;

          if (negative) {
            if (scale > f_conversion_scale_binary_signed) {
              return F_status_set_error(F_number_underflow);
            }

            converted <<= 1;
            converted -= digit;
          }
          else {
            if (scale > f_conversion_scale_binary_signed) {
              return F_status_set_error(F_number_overflow);
            }

            converted <<= 1;
            converted += digit;
          }
        }
        else if (digit != 0) {
          scale = 1;

          if (negative) {
            converted = 0 - digit;
          }
          else {
            converted = digit;
          }
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_binary_signed_

#ifndef _di_f_conversion_string_to_binary_unsigned_
  f_return_status f_conversion_string_to_binary_unsigned(const f_string string, f_number_unsigned *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_binary(string[i], &digit) == F_none) {
        if (scale) {
          scale++;

          if (scale > f_conversion_scale_binary_unsigned) {
            return F_status_set_error(F_number_overflow);
          }

          converted <<= 1;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_binary_unsigned_

#ifndef _di_f_conversion_string_to_decimal_signed_
  f_return_status f_conversion_string_to_decimal_signed(const f_string string, f_number_signed *number, const f_string_range range, const bool negative) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_decimal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (negative) {
            if (scale > f_conversion_scale_decimal_signed) {
              if ((converted * 10) - digit < f_type_number_size_negative || (converted * 10) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted *= 10;
            converted -= digit;
          }
          else {
            if (scale > f_conversion_scale_decimal_signed) {
              if ((converted * 10) + digit > f_type_number_size_positive || (converted * 10) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted *= 10;
            converted += digit;
          }
        }
        else if (digit != 0) {
          scale = 1;

          if (negative) {
            converted = 0 - digit;
          }
          else {
            converted = digit;
          }
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_decimal_signed_

#ifndef _di_f_conversion_string_to_decimal_unsigned_
  f_return_status f_conversion_string_to_decimal_unsigned(const f_string string, f_number_unsigned *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_decimal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (scale > f_conversion_scale_decimal_unsigned) {
            if ((converted * 10) + digit > f_type_number_size_unsigned || (converted * 10) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted *= 10;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_decimal_unsigned_

#ifndef _di_f_conversion_string_to_duodecimal_signed_
  f_return_status f_conversion_string_to_duodecimal_signed(const f_string string, f_number_signed *number, const f_string_range range, const bool negative) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_duodecimal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (negative) {
            if (scale > f_conversion_scale_duodecimal_signed) {
              if ((converted * 12) - digit < f_type_number_size_negative || (converted * 12) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted *= 12;
            converted -= digit;
          }
          else {
            if (scale > f_conversion_scale_duodecimal_signed) {
              if ((converted * 12) + digit > f_type_number_size_positive || (converted * 12) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted *= 12;
            converted += digit;
          }
        }
        else if (digit != 0) {
          scale = 1;

          if (negative) {
            converted = 0 - digit;
          }
          else {
            converted = digit;
          }
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_duodecimal_signed_

#ifndef _di_f_conversion_string_to_duodecimal_unsigned_
  f_return_status f_conversion_string_to_duodecimal_unsigned(const f_string string, f_number_unsigned *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_duodecimal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (scale > f_conversion_scale_duodecimal_unsigned) {
            if ((converted * 12) + digit > f_type_number_size_unsigned || (converted * 12) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted *= 12;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_duodecimal_unsigned_

#ifndef _di_f_conversion_string_to_hexidecimal_signed_
  f_return_status f_conversion_string_to_hexidecimal_signed(const f_string string, f_number_signed *number, const f_string_range range, const bool negative) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_hexidecimal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (negative) {
            if (scale > f_conversion_scale_hexidecimal_signed) {
              if ((converted << 4) - digit < f_type_number_size_negative || (converted << 4) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted <<= 4;
            converted -= digit;
          }
          else {
            if (scale > f_conversion_scale_hexidecimal_signed) {
              if ((converted << 4) + digit > f_type_number_size_positive || (converted << 4) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted <<= 4;
            converted += digit;
          }
        }
        else if (digit != 0) {
          scale = 1;

          if (negative) {
            converted = 0 - digit;
          }
          else {
            converted = digit;
          }
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_hexidecimal_signed_

#ifndef _di_f_conversion_string_to_hexidecimal_unsigned_
  f_return_status f_conversion_string_to_hexidecimal_unsigned(const f_string string, f_number_unsigned *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_hexidecimal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (scale > f_conversion_scale_hexidecimal_unsigned) {
            if ((converted << 4) + digit > f_type_number_size_unsigned || (converted << 4) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted <<= 4;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_hexidecimal_unsigned_

#ifndef _di_f_conversion_string_to_octal_signed_
  f_return_status f_conversion_string_to_octal_signed(const f_string string, f_number_signed *number, const f_string_range range, const bool negative) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_octal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (negative) {
            if (scale > f_conversion_scale_octal_signed) {
              if ((converted << 3) - digit < f_type_number_size_negative || (converted << 3) - digit > converted) {
                return F_status_set_error(F_number_underflow);
              }
            }

            converted <<= 3;
            converted -= digit;
          }
          else {
            if (scale > f_conversion_scale_octal_signed) {
              if ((converted << 3) + digit > f_type_number_size_positive || (converted << 3) + digit < converted) {
                return F_status_set_error(F_number_overflow);
              }
            }

            converted <<= 3;
            converted += digit;
          }
        }
        else if (digit != 0) {
          scale = 1;

          if (negative) {
            converted = 0 - digit;
          }
          else {
            converted = digit;
          }
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_octal_signed_

#ifndef _di_f_conversion_string_to_octal_unsigned_
  f_return_status f_conversion_string_to_octal_unsigned(const f_string string, f_number_unsigned *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t scale = 0;
    f_number_unsigned digit = 0;
    f_number_unsigned converted = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      if (f_conversion_character_to_octal(string[i], &digit) == F_none) {

        if (scale) {
          scale++;

          if (scale > f_conversion_scale_octal_unsigned) {
            if ((converted << 3) + digit > f_type_number_size_unsigned || (converted << 3) + digit < converted) {
              return F_status_set_error(F_number_overflow);
            }
          }

          converted <<= 3;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else if (string[i] != 0) {
        return F_status_set_error(F_number);
      }
    } // for

    *number = converted;
    return F_none;
  }
#endif // _di_f_conversion_string_to_octal_unsigned_

#ifndef _di_f_conversion_string_to_number_signed_
  f_return_status f_conversion_string_to_number_signed(const f_string string, f_number_signed *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t width = 0;
    uint8_t width_max = 0;
    uint8_t mode = 0;
    int8_t vector = 0; // 0 for assumed positive, 1 for explicit positive, -1 for negative.
    f_string_length j = 0;
    f_string_length offset = 0;
    f_status status = F_none;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      width = f_macro_utf_byte_width_is(string[i]);

      if (width == 0) {
        if (isspace(string[i])) {
          if (mode == 0 && vector == 0) {
            offset++;
            continue;
          }

          return F_status_set_error(F_number);
        }
      }
      else {
        if (mode == 0 && vector == 0) {
          width_max = (range.stop - i) + 1;

          status = f_utf_is_whitespace(string + i, width_max);

          if (status == F_true) {
            offset = i + 1;
            continue;
          }

          if (F_status_is_error(status)) {
            if (status == F_status_set_error(F_maybe)) {
              status = F_status_set_error(F_incomplete_utf);
            }

            return status;
          }
        }

        return F_status_set_error(F_number);
      }

      if (string[i] == 0x30) {
        j = i + 1;

        // Immediate next value must be either a number, 'x', 'X', 'd', 'D', 'o', 'O', 'b', or 'B'.
        if (j > range.stop) {
          *number = 0;
          return F_none;
        }
        else if (string[j] > 0x29 && string[j] < 0x3a) {
          mode = 10;
        }
        else if (string[j] == 0x78 || string[j] == 0x58) {
          mode = 16;
          offset += 2;
        }
        else if (string[j] == 0x44 || string[j] == 0x64) {
          mode = 12;
          offset += 2;
        }
        else if (string[j] == 0x6f || string[j] == 0x4f) {
          mode = 8;
          offset += 2;
        }
        else if (string[j] == 0x62 || string[j] == 0x42) {
          mode = 2;
          offset += 2;
        }
        else {
          return F_status_set_error(F_number);
        }

        break;
      }

      // plus sign is only allowed as the first non-whitespace character.
      if (string[i] == 0x2b) {
        if (mode == 0 && vector == 0) {
          vector = 1;
          offset++;
        }
        else {
          return F_status_set_error(F_number);
        }
      }

      // negative sign is not allowed.
      if (string[i] == 0x2d) {
        if (mode == 0 && vector == 0) {
          vector = -1;
          offset++;
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

    if (mode == 0) {
      return F_status_set_error(F_number);
    }

    f_string_range location_offset = f_string_range_initialize;
    location_offset.start = range.start + offset;
    location_offset.stop = range.stop;

    if (mode == 10) {
      return f_conversion_string_to_decimal_signed(string, number, location_offset, vector == -1);
    }

    if (mode == 16) {
      return f_conversion_string_to_hexidecimal_signed(string, number, location_offset, vector == -1);
    }

    if (mode == 12) {
      return f_conversion_string_to_duodecimal_signed(string, number, location_offset, vector == -1);
    }

    if (mode == 8) {
      return f_conversion_string_to_octal_signed(string, number, location_offset, vector == -1);
    }

    return f_conversion_string_to_binary_signed(string, number, location_offset, vector == -1);
  }
#endif // _di_f_conversion_string_to_number_signed_

#ifndef _di_f_conversion_string_to_number_unsigned_
  f_return_status f_conversion_string_to_number_unsigned(const f_string string, f_number_unsigned *number, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (number == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string[0] == 0) {
      return F_data_not;
    }

    uint8_t width = 0;
    uint8_t width_max = 0;
    uint8_t mode = 0;
    f_string_length j = 0;
    f_string_length offset = 0;
    f_status status = F_none;
    int8_t sign_found = 0;

    for (f_string_length i = range.start; i <= range.stop; i++) {
      width = f_macro_utf_byte_width_is(string[i]);

      if (width == 0) {
        if (isspace(string[i])) {
          if (mode == 0) {
            offset++;
            continue;
          }

          return F_status_set_error(F_number);
        }
      }
      else {
        if (mode == 0) {
          width_max = (range.stop - i) + 1;

          status = f_utf_is_whitespace(string + i, width_max);

          if (status == F_true) {
            offset = i + 1;
            continue;
          }

          if (F_status_is_error(status)) {
            if (status == F_status_set_error(F_maybe)) {
              status = F_status_set_error(F_incomplete_utf);
            }

            return status;
          }
        }

        return F_status_set_error(F_number);
      }

      if (string[i] == 0x30) {
        j = i + 1;

        // Immediate next value must be either a number, 'x', 'X', 'd', 'D', 'o', 'O', 'b', or 'B'.
        if (j > range.stop) {
          *number = 0;
          return F_none;
        }
        else if (string[j] > 0x29 && string[j] < 0x3a) {
          mode = 10;
        }
        else if (string[j] == 0x78 || string[j] == 0x58) {
          mode = 16;
          offset += 2;
        }
        else if (string[j] == 0x44 || string[j] == 0x64) {
          mode = 12;
          offset += 2;
        }
        else if (string[j] == 0x6f || string[j] == 0x4f) {
          mode = 8;
          offset += 2;
        }
        else if (string[j] == 0x62 || string[j] == 0x42) {
          mode = 2;
          offset += 2;
        }
        else {
          return F_status_set_error(F_number);
        }

        break;
      }

      if (string[i] == 0x2b) {
        offset++;
        sign_found = 1;
      }

      if (string[i] == 0x2d) {
        offset++;
        sign_found = -1;
      }

      if (f_conversion_character_is_decimal(string[i]) == F_true) {
        mode = 10;
        break;
      }

      return F_status_set_error(F_number);
    } // for

    if (mode == 0) {
      return F_status_set_error(F_number);
    }

    f_string_range location_offset = f_string_range_initialize;
    location_offset.start = range.start + offset;
    location_offset.stop = range.stop;

    if (mode == 10) {
      status = f_conversion_string_to_decimal_unsigned(string, number, location_offset);
    }
    else if (mode == 16) {
      status = f_conversion_string_to_hexidecimal_unsigned(string, number, location_offset);
    }
    else if (mode == 12) {
      status = f_conversion_string_to_duodecimal_unsigned(string, number, location_offset);
    }
    else if (mode == 8) {
      status = f_conversion_string_to_octal_unsigned(string, number, location_offset);
    }
    else {
      status = f_conversion_string_to_binary_unsigned(string, number, location_offset);
    }

    // +/- signs are not allowed.
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
#endif // _di_f_conversion_string_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif

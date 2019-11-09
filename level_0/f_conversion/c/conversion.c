#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_conversion_character_is_binary_
  f_return_status f_conversion_character_is_binary(const int8_t character) {

    if (character == 0x30 || character == 0x31) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_conversion_character_is_binary_

#ifndef _di_f_conversion_character_is_decimal_
  f_return_status f_conversion_character_is_decimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_conversion_character_is_decimal_

#ifndef _di_f_conversion_character_is_hexidecimal_
  f_return_status f_conversion_character_is_hexidecimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return f_true;
    }
    else if (character > 0x40 && character < 0x47) {
      return f_true;
    }
    else if (character > 0x60 && character < 0x67) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_conversion_character_is_hexidecimal_

#ifndef _di_f_conversion_character_is_octal_
  f_return_status f_conversion_character_is_octal(const int8_t character) {

    if (character > 0x29 && character < 0x38) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_conversion_character_is_octal_

#ifndef _di_f_conversion_character_to_binary_
  f_return_status f_conversion_character_to_binary(const int8_t character, uint64_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (number == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *number = 0; break;
      case 0x31: *number = 1; break;
      default:
        return f_status_set_error(f_invalid_number);
    }

    return f_none;
  }
#endif // _di_f_conversion_character_to_binary_

#ifndef _di_f_conversion_character_to_decimal_
  f_return_status f_conversion_character_to_decimal(const int8_t character, uint64_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (number == 0) return f_status_set_error(f_invalid_parameter);
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
        return f_status_set_error(f_invalid_number);
    }

    return f_none;
  }
#endif // _di_f_conversion_character_to_decimal_

#ifndef _di_f_conversion_character_to_hexidecimal_
  f_return_status f_conversion_character_to_hexidecimal(const int8_t character, uint64_t *decimal) {
    #ifndef _di_level_0_parameter_checking_
      if (decimal == 0) return f_status_set_error(f_invalid_parameter);
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
        return f_status_set_error(f_invalid_number);
    }

    return f_none;
  }
#endif // _di_f_conversion_character_to_hexidecimal_

#ifndef _di_f_conversion_character_to_octal_
  f_return_status f_conversion_character_to_octal(const int8_t character, uint64_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (number == 0) return f_status_set_error(f_invalid_parameter);
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
        return f_status_set_error(f_invalid_number);
    }

    return f_none;
  }
#endif // _di_f_conversion_character_to_octal_

#ifndef _di_f_conversion_string_to_binary_unsigned_
  f_return_status f_conversion_string_to_binary_unsigned(const f_string string, uint64_t *number, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
      if (number == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    bool scale = 0;
    uint64_t digit = 0;
    uint64_t converted = 0;

    // @todo: needs overflow/underflow detection.
    for (f_string_length i = location.start; i <= location.stop; i++) {
      if (f_conversion_character_to_binary(string[i], &digit) == f_none) {
        if (scale) {
          converted <<= 1;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else {
        return f_status_set_error(f_invalid_number);
      }
    } // for

    *number = converted;
    return f_none;
  }
#endif // _di_f_conversion_string_to_binary_unsigned_

#ifndef _di_f_conversion_string_to_decimal_unsigned_
  f_return_status f_conversion_string_to_decimal_unsigned(const f_string string, uint64_t *number, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
      if (number == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    bool scale = 0;
    uint64_t digit = 0;
    uint64_t converted = 0;

    // @todo: needs overflow/underflow detection.
    for (f_string_length i = location.start; i <= location.stop; i++) {
      if (f_conversion_character_to_decimal(string[i], &digit) == f_none) {

        if (scale) {
          converted *= 10;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else {
        return f_status_set_error(f_invalid_number);
      }
    } // for

    *number = converted;
    return f_none;
  }
#endif // _di_f_conversion_string_to_decimal_unsigned_

#ifndef _di_f_conversion_string_to_hexidecimal_unsigned_
  f_return_status f_conversion_string_to_hexidecimal_unsigned(const f_string string, uint64_t *number, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
      if (number == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    bool scale = 0;
    uint64_t digit = 0;
    uint64_t converted = 0;

    // @todo: needs overflow/underflow detection.
    for (f_string_length i = location.start; i <= location.stop; i++) {
      if (f_conversion_character_to_hexidecimal(string[i], &digit) == f_none) {

        if (scale) {
          converted <<= 4;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else {
        return f_status_set_error(f_invalid_number);
      }
    } // for

    *number = converted;
    return f_none;
  }
#endif // _di_f_conversion_string_to_hexidecimal_unsigned_

#ifndef _di_f_conversion_string_to_octal_unsigned_
  f_return_status f_conversion_string_to_octal_unsigned(const f_string string, uint64_t *number, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
      if (number == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    bool scale = 0;
    uint64_t digit = 0;
    uint64_t converted = 0;

    // @todo: needs overflow/underflow detection.
    for (f_string_length i = location.start; i <= location.stop; i++) {
      if (f_conversion_character_to_octal(string[i], &digit) == f_none) {

        // when the scale exists, then we need to make the number larger, for this function the scale is base 8.
        if (scale) {
          converted *= 8;
          converted += digit;
        }
        else if (digit != 0) {
          scale = 1;
          converted = digit;
        }
      }
      else {
        return f_status_set_error(f_invalid_number);
      }
    } // for

    *number = converted;
    return f_none;
  }
#endif // _di_f_conversion_string_to_octal_unsigned_

#ifndef _di_f_conversion_string_to_number_unsigned_
  f_return_status f_conversion_string_to_number_unsigned(const f_string string, uint64_t *number, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
      if (number == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    bool scale = 0;
    uint64_t digit = 0;
    uint64_t converted = 0;
    uint8_t width = 0;
    uint8_t width_max = 0;
    uint8_t mode = 0;
    f_string_length j = 0;
    f_string_length offset = 0;
    f_status status = f_none;

    for (f_string_length i = location.start; i <= location.stop; i++) {
      width = f_macro_utf_byte_width_is(string[i]);

      if (width == 0) {
        if (isspace(string[i])) {
          if (mode == 0) {
            offset++;
            continue;
          }

          return f_status_set_error(f_invalid_number);
        }
      }
      else {
        if (mode == 0) {
          width_max = (location.stop - i) + 1;

          status = f_utf_is_whitespace(string + i, width_max);

          if (status == f_true) {
            offset = i + 1;
            continue;
          }

          if (f_status_is_error(status)) {
            if (status == f_status_set_error(f_maybe)) {
              status = f_status_set_error(f_incomplete_utf);
            }

            return status;
          }
        }

        return f_status_set_error(f_invalid_number);
      }

      if (string[i] == 0x30) {
        j = i + 1;

        // immediate next value must be either '0', 'x', 'X', 'o', 'O', 'b', or 'B'.
        if (j > location.stop) {
          *number = 0;
          return f_none;
        }
        else if (string[j] == 0x30) {
          mode = 10;
        }
        else if (string[j] == 0x78 || string[j] == 0x58) {
          mode = 16;
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
          return f_status_set_error(f_invalid_number);
        }

        break;
      }

      // plus sign is not allowed.
      if (string[i] == 0x2b) {
        return f_status_set_error(f_invalid_number);
      }

      // negative sign is not allowed.
      if (string[i] == 0x2d) {
        return f_status_set_error(f_negative_number);
      }

      if (f_conversion_character_is_decimal(string[i]) == f_true) {
        mode = 10;
        break;
      }

      return f_status_set_error(f_negative_number);
    } // for

    if (mode == 0) {
      return f_no_data;
    }

    f_string_location location_offset = f_string_location_initialize;
    location_offset.start = location.start + offset;
    location_offset.stop = location.stop;

    if (mode == 10) {
      return f_conversion_string_to_decimal_unsigned(string, number, location_offset);
    }

    if (mode == 16) {
      return f_conversion_string_to_hexidecimal_unsigned(string, number, location_offset);
    }

    if (mode == 8) {
      return f_conversion_string_to_octal_unsigned(string, number, location_offset);
    }

    return f_conversion_string_to_binary_unsigned(string, number, location_offset);
  }
#endif // _di_f_conversion_string_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif

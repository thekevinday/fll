#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_is_decimal_
  f_return_status f_is_decimal(const char character) {

    if (character > 0x29 && character < 0x40) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_is_decimal_

#ifndef _di_f_is_hexidecimal_
  f_return_status f_is_hexidecimal(const char character) {

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
#endif // _di_f_is_hexidecimal_

#ifndef _di_f_character_to_digit_
  f_return_status f_character_to_digit(const char character, unsigned long *digit) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *digit = 0; break;
      case 0x31: *digit = 1; break;
      case 0x32: *digit = 2; break;
      case 0x33: *digit = 3; break;
      case 0x34: *digit = 4; break;
      case 0x35: *digit = 5; break;
      case 0x36: *digit = 6; break;
      case 0x37: *digit = 7; break;
      case 0x38: *digit = 8; break;
      case 0x39: *digit = 9; break;
      default:
        return f_no_data;
    }

    return f_none;
  }
#endif // _di_f_character_to_digit_

#ifndef _di_f_character_to_hexdecimal_
  f_return_status f_character_to_hexdecimal(const char character, unsigned long *digit) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case 0x30: *digit = 0; break;
      case 0x31: *digit = 1; break;
      case 0x32: *digit = 2; break;
      case 0x33: *digit = 3; break;
      case 0x34: *digit = 4; break;
      case 0x35: *digit = 5; break;
      case 0x36: *digit = 6; break;
      case 0x37: *digit = 7; break;
      case 0x38: *digit = 8; break;
      case 0x39: *digit = 9; break;
      case 0x41: *digit = 10; break;
      case 0x42: *digit = 11; break;
      case 0x43: *digit = 12; break;
      case 0x44: *digit = 13; break;
      case 0x45: *digit = 14; break;
      case 0x46: *digit = 15; break;
      case 0x61: *digit = 10; break;
      case 0x62: *digit = 11; break;
      case 0x63: *digit = 12; break;
      case 0x64: *digit = 13; break;
      case 0x65: *digit = 14; break;
      case 0x66: *digit = 15; break;
      default:
        return f_no_data;
    }

    return f_none;
  }
#endif // _di_f_character_to_hexdecimal_

#ifndef _di_f_string_to_decimal_
  f_return_status f_string_to_decimal(const f_string string, unsigned long *digit, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop <= location.start) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length current_location = location.start;
    unsigned long scale = 0;
    unsigned long temp_digit = 0;

    while (current_location < location.stop) {
      if (f_character_to_digit(string[current_location], &temp_digit) == f_none) {

        // when the scale exists, then we need to make the number larger, for this function the scale is base 10
        if (scale > 0) {
          *digit = 10 * *digit;
          *digit += temp_digit;
        }
        else {
          scale = 1;
          *digit = temp_digit;
        }
      }
      else {
        break;
      }

      ++current_location;
    } // while

    return f_none;
  }
#endif // _di_f_string_to_decimal_

#ifndef _di_f_string_to_hexidecimal_
  f_return_status f_string_to_hexidecimal(const f_string string, unsigned long *digit, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop <= location.start) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length current_location = location.start;
    unsigned long scale = 0;
    unsigned long temp_digit = 0;

    while (current_location < location.stop) {
      if (f_character_to_hexdecimal(string[current_location], &temp_digit) == f_none) {

        // when the scale exists, then we need to make the number larger, for this function the scale is base 16
        if (scale > 0) {
          *digit <<= 4;
          *digit += temp_digit;
        }
        else {
          scale = 1;
          *digit = temp_digit;
        }
      }
      else {
        break;
      }

      ++current_location;
    } // while

    return f_none;
  }
#endif // _di_f_string_to_hexidecimal_

#ifdef __cplusplus
} // extern "C"
#endif

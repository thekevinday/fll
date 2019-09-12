#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_is_decimal_
  f_return_status f_is_decimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_is_decimal_

#ifndef _di_f_is_hexidecimal_
  f_return_status f_is_hexidecimal(const int8_t character) {

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

#ifndef _di_f_character_to_decimal_
  f_return_status f_character_to_decimal(const int8_t character, unsigned long *decimal) {
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
      default:
        return f_no_data;
    }

    return f_none;
  }
#endif // _di_f_character_to_decimal_

#ifndef _di_f_character_to_hexidecimal_
  f_return_status f_character_to_hexidecimal(const int8_t character, unsigned long *decimal) {
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
        return f_no_data;
    }

    return f_none;
  }
#endif // _di_f_character_to_hexidecimal_

#ifndef _di_f_string_to_decimal_
  f_return_status f_string_to_decimal(const f_string string, unsigned long *decimal, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (decimal == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop <= location.start) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length current_location = location.start;
    unsigned long scale = 0;
    unsigned long digit = 0;
    unsigned long decimal_value = 0;

    while (current_location < location.stop) {
      if (f_character_to_decimal(string[current_location], &digit) == f_none) {

        // when the scale exists, then we need to make the number larger, for this function the scale is base 10
        if (scale > 0) {
          decimal_value = 10 * decimal_value;
          decimal_value += digit;
        }
        else {
          scale = 1;
          decimal_value = digit;
        }
      }
      else {
        return f_no_data;
      }

      ++current_location;
    } // while

    *decimal = decimal_value;

    return f_none;
  }
#endif // _di_f_string_to_decimal_

#ifndef _di_f_string_to_hexidecimal_
  f_return_status f_string_to_hexidecimal(const f_string string, unsigned long *decimal, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (decimal == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop <= location.start) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length current_location = location.start;
    unsigned long scale = 0;
    unsigned long digit = 0;
    unsigned long decimal_value = 0;

    while (current_location < location.stop) {
      if (f_character_to_hexidecimal(string[current_location], &digit) == f_none) {

        // when the scale exists, then we need to make the number larger, for this function the scale is base 16.
        if (scale > 0) {
          decimal_value <<= 4;
          decimal_value += digit;
        }
        else {
          scale = 1;
          decimal_value = digit;
        }
      }
      else {
        return f_no_data;
      }

      ++current_location;
    } // while

    *decimal = decimal_value;

    return f_none;
  }
#endif // _di_f_string_to_hexidecimal_

#ifdef __cplusplus
} // extern "C"
#endif

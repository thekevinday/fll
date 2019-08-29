#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_is_digit_
  f_return_status f_is_digit(const char character) {

    // at this point, it seems that it would incur more overhead to use the libc isdigit here, so just use one less call and test it here
    switch (character) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        return f_true;
      default:
        return f_false;
    }

    return f_unknown;
  }
#endif // _di_f_is_digit_

#ifndef _di_f_is_hexdigit_
  f_return_status f_is_hexdigit(const char character) {

    switch (character) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
        return f_true;
      default:
        return f_false;
    }
  }
#endif // _di_f_is_hexdigit_

#ifndef _di_f_character_to_digit_
  f_return_status f_character_to_digit(const char character, f_u_long *digit) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case '0': *digit = 0;  break;
      case '1': *digit = 1;  break;
      case '2': *digit = 2;  break;
      case '3': *digit = 3;  break;
      case '4': *digit = 4;  break;
      case '5': *digit = 5;  break;
      case '6': *digit = 6;  break;
      case '7': *digit = 7;  break;
      case '8': *digit = 8;  break;
      case '9': *digit = 9;  break;
      default:
        return f_no_data;
    }

    return f_none;
  }
#endif // _di_f_character_to_digit_

#ifndef _di_f_character_to_hexdigit_
  f_return_status f_character_to_hexdigit(const char character, f_u_long *digit) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (character) {
      case '0': *digit = 0;  break;
      case '1': *digit = 1;  break;
      case '2': *digit = 2;  break;
      case '3': *digit = 3;  break;
      case '4': *digit = 4;  break;
      case '5': *digit = 5;  break;
      case '6': *digit = 6;  break;
      case '7': *digit = 7;  break;
      case '8': *digit = 8;  break;
      case '9': *digit = 9;  break;
      case 'A': *digit = 10; break;
      case 'B': *digit = 11; break;
      case 'C': *digit = 12; break;
      case 'D': *digit = 13; break;
      case 'E': *digit = 14; break;
      case 'F': *digit = 15; break;
      case 'a': *digit = 10; break;
      case 'b': *digit = 11; break;
      case 'c': *digit = 12; break;
      case 'd': *digit = 13; break;
      case 'e': *digit = 14; break;
      case 'f': *digit = 15; break;
      default:
        return f_no_data;
    }

    return f_none;
  }
#endif // _di_f_character_to_hexdigit_

#ifndef _di_f_string_to_digit_
  f_return_status f_string_to_digit(const f_string string, f_u_long *digit, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop <= location.start) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length current_location = location.start;
    f_u_long scale = 0;
    f_u_long temp_digit = 0;

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
    }

    return f_none;
  }
#endif // _di_f_string_to_digit_

#ifndef _di_f_string_to_hexdigit_
  f_return_status f_string_to_hexdigit(const f_string string, f_u_long *digit, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (digit == 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop <= location.start) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length current_location = location.start;
    f_u_long scale = 0;
    f_u_long temp_digit = 0;

    while (current_location < location.stop) {
      if (f_character_to_hexdigit(string[current_location], &temp_digit) == f_none) {

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
    }

    return f_none;
  }
#endif // _di_f_string_to_hexdigit_

#ifdef __cplusplus
} // extern "C"
#endif

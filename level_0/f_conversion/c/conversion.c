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

#ifdef __cplusplus
} // extern "C"
#endif

#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_conversion_character_is_binary_
  f_status_t f_conversion_character_is_binary(const char character) {

    if (character == 0x30 || character == 0x31) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_binary_

#ifndef _di_f_conversion_character_is_decimal_
  f_status_t f_conversion_character_is_decimal(const char character) {

    if (character > 0x29 && character < 0x40) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_decimal_

#ifndef _di_f_conversion_character_is_duodecimal_
  f_status_t f_conversion_character_is_duodecimal(const char character) {

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
  f_status_t f_conversion_character_is_hexidecimal(const char character) {

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
  f_status_t f_conversion_character_is_octal(const char character) {

    if (character > 0x29 && character < 0x38) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_octal_

#ifndef _di_f_conversion_character_to_binary_
  f_status_t f_conversion_character_to_binary(const char character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
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
  f_status_t f_conversion_character_to_decimal(const char character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (character > 0x29 && character < 0x40) {
      *number = 0xf & character;

      return F_none;
    }

    return F_status_set_error(F_number);
  }
#endif // _di_f_conversion_character_to_decimal_

#ifndef _di_f_conversion_character_to_duodecimal_
  f_status_t f_conversion_character_to_duodecimal(const char character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (character > 0x29 && character < 0x40) {
      *number = 0xf & character;

      return F_none;
    }

    if (character > 0x40 && character < 0x43 || character > 0x60 && character < 0x63) {
      *number = 9 + (0xf & character);

      return F_none;
    }

    return F_status_set_error(F_number);
  }
#endif // _di_f_conversion_character_to_duodecimal_

#ifndef _di_f_conversion_character_to_hexidecimal_
  f_status_t f_conversion_character_to_hexidecimal(const char character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (character > 0x29 && character < 0x40) {
      *number = 0xf & character;

      return F_none;
    }

    if (character > 0x40 && character < 0x47 || character > 0x60 && character < 0x67) {
      *number = 9 + (0xf & character);

      return F_none;
    }

    return F_status_set_error(F_number);
  }
#endif // _di_f_conversion_character_to_hexidecimal_

#ifndef _di_f_conversion_character_to_octal_
  f_status_t f_conversion_character_to_octal(const char character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (character < 0x30 || character > 0x37) {
      return F_status_set_error(F_number);
    }

    *number = 0xf & character;

    return F_none;
  }
#endif // _di_f_conversion_character_to_octal_

#ifndef _di_f_conversion_number_signed_print_
  f_status_t f_conversion_number_signed_print(const f_number_signed_t number, const f_conversion_data_t data, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
      if (data.base < 2 || data.base > 16) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (number < 0) {
      return private_f_conversion_digit_to_file((f_number_unsigned_t) (0 - number), data, 1, output);
    }

    return private_f_conversion_digit_to_file((f_number_unsigned_t) number, data, number ? 0 : 2, output);
  }
#endif // _di_f_conversion_number_signed_print_

#ifndef _di_f_conversion_number_signed_to_string_
  f_status_t f_conversion_number_signed_to_string(const f_number_signed_t number, const f_conversion_data_t data, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (data.base < 2 || data.base > 16) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (number < 0) {
      return private_f_conversion_digit_to_string((f_number_unsigned_t) (0 - number), data, 1, destination);
    }

    return private_f_conversion_digit_to_string((f_number_unsigned_t) number, data, number ? 0 : 2, destination);
  }
#endif // _di_f_conversion_number_signed_to_string_

#ifndef _di_f_conversion_number_unsigned_print_
  f_status_t f_conversion_number_unsigned_print(const f_number_unsigned_t number, const f_conversion_data_t data, FILE *output) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
      if (data.base < 2 || data.base > 16) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_conversion_digit_to_file(number, data, number ? 0 : 2, output);
  }
#endif // _di_f_conversion_number_unsigned_print_

#ifndef _di_f_conversion_number_unsigned_to_string_
  f_status_t f_conversion_number_unsigned_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (data.base < 2 || data.base > 16) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_conversion_digit_to_string(number, data, number ? 0 : 2, destination);
  }
#endif // _di_f_conversion_number_unsigned_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

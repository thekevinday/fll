#include "conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_conversion_character_is_binary_
  f_status_t f_conversion_character_is_binary(const int8_t character) {

    if (character == 0x30 || character == 0x31) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_binary_

#ifndef _di_f_conversion_character_is_decimal_
  f_status_t f_conversion_character_is_decimal(const int8_t character) {

    if (character > 0x29 && character < 0x40) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_decimal_

#ifndef _di_f_conversion_character_is_duodecimal_
  f_status_t f_conversion_character_is_duodecimal(const int8_t character) {

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
  f_status_t f_conversion_character_is_hexidecimal(const int8_t character) {

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
  f_status_t f_conversion_character_is_octal(const int8_t character) {

    if (character > 0x29 && character < 0x38) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_conversion_character_is_octal_

#ifndef _di_f_conversion_character_to_binary_
  f_status_t f_conversion_character_to_binary(const int8_t character, f_number_unsigned_t *number) {
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
  f_status_t f_conversion_character_to_decimal(const int8_t character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
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
  f_status_t f_conversion_character_to_duodecimal(const int8_t character, f_number_unsigned_t *decimal) {
    #ifndef _di_level_0_parameter_checking_
      if (!decimal) return F_status_set_error(F_parameter);
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
  f_status_t f_conversion_character_to_hexidecimal(const int8_t character, f_number_unsigned_t *decimal) {
    #ifndef _di_level_0_parameter_checking_
      if (!decimal) return F_status_set_error(F_parameter);
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
  f_status_t f_conversion_character_to_octal(const int8_t character, f_number_unsigned_t *number) {
    #ifndef _di_level_0_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
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

#ifndef _di_f_conversion_number_signed_to_string_
  f_status_t f_conversion_number_signed_to_string(const f_number_signed_t number, const uint8_t base, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (base < 2 || base > 16) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (!number) {
      f_macro_string_dynamic_t_resize(status, (*destination), destination->used + 2);
      if (F_status_is_error(status)) return status;

      destination->string[destination->used] = '0';
      destination->string[destination->used + 1] = 0;
      destination->used += 2;

      return F_none;
    }

    bool negative = F_false;
    f_number_unsigned_t current = number;

    if (number < 0) {
      current = 0 - number;
      negative = F_true;
    }

    f_string_length_t total = 0;

    for (register f_number_signed_t work = current; work; total++) {
      work /= base;
    } // for

    if (negative) {
      f_macro_string_dynamic_t_resize(status, (*destination), destination->used + total + 2);
    }
    else {
      f_macro_string_dynamic_t_resize(status, (*destination), destination->used + total + 1);
    }

    if (F_status_is_error(status)) return status;

    f_number_unsigned_t work = 0;
    f_number_unsigned_t power = 1;

    if (negative) {
      destination->string[destination->used] = '-';
      destination->used++;
    }

    for (register uint8_t i = 1; i < total; i++) {
      power *= base;
    } // for

    for (; power; total--) {
      work = current / power;
      current -= work * power;
      power /= base;

      switch (work) {
        case 0:
          destination->string[destination->used] = '0';
          break;
        case 1:
          destination->string[destination->used] = '1';
          break;
        case 2:
          destination->string[destination->used] = '2';
          break;
        case 3:
          destination->string[destination->used] = '3';
          break;
        case 4:
          destination->string[destination->used] = '4';
          break;
        case 5:
          destination->string[destination->used] = '5';
          break;
        case 6:
          destination->string[destination->used] = '6';
          break;
        case 7:
          destination->string[destination->used] = '7';
          break;
        case 8:
          destination->string[destination->used] = '8';
          break;
        case 9:
          destination->string[destination->used] = '9';
          break;
        case 10:
          destination->string[destination->used] = 'a';
          break;
        case 11:
          destination->string[destination->used] = 'b';
          break;
        case 12:
          destination->string[destination->used] = 'c';
          break;
        case 13:
          destination->string[destination->used] = 'd';
          break;
        case 14:
          destination->string[destination->used] = 'e';
          break;
        case 15:
          destination->string[destination->used] = 'f';
          break;
      }

      destination->used++;
    } // for

    destination->string[destination->used] = 0;
    destination->used++;

    return F_none;
  }
#endif // _di_f_conversion_decimal_signed_to_string_

#ifndef _di_f_conversion_number_unsigned_to_string_
  f_status_t f_conversion_number_unsigned_to_string(const f_number_unsigned_t number, const uint8_t base, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (base < 2 || base > 16) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (!number) {
      f_macro_string_dynamic_t_resize(status, (*destination), destination->used + 2);
      if (F_status_is_error(status)) return status;

      destination->string[destination->used] = '0';
      destination->string[destination->used + 1] = 0;
      destination->used += 2;

      return F_none;
    }

    f_string_length_t total = 0;

    for (register f_number_unsigned_t work = number; work; total++) {
      work /= base;
    } // for

    f_macro_string_dynamic_t_resize(status, (*destination), destination->used + total + 1);
    if (F_status_is_error(status)) return status;

    f_number_unsigned_t current = number;
    f_number_unsigned_t work = 0;
    f_number_unsigned_t power = 1;

    for (register uint8_t i = 1; i < total; i++) {
      power *= base;
    } // for

    for (; power; total--) {
      work = current / power;
      current -= work * power;
      power /= base;

      switch (work) {
        case 0:
          destination->string[destination->used] = '0';
          break;
        case 1:
          destination->string[destination->used] = '1';
          break;
        case 2:
          destination->string[destination->used] = '2';
          break;
        case 3:
          destination->string[destination->used] = '3';
          break;
        case 4:
          destination->string[destination->used] = '4';
          break;
        case 5:
          destination->string[destination->used] = '5';
          break;
        case 6:
          destination->string[destination->used] = '6';
          break;
        case 7:
          destination->string[destination->used] = '7';
          break;
        case 8:
          destination->string[destination->used] = '8';
          break;
        case 9:
          destination->string[destination->used] = '9';
          break;
        case 10:
          destination->string[destination->used] = 'a';
          break;
        case 11:
          destination->string[destination->used] = 'b';
          break;
        case 12:
          destination->string[destination->used] = 'c';
          break;
        case 13:
          destination->string[destination->used] = 'd';
          break;
        case 14:
          destination->string[destination->used] = 'e';
          break;
        case 15:
          destination->string[destination->used] = 'f';
          break;
      }

      destination->used++;
    } // for

    destination->string[destination->used] = 0;
    destination->used++;

    return F_none;
  }
#endif // _di_f_conversion_decimal_unsigned_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

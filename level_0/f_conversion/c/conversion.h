/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to convert one data type to another, such as a string to an integer.
 */
#ifndef _F_conversion_h
#define _F_conversion_h

// libc includes
#include <ctype.h>
#include <stdlib.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide custom conversion scale limits based on selected type sizes.
 *
 * Utilize the f_type_number_* defines to determine the expected sizes to use for the sxcales.
 *
 * 64-bit is the designed default.
 */
#ifndef _di_f_type_number_64_
  #define f_conversion_scale_binary_unsigned 64
  #define f_conversion_scale_binary_signed   63

  #define f_conversion_scale_octal_unsigned 21
  #define f_conversion_scale_octal_signed   20

  #define f_conversion_scale_decimal_unsigned 19
  #define f_conversion_scale_decimal_signed   18

  #define f_conversion_scale_duodecimal_unsigned 17
  #define f_conversion_scale_duodecimal_signed   17

  #define f_conversion_scale_hexidecimal_unsigned 15
  #define f_conversion_scale_hexidecimal_signed   15
#endif // _di_f_type_number_64_

#ifdef _en_f_type_number_32_
  #define f_conversion_scale_binary_unsigned 32
  #define f_conversion_scale_binary_signed   31

  #define f_conversion_scale_octal_unsigned 10
  #define f_conversion_scale_octal_signed   10

  #define f_conversion_scale_decimal_unsigned 9
  #define f_conversion_scale_decimal_signed   9

  #define f_conversion_scale_duodecimal_unsigned 8
  #define f_conversion_scale_duodecimal_signed   8

  #define f_conversion_scale_hexidecimal_unsigned 7
  #define f_conversion_scale_hexidecimal_signed   7
#endif // _en_f_type_number_32_

#ifdef _en_f_type_number_128_
  #define f_conversion_scale_binary_unsigned 128
  #define f_conversion_scale_binary_signed   127

  #define f_conversion_scale_octal_unsigned 42
  #define f_conversion_scale_octal_signed   42

  #define f_conversion_scale_decimal_unsigned 38
  #define f_conversion_scale_decimal_signed   38

  #define f_conversion_scale_duodecimal_unsigned 35
  #define f_conversion_scale_duodecimal_signed   35

  #define f_conversion_scale_hexidecimal_unsigned 31
  #define f_conversion_scale_hexidecimal_signed   31
#endif // _en_f_type_number_128_

/**
 * Convert a single character into the binary digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a binary.
 *   F_false if character is not a binary.
 */
#ifndef _di_f_conversion_character_is_binary_
  extern f_return_status f_conversion_character_is_binary(const int8_t character);
#endif // _di_f_conversion_character_is_binary_

/**
 * Convert a single character into the decimal value that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a decimal.
 *   F_false if character is not a decimal.
 */
#ifndef _di_f_conversion_character_is_decimal_
  extern f_return_status f_conversion_character_is_decimal(const int8_t character);
#endif // _di_f_conversion_character_is_decimal_

/**
 * Convert a single character into the duodecimal digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a duodecimal.
 *   F_false if character is not a duodecimal.
 */
#ifndef _di_f_conversion_character_is_duodecimal_
  extern f_return_status f_conversion_character_is_duodecimal(const int8_t character);
#endif // _di_f_conversion_character_is_duodecimal_

/**
 * Convert a single character into the hexidecimal digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a hexidecimal.
 *   F_false if character is not a hexidecimal.
 */
#ifndef _di_f_conversion_character_is_hexidecimal_
  extern f_return_status f_conversion_character_is_hexidecimal(const int8_t character);
#endif // _di_f_conversion_character_is_hexidecimal_

/**
 * Convert a single character into the octal digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is an octal.
 *   F_false if character is not an octal.
 */
#ifndef _di_f_conversion_character_is_octal_
  extern f_return_status f_conversion_character_is_octal(const int8_t character);
#endif // _di_f_conversion_character_is_octal_

/**
 * Convert a single character into the binary digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a binary.
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_binary_
  extern f_return_status f_conversion_character_to_binary(const int8_t character, f_number_unsigned *number);
#endif // _di_f_conversion_character_to_binary_

/**
 * Convert a single character into the decimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a decimal.
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_decimal_
  extern f_return_status f_conversion_character_to_decimal(const int8_t character, f_number_unsigned *number);
#endif // _di_f_conversion_character_to_decimal_

/**
 * Convert a single character into the duodecimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a duodecimal.
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_duodecimal_
  extern f_return_status f_conversion_character_to_duodecimal(const int8_t character, f_number_unsigned *number);
#endif // _di_f_conversion_character_to_duodecimal_

/**
 * Convert a single character into the hexidecimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a hexidecimal.
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_hexidecimal_
  extern f_return_status f_conversion_character_to_hexidecimal(const int8_t character, f_number_unsigned *number);
#endif // _di_f_conversion_character_to_hexidecimal_

/**
 * Convert a single character into the octal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a hexidecimal.
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_octal_
  extern f_return_status f_conversion_character_to_octal(const int8_t character, f_number_unsigned *number);
#endif // _di_f_conversion_character_to_octal_

/**
 * Convert a signed number into the decimal digit string that it represents.
 *
 * The generated number is appended to the destination string.
 *
 * This only supports the following base units: 2 through 16.
 *
 * @param number
 *   The number to convert.
 * @param base
 *   The base unit, usually 10.
 * @param destination
 *   The destination the converted string is saved into.
 *
 * @return
 *   F_none if the number was converted to a string.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_f_conversion_number_signed_to_string_
  extern f_return_status f_conversion_number_signed_to_string(const f_number_signed number, const uint8_t base, f_string_dynamic *destination);
#endif // _di_f_conversion_number_signed_to_string_

/**
 * Convert an unsigned number into the decimal digit string that it represents.
 *
 * The generated number is appended to the destination string.
 *
 * This only supports the following base units: 2 through 16.
 *
 * @param number
 *   The number to convert.
 * @param base
 *   The base unit, usually 10.
 * @param destination
 *   The destination the converted string is saved into.
 *
 * @return
 *   F_none if the number was converted to a string.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_f_conversion_number_unsigned_to_string_
  extern f_return_status f_conversion_number_unsigned_to_string(const f_number_unsigned number, const uint8_t base, f_string_dynamic *destination);
#endif // _di_f_conversion_number_unsigned_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

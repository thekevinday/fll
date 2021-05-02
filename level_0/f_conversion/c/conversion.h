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
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// fll-0 conversion includes
#include <fll/level_0/conversion-common.h>

#ifdef __cplusplus
extern "C" {
#endif

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
  extern f_status_t f_conversion_character_is_binary(const char character);
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
  extern f_status_t f_conversion_character_is_decimal(const char character);
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
  extern f_status_t f_conversion_character_is_duodecimal(const char character);
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
  extern f_status_t f_conversion_character_is_hexidecimal(const char character);
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
  extern f_status_t f_conversion_character_is_octal(const char character);
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
 *
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_binary_
  extern f_status_t f_conversion_character_to_binary(const char character, f_number_unsigned_t *number);
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
 *
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_decimal_
  extern f_status_t f_conversion_character_to_decimal(const char character, f_number_unsigned_t *number);
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
 *
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_duodecimal_
  extern f_status_t f_conversion_character_to_duodecimal(const char character, f_number_unsigned_t *number);
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
 *
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_hexidecimal_
  extern f_status_t f_conversion_character_to_hexidecimal(const char character, f_number_unsigned_t *number);
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
 *
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_octal_
  extern f_status_t f_conversion_character_to_octal(const char character, f_number_unsigned_t *number);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) on out of memory.
 */
#ifndef _di_f_conversion_number_signed_to_string_
  extern f_status_t f_conversion_number_signed_to_string(const f_number_signed_t number, const uint8_t base, f_string_dynamic_t *destination);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) on out of memory.
 */
#ifndef _di_f_conversion_number_unsigned_to_string_
  extern f_status_t f_conversion_number_unsigned_to_string(const f_number_unsigned_t number, const uint8_t base, f_string_dynamic_t *destination);
#endif // _di_f_conversion_number_unsigned_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

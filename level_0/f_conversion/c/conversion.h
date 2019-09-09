/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to convert one data type to another, such as a string to an integer.
 * Provide means to identify a digit or a hexadecimal digit (hexdigit).
 * In the future this will have to link to locale support, due to interpeting strings.
 *
 * Possible error values on return:
 *   f_critical          - an error.
 *   f_invalid_data      - something is wrong with the data sent to this function, error.
 *   f_invalid_parameter - a parameter sent to this function is invalid, error.
 *   f_invalid_syntax    - syntax for data sent to this is invalid, error.
 *   f_no_data           - something is wrong with the data sent to this function, warning.
 *   f_none              - no errors or warnings.
 *   f_unknown           - an unknown error.
 *   f_warn              - a possible problem, but not an error (warning).
 */
#ifndef _F_conversion_h
#define _F_conversion_h

// libc includes
#include <stdlib.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_is_decimal_
  /**
   * convert a single character into the decimal value that it represents.
   */
  extern f_return_status f_is_decimal(const char character);
#endif // _di_f_is_decimal_

#ifndef _di_f_is_hexidecimal_
  /**
   * convert a single character into the hexidecimal digit that it represents
   */
  extern f_return_status f_is_hexidecimal(const char character);
#endif // _di_f_is_hexidecimal_

#ifndef _di_f_character_to_digit_
  /**
   * convert a single character into the digit that it represents.
   */
  extern f_return_status f_character_to_digit(const char character, f_u_long *digit);
#endif // _di_f_character_to_digit_

#ifndef _di_f_character_to_hexdecimal_
  /**
   *convert a single character into the hexidecimal digit that it represents.
   */
  extern f_return_status f_character_to_hexdecimal(const char character, f_u_long *digit);
#endif // _di_f_character_to_hexdecimal_

#ifndef _di_f_string_to_decimal_
  /**
   * works like atoi, except there is a start/stop range.
   * convert a series of positive numbers into a string, stopping at one of the following: EOS, max_length, or a non-digit.
   * will not process signed statuses (+/-).
   */
  extern f_return_status f_string_to_decimal(const f_string string, f_u_long *digit, const f_string_location location);
#endif // _di_f_string_to_decimal_

#ifndef _di_f_string_to_hexidecimal_

  /**
   * works like atoi, except there is a start/stop range and that this is for hexidecimal digits.
   * convert a series of positive  numbers into a string, stopping at one of the following: EOS, max_length, or a non-hexdigit.
   * will not process signed statuses (+/-).
   */
  extern f_return_status f_string_to_hexidecimal(const f_string string, f_u_long *digit, const f_string_location location);
#endif // _di_f_string_to_hexidecimal_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

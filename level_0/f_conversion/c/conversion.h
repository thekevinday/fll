/* FLL - Level 0
 * Project:       Conversion
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide means to convert one data type to another, such as a string to an integer
 * Provide means to identify a digit or a hexadecimal digit (hexdigit)
 * In the future this will have to link to locale support, due to interpeting strings
 *
 * Possible error values on return:
 *   f_warn               - a possible problem, but not an error (warning)
 *   f_critical           - an error
 *   f_unknown            - an unknown error
 *   f_invalid_parameter  - a parameter sent to this function is invalid, error
 *   f_invalid_syntax     - syntax for data sent to this is invalid, error
 *   f_invalid_data       - something is wrong with the data sent to this function, error
 *   f_no_data            - something is wrong with the data sent to this function, warning
 *   f_none               - no errors or warnings
 */
#ifndef _F_conversion_h
#define _F_conversion_h

// fll includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_is_digit_
  // convert a single character into the digit that it represents
  f_extern f_return_status f_is_digit(f_const f_autochar character);
#endif // _di_f_is_digit_

#ifndef _di_f_is_hexdigit_
  // convert a single character into the hexidecimal digit that it represents
  f_extern f_return_status f_is_hexdigit(f_const f_autochar character);
#endif // _di_f_is_hexdigit_

#ifndef _di_f_character_to_digit_
  // convert a single character into the digit that it represents
  f_extern f_return_status f_character_to_digit(f_const f_autochar character, f_u_long *digit);
#endif // _di_f_character_to_digit_

#ifndef _di_f_character_to_hexdigit_
  // convert a single character into the hexidecimal digit that it represents
  f_extern f_return_status f_character_to_hexdigit(f_const f_autochar character, f_u_long *digit);
#endif // _di_f_character_to_hexdigit_

#ifndef _di_f_string_to_digit_
  // works like atoi, except there is a start/stop range
  // convert a series of positive numbers into a string, stopping at one of the following: EOS, max_length, or a non-digit
  // will not process signed statuses (+/-)
  f_extern f_return_status f_string_to_digit(f_const f_string string, f_u_long *digit, f_const f_string_location location);
#endif // _di_f_string_to_digit_

#ifndef _di_f_string_to_hexdigit_
  // works like atoi, except there is a start/stop range and that this is for hexidecimal digits
  // convert a series of positive  numbers into a string, stopping at one of the following: EOS, max_length, or a non-hexdigit
  // will not process signed statuses (+/-)
  f_extern f_return_status f_string_to_hexdigit(f_const f_string string, f_u_long *digit, f_const f_string_location location);
#endif // _di_f_string_to_hexdigit_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

/**
 * FLL - Level 1
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Some console input/output commands.
 */
#ifndef _FL_console_h
#define _FL_console_h

// libc include
#include <limits.h>
#include <string.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/conversion.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a console parameter additional argument to a signed integer.
 *
 * This will detect based types as follows:
 * - hexidecimals begin with either '0x' or '0X'.
 * - duodecimals begin with either '0d' or '0D'.
 * - octals begin with either '0o' or '0O'.
 * - binaries begin with either '0b' or '0B'.
 * - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * @param argv
 *   The argument string expected to be a number.
 *   This is generally passed from the argv[].
 * @param number
 *   The converted number is stored here.
 *   This only gets modified on success.
 *
 * @return
 *   f_none on success.
 *   f_no_data (with error bit) if string starts wth a null (length is 0).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_number (with error bit) if parameter is not a number.
 *   f_overflow (with error bit) on integer overflow.
 *   f_underflow (with error bit) on integer underflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *
 * @see f_conversion_string_to_number_signed()
 */
#ifndef _fl_console_parameter_to_number_signed_
  f_return_status fl_console_parameter_to_number_signed(const f_string argument, f_number_signed *number);
#endif // _fl_console_parameter_to_number_signed_

/**
 * Convert a console parameter additional argument to an unsigned integer.
 *
 * This will detect based types as follows:
 * - hexidecimals begin with either '0x' or '0X'.
 * - duodecimals begin with either '0d' or '0D'.
 * - octals begin with either '0o' or '0O'.
 * - binaries begin with either '0b' or '0B'.
 * - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * @param argv
 *   The argument string expected to be a number.
 *   This is generally passed from the argv[].
 * @param number
 *   The converted number is stored here.
 *   This only gets modified on success.
 *
 * @return
 *   f_none on success.
 *   f_no_data (with error bit) if string starts wth a null (length is 0).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_number (with error bit) if parameter is not a number.
 *   f_negative_number (with error bit) on negative value.
 *   f_overflow (with error bit) on integer overflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *
 * @see f_conversion_string_to_number_unsigned()
 */
#ifndef _fl_console_parameter_to_number_unsigned_
  f_return_status fl_console_parameter_to_number_unsigned(const f_string argument, f_number_unsigned *number);
#endif // _fl_console_parameter_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h

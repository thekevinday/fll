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
#include <sys/stat.h>

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
 * Validate and convert a console parameter additional argument to a file directory in a dynamic string.
 *
 * The directory path is validated to exist.
 *
 * The path to a directy has the following very basic cleanup operations performed:
 * - Ensures that it always ends in a '/'.
 * - Ensures that multiple '/' in front or multiple '/' at end of string is reduced to a single '/' in front and a single '/' at end.
 * - Ensures that multiple '/' following './' at the start of the string is reduced to only './' ('.////' would become './').
 * - Ensures that multiple '/' following '../' at the start of the string is reduced to only '../' ('..////' would become '../').
 *
 * This does not perform complex cleanup, such as '..///..///' to '../../'.
 *
 * The purpose of the cleanups is to ensure/enforce a consistent beginning and ending of the path strings.
 * These path strings can then, very simply, be checked to see how to join them with another string, such as a filename.
 *
 * @param argv
 *   The argument string expected to be a number.
 *   This is generally passed from the argv[].
 * @param directory
 *   The dynamically allocated processed directory string.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on allocation error.
 */
#ifndef _fl_console_parameter_to_string_dynamic_directory_
  extern f_return_status fl_console_parameter_to_string_dynamic_directory(const f_string argument, f_string_dynamic *directory);
#endif // _fl_console_parameter_to_string_dynamic_directory_

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
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_conversion_string_to_number_signed()
 */
#ifndef _fl_console_parameter_to_number_signed_
  extern f_return_status fl_console_parameter_to_number_signed(const f_string argument, f_number_signed *number);
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
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_conversion_string_to_number_unsigned()
 */
#ifndef _fl_console_parameter_to_number_unsigned_
  extern f_return_status fl_console_parameter_to_number_unsigned(const f_string argument, f_number_unsigned *number);
#endif // _fl_console_parameter_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h

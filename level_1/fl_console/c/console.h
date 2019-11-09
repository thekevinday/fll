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
 * Process console parameters.
 *
 * Short parameters are processed as follows:
 * - Begin with either '-' or '+'.
 * - "Empty" parameters are allow, such that '-' or '+' are valid parameters.
 * - Are one character long.
 * - May be grouped as a single parameter, such as "tar -xcf" and "tar -x -c -f" are equivalent.
 * - Additional parameters must immediately follow the parameter or grouped parameters, such as "tar -xfc file.tar.gz" or "tar -x -f file.tar.gz -c".
 *
 * Long parameters are processed as follows:
 * - Begin with either '--' or '++'.
 * - "Empty" parameters are allow, such that '--' or '++' are valid parameters.
 * - Are any length long so long as it is less than f_console_max_size.
 * - May not be grouped and must be separated from any subsequent parameter, such as: "tar --extract --create --file".
 * - Additional parameters must immediately follow the parameter, such as "tar --extract --file file.tar.gz --create".
 *
 * Other parameters are processed as follows:
 * - Anything that does not begin with '-', '+', '--', or '++'.
 * - Are any length long so long as it is less than f_console_max_size.
 * - May not be grouped and must be separated from any subsequent parameter, such as: "tar extract create file".
 * - Additional parameters must immediately follow the parameter, such as "tar extract file file.tar.gz create".
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param parameters
 *   The console parameters to look for.
 *   This will be updated by this function with the results.
 * @param remaining
 *   A list of remaining parameters not associated with anything.
 *
 * @return
 *   f_none on success.
 *   f_no_data if "additional" parameters were expected but not found.
 *   f_failure (with error bit) if width is not long enough to convert when processing arguments as UTF-8.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character, when processing arguments.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_console_parameter_process_
  extern f_return_status fl_console_parameter_process(const f_console_arguments arguments, f_console_parameters parameters, f_string_lengths *remaining);
#endif // _di_fl_console_parameter_process_

/**
 * Given a set of parameter choices, determine which one has the highest priority.
 *
 * The priority is determined by viewing the parameters from left to right.
 * The right-most parameter defined in the set has the priority over others.
 *
 * For example, the color context modes override each other, so only one gets priority.
 * If given, say "+l ++no_color +d", the "+d" would be the right-most parameter "+l" and "++no_color".
 * The decision would be "+d".
 *
 * This also applies to short parameters combined into one, such as "+lnd", the "d" would again be the decision.
 *
 * @param parameters
 *   The parameters to process.
 * @param choices
 *   An array of numeric ids, each representing a parameter within the parameters variable.
 *   The order does not matter.
 * @param decision
 *   The resulting decision.
 *   If none of the parameters are found, then this will not be updated (therefore it is safe to have it pre-initialized to the default).
 *
 * @return
 *   f_none on success.
 *   f_no_data if no parameters were found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_console_parameter_prioritize__
  extern f_return_status fl_console_parameter_prioritize(const f_console_parameters parameters, const f_console_parameter_ids choices, f_console_parameter_id *decision);
#endif // _di_fl_console_parameter_prioritize__

/**
 * Convert a console parameter additional argument to an unsigned integer.
 *
 * Unlike strtoull(), this only accepts complete numbers.
 * If the argument has anything else, such as "123abc", this will consider the number to be "123".
 *
 * This accepts base-16, base-10, and base-8.
 * - Base-16 is prefixed with '0x' or '0X'.
 * - Base-10 is not prefixed.
 * - Base-8 is prefixed with '0'.
 *
 * Note: The idea of an octal (base-8) being prefixed with '0' is a horrible mistake.
 *       This is done by strtoull().
 *       In the future, custom code may be used in place of strtoull() to use '0o' for octal.
 *       Furthermore, '0b' for binary should be supported as well.
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
 *   f_no_data the argument is empty.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_number (with error bit) if parameter is not a number.
 *   f_negative_number (with error bit) on negative value.
 *   f_overflow (with error bit) on overflow.
 *
 * @see strtoull()
 */
#ifndef _fl_console_parameter_to_number_unsigned_
  f_return_status fl_console_parameter_to_number_unsigned(const f_string argument, uint64_t *number);
#endif // _fl_console_parameter_to_number_unsigned_

/**
 * Convert a console parameter additional argument to a signed integer.
 *
 * Unlike strtoll(), this only accepts complete numbers.
 * If the argument has anything else, such as "123abc", this will consider the number to be "123".
 *
 * This accepts base-16, base-10, and base-8.
 * - Base-16 is prefixed with '0x' or '0X'.
 * - Base-10 is not prefixed.
 * - Base-8 is prefixed with '0'.
 *
 * Note: The idea of an octal (base-8) being prefixed with '0' is a horrible mistake.
 *       This is done by strtoull().
 *       In the future, custom code may be used in place of strtoull() to use '0o'/'0O' for octal.
 *       Furthermore, '0b'/'0B' for binary should be supported as well.
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
 *   f_no_data the argument is empty.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_number (with error bit) if parameter is not a number.
 *   f_underflow (with error bit) on underflow.
 *   f_overflow (with error bit) on overflow.
 *
 * @see strtoll()
 */
#ifndef _fl_console_parameter_to_number_signed_
  f_return_status fl_console_parameter_to_number_signed(const f_string argument, int64_t *number);
#endif // _fl_console_parameter_to_number_signed_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h

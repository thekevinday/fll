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
#include <string.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

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
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h

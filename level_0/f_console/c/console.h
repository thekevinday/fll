/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Some console input/output commands.
 */
#ifndef _F_console_h
#define _F_console_h

// libc include
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/type_array.h>
#include <level_0/string.h>
#include <level_0/utf.h>

// fll-0 console includes
#include <level_0/console-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine the type code the given input parameter represents.
 *
 * @param input
 *   The input parameter to process.
 * @param result
 *   The resulting console type code determined by this function.
 *
 * @return
 *   F_none on success.
 *   F_data_not the input string is empty.
 */
#ifndef _di_f_console_identify_
  extern f_status_t f_console_identify(const f_string_t input, f_console_id_t *result);
#endif // _di_f_console_identify_

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
 * - Are any length long so long as it is less than f_console_length_size.
 * - May not be grouped and must be separated from any subsequent parameter, such as: "tar --extract --create --file".
 * - Additional parameters must immediately follow the parameter, such as "tar --extract --file file.tar.gz --create".
 *
 * Other parameters are processed as follows:
 * - Anything that does not begin with '-', '+', '--', or '++'.
 * - Are any length long so long as it is less than f_console_length_size.
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
 *   F_none on success.
 *   F_data_not if "values" parameters were expected but not found.
 *   F_array_too_large (with error bit) if a buffer would exceed max length.
 *   F_failure (with error bit) if width is not long enough to convert when processing arguments as UTF-8.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character, when processing arguments.
 */
#ifndef _di_f_console_parameter_process_
  extern f_status_t f_console_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t parameters, f_string_lengths_t *remaining);
#endif // _di_f_console_parameter_process_

/**
 * Given a set of parameter choices, determine which one has the highest priority.
 *
 * The priority is determined by viewing the parameters from left to right.
 * The left-most parameter defined in the set has the priority over others.
 *
 * For example, the color context modes override each other, so only one gets priority.
 * If given, say "+l ++no_color +d", the "+d" would be the left-most parameter "+l" and "++no_color".
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
 *   F_none on success.
 *   F_data_not if no parameters were found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_console_parameter_prioritize_left_
  extern f_status_t f_console_parameter_prioritize_left(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t *decision);
#endif // _di_f_console_parameter_prioritize_left_

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
 *   F_none on success.
 *   F_data_not if no parameters were found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_console_parameter_prioritize_right_
  extern f_status_t f_console_parameter_prioritize_right(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t *decision);
#endif // _di_f_console_parameter_prioritize_right_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_console_h

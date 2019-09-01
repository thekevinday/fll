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
 * The UTF-8 BOM is not allowed in the parameters.
 *
 * @param argc
 *   The number of parameters passed to the process.
 * @param argv
 *   The parameters passed to the process.
 * @param parameters
 *   The console parameters to look for.
 * @param total_parameters
 *   The used size of the parameters array.
 *
 * @return
 *   f_none on success.
 *   f_no_data if "additional" parameters were expected but not found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_process_parameters_
  extern f_return_status fl_process_parameters(const f_array_length argc, const f_string argv[], f_console_parameter parameters[], const f_array_length total_parameters, f_string_lengths *remaining);
#endif // _di_fl_process_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h

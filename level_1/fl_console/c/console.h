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
#include <level_0/strings.h>
#include <level_0/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process console parameters.
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
 *   f_no_data if no "extra" parameters were found.
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

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
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_process_parameters_
  /**
   * Process console parameters.
   */
  extern f_return_status fl_process_parameters(const f_array_length argc, const f_string argv[], f_console_parameter parameters[], const f_array_length total_parameters, f_string_lengths *remaining);
#endif // _di_fl_process_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h

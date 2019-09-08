/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide functions commonly used by FLL based programs.
 */
#ifndef _FL_program_h
#define _FL_program_h

// libc include
#include <stdio.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print standard help header.
 *
 * @param context
 *   The color context.
 * @param name
 *   The name of the program.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fll_program_print_help_header_
  extern f_return_status fll_program_print_help_header(const fl_color_context context, const f_string name, const f_string version);
#endif // _di_fll_program_print_help_header_

/**
 * Print standard help option.
 *
 * @param context
 *   The color context.
 * @param option_short
 *   The short name of the option.
 * @param option_long
 *   The long name of the option.
 * @param symbol_short
 *   The short symbol of the option.
 * @param symbol_long
 *   The long symbol of the option.
 * @param description
 *   A desciption associated with the option.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fll_program_print_help_option_
  extern f_return_status fll_program_print_help_option(const fl_color_context context, const f_string option_short, const f_string option_long, const f_string symbol_short, const f_string symbol_long, const f_string description);
#endif // _di_fll_program_print_help_option_

/**
 * Print standard help option (long option only).
 *
 * @param context
 *   The color context.
 * @param option_long
 *   The long name of the option.
 * @param symbol_long
 *   The long symbol of the option.
 * @param description
 *   A desciption associated with the option.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fll_program_print_help_option_long_
  extern f_return_status fll_program_print_help_option_long(const fl_color_context context, const f_string option_long, const f_string symbol_long, const f_string description);
#endif // _di_fll_program_print_help_option_long_

/**
 * Print standard help usage.
 *
 * @param context
 *   The color context.
 * @param name
 *   The name of the program.
 * @param parameters
 *   The non-option parameters to be displayed inside the brackets.
 *   Set the first array value to EOS to disable printing of parameters.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fll_program_print_help_usage_
  extern f_return_status fll_program_print_help_usage(const fl_color_context context, const f_string name, const f_string parameters);
#endif // _di_fll_program_print_help_usage_

/**
 * Print the program version.
 *
 * @param version
 *   The version number of the program.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fll_program_print_version_
  extern f_return_status fll_program_print_version(const f_string version);
#endif // _di_fll_program_print_version_

/**
 * Perform basic parameter loading, including initialization of color context and printing errors.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param parameters
 *   The console parameters to look for.
 * @param choices
 *   A set of the color options: no-color option, light-color option, dark-color option.
 *   This must have its used size set to 3 and the ids are expected to be in this order: no_color, light, and dark.
 * @param remaining
 *   A list of remaining parameters not associated with anything.
 * @param context
 *   The color context.
 *
 * @return
 *   f_none on success.
 *   f_no_data if "additional" parameters were expected but not found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fll_program_process_parameters_
  extern f_return_status fll_program_process_parameters(const f_console_arguments arguments, f_console_parameters parameters, const f_console_parameter_ids choices, f_string_lengths *remaining, fl_color_context *context);
#endif // _di_fll_program_process_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_program_h

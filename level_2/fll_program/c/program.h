/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide functions commonly used by FLL based programs.
 */
#ifndef _FLL_program_h
#define _FLL_program_h

// libc include
#include <stdio.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/file.h>

// fll-1 includes
#include <fll/level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print standard help header.
 *
 * @param file
 *   The file to output to.
 * @param context
 *   The color context.
 * @param name
 *   The name of the program.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_color_print().
 *
 * @param f_color_print()
 */
#ifndef _di_fll_program_print_help_header_
  extern f_status_t fll_program_print_help_header(const f_file_t file, const f_color_context_t context, const f_string_t name, const f_string_t version);
#endif // _di_fll_program_print_help_header_

/**
 * Print standard help option.
 *
 * @param file
 *   The file to output to.
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
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_color_print().
 *
 * @param f_color_print()
 */
#ifndef _di_fll_program_print_help_option_
  extern f_status_t fll_program_print_help_option(const f_file_t file, const f_color_context_t context, const f_string_t option_short, const f_string_t option_long, const f_string_t symbol_short, const f_string_t symbol_long, const f_string_t description);
#endif // _di_fll_program_print_help_option_

/**
 * Print standard help option (long option only).
 *
 * @param file
 *   The file to output to.
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
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_color_print().
 *
 * @param f_color_print()
 */
#ifndef _di_fll_program_print_help_option_long_
  extern f_status_t fll_program_print_help_option_long(const f_file_t file, const f_color_context_t context, const f_string_t option_long, const f_string_t symbol_long, const f_string_t description);
#endif // _di_fll_program_print_help_option_long_

/**
 * Print standard help option (other option only).
 *
 * @param file
 *   The file to output to.
 * @param context
 *   The color context.
 * @param option_other
 *   The other name of the option.
 * @param description
 *   A desciption associated with the option.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_color_print().
 *
 * @param f_color_print()
 */
#ifndef _di_fll_program_print_help_option_other_
  extern f_status_t fll_program_print_help_option_other(const f_file_t file, const f_color_context_t context, const f_string_t option_other, const f_string_t description);
#endif // _di_fll_program_print_help_option_other_

/**
 * Print standard help usage.
 *
 * @param file
 *   The file to output to.
 * @param context
 *   The color context.
 * @param name
 *   The name of the program.
 * @param parameters
 *   The non-option parameters to be displayed inside the brackets.
 *   Set the first array value to EOS to disable printing of parameters.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_color_print().
 *
 * @param f_color_print()
 */
#ifndef _di_fll_program_print_help_usage_
  extern f_status_t fll_program_print_help_usage(const f_file_t file, const f_color_context_t context, const f_string_t name, const f_string_t parameters);
#endif // _di_fll_program_print_help_usage_

/**
 * Print the program version.
 *
 * @param file
 *   The file to output to.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fll_program_print_version_
  extern f_status_t fll_program_print_version(const f_file_t file, const f_string_t version);
#endif // _di_fll_program_print_version_

/**
 * Perform basic parameter loading, including initialization of color context.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param parameters
 *   The console parameters to look for.
 * @param choices
 *   A set of the color options: no-color option, light-color option, dark-color option.
 *   This must have its used size set to 3 and the ids are expected to be in this order: no_color, light, and dark.
 * @param right
 *   Set to TRUE for right priortization and FALSE for left prioritization.
 * @param remaining
 *   A list of remaining parameters not associated with anything.
 * @param context
 *   The color context.
 *
 * @return
 *   F_none on success.
 *   F_data_not if "values" parameters were expected but not found.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_console_parameter_prioritize_left().
 *   Errors (with error bit) from: f_console_parameter_prioritize_right().
 *   Errors (with error bit) from: f_console_parameter_process().
 *   Errors (with error bit) from: f_color_load_context().
 *
 * @see f_console_parameter_prioritize_left()
 * @see f_console_parameter_prioritize_right()
 * @see f_console_parameter_process()
 * @see f_color_load_context()
 */
#ifndef _di_fll_program_parameter_process_
  extern f_status_t fll_program_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t parameters, const f_console_parameter_ids_t choices, const bool right, f_array_lengths_t *remaining, f_color_context_t *context);
#endif // _di_fll_program_parameter_process_

/**
 * Set the provided context to empty along with all additional color sets.
 *
 * This will allow for safe usage of the color context and color sets to be safely processed when colors are disabled.
 *
 * @param context
 *   The primary color context to assign.
 * @param sets
 *   (optional) A NULL terminated array representing additional sets to assign as empty.
 *   Set to NULL to not use.
 */
#ifndef _di_fll_program_parameter_process_empty_
  extern void fll_program_parameter_process_empty(f_color_context_t *context, f_color_set_t *sets[]);
#endif // _di_fll_program_parameter_process_empty_

/**
 * Allocate new strings from all of the provided locations.
 *
 * These new strings are appended onto the destination.
 *
 * Empty console parameters are ignored.
 *
 * @param argv
 *   The program argument array to parse.
 * @param values
 *   The string locations where the console parameters are found.
 * @param destination
 *   An array of dynamic strings each representing a console parameter.
 *
 * @return
 *   F_none on success.
 *   F_data_not if nothing to rip, no allocations or reallocations are performed.
 *
 *   F_array_too_large (with error bit) if a buffer would exceed max length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_append().
 *
 * @see f_string_append()
 */
#ifndef _di_fll_program_parameter_additional_append_
  extern f_status_t fll_program_parameter_additional_append(const f_string_t *argv, const f_array_lengths_t values, f_string_dynamics_t *destination);
#endif // _di_fll_program_parameter_additional_append_

/**
 * Mash together all values arguments associated with a given console parameter.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param argv
 *   The program argument array to parse.
 * @param values
 *   The string locations where the console parameters are found.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if nothing to rip, no allocations or reallocations are performed.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_string_mash().
 *
 * @see f_string_mash()
 */
#ifndef _di_fll_program_parameter_additional_mash_
  extern f_status_t fll_program_parameter_additional_mash(const f_string_t glue, const f_array_length_t glue_length, const f_string_t *argv, const f_array_lengths_t values, f_string_dynamic_t *destination);
#endif // _di_fll_program_parameter_additional_mash_

/**
 * Allocate new strings from all of the provided locations.
 *
 * The console parameters are trimmed.
 *
 * @param argv
 *   The program argument array to parse.
 * @param values
 *   The string locations where the console parameters are found.
 * @param destination
 *   An array of dynamic strings each representing a console parameter.
 *
 * @return
 *   F_none on success.
 *   F_data_not if nothing to rip, no allocations or reallocations are performed.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_rip().
 *
 * @see fl_string_rip()
 */
#ifndef _di_fll_program_parameter_additional_rip_
  extern f_status_t fll_program_parameter_additional_rip(const f_string_t *argv, const f_array_lengths_t values, f_string_dynamics_t *destination);
#endif // _di_fll_program_parameter_additional_rip_

/**
 * Mash together all values arguments associated with a given console parameter.
 *
 * The console parameter is trimmed before mashing.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param argv
 *   The program argument array to parse.
 * @param values
 *   The string locations where the console parameters are found.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if nothing to rip, no allocations or reallocations are performed.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_string_dynamic_mash().
 *   Errors (with error bit) from: fl_string_rip().
 *
 * @see f_string_dynamic_mash()
 * @see fl_string_rip()
 */
#ifndef _di_fll_program_parameter_additional_rip_mash_
  extern f_status_t fll_program_parameter_additional_rip_mash(const f_string_t glue, const f_array_length_t glue_length, const f_string_t *argv, const f_array_lengths_t values, f_string_dynamic_t *destination);
#endif // _di_fll_program_parameter_additional_rip_mash_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_program_h

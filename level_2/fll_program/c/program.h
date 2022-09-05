/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provide functions commonly used by FLL based programs.
 */
#ifndef _FLL_program_h
#define _FLL_program_h

// Libc includes.
#include <stdio.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/file.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/string.h>
#include <fll/level_1/print.h>

// FLL-2 program includes.
#include <fll/level_2/program/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print standard help header.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param output
 *   The file stream to output to.
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
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_header_
  extern f_status_t fll_program_print_help_header(const f_file_t output, const f_color_context_t context, const f_string_static_t name, const f_string_static_t version);
#endif // _di_fll_program_print_help_header_

/**
 * Print standard help option.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param output
 *   The file stream to output to.
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
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_option_
  extern f_status_t fll_program_print_help_option(const f_file_t output, const f_color_context_t context, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description);
#endif // _di_fll_program_print_help_option_

/**
 * Print standard help option (long option only).
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param output
 *   The file stream to output to.
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
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_option_long_
  extern f_status_t fll_program_print_help_option_long(const f_file_t output, const f_color_context_t context, const f_string_static_t option_long, const f_string_static_t symbol_long, const char *description);
#endif // _di_fll_program_print_help_option_long_

/**
 * Print standard help option (other option only).
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param output
 *   The file stream to output to.
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
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_option_other_
  extern f_status_t fll_program_print_help_option_other(const f_file_t output, const f_color_context_t context, const f_string_static_t option_other, const char *description);
#endif // _di_fll_program_print_help_option_other_

/**
 * Print standard help usage.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param output
 *   The file stream to output to.
 * @param context
 *   The color context.
 * @param name
 *   The name of the program.
 * @param parameters
 *   (optional) The non-option parameters to be displayed inside the brackets.
 *   Set the first array value to EOS to disable printing of parameters.
 *   Set parameters.used to 0 to disable.
 *
 * @return
 *   F_none on success.
 *
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_usage_
  extern f_status_t fll_program_print_help_usage(const f_file_t output, const f_color_context_t context, const f_string_static_t name, const f_string_static_t parameters);
#endif // _di_fll_program_print_help_usage_

/**
 * Print the program version.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param output
 *   The file stream to output to.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 *
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_version_
  extern f_status_t fll_program_print_version(const f_file_t output, const f_string_static_t version);
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
  extern f_status_t fll_program_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t * const parameters, const f_console_parameter_ids_t choices, const bool right, f_color_context_t * const context);
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
  extern void fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]);
#endif // _di_fll_program_parameter_process_empty_

/**
 * Allocate new strings from all of the provided locations.
 *
 * These new strings are appended onto the destination.
 *
 * Empty console parameters are ignored.
 *
 * @param arguments
 *   The program argument array to parse.
 *   The caller must guarantee that the indexes within values do not exceed the arguments array length.
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
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 * @see f_string_dynamic_append()
 */
#ifndef _di_fll_program_parameter_additional_append_
  extern f_status_t fll_program_parameter_additional_append(const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamics_t * const destination);
#endif // _di_fll_program_parameter_additional_append_

/**
 * Mash together all values arguments associated with a given console parameter.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param arguments
 *   The program argument array to parse.
 *   The caller must guarantee that the indexes within values do not exceed the arguments array length.
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
 *
 * @see f_string_dynamic_mash()
 */
#ifndef _di_fll_program_parameter_additional_mash_
  extern f_status_t fll_program_parameter_additional_mash(const f_string_static_t glue, const f_string_static_t *arguments, const f_array_lengths_t values, f_string_dynamic_t * const destination);
#endif // _di_fll_program_parameter_additional_mash_

/**
 * Allocate new strings from all of the provided locations.
 *
 * The console parameters are trimmed.
 *
 * @param arguments
 *   The program argument array to parse.
 *   The caller must guarantee that the indexes within values do not exceed the arguments array length.
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
 *   Errors (with error bit) from: fl_string_dynamic_rip().
 *
 * @see fl_string_dynamic_rip()
 */
#ifndef _di_fll_program_parameter_additional_rip_
  extern f_status_t fll_program_parameter_additional_rip(const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamics_t * const destination);
#endif // _di_fll_program_parameter_additional_rip_

/**
 * Mash together all values arguments associated with a given console parameter.
 *
 * The console parameter is trimmed before mashing.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param arguments
 *   The program argument array to parse.
 *   The caller must guarantee that the indexes within values do not exceed the arguments array length.
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
 *   Errors (with error bit) from: fl_string_dynamic_rip().
 *
 * @see f_string_dynamic_mash()
 * @see fl_string_dynamic_rip()
 */
#ifndef _di_fll_program_parameter_additional_rip_mash_
  extern f_status_t fll_program_parameter_additional_rip_mash(const f_string_static_t glue, const f_string_static_t *arguments, const f_array_lengths_t values, f_string_dynamic_t * const destination);
#endif // _di_fll_program_parameter_additional_rip_mash_

/**
 * Print message about two long parameters not being allowed to be used together.
 *
 * This assumes both of the long parameters use f_console_symbol_long_enable_s.
 *
 * @param print
 *   The output structure.
 * @param first
 *   The first string.
 * @param second
 *   The second string.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fll_program_parameter_long_print_cannot_use_with_
  extern f_status_t fll_program_parameter_long_print_cannot_use_with(const fl_print_t print, const f_string_static_t first, const f_string_static_t second);
#endif // _di_fll_program_parameter_long_print_cannot_use_with_

/**
 * This provides a standard program setdown operations used by FLL programs.
 *
 * This does the following:
 *   - Flushes standard outputs.
 *   - Closes standard inputs and outputs.
 *   - Closes the signal handler.
 *
 * @param signal
 *   The signal structure.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_signal_close().
 *
 * @see f_signal_close()
 */
#ifndef _di_fll_program_standard_setdown_
  extern f_status_t fll_program_standard_setdown(f_signal_t * const signal);
#endif // _di_fll_program_standard_setdown_

/**
 * This provides a standard program setup operations used by FLL programs.
 *
 * This does the following:
 *   - Handle signals so that program can cleanly exit, deallocating as appropriate.
 *
 * @param signal
 *   The signal structure.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_signal_mask().
 *   Errors (with error bit) from: f_signal_open().
 *
 * @see f_signal_mask()
 * @see f_signal_open()
 * @see f_signal_set_add()
 * @see f_signal_set_delete()
 * @see f_signal_set_empty()
 * @see f_signal_set_fill()
 */
#ifndef _di_fll_program_standard_setup_
  extern f_status_t fll_program_standard_setup(f_signal_t * const signal);
#endif // _di_fll_program_standard_setup_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * If no signals are blocked, then this always returns F_false.
 *
 * @param main
 *   The main program data.
 *   The main->signal must be used to designate blocked signals.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   0 on no signal received or when main is NULL.
 *
 * @see f_signal_read()
 */
#ifndef _di_fll_program_standard_signal_received_
  extern f_status_t fll_program_standard_signal_received(fll_program_data_t * const main);
#endif // _di_fll_program_standard_signal_received_

/**
 * Standardized callback for checking for interrupts via the f_state_t interrupt callback.
 *
 * This only checks for the signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * These signals may not be checked if they are not also blocked via the fll_program_data_t.signals variable.
 *
 * When one of the above signals is both blocked and received, then this calls fll_program_standard_signal_received().
 *
 * @param state
 *   The state data.
 *   This must be of type (f_state_t *).
 *
 *   When constructing the f_state_t variable, a fll_program_data_t pointer must be passed into the f_state_t.custom variable.
 *   This requires the state.custom variable to be of type (fll_program_data_t *).
 * @param internal
 *   Not used.
 *
 * @return
 *   F_interrupt_not if not interrupted.
 *
 *   F_interrupt (with error bit) if interrupted.
 *
 * @see fll_program_standard_signal_received()
 */
#ifndef _di_fll_program_standard_signal_state_
  extern f_status_t fll_program_standard_signal_state(void * const state, void * const internal);
#endif // _di_fll_program_standard_signal_state_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_program_h

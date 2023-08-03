/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.7
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
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/print.h>

// FLL-2 program includes.
#include <fll/level_2/program/common.h>
#include <fll/level_2/program/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine the color context from the parameters and then set the color context based on the choice.
 *
 * This will allow for the color context and the color sets to be safely used when colors are disabled.
 *
 * @param choices
 *   An array of color modes.
 *   The default, if no mode is specified, will be the last value in the array.
 * @param modes
 *   An array designating the context modes associated with each choice.
 *   This must exactly match the size of the choices array.
 *   No bounds checking is performed.
 * @param right
 *   If TRUE, use the right-most parameter on conflict.
 *   If FALSE, use the left-most parameter on conflict.
 * @param main
 *   The main program data.
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
 *   Errors (with error bit) from: f_color_load_context().
 *
 * @see f_console_parameter_prioritize_left()
 * @see f_console_parameter_prioritize_right()
 * @see f_color_load_context()
 */
#ifndef _di_fll_program_parameter_process_context_
  extern f_status_t fll_program_parameter_process_context(const f_uint16s_t choices, const uint8_t modes[], const bool right, fll_program_data_t * const main);
#endif // _di_fll_program_parameter_process_context_

/**
 * Determine the color context from the parameters and then set the color context based on the choice.
 *
 * This will allow for the color context and the color sets to be safely used when colors are disabled.
 *
 * This is identical to fll_program_parameter_process_context() except it provides the standard choices and modes.
 *
 * @param right
 *   If TRUE, use the right-most parameter on conflict.
 *   If FALSE, use the left-most parameter on conflict.
 * @param main
 *   The main program data.
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
 *   Errors (with error bit) from: f_color_load_context().
 *
 * @see f_console_parameter_prioritize_left()
 * @see f_console_parameter_prioritize_right()
 * @see f_color_load_context()
 */
#ifndef _di_fll_program_parameter_process_context_standard_
  extern f_status_t fll_program_parameter_process_context_standard(const bool right, fll_program_data_t * const main);
#endif // _di_fll_program_parameter_process_context_standard_

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
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fll_program_parameter_process_empty_
  extern f_status_t fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]);
#endif // _di_fll_program_parameter_process_empty_

/**
 * Determine the verbosity from the parameters and then set the verbosity based on the choice.
 *
 * @param choices
 *   The available choices based on parameter ids.
 *   The default, if no verbosity is specified, will be the last value in the array.
 * @param verbosity
 *   An array designating what to set the verbosity to based on the choice made.
 *   This must exactly match the size of the choices array.
 *   No bounds checking is performed.
 * @param right
 *   If TRUE, use the right-most parameter on conflict.
 *   If FALSE, use the left-most parameter on conflict.
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but choices.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_console_parameter_prioritize_left().
 *   Errors (with error bit) from: f_console_parameter_prioritize_right().
 *
 * @see f_console_parameter_prioritize_left()
 * @see f_console_parameter_prioritize_right()
 */
#ifndef _di_fll_program_parameter_process_verbosity_
  extern f_status_t fll_program_parameter_process_verbosity(const f_uint16s_t choices, const uint8_t verbosity[], const bool right, fll_program_data_t * const main);
#endif // _di_fll_program_parameter_process_verbosity_

/**
 * Determine the verbosity from the parameters and then set the verbosity based on the choice.
 *
 * This is identical to fll_program_parameter_process_verbosity() except it provides the standard choices and modes.
 *
 * @param right
 *   If TRUE, use the right-most parameter on conflict.
 *   If FALSE, use the left-most parameter on conflict.
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_console_parameter_prioritize_left().
 *   Errors (with error bit) from: f_console_parameter_prioritize_right().
 *
 * @see f_console_parameter_prioritize_left()
 * @see f_console_parameter_prioritize_right()
 */
#ifndef _di_fll_program_parameter_process_verbosity_standard_
  extern f_status_t fll_program_parameter_process_verbosity_standard(const bool right, fll_program_data_t * const main);
#endif // _di_fll_program_parameter_process_verbosity_standard_

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
  extern f_status_t fll_program_parameter_additional_append(const f_string_static_t * const arguments, const f_number_unsigneds_t values, f_string_dynamics_t * const destination);
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
  extern f_status_t fll_program_parameter_additional_mash(const f_string_static_t glue, const f_string_static_t *arguments, const f_number_unsigneds_t values, f_string_dynamic_t * const destination);
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
 *   Errors (with error bit) from: f_rip_dynamic().
 *
 * @see f_rip_dynamic()
 */
#ifndef _di_fll_program_parameter_additional_rip_
  extern f_status_t fll_program_parameter_additional_rip(const f_string_static_t * const arguments, const f_number_unsigneds_t values, f_string_dynamics_t * const destination);
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
 *   Errors (with error bit) from: f_rip_dynamic().
 *
 * @see f_string_dynamic_mash()
 * @see f_rip_dynamic()
 */
#ifndef _di_fll_program_parameter_additional_rip_mash_
  extern f_status_t fll_program_parameter_additional_rip_mash(const f_string_static_t glue, const f_string_static_t *arguments, const f_number_unsigneds_t values, f_string_dynamic_t * const destination);
#endif // _di_fll_program_parameter_additional_rip_mash_

/**
 * This provides a standard program set down operations used by FLL programs.
 *
 * This does the following:
 *   - Flushes program data files.
 *   - Flushes standard outputs.
 *   - Closes program data files.
 *   - Closes standard inputs and outputs.
 *   - Closes the signal handler.
 *
 * @param program
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_signal_close().
 *
 * @see f_file_close()
 * @see f_file_flush()
 * @see f_file_stream_close()
 * @see f_file_stream_flush()
 * @see f_signal_close()
 */
#ifndef _di_fll_program_standard_set_down_
  extern f_status_t fll_program_standard_set_down(fll_program_data_t * const program);
#endif // _di_fll_program_standard_set_down_

/**
 * This provides a standard program set up operations used by FLL programs.
 *
 * This does the following:
 *   - Handle signals so that program can cleanly exit, de-allocating as appropriate.
 *
 * @param program
 *   The program data.
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
#ifndef _di_fll_program_standard_set_up_
  extern f_status_t fll_program_standard_set_up(fll_program_data_t * const program);
#endif // _di_fll_program_standard_set_up_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * If no signals are blocked, then this always returns F_false.
 *
 * @param program
 *   The program data.
 *   The program.signal must be used to designate blocked signals.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   0 on no signal received or when main is NULL.
 *
 * @see f_signal_read()
 */
#ifndef _di_fll_program_standard_signal_received_
  extern uint32_t fll_program_standard_signal_received(fll_program_data_t * const program);
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
 * As a callback, this does not perform the standard parameter checking.
 *
 * @param state
 *   The state data.
 *   This must be of type (f_state_t *).
 *
 *   When constructing the f_state_t variable, a fll_program_data_t pointer must be passed into the f_state_t.custom variable.
 *   This requires the state.custom variable to be of type (fll_program_data_t *).
 *   This must not be NULL.
 *
 *   This alters state.status:
 *     F_interrupt_not if not interrupted.
 *
 *     F_interrupt (with error bit) if interrupted.
 * @param internal
 *   Not used.
 *
 * @see fll_program_standard_signal_received()
 */
#ifndef _di_fll_program_standard_signal_handle_
  extern void fll_program_standard_signal_handle(void * const state, void * const internal);
#endif // _di_fll_program_standard_signal_handle_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_program_h

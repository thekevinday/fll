/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This file is only ever included by main/main.c and should not normally be included anywhere else.
 * Anything that wants to include this should be providing the "fss_read" program functionality in some manner.
 */
#ifndef _fss_read_main_h
#define _fss_read_main_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Standard program entry point.
 *
 * @param argc
 *   The number of arguments.
 * @param argv
 *   The array of arguments.
 * @param envp
 *   The array of all environment variables on program start.
 *
 * @return
 *   0 on success.
 *   1 on error.
 */
extern int main(const int argc, const f_string_t *argv, const f_string_t *envp);

/**
 * Process printing help for when not specifying "--as".
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This does not alter main.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_read_main_process_help_
  extern void fss_read_main_process_help(void * const main);
#endif // _di_fss_read_main_process_help_

/**
 * Perform the standard program setting load process for the "--as" parameter.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.callback.process_help, main.callback.process_normal, and main.callback.process_pipe.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *     F_interrupt on (exit) signal received.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 *
 * @see fss_read_setting_load()
 */
#ifndef _di_fss_read_main_setting_load_as_
  extern void fss_read_main_setting_load_as(const f_console_arguments_t arguments, fss_read_main_t * const main);
#endif // _di_fss_read_main_setting_load_as_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_main_h

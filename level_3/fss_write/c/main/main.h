/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This file is only ever included by main/main.c and should not normally be included anywhere else.
 * Anything that wants to include this should be providing the "main" program functionality in some manner.
 * Any program utilizing this should link to the "main" program library.
 */
#ifndef _fss_write_main_h
#define _fss_write_main_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process printing help for when not specifying "--as".
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_main_process_help_
  extern void fss_write_main_process_help(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_main_process_help_

/**
 * Perform the standard program setting load process for the "--as" parameter.
 *
 * This should be called before fss_write_setting_load() is called to ensure "--as" gets processed before "--help".
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately retuns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.process_help, setting.process_normal, and setting.process_pipe.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
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
 * @see fss_write_setting_load()
 */
#ifndef _di_fss_write_main_setting_load_as_
  extern void fss_write_main_setting_load_as(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_main_setting_load_as_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_main_h

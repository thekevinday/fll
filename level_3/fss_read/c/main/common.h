/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_common_h
#define _fss_read_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Make sure the array size of quotes_object and quotes_content matches the respective objects and contents.
 *
 * @param main
 *   The main program data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_uint8s_resize().
 *     Errors (with error bit) from: f_uint8ss_resize().
 *
 * @see f_uint8s_resize()
 * @see f_uint8ss_resize()
 */
#ifndef _di_fss_read_ensure_quotes_length_
  extern void fss_read_ensure_quotes_length(fss_read_main_t * const main);
#endif // _di_fss_read_ensure_quotes_length_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 *
 *   This calls main.callback.process_last_line() if not NULL.
 *
 *   This alters main.setting.range.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity_standard().
 *
 *     Errors (with error bit) from: fss_read_setting_load_depth().
 *     Errors (with error bit) from: fss_read_signal_check()
 * @param callback
 *   (optional) Designate a function to call after performing the initial processing, but before printing help.
 *   If the function returns F_done, then this function immediately returns, resetting status to F_none.
 *   Set to NULL to disable.
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity_standard()
 *
 * @see fss_read_setting_load_depth()
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_setting_load_
  extern void fss_read_setting_load(const f_console_arguments_t arguments, fss_read_main_t * const main, void (*callback)(const f_console_arguments_t arguments, fss_read_main_t * const main));
#endif // _di_fss_read_setting_load_

/**
 * Process the depth and depth related parameters.
 *
 * Will handle depth-sensitive parameter conflicts, such as --name being used with --at (which is not allowed).
 *
 * This should only be called by standards that support this behavior.
 *
 * This is intended to be called within the scope of a setting load callback in fss_read_setting_load().
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_rip_dynamic().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *
 *     Errors (with error bit) from: fss_read_depths_resize().
 * @param parameters
 *   The console parameters structure representing the processed arguments.
 *
 *   Must not be NULL.
 *
 * @see f_rip_dynamic()
 * @see f_string_dynamic_append()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fll_program_print_signal_received()
 *
 * @see fss_read_depths_resize()
 * @see fss_read_setting_load()
 */
#ifndef _di_fss_read_setting_load_depth_
  extern void fss_read_setting_load_depth(const f_console_arguments_t arguments, void * const main, f_console_parameters_t * const parameters);
#endif // _di_fss_read_setting_load_depth_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_common_h

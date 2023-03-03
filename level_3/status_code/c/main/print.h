/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _status_code_print_h
#define _status_code_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic code.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param code
 *   The code to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_code_
  f_status_t status_code_print_code(status_code_setting_t * const setting, const fl_print_t print, const uint16_t code);
#endif // _di_status_code_print_code_

/**
 * Print generic context wrapped value.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param context
 *   The context string to wrap the variable with.
 * @param value
 *   The value string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_context_value_
  f_status_t status_code_print_context_value(status_code_setting_t * const setting, const fl_print_t print, const f_color_set_t context, const f_string_static_t value);
#endif // _di_status_code_print_context_value_

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 *
 * @see status_code_print_line_first_locked()
 */
#ifndef _di_status_code_print_error_
  extern f_status_t status_code_print_error(status_code_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_status_code_print_error_

/**
 * Print an error message when error parameter and warning parameter are specified without number parameter.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_status_code_print_error_cannot_error_warning_number_
  extern f_status_t status_code_print_error_cannot_error_warning_number(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_error_cannot_error_warning_number_

/**
 * Print an error message when no status codes are provided.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_error_no_status_codes_
  extern f_status_t status_code_print_error_no_status_codes(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_error_no_status_codes_

/**
 * Print an error message when a callback from status_code_setting_t is invalid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name of the callback setting that is invalid.
 *   This should either be 'status_string_from' or 'status_string_to'.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_status_code_print_error_invalid_callback_
  extern f_status_t status_code_print_error_invalid_callback(status_code_setting_t * const setting, const fl_print_t print, const f_string_t name);
#endif // _di_status_code_print_error_invalid_callback_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fl_print_format()
 *
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_standard()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_status_code_print_help_
  extern f_status_t status_code_print_help(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_help_

/**
 * Print help detailed part of the help.
 *
 * This is designed to be called from within status_code_print_help().
 * This neither locks nor unlocks the stream and expects the stream to be unlocked.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type status_code_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fl_print_format()
 *
 * @see status_code_print_help()
 */
#ifndef _di_status_code_print_help_detail_
  extern f_status_t status_code_print_help_detail(void * const setting, const fl_print_t print);
#endif // _di_status_code_print_help_detail_

/**
 * Print first new line, if applicable, otherwise nothing.
 *
 * This is generally intended to be used before data prints.
 * This should probably be printed to setting.message while data goes to setting.output.
 *
 * This ensures a first line is printed if the data is the first output to be performed.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_status_code_print_line_first_data_
  extern f_status_t status_code_print_line_first_data(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_first_data_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_status_code_print_line_first_locked_
  extern f_status_t status_code_print_line_first_locked(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_first_locked_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_status_code_print_line_first_unlocked_
  extern f_status_t status_code_print_line_first_unlocked(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_first_unlocked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_status_code_print_line_last_locked_
  extern f_status_t status_code_print_line_last_locked(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_last_locked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_print_dynamic_raw()
 */
#ifndef _di_status_code_print_line_last_unlocked_
  extern f_status_t status_code_print_line_last_unlocked(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_h

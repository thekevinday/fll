/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_print_h
#define _status_code_print_h

#ifdef __cplusplus
extern "C" {
#endif

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
#ifndef _di_status_code_print_line_first_
  extern f_status_t status_code_print_line_first(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_first_

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
#ifndef _di_status_code_print_line_last_
  extern f_status_t status_code_print_line_last(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_h

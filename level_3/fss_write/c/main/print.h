/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_write_print_h
#define _fss_write_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_print()
 */
#ifndef _di_fss_write_print_error_
  extern f_status_t fss_write_print_error(fss_write_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_fss_write_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fss_write_print_error_file_
  extern f_status_t fss_write_print_error_file(fss_write_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fss_write_print_error_file_

/**
 * Print error message about each Object parameter not being specified before a Content parameter.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_error_object_not_before_content_
  extern f_status_t fss_write_print_error_object_not_before_content(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_error_object_not_before_content_

/**
 * Print an message about a multiple Content being unsupported.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param standard
 *   A string representing the standard name, such as "FSS-0000 (Basic)".
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_error_one_content_only_
  extern f_status_t fss_write_print_error_one_content_only(fss_write_setting_t * const setting, const fl_print_t print, const f_string_static_t standard);
#endif // _di_fss_write_print_error_one_content_only_

/**
 * Print error when prepend parameter has something other than white space.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _fss_write_print_error_prepend_only_whitespace_
  extern f_status_t fss_write_print_error_prepend_only_whitespace(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _fss_write_print_error_prepend_only_whitespace_

/**
 * Print an error message about a parameter New Line character '\n' (U+000A) being unsupported.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param standard
 *   A string representing the standard name, such as "FSS-0000 (Basic)".
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_error_unsupported_eol_
  extern f_status_t fss_write_print_error_unsupported_eol(fss_write_setting_t * const setting, const fl_print_t print, const f_string_static_t standard);
#endif // _di_fss_write_print_error_unsupported_eol_

/**
 * Print standard parts of the help.
 *
 * This is expected to be called as part of the help printing and does not perform any locking.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 */
#ifndef _di_fss_write_print_help_
  extern void fss_write_print_help(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_help_

/**
 * Print standard parts of the help regarding pipe usage.
 *
 * This is expected to be called as part of the help printing and does not perform any locking.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 */
#ifndef _di_fss_write_print_help_pipe_
  extern void fss_write_print_help_pipe(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_help_pipe_

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
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_line_first_locked_
  extern f_status_t fss_write_print_line_first_locked(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_line_first_locked_

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
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_line_first_unlocked_
  extern f_status_t fss_write_print_line_first_unlocked(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_line_first_unlocked_

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
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_line_last_locked_
  extern f_status_t fss_write_print_line_last_locked(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_line_last_locked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_line_last_unlocked_
  extern f_status_t fss_write_print_line_last_unlocked(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_print_h

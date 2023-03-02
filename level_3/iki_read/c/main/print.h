/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _iki_read_print_h
#define _iki_read_print_h

#ifdef __cplusplus
extern "C" {
#endif

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
 * @see fll_error_print()
 */
#ifndef _di_iki_read_print_error_
  extern f_status_t iki_read_print_error(iki_read_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_iki_read_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
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
#ifndef _di_iki_read_print_error_file_
  extern f_status_t iki_read_print_error_file(iki_read_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_iki_read_print_error_file_

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
 */
#ifndef _di_iki_read_print_help_
  extern f_status_t iki_read_print_help(iki_read_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_read_print_help_

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
 */
#ifndef _di_iki_read_print_line_first_locked_
  extern f_status_t iki_read_print_line_first_locked(iki_read_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_read_print_line_first_locked_

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
 */
#ifndef _di_iki_read_print_line_first_unlocked_
  extern f_status_t iki_read_print_line_first_unlocked(iki_read_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_read_print_line_first_unlocked_

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
 */
#ifndef _di_iki_read_print_line_last_locked_
  extern f_status_t iki_read_print_line_last_locked(iki_read_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_read_print_line_last_locked_

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
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_iki_read_print_line_last_unlocked_
  extern f_status_t iki_read_print_line_last_unlocked(iki_read_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_read_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_print_h

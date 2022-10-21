/**
 * FLL - Level 3
 *
 * Project: FSS Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_status_code_print_h
#define _fss_status_code_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error message when error parameter and warning parameter are specified without number parameter.
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
#ifndef _di_fss_status_code_print_error_cannot_error_warning_number_
  extern f_status_t fss_status_code_print_error_cannot_error_warning_number(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_error_cannot_error_warning_number_

/**
 * Print an error message when no status codes are provided.
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
#ifndef _di_fss_status_code_print_error_no_fss_status_codes_
  extern f_status_t fss_status_code_print_error_no_fss_status_codes(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_error_no_fss_status_codes_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_status_code_print_help_
  extern f_status_t fss_status_code_print_help(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_help_

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
#ifndef _di_fss_status_code_print_line_first_locked_
  extern f_status_t fss_status_code_print_line_first_locked(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_line_first_locked_

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
#ifndef _di_fss_status_code_print_line_first_unlocked_
  extern f_status_t fss_status_code_print_line_first_unlocked(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_line_first_unlocked_

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
#ifndef _di_fss_status_code_print_line_last_locked_
  extern f_status_t fss_status_code_print_line_last_locked(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_line_last_locked_

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
#ifndef _di_fss_status_code_print_line_last_unlocked_
  extern f_status_t fss_status_code_print_line_last_unlocked(fss_status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_status_code_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_status_code_print_h

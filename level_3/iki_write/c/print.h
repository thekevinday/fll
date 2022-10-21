/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _iki_write_print_h
#define _iki_write_print_h

#ifdef __cplusplus
extern "C" {
#endif

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
#ifndef _di_iki_write_print_help_
  extern f_status_t iki_write_print_help(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_help_

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
#ifndef _di_iki_write_print_line_first_locked_
  extern f_status_t iki_write_print_line_first_locked(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_line_first_locked_

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
#ifndef _di_iki_write_print_line_first_unlocked_
  extern f_status_t iki_write_print_line_first_unlocked(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_line_first_unlocked_

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
#ifndef _di_iki_write_print_line_last_locked_
  extern f_status_t iki_write_print_line_last_locked(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_line_last_locked_

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
#ifndef _di_iki_write_print_line_last_unlocked_
  extern f_status_t iki_write_print_line_last_unlocked(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_line_last_unlocked_

/**
 * Print error message about "main" Object being missing.
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
#ifndef _di_iki_write_print_error_main_missing_
  extern f_status_t iki_write_print_error_main_missing(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_error_main_missing_

/**
 * Print error message about an Object not being valid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param object
 *   The a string representing the object that is missing.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_iki_write_print_error_object_not_valid_
  extern f_status_t iki_write_print_error_object_not_valid(iki_write_setting_t * const setting, const fl_print_t print, const f_string_static_t object);
#endif // _di_iki_write_print_error_object_not_valid_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_print_h

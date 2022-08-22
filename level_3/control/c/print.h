/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _control_print_h
#define _control_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 * @see control_main()
 */
#ifndef _di_control_print_help_
  extern f_status_t control_print_help(const fll_program_data_t * const main);
#endif // _di_control_print_help_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param lock
 *   If TRUE, then lock the stream.
 *   If FALSE, then do not lock or unlock the stream.
 */
#ifndef _di_control_print_line_first_
  extern void control_print_line_first(control_setting_t * const setting, const fl_print_t print, const bool lock);
#endif // _di_control_print_line_first_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param lock
 *   If TRUE, then lock the stream.
 *   If FALSE, then do not lock or unlock the stream.
 */
#ifndef _di_control_print_line_last_
  extern void control_print_line_last(control_setting_t * const setting, const fl_print_t print, const bool lock);
#endif // _di_control_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_print_h

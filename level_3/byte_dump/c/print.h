/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _byte_dump_print_h
#define _byte_dump_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param output
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 *
 * @see byte_dump_main()
 */
#ifndef _di_byte_dump_print_help_
  extern f_status_t byte_dump_print_help(byte_dump_setting_t * const setting, const fl_print_t print);
#endif // _di_byte_dump_print_help_

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
#ifndef _di_byte_dump_print_line_first_
  extern void byte_dump_print_line_first(byte_dump_setting_t * const setting, const fl_print_t print, const bool lock);
#endif // _di_byte_dump_print_line_first_

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
#ifndef _di_byte_dump_print_line_last_
  extern void byte_dump_print_line_last(byte_dump_setting_t * const setting, const fl_print_t print, const bool lock);
#endif // _di_byte_dump_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_print_h

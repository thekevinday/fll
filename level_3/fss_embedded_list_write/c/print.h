/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_embedded_list_write_print_h
#define _fss_embedded_list_write_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_embedded_list_write_print_help_
  extern f_status_t fss_embedded_list_write_print_help(fss_embedded_list_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_embedded_list_write_print_help_

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
#ifndef _di_fss_embedded_list_write_print_line_first_
  extern void fss_embedded_list_write_print_line_first(fss_embedded_list_write_setting_t * const setting, const fl_print_t print, const bool lock);
#endif // _di_fss_embedded_list_write_print_line_first_

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
#ifndef _di_fss_embedded_list_write_print_line_last_
  extern void fss_embedded_list_write_print_line_last(fss_embedded_list_write_setting_t * const setting, const fl_print_t print, const bool lock);
#endif // _di_fss_embedded_list_write_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_embedded_list_write_print_h

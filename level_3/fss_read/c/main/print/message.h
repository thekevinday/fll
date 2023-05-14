/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_print_message_h
#define _fss_read_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print standard parts of the help.
 *
 * This is expected to be called as part of the help printing and does not perform any locking.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 */
#ifndef _di_fss_read_print_message_help_
  extern void fss_read_print_message_help(fl_print_t * const print);
#endif // _di_fss_read_print_message_help_

/**
 * Print standard parts of the help regarding the notes header.
 *
 * This is expected to be called as part of the help printing and does not perform any locking.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param number
 *   The FSS standard number, such as "0000".
 * @param name
 *   The FSS standard name, such as "Basic".
 */
#ifndef _di_fss_read_print_message_help_note_header_
  extern void fss_read_print_message_help_note_header(fl_print_t * const print, const f_string_static_t number, const f_string_static_t name);
#endif // _di_fss_read_print_message_help_note_header_

/**
 * Print standard parts of the help regarding notes.
 *
 * This is expected to be called as part of the help printing and does not perform any locking.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param new_line
 *   If 0x0 (F_false), then print help regarding space separating Object and Content.
 *   If 0x1 (F_true), then print help regarding new line separating Object and Content.
 *   If 0x2, then print both separation types (intended for use by the general fss_read program).
 */
#ifndef _di_fss_read_print_message_help_note_
  extern void fss_read_print_message_help_note(fl_print_t * const print, const uint8_t new_line);
#endif // _di_fss_read_print_message_help_note_

/**
 * Print standard parts of the help regarding pipe usage.
 *
 * This is expected to be called as part of the help printing and does not perform any locking.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 */
#ifndef _di_fss_read_print_message_help_pipe_
  extern void fss_read_print_message_help_pipe(fl_print_t * const print);
#endif // _di_fss_read_print_message_help_pipe_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_print_message_h

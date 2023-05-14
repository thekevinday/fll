/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_print_message_h
#define _fss_write_print_message_h

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
#ifndef _di_fss_write_print_message_help_
  extern void fss_write_print_message_help(fl_print_t * const print);
#endif // _di_fss_write_print_message_help_

/**
 * Print standard parts of the help regarding Object End, Content Next, and Content End usage.
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
#ifndef _di_fss_write_print_message_help_end_next_
  extern void fss_write_print_message_help_end_next(fl_print_t * const print);
#endif // _di_fss_write_print_message_help_end_next_

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
#ifndef _di_fss_write_print_message_help_pipe_
  extern void fss_write_print_message_help_pipe(fl_print_t * const print);
#endif // _di_fss_write_print_message_help_pipe_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_print_message_h

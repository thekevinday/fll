/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_print_message_h
#define _iki_read_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_iki_read_print_message_help_
  extern f_status_t iki_read_print_message_help(fl_print_t * const print);
#endif // _di_iki_read_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_print_message_h

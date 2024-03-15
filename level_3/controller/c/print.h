/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _controller_print_h
#define _controller_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type controller_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_controller_print_message_help_
  extern f_status_t controller_print_message_help(fl_print_t * const print);
#endif // _di_controller_print_message_help_
#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_print_h

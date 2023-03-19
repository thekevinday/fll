/**
 * FLL - Level 3
 *
 * Project: UTF8
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
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_controller_print_help_
  extern f_status_t controller_print_help(controller_setting_t * const setting, const fl_print_t print);
#endif // _di_controller_print_help_
#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_print_h

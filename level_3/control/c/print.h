/**
 * FLL - Level 3
 *
 * Project: Control
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
#ifndef _di_control_print_help_
  extern f_status_t control_print_help(control_setting_t * const setting, const fl_print_t print);
#endif // _di_control_print_help_control

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_print_h

/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _firewall_print_h
#define _firewall_print_h

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
 */
#ifndef _di_firewall_print_help_
  extern f_status_t firewall_print_help(firewall_setting_t * const setting, const fl_print_t print);
#endif // _di_firewall_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_print_h

/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the operate show functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_show_h
#define _firewall_operate_show_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the firewall show operation.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_child on child process exiting.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: fll_execute_program()
 *     Errors (with error bit) from: fll_print_dynamic_raw()
 *
 * @see fll_execute_program()
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_firewall_operate_show_
  extern void firewall_operate_show(firewall_main_t * const main);
#endif // _di_firewall_operate_show_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_show_h

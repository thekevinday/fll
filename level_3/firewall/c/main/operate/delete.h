/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the delete functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_delete_h
#define _firewall_operate_delete_h

#ifdef __cplusplus
extern "C" {
#endif

 /**
 * Unapply (remove) the firewall rules, deleting all existing firewall rules being used.
 *
 * This function is not about de-allocating memory.
 * This function is not about modifying settings or files.
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
 *
 * @see fll_execute_program()
 */
#ifndef _di_firewall_operate_delete_chains_
  extern void firewall_operate_delete_chains(firewall_main_t * const main);
#endif // _di_firewall_operate_delete_chains_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_delete_h

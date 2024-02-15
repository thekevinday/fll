/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_process_h
#define _firewall_operate_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perforrm the loaded firewall rules.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: ()
 *
 * @see ()
 */
#ifndef _di_firewall_operate_process_rules_
  extern void firewall_operate_process_rules(firewall_main_t * const main);
#endif // _di_firewall_operate_process_rules_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_process_h

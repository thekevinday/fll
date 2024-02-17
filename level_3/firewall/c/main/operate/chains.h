/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the operate chains functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_chains_h
#define _firewall_operate_chains_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load and operate the each of the Content chains.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters:
 *     - main.data.is.
 *     - main.data.range.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: firewall_operate_rules()
 *
 * @see firewall_operate_rules()
 */
#ifndef _di_firewall_operate_chains_
  extern void firewall_operate_chains(firewall_main_t * const main);
#endif // _di_firewall_operate_chains_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_chains_h

/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the load functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_load_h
#define _firewall_operate_load_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load and process the Content chains.
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
 *     Errors (with error bit) from: firewall_operate_load_rules()
 *
 * @see firewall_operate_load_rules()
 */
#ifndef _di_firewall_operate_load_chains_
  extern void firewall_operate_load_chains(firewall_main_t * const main);
#endif // _di_firewall_operate_load_chains_

/**
 * Load and process the rules.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters:
 *     - main.data.buffer.
 *     - main.data.delimits.
 *     - main.data.rule_objects.
 *     - main.data.rule_contents.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_fss_apply_delimit()
 *     Errors (with error bit) from: firewall_operate_process_rules()
 *     Errors (with error bit) from: fll_fss_extended_read()
 *
 * @see f_fss_apply_delimit()
 * @see firewall_operate_process_rules()
 * @see fll_fss_extended_read()
 */
#ifndef _di_firewall_operate_load_rules_
  extern void firewall_operate_load_rules(firewall_main_t * const main);
#endif // _di_firewall_operate_load_rules_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_load_h

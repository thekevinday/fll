/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides operate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_h
#define _firewall_operate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the firewall operation.
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
 *     Errors (with error bit) from: f_directory_list()
 *     Errors (with error bit) from: f_memory_array_increase_by()
 *     Errors (with error bit) from: firewall_operate_buffer_chain()
 *     Errors (with error bit) from: firewall_operate_create_custom_chains()
 *     Errors (with error bit) from: firewall_operate_default_lock()
 *     Errors (with error bit) from: firewall_operate_delete_chains()
 *     Errors (with error bit) from: firewall_operate_rules()
 *     Errors (with error bit) from: firewall_operate_process_rules()
 *     Errors (with error bit) from: firewall_operate_show()
 *
 * @see f_directory_list()
 * @see f_memory_array_increase_by()
 * @see firewall_operate_buffer_chain()
 * @see firewall_operate_create_custom_chains()
 * @see firewall_operate_default_lock()
 * @see firewall_operate_delete_chains()
 * @see firewall_operate_rules()
 * @see firewall_operate_process_rules()
 * @see firewall_operate_show()
 */
#ifndef _di_firewall_operate_
  extern void firewall_operate(firewall_main_t * const main);
#endif // _di_firewall_operate_

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

/**
 * Operate the rules.
 *
 * @param main
 *   The main program and setting data.
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
#ifndef _di_firewall_operate_rules_
  extern void firewall_operate_rules(firewall_main_t * const main);
#endif // _di_firewall_operate_rules_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_h

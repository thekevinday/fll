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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_h

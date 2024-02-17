/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the operate create functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_create_h
#define _firewall_operate_create_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Apply firewall rules for creating custom chains.
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
 *     Errors (with error bit) from: f_memory_array_increase()
 *     Errors (with error bit) from: f_memory_array_increase_by()
 *     Errors (with error bit) from: f_string_dynamic_append()
 *     Errors (with error bit) from: fll_execute_program()
 * @param file
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see fll_execute_program()
 */
#ifndef _di_firewall_operate_create_custom_chains_
  extern void firewall_operate_create_custom_chains(firewall_main_t * const main);
#endif // _di_firewall_operate_create_custom_chains_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_create_h

/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the operate buffer functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_buffer_h
#define _firewall_operate_buffer_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Buffer firewall chain.
 *
 * The rules being processed are selected from main.data.range within main.data.buffer.
 * Delimits are applied to the main.data.buffer on success.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters:
 *     - main.cache.delimits.
 *     - main.data.buffer.
 *     - main.data.chain_contents.
 *     - main.data.chain_objects.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_child on child process exiting.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_file_open()
 *     Errors (with error bit) from: f_file_read()
 *     Errors (with error bit) from: f_fss_apply_delimit()
 *     Errors (with error bit) from: fll_fss_basic_list_read()
 * @param file
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 *
 * @see f_file_open()
 * @see f_file_read()
 * @see f_fss_apply_delimit()
 * @see fll_fss_basic_list_read()
 */
#ifndef _di_firewall_operate_buffer_chain_
  extern void firewall_operate_buffer_chain(firewall_main_t * const main, const f_string_static_t file, const bool optional);
#endif // _di_firewall_operate_buffer_chain_

/**
 * Buffer firewall rules.
 *
 * The rules being processed are selected from main.data.range within main.data.buffer.
 * Delimits are applied to the main.data.buffer on success.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters:
 *     - main.cache.delimits.
 *     - main.data.buffer.
 *     - main.data.rule_contents.
 *     - main.data.rule_objects.
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
#ifndef _di_firewall_operate_buffer_rules_
  extern void firewall_operate_buffer_rules(firewall_main_t * const main);
#endif // _di_firewall_operate_buffer_rules_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_buffer_h

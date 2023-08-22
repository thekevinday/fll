/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_firewall_h
#define _PRIVATE_firewall_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform commands.
 *
 * @param data
 *   The program data.
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_parameter (with error bit) on invalid parameter passed.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_partial_append().
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_partial_append()
 */
extern f_status_t firewall_perform_commands(firewall_data_t * const data, firewall_local_data_t * const local) F_attribute_visibility_internal_d;

/**
 * Create custom chains.
 *
 * @param data
 *   The program data.
 * @param reserved
 *   firewall chains.
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_parameter (with error bit) on invalid parameter passed.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_create_custom_chains(firewall_data_t * const data, firewall_reserved_chains_t * const reserved, firewall_local_data_t * const local) F_attribute_visibility_internal_d;

/**
 * Deallocate chains.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_parameter (with error bit) on invalid parameter passed.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_delete_chains(firewall_data_t * const data) F_attribute_visibility_internal_d;

/**
 * Lock the firewall.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_default_lock(firewall_data_t * const data) F_attribute_visibility_internal_d;

/**
 * Buffer firewall rules.
 *
 * @param data
 *   The program data.
 * @param filename
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_buffer_rules(firewall_data_t * const data, const f_string_static_t filename, const bool optional, firewall_local_data_t * const local) F_attribute_visibility_internal_d;

/**
 * Process buffered rules.
 *
 * @param data
 *   The program data.
 * @param range
 *   The current position within the buffer and the stop point.
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_process_rules(firewall_data_t * const data, f_string_range_t * const range, firewall_local_data_t * const local) F_attribute_visibility_internal_d;

/**
 * Delete allocated local data.
 *
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_okay on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_delete_local_data(firewall_local_data_t * const local) F_attribute_visibility_internal_d;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_firewall_h

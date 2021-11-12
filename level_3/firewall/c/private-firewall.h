/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_firewall_h
#define _PRIVATE_firewall_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform commands.
 *
 * @param main
 *   The main program data.
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_perform_commands(firewall_main_t * const main, const firewall_local_data_t local) F_attribute_visibility_internal_d;

/**
 * Create custom chains.
 *
 * @param main
 *   The main program data.
 * @param reserved
 *   firewall chains.
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_create_custom_chains(firewall_main_t * const main, firewall_reserved_chains_t *reserved, firewall_local_data_t *local) F_attribute_visibility_internal_d;

/**
 * Deallocate chains.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_delete_chains(firewall_main_t * const main) F_attribute_visibility_internal_d;

/**
 * Lock the firewall.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_default_lock(firewall_main_t * const main) F_attribute_visibility_internal_d;

/**
 * Buffer firewall rules.
 *
 * @param main
 *   The main program data.
 * @param filename
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_buffer_rules(firewall_main_t * const main, const f_string_t filename, const bool optional, firewall_local_data_t *local) F_attribute_visibility_internal_d;

/**
 * Process buffered rules.
 *
 * @param main
 *   The main program data.
 * @param range
 *   The current position within the buffer and the stop point.
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_process_rules(firewall_main_t * const main, f_string_range_t *range, firewall_local_data_t *local) F_attribute_visibility_internal_d;

/**
 * Delete allocated local data.
 *
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_delete_local_data(firewall_local_data_t * const local) F_attribute_visibility_internal_d;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_firewall_h

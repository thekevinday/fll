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
 * @param local
 *   Local firewall settings.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_perform_commands(const firewall_local_data_t local, const firewall_main_t main) f_attribute_visibility_internal;

/**
 * Create custom chains.
 *
 * @param reserved
 *   firewall chains.
 * @param local
 *   Local firewall settings.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_create_custom_chains(firewall_reserved_chains_t *reserved, firewall_local_data_t *local, firewall_main_t *main) f_attribute_visibility_internal;

/**
 * Deallocate chains.
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_delete_chains(const firewall_main_t main) f_attribute_visibility_internal;

/**
 * Lock the firewall.
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_default_lock(const firewall_main_t main) f_attribute_visibility_internal;

/**
 * Buffer firewall rules.
 *
 * @param filename
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 * @param local
 *   Local firewall settings.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_buffer_rules(const f_string_t filename, const bool optional, firewall_local_data_t *local, firewall_main_t *main) f_attribute_visibility_internal;

/**
 * Process buffered rules.
 *
 * @param range
 *   The current position within the buffer and the stop point.
 * @param local
 *   Local firewall settings.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
extern f_status_t firewall_process_rules(f_string_range_t *range, firewall_local_data_t *local, firewall_main_t *main) f_attribute_visibility_internal;

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
extern f_status_t firewall_delete_local_data(firewall_local_data_t *local) f_attribute_visibility_internal;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_firewall_h

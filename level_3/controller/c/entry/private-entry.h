/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_entry_h
#define _PRIVATE_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine if the type code represents a Rule type.
 *
 * @param type
 *   The type code to compare against.
 *
 * @return
 *    TRUE if Rule type.
 *    FALSE otherwise.
 */
#ifndef _di_controller_entry_action_type_is_rule_
  extern f_status_t controller_entry_action_type_is_rule(uint8_t type) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_action_type_is_rule_

/**
 * Convert the Entry Action type to Rule Action type.
 *
 * @param type
 *   The Entry Action type.
 *
 * @return
 *    TRUE if Rule type.
 *    FALSE otherwise.
 */
#ifndef _di_controller_entry_action_type_to_rule_action_type_
  extern uint8_t controller_entry_action_type_to_rule_action_type(uint8_t type) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_action_type_to_rule_action_type_

/**
 * Read the entry list, extracting all items and values.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param content_range
 *   The range in the list buffer representing the content.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param actions
 *   The processed actions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_entry_actions_increase_by().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_fss_apply_delimit().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_partial_rip_nulless().
 *   Errors (with error bit) from: f_string_dynamics_increase_by().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 * @see controller_entry_actions_increase_by()
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase_by()
 * @see f_fss_apply_delimit()
 * @see fl_string_dynamic_partial_rip_nulless()
 * @see fll_fss_extended_read()
 */
#ifndef _di_controller_entry_actions_read_
  extern f_status_t controller_entry_actions_read(const controller_global_t global, const bool is_entry, const f_string_range_t content_range, controller_cache_t * const cache, controller_entry_actions_t *actions) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_actions_read_

/**
 * Pre-process all items for the loaded entry.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 * @param cache
 *   The main/global cache to use.
 *
 * @return
 *   F_none on success.
 *   F_recurse (with error bit) on a recursion error.
 *   F_valid_not (with error bit) on invalid entry item, entry item action, or entry item action value.
 *
 *   Errors (with error bit) from: macro_f_array_lengths_t_increase_by().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 *   This will detect and report all errors, but only the first error is returned.
 *   Memory related errors return immediately.

 * @see macro_f_array_lengths_t_increase_by()
 * @see f_string_dynamic_append()
 */
#ifndef _di_controller_entry_preprocess_
  extern f_status_t controller_entry_preprocess(const controller_global_t global, const bool is_entry, controller_cache_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_preprocess_

/**
 * Process (execute) all Items for the loaded Entry or Exit.
 *
 * @param global
 *   The global data.
 * @param cache
 *   The main/global cache to use.
 * @param failsafe
 *   If TRUE, operate in failsafe mode (starts at designated failsafe Item).
 *   If FALSE, operate in normal mode (starts at "main" Item).
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 *
 * @return
 *   F_none on success.
 *   F_execute on success and program exiting (scripts may result in this) or when execute would have been executed but is instead simulated.
 *
 *   F_require (with error bit) if a required Item failed.
 *   F_critical (with error bit) on any critical error.
 *   F_execute (with error bit) if the "execute" Item Action failed.
 *
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *
 *   Errors (with error bit) from: macro_f_array_lengths_t_increase_by().
 *   Errors (with error bit) from: controller_perform_ready().
 *
 * @see f_string_dynamic_append_nulless()
 *
 * @see macro_f_array_lengths_t_increase_by()
 * @see controller_perform_ready()
 */
#ifndef _di_controller_entry_process_
  extern f_status_t controller_entry_process(const controller_global_t * const global, controller_cache_t * const cache, const bool failsafe, const bool is_entry) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_process_

/**
 * Read the entry, extracting all lists.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   The cache for the specific thread.
 *   This should be the cache global.thread->asynchronouss.array[global.id].cache.
 *
 * @return
 *   F_none on success.
 *   F_file_found_not on file not found for a an exit file (is_entry is FALSE).
 *
 *   Errors (with error bit) from: controller_entry_actions_read().
 *   Errors (with error bit) from: controller_entry_items_increase_by().
 *   Errors (with error bit) from: controller_file_load().
 *   Errors (with error bit) from: controller_status_simplify_error().
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_fss_apply_delimit().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_items_increase_by()
 * @see controller_file_load()
 * @see controller_status_simplify_error()
 *
 * @see f_fss_count_lines()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate()
 * @see f_fss_apply_delimit()
 * @see fll_fss_basic_list_read()
 */
#ifndef _di_controller_entry_read_
  extern f_status_t controller_entry_read(const controller_global_t global, const bool is_entry, controller_cache_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_read_

/**
 * Read the entry settings, loading all settings.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param content_range
 *   The range in the list buffer representing the content.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 *   Errors (with error bit) from: controller_entry_print_error_file().
 *
 * @see controller_entry_print_error_file()
 */
#ifndef _di_controller_entry_settings_read_
  extern f_status_t controller_entry_settings_read(const controller_global_t global, const bool is_entry, const f_string_range_t content_range, controller_cache_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_

/**
 * Load the given ranges within the buffer into the provided map.
 *
 * @param buffer
 *   The buffer the ranges are associated with.
 * @param ranges
 *   The ranges to load from the buffer.
 *   This expects the caller to already ensure the ranges.used = 2.
 * @param setting_maps
 *   The map to load the settings into.
 *
 * @return
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_maps_increase().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_maps_increase()
 */
#ifndef _di_controller_entry_settings_read_map_
  f_status_t controller_entry_settings_read_map(const f_string_static_t buffer, const f_string_ranges_t ranges, f_string_maps_t *setting_maps) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_map_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_entry_h

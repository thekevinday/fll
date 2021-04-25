/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_entry_h
#define _PRIVATE_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print all parameters for some action, separated by a space.
 *
 * @param stream
 *   The file stream to print to.
 * @param action
 *   The entry action whose parameters will be printed.
 */
#ifndef _di_controller_entry_action_parameters_print_
  extern void controller_entry_action_parameters_print(FILE * const stream, const controller_entry_action_t action) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_action_parameters_print_

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
  extern f_status_t controller_entry_action_type_is_rule(uint8_t type) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_action_type_is_rule_

/**
 * Get a string representing the entry action type.
 *
 * @param type
 *   The entry action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_entry_action_type_name_
  extern f_string_static_t controller_entry_action_type_name(const uint8_t type) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_action_type_name_

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
  extern uint8_t controller_entry_action_type_to_rule_action_type(uint8_t type) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_action_type_to_rule_action_type_

/**
 * Increase the size of the entry item actions array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param actions
 *   The entry item actions to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_actions_increase_by_
  extern f_status_t controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t *actions) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_actions_increase_by_

/**
 * Read the entry list, extracting all items and values.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param content_range
 *   The range in the list buffer representing the content.
 * @param main
 *   The main data.
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
 *   Errors (with error bit) from: fl_fss_apply_delimit().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_rip_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *   Errors (with error bit) from: f_string_dynamics_increase_by().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 * @see controller_entry_actions_increase_by()
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate_after()
 * @see f_string_dynamics_increase_by()
 * @see fl_fss_apply_delimit()
 * @see fl_string_dynamic_rip_nulless()
 * @see fll_fss_extended_read()
 */
#ifndef _di_controller_entry_actions_read_
  extern f_status_t controller_entry_actions_read(const bool is_entry, const f_string_range_t content_range, controller_main_t main, controller_cache_t *cache, controller_entry_actions_t *actions) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_actions_read_

/**
 * Print the entry related error, locking the print mutex during the print.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param print
 *   Designates how printing is to be performed.
 * @param cache
 *   The action cache.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 * @param thread
 *   The thread data.
 *
 * @see fll_error_print()
 * @see controller_entry_error_print_cache()
 */
#ifndef _di_controller_entry_error_print_
  extern void controller_entry_error_print(const bool is_entry, const fll_error_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_error_print_

/**
 * Print additional error/warning information in addition to existing error that is found within the cache.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * This neither locks the thread nor does it check to see if output is enabled or disabled.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param print
 *   Designates how printing is to be performed.
 * @param cache
 *   The action cache.
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_read()
 */
#ifndef _di_controller_entry_error_print_cache_
  extern void controller_entry_error_print_cache(const bool is_entry, const fll_error_print_t print, const controller_cache_action_t cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_error_print_cache_

/**
 * Increase the size of the entry items array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param items
 *   The entry items to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_items_increase_by_
  extern f_status_t controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_items_increase_by_

/**
 * Read the entry, extracting all lists.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param main
 *   The main data.
 * @param cache
 *   The cache for the specific thread.
 *   This should be the cache main.thread->asynchronouss.array[main.id].cache.
 *
 * @return
 *   F_none on success.
 *   F_file_found_not on file not found for a an exit file (is_entry is FALSE).
 *
 *   Errors (with error bit) from: controller_entry_actions_read().
 *   Errors (with error bit) from: controller_entry_items_increase_by().
 *   Errors (with error bit) from: controller_file_load().
 *   Errors (with error bit) from: controller_status_simplify_error().
 *   Errors (with error bit) from: controller_string_dynamic_append_terminated().
 *   Errors (with error bit) from: controller_string_dynamic_partial_append_terminated().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_fss_apply_delimit().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_items_increase_by()
 * @see controller_file_load()
 * @see controller_status_simplify_error()
 * @see controller_string_dynamic_append_terminated()
 * @see controller_string_dynamic_partial_append_terminated()
 * @see f_fss_count_lines()
 * @see fl_fss_apply_delimit()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate()
 * @see fll_fss_basic_list_read()
 */
#ifndef _di_controller_entry_read_
  extern f_status_t controller_entry_read(const bool is_entry, controller_main_t main, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_read_

/**
 * Read the entry settings, loading all settings.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param content_range
 *   The range in the list buffer representing the content.
 * @param main
 *   The main data.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_entry_settings_read_
  extern f_status_t controller_entry_settings_read(const bool is_entry, const f_string_range_t content_range, controller_main_t main, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_settings_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_entry_h

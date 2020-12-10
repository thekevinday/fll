/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_rule_h
#define _PRIVATE_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get a string representing the rule action method.
 *
 * @param type
 *   The rule action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_action_method_name_
  extern f_string_static_t controller_rule_action_method_name(const uint8_t type) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_action_method_name_

/**
 * Read the rule action.
 *
 * The object and content ranges are merged together (in that order) as the action parameters.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   The buffer containing the content.
 * @param object
 *   (optional) The range representing where the object is found within the buffer.
 *   Set pointer address to 0 to disable.
 * @param content
 *   (optional) The ranges representing where the content is found within the buffer.
 *   Set pointer address to 0 to disable.
 * @param action
 *   The processed action.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see f_fss_count_lines()
 * @see fl_string_dynamic_partial_append_nulless()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_controller_rule_action_read_
  extern f_return_status controller_rule_action_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, controller_rule_action_t *action) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_action_read_

/**
 * Get a string representing the rule action type.
 *
 * @param type
 *   The rule action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_action_type_name_
  extern f_string_static_t controller_rule_action_type_name(const uint8_t type) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_action_type_name_

/**
 * Increase the size of the rule actions array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param actions
 *   The actions to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_controller_rule_actions_increase_by_
  extern f_return_status controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t *actions) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_actions_increase_by_

/**
 * Read the content within the buffer, extracting all valid actions for the current processed item.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   The processed item.
 * @param actions
 *   The processed actions.
 * @param range
 *   The current positions within the buffer being operated on.
 *   This is expected to be set to a position immediately after a valid object read.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_rule_action_read().
 *   Errors (with error bit) from: controller_rule_actions_increase_by().
 *   Errors (with error bit) from: f_fss_count_lines().
 *
 * @see controller_rule_action_read()
 * @see controller_rule_actions_increase_by()
 * @see f_fss_count_lines()
 */
#ifndef _di_controller_rule_actions_read_
  extern f_return_status controller_rule_actions_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_actions_read_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * @param output
 *   The error or warning output structure.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 *
 * @see controller_rule_actions_read()
 * @see controller_rule_item_read()
 * @see controller_rule_items_read()
 * @see controller_rule_read()
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_rule_error_print_
  extern void controller_rule_error_print(const fll_error_print_t output, const controller_cache_t cache, const bool item) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

/**
 * Perform an execution of the given rule.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param index
 *   The position in the setting.rules array representing the rule to simulate.
 * @param setting
 *   The controller settings data.
 *
 * @return
 *   F_none on success.
 *
 *   On success and the rule is run synchronously, then the individual status for the rule is set to F_complete.
 *   On success and the rule is run asynchronously, then the individual status for the rule is set to F_busy.
 *   On failure, the individual status for the rule is set to an appropriate error status.
 */
#ifndef _di_controller_rule_execute_
  extern f_return_status controller_rule_execute(const controller_data_t data, const controller_cache_t cache, const f_array_length_t index, controller_setting_t *setting) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_execute_

/**
 * Search the already loaded rules to see if one is found.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param rule_id
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 *
 * @return
 *   If found, a valid location within the setting.rules array.
 *   If not found, then setting.rules.used is returned.
 */
#ifndef _di_controller_rule_find_loaded_
  extern f_array_length_t controller_rule_find_loaded(const controller_data_t data, const controller_setting_t setting, const f_string_static_t rule_id) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_find_loaded_

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   The processed item.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 *
 * @see controller_rule_actions_read()
 * @see f_fss_count_lines()
 * @see fl_string_dynamic_partial_append_nulless()
 * @see fl_string_dynamic_terminate_after()
 */
#ifndef _di_controller_rule_item_read_
  extern f_return_status controller_rule_item_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_item_read_

/**
 * Get a string representing the rule item type.
 *
 * @param type
 *   The rule item type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_item_type_name_
  extern f_string_static_t controller_rule_item_type_name(const uint8_t type) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_item_type_name_

/**
 * Increase the size of the rule items array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param items
 *   The items to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rule_items_increase_by_
  extern f_return_status controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_items_increase_by_

/**
 * Process and execute the given rule by the rule id.
 *
 * Any dependent rules are loaded and executed as per "need", "want", and "wish" rule settings.
 * All dependent rules must be already loaded, this function will not load any rules.
 *
 * This function is recursively called for each "need", "want", and "wish", and has a max recursion length of the max size of the f_array_lengths_t array.
 *
 * @todo add asynchronous boolean? (will also need a wait boolean, so this should probably be a uint8_t with using bitwise states).
 *
 * @param data
 *   The program data.
 * @param index
 *   Position in the rules array representing the rule to execute
 * @param simulate
 *   If TRUE, then the rule execution is simulated (printing a message that the rule would be executed but does not execut the rule).
 *   If FALSE, the rule is not simulated and is executed as normal.
 * @param setting
 *   The controller settings data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *   This utilizes cache.stack for recursive executions, no function called by this may therefore safely use cache.stack for any other purpose.
 *   This utilizes line_action, line_item, name_action, and name_item from cache, but they are backed up before starting and then restored after finishing.
 *
 * @return
 *    F_none on success.
 */
#ifndef _di_controller_rule_process_
  extern f_return_status controller_rule_process(const controller_data_t data, const f_array_length_t index, const bool simulate, controller_setting_t *setting, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_process_

/**
 * Read the rule file, extracting all valid items.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param rule_id
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *   The rule status will be updated by this function.
 *
 * @return
 *   F_true on success.
 *   F_false on failure.
 *
 * @see controller_rule_items_increase_by().
 * @see controller_rule_item_read().
 * @see f_file_stream_open().
 * @see f_file_stream_read().
 * @see f_fss_count_lines().
 * @see fl_fss_apply_delimit().
 * @see fl_string_dynamic_partial_append().
 * @see fl_string_dynamic_partial_append_nulless().
 * @see fl_string_dynamic_terminate_after().
 * @see fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_return_status controller_rule_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t rule_id, controller_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_read_

/**
 * Read the content within the buffer, extracting all valid settings.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * Errors from this are not considered fatal, but the first error code encountered is returned.
 * Memory failure errors are always immediately returned.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *
 * @return
 *    F_none on success.
 *    F_valid_not (with error bit) on success but there were one or more invalid settings encountered.
 *
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_rip_nulless().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *   Errors (with error bit) from: fl_string_maps_increase().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *   Errors (with error bit) from: fll_path_canonical().
 *
 * @see fl_string_dynamic_partial_append_nulless()
 * @see fl_string_dynamic_rip_nulless()
 * @see fl_string_dynamics_increase()
 * @see fl_string_maps_increase()
 * @see fll_fss_extended_read()
 * @see fll_path_canonical()
 */
#ifndef _di_controller_rule_setting_read_
  extern f_return_status controller_rule_setting_read(const controller_data_t data, controller_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_setting_read_

/**
 * Perform a simulated execution of the given rule.
 *
 * This simply prints information about the rule.
 *
 * This automatically sets the rule's status to F_complete.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param index
 *   The position in the setting.rules array representing the rule to simulate.
 * @param setting
 *   The controller settings data.
 */
#ifndef _di_controller_rule_simulate_
  extern void controller_rule_simulate(const controller_data_t data, const controller_cache_t cache, const f_array_length_t index, controller_setting_t *setting) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_simulate_

/**
 * Increase the size of the rules array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param rules
 *   The rules to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rules_increase_by_
  extern f_return_status controller_rules_increase_by(const f_array_length_t amount, controller_rules_t *rules) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h

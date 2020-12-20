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
 * Read the parameters for some rule action.
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
 * @param parameters
 *   The processed parameters.
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
#ifndef _di_controller_rule_parameters_read_
  extern f_return_status controller_rule_parameters_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_parameters_read_

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
 * Read the content within the buffer, processing the action (or a set of within a list) for the given item.
 *
 * This will automatically increase the size of the actions array as needed.
 *
 * @param data
 *   The program data.
 * @param type
 *   The action type for this action or set of actions.
 * @param method
 *   The action method for this action or set of actions.
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
 *   Errors (with error bit) from: controller_rule_actions_increase_by().
 *   Errors (with error bit) from: controller_rule_parameters_read().
 *   Errors (with error bit) from: f_fss_count_lines().
 *
 * @see controller_rule_actions_increase_by()
 * @see controller_rule_parameters_read()
 * @see f_fss_count_lines()
 */
#ifndef _di_controller_rule_action_read_
  extern f_return_status controller_rule_action_read(const controller_data_t data, const uint8_t type, const uint8_t method, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_action_read_

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
 * @see controller_rule_action_read()
 * @see controller_rule_item_read()
 * @see controller_rule_items_read()
 * @see controller_rule_read()
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_rule_error_print_
  extern void controller_rule_error_print(const fll_error_print_t output, const controller_cache_t cache, const bool item) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

/**
 * Print an error or warning message related to the failed execution of some program or script.
 *
 * @param output
 *   The error or warning output structure.
 * @param program_is
 *   If TRUE, then this represents a program.
 *   If FALSE, then this represents a script.
 * @param name
 *   The name of the program or script.
 * @param code
 *   The code returned by the executed program or script.
 */
#ifndef _di_controller_rule_error_print_execute_
  extern void controller_rule_error_print_execute(const fll_error_print_t output, const bool program_is, const f_string_t name, const int code) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_execute_

/**
 * Print an error or warning message related to need/want/wish settings of some rule.
 *
 * @param output
 *   The error or warning output structure.
 * @param need_want_wish
 *   The appropriate string, such as "needs", "wants", or "wishes for" to print when describing this error/warning.
 * @param value
 *   The value that is the error or warning.
 * @param why
 *   A short explanation on why this is an error or warning.
 */
#ifndef _di_controller_rule_error_print_need_want_wish_
  extern void controller_rule_error_print_need_want_wish(const fll_error_print_t output, const f_string_t need_want_wish, const f_string_t value, const f_string_t why) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_need_want_wish_

/**
 * Perform an execution of the given rule.
 *
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param index
 *   The position in the setting.rules array representing the rule to simulate.
 * @param type
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *
 *   On success and the rule is run synchronously, then the individual status for the rule is set to F_complete.
 *   On success and the rule is run asynchronously, then the individual status for the rule is set to F_busy.
 *   On failure, the individual status for the rule is set to an appropriate error status.
 */
#ifndef _di_controller_rule_execute_
  extern f_return_status controller_rule_execute(const controller_cache_t cache, const f_array_length_t index, const uint8_t type, controller_data_t *data, controller_setting_t *setting) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_execute_

/**
 * Perform an execution of the given rule for the script execution type.
 *
 * @param action
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param options
 *   The controller execute options (and not fl_execute_parameter_t.option).
 *   This is for designating asynchronous and other controller specific execution options.
 *   @todo this is not yet implemented.
 * @param arguments
 *   The arguments to pass to the script.
 * @param parameter
 *   The execute parameter settings.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_script_
  extern f_return_status controller_rule_execute_script(const controller_rule_action_t action, const uint8_t options, const f_string_dynamics_t arguments, fl_execute_parameter_t * const parameter, controller_data_t *data) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_execute_script_

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
 * Construct an id from two distinct strings found within a single given source.
 *
 * @param data
 *   The program data.
 * @param source
 *   The source string that both the directory and basename are copied from.
 * @param directory
 *   A range within the source representing the directory part of a rule id.
 * @param basename
 *   A range within the source representing the basename part of a rule id.
 * @param id
 *   The constructed id.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 *
 * @see f_string_append()
 * @see fl_string_dynamic_partial_append_nulless()
 * @see fl_string_dynamic_terminate_after()
 */
#ifndef _di_controller_rule_id_construct_
  extern f_return_status controller_rule_id_construct(const controller_data_t data, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t *id) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_id_construct_

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
 * @see controller_rule_action_read()
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
 * Construct a canonical rule file path from the given path directory and name.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param path_directory
 *   The path directory, such as 'boot' from '/etc/controller/rules/boot/default.rule'.
 * @param path_name
 *   The path name, such as 'default' from '/etc/controller/rules/boot/default.rule'.
 * @param path
 *   The constructed path.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 *   Errors (with error bit) from: fll_path_canonical().
 *
 * @see f_file_stat()
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 * @see fl_string_append()
 * @see fl_string_dynamic_terminate_after()
 * @see fll_path_canonical()
 */
#ifndef _di_controller_rule_path_
  extern f_return_status controller_rule_path(const controller_data_t data, const controller_setting_t setting, const f_string_static_t path_directory, const f_string_static_t path_name, f_string_dynamic_t *path) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_path_

/**
 * Process and execute the given rule by the rule id.
 *
 * Any dependent rules are loaded and executed as per "need", "want", and "wish" rule settings.
 * All dependent rules must be already loaded, this function will not load any rules.
 *
 * This function is recursively called for each "need", "want", and "wish", and has a max recursion length of the max size of the f_array_lengths_t array.
 *
 * @param index
 *   Position in the rules array representing the rule to execute
 * @param action
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_rule_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_rule_option_asynchronous, then run asynchronously.
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *   This utilizes cache.stack for recursive executions, no function called by this may therefore safely use cache.stack for any other purpose.
 *   This utilizes line_action, line_item, name_action, and name_item from cache, but they are backed up before starting and then restored after finishing.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 */
#ifndef _di_controller_rule_process_
  extern f_return_status controller_rule_process(const f_array_length_t index, const uint8_t action, const uint8_t options, controller_data_t *data, controller_setting_t *setting, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
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
 * @param action
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_rule_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_rule_option_asynchronous, then run asynchronously.
 * @param setting
 *   The controller settings data.
 */
#ifndef _di_controller_rule_simulate_
  extern void controller_rule_simulate(const controller_data_t data, const controller_cache_t cache, const f_array_length_t index, const uint8_t action, const uint8_t options, controller_setting_t *setting) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_simulate_

/**
 * Increase the size of the rules array, but only if necessary.
 *
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
#ifndef _di_controller_rules_increase_
  extern f_return_status controller_rules_increase(controller_rules_t *rules) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_increase_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h

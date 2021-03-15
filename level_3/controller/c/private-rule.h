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
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_controller_rule_parameters_read_
  extern f_status_t controller_rule_parameters_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) f_gcc_attribute_visibility_internal;
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
  extern f_status_t controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t *actions) f_gcc_attribute_visibility_internal;
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
  extern f_status_t controller_rule_action_read(const controller_data_t data, const uint8_t type, const uint8_t method, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_action_read_

/**
 * Copy a rule, allocating new space as necessary.
 *
 * This does not do any locking or unlocking for the rule data, be sure to lock appropriately before and after calling this.
 *
 * @todo finish writing this.
 *
 * @param source
 *   The source rule to copy from.
 * @param destination
 *   The destination rule to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: XXXX().
 */
#ifndef _di_controller_rule_copy_
  extern f_status_t controller_rule_copy(controller_rule_t *source, controller_rule_t *destination) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_copy_

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
  extern void controller_rule_error_print(const fll_error_print_t output, const controller_cache_action_t cache, const bool item) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

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
 * @param thread
 *   The thread data.
 *
 * @see controller_rule_error_print()
 */
#ifndef _di_controller_rule_error_print_
  extern void controller_rule_error_print_locked(const fll_error_print_t output, const controller_cache_action_t cache, const bool item, controller_thread_t *thread) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

/**
 * Print an error or warning message related to the failed execution of some program or script.
 *
 * @param output
 *   The error or warning output structure.
 * @param script_is
 *   If TRUE, then this represents a script.
 *   If FALSE, then this represents a program.
 * @param name
 *   The name of the program or script.
 * @param code
 *   The code returned by the executed program or script.
 * @param status
 *   The status code representing the failure (without the error bit set).
 */
#ifndef _di_controller_rule_error_print_execute_
  extern void controller_rule_error_print_execute(const fll_error_print_t output, const bool script_is, const f_string_t name, const int code, const f_status_t status) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_execute_

/**
 * Print an error or warning message related to the failed execution of some program or script for when the program or script is not found.
 *
 * @param output
 *   The error or warning output structure.
 * @param script_is
 *   If TRUE, then this represents a script.
 *   If FALSE, then this represents a program.
 * @param code
 *   The code returned by the executed program or script.
 */
#ifndef _di_controller_rule_error_print_execute_not_found_
  extern void controller_rule_error_print_execute_not_found(const fll_error_print_t output, const bool script_is, const f_string_t name) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_execute_not_found_

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
 * @param type
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_pause
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_resume
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If bit controller_rule_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param thread_data
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The rule to process.
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
  extern f_status_t controller_rule_execute(const uint8_t type, const uint8_t options, controller_thread_data_t thread_data, controller_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_execute_

/**
 * Perform an execution of the given rule in the foreground.
 *
 * @param type
 *   The item type code.
 * @param action
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param program
 *   The program to use (such as "bash").
 * @param arguments
 *   The arguments to pass to the program.
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If bit controller_rule_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param execute_set
 *   The execute parameter and as settings.
 * @param thread_data
 *   The thread data.
 * @param rule
 *   The rule to process.
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
#ifndef _di_controller_rule_execute_foreground_
  extern f_status_t controller_rule_execute_foreground(const uint8_t type, const controller_rule_action_t action, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_thread_data_t thread_data, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_execute_foreground_

/**
 * Perform an execution of the given rule in the foreground or background and creating a PID file.
 *
 * When this is synchronous, this will wait for the PID file to be generated before continuing.
 * When this is asynchronous, this will continue on adding the rule id and action to the asynchronous list.
 *
 * @param type
 *   The item type code.
 * @param action
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill
 *   - controller_rule_action_type_reload
 *   - controller_rule_action_type_restart
 *   - controller_rule_action_type_start
 *   - controller_rule_action_type_stop
 * @param program
 *   The program to use (such as "bash").
 * @param arguments
 *   The arguments to pass to the program.
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If bit controller_rule_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param execute_set
 *   The execute parameter and as settings.
 * @param thread
 *   The thread data.
 * @param asynchronous
 *   Holds the current asynchronous thread information if this is being run from within one.
 *   Set to NULL when this is not being called from within an asynchronous thread.
 *
 * @return
 *   F_none on success.
 *   F_busy on successful execute in asynchronous mode (executed process may or may not fail later on).
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_pid_with_
  extern f_status_t controller_rule_execute_pid_with(const uint8_t type, const controller_rule_action_t action, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_thread_data_t thread_data, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_execute_pid_with_

/**
 * Search the already loaded rules to see if one is found.
 *
 * Looks up the rules starting from the end so that the latest loaded version of any given rule is found and used first.
 * The rule thread should be locked before calling this to ensure the rule is not loaded after this search.
 *
 * This does not do any locking or unlocking, be sure to lock appropriately before and after calling this.
 *
 * @param rule_id
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 * @param thread_data
 *   The thread data.
 *
 * @return
 *   If found, a valid location within the setting.rules array.
 *   If not found, then setting.rules.used is returned.
 */
#ifndef _di_controller_rule_find_loaded_
  extern f_array_length_t controller_rule_find_loaded(const f_string_static_t rule_id, controller_thread_data_t thread_data) f_gcc_attribute_visibility_internal;
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
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_string_append()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_rule_id_construct_
  extern f_status_t controller_rule_id_construct(const controller_data_t data, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t *id) f_gcc_attribute_visibility_internal;
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
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see controller_rule_action_read()
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_rule_item_read_
  extern f_status_t controller_rule_item_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item) f_gcc_attribute_visibility_internal;
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
  extern f_status_t controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_items_increase_by_

/**
 * Get a string representing the rule setting limit type.
 *
 * @param type
 *   The rule setting limit type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_setting_limit_type_name_
  extern f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type) f_gcc_attribute_visibility_internal;
#endif // di_controller_rule_setting_limit_type_name_

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
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *   Errors (with error bit) from: fll_path_canonical().
 *
 * @see f_file_stat()
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 * @see f_string_append()
 * @see f_string_dynamic_terminate_after()
 * @see fll_path_canonical()
 */
#ifndef _di_controller_rule_path_
  extern f_status_t controller_rule_path(const controller_data_t data, const controller_setting_t setting, const f_string_static_t path_directory, const f_string_static_t path_name, f_string_dynamic_t *path) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_path_

/**
 * Synchronously process and execute the given rule by the rule id.
 *
 * Any dependent rules are loaded and executed as per "need", "want", and "wish" rule settings.
 * All dependent rules must be already loaded, this function will not load any rules.
 *
 * This function is recursively called for each "need", "want", and "wish", and has a max recursion length of the max size of the f_array_lengths_t array.
 *
 * @param rule
 *   The rule information at the time the rule process started.
 * @param at_process
 *   The position within the processs array representing this rule process.
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
 * @param thread_data
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 */
#ifndef _di_controller_rule_process_
  extern f_status_t controller_rule_process(const controller_rule_t rule, const f_array_length_t at_process, const uint8_t action, const uint8_t options, controller_thread_data_t thread_data, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_process_

/**
 * Asynchronously process and execute the given rule by the rule id.
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
 * @param thread_data
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_none on success.
 *   F_signal on (exit) signal received.
 *
 *   Errors (with error bit) from: controller_asynchronouss_increase().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_thread_create().
 */
#ifndef _di_controller_rule_process_asynchronous_
  extern f_status_t controller_rule_process_asynchronous(const f_array_length_t index, const uint8_t action, const uint8_t options, controller_thread_data_t thread_data, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_process_asynchronous_

/**
 * Read the rule file, extracting all valid items.
 *
 * @param rule_id
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 * @param thread_data
 *   The thread data.
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
 * @see f_string_dynamic_partial_append().
 * @see f_string_dynamic_partial_append_nulless().
 * @see f_string_dynamic_terminate_after().
 * @see fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_status_t controller_rule_read(const f_string_static_t rule_id, controller_thread_data_t thread_data, controller_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
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
 * @param setting
 *   The controller settings data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *
 * @return
 *    F_none on success.
 *    F_valid_not (with error bit) on success but there were one or more invalid settings encountered.
 *
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_rip_nulless().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *   Errors (with error bit) from: f_string_maps_increase().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *   Errors (with error bit) from: fll_path_canonical().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase()
 * @see f_string_maps_increase()
 * @see fl_string_dynamic_rip_nulless()
 * @see fll_fss_extended_read()
 * @see fll_path_canonical()
 */
#ifndef _di_controller_rule_setting_read_
  extern f_status_t controller_rule_setting_read(const controller_data_t data, const controller_setting_t setting, controller_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_setting_read_

/**
 * Perform a simulated execution of the given rule.
 *
 * This simply prints information about the rule.
 *
 * This automatically sets the rule's status to F_complete.
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
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_rule_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_rule_option_asynchronous, then run asynchronously.
 * @param thread_data
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The rule to process.
 */
#ifndef _di_controller_rule_simulate_
  extern void controller_rule_simulate(const uint8_t action, const uint8_t options, controller_thread_data_t thread_data, controller_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_simulate_

/**
 * Wait until all currently running asynchronous execution threads are complete.
 *
 * @param thread
 *   The thread data.
 */
#ifndef _di_controller_rule_wait_all_
  extern void controller_rule_wait_all(controller_thread_t *thread) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_wait_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h

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
  extern f_string_static_t controller_rule_action_method_name(const uint8_t type) f_attribute_visibility_internal;
#endif // _di_controller_rule_action_method_name_

/**
 * Find the location of the Rule by the Rule alias.
 *
 * @param alias
 *   The Rule alias to find.
 * @param rules
 *   The rules to search through.
 * @param at
 *   The index the rule was found at.
 *   (optional) Set to NULL to disable.
 *
 * @return
 *   F_none on success, but the id.used is 0.
 *   F_true on success and rule was found, index is updated.
 *   F_false on success and rule was not found.
 */
#ifndef _di_controller_rule_find_
  extern f_status_t controller_rule_find(const f_string_static_t alias, const controller_rules_t rules, f_array_length_t *at) f_attribute_visibility_internal;
#endif // _di_controller_rule_find_

/**
 * Read the parameters for some rule action.
 *
 * The object and content ranges are merged together (in that order) as the action parameters.
 *
 * @param global
 *   The global data.
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
  extern f_status_t controller_rule_parameters_read(const controller_global_t global, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) f_attribute_visibility_internal;
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
  extern f_string_static_t controller_rule_action_type_name(const uint8_t type) f_attribute_visibility_internal;
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
  extern f_status_t controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t *actions) f_attribute_visibility_internal;
#endif // _di_controller_rule_actions_increase_by_

/**
 * Read the content within the buffer, processing the action (or a set of within a list) for the given item.
 *
 * This will automatically increase the size of the actions array as needed.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param global
 *   The global data.
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
  extern f_status_t controller_rule_action_read(const bool is_normal, const controller_global_t global, const uint8_t type, const uint8_t method, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) f_attribute_visibility_internal;
#endif // _di_controller_rule_action_read_

/**
 * Copy a rule, allocating new space as necessary.
 *
 * This does not do any locking or unlocking for the rule data, be sure to lock appropriately before and after calling this.
 *
 * @param source
 *   The source rule to copy from.
 * @param destination
 *   The destination rule to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_capability_copy().
 *   Errors (with error bit) from: f_control_group_copy().
 *   Errors (with error bit) from: f_limit_sets_copy().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamics_append().
 *   Errors (with error bit) from: f_string_maps_append().
 *   Errors (with error bit) from: f_type_int32s_append().
 *
 *  @see f_capability_copy()
 *  @see f_control_group_copy()
 *  @see f_limit_sets_append()
 *  @see f_string_dynamic_append()
 *  @see f_string_dynamics_append()
 *  @see f_string_maps_append()
 *  @see f_type_int32s_append()
 */
#ifndef _di_controller_rule_copy_
  extern f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination) f_attribute_visibility_internal;
#endif // _di_controller_rule_copy_

/**
 * Print generic error/warning information.
 *
 * This is essentially a wrapper to fll_error_print() that includes locking.
 *
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
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 *
 * @see fll_error_print()
 * @see controller_entry_error_print_cache()
 */
#ifndef _di_controller_rule_error_print_
  extern void controller_rule_error_print(const fll_error_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const bool item, controller_thread_t *thread) f_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * This neither locks the thread nor does it check to see if output is enabled or disabled.
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
#ifndef _di_controller_rule_error_print_cache_
  extern void controller_rule_error_print_cache(const fll_error_print_t output, const controller_cache_action_t cache, const bool item) f_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_cache_

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
 * @see controller_rule_error_print_cache()
 */
#ifndef _di_controller_rule_item_error_print_
  extern void controller_rule_item_error_print(const fll_error_print_t output, const controller_cache_action_t cache, const bool item, controller_thread_t *thread) f_attribute_visibility_internal;
#endif // _di_controller_rule_item_error_print_

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
#ifndef _di_controller_rule_item_error_print_execute_
  extern void controller_rule_item_error_print_execute(const fll_error_print_t output, const bool script_is, const f_string_t name, const int code, const f_status_t status) f_attribute_visibility_internal;
#endif // _di_controller_rule_item_error_print_execute_

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
#ifndef _di_controller_rule_item_error_print_execute_not_found_
  extern void controller_rule_item_error_print_execute_not_found(const fll_error_print_t output, const bool script_is, const f_string_t name) f_attribute_visibility_internal;
#endif // _di_controller_rule_item_error_print_execute_not_found_

/**
 * Print an error or warning message related to need/want/wish settings of some rule.
 *
 * @param output
 *   The error or warning output structure.
 * @param need_want_wish
 *   The appropriate string, such as "needs", "wants", or "wishes for" to output when describing this error/warning.
 *   This string is expected to already be "safe" (no control characters, etc..).
 * @param value
 *   The value that is the error or warning.
 * @param why
 *   A short explanation on why this is an error or warning.
 */
#ifndef _di_controller_rule_item_error_print_need_want_wish_
  extern void controller_rule_item_error_print_need_want_wish(const fll_error_print_t output, const f_string_t need_want_wish, const f_string_t value, const f_string_t why) f_attribute_visibility_internal;
#endif // _di_controller_rule_item_error_print_need_want_wish_

/**
 * Print an error or warning message about some rule not being loaded.
 *
 * @param output
 *   The error or warning output structure.
 * @param alias
 *   The rule alias of the rule that is not loaded.
 */
#ifndef _di_controller_rule_item_error_print_rule_not_loaded_
  extern void controller_rule_item_error_print_rule_not_loaded(const fll_error_print_t output, const f_string_t alias) f_attribute_visibility_internal;
#endif // _di_controller_rule_item_error_print_rule_not_loaded_

/**
 * Print an error or warning message about some rule not having the pid file information.
 *
 * @param output
 *   The error or warning output structure.
 * @param alias
 *   The rule alias of the rule that is missing the pid file designation.
 */
#ifndef _di_controller_rule_action_error_missing_pid_
  extern void controller_rule_action_error_missing_pid(const fll_error_print_t output, const f_string_t alias) f_attribute_visibility_internal;
#endif // _di_controller_rule_action_error_missing_pid_

/**
 * Perform an execution of the given rule.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * @param action
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
 *   Process options to consider when executing.
 *   If bit controller_process_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param global
 *   The global data.
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *   F_ignore if the rule is unknown and nothing can be done.
 *
 *   F_failure (with error bit) if failed to execute.
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   On success and the rule is run synchronously, then the individual status for the rule is set to F_complete.
 *   On success and the rule is run asynchronously, then the individual status for the rule is set to F_busy.
 *   On failure, the individual status for the rule is set to an appropriate error status.
 */
#ifndef _di_controller_rule_execute_
  extern f_status_t controller_rule_execute(const uint8_t action, const uint8_t options, const controller_global_t global, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_rule_execute_

/**
 * Perform an execution of the given rule in the foreground.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * @param type
 *   The item type ID.
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
 *   Process options to consider when executing.
 *   If bit controller_process_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param global
 *   The global data.
 * @param execute_set
 *   The execute parameter and as settings.
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_foreground_
  extern f_status_t controller_rule_execute_foreground(const uint8_t type, const controller_rule_action_t action, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, const controller_global_t global, controller_execute_set_t * const execute_set, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_rule_execute_foreground_

/**
 * Perform an execution of the given rule in the foreground or background and creating a PID file.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * When this is synchronous, this will wait for the PID file to be generated before continuing.
 * When this is asynchronous, this will continue on adding the rule id and action to the asynchronous list.
 *
 * @param pid_file
 *   The path to the PID file.
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
 *   Process options to consider when executing.
 *   If bit controller_process_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param with
 *   The "with" option flags.
 * @param global
 *   The global data.
 * @param execute_set
 *   The execute parameter and as settings.
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *   F_file_found (with error bit) if the PID file already exists.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_pid_with_
  extern f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const controller_rule_action_t action, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, const uint8_t with, const controller_global_t global, controller_execute_set_t * const execute_set, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_rule_execute_pid_with_

/**
 * Construct an id from two distinct strings found within a single given source.
 *
 * @param global
 *   The global data.
 * @param source
 *   The source string that both the directory and basename are copied from.
 * @param directory
 *   A range within the source representing the directory part of a rule id.
 * @param basename
 *   A range within the source representing the basename part of a rule id.
 * @param alias
 *   The constructed alias.
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
  extern f_status_t controller_rule_id_construct(const controller_global_t global, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t *alias) f_attribute_visibility_internal;
#endif // _di_controller_rule_id_construct_

/**
 * Check to see if the given Rule has status F_known_not for the given Rule Action.
 *
 * The global Rule status is checked for error and any errors on the global Rule status will result in F_false.
 *
 * @param action
 *   The Rule Action type.
 * @param rule
 *   The Rule.
 *
 * @return
 *   F_true on available (status is F_known_not).
 *   F_false on unavailable.
 */
#ifndef _di_controller_rule_status_is_available_
  extern f_status_t controller_rule_status_is_available(const uint8_t action, const controller_rule_t rule) f_attribute_visibility_internal;
#endif // _di_controller_rule_status_is_available_

/**
 * Check to see if the given Rule has status is designated as an error for the given Rule Action.
 *
 * The global Rule status is checked for error and any errors on the global Rule status will result in F_true.
 *
 * @param action
 *   The Rule Action type.
 * @param rule
 *   The Rule.
 *
 * @return
 *   F_true if status represents an error.
 *   F_false if status does not represent an error.
 */
#ifndef _di_controller_rule_status_is_error_
  extern f_status_t controller_rule_status_is_error(const uint8_t action, const controller_rule_t rule) f_attribute_visibility_internal;
#endif // _di_controller_rule_status_is_error_

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param global
 *   The global data.
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
  extern f_status_t controller_rule_item_read(const bool is_normal, const controller_global_t global, controller_cache_t *cache, controller_rule_item_t *item) f_attribute_visibility_internal;
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
  extern f_string_static_t controller_rule_item_type_name(const uint8_t type) f_attribute_visibility_internal;
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
  extern f_status_t controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) f_attribute_visibility_internal;
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
  extern f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type) f_attribute_visibility_internal;
#endif // di_controller_rule_setting_limit_type_name_

/**
 * Process and execute the given rule.
 *
 * Any dependent rules are processed and executed as per "need", "want", and "wish" rule settings.
 * All dependent rules must be already loaded, this function will not load any rules.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * This function is recursively called for each "need", "want", and "wish", and has a max recursion length of the max size of the f_array_lengths_t array.
 *
 * The rule status will be updated by this function.
 *
 * @param global
 *   The global data.
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on (exit) signal received.
 *   F_failure on execution failure.
 *
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   Errors (with error bit) from: controller_lock_read().
 *   Errors (with error bit) from: controller_lock_write().
 */
#ifndef _di_controller_rule_process_
  extern f_status_t controller_rule_process(const controller_global_t global, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_rule_process_

/**
 * Synchronously or asynchronously begin processing some rule.
 *
 * @param options_force
 *   Force the given process options, only supporting a subset of process options.
 *
 *   If controller_process_option_asynchronous, then asynchronously execute.
 *   If not controller_process_option_asynchronous, then synchronously execute.
 * @param alias_rule
 *   The alias of the rule, such as "boot/init".
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   The process options to pass to the process.
 * @param type
 *   The process type, such as controller_process_type_entry.
 * @param stack
 *   A stack representing the processes already running in this rule process dependency tree.
 *   This is used to prevent circular dependencies.
 * @param global
 *   The global data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_none on success.
 *   F_busy on success and the process was found to already be running (nothing to do).
 *   F_signal on (exit) signal received.
 *
 *   F_found_not (with error bit) if unable to for a process for the given rule id.
 *   F_recurse (with error bit) on recursion error (the process is already on the process stack).
 *
 *   Status from: controller_rule_process().
 *
 *   Errors (with error bit) from: controller_rule_process().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_thread_create().
 *
 * @see controller_rule_process()
 * @see f_string_dynamic_append()
 * @see f_thread_create()
 */
#ifndef _di_controller_rule_process_begin_
  extern f_status_t controller_rule_process_begin(const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_array_lengths_t stack, const controller_global_t global, const controller_cache_t cache) f_attribute_visibility_internal;
#endif // _di_controller_rule_process_begin_

/**
 * Helper for calling controller_rule_process().
 *
 * This does all the preparation work that needs to be synchronously performed within the same thread.
 * This will copy the rule by the alias to the process structure.
 *
 * @param options_force
 *   Force the given process options, only supporting a subset of process options.
 *
 *   If controller_process_option_asynchronous, then asynchronously execute.
 *   If not controller_process_option_asynchronous, then synchronously execute.
 * @param process
 *   The process data.
 *
 * @return
 *   F_none on success.
 *   F_found on the process was found to already be running (nothing to do).
 *   F_process_not if the process was not executed because it is a "consider" Action.
 *   F_signal on (exit) signal received.
 *
 *   F_found_not (with error bit) if unable to for a process for the given rule id.
 *
 *   Status from: controller_rule_process().
 *
 *   Errors (with error bit) from: controller_rule_copy().
 *   Errors (with error bit) from: controller_rule_process().
 *
 * @see controller_rule_copy()
 * @see controller_rule_process()
 * @see controller_rule_process_begin()
 */
#ifndef _di_controller_rule_process_do_
  extern f_status_t controller_rule_process_do(const uint8_t options_force, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_rule_process_do_

/**
 * Read the rule file, extracting all valid items.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param alias
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 * @param global
 *   The global data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *   The rule status will be updated by this function.
 *
 * @return
 *   F_none on success.
 *
 *   Simplified status (with error bit) from controller_status_simplify_error() on failure.
 *
 * @see controller_rule_items_increase_by().
 * @see controller_rule_item_read().
 * @see f_fss_count_lines().
 * @see fl_fss_apply_delimit().
 * @see f_string_dynamic_partial_append().
 * @see f_string_dynamic_partial_append_nulless().
 * @see f_string_dynamic_terminate_after().
 * @see fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_status_t controller_rule_read(const bool is_normal, const f_string_static_t alias, controller_global_t global, controller_cache_t *cache, controller_rule_t *rule) f_attribute_visibility_internal;
#endif // _di_controller_rule_read_

/**
 * Read the content within the buffer, extracting all valid settings.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * Errors from this are not considered fatal, but the first error code encountered is returned.
 * Memory failure errors are always immediately returned.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param global
 *   The global data.
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
  extern f_status_t controller_rule_setting_read(const bool is_normal, const controller_global_t global, const controller_setting_t setting, controller_cache_t *cache, controller_rule_t *rule) f_attribute_visibility_internal;
#endif // _di_controller_rule_setting_read_

/**
 * Perform a simulated execution of the given rule.
 *
 * This simply prints information about the rule.
 *
 * This automatically sets the rule's status to F_complete.
 *
 * @param rule
 *   The rule to process.
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_process_option_simulate, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_process_option_asynchronous, then run asynchronously.
 * @param global
 *   The global data.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_rule_validate_
  extern void controller_rule_validate(const controller_rule_t rule, const uint8_t action, const uint8_t options, const controller_global_t global, controller_cache_t *cache) f_attribute_visibility_internal;
#endif // _di_controller_rule_validate_

/**
 * Wait until all currently running Rule processes are complete.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 *   This is ignored when caller is not NULL.
 * @param global
 *   The global data.
 * @param required
 *   If TRUE, then only process required rules and if a required rule has failed, return.
 *   If FALSE, process all waits, returning normally.
 * @param caller
 *   The process representing the caller so that the process never waits on itself.
 *   (optional) set to 0 when calling from a thread that is not running/executing any process.
 *   Failure to set this to the process on a thread running/executing a process will likely result in a deadlock.
 *
 * @return
 *    F_none on success.
 *    F_data_not on success and nothing to do.
 *    F_require on success, but a required rule has not been run yet.
 *    F_signal on (exit) signal received.
 *
 *    F_require (with error bit set) if a required process is in failed status when required is TRUE.
 */
#ifndef _di_controller_rule_wait_all_
  extern f_status_t controller_rule_wait_all(const bool is_normal, const controller_global_t global, const bool required, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_rule_wait_all_

/**
 * Wait until all currently running Rule processes are complete for some process type.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param global
 *   The global data.
 * @param required
 *   If TRUE, then only process required rules and if a required rule has failed, return.
 *   If FALSE, process all waits, returning normally.
 * @param caller
 *   The process representing the caller so that the process never waits on itself.
 *   (optional) set to 0 when calling from a thread that is not running/executing any process.
 *   Failure to set this to the process on a thread running/executing a process will likely result in a deadlock.
 *
 * @return
 *
 *   Success from controller_rule_wait_all().
 *
 *   Errors (with error bit) from: controller_rule_wait_all().
 *
 * @see controller_rule_wait_all()
 */
#ifndef _di_controller_rule_wait_all_process_type_
  extern f_status_t controller_rule_wait_all_process_type(const uint8_t type, const controller_global_t global, const bool required, controller_process_t *caller) f_attribute_visibility_internal;
#endif // _di_controller_rule_wait_all_process_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h

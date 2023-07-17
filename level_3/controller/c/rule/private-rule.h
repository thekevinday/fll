/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_rule_h
#define _PRIVATE_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Special strings used for rules.
 */
#ifndef _di_controller_rule_string_s_
  #define CONTROLLER_rule_needed_s "needed"
  #define CONTROLLER_rule_wanted_s "wanted"
  #define CONTROLLER_rule_wished_s "wished for"

  #define CONTROLLER_rule_needed_s_length 6
  #define CONTROLLER_rule_wanted_s_length 6
  #define CONTROLLER_rule_wished_s_length 10

  extern const f_string_static_t controller_rule_needed_s;
  extern const f_string_static_t controller_rule_wanted_s;
  extern const f_string_static_t controller_rule_wished_s;
#endif // _di_controller_rule_print_string_s_

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
  extern f_string_static_t controller_rule_action_method_name(const uint8_t type) F_attribute_visibility_internal_d;
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
  extern f_status_t controller_rule_find(const f_string_static_t alias, const controller_rules_t rules, f_number_unsigned_t *at) F_attribute_visibility_internal_d;
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
 * @param action
 *   The rule action.
 * @param state
 *   The state data for passing to fl_iki_read().
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_iki_datas_increase_by().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *   Errors (with error bit) from: f_string_dynamics_increase_by().
 *   Errors (with error bit) from: fl_iki_read().
 *
 * @see f_fss_count_lines()
 * @see f_iki_datas_increase_by()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase()
 * @see f_string_dynamics_increase_by()
 * @see fl_iki_read()
 */
#ifndef _di_controller_rule_parameters_read_
  extern f_status_t controller_rule_parameters_read(const controller_global_t global, const f_string_static_t buffer, f_string_range_t * const object, f_string_ranges_t * const content, controller_rule_action_t * const action, f_state_t * const state) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_parameters_read_

/**
 * Convert the action type to an action execute type.
 *
 * @param type
 *   The action type to convert from.
 *
 * @return
 *   The converted action type, converted into an action execute type.
 *
 *   The code controller_rule_action_execute_type__enum_size_e is returned for unknown types.
 */
#ifndef _di_controller_rule_action_type_to_action_execute_type_
  extern uint8_t controller_rule_action_type_to_action_execute_type(const uint8_t type) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_action_type_to_action_execute_type_

/**
 * Read the content within the buffer, processing the action (or a set of within a list) for the given item.
 *
 * This will automatically increase the size of the actions array as needed.
 *
 * @param global
 *   The global data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
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
  extern f_status_t controller_rule_action_read(const controller_global_t global, const bool is_normal, const uint8_t type, const uint8_t method, controller_cache_t * const cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) F_attribute_visibility_internal_d;
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
 *   Errors (with error bit) from: f_iki_datas_append_all().
 *   Errors (with error bit) from: f_int32s_append_all().
 *   Errors (with error bit) from: f_limit_sets_copy().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamics_append_all().
 *   Errors (with error bit) from: f_string_maps_append_all().
 *
 *  @see f_capability_copy()
 *  @see f_control_group_copy()
 *  @see f_iki_datas_append_all()
 *  @see f_int32s_append_all()
 *  @see f_limit_sets_append()
 *  @see f_string_dynamic_append()
 *  @see f_string_dynamics_append_all()
 *  @see f_string_maps_append_all()
 */
#ifndef _di_controller_rule_copy_
  extern f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_copy_

/**
 * Perform an execution of the given rule.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * @param global
 *   The global data.
 * @param action
 *   The action to perform based on the action type codes.
 *
 *   Only subset of the action type codes are supported:
 *   - controller_rule_action_type_kill_e
 *   - controller_rule_action_type_pause_e
 *   - controller_rule_action_type_reload_e
 *   - controller_rule_action_type_restart_e
 *   - controller_rule_action_type_resume_e
 *   - controller_rule_action_type_start_e
 *   - controller_rule_action_type_stop_e
 * @param options
 *   Process options to consider when executing.
 *   If bit controller_process_option_simulate_d, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_ignore if the rule is unknown and nothing can be done.
 *
 *   F_failure (with error bit) if failed to execute.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   On success and the rule is run synchronously, then the individual status for the rule is set to F_complete.
 *   On success and the rule is run asynchronously, then the individual status for the rule is set to F_busy.
 *   On failure, the individual status for the rule is set to an appropriate error status.
 */
#ifndef _di_controller_rule_execute_
  extern f_status_t controller_rule_execute(const controller_global_t global, const uint8_t action, const uint8_t options, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_execute_

/**
 * Perform an execution of the given rule in the foreground.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * @param type
 *   The item type code.
 * @param program
 *   The program to use (such as "bash").
 * @param arguments
 *   The arguments to pass to the program.
 * @param options
 *   Process options to consider when executing.
 *   If bit controller_process_option_simulate_d, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param execute_set
 *   The execute parameter and as settings.
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_foreground_
  extern f_status_t controller_rule_execute_foreground(const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_process_t * const process) F_attribute_visibility_internal_d;
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
 * @param program
 *   The program to use (such as "bash").
 * @param arguments
 *   The arguments to pass to the program.
 * @param options
 *   Process options to consider when executing.
 *   If bit controller_process_option_simulate_d, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 * @param with
 *   The "with" option flags.
 * @param execute_set
 *   The execute parameter and as settings.
 * @param process
 *   The process data for processing this rule.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *
 *   F_file_found (with error bit) if the PID file already exists.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   Errors (with error bit) from: fll_execute_program().
 *
 * @see fll_execute_program()
 */
#ifndef _di_controller_rule_execute_pid_with_
  extern f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, const uint8_t with, controller_execute_set_t * const execute_set, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_execute_pid_with_

/**
 * Determine whether or not an execute rule should be re-run, applying a delay as requested.
 *
 * @param action
 *   The action type.
 * @param process
 *   The process data for processing this rule.
 * @param item
 *   The rule item being executed.
 *
 * @return
 *   A positive number to designate re-run.
 *   0 to designate do not re-run.
 *   -1 to designate an error from nanosleep(), with errno set to values like:
 *     - EFAULT: Designates that there was a problem copying information from user space.
 *     - EINTR:  Consider this having returned F_interrupt.
 *     - EINVAL: Consider this having returned F_status_set_error(F_parameter);
 *   -2 to designate exit due to signal/disabled thread.
 */
#ifndef _di_controller_rule_execute_rerun_
  extern int8_t controller_rule_execute_rerun(const uint8_t action, controller_process_t * const process, controller_rule_item_t * const item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_execute_rerun_

/**
 * Expand a single IKI variable into the buffer.
 *
 * @param
 *   The global data.
 * @param action
 *   The rule action data.
 * @param process
 *   The process information.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_rule_expand_iki().
 *
 *   @see controller_rule_expand_iki()
 */
#ifndef _di_controller_rule_expand_
  extern f_status_t controller_rule_expand(const controller_global_t global, const controller_rule_action_t action, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_expand_

/**
 * Expand a single IKI variable into the buffer.
 *
 * @param process
 *   The process information.
 * @param source
 *   The source buffer holding the string referenced by the IKI data.
 * @param vocabulary
 *   The range representing the IKI variable vocabulary.
 * @param content
 *   The range representing the IKI variable content.
 * @param destination
 *   The buffer to expand into.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_environment_get().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 *   @see f_environment_get()
 *   @see f_string_dynamic_append()
 */
#ifndef _di_controller_rule_expand_iki_
  extern f_status_t controller_rule_expand_iki(controller_process_t * const process, const f_string_static_t source, const f_string_range_t vocabulary, const f_string_range_t content, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_expand_iki_

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
 *
 * @see f_string_append()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_controller_rule_id_construct_
  extern f_status_t controller_rule_id_construct(const controller_global_t global, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t * const alias) F_attribute_visibility_internal_d;
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
  extern f_status_t controller_rule_status_is_available(const uint8_t action, const controller_rule_t rule) F_attribute_visibility_internal_d;
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
  extern f_status_t controller_rule_status_is_error(const uint8_t action, const controller_rule_t rule) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_status_is_error_

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param global
 *   The global data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   The processed item.
 *
 * @return
 *   F_none on success.
 *   F_valid_not (with error bit) on invalid data.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see controller_rule_action_read()
 * @see f_fss_count_lines()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_controller_rule_item_read_
  extern f_status_t controller_rule_item_read(const controller_global_t global, const bool is_normal, controller_cache_t * const cache, controller_rule_item_t * const item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_read_

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
  extern f_status_t controller_rule_items_increase_by(const f_number_unsigned_t amount, controller_rule_items_t * const items) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_items_increase_by_

/**
 * Process and execute the given rule.
 *
 * Any dependent rules are processed and executed as per "need", "want", and "wish" rule settings.
 * All dependent rules must be already loaded, this function will not load any rules.
 *
 * This requires that a read lock be set on process->lock before being called.
 *
 * This function is recursively called for each "need", "want", and "wish", and has a max recursion length of the max size of the f_number_unsigneds_t array.
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
 *   F_failure on execution failure.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_lock (with error bit) if failed to re-establish read lock on process->lock while returning.
 *
 *   Errors (with error bit) from: controller_lock_read().
 *   Errors (with error bit) from: controller_lock_write().
 */
#ifndef _di_controller_rule_process_
  extern f_status_t controller_rule_process(const controller_global_t global, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_process_

/**
 * Synchronously or asynchronously begin processing some rule.
 *
 * @param global
 *   The global data.
 * @param options_force
 *   Force the given process options, only supporting a subset of process options.
 *
 *   If controller_process_option_asynchronous_d, then asynchronously execute.
 *   If not controller_process_option_asynchronous_d, then synchronously execute.
 * @param alias_rule
 *   The alias of the rule, such as "boot/init".
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   The process options to pass to the process.
 * @param type
 *   The process type, such as controller_process_type_entry_e.
 * @param stack
 *   A stack representing the processes already running in this rule process dependency tree.
 *   This is used to prevent circular dependencies.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @return
 *   F_none on success.
 *   F_busy on success and the process was found to already be running (nothing to do).
 *
 *   F_found_not (with error bit) if unable to for a process for the given rule id.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
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
  extern f_status_t controller_rule_process_begin(const controller_global_t global, const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_number_unsigneds_t stack, const controller_cache_t cache) F_attribute_visibility_internal_d;
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
 *   If controller_process_option_asynchronous_d, then asynchronously execute.
 *   If not controller_process_option_asynchronous_d, then synchronously execute.
 * @param process
 *   The process data.
 *
 * @return
 *   F_none on success.
 *   F_found on the process was found to already be running (nothing to do).
 *   F_process_not if the process was not executed because it is a "consider" Action.
 *
 *   F_found_not (with error bit) if unable to for a process for the given rule id.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
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
  extern f_status_t controller_rule_process_do(const uint8_t options_force, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_process_do_

/**
 * Read the rule file, extracting all valid items.
 *
 * @param global
 *   The global data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param alias
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/rules/example/my.rule" would have a rule id of "example/my".
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param entry
 *   The entry containing the rule being read.
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
 * @see f_fss_apply_delimit().
 * @see f_string_dynamic_partial_append().
 * @see f_string_dynamic_partial_append_nulless().
 * @see fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_status_t controller_rule_read(const controller_global_t global, const bool is_normal, const f_string_static_t alias, controller_cache_t * const cache, controller_entry_t * const entry, controller_rule_t * const rule) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_read_

/**
 * Process a number from a rule file, incrementing index as necessary.
 *
 * This prints error messages as necessary.
 *
 * This is intended to be called by controller_rule_action_read().
 *
 * @param global
 *   The global data.
 * @param name
 *   The name representing the value whose number is being processed.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param index
 *   The position within the content action array for some rule to process.
 * @param number
 *   The processed number will be saved here.
 *
 * @return
 *   F_none on success.
 *
 *   F_valid_not (with error bit) on failure due to invalid value.
 *
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_signed_detect().
 *
 * @see controller_rule_action_read()
 * @see fl_conversion_dynamic_partial_to_signed_detect()
 */
#ifndef _di_controller_rule_action_read_rerun_number_
  extern f_status_t controller_rule_action_read_rerun_number(const controller_global_t global, const f_string_t name, controller_cache_t * const cache, f_number_unsigned_t * const index, f_number_unsigned_t * const number) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_action_read_rerun_number_

/**
 * Read the content within the buffer, extracting all valid settings.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * Errors from this are not considered fatal, but the first error code encountered is returned.
 * Memory failure errors are always immediately returned.
 *
 * @param global
 *   The global data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param setting
 *   The controller settings data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *
 * @return
 *    F_none on success.
 *
 *    F_valid_not (with error bit) on success but there were one or more invalid settings encountered.
 *
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *   Errors (with error bit) from: f_string_maps_increase().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 *   Errors (with error bit) from: controller_path_canonical_relative().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase()
 * @see f_string_maps_increase()
 * @see f_rip_dynamic_partial_nulless()
 * @see fll_fss_extended_read()
 *
 * @see controller_path_canonical_relative()
 */
#ifndef _di_controller_rule_setting_read_
  extern f_status_t controller_rule_setting_read(const controller_global_t global, const bool is_normal, const controller_setting_t setting, controller_cache_t * const cache, controller_rule_t * const rule) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_setting_read_

/**
 * Perform a simulated execution of the given rule.
 *
 * This simply prints information about the rule.
 *
 * This automatically sets the rule's status to F_complete.
 *
 * @param global
 *   The global data.
 * @param rule
 *   The rule to process.
 * @param action
 *   The action to perform based on the action type codes.
 * @param options
 *   A number using bits to represent specific boolean options.
 *   If no bits set, then operate normally in a synchronous manner.
 *   If bit controller_process_option_simulate_d, then the rule execution is in simulation mode (printing a message that the rule would be executed but does not execute the rule).
 *   If bit controller_process_option_asynchronous_d, then run asynchronously.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_rule_validate_
  extern void controller_rule_validate(const controller_global_t global, const controller_rule_t rule, const uint8_t action, const uint8_t options, controller_cache_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_validate_

/**
 * Wait until all currently running Rule processes are complete.
 *
 * @param global
 *   The global data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 *   This is ignored when caller is not NULL.
 * @param required
 *   If TRUE, then only process required rules and if a required rule has failed, return.
 *   If FALSE, process all waits, returning normally (required rules still result in failure).
 *
 * @return
 *   F_none on success.
 *   F_data_not on success and nothing to do.
 *   F_require on success, but a required rule has not been run yet.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_require (with error bit set) if a required process is in failed status when required is TRUE.
 */
#ifndef _di_controller_rule_wait_all_
  extern f_status_t controller_rule_wait_all(const controller_global_t global, const bool is_normal, const bool required) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_wait_all_

/**
 * Wait until all currently running Rule processes are complete for some process type.
 *
 * @param global
 *   The global data.
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param required
 *   If TRUE, then only process required rules and if a required rule has failed, return.
 *   If FALSE, process all waits, returning normally.
 *
 * @return
 *   Success from controller_rule_wait_all().
 *
 *   Errors (with error bit) from: controller_rule_wait_all().
 *
 * @see controller_rule_wait_all()
 */
#ifndef _di_controller_rule_wait_all_process_type_
  extern f_status_t controller_rule_wait_all_process_type(const controller_global_t global, const uint8_t type, const bool required) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_wait_all_process_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h

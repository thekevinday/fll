/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_rule_print_h
#define _PRIVATE_rule_print_h

#ifdef __cplusplus
extern "C" {
#endif

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
 * @see controller_rule_print_error_cache()
 */
#ifndef _di_controller_rule_print_error_
  extern void controller_rule_print_error(const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const bool item, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_print_error_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * This neither locks the thread nor does it check to see if output is enabled or disabled.
 *
 * @param print
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
#ifndef _di_controller_rule_print_error_cache_
  extern void controller_rule_print_error_cache(const fl_print_t print, const controller_cache_action_t cache, const bool item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_print_error_cache_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * @param print
 *   The error or warning print structure.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 * @param status
 *   The status code representing the failure (without the error bit set).
 * @param thread
 *   The thread data.
 *
 * @see controller_rule_print_error_cache()
 */
#ifndef _di_controller_rule_item_print_error_
  extern void controller_rule_item_print_error(const fl_print_t print, const controller_cache_action_t cache, const bool item, const f_status_t status, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_print_error_

/**
 * Print an error or warning message related to the failed execution of some program or script.
 *
 * @param script_is
 *   If TRUE, then this represents a script.
 *   If FALSE, then this represents a program.
 * @param name
 *   The name of the program or script.
 * @param code
 *   The code returned by the executed program or script.
 * @param status
 *   The status code representing the failure (without the error bit set).
 * @param process
 *   The process to use.
 */
#ifndef _di_controller_rule_item_print_error_execute_
  extern void controller_rule_item_print_error_execute(const bool script_is, const f_string_t name, const f_status_t status, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_print_error_execute_

/**
 * Print an error or warning message about some rule not having the pid file information.
 *
 * @param print
 *   The error or warning output structure.
 * @param alias
 *   The rule alias of the rule that is missing the pid file designation.
 */
#ifndef _di_controller_rule_action_print_error_missing_pid_
  extern void controller_rule_action_print_error_missing_pid(const fl_print_t print, const f_string_t alias) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_action_print_error_missing_pid_

/**
 * Print an error or warning message related to need/want/wish settings of some rule.
 *
 * @param print
 *   The error or warning output structure.
 * @param need_want_wish
 *   The appropriate string, such as "needs", "wants", or "wishes for" to output when describing this error/warning.
 *   This string is expected to already be "safe" (no control characters, etc..).
 * @param value
 *   The value that is the error or warning.
 * @param why
 *   A short explanation on why this is an error or warning.
 */
#ifndef _di_controller_rule_item_print_error_need_want_wish_
  extern void controller_rule_item_print_error_need_want_wish(const fl_print_t print, const f_string_t need_want_wish, const f_string_t value, const f_string_t why) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_print_error_need_want_wish_

/**
 * Print an error or warning message about some rule not being loaded.
 *
 * @param print
 *   The error or warning output structure.
 * @param alias
 *   The rule alias of the rule that is not loaded.
 */
#ifndef _di_controller_rule_item_print_error_rule_not_loaded_
  extern void controller_rule_item_print_error_rule_not_loaded(const fl_print_t print, const f_string_t alias) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_print_error_rule_not_loaded_

/**
 * Print a message about a rule setting problem.
 *
 * This is intended to be explicitly called by controller_rule_setting_read().
 * This is intended only to be used for simple messages.
 *
 * @param print
 *   The error or warning output structure.
 * @param message
 *   The string to append to the message being printed.
 * @param index
 *   The position in the object actions cache representing the object.
 * @param line_item
 *   The current line number.
 * @param thread
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_rule_setting_read_print_error_
  extern void controller_rule_setting_read_print_error(const fl_print_t print, const f_string_t message, const f_array_length_t index, const f_array_length_t line_item, controller_thread_t *thread, controller_cache_t *cache) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_setting_read_print_error_

/**
 * Print a message about a rule setting problem, with additional messages about value.
 *
 * This is intended to be explicitly called by controller_rule_setting_read().
 * This is intended only to be used for simple messages.
 *
 * @param print
 *   The error or warning output structure.
 * @param before
 *   The string to append to the message being printed (before the value).
 * @param range
 *   The range within the cache item buffer representing the value.
 * @param after
 *   The string to append to the message being printed (after the value).
 * @param index
 *   The position in the object actions cache representing the object.
 * @param line_item
 *   The current line number.
 * @param thread
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @see controller_rule_setting_read()
 */
#ifndef _di_controller_rule_setting_read_print_error_with_range_
  extern void controller_rule_setting_read_print_error_with_range(const fl_print_t print, const f_string_t before, const f_string_range_t range, const f_string_t after, const f_array_length_t index, const f_array_length_t line_item, controller_thread_t *thread, controller_cache_t *cache) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_setting_read_print_error_with_range_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * @param global
 *   The global data.
 * @param name
 *   The Object name of the setting being populated.
 * @param name_sub
 *   (optional) A sub-name associated with the setting being populated.
 *   Set to NULL to disable.
 * @param value
 *   The value being set.
 * @param suffix
 *   An additional message to append at the end (before the final period).
 */
#ifndef _di_controller_rule_setting_read_print_value_
  extern void controller_rule_setting_read_print_value(const controller_global_t global, const f_string_t name, const f_string_t name_sub, const f_string_static_t value, const f_string_t suffix) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_setting_read_print_value_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * This handles the case where there are multiple values stored in the buffer_item at a given content_actions position.
 *
 * @param global
 *   The global data.
 * @param name
 *   The Object name of the setting being populated.
 * @param index
 *   Position within the content_actions range cache array.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_rule_setting_read_print_values_
  extern void controller_rule_setting_read_print_values(const controller_global_t global, const f_string_t name, const f_array_length_t index, controller_cache_t *cache) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_setting_read_print_values_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_print_h

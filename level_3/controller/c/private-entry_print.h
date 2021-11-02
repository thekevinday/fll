/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_entry_print_h
#define _PRIVATE_entry_print_h

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
  extern void controller_entry_action_parameters_print(FILE * const stream, const controller_entry_action_t action) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_action_parameters_print_

/**
 * Print message regarding the population of a setting when in simulation or verbose mode.
 *
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
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
#ifndef _di_controller_entry_preprocess_print_simulate_setting_value_
  extern void controller_entry_preprocess_print_simulate_setting_value(const bool is_entry, const controller_global_t global, const f_string_t name, const f_string_t name_sub, const f_string_static_t value, const f_string_t suffix) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_preprocess_print_simulate_setting_value_

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
 * @see controller_entry_print_error_cache()
 */
#ifndef _di_controller_entry_print_error_
  extern void controller_entry_print_error(const bool is_entry, const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_print_error_

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
 * @param output
 *   Designates how printing is to be performed.
 * @param cache
 *   The action cache.
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_read()
 */
#ifndef _di_controller_entry_print_error_cache_
  extern void controller_entry_print_error_cache(const bool is_entry, const fl_print_t output, const controller_cache_action_t cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_print_error_cache_

/**
 * Print a message for when an entry setting action has the incorrect number of parameters.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param global
 *   The global data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 */
#ifndef _di_controller_entry_settings_read_print_setting_requires_exactly_
  extern void controller_entry_settings_read_print_setting_requires_exactly(const bool is_entry, const controller_global_t global, const controller_cache_t cache, const f_number_unsigned_t total) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_print_setting_requires_exactly_

/**
 * Print a message for when an entry setting action is unknown.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param global
 *   The global data.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_
  extern void controller_entry_settings_read_print_setting_unknown_action(const bool is_entry, const controller_global_t global, const controller_cache_t cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_

/**
 * Print a message for when an entry setting action has an unknown value.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param global
 *   The global data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 * @param index
 *   The location in the content actions array representing the action value.
 */
#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_value_
  extern void controller_entry_settings_read_print_setting_unknown_action_value(const bool is_entry, const controller_global_t global, const controller_cache_t cache, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_entry_print_h

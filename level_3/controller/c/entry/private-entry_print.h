/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_entry_print_h
#define _PRIVATE_entry_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Special strings used for printing.
 */
#ifndef _di_controller_entry_print_string_s_
  #define CONTROLLER_entry_print_considering_s     "Considering"
  #define CONTROLLER_entry_print_failsafe_s        "failsafe"
  #define CONTROLLER_entry_print_processing_s      "Processing"
  #define CONTROLLER_entry_print_suffix_megatime_s " MegaTime (milliseconds)"

  #define CONTROLLER_entry_print_considering_s_length     11
  #define CONTROLLER_entry_print_failsafe_s_length        8
  #define CONTROLLER_entry_print_processing_s_length      10
  #define CONTROLLER_entry_print_suffix_megatime_s_length 24

  extern const f_string_static_t controller_entry_print_considering_s;
  extern const f_string_static_t controller_entry_print_failsafe_s;
  extern const f_string_static_t controller_entry_print_processing_s;
  extern const f_string_static_t controller_entry_print_suffix_megatime_s;
#endif // _di_controller_entry_print_string_s_

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
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 * @param name
 *   The Object name of the setting being populated.
 * @param name_sub
 *   A sub-name associated with the setting being populated.
 *   Set to a string with used set to 0 to not use.
 * @param value
 *   The value being set.
 * @param suffix
 *   An additional message to append at the end (before the final period).
 */
#ifndef _di_controller_entry_preprocess_print_simulate_setting_value_
  extern void controller_entry_preprocess_print_simulate_setting_value(const controller_global_t global, const bool is_entry, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_static_t suffix) F_attribute_visibility_internal_d;
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
 * Print the entry related file error, locking the print mutex during the print.
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
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 * @param thread
 *   The thread data.
 *
 * @see fll_error_file_print()
 * @see controller_entry_print_error_cache()
 */
#ifndef _di_controller_entry_print_error_file_
  extern void controller_entry_print_error_file(const bool is_entry, const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_print_error_file_

/**
 * Print a message about an entry setting problem, with additional messages about the value.
 *
 * This is intended to be explicitly called by controller_entry_settings_read().
 * This is intended only to be used for simple messages.
 *
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param print
 *   The error or warning output structure.
 * @param before
 *   The string to add to the message being printed (before the value).
 * @param range
 *   The range within the cache item buffer representing the value.
 * @param after
 *   The string to add to the message being printed (after the value).
 * @param thread
 *   The thread data.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @see controller_entry_settings_read()
 */
#ifndef _di_controller_entry_setting_read_print_error_with_range_
  extern void controller_entry_setting_read_print_error_with_range(const bool is_entry, const fl_print_t print, const f_string_t before, const f_string_range_t range, const f_string_t after, controller_thread_t * const thread, controller_cache_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_setting_read_print_error_with_range_

/**
 * Print a message for when an entry setting action has the incorrect number of parameters.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 */
#ifndef _di_controller_entry_settings_read_print_setting_requires_exactly_
  extern void controller_entry_settings_read_print_setting_requires_exactly(const controller_global_t global, const bool is_entry, const controller_cache_t cache, const f_number_unsigned_t total) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_print_setting_requires_exactly_

/**
 * Print a message for when an entry setting action is unknown.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 */
#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_
  extern void controller_entry_settings_read_print_setting_unknown_action(const controller_global_t global, const bool is_entry, const controller_cache_t cache) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_

/**
 * Print a message for when an entry setting action has an unknown value.
 *
 * @param global
 *   The global data.
 * @param is_entry
 *   If TRUE, then this loads as an entry.
 *   If FALSE, then this loads as an exit.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param total
 *   The expected number of arguments.
 * @param index
 *   The location in the content actions array representing the action value.
 */
#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_value_
  extern void controller_entry_settings_read_print_setting_unknown_action_value(const controller_global_t global, const bool is_entry, const controller_cache_t cache, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_entry_print_h

/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_controller_h
#define _PRIVATE_controller_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Rip a string fromt he source and then add a NULL after the end of the string.
 *
 * @param source
 *   The string to copy from.
 * @param destination
 *   The string to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *   Errors (with error bit) from: fl_string_dynamic_rip_nulless().
 *
 * @see f_string_dynamic_terminate_after()
 * @see fl_string_dynamic_rip_nulless()
 */
#ifndef _di_controller_string_dynamic_rip_nulless_terminated_
  extern f_status_t controller_string_dynamic_rip_nulless_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // _di_controller_string_dynamic_rip_nulless_terminated_

/**
 * Append a string and then add a NULL after the end of the string.
 *
 * @param source
 *   The string to copy from.
 * @param destination
 *   The string to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_string_dynamic_append_terminated_
  extern f_status_t controller_string_dynamic_append_terminated(const f_string_static_t from, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // _di_controller_string_dynamic_append_terminated_

/**
 * Append given range from within a string and then add a NULL after the end of the string.
 *
 * @param from
 *   The string to copy from.
 * @param range
 *   The range within the from string to copy.
 * @param destination
 *   The string to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_string_dynamic_partial_append_terminated_
  extern f_status_t controller_string_dynamic_partial_append_terminated(const f_string_static_t from, const f_string_range_t range, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // _di_controller_string_dynamic_partial_append_terminated_

/**
 * Load a file from the controller settings directory.
 *
 * @param required
 *   If TRUE, the file is required to exist and will throw an error if not found.
 *   If FALSE, the file is not required to exist and will return without error if not found.
 * @param path_prefix
 *   The path prefix, such as 'entries' from '/etc/controller/entries/default.entry'.
 * @param path_name
 *   The path name, such as 'default' from '/etc/controller/entries/default.entry'.
 * @param path_suffix
 *   The path suffix, such as 'entry' from '/etc/controller/entries/default.entry'.
 * @param path_prefix_length
 *   The length of the prefix path.
 * @param path_suffix_length
 *   The length of the suffix path.
 * @param main
 *   The main data.
 * @param cache
 *   The following within the cache is updated:
 *   - name_file: The partial path of the file is inserted.
 *   - buffer_file: The contents of the file is inserted.
 *   - timestamp: This is updated to reflect the last changed timestamp.
 *
 * @return
 *   F_none on success.
 *   F_file_found_not if required is FALSE and the file is not found.
 *
 *   Errors (with error bit) from: f_file_stat().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_file_stat()
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 * @see f_string_append()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_file_load_
  extern f_status_t controller_file_load(const bool required, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_array_length_t path_prefix_length, const f_array_length_t path_suffix_length, controller_main_t main, controller_cache_t *cache) f_attribute_visibility_internal;
#endif // _di_controller_file_load_

/**
 * Create the pid file, if possible.
 *
 * @param pid
 *   The PID (process id).
 * @param path
 *   The file path to the pid file to create.
 *
 * @return
 *   F_none on success.
 *   F_access_denied if pid file is not created due to access denied errors.
 *   F_directory_not if pid file is not created due to a parent directory is unavailable or invalid.
 *
 *   Errors (with error bit) from: f_directory_exists().
 *   Errors (with error bit) from: f_file_name_directory().
 *   Errors (with error bit) from: f_file_stream_open().
 *
 * @see f_directory_exists()
 * @see f_file_name_directory()
 * @see f_file_stream_open()
 */
#ifndef _di_controller_file_pid_create_
  f_status_t controller_file_pid_create(const pid_t pid, const f_string_static_t path) f_attribute_visibility_internal;
#endif // _di_controller_file_pid_create_

/**
 * Delete the pid file, if exists and is valid.
 *
 * This is meant to be called on exit and avoids checking status codes, returning void.
 *
 * @param pid
 *   The PID (process id).
 * @param path
 *   The file path to the pid file to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_number_not (with error bit) if the number from the pid file doesn't match the expected pid.
 *
 *   Errors (with error bit) from: f_file_stream_close().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: fl_conversion_string_to_decimal_unsigned()
 */
#ifndef _di_controller_file_pid_delete_
  f_status_t controller_file_pid_delete(const pid_t pid, const f_string_static_t path) f_attribute_visibility_internal;
#endif // _di_controller_file_pid_delete_

/**
 * Read the PID from a PID file.
 *
 * @param path
 *   The file path to the pid file to create.
 * @param pid
 *   The PID to be read.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_stream_close().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: fl_conversion_string_to_decimal_unsigned()
 */
#ifndef _di_controller_file_pid_read_
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t *pid) f_attribute_visibility_internal;
#endif // _di_controller_file_pid_read_

/**
 * Find an existing process, for the given Rule Action.
 *
 * Do not confuse this with a process in the context of a PID.
 * This is a stucture for the current processing of some rule.
 *
 * This does not do any locking or unlocking for the processs data, be sure to lock appropriately before and after calling this.
 *
 * @param action
 *   The Rule Action to find.
 * @param alias
 *   The Rule alias to find.
 * @param processs
 *   The array of processes to.
 * @param at
 *   The location within processs the id was found.
 *   (optional) Set to NULL to disable.
 *
 * @return
 *   F_none if not given a valid id to search.
 *   F_false if there is no process found.
 *   F_true if there is a process found (address is stored in "at").
 */
#ifndef _di_controller_find_process_
  f_status_t controller_find_process(const f_array_length_t action, const f_string_static_t alias, const controller_processs_t processs, f_array_length_t *at) f_attribute_visibility_internal;
#endif // _di_controller_find_process_

/**
 * Convert the string from a string representation of an ID or a user name into the numeric representation of that ID or user name.
 *
 * @param buffer
 *   A string containing user name or ID.
 * @param range
 *   The range within the buffer specifically containing the name or ID.
 * @param cache
 *   The cache.
 * @param id
 *   The determined user ID.
 *
 * @return
 *   F_none on success.
 *   F_exist_not (with error bit) if failed to match the name to an ID.
 *   F_number_too_large (with error bit) if the given ID is too large.
 *
 *   Errors (with error bit) from: f_account_id_user_by_name().
 *   Errors (with error bit) from: fl_conversion_string_to_number_unsigned().
 *
 * @see f_account_id_user_by_name()
 * @see fl_conversion_string_to_number_unsigned()
 */
#ifndef _di_controller_get_id_user_
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, uid_t *id) f_attribute_visibility_internal;
#endif // _di_controller_get_id_user_

/**
 * Convert the string from a string representation of an ID or a group name into the numeric representation of that ID or group name.
 *
 * @param buffer
 *   A string containing group name or ID.
 * @param range
 *   The range within the buffer specifically containing the name or ID.
 * @param cache
 *   The cache.
 * @param id
 *   The determined group ID.
 *
 * @return
 *   F_none on success.
 *   F_exist_not (with error bit) if failed to match the name to an ID.
 *   F_number_too_large (with error bit) if the given ID is too large.
 *
 *   Errors (with error bit) from: f_account_id_group_by_name().
 *   Errors (with error bit) from: fl_conversion_string_to_number_unsigned().
 *
 * @see f_account_id_group_by_name()
 * @see fl_conversion_string_to_number_unsigned()
 */
#ifndef _di_controller_get_id_group_
  f_status_t controller_get_id_group(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, gid_t *id) f_attribute_visibility_internal;
#endif // _di_controller_get_id_group_

/**
 * Perform all activities requiring the state to be "ready".
 *
 * This prints messages on errors.
 *
 * This does not do any locking or unlocking for the setting data, be sure to lock appropriately before and after calling this.
 *
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 * @param main
 *   The main data.
 * @param cache
 *   The cache.
 *
 * @return
 *   F_none on success.
 *
 *   Errors from controller_file_pid_create() are not returned, unless it is a memory error.
 *
 * @see controller_file_pid_create()
 */
#ifndef _di_controller_perform_ready_
  extern f_status_t controller_perform_ready(const bool is_entry, controller_main_t main, controller_cache_t *cache) f_attribute_visibility_internal;
#endif // _di_controller_perform_ready_

/**
 * Pre-process all items for the loaded entry.
 *
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 * @param main
 *   The main data.
 * @param cache
 *   The main/global cache to use.
 *
 * @return
 *   F_none on success.
 *   F_recurse (with error bit) on a recursion error.
 *   F_valid_not (with error bit) on invalid entry item, entry item action, or entry item action value.
 *
 *   Errors (with error bit) from: f_macro_array_lengths_t_increase_by().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 *   This will detect and report all errors, but only the first error is returned.
 *   Memory related errors return immediately.

 * @see f_macro_array_lengths_t_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_preprocess_entry_
  extern f_status_t controller_preprocess_entry(const bool is_entry, controller_main_t main, controller_cache_t *cache) f_attribute_visibility_internal;
#endif // _di_controller_preprocess_entry_

/**
 * Process (execute) all Items for the loaded Entry or Exit.
 *
 * @param failsafe
 *   If TRUE, operate in failsafe mode (starts at designated failsafe Item).
 *   If FALSE, operate in normal mode (starts at "main" Item).
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 * @param main
 *   The main data.
 * @param cache
 *   The main/global cache to use.
 *
 * @return
 *   F_none on success.
 *   F_execute on success and program exiting (scripts may result in this) or when execute would have been executed but is instead simulated.
 *
 *   F_require (with error bit) if a required Item failed.
 *   F_critical (with error bit) on any critical error.
 *   F_execute (with error bit) if the "execute" Item Action failed.
 *
 *   Errors (with error bit) from: f_macro_array_lengths_t_increase_by().
 *   Errors (with error bit) from: controller_perform_ready().
 *   Errors (with error bit) from: controller_string_dynamic_append_terminated().
 *
 * @see f_macro_array_lengths_t_increase_by()
 * @see controller_perform_ready()
 * @see controller_string_dynamic_append_terminated()
 */
#ifndef _di_controller_process_entry_
  extern f_status_t controller_process_entry(const bool failsafe, const bool is_entry, controller_main_t *main, controller_cache_t *cache) f_attribute_visibility_internal;
#endif // _di_controller_process_entry_

/**
 * Prepare the process.
 *
 * The process is initialized with the process id, the rule alias, and the rule action type.
 * These are the necessary parts for uniquely identifying the process.
 *
 * If a process by the given Rule alias and Rule Action already exists, then nothing is done.
 *
 * This requires that a main.thread->lock.process lock be set on process->lock before being called.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param action
 *   The Rule Action to use.
 * @param alias
 *   The Rule alias to use.
 * @param main
 *   The main data.
 * @param id
 *   (optional) The process ID when found or created.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_found on success, but nothing was done because an existing process was found.
 *
 *   F_lock (with error bit) if failed to re-establish read lock on main.thread->lock.process while returning.
 *
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *   Errors (with error bit) from: controller_lock_write().
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_terminate_after()
 * @see controller_lock_read()
 * @see controller_lock_write()
 */
#ifndef _di_controller_process_prepare_
  extern f_status_t controller_process_prepare(const bool is_normal, const uint8_t action, const f_string_static_t alias, const controller_main_t main, f_array_length_t *id) f_attribute_visibility_internal;
#endif // _di_controller_process_prepare_

/**
 * Prepare the process for some process type.
 *
 * The process is initialized with the process id, the rule alias, and the rule action type.
 * These are the necessary parts for uniquely identifying the process.
 *
 * If a process by the given Rule alias and Rule Action already exists, then nothing is done.
 *
 * This requires that a main.thread->lock.process lock be set on process->lock before being called.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param action
 *   The Rule Action to use.
 * @param alias
 *   The Rule alias to use.
 * @param main
 *   The main data.
 * @param id
 *   (optional) The process ID when found or created.
 *   Set to NULL to not use.
 *
 * @return
 *   Success from: controller_process_prepare()
 *
 *   Errors (with error bit) from: controller_process_prepare().
 *
 * @see controller_process_prepare()
 */
#ifndef _di_controller_process_prepare_process_type_
  extern f_status_t controller_process_prepare_process_type(const uint8_t type, const uint8_t action, const f_string_static_t alias, const controller_main_t main, f_array_length_t *id) f_attribute_visibility_internal;
#endif // _di_controller_process_prepare_process_type_

/**
 * Given a wide range of status codes (that are errors), simplify them down to a small subset.
 *
 * @param status
 *   The status code (without the error bit set) to simplify.
 *
 * @return
 *   A subset of status codes with error bit.
 */
#ifndef _di_controller_status_simplify_error_
  extern f_status_t controller_status_simplify_error(const f_status_t status) f_attribute_visibility_internal;
#endif // _di_controller_status_simplify_error_

/**
 * Validate that the given string is a valid environment variable name.
 *
 * A valid environment variable name must begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @param name
 *   The string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 *
 *   Errors (with error bit) from: f_utf_is_alpha().
 *   Errors (with error bit) from: f_utf_is_alpha_digit().
 *
 * @see f_utf_is_alpha()
 * @see f_utf_is_alpha_digit()
 */
#ifndef _di_controller_validate_define_name_
  extern f_status_t controller_validate_environment_name(const f_string_static_t name) f_attribute_visibility_internal;
#endif // _di_controller_validate_define_name_

/**
 * Validate that the given string has at least one graph character.
 *
 * @param name
 *   The string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_controller_validate_has_graph_
  extern f_status_t controller_validate_has_graph(const f_string_static_t name) f_attribute_visibility_internal;
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_controller_h

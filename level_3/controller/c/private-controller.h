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
  extern f_status_t controller_string_dynamic_rip_nulless_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
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
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_controller_string_dynamic_append_terminated_
  extern f_status_t controller_string_dynamic_append_terminated(const f_string_static_t from, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
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
  extern f_status_t controller_string_dynamic_partial_append_terminated(const f_string_static_t from, const f_string_range_t range, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
#endif // _di_controller_string_dynamic_partial_append_terminated_

/**
 * Load a file from the controller settings directory.
 *
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
  extern f_status_t controller_file_load(const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_array_length_t path_prefix_length, const f_array_length_t path_suffix_length, controller_main_t main, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_file_load_

/**
 * Create the pid file, if possible.
 *
 * @param data
 *   The program data.
 * @param path_pid
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
  f_status_t controller_file_pid_create(const controller_data_t data, const f_string_static_t path_pid) f_gcc_attribute_visibility_internal;
#endif // _di_controller_file_pid_create_

/**
 * Delete the pid file, if exists and is valid.
 *
 * This is meant to be called on exit and avoids checking status codes, returning void.
 *
 * @param data
 *   The program data.
 * @param path_pid
 *   The file path to the pid file to create.
 */
#ifndef _di_controller_file_pid_delete_
  void controller_file_pid_delete(const controller_data_t data, const f_string_static_t path_pid) f_gcc_attribute_visibility_internal;
#endif // _di_controller_file_pid_delete_

/**
 * Find an existing process.
 *
 * Do not confuse this with a process in the context of a PID.
 * This is a stucture for the current processing of some rule.
 *
 * This does not do any locking or unlocking for the processs data, be sure to lock appropriately before and after calling this.
 *
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
  f_status_t controller_find_process(const f_string_static_t alias, const controller_processs_t processs, f_array_length_t *at) f_gcc_attribute_visibility_internal;
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
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, uid_t *id) f_gcc_attribute_visibility_internal;
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
  f_status_t controller_get_id_group(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, gid_t *id) f_gcc_attribute_visibility_internal;
#endif // _di_controller_get_id_group_

/**
 * Perform all activities requiring the state to be "ready".
 *
 * This prints messages on errors.
 *
 * This does not do any locking or unlocking for the setting data, be sure to lock appropriately before and after calling this.
 *
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
  extern f_status_t controller_perform_ready(controller_main_t main, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_perform_ready_

/**
 * Pre-process all items for the loaded entry.
 *
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
  extern f_status_t controller_preprocess_entry(controller_main_t main, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_preprocess_entry_

/**
 * Process (execute) all items for the loaded entry.
 *
 * @param main
 *   The main data.
 * @param cache
 *   The main/global cache to use.
 *
 * @return
 *   F_none on success.
 *   F_critical (with error bit) on any critical error.
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
  extern f_status_t controller_process_entry(controller_main_t main, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_process_entry_

/**
 * Given a wide range of status codes, simplify them down to a small subset.
 *
 * @param status
 *   The status code (without the error bit set) to simplify.
 *
 * @return
 *   A subset of status codes with error bit.
 */
#ifndef _di_controller_status_simplify_
  extern f_status_t controller_status_simplify(const f_status_t status) f_gcc_attribute_visibility_internal;
#endif // _di_controller_status_simplify_

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
  extern f_status_t controller_validate_environment_name(const f_string_static_t name) f_gcc_attribute_visibility_internal;
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
  extern f_status_t controller_validate_has_graph(const f_string_static_t name) f_gcc_attribute_visibility_internal;
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_controller_h

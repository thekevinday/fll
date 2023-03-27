/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_controller_h
#define _PRIVATE_controller_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given a string whose range represents a number, seek past the first positive or negative sign.
 *
 * This will stop at the first non-NULL, non-'+' and non-'-' characters.
 *
 * Only the first '+' or '-' are processed.
 *
 * @param buffer
 *   The string referenced by the range.
 * @param range
 *   The range within the buffer to process.
 *
 * @return
 *   The string range.
 *   The start range will be past the stop range on overflow or on any failure.
 */
#ifndef _di_controller_range_after_number_sign_
  extern f_string_range_t controller_range_after_number_sign(const f_string_static_t buffer, const f_string_range_t range) F_attribute_visibility_internal_d;
#endif // _di_controller_range_after_number_sign_

/**
 * Load a file from the controller settings directory.
 *
 * @param global
 *   The global data.
 * @param required
 *   If TRUE, the file is required to exist and will throw an error if not found.
 *   If FALSE, the file is not required to exist and will return without error if not found.
 * @param path_prefix
 *   The path prefix, such as 'entries' from '/etc/controller/entries/default.entry'.
 * @param path_name
 *   The path name, such as 'default' from '/etc/controller/entries/default.entry'.
 * @param path_suffix
 *   The path suffix, such as 'entry' from '/etc/controller/entries/default.entry'.
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
 *
 * @see f_file_stat()
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 * @see f_string_append()
 */
#ifndef _di_controller_file_load_
  extern f_status_t controller_file_load(const controller_global_t global, const bool required, const f_string_static_t path_prefix, const f_string_static_t path_name, const f_string_static_t path_suffix, controller_cache_t * const cache) F_attribute_visibility_internal_d;
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
  f_status_t controller_file_pid_create(const pid_t pid, const f_string_static_t path) F_attribute_visibility_internal_d;
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
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned()
 */
#ifndef _di_controller_file_pid_delete_
  f_status_t controller_file_pid_delete(const pid_t pid, const f_string_static_t path) F_attribute_visibility_internal_d;
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
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned()
 */
#ifndef _di_controller_file_pid_read_
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t * const pid) F_attribute_visibility_internal_d;
#endif // _di_controller_file_pid_read_

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
 *   Errors (with error bit) from: f_account_id_by_name().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *
 * @see f_account_id_by_name()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see f_rip_dynamic_partial_nulless()
 */
#ifndef _di_controller_get_id_user_
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t * const cache, uid_t * const id) F_attribute_visibility_internal_d;
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
 *   Errors (with error bit) from: f_account_group_id_by_name().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: f_rip_dynamic_partial_nulless().
 *
 * @see f_account_group_id_by_name()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see f_rip_dynamic_partial_nulless()
 */
#ifndef _di_controller_get_id_group_
  f_status_t controller_get_id_group(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t * const cache, gid_t * const id) F_attribute_visibility_internal_d;
#endif // _di_controller_get_id_group_

/**
 * Determine a canonical path and then if it is relative to the current working directory, make it relative.
 *
 * For example, given the paths "../hello/world/" and "../controller/files/" with a current working directory of "/tmp/controller", then a canonical path for these might look like:
 * - "/tmp/hello/world/"
 * - "/tmp/controller/files/"
 *
 * This function would instead result in the following:
 * - "/tmp/hello/world/"
 * - "files/"
 *
 * @param setting
 *   The controller settings data.
 * @param source
 *   The source path to determine the relative canonical from.
 * @param destination
 *   The resulting relative canonical path.
 *   The destination will be completely replaced on success.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fl_path_canonical().
 *
 * @see fl_path_canonical()
 */
#ifndef _di_controller_path_canonical_relative_
  extern f_status_t controller_path_canonical_relative(const controller_setting_t * const global, const f_string_static_t source, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // _di_controller_path_canonical_relative_

/**
 * Perform all activities requiring the state to be "ready".
 *
 * This prints messages on errors.
 *
 * This does not do any locking or unlocking for the setting data, be sure to lock appropriately before and after calling this.
 *
 * @param global
 *   The global data.
 * @param cache
 *   The cache.
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 *
 * @return
 *   F_none on success.
 *
 *   Errors from controller_file_pid_create() are not returned, unless it is a memory error.
 *
 * @see controller_file_pid_create()
 */
#ifndef _di_controller_perform_ready_
  extern f_status_t controller_perform_ready(const controller_global_t * const global, controller_cache_t * const cache, const bool is_entry) F_attribute_visibility_internal_d;
#endif // _di_controller_perform_ready_

/**
 * Perform the socket loading when "ready".
 *
 * This prints messages on errors.
 *
 * This does not do any locking or unlocking for the setting data, be sure to lock appropriately before and after calling this.
 *
 * @param global
 *   The global data.
 * @param cache
 *   The cache.
 * @param is_entry
 *   If TRUE, then this operate as an entry.
 *   If FALSE, then this operate as an exit.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but socket file not created.
 *
 *   Errors (with error bit) from: f_file_mode_set().
 *   Errors (with error bit) from: f_file_remove().
 *   Errors (with error bit) from: f_file_role_change().
 *   Errors (with error bit) from: f_socket_bind_local().
 *   Errors (with error bit) from: f_socket_create().
 *   Errors (with error bit) from: f_thread_create().
 *
 * @see f_file_mode_set()
 * @see f_file_remove()
 * @see f_file_role_change()
 * @see f_socket_bind_local()
 * @see f_socket_create()
 * @see f_thread_create()
 */
#ifndef _di_controller_perform_ready_socket_
  extern f_status_t controller_perform_ready_socket(const controller_global_t * const global, controller_cache_t * const cache, const bool is_entry) F_attribute_visibility_internal_d;
#endif // _di_controller_perform_ready_socket_

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
  extern f_status_t controller_status_simplify_error(const f_status_t status) F_attribute_visibility_internal_d;
#endif // _di_controller_status_simplify_error_

/**
 * Get the current time, plus the given offset.
 *
 * @todo this is basic enough that there needs to be an f_time class with this function f_time_now(), f_time_future(), f_time_past().
 *       "struct timespec" -> f_time_nano_t, "struct timeval" -> f_time_micro_t.
 *
 * @param seconds
 *   The seconds to add to current time.
 * @param nanoseconds
 *   The nanoseconds to add to current time.
 * @param time
 *   The resulting current time.
 */
#ifndef _di_controller_time_
  void controller_time(const time_t seconds, const long nanoseconds, struct timespec *time) F_attribute_visibility_internal_d;
#endif // _di_controller_time_

/**
 * Convert milliseconds to nanoseconds.
 *
 * @param milliseconds
 *   The number of milliseconds.
 *
 * @return
 *   A time structure suitable for passing to nanosleep() and similar functions.
 *
 * @see nanosleep()
 */
#ifndef _di_controller_time_milliseconds_
  extern struct timespec controller_time_milliseconds(const f_number_unsigned_t milliseconds) F_attribute_visibility_internal_d;
#endif // _di_controller_time_milliseconds_

/**
 * Convert seconds to nanoseconds.
 *
 * @param seconds
 *   The number of seconds.
 *
 * @return
 *   A time structure suitable for passing to nanosleep() and similar functions.
 *
 * @see nanosleep()
 */
#ifndef _di_controller_time_seconds_
  extern struct timespec controller_time_seconds(const f_number_unsigned_t seconds) F_attribute_visibility_internal_d;
#endif // _di_controller_time_seconds_

/**
 * Sleep for a given number of nanoseconds.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The controller settings data.
 * @param time
 *   The number of nanoseconds to sleep.
 *
 * @return
 *   The result of nanosleep().
 *
 * @see nanosleep()
 */
#ifndef _di_controller_time_sleep_nanoseconds_
  extern int controller_time_sleep_nanoseconds(controller_main_t * const main, controller_setting_t * const setting, struct timespec time) F_attribute_visibility_internal_d;
#endif // _di_controller_time_sleep_nanoseconds_

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
 *   Errors (with error bit) from: f_utf_is_alphabetic().
 *   Errors (with error bit) from: f_utf_is_alphabetic_digit().
 *
 * @see f_utf_is_alphabetic()
 * @see f_utf_is_alphabetic_digit()
 */
#ifndef _di_controller_validate_define_name_
  extern f_status_t controller_validate_environment_name(const f_string_static_t name) F_attribute_visibility_internal_d;
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
  extern f_status_t controller_validate_has_graph(const f_string_static_t name) F_attribute_visibility_internal_d;
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_controller_h

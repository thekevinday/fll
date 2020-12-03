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
 * Load a file from the controller settings directory.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
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
 * @param path_file
 *   This is updated with a partial path to the given file.
 * @param buffer
 *   The buffer to load the file into.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 */
#ifndef _di_controller_file_load_
  extern f_return_status controller_file_load(const controller_data_t data, const controller_setting_t setting, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_string_length_t path_prefix_length, const f_string_length_t path_suffix_length, f_string_dynamic_t *path_file, f_string_dynamic_t *buffer) f_gcc_attribute_visibility_internal;
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
  f_return_status controller_file_pid_create(const controller_data_t data, const f_string_static_t path_pid) f_gcc_attribute_visibility_internal;
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
 * Load relevant rules into memory and performing other pre-process tasks.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param cache
 *   The cache.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_controller_preprocess_rules_
  extern f_return_status controller_preprocess_rules(const controller_data_t data, controller_setting_t *setting, controller_cache_t *cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_preprocess_rules_

/**
 * Given a wide range of status codes, simplify them down to a small subset.
 *
 * @param status
 *   The status code (without the error bit set) to simplify.
 *
 * @return
 *   A subset of status codes with error bit set.
 */
#ifndef _di_controller_status_simplify_
  extern f_return_status controller_status_simplify(const f_status_t status) f_gcc_attribute_visibility_internal;
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
  extern f_return_status controller_validate_environment_name(const f_string_static_t name) f_gcc_attribute_visibility_internal;
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
  extern f_return_status controller_validate_has_graph(const f_string_static_t name) f_gcc_attribute_visibility_internal;
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_controller_h

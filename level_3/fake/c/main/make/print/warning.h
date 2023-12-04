/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make warning print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_print_warning_h
#define _fake_make_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print warning message when unable to change back to original path.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path that cannot be changed back to.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_make_print_warning_cannot_change_back_
  extern f_status_t fake_make_print_warning_cannot_change_back(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_make_print_warning_cannot_change_back_

/**
 * Print warning about a setting name being already added.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the environment variable that is already added.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple_variable()
 */
#ifndef _di_fake_make_print_warning_environment_name_already_added_
  extern f_status_t fake_make_print_warning_environment_name_already_added(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fake_make_print_warning_environment_name_already_added_

/**
 * Print warning about a given environment name being invalid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the environment variable that is invalid.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple_variable()
 */
#ifndef _di_fake_make_print_warning_environment_name_invalid_
  extern f_status_t fake_make_print_warning_environment_name_invalid(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fake_make_print_warning_environment_name_invalid_

/**
 * Print warning about a given fakefile being empty.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple_variable()
 */
#ifndef _di_fake_make_print_warning_fakefile_empty_
  extern f_status_t fake_make_print_warning_fakefile_empty(fl_print_t * const print, const f_string_static_t fakefile);
#endif // _di_fake_make_print_warning_fakefile_empty_

/**
 * Print warning about a file not being found.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param file
 *   The name or path of the file that is not found.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple_variable()
 */
#ifndef _di_fake_make_print_warning_file_not_found_
  extern f_status_t fake_make_print_warning_file_not_found(fl_print_t * const print, const f_string_static_t file);
#endif // _di_fake_make_print_warning_file_not_found_

/**
 * Print message when fake settings content is empty.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param range
 *   The range within the buffer representing the object.
 * @param name
 *   The name of the setting that has an invalid value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_make_print_warning_setting_content_empty_
  extern f_status_t fake_make_print_warning_setting_content_empty(fl_print_t * const print, const f_string_static_t fakefile, const f_string_dynamic_t buffer, const f_range_t range, const f_string_static_t name);
#endif // _di_fake_make_print_warning_setting_content_empty_

/**
 * Print warning message when fake settings content is invalid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param object
 *   The range within the buffer representing the object.
 * @param content
 *   The range within the buffer representing the content.
 * @param name
 *   The name of the setting that has an invalid value.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_make_print_warning_setting_content_invalid_
  extern f_status_t fake_make_print_warning_setting_content_invalid(fl_print_t * const print, const f_string_static_t fakefile, const f_string_dynamic_t buffer, const f_range_t object, const f_range_t content, const f_string_static_t name);
#endif // _di_fake_make_print_warning_setting_content_invalid_

/**
 * Print warning message when settings content has too many values.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param name
 *   The name of the content.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_make_print_warning_setting_content_multiple_
  extern f_status_t fake_make_print_warning_setting_content_multiple(fl_print_t * const print, const f_string_static_t fakefile, const f_string_static_t name);
#endif // _di_fake_make_print_warning_setting_content_multiple_

/**
 * Print warning message when fakefile has too many objects with the same name.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param name
 *   The name of the object.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_make_print_warning_setting_object_multiple_
  extern f_status_t fake_make_print_warning_setting_object_multiple(fl_print_t * const print, const f_string_static_t fakefile, const f_string_static_t name);
#endif // _di_fake_make_print_warning_setting_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_warning_h

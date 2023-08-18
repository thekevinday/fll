/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build error print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_print_error_h
#define _fake_build_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error message about not creating path due to a parent directory not existing or is otherwise invalid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path that cannot be created.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_build_print_error_cannot_create_due_to_parent_
  extern f_status_t fake_build_print_error_cannot_create_due_to_parent(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_build_print_error_cannot_create_due_to_parent_

/**
 * Print error message about not creating path due to a parent directory not existing or is otherwise invalid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path that cannot be created.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_build_print_error_exist_not_directory_
  extern f_status_t fake_build_print_error_exist_not_directory(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_build_print_error_exist_not_directory_

/**
 * Print error message about a required setting missing.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the missing setting.
 * @param path
 *   The path to the file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_build_print_error_missing_required_setting_
  extern f_status_t fake_build_print_error_missing_required_setting(fl_print_t * const print, const f_string_static_t name, const f_string_static_t path);
#endif // _di_fake_build_print_error_missing_required_setting_


/**
 * Print error message about a mode being invalid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param mode
 *   The invalid mode.
 * @param path
 *   The path to the file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_build_print_error_mode_invalid_
  extern f_status_t fake_build_print_error_mode_invalid(fl_print_t * const print, const f_string_static_t mode, const f_string_static_t path);
#endif // _di_fake_build_print_error_mode_invalid_

/**
 * Print error message about an unnamed setting being too long.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path that cannot be created.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_build_print_error_setting_too_long_
  extern f_status_t fake_build_print_error_setting_too_long(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_build_print_error_setting_too_long_

/**
 * Print error message about the given setting for the given file being too long.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the setting.
 * @param path
 *   The path that cannot be created.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_build_print_error_setting_value_too_long_
  extern f_status_t fake_build_print_error_setting_value_too_long(fl_print_t * const print, const f_string_static_t name, const f_string_static_t path);
#endif // _di_fake_build_print_error_setting_value_too_long_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_error_h

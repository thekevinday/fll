/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_build_print_error_h
#define _PRIVATE_build_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error message about not creating path due to a parent directory not existing or is otherwise invalid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The path that cannot be created.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_build_print_error_cannot_create_due_to_parent_
  extern f_status_t fake_build_print_error_cannot_create_due_to_parent(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_build_print_error_cannot_create_due_to_parent_

/**
 * Print error message about not creating path due to a parent directory not existing or is otherwise invalid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The path that cannot be created.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_build_print_error_exist_not_directory_
  extern f_status_t fake_build_print_error_exist_not_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_build_print_error_exist_not_directory_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_print_error_h

/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the verbose print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_verbose_h
#define _fake_print_verbose_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Helper function for performing a verbose print for a file clone operation.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param source
 *   The source string.
 * @param destination
 *   The destination string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_wrapped_variables()
 */
#ifndef _di_fake_print_verbose_clone_
  extern f_status_t fake_print_verbose_clone(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_print_verbose_clone_

/**
 * Helper function for performing a verbose print for a file copy operation.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param source
 *   The source string.
 * @param destination
 *   The destination string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_verbose_copy_
  extern f_status_t fake_print_verbose_copy(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_print_verbose_copy_

/**
 * Print verbose message about creating a directory.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_simple_variable()
 */
#ifndef _di_fake_print_verbose_create_directory_
  extern f_status_t fake_print_verbose_create_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_create_directory_

/**
 * Print verbose message about creating a file.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_simple_variable()
 */
#ifndef _di_fake_print_verbose_create_file_
  extern f_status_t fake_print_verbose_create_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_create_file_

/**
 * Print a verbose message for when a directory already exists.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_directory_exists_
  extern f_status_t fake_print_verbose_directory_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_directory_exists_

/**
 * Print a verbose message for when a file already exists.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_file_exists_
  extern f_status_t fake_print_verbose_file_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_exists_

/**
 * Print a verbose message for when a file already exists as a symbolic link.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_file_exists_as_link_
  extern f_status_t fake_print_verbose_file_exists_as_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_exists_as_link_

/**
 * Print a verbose message for when a file already exists but is not a regular file or a symbolic link.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_file_exists_not_regular_or_link_
  extern f_status_t fake_print_verbose_file_exists_not_regular_or_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_exists_not_regular_or_link_

/**
 * Print a verbose message for when a file is pre-populated.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_simple_variable()
 */
#ifndef _di_fake_print_verbose_file_pre_populated_
  extern f_status_t fake_print_verbose_file_pre_populated(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_pre_populated_

/**
* Print a verbose message for when a file is moved.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param source
 *   The source string.
 * @param destination
 *   The destination string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_verbose_move_
  extern f_status_t fake_print_verbose_move(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_print_verbose_move_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_verbose_h

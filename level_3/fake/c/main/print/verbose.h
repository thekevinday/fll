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
 * Print verbose message about cloning a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param source
 *   The source file path.
 * @param destination
 *   The destination file path.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variables()
 */
#ifndef _di_fake_print_verbose_cloning_
  extern f_status_t fake_print_verbose_cloning(fl_print_t * const print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_print_verbose_cloning_

/**
 * Print verbose message about copying a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param source
 *   The source file path.
 * @param destination
 *   The destination file path.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variables()
 */
#ifndef _di_fake_print_verbose_copying_
  extern f_status_t fake_print_verbose_copying(fl_print_t * const print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_print_verbose_copying_

/**
 * Print verbose message about creating a directory.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the file.
 *
 * @see fake_print_common_simple_variable()
 */
#ifndef _di_fake_print_verbose_create_directory_
  extern void fake_print_verbose_create_directory(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_create_directory_

/**
 * Print verbose message about creating a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the file.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_simple_variable()
 */
#ifndef _di_fake_print_verbose_create_file_
  extern f_status_t fake_print_verbose_create_file(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_create_file_

/**
 * Print a verbose message for when a directory already exists.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_directory_exists_
  extern f_status_t fake_print_verbose_directory_exists(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_directory_exists_

/**
 * Print a verbose message for when a file already exists.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_file_exists_
  extern f_status_t fake_print_verbose_file_exists(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_exists_

/**
 * Print a verbose message for when a file already exists as a symbolic link.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_file_exists_as_link_
  extern f_status_t fake_print_verbose_file_exists_as_link(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_exists_as_link_

/**
 * Print a verbose message for when a file already exists but is not a regular file or a symbolic link.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variable()
 */
#ifndef _di_fake_print_verbose_file_exists_not_regular_or_link_
  extern f_status_t fake_print_verbose_file_exists_not_regular_or_link(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_exists_not_regular_or_link_

/**
 * Print a verbose message for when a file is pre-populated.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_simple_variable()
 */
#ifndef _di_fake_print_verbose_file_pre_populated_
  extern f_status_t fake_print_verbose_file_pre_populated(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_verbose_file_pre_populated_

/**
 * Print verbose message about moving a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param source
 *   The source file path.
 * @param destination
 *   The destination file path.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variables()
 */
#ifndef _di_fake_print_verbose_moving_
  extern f_status_t fake_print_verbose_moving(fl_print_t * const print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_print_verbose_moving_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_verbose_h

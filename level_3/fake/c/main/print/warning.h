/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the warning print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_warning_h
#define _fake_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print warning message about the build directory not being found.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path of the build directory.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_warning_build_directory_not_directory_
  extern f_status_t fake_print_warning_build_directory_not_directory(fl_print_t * const print, f_string_static_t path);
#endif // _di_fake_print_warning_build_directory_not_directory_

/**
 * Print warning message about path existing but is not a directory.
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
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_warning_path_exists_not_directory_
  extern f_status_t fake_print_warning_path_exists_not_directory(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_warning_path_exists_not_directory_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_warning_h

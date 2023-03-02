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
 * Print warning message about path existing but is not a directory.
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
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_warning_path_exists_not_directory_
  extern f_status_t fake_print_warning_path_exists_not_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_print_warning_path_exists_not_directory_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_warning_h

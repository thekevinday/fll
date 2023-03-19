/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build verbose print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_print_verbose_h
#define _fake_build_print_verbose_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print verbose message about copying a file.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
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
 * @see fake_print_wrapped_variables()
 */
#ifndef _di_fake_build_print_verbose_copied_file_
  extern f_status_t fake_build_print_verbose_copied_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_build_print_verbose_create_directory_

/**
 * Print verbose message about _di_fake_build_print_verbose_copied_file_ a directory.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param directory
 *   The directory created.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_simple_variable()
 */
#ifndef _di_fake_build_print_verbose_create_directory_
  extern f_status_t fake_build_print_verbose_create_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t directory);
#endif // _di_fake_build_print_verbose_create_directory_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_verbose_h

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
 * Print verbose message about _di_fake_build_print_verbose_copied_file_ a directory.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param directory
 *   The directory created.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_simple_variable()
 */
#ifndef _di_fake_build_print_verbose_create_directory_
  extern f_status_t fake_build_print_verbose_create_directory(fl_print_t * const print, const f_string_static_t directory);
#endif // _di_fake_build_print_verbose_create_directory_

/**
 * Print message about linking a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param from
 *   The link source.
 * @param to
 *   The link destination.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_common_wrapped_variables()
 */
#ifndef _di_fake_build_print_verbose_linked_file_
  extern f_status_t fake_build_print_verbose_linked_file(fl_print_t * const print, const f_string_static_t from, const f_string_static_t to);
#endif // _di_fake_build_print_verbose_linked_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_verbose_h

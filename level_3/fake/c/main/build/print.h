/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_print_h
#define _fake_build_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message when compiling a shared library.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
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
 * @see fake_print_wrapped_variables()
 */
#ifndef _di_fake_build_print_linked_file_
  extern f_status_t fake_build_print_linked_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t from, const f_string_static_t to);
#endif // _di_fake_build_print_linked_file_

/**
 * Print message when building base skeleton directories.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_skeleton_build_base_
  extern f_status_t fake_build_print_skeleton_build_base(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_skeleton_build_base_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_h

/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_print_message_h
#define _fake_build_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message when building base skeleton directories.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_message_skeleton_build_base_
  extern f_status_t fake_build_print_message_skeleton_build_base(fl_print_t * const print);
#endif // _di_fake_build_print_message_skeleton_build_base_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_message_h

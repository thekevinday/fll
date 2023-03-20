/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build skeleton functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_skeleton_h
#define _fake_build_skeleton_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create all of the base directories inside the build directory.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_directory_create().
 *     Errors (with error bit) from: f_directory_exists().
 *
 *     Errors (with error bit) from: fake_build_touch().
 * @param data_build
 *   The build data.
 * @param mode
 *   The directory mode.
 * @param file_stage
 *   The specific stage file path.
 *
 * @see f_directory_create()
 * @see f_directory_exists()
 * @see fll_program_standard_signal_received()
 *
 * @see fake_build_touch()
 */
#ifndef _di_fake_build_skeleton_
  extern void fake_build_skeleton(fake_data_t * const data, fake_build_data_t * const data_build, const mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_skeleton_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_skeleton_h

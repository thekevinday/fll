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
#ifndef _PRIVATE_build_skeleton_h
#define _PRIVATE_build_skeleton_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create all of the base directories inside the build directory.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   The build data.
 * @param mode
 *   The directory mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_skeleton_
  extern void fake_build_skeleton(fake_data_t * const data, fake_build_data_t * const data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t * const status);
#endif // _di_fake_build_skeleton_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_skeleton_h

/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_skeleton_h
#define _PRIVATE_skeleton_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the skeleton operation.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_
  extern f_status_t fake_skeleton_operate(fake_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fake_skeleton_operate_

/**
 * Create a directory if it does not exist, ignore it if it does, and warn if path exists but is not a directory.
 *
 * @param main
 *   The main program data.
 * @param path
 *   The file path for the directory to create.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with warning bit) are returned on certain problems that can be ignored.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_directory_create_
  extern f_status_t fake_skeleton_operate_directory_create(fake_main_t * const main, const f_string_dynamic_t path) F_attribute_visibility_internal_d;
#endif // _di_fake_skeleton_operate_directory_create_

/**
 * Create a file if it does not exist, ignore it if it does, and warn if path exists but is not a file.
 *
 * @param main
 *   The main program data.
 * @param path
 *   The file path for the directory to create.
 * @param executable
 *   Set to TRUE to make the file executable.
 *   Set to FALSE to not make the file executable.
 * @param content
 *   When creating a new file, write the content specified by this string to that file.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with warning bit) are returned on certain problems that can be ignored.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_file_create_
  extern f_status_t fake_skeleton_operate_file_create(fake_main_t * const main, const f_string_dynamic_t path, const bool executable, const f_string_static_t content) F_attribute_visibility_internal_d;
#endif // _di_fake_skeleton_operate_file_create_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_skeleton_h

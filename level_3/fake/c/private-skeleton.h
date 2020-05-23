/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_skeleton_h
#define _PRIVATE_skeleton_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the skeleton operation.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_
  extern f_return_status fake_skeleton_operate(const fake_data data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_skeleton_operate_

/**
 * Create a directory if it does not exist, ignore it if it does, and warn if path exists but is not a directory.
 *
 * @param data
 *   The program data.
 * @param path
 *   The file path for the directory to create.
 *
 * @return
 *   F_none on success.
 *   Status codes (with warning bit) are returned on certain problems that can be ignored.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_directory_create_
  extern f_return_status fake_skeleton_operate_directory_create(const fake_data data, const f_string_dynamic path) f_gcc_attribute_visibility_internal;
#endif // _di_fake_skeleton_operate_directory_create_

/**
 * Create a file if it does not exist, ignore it if it does, and warn if path exists but is not a file.
 *
 * @param data
 *   The program data.
 * @param path
 *   The file path for the directory to create.
 * @param executable
 *   Set to TRUE to make the file executable.
 *   Set to FALSE to not make the file executable.
 *
 * @return
 *   F_none on success.
 *   Status codes (with warning bit) are returned on certain problems that can be ignored.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_file_create_
  extern f_return_status fake_skeleton_operate_file_create(const fake_data data, const f_string_dynamic path, const bool executable) f_gcc_attribute_visibility_internal;
#endif // _di_fake_skeleton_operate_file_create_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_skeleton_h

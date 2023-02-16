/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
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
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_
  extern f_status_t fake_skeleton_operate(fake_data_t * const data);
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
 *
 *   Status codes (with warning bit) are returned on certain problems that can be ignored.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_directory_create_
  extern f_status_t fake_skeleton_operate_directory_create(fake_data_t * const data, const f_string_static_t path);
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
  extern f_status_t fake_skeleton_operate_file_create(fake_data_t * const data, const f_string_static_t path, const bool executable, const f_string_static_t content);
#endif // _di_fake_skeleton_operate_file_create_

/**
 * Calculate the length of the sources path so that it can be used to manually construct a static string.
 *
 * @param data
 *   The program data.
 * @param partial
 *   The partial path string, such as "bash".
 * @param source
 *   The static string.
 *   The path_sources.string is not expected to be defined at this point.
 *   The path_sources.used is updated.
 *   The path_sources.size is ignored.
 */
#ifndef _di_fake_skeleton_path_source_length_
  extern void fake_skeleton_path_source_length(fake_data_t * const data, const f_string_static_t *partial, f_string_static_t * const source);
#endif // _di_fake_skeleton_path_source_length_

/**
 * Construct a static string array of the sources path.
 *
 * @param data
 *   The program data.
 * @param partial
 *   The partial path string, such as "bash".
 * @param source
 *   The static string.
 *   The path_sources.string is expected to be defined and set to a size from path_sources.used + 1.
 *   The path_sources.used is updated.
 *   The path_sources.size is ignored.
 */
#ifndef _di_fake_skeleton_path_source_string_
  extern void fake_skeleton_path_source_string(fake_data_t * const data, const f_string_static_t *partial, f_string_static_t * const source);
#endif // _di_fake_skeleton_path_source_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_skeleton_h

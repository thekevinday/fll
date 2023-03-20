/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides skeleton functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_skeleton_h
#define _fake_skeleton_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the skeleton operation.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: fake_skeleton_operate_directory_create()
 *     Errors (with error bit) from: fake_skeleton_operate_file_create()
 *
 * @see fake_skeleton_operate_directory_create()
 * @see fake_skeleton_operate_file_create()
 */
#ifndef _di_fake_skeleton_operate_
  extern void fake_skeleton_operate(fake_data_t * const data);
#endif // _di_fake_skeleton_operate_

/**
 * Create a directory if it does not exist, ignore it if it does, and warn if path exists but is not a directory.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     F_failure (with warning bit) on path exists but is not a directory.
 *
 *     Errors (with error bit) from: f_directory_create()
 *     Errors (with error bit) from: f_directory_exists()
 * @param path
 *   The file path for the directory to create.
 *
 * @see f_directory_create()
 * @see f_directory_exists()
 */
#ifndef _di_fake_skeleton_operate_directory_create_
  extern void fake_skeleton_operate_directory_create(fake_data_t * const data, const f_string_static_t path);
#endif // _di_fake_skeleton_operate_directory_create_

/**
 * Create a file if it does not exist, ignore it if it does, and warn if path exists but is not a file.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     F_none (with warning bit) on file exists but is not a regular or a link.
 *
 *     Errors (with error bit) from: f_file_create()
 *     Errors (with error bit) from: f_file_is()
 *     Errors (with error bit) from: f_file_open()
 *     Errors (with error bit) from: f_file_write()
 * @param path
 *   The file path for the directory to create.
 * @param executable
 *   Set to TRUE to make the file executable.
 *   Set to FALSE to not make the file executable.
 * @param content
 *   When creating a new file, write the content specified by this string to that file.
 *
 * @see f_file_create()
 * @see f_file_is()
 * @see f_file_open()
 * @see f_file_write()
 */
#ifndef _di_fake_skeleton_operate_file_create_
  extern void fake_skeleton_operate_file_create(fake_data_t * const data, const f_string_static_t path, const bool executable, const f_string_static_t content);
#endif // _di_fake_skeleton_operate_file_create_

/**
 * Calculate the length of the sources path so that it can be used to manually construct a static string.
 *
 * @param data
 *   The program data.
 *
 *   This does not alter data.main->setting.state.status.
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
 *
 *   This does not alter data.main->setting.state.status.
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

#endif // _fake_skeleton_h

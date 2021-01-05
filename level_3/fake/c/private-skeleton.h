/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_skeleton_h
#define _PRIVATE_skeleton_h

#ifndef _di_fake_skeleton_content_
  #define fake_make_skeleton_content_defines      "# fss-0000\n\n"
  #define fake_make_skeleton_content_dependencies "# fss-0000\n\n"
  #define fake_make_skeleton_content_fakefile     "# fss-0005 iki-0002\n\nsettings:\n  fail exit\n\nmain:\n\n"
  #define fake_make_skeleton_content_settings     "# fss-0001\n\n"

  #define fake_make_skeleton_content_defines_length      12
  #define fake_make_skeleton_content_dependencies_length 12
  #define fake_make_skeleton_content_fakefile_length     51
  #define fake_make_skeleton_content_settings_length     12
#endif // _di_fake_skeleton_content_

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
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_skeleton_operate_
  extern f_status_t fake_skeleton_operate(const fake_data_t data) f_gcc_attribute_visibility_internal;
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
  extern f_status_t fake_skeleton_operate_directory_create(const fake_data_t data, const f_string_dynamic_t path) f_gcc_attribute_visibility_internal;
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
  extern f_status_t fake_skeleton_operate_file_create(const fake_data_t data, const f_string_dynamic_t path, const bool executable, const f_string_static_t content) f_gcc_attribute_visibility_internal;
#endif // _di_fake_skeleton_operate_file_create_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_skeleton_h

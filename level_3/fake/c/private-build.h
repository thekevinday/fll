/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_build_h
#define _PRIVATE_build_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add the standard arguments for building a library/program.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
 * @param is_shared
 *   Set to TRUE to designate that this is adding for a shared library/program.
 *   Set to FALSE to designate that this is adding for a static library/program.
 * @param is_library
 *   Set to TRUE to designate that this is adding for a library.
 *   Set to FALSE to designate that this is adding for a program.
 * @param arguments
 *   The arguments array to append to.
 * @param status
 *   The return status.
 *
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_arguments_standard_add_
  extern void fake_build_arguments_standard_add(fake_main_t * const main, const fake_build_data_t data_build, const bool is_shared, const bool is_library, f_string_dynamics_t *arguments, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_arguments_standard_add_

/**
 * Copy over the main setting files.
 *
 * @param main
 *   The main program data.
 * @param mode
 *   The modes for each file type.
 * @param label
 *   A label used when printing the now copying message.
 * @param source
 *   The specific build path to copy from.
 * @param destination
 *   The specific build path to copy to.
 * @param files
 *   The files to copy from source to destination.
 * @param file_stage
 *   The specific stage file path.
 * @param perserve
 *   When a positive number, this represents the amount of characters at the front of each file to ignore.
 *   Everything after that is preserved, and the directory is created if necessary.
 *
 *   This is always treated as 0 for any file that is a directory type.
 *   Set to 0 to disable.
 *
 *   Example: 'sources/c/level_0/fss.h' with a preseve of 10, would result in the path of 'level_0/fss.h' being preserved.
 *            Whereas a preserve of 0 would result in a path of 'fss.h' being used (the 'level_0/' directory is not preserved).
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_copy_
  extern void fake_build_copy(fake_main_t * const main, const f_mode_t mode, const f_string_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t preserve, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_copy_

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   All build related main.
 * @param process_script
 *   The setting_data file name fo the appropriate process script.
 *   This is expected to be either setting.process_pre or setting.process_post.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_execute_process_script_
  extern int fake_build_execute_process_script(fake_main_t * const main, const fake_build_data_t data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_execute_process_script_

/**
 * Get the file name without the extension and without the path parts.
 *
 * @param main
 *   The main program data.
 * @param path
 *   The file path to get the file name from.
 * @param name
 *   The processed filename.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_get_file_name_without_extension_
  extern f_status_t fake_build_get_file_name_without_extension(fake_main_t * const main, const f_string_static_t path, f_string_dynamic_t *name);
#endif // _di_fake_build_get_file_name_without_extension_

/**
 * Execute the build operation.
 *
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_operate_
  extern f_status_t fake_build_operate(const f_string_static_t setting_file, fake_main_t *main) F_attribute_visibility_internal_d;
#endif // _di_fake_build_operate_

/**
 * Touch the given build stage file, but only if there are no current errors in status.
 *
 * @param main
 *   The main program data.
 * @param file
 *   The file path to touch.
 * @param status
 *   The return status.
 *
 * @see f_file_touch()
 */
#ifndef _di_fake_build_touch_
  extern void fake_build_touch(fake_main_t * const main, const f_string_dynamic_t file, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_h

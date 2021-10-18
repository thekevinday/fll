/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 *   The main data.
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
  extern void fake_build_arguments_standard_add(const fake_main_t main, const fake_build_data_t data_build, const bool is_shared, const bool is_library, f_string_dynamics_t *arguments, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_arguments_standard_add_

/**
 * Copy over the main setting files.
 *
 * @param main
 *   The main data.
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
  extern void fake_build_copy(const fake_main_t main, const f_mode_t mode, const f_string_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t preserve, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_copy_

/**
 * Create all of the base directories inside the build directory.
 *
 * @param main
 *   The main data.
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
  extern void fake_build_skeleton(const fake_main_t main, const fake_build_data_t data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_skeleton_

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param main
 *   The main data.
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
  extern int fake_build_execute_process_script(const fake_main_t main, const fake_build_data_t data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_execute_process_script_

/**
 * Get the file name without the extension and without the path parts.
 *
 * @param main
 *   The main data.
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
  extern f_status_t fake_build_get_file_name_without_extension(const fake_main_t main, const f_string_static_t path, f_string_dynamic_t *name);
#endif // _di_fake_build_get_file_name_without_extension_

/**
 * Build the script libraries.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_libraries_script_
  extern int fake_build_libraries_script(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_libraries_script_

/**
 * Build the shared libraries.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_library_shared_
  extern int fake_build_library_shared(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_library_shared_

/**
 * Build the static libraries.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_library_static_
  extern int fake_build_library_static(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_library_static_

/**
 * Find the build setting file, load it, validate it, and process it.
 *
 * @param main
 *   The main data.
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 * @param setting
 *   All build related setting data from the build setting file are loaded into this.
 *   These setting will have any specified mode property applied.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_setting_
  extern void fake_build_load_setting(const fake_main_t main, const f_string_static_t setting_file, fake_build_setting_t *setting, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_setting_

/**
 * Assign build setting defaults.
 *
 * @param main
 *   The main data.
 * @param path_file
 *   The path to the buffer.
 * @param buffer
 *   The loaded file data.
 * @param setting
 *   All build related setting data from the build setting file are loaded into this.
 *   These setting will have any specified mode property applied.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_setting_defaults_
  extern void fake_build_load_setting_defaults(const fake_main_t main, fake_build_setting_t *setting, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_setting_defaults_

/**
 * Load and process the setting buffer.
 *
 * @param main
 *   The main data.
 * @param path_file
 *   The path to the buffer.
 * @param buffer
 *   The loaded file data.
 * @param objects
 *   The object mapping.
 * @param contents
 *   The content mapping.
 * @param setting
 *   All build related setting data from the build setting file are loaded into this.
 *   These setting will have any specified mode property applied.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_setting_process_
  extern void fake_build_load_setting_process(const fake_main_t main, const f_string_t path_file, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t *setting, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_setting_process_

/**
 * Load the environment used when executing commands.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param environment
 *   The environment data.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_environment_
  extern void fake_build_load_environment(const fake_main_t main, const fake_build_data_t data_build, f_string_maps_t *environment, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_environment_

/**
 * Load the stage file paths.
 *
 * @param main
 *   The main data.
 * @param settings_file
 *   The path to the settings file.
 * @param stage
 *   All stage file paths.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_stage_
  extern void fake_build_load_stage(const fake_main_t main, const f_string_static_t settings_file, fake_build_stage_t *stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_stage_

/**
 * Build the static objects.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_objects_static_
  extern int fake_build_objects_static(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_objects_static_

/**
 * Execute the build operation.
 *
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 * @param main
 *   The main data.
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
 * Build the script programs.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_programs_script_
  extern int fake_build_programs_script(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_programs_script_

/**
 * Build the shared programs.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_program_shared_
  extern int fake_build_program_shared(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_program_shared_

/**
 * Build the static programs.
 *
 * @param main
 *   The main data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
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
#ifndef _di_fake_build_program_static_
  extern int fake_build_program_static(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_program_static_

/**
 * Touch the given build stage file, but only if there are no current errors in status.
 *
 * @param main
 *   The main data.
 * @param file
 *   The file path to touch.
 * @param status
 *   The return status.
 *
 * @see f_file_touch()
 */
#ifndef _di_fake_build_touch_
  extern void fake_build_touch(const fake_main_t main, const f_string_dynamic_t file, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_h

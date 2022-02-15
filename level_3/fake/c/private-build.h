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

#ifndef _di_fake_build_strings_
  #define FAKE_build_header_files_s        "header files"
  #define FAKE_build_header_files_shared_s "shared header files"
  #define FAKE_build_header_files_static_s "static header files"
  #define FAKE_build_scripts_s             "scripts"
  #define FAKE_build_setting_files_s       "setting files"

  #define FAKE_build_header_files_s_length        12
  #define FAKE_build_header_files_shared_s_length 19
  #define FAKE_build_header_files_static_s_length 19
  #define FAKE_build_scripts_s_length             7
  #define FAKE_build_setting_files_s_length       13

  extern const f_string_static_t fake_build_header_files_s;
  extern const f_string_static_t fake_build_header_files_shared_s;
  extern const f_string_static_t fake_build_header_files_static_s;
  extern const f_string_static_t fake_build_scripts_s;
  extern const f_string_static_t fake_build_setting_files_s;
#endif // _di_fake_build_strings_

/**
 * Build Types.
 *
 * fake_build_type_*:
 *   - library: A library build type.
 *   - object:  An object build type.
 *   - program: A program build type.
 */
#ifndef _di_fake_build_types_
  enum {
    fake_build_type_library_e = 1,
    fake_build_type_object_e,
    fake_build_type_program_e,
  };
#endif // _di_fake_build_types_

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
 * @param type
 *   A build type from the fake_build_type_* enumeration.
 * @param arguments
 *   The arguments array to append to.
 * @param status
 *   The return status.
 *
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_arguments_standard_add_
  extern void fake_build_arguments_standard_add(fake_main_t * const main, fake_build_data_t * const data_build, const bool is_shared, const uint8_t type, f_string_dynamics_t *arguments, f_status_t *status) F_attribute_visibility_internal_d;
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
 * @param perserve_offset
 *   When a positive number, this represents the amount of characters at the front of each file to ignore.
 *   Everything after that is preserved, and the directory is created if necessary.
 *
 *   This is always treated as 0 for any file that is a directory type.
 *   Set to 0 to disable.
 *
 *   Example: 'sources/c/level_0/fss.h' with a preseve of 10, would result in the path of 'level_0/fss.h' being preserved.
 *            Whereas a perserve_offset of 0 would result in a path of 'fss.h' being used (the 'level_0/' directory is not preserved).
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_copy_
  extern void fake_build_copy(fake_main_t * const main, const f_mode_t mode, const f_string_static_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t perserve_offset, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_copy_

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
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
  extern int fake_build_execute_process_script(fake_main_t * const main, fake_build_data_t * const data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
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
 * Add the pre-compiled objects to the execute arguments array (such as "build_objects_library").
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
 * @param path
 *   The sub-path to find the object files within.
 * @param generic
 *   The generic sources to add.
 * @param specific
 *   The specific sources to add.
 * @param arguments
 *   The execute arguments array being updated.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_objects_add_
  extern f_status_t fake_build_objects_add(fake_main_t * const main, fake_build_data_t * const data_build, const f_string_static_t *path, const f_string_statics_t *generic, const f_string_statics_t *specific, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_build_objects_add_

/**
 * Execute the build operation.
 *
 * @param main
 *   The main program data.
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_operate_
  extern f_status_t fake_build_operate(fake_main_t * const main, const f_string_static_t setting_file) F_attribute_visibility_internal_d;
#endif // _di_fake_build_operate_

/**
 * Calculate the length of the sources path so that it can be used to manually construct a static string.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
 * @param setting_path_source
 *   The source path from the build settings file.
 * @param source
 *   The static string.
 *   The path_sources.string is not expected to be defined at this point.
 *   The path_sources.used is updated.
 *   The path_sources.size is ignored.
 */
#ifndef _di_fake_build_path_source_length_
  extern void fake_build_path_source_length(fake_main_t * const main, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source, f_string_static_t * const source) F_attribute_visibility_internal_d;
#endif // _di_fake_build_path_source_length_

/**
 * Construct a static string array of the sources path.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
 * @param setting_path_source
 *   The source path from the build settings file.
 * @param source
 *   The static string.
 *   The path_sources.string is expected to be defined and set to a size from path_sources.used + 1.
 *   The path_sources.used is updated.
 *   The path_sources.size is ignored.
 */
#ifndef _di_fake_build_path_source_string_
  extern void fake_build_path_source_string(fake_main_t * const main, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source, f_string_static_t * const source) F_attribute_visibility_internal_d;
#endif // _di_fake_build_path_source_string_

/**
 * Add the sources to the execute arguments array.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
 * @param generic
 *   The generic sources to add.
 * @param specific
 *   The specific sources to add.
 * @param arguments
 *   The execute arguments array being updated.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_sources_add_
  extern f_status_t fake_build_sources_add(fake_main_t * const main, fake_build_data_t * const data_build, const f_string_statics_t *generic, const f_string_statics_t *specific, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_build_sources_add_

/**
 * Add the sources object to the execute arguments array.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
 * @param generic
 *   The generic sources to add.
 * @param specific
 *   The specific sources to add.
 * @param arguments
 *   The execute arguments array being updated.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_sources_object_add_
  extern f_status_t fake_build_sources_object_add(fake_main_t * const main, fake_build_data_t * const data_build, const f_string_static_t *generic, const f_string_static_t *specific, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_build_sources_object_add_

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

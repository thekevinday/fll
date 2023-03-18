/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_h
#define _fake_build_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add the standard arguments for building a library/program.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fll_execute_arguments_add()
 * @param data_build
 *   The build data.
 * @param is_shared
 *   Set to TRUE to designate that this is adding for a shared library/program.
 *   Set to FALSE to designate that this is adding for a static library/program.
 * @param type
 *   A build type from the fake_build_type_* enumeration.
 * @param arguments
 *   The arguments array to append to.
 *
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_arguments_standard_add_
  extern void fake_build_arguments_standard_add(fake_data_t * const data, fake_build_data_t * const data_build, const bool is_shared, const uint8_t type, f_string_dynamics_t *arguments);
#endif // _di_fake_build_arguments_standard_add_

/**
 * Copy over the main setting files.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_directory_is()
 *     Errors (with error bit) from: f_file_copy()
 *     Errors (with error bit) from: f_file_name_base()
 *     Errors (with error bit) from: f_file_name_directory()
 *     Errors (with error bit) from: f_string_append()
 *     Errors (with error bit) from: f_string_dynamic_append_nulless()
 *     Errors (with error bit) from: f_string_dynamic_resize()
 *     Errors (with error bit) from: fl_directory_create()
 *     Errors (with error bit) from: fl_directory_copy()
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
 *
 * @see f_directory_is()
 * @see f_file_copy()
 * @see f_file_name_base()
 * @see f_file_name_directory()
 * @see f_string_append()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_resize()
 * @see fl_directory_create()
 * @see fl_directory_copy()
 * @see fll_program_print_signal_received()
 */
#ifndef _di_fake_build_copy_
  extern void fake_build_copy(fake_data_t * const data, const f_mode_t mode, const f_string_static_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t perserve_offset);
#endif // _di_fake_build_copy_

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_nulless()
 *     Errors (with error bit) from: f_string_dynamic_mash()
 *     Errors (with error bit) from: fll_execute_arguments_add()
 *     Errors (with error bit) from: fll_execute_arguments_add_parameter_set()
 *     Errors (with error bit) from: fll_execute_program()
 *
 *     Errors (with error bit) from: fake_build_touch()
 * @param data_build
 *   The build data.
 * @param process_script
 *   The setting_data file name fo the appropriate process script.
 *   This is expected to be either setting.process_pre or setting.process_post.
 * @param file_stage
 *   The specific stage file path.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 *
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_mash()
 * @see fll_execute_arguments_add()
 * @see fll_execute_arguments_add_parameter_set()
 * @see fll_execute_program()
 *
 * @see fake_build_touch()
 */
#ifndef _di_fake_build_execute_process_script_
  extern int fake_build_execute_process_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t process_script, const f_string_static_t file_stage);
#endif // _di_fake_build_execute_process_script_

/**
 * Get the file name without the extension and without the path parts.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_file_name_base()
 * @param path
 *   The file path to get the file name from.
 * @param name
 *   The processed filename.
 *
 * @see f_file_name_base()
 */
#ifndef _di_fake_build_get_file_name_without_extension_
  extern void fake_build_get_file_name_without_extension(fake_data_t * const data, const f_string_static_t path, f_string_dynamic_t *name);
#endif // _di_fake_build_get_file_name_without_extension_

/**
 * Add the pre-compiled objects to the execute arguments array (such as "build_objects_library").
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fll_execute_arguments_add()
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
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_objects_add_
  extern void fake_build_objects_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t *path, const f_string_statics_t *generic, const f_string_statics_t *specific, f_string_dynamics_t *arguments);
#endif // _di_fake_build_objects_add_

/**
 * Execute the build operation.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: fll_program_print_signal_received()
 *
 *     Errors (with error bit) from: fake_build_copy()
 *     Errors (with error bit) from: fake_build_execute_process_script()
 *     Errors (with error bit) from: fake_build_library_script()
 *     Errors (with error bit) from: fake_build_library_shared()
 *     Errors (with error bit) from: fake_build_library_static()
 *     Errors (with error bit) from: fake_build_load_environment()
 *     Errors (with error bit) from: fake_build_load_setting()
 *     Errors (with error bit) from: fake_build_load_stage()
 *     Errors (with error bit) from: fake_build_object_script()
 *     Errors (with error bit) from: fake_build_object_shared()
 *     Errors (with error bit) from: fake_build_object_static()
 *     Errors (with error bit) from: fake_build_objects_static()
 *     Errors (with error bit) from: fake_build_program_script()
 *     Errors (with error bit) from: fake_build_program_shared()
 *     Errors (with error bit) from: fake_build_program_static()
 *     Errors (with error bit) from: fake_build_skeleton()
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 * @param build_arguments
 *   (optional) A set of custom arguments to pass to the build.
 *   The first argument represents the name of the settings file to use.
 *   The second and on arguments represent custom modes to use.
 *   If build_arguments is NULL, then the default (or program supplied) settings file and modes are used.
 *   If build_arguments.used is 0, then the default or program parameter supplied file is used.
 *   Set the first argument used length to 0 to use the default program parameter supplied file.
 *   Set the second argument used length to 0 without any further arguments to not use any modes.
 * @param process_pipe
 *   If TRUE, then use the program input pipe.
 *   If FALSE, then ignore the program input pipe.
 *
 * @see fll_program_print_signal_received()
 *
 * @see fake_build_copy()
 * @see fake_build_execute_process_script()
 * @see fake_build_library_script()
 * @see fake_build_library_shared()
 * @see fake_build_library_static()
 * @see fake_build_load_environment()
 * @see fake_build_load_setting()
 * @see fake_build_load_stage()
 * @see fake_build_object_script()
 * @see fake_build_object_shared()
 * @see fake_build_object_static()
 * @see fake_build_objects_static()
 * @see fake_build_program_script()
 * @see fake_build_program_shared()
 * @see fake_build_program_static()
 * @see fake_build_skeleton()
 */
#ifndef _di_fake_build_operate_
  extern void fake_build_operate(fake_data_t * const data, const f_string_statics_t * const build_arguments, const bool process_pipe);
#endif // _di_fake_build_operate_

/**
 * Calculate the length of the sources path so that it can be used to manually construct a static string.
 *
 * @param data
 *   The program data.
 *
 *   This does not alter data.setting.state.status.
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
  extern void fake_build_path_source_length(fake_data_t * const data, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source, f_string_static_t * const source);
#endif // _di_fake_build_path_source_length_

/**
 * Construct a static string array of the sources path.
 *
 * @param data
 *   The program data.
 *
 *   This does not alter data.setting.state.status.
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
  extern void fake_build_path_source_string(fake_data_t * const data, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source, f_string_static_t * const source);
#endif // _di_fake_build_path_source_string_

/**
 * Add the sources to the execute arguments array.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fll_execute_arguments_add()
 * @param data_build
 *   The build data.
 * @param generic
 *   The generic sources to add.
 * @param specific
 *   The specific sources to add.
 * @param arguments
 *   The execute arguments array being updated.
 *
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_sources_add_
  extern void fake_build_sources_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_statics_t *generic, const f_string_statics_t *specific, f_string_dynamics_t *arguments);
#endif // _di_fake_build_sources_add_

/**
 * Add the sources object to the execute arguments array.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fll_execute_arguments_add()
 * @param data_build
 *   The build data.
 * @param generic
 *   The generic sources to add.
 * @param specific
 *   The specific sources to add.
 * @param arguments
 *   The execute arguments array being updated.
 *
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_sources_object_add_
  extern void fake_build_sources_object_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t *generic, const f_string_static_t *specific, f_string_dynamics_t *arguments);
#endif // _di_fake_build_sources_object_add_

/**
 * Touch the given build stage file, but only if there are no current errors in status.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_file_touch()
 * @param file
 *   The file path to touch.
 *
 * @see f_file_touch()
 * @see fll_program_print_signal_received()
 */
#ifndef _di_fake_build_touch_
  extern void fake_build_touch(fake_data_t * const data, const f_string_dynamic_t file);
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_h

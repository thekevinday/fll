/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build library functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_library_h
#define _fake_build_library_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Build the script libraries.
 *
 * If there ever are scripting languages that have a concept of libraries, then this function is here to do the job.
 * None of the built in languages support this so this function does nothing.
 *
 * One potential use of this function could be to construct a script from pieces, effectively building an "library".
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_file_link()
 *     Errors (with error bit) from: f_string_dynamics_resize()
 *     Errors (with error bit) from: fll_execute_arguments_add()
 *
 *     Errors (with error bit) from: fake_execute()
 *     Errors (with error bit) from: fake_build_arguments_standard_add()
 *     Errors (with error bit) from: fake_build_objects_add()
 *     Errors (with error bit) from: fake_build_sources_add()
 *     Errors (with error bit) from: fake_build_touch()
 * @param data_build
 *   The build data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 *
 * @see f_file_link()
 * @see f_string_dynamics_resize()
 * @see fll_execute_arguments_add()
 *
 * @see fake_execute()
 * @see fake_build_arguments_standard_add()
 * @see fake_build_objects_add()
 * @see fake_build_sources_add()
 * @see fake_build_touch()
 */
#ifndef _di_fake_build_library_script_
  extern int fake_build_library_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_library_script_

/**
 * Build the shared libraries.
 *
 * @param data
 *   The program data.
 *
 *   This modifies data.main.cache_argument.
 *   This modifies data.main.cache_arguments.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_file_link()
 *     Errors (with error bit) from: fll_execute_arguments_add()
 *
 *     Errors (with error bit) from: fake_build_objects_add()
 *     Errors (with error bit) from: fake_build_sources_add()
 *     Errors (with error bit) from: fake_build_touch()
 *     Errors (with error bit) from: fake_execute()
 * @param data_build
 *   The build data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 *
 * @see f_file_link()
 * @see fll_execute_arguments_add()
 *
 * @see fake_build_objects_add()
 * @see fake_build_sources_add()
 * @see fake_build_touch()
 * @see fake_execute()
 */
#ifndef _di_fake_build_library_shared_
  extern int fake_build_library_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_library_shared_

/**
 * Build the static libraries.
 *
 * @param data
 *   The program data.
 *
 *   This modifies data.main.cache_1.
 *   This modifies data.main.cache_2.
 *   This modifies data.main.cache_argument.
 *   This modifies data.main.cache_arguments.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_file_name_directory()
 *     Errors (with error bit) from: f_string_dynamic_append_assure()
 *     Errors (with error bit) from: f_string_dynamic_prepend()
 *     Errors (with error bit) from: fll_execute_arguments_add()
 *
 *     Errors (with error bit) from: fake_build_get_file_name_without_extension()
 *     Errors (with error bit) from: fake_build_print_compile_library_static()
 *     Errors (with error bit) from: fake_build_touch()
 *     Errors (with error bit) from: fake_execute()
 * @param data_build
 *   The build data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 *
 * @see f_file_name_directory()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_prepend()
 * @see fll_execute_arguments_add()
 *
 * @see fake_build_get_file_name_without_extension()
 * @see fake_build_print_compile_library_static()
 * @see fake_build_touch()
 * @see fake_execute()
 */
#ifndef _di_fake_build_library_static_
  extern int fake_build_library_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_library_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_library_h

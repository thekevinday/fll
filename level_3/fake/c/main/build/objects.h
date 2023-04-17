/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build objects functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_objects_h
#define _fake_build_objects_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Build static options that are needed when building a static library.
 *
 * This is neither the "build_sources_object" nor the "build_sources_object_static" property.
 * Instead, this converts the "build_sources_library" and the "build_sources_library_static" into a static object file so that the indexer program (such as GNU ar) can combine these into a static file.
 *
 * @param data
 *   The program data.
 *
 *   This modifies data.main.cache_1.
 *   This modifies data.main.cache_2.
 *   This modifies data.main.cache_argument.
 *   This modifies data.main.cache_arguments.
 *
 *   This alters data.main->settings.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_directory_create().
 *     Errors (with error bit) from: f_directory_exists().
 *     Errors (with error bit) from: f_file_name_directory().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_prepend().
 *     Errors (with error bit) from: fll_execute_arguments_add().
 *
 *     Errors (with error bit) from: fake_build_arguments_standard_add().
 *     Errors (with error bit) from: fake_build_get_file_name_without_extension().
 *     Errors (with error bit) from: fake_build_objects_add().
 *     Errors (with error bit) from: fake_execute().
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
 * @see f_directory_create()
 * @see f_directory_exists()
 * @see f_file_name_directory()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_prepend()
 * @see fll_execute_arguments_add()
 *
 * @see fake_build_arguments_standard_add()
 * @see fake_build_get_file_name_without_extension()
 * @see fake_build_objects_add()
 * @see fake_execute()
 */
#ifndef _di_fake_build_objects_static_
  extern int fake_build_objects_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_objects_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_objects_h

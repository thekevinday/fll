/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_build_load_h
#define _PRIVATE_build_load_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find the build setting file, load it, validate it, and process it.
 *
 * @param data
 *   The program data.
 * @param build_arguments
 *   (optional) A set of custom arguments to pass to the build.
 *   The first argument represents the name of the settings file to use.
 *   The second and on arguments represent custom modes to use.
 *   If build_arguments is NULL, then the default (or program supplied) settings file and modes are used.
 *   If build_arguments.used is 0, then the default or program parameter supplied file is used.
 *   Set the first argument used length to 0 to use the default program parameter supplied file.
 *   Set the second argument used length to 0 without any further arguments to not use any modes.
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
  extern void fake_build_load_setting(fake_data_t * const data, const f_string_statics_t * const build_arguments, fake_build_setting_t * const setting, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_setting_

/**
 * Override build settings based on command line arguments.
 *
 * @param data
 *   The program data.
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
#ifndef _di_fake_build_load_setting_override_
  extern void fake_build_load_setting_override(fake_data_t * const data, fake_build_setting_t * const setting, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_setting_override_

/**
 * Load and process the setting buffer.
 *
 * @param data
 *   The program data.
 * @param checks
 *   If TRUE, perform certain "required" sanity checks.
 *   If FALSE, do not perform certain "required" sanity checks (intended for a fakefile rather than a build settings file).
 * @param path_file
 *   The path to the buffer.
 * @param modes_custom
 *   (optional) When not NULL, specifies custom modes to use rather than what is provided.
 *   This also overrides command line parameters that specify the mode.
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
 *   Errors (with error bit) from: f_path_directory_cleanup().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *   Errors (with error bit) from: fll_fss_snatch_apart().
 *
 * @see f_path_directory_cleanup()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_increase_by()
 * @see fll_fss_snatch_apart()
 */
#ifndef _di_fake_build_load_setting_process_
  extern void fake_build_load_setting_process(fake_data_t * const data, const bool checks, const f_string_static_t path_file, const f_string_statics_t * const modes_custom, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t * const setting, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_setting_process_

/**
 * Load the environment used when executing commands.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   The build data.
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
  extern void fake_build_load_environment(fake_data_t * const data, fake_build_data_t * const data_build, f_string_maps_t * const environment, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_environment_

/**
 * Load the stage file paths.
 *
 * @param data
 *   The program data.
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
  extern void fake_build_load_stage(fake_data_t * const data, const f_string_static_t settings_file, fake_build_stage_t * const stage, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_load_stage_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_load_h

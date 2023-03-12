/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make load fakefile functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_load_fakefile_h
#define _fake_make_load_fakefile_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find the fake file, load it, validate it, and process it.
 *
 * This will process any additional files as necessary, such as the build settings file.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.settings.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *     Errors (with error bit) from: fake_build_load_setting().
 * @param process_pipe
 *   If TRUE, then use the program input pipe.
 *   If FALSE, then ignore the program input pipe.
 *
 * @see fake_build_load_setting()
 */
#ifndef _di_fake_make_load_fakefile_
  extern void fake_make_load_fakefile(fake_make_data_t * const data_make, const bool process_pipe);
#endif // _di_fake_make_load_fakefile_

/**
 * Load the fakefile setting "build".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 */
#ifndef _di_fake_make_load_fakefile_setting_build_
  extern void fake_make_load_fakefile_setting_build(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content);
#endif // _di_fake_make_load_fakefile_setting_build_

/**
 * Load the fakefile setting "compiler".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 * @param range_compiler
 *   A pointer to the range that representing the compiler setting within the buffer.
 */
#ifndef _di_fake_make_load_fakefile_setting_compiler_
  extern void fake_make_load_fakefile_setting_compiler(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content, f_string_range_t **range_compiler);
#endif // _di_fake_make_load_fakefile_setting_compiler_

/**
 * Load the fakefile setting "parameter".
 *
 * @param data
 *   The program data.
 *
 *   This alters data_make.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_environment_set().
 *     Errors (with error bit) from: f_string_dynamic_mash_nulless().
 *     Errors (with error bit) from: fll_fss_snatch_map_apart().
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param settings
 *   The settings data.
 *
 * @see f_environment_set()
 * @see f_string_dynamic_mash_nulless()
 * @see fll_fss_snatch_map_apart()
 */
#ifndef _di_fake_make_load_fakefile_setting_define_and_parameter_
  extern void fake_make_load_fakefile_setting_define_and_parameter(fake_data_t * const data, fake_make_data_t * const data_make, f_fss_set_t * const settings);
#endif // _di_fake_make_load_fakefile_setting_define_and_parameter_

/**
 * Load the fakefile setting "environment".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *     Errors (with error bit) from: f_string_dynamics_increase().
 * @param content
 *   The setting content.
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fake_make_load_fakefile_setting_environment_
  extern void fake_make_load_fakefile_setting_environment(fake_make_data_t * const data_make, f_fss_content_t * const content);
#endif // _di_fake_make_load_fakefile_setting_environment_

/**
 * Load the fakefile setting "fail".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 */
#ifndef _di_fake_make_load_fakefile_setting_fail_
  extern void fake_make_load_fakefile_setting_fail(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content);
#endif // _di_fake_make_load_fakefile_setting_fail_

/**
 * Load the fakefile setting "indexer".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 * @param range_indexer
 *   A pointer to the range that representing the indexer setting within the buffer.
 */
#ifndef _di_fake_make_load_fakefile_setting_indexer_
  extern void fake_make_load_fakefile_setting_indexer(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content, f_string_range_t **range_indexer);
#endif // _di_fake_make_load_fakefile_setting_indexer_

/**
 * Load the fakefile setting "parameter".
 *
 * This only processes special "parameter" settings, namely "return".
 * For all other "parameter" settings, see fake_make_load_fakefile_setting_define_and_parameter().
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_string_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_define_and_parameter().
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 *
 * @see f_string_append_assure()
 * @see f_string_dynamic_partial_append_nulless()
 *
 * @see fake_make_load_fakefile_setting_define_and_parameter()
 */
#ifndef _di_fake_make_load_fakefile_setting_parameter_
  extern void fake_make_load_fakefile_setting_parameter(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content);
#endif // _di_fake_make_load_fakefile_setting_parameter_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_load_fakefile_h

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
 *   This alters data_make.main->setting.state.status:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_fss_apply_delimit().
 *     Errors (with error bit) from: f_memory_array_resize().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_partial_append().
 *     Errors (with error bit) from: fll_fss_basic_list_read().
 *     Errors (with error bit) from: fll_fss_extended_read().
 *     Errors (with error bit) from: fll_program_standard_signal_received().
 *
 *     Errors (with error bit) from: fake_build_load_setting().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_build().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_compiler().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_define_and_parameter().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_environment().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_fail().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_indexer().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_parameter().
 *     Errors (with error bit) from: fake_file_buffer().
 *     Errors (with error bit) from: fake_pipe_buffer().
 * @param process_pipe
 *   If TRUE, then use the program input pipe.
 *   If FALSE, then ignore the program input pipe.
 *
 * @see f_fss_apply_delimit()
 * @see f_memory_array_resize()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_partial_append()
 * @see fll_fss_basic_list_read()
 * @see fll_fss_extended_read()
 * @see fll_program_standard_signal_received()
 *
 * @see fake_build_load_setting()
 * @see fake_make_load_fakefile_setting_build()
 * @see fake_make_load_fakefile_setting_compiler()
 * @see fake_make_load_fakefile_setting_define_and_parameter()
 * @see fake_make_load_fakefile_setting_environment()
 * @see fake_make_load_fakefile_setting_fail()
 * @see fake_make_load_fakefile_setting_indexer()
 * @see fake_make_load_fakefile_setting_parameter()
 * @see fake_file_buffer()
 * @see fake_pipe_buffer()
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
 *   This does not alter data_make.main.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 */
#ifndef _di_fake_make_load_fakefile_setting_build_
  extern void fake_make_load_fakefile_setting_build(fake_make_data_t * const data_make, f_range_t * const object, f_ranges_t * const content);
#endif // _di_fake_make_load_fakefile_setting_build_

/**
 * Load the fakefile setting "compiler".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.main.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 * @param range_compiler
 *   A pointer to the range that representing the compiler setting within the buffer.
 */
#ifndef _di_fake_make_load_fakefile_setting_compiler_
  extern void fake_make_load_fakefile_setting_compiler(fake_make_data_t * const data_make, f_range_t * const object, f_ranges_t * const content, f_range_t **range_compiler);
#endif // _di_fake_make_load_fakefile_setting_compiler_

/**
 * Load the fakefile setting "parameter".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_environment_set().
 *     Errors (with error bit) from: f_string_dynamic_mash().
 *     Errors (with error bit) from: f_string_dynamic_mash_nulless().
 *     Errors (with error bit) from: fll_fss_snatch_map_apart().
 *
 *     Errors (with error bit) from: fake_build_load_setting_process().
 *     Errors (with error bit) from: fake_make_operate_validate_define_name().
 * @param settings
 *   The settings data.
 *
 * @see f_environment_set()
 * @see f_string_dynamic_mash()
 * @see f_string_dynamic_mash_nulless()
 * @see fll_fss_snatch_map_apart()
 *
 * @see fake_build_load_setting_process()
 * @see fake_make_operate_validate_define_name()
 */
#ifndef _di_fake_make_load_fakefile_setting_define_and_parameter_
  extern void fake_make_load_fakefile_setting_define_and_parameter(fake_make_data_t * const data_make, f_fss_set_t * const settings);
#endif // _di_fake_make_load_fakefile_setting_define_and_parameter_

/**
 * Load the fakefile setting "environment".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 * @param content
 *   The setting content.
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 */
#ifndef _di_fake_make_load_fakefile_setting_environment_
  extern void fake_make_load_fakefile_setting_environment(fake_make_data_t * const data_make, f_ranges_t * const content);
#endif // _di_fake_make_load_fakefile_setting_environment_

/**
 * Load the fakefile setting "fail".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.main.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 */
#ifndef _di_fake_make_load_fakefile_setting_fail_
  extern void fake_make_load_fakefile_setting_fail(fake_make_data_t * const data_make, f_range_t * const object, f_ranges_t * const content);
#endif // _di_fake_make_load_fakefile_setting_fail_

/**
 * Load the fakefile setting "indexer".
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.main.setting.state.status.
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 * @param range_indexer
 *   A pointer to the range that representing the indexer setting within the buffer.
 */
#ifndef _di_fake_make_load_fakefile_setting_indexer_
  extern void fake_make_load_fakefile_setting_indexer(fake_make_data_t * const data_make, f_range_t * const object, f_ranges_t * const content, f_range_t **range_indexer);
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
 *   This alters data_make.main->setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_string_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *     Errors (with error bit) from: fake_make_load_fakefile_setting_define_and_parameter().
 * @param object
 *   The setting object.
 * @param content
 *   The setting content.
 *
 * @see f_string_append_assure()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_partial_append_nulless()
 *
 * @see fake_make_load_fakefile_setting_define_and_parameter()
 */
#ifndef _di_fake_make_load_fakefile_setting_parameter_
  extern void fake_make_load_fakefile_setting_parameter(fake_make_data_t * const data_make, f_range_t * const object, f_ranges_t * const content);
#endif // _di_fake_make_load_fakefile_setting_parameter_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_load_fakefile_h

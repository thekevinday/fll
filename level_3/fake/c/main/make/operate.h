/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make operate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_operate_h
#define _fake_make_operate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the make sections and their respective operations.
 *
 * The first section operated on is the 'main' section.
 * The 'settings' section is only loaded into settings and is never operated on.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_okay on success.
 *     F_data_not on success but fakefile is empty.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_directory_open()
 *     Errors (with error bit) from: f_path_change_at()
 *     Errors (with error bit) from: f_path_current()
 *     Errors (with error bit) from: f_string_dynamics_increase()
 *
 *     Errors (with error bit) from: fake_make_load_fakefile()
 *     Errors (with error bit) from: fake_make_load_parameters()
 *     Errors (with error bit) from: fake_make_operate_section()
 *
 * @see f_directory_open()
 * @see f_path_change_at()
 * @see f_path_current()
 * @see f_string_dynamics_increase()
 * @see fll_program_print_signal_received()
 *
 * @see fake_make_load_fakefile()
 * @see fake_make_load_parameters()
 * @see fake_make_operate_section()
 */
#ifndef _di_fake_make_operate_
  extern void fake_make_operate(fake_data_t * const data);
#endif // _di_fake_make_operate_

/**
 * For a given make section operation, expand the content into an arguments array for that operation.
 *
 * This prints errors via data_make.error.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_okay on success.
 *     F_data_not on success but fakefile is empty.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_string_dynamic_append()
 *     Errors (with error bit) from: f_string_dynamic_append_assure()
 *     Errors (with error bit) from: f_string_dynamic_append_nulless()
 *     Errors (with error bit) from: f_string_dynamic_increase_by()
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless()
 *     Errors (with error bit) from: f_string_dynamics_increase()
 *     Errors (with error bit) from: f_string_dynamics_increase_by()
 *     Errors (with error bit) from: fl_iki_read()
 *     Errors (with error bit) from: f_compare_dynamic_partial_string()
 *
 *     Errors (with error bit) from: fake_make_operate_expand_build()
 *     Errors (with error bit) from: fake_make_operate_expand_context()
 *     Errors (with error bit) from: fake_make_operate_expand_environment()
 * @param section_name
 *   The section name.
 * @param content
 *   The content array.
 * @param quotes
 *   The array of quotes associated with the content.
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_increase()
 * @see f_string_dynamics_increase_by()
 * @see fl_iki_read()
 * @see f_compare_dynamic_partial_string()
 *
 * @see fake_make_operate_expand_build()
 * @see fake_make_operate_expand_context()
 * @see fake_make_operate_expand_environment()
 */
#ifndef _di_fake_make_operate_expand_
  extern void fake_make_operate_expand(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_ranges_t content, const f_uint8s_t quotes);
#endif // _di_fake_make_operate_expand_

/**
 * Perform the expand operation, specifically for the build settings.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data.main->setting.state.status:
 *     F_data_not on success, but nothing is added (data length to append is 0).
 *     F_true on success and match expanded.
 *     F_false on no matches to expand.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_nulless()
 *     Errors (with error bit) from: f_string_dynamic_mash()
 *     Errors (with error bit) from: f_string_dynamics_increase()
 * @param quote
 *   The quote associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make.main.buffer.
 *
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_mash()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fake_make_operate_expand_build_
  extern void fake_make_operate_expand_build(fake_make_data_t * const data_make, const uint8_t quote, const f_string_range_t range_name);
#endif // _di_fake_make_operate_expand_build_

/**
 * Perform the expand operation, specifically for the context variables.
 *
 * Unknown or unsupported context variables are expanded into an empty string.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data.main->setting.state.status:
 *     F_true on success and match expanded.
 *     F_false on no matches to expand.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_nulless()
 * @param quote
 *   The quote associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make.main.buffer.
 *
 * @see f_string_dynamic_append_nulless()
 */
#ifndef _di_fake_make_operate_expand_context_
  extern void fake_make_operate_expand_context(fake_make_data_t * const data_make, const uint8_t quote, const f_string_range_t range_name);
#endif // _di_fake_make_operate_expand_context_

/**
 * Perform the expand operation, specifically for the environment variables.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data.main->setting.state.status:
 *     F_data_not on success, but nothing is added (data length to append is 0).
 *     F_true on success and match expanded.
 *     F_false on no matches to expand.
 *
 *     Errors (with error bit) from: f_environment_get().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_increase_by().
 *     Errors (with error bit) from: f_string_dynamics_increase().
 * @param quote
 *   The quote associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make.main.buffer.
 *
 * @see f_environment_get()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fake_make_operate_expand_environment_
  extern void fake_make_operate_expand_environment(fake_make_data_t * const data_make, const uint8_t quote, const f_string_range_t range_name);
#endif // _di_fake_make_operate_expand_environment_

/**
 * Perform the make operations within the given section.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_okay on success.
 *     F_child on child process exiting.
 *     F_signal_abort on abort signal received.
 *     F_signal_quit on quit signal received.
 *
 *     F_failure (with error bit) on failure.
 *     F_interrupt (with error bit) on interrupt signal received.
 *     F_parameter (with error bit) on invalid parameter.
 *     F_recurse (with error bit) is returned if unable to recurse to another operation section (usually max stack depth reached).
 *     F_valid_not (with error bit) is returned if any part of the section is invalid, such as an invalid operation name.
 *
 *     Errors (with error bit) from: f_memory_array_increase()
 *
 *     Errors (with error bit) from: fake_make_operate_block_postprocess()
 *     Errors (with error bit) from: fake_make_operate_block_prepare()
 *     Errors (with error bit) from: fake_make_operate_expand()
 *     Errors (with error bit) from: fake_make_operate_process()
 *     Errors (with error bit) from: fake_make_operate_validate()
 * @param id_section
 *   The array location id within the fakefile of the section to operate on.
 * @param section_stack
 *   The current operation stack.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 *
 * @see f_memory_array_increase()
 *
 * @see fake_make_operate_block_postprocess()
 * @see fake_make_operate_block_prepare()
 * @see fake_make_operate_expand()
 * @see fake_make_operate_process()
 * @see fake_make_operate_validate()
 */
#ifndef _di_fake_make_operate_section_
  extern int fake_make_operate_section(fake_make_data_t * const data_make, const f_number_unsigned_t id_section, f_number_unsigneds_t *section_stack);
#endif // _di_fake_make_operate_section_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_h

/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_operate_h
#define _PRIVATE_make_operate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the make sections and their respective operations.
 *
 * The first section operated on is the 'main' section.
 * The 'settings' section is only loaded into settings and is never operated on.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_
  extern f_status_t fake_make_operate(fake_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_

/**
 * For a given make section operation, expand the content into an arguments array for that operation.
 *
 * This prints errors via data_make.error.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation being performed.
 * @param content
 *   The content array.
 * @param quoteds
 *   The array of quoted associated with the content.
 * @param arguments
 *   The expanded arguments.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_
  extern void fake_make_operate_expand(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_array_length_t operation, const f_fss_content_t content, const f_fss_quotes_t quoteds, f_string_dynamics_t * const arguments, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_

/**
 * Perform the expand operation, specifically for the context variables.
 *
 * Unknown or unsupported context variables are expanded into an empty string.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_context_
  extern f_status_t fake_make_operate_expand_context(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t * const arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_context_

/**
 * Perform the expand operation, specifically for the environment variables.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fake_make_operate_expand_environment_
  extern f_status_t fake_make_operate_expand_environment(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t * const arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_environment_

/**
 * Perform the expand operation, specifically for the build settings.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_build_
  extern f_status_t fake_make_operate_expand_build(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t * const arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_build_

/**
 * Perform the make operations within the given section.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param id_section
 *   The array location id within the fakefile of the section to operate on.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *   F_recurse (with error bit) is returned if unable to recurse to another operation section (usually max stack depth reached).
 *   F_valid_not (with error bit) is returned if any part of the section is invalid, such as an invalid operation name.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_make_operate_section_
  int fake_make_operate_section(fake_make_data_t * const data_make, const f_array_length_t id_section, f_array_lengths_t *section_stack, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_section_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_operate_h

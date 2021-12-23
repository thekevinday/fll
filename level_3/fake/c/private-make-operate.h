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
 * @param main
 *   The main program data.
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
  extern void fake_make_operate_expand(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_range_t section_name, const f_array_length_t operation, const f_fss_content_t content, const f_fss_quotes_t quoteds, f_string_dynamics_t *arguments, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_

/**
 * Perform the expand operation, specifically for the environment variables.
 *
 * @param main
 *   The main program data.
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
#ifndef _di_fake_make_operate_expand_environment_
  extern f_status_t fake_make_operate_expand_environment(fake_main_t * const main, fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_environment_

/**
 * Perform the expand operation, specifically for the build settings.
 *
 * @param main
 *   The main program data.
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
  extern f_status_t fake_make_operate_expand_build(fake_main_t * const main, fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_expand_build_

/**
 * Perform the make operations within the given section.
 *
 * @param main
 *   The main program data.
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
  int fake_make_operate_section(fake_main_t * const main, fake_make_data_t * const data_make, const f_array_length_t id_section, f_array_lengths_t *section_stack, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_section_

/**
 * Perform a specific make operation within the given section.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param section_name
 *   The section name.
 * @param arguments
 *   The expanded arguments.
 * @param success
 *   Whether or not a previous section operation succeeded or failed.
 * @param state_process
 *   The operation and if-condition states.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_make_operate_process_
  extern int fake_make_operate_process(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, const bool success, fake_state_process_t *state_process, f_array_lengths_t *section_stack, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param program
 *   The program to be executed.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_execute_
  extern f_status_t fake_make_operate_process_execute(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_execute_

/**
 * Handle the return code, converting it to a standard return number and store it as a string.
 *
 * The return value is stored in: data_make.setting_make.parameter.array[0].value.array[0].
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param return_code
 *   The return code to process.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on identifying the return code as an error code and fail mode is set to fake_make_operation_fail_type_exit.
 *
 *   Errors (with error bit) from: f_conversion_number_signed_to_string().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_string_append()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_terminate_after()
 */
#ifndef _di_fake_make_operate_process_return_
  extern f_status_t fake_make_operate_process_return(fake_main_t * const main, fake_make_data_t * const data_make, const int return_code) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_return_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_run_
  extern f_status_t fake_make_operate_process_run(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_statics_t arguments, const bool as_shell) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_run_

/**
 * For a given make section operation, validate the given operation.
 *
 * This performs pre-operation validations.
 * Additional issues may occure when running operations that are not detected nor detectable by this.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param section_name
 *   The section name.
 * @param arguments
 *   The expanded arguments.
 * @param state_process
 *   The operation and if-condition operation states.
 *   This condition will be updated by this as appropriate.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_validate_
  extern void fake_make_operate_validate(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, fake_state_process_t *state_process, f_array_lengths_t *section_stack, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_validate_

/**
 * Validate that the given define variable name is valid.
 *
 * A valid define variable name must begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @fixme make this UTF-8 friendly.
 *
 * @param name
 *   The variable name string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 */
#ifndef _di_fake_make_operate_validate_define_name_
  extern f_status_t fake_make_operate_validate_define_name(const f_string_static_t name) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_validate_define_name_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_operate_h

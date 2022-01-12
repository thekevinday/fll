/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_operate_process_h
#define _PRIVATE_make_operate_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform a specific make operation within the given section.
 *
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
  extern int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, const bool success, fake_state_process_t *state_process, f_array_lengths_t *section_stack, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_

/**
 * Execute either the run operation or the shell operation.
 *
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
  extern f_status_t fake_make_operate_process_execute(fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_execute_

/**
 * Handle the return code, converting it to a standard return number and store it as a string.
 *
 * The return value is stored in: data_make.setting_make.parameter.array[0].value.array[0].
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param return_code
 *   The return code to process.
 *
 * @return
 *   F_none on success.
 *   F_failure on identifying the return code as an error code and fail mode is not set to fake_make_operation_fail_type_exit_e.
 *
 *   F_failure (with error bit) on identifying the return code as an error code and fail mode is set to fake_make_operation_fail_type_exit_e.
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
  extern f_status_t fake_make_operate_process_return(fake_make_data_t * const data_make, const int return_code) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_return_

/**
 * Execute either the run operation or the shell operation.
 *
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
  extern f_status_t fake_make_operate_process_run(fake_make_data_t * const data_make, const f_string_statics_t arguments, const bool as_shell) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_operate_process_h

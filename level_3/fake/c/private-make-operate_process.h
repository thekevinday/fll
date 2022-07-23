/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.6
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
 *
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_make_operate_process_
  extern int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, fake_state_process_t * const state_process, f_array_lengths_t * const section_stack, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_

/**
 * Process the given string, converting escape sequences into code.
 *
 * The following escape sequences are supported for printing special characters:
 *   - "\f": Form Feed.
 *   - "\n": New Line.
 *   - "\r": Carriage Return.
 *   - "\t": Tab.
 *   - "\v": Vertical Tab.
 *   - "\\": Backslash Character (may require additional slashes in certain circumstances.)
 *   - "\0": NULL Character.
 *   - "\U+": Unicode Sequence (followed by a valid Unicode sequence with a minimum 4 hexidecimal digits and a maximum of 6 hexidecimal digits).
 *   - "\!": Non-printing separator, allowing for "\U+000A\ 5" to be equivalent to "\n5".
 *
 * If the Unicode is invalid, then nothing is copied for that character (the invalid character is skipped when printing).
 * Example Unicodes\:
 *   - "\U+000A": Prints a new line, equivalent to "\n".
 *   - "\U+2E19": Prints the Unicode feather-like character "⸙".
 *
 * Only ASCII alpha-numeric hexidecimal digits are allowed in the Unicode sequence (upper or lower case).
 *
 * Invalid or unknown escape sequences are not copied.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param source
 *   The source string to process and esacpe.
 * @param destination
 *   The processed and escaped string.
 *   This is appended to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source.used is 0.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *   Errors (with error bit) from: f_utf_unicode_from().
 *   Errors (with error bit) from: f_utf_unicode_string_to().
 *
 * @see f_string_dynamic_increase_by()
 * @see f_utf_unicode_from()
 * @see f_utf_unicode_string_to()
 */
#ifndef _di_fake_make_operate_process_buffer_escape_
  extern f_status_t fake_make_operate_process_buffer_escape(fake_make_data_t * const data_make, const f_string_static_t source, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_buffer_escape_

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
 *   F_data_not if both program.used is 0 and arguments.used is 0.
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
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_string_append()
 * @see f_string_dynamic_append()
 */
#ifndef _di_fake_make_operate_process_return_
  extern f_status_t fake_make_operate_process_return(fake_make_data_t * const data_make, const int return_code) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_return_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 *
 * @return
 *   F_data_not if arguments.used is 0.
 *
 *   Success results from: fake_make_operate_process_execute().
 *
 *   Errors (with error bit) from: fake_make_operate_process_execute().
 */
#ifndef _di_fake_make_operate_process_run_
  extern f_status_t fake_make_operate_process_run(fake_make_data_t * const data_make, const bool as_shell) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_operate_process_h

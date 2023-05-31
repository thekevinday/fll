/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make operate process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_operate_process_h
#define _fake_make_operate_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform a specific make operation within the given section.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: fake_make_operate_process_run()
 *     Errors (with error bit) from: fake_make_operate_process_type_break()
 *     Errors (with error bit) from: fake_make_operate_process_type_build()
 *     Errors (with error bit) from: fake_make_operate_process_type_clean()
 *     Errors (with error bit) from: fake_make_operate_process_type_copy()
 *     Errors (with error bit) from: fake_make_operate_process_type_compile()
 *     Errors (with error bit) from: fake_make_operate_process_type_copy()
 *     Errors (with error bit) from: fake_make_operate_process_type_define()
 *     Errors (with error bit) from: fake_make_operate_process_type_deletes()
 *     Errors (with error bit) from: fake_make_operate_process_type_deletes()
 *     Errors (with error bit) from: fake_make_operate_process_type_exit()
 *     Errors (with error bit) from: fake_make_operate_process_type_fail()
 *     Errors (with error bit) from: fake_make_operate_process_type_groups()
 *     Errors (with error bit) from: fake_make_operate_process_type_groups()
 *     Errors (with error bit) from: fake_make_operate_process_type_condition()
 *     Errors (with error bit) from: fake_make_operate_process_type_index()
 *     Errors (with error bit) from: fake_make_operate_process_type_link()
 *     Errors (with error bit) from: fake_make_operate_process_type_modes()
 *     Errors (with error bit) from: fake_make_operate_process_type_modes()
 *     Errors (with error bit) from: fake_make_operate_process_type_move()
 *     Errors (with error bit) from: fake_make_operate_process_type_operate()
 *     Errors (with error bit) from: fake_make_operate_process_type_owners()
 *     Errors (with error bit) from: fake_make_operate_process_type_owners()
 *     Errors (with error bit) from: fake_make_operate_process_type_parameter()
 *     Errors (with error bit) from: fake_make_operate_process_type_pop()
 *     Errors (with error bit) from: fake_make_operate_process_type_print()
 *     Errors (with error bit) from: fake_make_operate_process_type_skeleton()
 *     Errors (with error bit) from: fake_make_operate_process_type_to()
 *     Errors (with error bit) from: fake_make_operate_process_type_top()
 *     Errors (with error bit) from: fake_make_operate_process_type_touch()
 *     Errors (with error bit) from: fake_make_operate_process_type_write()
 * @param section_name
 *   The section name.
 * @param state_process
 *   The operation and if-condition states.
 * @param section_stack
 *   The current operation stack.
 *
 * @return
 *   The return code of the execution process.
 *
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 *
 * @see fake_make_operate_process_run()
 * @see fake_make_operate_process_type_break()
 * @see fake_make_operate_process_type_build()
 * @see fake_make_operate_process_type_clean()
 * @see fake_make_operate_process_type_copy()
 * @see fake_make_operate_process_type_compile()
 * @see fake_make_operate_process_type_copy()
 * @see fake_make_operate_process_type_define()
 * @see fake_make_operate_process_type_deletes()
 * @see fake_make_operate_process_type_deletes()
 * @see fake_make_operate_process_type_exit()
 * @see fake_make_operate_process_type_fail()
 * @see fake_make_operate_process_type_groups()
 * @see fake_make_operate_process_type_groups()
 * @see fake_make_operate_process_type_condition()
 * @see fake_make_operate_process_type_index()
 * @see fake_make_operate_process_type_link()
 * @see fake_make_operate_process_type_modes()
 * @see fake_make_operate_process_type_modes()
 * @see fake_make_operate_process_type_move()
 * @see fake_make_operate_process_type_operate()
 * @see fake_make_operate_process_type_owners()
 * @see fake_make_operate_process_type_owners()
 * @see fake_make_operate_process_type_parameter()
 * @see fake_make_operate_process_type_pop()
 * @see fake_make_operate_process_type_print()
 * @see fake_make_operate_process_type_skeleton()
 * @see fake_make_operate_process_type_to()
 * @see fake_make_operate_process_type_top()
 * @see fake_make_operate_process_type_touch()
 * @see fake_make_operate_process_type_write()
 */
#ifndef _di_fake_make_operate_process_
  extern int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, fake_state_process_t * const state_process, f_array_lengths_t * const section_stack);
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
 *   - "\U+": Unicode Sequence (followed by a valid Unicode sequence with a minimum 4 hexadecimal digits and a maximum of 6 hexadecimal digits).
 *   - "\!": Non-printing separator, allowing for "\U+000A\ 5" to be equivalent to "\n5".
 *
 * If the Unicode is invalid, then nothing is copied for that character (the invalid character is skipped when printing).
 * Example Unicodes\:
 *   - "\U+000A": Prints a new line, equivalent to "\n".
 *   - "\U+2E19": Prints the Unicode feather-like character "⸙".
 *
 * Only ASCII alpha-numeric hexadecimal digits are allowed in the Unicode sequence (upper or lower case).
 *
 * Invalid or unknown escape sequences are not copied.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters date_make.setting.state.status:
 *     F_none on success.
 *     F_data_not if source.used is 0.
 *
 *     Errors (with error bit) from: f_string_dynamic_increase_by().
 *     Errors (with error bit) from: f_utf_unicode_from().
 *     Errors (with error bit) from: f_utf_unicode_string_to().
 * @param source
 *   The source string to process and esacpe.
 * @param destination
 *   The processed and escaped string.
 *   This is appended to.
 *
 * @see f_string_dynamic_increase_by()
 * @see f_utf_unicode_from()
 * @see f_utf_unicode_string_to()
 */
#ifndef _di_fake_make_operate_process_buffer_escape_
  extern void fake_make_operate_process_buffer_escape(fake_make_data_t * const data_make, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_fake_make_operate_process_buffer_escape_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters date_make.setting.state.status:
 *     F_none on success.
 *     F_data_not if both program.used is 0 and arguments.used is 0.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_environment_get_all().
 *     Errors (with error bit) from: fl_environment_load_names().
 *     Errors (with error bit) from: fll_execute_program().
 *
 *     Errors (with error bit) from: fake_make_operate_process_return().
 *
 *     Status codes (with error bit) are returned on any problem.
 * @param program
 *   The program to be executed.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 *
 * @see f_environment_get_all()
 * @see fl_environment_load_names()
 * @see fll_execute_program()
 * @see fll_program_standard_signal_received()
 *
 * @see fake_make_operate_process_return()
 */
#ifndef _di_fake_make_operate_process_execute_
  extern void fake_make_operate_process_execute(fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell);
#endif // _di_fake_make_operate_process_execute_

/**
 * Handle the return code, converting it to a standard return number and store it as a string.
 *
 * The return value is stored in: data_make.main->setting_make.parameter.array[0].value.array[0].
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters date_make.setting.state.status:
 *     F_none on success.
 *     F_failure on identifying the return code as an error code and fail mode is not set to fake_make_operation_fail_exit_e.
 *
 *     F_failure (with error bit) on identifying the return code as an error code and fail mode is set to fake_make_operation_fail_exit_e.
 *
 *     Errors (with error bit) from: f_conversion_number_signed_to_string().
 *     Errors (with error bit) from: f_string_append().
 *     Errors (with error bit) from: f_string_dynamic_append().
 * @param return_code
 *   The return code to process.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_string_append()
 * @see f_string_dynamic_append()
 */
#ifndef _di_fake_make_operate_process_return_
  extern void fake_make_operate_process_return(fake_make_data_t * const data_make, const int return_code);
#endif // _di_fake_make_operate_process_return_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters date_make.setting.state.status:
 *     F_data_not if arguments.used is 0.
 *
 *     Success results from: fake_make_operate_process_execute().
 *
 *     Errors (with error bit) from: fake_make_operate_process_execute().
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 *
 * @see fake_make_operate_process_execute()
 */
#ifndef _di_fake_make_operate_process_run_
  extern void fake_make_operate_process_run(fake_make_data_t * const data_make, const bool as_shell);
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_process_h
/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides error print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_error_h
#define _fake_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * This does not print a leading first line, better allowing it to be used while loading settings or before the normal first line is printed.
 *
 * @param print
 *   Designates the how and where to print.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The function name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_
  extern f_status_t fake_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_fake_print_error_

/**
 * Print an error message for when an argument is an empty string.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param index
 *   The index of the argument that is an empty string.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_number()
 */
#ifndef _di_fake_print_error_argument_empty_
  extern f_status_t fake_print_error_argument_empty(fl_print_t * const print, const f_number_unsigned_t index);
#endif // _di_fake_print_error_argument_empty_

/**
 * Print build operation file error messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param function
 *   The name of the function where the error happened.
 * @param operation
 *   The operation performed.
 * @param source
 *   The operation source.
 * @param destination
 *   The operation destination, if applicable.
 *   Set destination.used to 0 to disable.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if print is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_build_operation_file_
  extern f_status_t fake_print_error_build_operation_file(fl_print_t * const print, const f_string_t function, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const bool fallback);
#endif // _di_fake_print_error_build_operation_file_

/**
 * Print build operation file error messages.
 *
 * This prints the "copy source to destination" part of the message.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param before
 *   The string being printed before the variable.
 *   Likely should have a space added at the end of the string.
 * @param operation
 *   The operation performed.
 * @param source
 *   The operation source.
 * @param destination
 *   The operation destination, if applicable.
 *   Set destination.used to 0 to disable.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if print is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_error_build_operation_file_partial()
 */
#ifndef _di_fake_print_error_build_operation_file_full_
  extern f_status_t fake_print_error_build_operation_file_full(fl_print_t * const print, const f_string_t before, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const f_string_t after);
#endif // _di_fake_print_error_build_operation_file_full_

/**
 * Helper function for printing build operation file error messages.
 *
 * This prints the "copy source to destination" part of the message.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation
 *   The operation performed.
 * @param source
 *   The operation source.
 * @param destination
 *   The operation destination, if applicable.
 *   Set destination.used to 0 to disable.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 *   Not optional when destination.used is not 0.
 *   Not used when destination.used is 0.
 *
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_build_operation_file_partial_
  extern void fake_print_error_build_operation_file_partial(fl_print_t * const print, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how);
#endif // _di_fake_print_error_build_operation_file_partial_

/**
 * Print error message regarding file create directory failure due to a missing or invalid parent directory.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_file_create_parent_missing_
  extern f_status_t fake_print_error_file_create_parent_missing(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_error_file_create_parent_missing_

/**
 * Print error message for when an operation fails.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation
 *   The identifier of the operation that failed.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_failure_operation_
  extern f_status_t fake_print_error_failure_operation(fl_print_t * const print, const uint8_t operation);
#endif // _di_fake_print_error_failure_operation_

/**
 * Print error message for when an operation fails.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param script
 *   The name of the script that failed.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_failure_script_
  extern f_status_t fake_print_error_failure_script(fl_print_t * const print, const f_string_static_t script);
#endif // _di_fake_print_error_failure_script_

/**
 * Print generic error message regarding a function failing in some way, setting fallback to F_false and returning result.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param function
 *   The function name.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed..
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_fallback_
  extern f_status_t fake_print_error_fallback(fl_print_t * const print, const f_string_t function);
#endif // _di_fake_print_error_fallback_

/**
 * Print file related error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_file_
  extern f_status_t fake_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fake_print_error_file_

/**
 * Print error message regarding file create failure due to a missing or invalid parent directory.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param path
 *   The name of the file or directory.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_directory_create_parent_missing_
  extern f_status_t fake_print_error_directory_create_parent_missing(fl_print_t * const print, const f_string_static_t path);
#endif // _di_fake_print_error_directory_create_parent_missing_

/**
 * Print error message regarding program needed for execution is not found.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param program
 *   The name of the not found program.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple_variable()
 */
#ifndef _di_fake_print_error_execute_program_not_found_
  extern f_status_t fake_print_error_execute_program_not_found(fl_print_t * const print, const f_string_static_t program);
#endif // _di_fake_print_error_execute_program_not_found_

/**
 * Print file related error message regarding a function failing in some way.
 *
 * This prints a simple message to avoid "Unable to find file..., because file cannot be found." type of messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_file_simple_
  extern f_status_t fake_print_error_file_simple(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fake_print_error_file_simple_

/**
 * Print FSS error messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param function
 *   The function call that returned the error.
 * @param path_file
 *   The path to the file.
 * @param range
 *   The range representing the position in the buffer such that range.start is where the error happened.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_error_fss_message()
 */
#ifndef _di_fake_print_error_fss_
  extern f_status_t fake_print_error_fss(fl_print_t * const print, const f_string_t function, const f_string_static_t path_file, const f_string_range_t range, const bool fallback);
#endif // _di_fake_print_error_fss_

/**
 * Print specific FSS error message.
 *
 * This is primarily used by numerous error print functions to reduce code.
 * This is not used for any error print functions that has complex format structures.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param function
 *   The function call that returned the error.
 * @param path_file
 *   The path to the file.
 * @param range
 *   The range representing the position in the buffer such that range.start is where the error happened.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_fss_message_
  extern f_status_t fake_print_error_fss_message(fl_print_t * const print, const f_string_t prefix, const f_string_t before, const f_number_unsigned_t number, const f_string_t middle, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_error_fss_message_

/**
 * Print error message regarding the group not being found.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param group
 *   A string representing the group (either as a name or as a group ID).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_group_not_found_
  extern f_status_t fake_print_error_group_not_found(fl_print_t * const print, const f_string_static_t group);
#endif // _di_fake_print_error_group_not_found_

/**
 * Print error message regarding the mode being invalid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param mode
 *   A string representing the invalid mode.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_mode_invalid_
  extern f_status_t fake_print_error_mode_invalid(fl_print_t * const print, const f_string_static_t mode);
#endif // _di_fake_print_error_mode_invalid_

/**
 * Print error message regarding the number being too large.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param number
 *   A string representing the number that is too large.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_number_too_large_
  extern f_status_t fake_print_error_number_too_large(fl_print_t * const print, const f_string_static_t number);
#endif // _di_fake_print_error_number_too_large_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation failed.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_operation_failed_
  extern f_status_t fake_print_error_operation_failed(fl_print_t * const print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name);
#endif // _di_fake_print_error_operation_failed_

/**
 * Print error messages when a given link argument is unknown.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param argument
 *   The argument that is unknown by the link operation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_operation_link_argument_unknown_
  extern f_status_t fake_print_error_operation_link_argument_unknown(fl_print_t * const print, const f_string_static_t argument);
#endif // _di_fake_print_error_operation_link_argument_unknown_

/**
 * Print error messages when a given link point file already exists.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param argument
 *   The argument representing the point file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_operation_link_point_exists_
  extern f_status_t fake_print_error_operation_link_point_exists(fl_print_t * const print, const f_string_static_t argument);
#endif // _di_fake_print_error_operation_link_point_exists_

/**
 * Print error messages when a given link target file does not already exist.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param argument
 *   The argument representing the point file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_common_wrapped_variable()
 */
#ifndef _di_fake_print_error_operation_link_target_exists_not_
  extern f_status_t fake_print_error_operation_link_target_exists_not(fl_print_t * const print, const f_string_static_t argument);
#endif // _di_fake_print_error_operation_link_target_exists_not_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation has a path outside of the project root.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param function
 *   The name of the function where the error happened.
 * @param path
 *   The path that is outside of the project path.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_operation_path_outside_
  extern f_status_t fake_print_error_operation_path_outside(fl_print_t * const print, const f_string_t function, const f_string_static_t path);
#endif // _fake_print_error_operation_path_outside_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation.
 *
 * @param data
 *   The program data.
 * @param error
 *   Designates how the section error/warning should be printed.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param path
 *   The path to the directory.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_operation_path_stack_max_
  extern f_status_t fake_print_error_operation_path_stack_max(fl_print_t * const print, const f_string_t function, const f_string_static_t path);
#endif // _di_fake_print_error_operation_path_stack_max_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that the max stack depth is reached.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 * @param stack_max
 *   The max stack depth.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_operation_stack_max_
  extern f_status_t fake_print_error_operation_stack_max(fl_print_t * const print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_number_unsigned_t stack_max);
#endif // _di_fake_print_error_operation_stack_max_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation is invalid.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_operation_unknown_
  extern f_status_t fake_print_error_operation_unknown(fl_print_t * const print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name);
#endif // _di_fake_print_error_operation_unknown_

/**
 * Print error message for when the parameter value is an empty string.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param symbol
 *   The symbol of the parameter.
 * @param name
 *   The name of the parameter.
 * @param value
 *   The value that is invalid.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_parameter()
 */
#ifndef _di_fake_print_error_parameter_not_empty_
  extern f_status_t fake_print_error_parameter_not_empty(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_not_empty_

/**
 * Print error message for when the directory parameter value is not found.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param symbol
 *   The symbol of the parameter.
 * @param name
 *   The name of the parameter.
 * @param value
 *   The value that is not found.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_parameter_value()
 */
#ifndef _di_fake_print_error_parameter_directory_not_found_path_
  extern f_status_t fake_print_error_parameter_directory_not_found_path(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_directory_not_found_path_

/**
 * Print error message for when the parameter value contains a non-word, non-minus, and non-plus character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param symbol
 *   The symbol of the parameter.
 * @param name
 *   The name of the parameter.
 * @param value
 *   The value that is invalid.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_parameter_not_word_
  extern f_status_t fake_print_error_parameter_not_word(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_not_word_

/**
 * Print error message for when two designated operations cannot be used together.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation_1
 *   The name of the first operation that cannot be used.
 * @param operation_2
 *   The name of the second operation that cannot be used.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variables()
 */
#ifndef _di_fake_print_error_parameter_operation_not_with_
  extern f_status_t fake_print_error_parameter_operation_not_with(fl_print_t * const print, const f_string_static_t operation_1, const f_string_static_t operation_2);
#endif // _di_fake_print_error_parameter_operation_not_with_

/**
 * Print an error message for when the parameter is specified too many times.
 *
 * @param data
 *   The program data.
 * @param parameter
 *   The parameter name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_parameter()
 */
#ifndef _di_fake_print_error_parameter_too_many_
  extern f_status_t fake_print_error_parameter_too_many(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t parameter);
#endif // _di_fake_print_error_parameter_too_many_

/**
 * Print an error message for when there are more arguments are required (such as to a fakefile operation).
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple()
 */
#ifndef _di_fake_print_error_requires_more_arguments_
  extern f_status_t fake_print_error_requires_more_arguments(fl_print_t * const print);
#endif // _di_fake_print_error_requires_more_arguments_

/**
 * Print an error message for when there are too many arguments passed (such as to a fakefile operation).
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_simple()
 */
#ifndef _di_fake_print_error_too_many_arguments_
  extern f_status_t fake_print_error_too_many_arguments(fl_print_t * const print);
#endif // _di_fake_print_error_too_many_arguments_

/**
 * Print error message regarding the user not being found.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param user
 *   A string representing the user (either as a name or as a user ID).
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_variable()
 */
#ifndef _di_fake_print_error_user_not_found_
  extern f_status_t fake_print_error_user_not_found(fl_print_t * const print, const f_string_static_t user);
#endif // _di_fake_print_error_user_not_found_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_error_h

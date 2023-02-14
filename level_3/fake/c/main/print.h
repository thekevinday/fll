/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_print_h
#define _fake_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_print()
 */
#ifndef _di_fake_print_error_
  extern f_status_t fake_print_error(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function);
#endif // _di_fake_print_error_

/**
 * Print generic error message regarding a function failing in some way, setting fallback to F_false and returning result.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_print()
 */
#ifndef _di_fake_print_error_fallback_
  extern f_status_t fake_print_error_fallback(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function);
#endif // _di_fake_print_error_fallback_

/**
 * Print file related error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
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
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_file_
  extern f_status_t fake_print_error_file(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fake_print_error_file_

/**
 * Print file related error message regarding a function failing in some way, setting fallback to F_false and returning result..
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
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
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_file_fallback_
  extern f_status_t fake_print_error_file_fallback(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fake_print_error_file_fallback_

/**
 * Print error message for when an operation fails.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation
 *   The identifier of the operation that failed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_failure_operation_
  extern f_status_t fake_print_error_failure_operation(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation);
#endif // _di_fake_print_error_failure_operation_

/**
 * Print error message for when an operation fails.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param script
 *   The name of the script that failed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_failure_script_
  extern f_status_t fake_print_error_failure_script(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t script);
#endif // _di_fake_print_error_failure_script_

/**
 * Print error message for when the parameter value is an empty string.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
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
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_parameter_not_empty_
  extern f_status_t fake_print_error_parameter_not_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_not_empty_

/**
 * Print error message for when the parameter value contains a non-word, non-minus, and non-plus character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
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
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_parameter_not_word_
  extern f_status_t fake_print_error_parameter_not_word(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_not_word_

/**
 * Print error message for when two designated operations cannot be used together.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation_1
 *   The name of the first operation that cannot be used.
 * @param operation_2
 *   The name of the second operation that cannot be used.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_parameter_operation_not_with_
  extern f_status_t fake_print_error_parameter_operation_not_with(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t operation_1, const f_string_static_t operation_2);
#endif // _di_fake_print_error_parameter_operation_not_with_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_help_
  extern f_status_t fake_print_help(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_help_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_first_locked_
  extern f_status_t fake_print_line_first_locked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_first_locked_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_first_unlocked_
  extern f_status_t fake_print_line_first_unlocked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_first_unlocked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_last_locked_
  extern f_status_t fake_print_line_last_locked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_last_locked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_last_unlocked_
  extern f_status_t fake_print_line_last_unlocked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_last_unlocked_

/**
 * Print message for when all operates successfully complete.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_operation_all_complete_
  extern f_status_t fake_print_operation_all_complete(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_operation_all_complete_

/**
 * Print build operation file error messages.
 *
 * @param data
 *   The program data.
 * @param status
 *   The status to use.
 *   This is provided, ignoring data.setting->status, for thread-safety reasons.
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
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_error_build_operation_file_message();
 */
#ifndef _di_fake_print_error_operation_file_
  extern bool fake_print_error_build_operation_file(fake_data_t * const data, const f_status_t status, const f_string_t function, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const bool fallback) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_operation_file_

/**
 * Helper function for printing build operation file error messages.
 *
 * This prints the "copy source to destination" part of the message.
 *
 * @param data
 *   The program data.
 * @param operation
 *   The operation performed.
 * @param source
 *   The operation source.
 * @param destination
 *   The operation destination, if applicable.
 *   Set destination.used to 0 to disable.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 *
 * @see fl_print_format()
 *
 * @see fake_print_error_build_operation_file()
 */
#ifndef _di_fake_print_error_build_operation_file_message_
  extern void fake_print_error_build_operation_file_message(fake_data_t * const data, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_build_operation_file_message_

/**
 * Print FSS error messages.
 *
 * @param data
 *   The program data.
 * @param status
 *   The error status code to report on.
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
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_fss_
  extern bool fake_print_error_fss(fake_data_t * const data, const f_status_t status, const f_string_t function, const f_string_static_t path_file, const f_string_range_t range, const bool fallback) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_fss_

/**
 * Print an error message for when the parameter is missing its accompanying value.
 *
 * @param data
 *   The program data.
 * @param parameter
 *   The parameter name.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_parameter_missing_value_
  extern void fake_print_error_parameter_missing_value(fake_data_t * const data, const f_string_static_t parameter) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_parameter_missing_value_

/**
 * Print an error message for when the parameter is specified too many times.
 *
 * @param data
 *   The program data.
 * @param parameter
 *   The parameter name.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_error_parameter_too_many_
  extern void fake_print_error_parameter_too_many(fake_data_t * const data, const f_string_static_t parameter) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_parameter_too_many_

/**
 * Print an error message for when there are more arguments are required (such as to a fakefile operation).
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_error_requires_more_arguments_
  extern void fake_print_error_requires_more_arguments(fake_make_data_t * const data_make) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_requires_more_arguments_

/**
 * Print an error message for when there are too many arguments passed (such as to a fakefile operation).
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_error_too_many_arguments_
  extern void fake_print_error_too_many_arguments(fake_make_data_t * const data_make) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_too_many_arguments_

/**
 * Print an error message for when an argument is an empty string.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param index
 *   The index of the argument that is an empty string.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_error_argument_empty_
  extern void fake_print_error_argument_empty(fake_make_data_t * const data_make, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_argument_empty_

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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_section_operation_failed_
  extern void fake_print_message_section_operation_failed(fake_data_t * const data, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_failed_

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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_section_operation_link_argument_unknown_
  extern void fake_print_message_section_operation_link_argument_unknown(fake_data_t * const data, const fl_print_t print, const f_string_static_t argument) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_link_argument_unknown_

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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_section_operation_link_point_exists_
  extern void fake_print_message_section_operation_link_point_exists(fake_data_t * const data, const fl_print_t print, const f_string_static_t argument) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_link_point_exists_

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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_section_operation_link_target_exists_not_
  extern void fake_print_message_section_operation_link_target_exists_not(fake_data_t * const data, const fl_print_t print, const f_string_static_t argument) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_link_target_exists_not_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation has a path outside of the project root.
 *
 * @param data
 *   The program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 * @param path
 *   The path that is outside of the project path.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_message_section_operation_path_outside_
  extern void fake_print_message_section_operation_path_outside(fake_data_t * const data, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t path) F_attribute_visibility_internal_d;
#endif // _fake_print_message_section_operation_path_outside_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation.
 *
 * @param data
 *   The program data.
 * @param error
 *   Designates how the section error/warning should be printed.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param path
 *   The path to the directory.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_message_section_operation_path_stack_max_
  extern void fake_print_message_section_operation_path_stack_max(fake_data_t * const data, fl_print_t error, const f_status_t status, const f_string_t function, const f_string_static_t path) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_path_stack_max_

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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_section_operation_stack_max_
  extern void fake_print_message_section_operation_stack_max(fake_data_t * const data, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_stack_max_

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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_section_operation_unknown_
  extern void fake_print_message_section_operation_unknown(fake_data_t * const data, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_unknown_

/**
 * Print message when fake settings content is empty.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param range_object
 *   The range within the buffer representing the object.
 * @param settings_name
 *   The name of the setting that has an invalid value.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_warning_settings_content_empty_
  extern void fake_print_warning_settings_content_empty(fake_data_t * const data, const f_string_static_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_static_t settings_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_content_empty_

/**
 * Print warning message when fake settings content is invalid.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param range_object
 *   The range within the buffer representing the object.
 * @param range_content
 *   The range within the buffer representing the content.
 * @param settings_name
 *   The name of the setting that has an invalid value.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_warning_settings_content_invalid_
  extern void fake_print_warning_settings_content_invalid(fake_data_t * const data, const f_string_static_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_static_t settings_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_content_invalid_

/**
 * Print warning message when settings content has too many values.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param name_object
 *   The name of the object.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_warning_settings_content_multiple_
  extern void fake_print_warning_settings_content_multiple(fake_data_t * const data, const f_string_static_t path_file, const f_string_static_t name_object) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_content_multiple_

/**
 * Print warning message when fakefile has too many objects with the same name.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param label
 *   A label describing what this object belongs to.
 * @param name_object
 *   The name of the object.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_warning_settings_object_multiple_
  extern void fake_print_warning_settings_object_multiple(fake_data_t * const data, const f_string_static_t path_file, const f_string_static_t label, const f_string_static_t name_object) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_h

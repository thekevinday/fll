/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fake_print_h
#define _PRIVATE_fake_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error messages.
 *
 * @param data
 *   The program data.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_none is returned on successful print of known errors.
 *   F_unknown is returned if the status code has no print message.
 */
#ifndef _di_fake_print_error_
  extern f_return_status fake_print_error(const fake_data data, const f_status status, const f_string function, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_

/**
 * Print build operation file error messages.
 *
 * @param data
 *   The program data.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The name of the function where the error happened.
 * @param operation
 *   The operation performed.
 * @param source
 *   The operation source.
 *   Set to 0 to disable.
 * @param destination
 *   The operation destination, if applicable.
 *   Requires source to be non-zero.
 *   Set to 0 to disable.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 *   Requires source and destination to be non-zero.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fake_print_error_operation_file_
  extern bool fake_print_error_build_operation_file(const fake_data data, const f_status status, const f_string function, const f_string operation, const f_string source, const f_string destination, const f_string how, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_operation_file_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation.
 *
 * @param data
 *   The program data.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param string
 *   A string used by certain error conditions.
 *   Set to 0 disable.
 */
#ifndef _di_fake_print_error_fakefile_section_line_
  extern void fake_print_error_fakefile_section_line(const fake_data data, const f_status status, const f_string function, const f_string string) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fakefile_section_line_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation failed.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 */
#ifndef _di_fake_print_error_fakefile_section_operation_failed_
  extern void fake_print_error_fakefile_section_operation_failed(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fakefile_section_operation_failed_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation has a path outside of the project root.
 *
 * @param data
 *   The program data.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 * @param path
 *   The path that is outside of the project path.
 */
#ifndef _di_fake_print_error_fakefile_section_operation_path_outside_
  extern void fake_print_error_fakefile_section_operation_path_outside(const fake_data data, const f_status status, const f_string function, const f_string path) f_gcc_attribute_visibility_internal;
#endif // _fake_print_error_fakefile_section_operation_path_outside_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that the max stack depth is reached.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 * @param stack_max
 *   The max stack depth.
 */
#ifndef _di_fake_print_error_fakefile_section_operation_stack_max_
  extern void fake_print_error_fakefile_section_operation_stack_max(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const f_array_length stack_max) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fakefile_section_operation_stack_max_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation is invalid.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 */
#ifndef _di_fake_print_error_fakefile_section_operation_unknown_
  extern void fake_print_error_fakefile_section_operation_unknown(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fakefile_section_operation_unknown_

/**
 * Print error message when fake settings content is invalid.
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
 */
#ifndef _di_fake_print_error_fakefile_settings_content_invalid_
  extern void fake_print_error_fakefile_settings_content_invalid(const fake_data data, const f_string path_file, const f_string_dynamic buffer, const f_string_range range_object, const f_string_range range_content, const f_string settings_name) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fakefile_settings_content_invalid_

/**
 * Print file/directory error messages.
 *
 * @todo the fll_file_error_print() needs to be reviewed and possibly changed.
 *
 * @param data
 *   The program data.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The function call that returned the error.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param is_file
 *   Set to TRUE if this is a file and FALSE if this is a directory.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fake_print_error_file_
  extern bool fake_print_error_file(const fake_data data, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_file_

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
 */
#ifndef _di_fake_print_error_fss_
  extern bool fake_print_error_fss(const fake_data data, const f_status status, const f_string function, const f_string path_file, const f_string_range range, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fss_

/**
 * Print an error message for when the parameter is missing its accompanying value.
 *
 * @param data
 *   The program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_fake_print_error_parameter_missing_value_
  extern void fake_print_error_parameter_missing_value(const fake_data data, const f_string parameter) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_parameter_missing_value_

/**
 * Print an error message for when the parameter is specified too many times.
 *
 * @param data
 *   The program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_fake_print_error_parameter_too_many_
  extern void fake_print_error_parameter_too_many(const fake_data data, const f_string parameter) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_parameter_too_many_

/**
 * Print a specific error message for a named section operation.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   A buffer containing the contents of the fakefile file.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The name of the operation designated to have an error.
 * @param message
 *   The error message.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 */
#ifndef _di_fake_print_error_section_operation_
  extern void fake_print_error_section_operation(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_static operation_name, const f_string message, ...) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_section_operation_

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
 */
#ifndef _di_fake_print_warning_fakefile_object_multiple_
  extern void fake_print_warning_fakefile_object_multiple(const fake_data data, const f_string path_file, const f_string label, const f_string name_object) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_warning_fakefile_object_multiple_

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
 */
#ifndef _di_fake_print_warning_settings_content_multiple_
  extern void fake_print_warning_settings_content_multiple(const fake_data data, const f_string path_file, const f_string name_object) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_warning_settings_content_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_print_h

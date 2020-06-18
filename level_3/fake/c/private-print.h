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
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
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
  extern f_return_status fake_print_error(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_

/**
 * Print error message when fake settings content is invalid.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
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
  extern void fake_print_error_fakefile_settings_content_invalid(const fl_color_context context, const uint8_t verbosity, const f_string path_file, const f_string_dynamic buffer, const f_string_range range_object, const f_string_range range_content, const f_string settings_name) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fakefile_settings_content_invalid_

/**
 * Print file/directory error messages.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The function call that returned the error.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that failes, such as 'create' or 'access'.
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
  extern bool fake_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_file_

/**
 * Print FSS error messages.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
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
#ifndef _di_fake_print_error_fss
  extern bool fake_print_error_fss(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string path_file, const f_string_range range, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_fss

/**
 * Print operation error messages.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The name of the function where the error happened.
 * @param operation
 *   The operation performed.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 * @param source
 *   The operation source.
 * @param destination
 *   The operation destination, if applicable.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fake_print_error_operation_
  extern bool fake_print_error_operation(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string operation, const f_string how, const f_string source, const f_string destination, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_operation_

/**
 * Print an error message for when the parameter is missing its accompanying value.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_fake_print_error_parameter_missing_value_
  extern void fake_print_error_parameter_missing_value(const fl_color_context context, const uint8_t verbosity, const f_string parameter) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_parameter_missing_value_

/**
 * Print an error message for when the parameter is specified too many times.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_fake_print_error_parameter_too_many_
  extern void fake_print_error_parameter_too_many(const fl_color_context context, const uint8_t verbosity, const f_string parameter) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_parameter_too_many_

/**
 * Print warning message when fakefile has too many objects with the same name.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
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
  extern void fake_print_warning_fakefile_object_multiple(const fl_color_context context, const uint8_t verbosity, const f_string path_file, const f_string label, const f_string name_object) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_warning_fakefile_object_multiple_

/**
 * Print warning message when settings content has too many values.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param name_object
 *   The name of the object.
 */
#ifndef _di_fake_print_warning_settings_content_multiple_
  extern void fake_print_warning_settings_content_multiple(const fl_color_context context, const uint8_t verbosity, const f_string path_file, const f_string name_object) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_warning_settings_content_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_print_h

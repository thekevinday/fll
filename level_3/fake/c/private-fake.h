/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fake_h
#define _PRIVATE_fake_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generate all appropriate paths based on runtime information.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_
  extern f_return_status fake_path_generate(fake_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_path_generate_

/**
 * Generate all appropriate paths based on runtime information from dynamic strings.
 *
 * @param data
 *   The program data.
 * @param source
 *   The string to copy from.
 * @param destination
 *   An array of pointers to the strings to append onto.
 * @param length
 *   The size of the values.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_string_dynamic_
  extern f_return_status fake_path_generate_string_dynamic(fake_data *data, const f_string_dynamic source, f_string_dynamic *destination[], const uint8_t size) f_gcc_attribute_visibility_internal;
#endif // _di_fake_path_generate_string_dynamic_

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
 *   F_none is returned on successful print of known errors.
 *   F_unknown is returned if the status code has no print message.
 */
#ifndef _di_fake_print_error_file_
  extern f_return_status fake_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_fake_print_error_file_

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
 * Validate console arguments and print any relating error messages.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_process_console_parameters_
  extern f_return_status fake_process_console_parameters(const f_console_arguments arguments, fake_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_validate_console_parameters_

/**
 * Validate directories and print any relating error messages.
 *
 * This should not be called for skeleton as in that case the directories probably do not exist.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_validate_parameter_directories_
  extern f_return_status fake_validate_parameter_directories(const f_console_arguments arguments, const fake_data data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_validate_parameter_directories_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_h

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
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_
  extern f_return_status fake_path_generate(fake_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_path_generate_

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
 *   Set to f_true to print the fallback error message for unknown errors.
 *
 * @return
 *   f_none is returned on successful print of known errors.
 *   f_unknown is returned if the status code has no print message.
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
 * @param file_name
 *   The name of the file or directory.
 * @param file_or_directory
 *   A string that should be either 'file' or 'directory' used when printing the message.
 * @param fallback
 *   Set to f_true to print the fallback error message for unknown errors.
 *
 * @return
 *   f_none is returned on successful print of known errors.
 *   f_unknown is returned if the status code has no print message.
 */
#ifndef _di_fake_print_error_file_
  extern f_return_status fake_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string file_name, const f_string file_or_directory, const bool fallback) f_gcc_attribute_visibility_internal;
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
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_process_console_parameters_
  extern f_return_status fake_process_console_parameters(const f_console_arguments arguments, fake_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_validate_console_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_h

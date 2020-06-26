/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_iki_read_h
#define _PRIVATE_iki_read_h

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
#ifndef _di_iki_read_print_error_
  extern f_return_status iki_read_print_error(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_print_error_

/**
 * Print file/directory error messages.
 *
 * @todo the fll_file_error_print() needs to be reviewed and possibly changed.
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
#ifndef _di_iki_read_print_error_file_
  extern bool iki_read_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_print_error_file_

/**
 * Print number argument errors.
 *
 * @param context
 *   The color context.
 * @param verbosity
 *   The verbosity level, which determines if and what should be printed.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The function call that returned the error.
 * @param parameter
 *   The parameter name.
 * @param argument
 *   The argument value.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_iki_read_print_error_number_argument_
  extern void iki_read_print_error_number_argument(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string parameter, const f_string argument) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_print_error_number_argument_

/**
 * Determine the range based on the --at parameter.
 *
 * If the --at parameter is not specified in the console arguments, then range is untouched.
 * The range.start will be greater than data->buffer.used if the --at range is not found before buffer end is reached.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param data
 *   The program specific data.
 * @param range
 *   The range value to represent the --at values.
 *
 * @return
 *   F_true is returned if the range is processed.
 *   F_false is returned if the range is not processed.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_at_
  extern f_return_status iki_read_process_at(const f_console_arguments arguments, const f_string file_name, iki_read_data *data, f_string_range *range) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_at_

/**
 * Process a given buffer.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param data
 *   The program specific data.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing done.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_
  extern f_return_status iki_read_process_buffer(const f_console_arguments arguments, const f_string file_name, iki_read_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_buffer_

/**
 * Process a given buffer, printing the given range.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param data
 *   The program specific data.
 * @param variable
 *   The ranges representing a variable.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param content
 *   The ranges representing content.
 * @param ranges
 *   The ranges to print when matched.
 *   Should be one of: variable, vocabulary, or content.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_
  extern f_return_status iki_read_process_buffer_ranges(const f_console_arguments arguments, const f_string file_name, iki_read_data *data, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content, f_string_ranges *ranges) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_buffer_ranges_

/**
 * Process a given buffer, printing the total.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param data
 *   The program specific data.
 * @param variable
 *   The ranges representing a variable.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param content
 *   The ranges representing content.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_total_
  extern f_return_status iki_read_process_buffer_total(const f_console_arguments arguments, const f_string file_name, iki_read_data *data, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_buffer_total_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_iki_read_h

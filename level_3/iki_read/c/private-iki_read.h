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
  extern f_return_status iki_read_print_error(const fl_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const bool fallback) f_gcc_attribute_visibility_internal;
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
  extern bool iki_read_print_error_file(const fl_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const f_string_t name, const f_string_t operation, const bool is_file, const bool fallback) f_gcc_attribute_visibility_internal;
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
  extern void iki_read_print_error_number_argument(const fl_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const f_string_t parameter, const f_string_t argument) f_gcc_attribute_visibility_internal;
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
 *   F_data_not if the range is processed, but the requested line is out of range.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_at_
  extern f_return_status iki_read_process_at(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_string_range_t *range) f_gcc_attribute_visibility_internal;
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
  extern f_return_status iki_read_process_buffer(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data) f_gcc_attribute_visibility_internal;
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
 * @param buffer_range
 *   The range within the buffer to process.
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
  extern f_return_status iki_read_process_buffer_ranges(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_string_range_t *buffer_range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_string_ranges_t *ranges) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_buffer_ranges_

/**
 * Process a given buffer, printing the given buffer in whole mode based on the given ranges.
 *
 * The entire variable is replaced with the range from the associated ranges.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param buffer_range
 *   The range within the buffer to process.
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
#ifndef _di_iki_read_process_buffer_ranges_whole_
  extern f_return_status iki_read_process_buffer_ranges_whole(const f_console_arguments_t arguments, const f_string_t file_name, const f_string_range_t buffer_range, iki_read_data_t *data, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_string_ranges_t *ranges) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_buffer_ranges_whole_

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
  extern f_return_status iki_read_process_buffer_total(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_process_buffer_total_

/**
 * Process the arguments, associating substitions with a given vocabulary.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param data
 *   The program specific data.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param substitutionss
 *   An array of substitutionss with each index representing an index for in the respective vocabulary array.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_substitutions_identify_
  extern f_return_status iki_read_substitutions_identify(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_substitutions_identify_

/**
 * Print any applicable substition and if there is non then print the given range at the given index.
 *
 * @param data
 *   The program specific data.
 * @param variable
 *   The ranges representing a variable.
 * @param content
 *   The ranges representing a content.
 * @param ranges
 *   The ranges containing the desired range to print as specified by index.
 * @param substitutions
 *   The substitions associated with the variable for the given range at the given index to use for potential printing.
 * @param index
 *   The index used to identify the desired range in variable, content, and ranges.
 * @param content_only
 *   Set to TRUE to only print the content when printing substituted text.
 *   Set to FALSE to print the entire variable when printing substituted text.
 */
#ifndef _di_iki_read_substitutions_print_
  extern void iki_read_substitutions_print(const iki_read_data_t data, const f_iki_variable_t variable, const f_iki_content_t content, const f_string_ranges_t ranges, const iki_read_substitutions_t substitutions, const f_string_length_t index, const bool content_only) f_gcc_attribute_visibility_internal;
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_iki_read_h

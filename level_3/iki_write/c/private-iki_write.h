/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_iki_write_h
#define _PRIVATE_iki_write_h

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
#ifndef _di_iki_write_print_error_
  extern f_return_status iki_write_print_error(const fl_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_iki_write_print_error_

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
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   Set to 0 for "file", 1 for "directory", and 2 for "pipe".
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_iki_write_print_error_file_
  extern bool iki_write_print_error_file(const fl_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const f_string_t name, const f_string_t operation, const uint8_t type, const bool fallback) f_gcc_attribute_visibility_internal;
#endif // _di_iki_write_print_error_file_

/**
 * Process a given object and content, printing the IKI if valid or an error if invalid.
 *
 * @param data
 *   The program data.
 * @param object
 *   The object to validate and print.
 * @param content
 *   The content to escape and print.
 * @param quote
 *   The quote character to use.
 *   This is either f_iki_syntax_quote_single or f_iki_syntax_quote_double.
 * @param output
 *   The output file descriptor to print processed iki text to.
 * @param escaped
 *   A string buffer used as a string cache to save the string into while escaping.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_iki_write_process_
  extern f_return_status iki_write_process(const iki_write_data_t data, const f_string_static_t object, const f_string_static_t content, const uint8_t quote, const int output, f_string_dynamic_t *escaped) f_gcc_attribute_visibility_internal;
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_iki_write_h

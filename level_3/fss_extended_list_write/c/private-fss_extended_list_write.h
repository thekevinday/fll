/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_extended_list_write_h
#define _PRIVATE_fss_extended_list_write_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an message about the object and content parameters not being specified the same number of times.
 *
 * @param main
 *   The main data.
 */
#ifndef _di_fss_extended_list_write_error_parameter_same_times_print_
  void fss_extended_list_write_error_parameter_same_times_print(const fss_extended_list_write_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_write_error_parameter_same_times_print_

/**
 * Print an message about a parameter EOL being unsupported.
 *
 * @param main
 *   The main data.
 */
#ifndef _di_fss_extended_list_write_error_parameter_unsupported_eol_print_
  void fss_extended_list_write_error_parameter_unsupported_eol_print(const fss_extended_list_write_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_write_error_parameter_unsupported_eol_print_

/**
 * Print an message about a parameter missing a value.
 *
 * @param main
 *   The main data.
 * @param symbol
 *   The console symbol, such as "--" in "--help".
 * @param parameter
 *   The parameter name, such as "help" in "--help".
 */
#ifndef _di_fss_extended_list_write_error_parameter_value_missing_print_
  void fss_extended_list_write_error_parameter_value_missing_print(const fss_extended_list_write_main_t main, const f_string_t symbol, const f_string_t parameter) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_write_error_parameter_value_missing_print_

/**
 * Process a given object and content, printing the FSS if valid or an error if invalid.
 *
 * @param main
 *   The main data.
 * @param output
 *   The file to output to.
 * @param quote
 *   The quote character to use.
 *   This is either single our double quote.
 * @param object
 *   The object to validate and print.
 *   Set pointer address to 0 to not use.
 * @param content
 *   The content to escape and print.
 *   Set pointer address to 0 to not use.
 * @param ignore
 *   An array of ranges within the Content to ignore.
 *   Set pointer address to 0 to not use.
 * @param buffer
 *   The buffer array used as a cache to construct the output before printing.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_fss_extended_list_write_process_
  extern f_status_t fss_extended_list_write_process(const fss_extended_list_write_main_t main, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_static_t *content, const f_string_ranges_t *ignore, f_string_dynamic_t *buffer) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_write_process_

/**
 * Process the pipe, reading from the pipe and writing to the output.
 *
 * @param main
 *   The main data.
 * @param output
 *   The file to output to.
 * @param quote
 *   The quote character to use.
 *   This is either single our double quote.
 * @param buffer
 *   The buffer array used as a cache to construct the output before printing.
 * @param ignore
 *   An array of ranges within the Content to ignore.
 *   Set pointer address to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_fss_extended_list_write_process_pipe_
  extern f_status_t fss_extended_list_write_process_pipe(const fss_extended_list_write_main_t main, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer, f_string_ranges_t *ignore) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_write_process_pipe_

/**
 * Process the ignore parameter associated with a specific content parameter.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main data.
 * @param contents
 *   The console parameter locations array for the content parameter.
 * @param location
 *   The specific location within the contents locations array.
 * @param ignore
 *   An array of ranges within the Content to ignore.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_fss_extended_list_write_process_parameter_ignore_
  extern f_status_t fss_extended_list_write_process_parameter_ignore(const f_console_arguments_t arguments, const fss_extended_list_write_main_t main, const f_array_lengths_t contents, const f_array_length_t location, f_string_ranges_t *ignore) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_write_process_parameter_ignore_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_extended_list_write_h

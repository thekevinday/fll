/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_basic_list_write_h
#define _PRIVATE_fss_basic_list_write_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an message about the object and content parameters not being specified the same number of times.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_fss_basic_list_write_error_parameter_same_times_print_
  void fss_basic_list_write_error_parameter_same_times_print(const fss_basic_list_write_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_write_error_parameter_same_times_print_

/**
 * Print an message about a parameter EOL being unsupported.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_fss_basic_list_write_error_parameter_unsupported_eol_print_
  void fss_basic_list_write_error_parameter_unsupported_eol_print(const fss_basic_list_write_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_write_error_parameter_unsupported_eol_print_

/**
 * Print an message about a parameter missing a value.
 *
 * @param data
 *   The program data.
 * @param symbol
 *   The console symbol, such as "--" in "--help".
 * @param parameter
 *   The parameter name, such as "help" in "--help".
 */
#ifndef _di_fss_basic_list_write_error_parameter_value_missing_print_
  void fss_basic_list_write_error_parameter_value_missing_print(const fss_basic_list_write_data_t data, const f_string_t symbol, const f_string_t parameter) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_write_error_parameter_value_missing_print_

/**
 * Process a given object and content, printing the FSS if valid or an error if invalid.
 *
 * @param data
 *   The program data.
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
 * @param buffer
 *   The buffer array used as a cache to construct the output before printing.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_fss_basic_list_write_process_
  extern f_status_t fss_basic_list_write_process(const fss_basic_list_write_data_t data, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_static_t *content, f_string_dynamic_t *buffer) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_write_process_

/**
 * Process the pipe, reading from the pipe and writing to the output.
 *
 * @param data
 *   The program data.
 * @param output
 *   The file to output to.
 * @param quote
 *   The quote character to use.
 *   This is either single our double quote.
 * @param buffer
 *   The buffer array used as a cache to construct the output before printing.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_fss_basic_list_write_process_pipe_
  extern f_status_t fss_basic_list_write_process_pipe(const fss_basic_list_write_data_t data, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_basic_list_write_h

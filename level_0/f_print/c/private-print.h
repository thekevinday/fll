/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_print_h
#define _PRIVATE_F_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_print().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 *
 * @return
 *   F_none on success.
 *   F_data_not if length is 0.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_print()
 * @see f_print_dynamic()
 * @see f_print_dynamic_partial()
 */
#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  extern f_return_status private_f_print(FILE *output, const f_string_t string, const f_string_length_t length) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

/**
 * Private implementation of f_print_to().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 *
 * @return
 *   F_none on success.
 *   F_data_not if length is 0.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_print_to()
 * @see f_print_to_dynamic()
 * @see f_print_to_dynamic_partial()
 */
#if !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)
  extern f_return_status private_f_print_to(const int id, const f_string_t string, const f_string_length_t length) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_print_h
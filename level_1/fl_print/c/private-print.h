/**
 * FLL - Level 1
 *
 * Project: Print
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_print_h
#define _PRIVATE_FL_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Helper function for converting one substitution in a string.
 *
 * This should be called after each first '%' is encountered.
 * This should return only after a single '%' group is fully processed, end of current is reached, or an error occurs.
 *
 * @param string
 *   The current character position within the string.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable arguments list.
 * @param status
 *   The status is stored here rather then via the return.
 *
 * @return
 *   This returns a string at either the start position (if nothing done or an error occurred) or at the character last processed.
 *   The caller is expected to increment past this if they wish to continue processing the string.
 *
 *   The status parameter will be set as follows:
 *
 *     F_none on success.
 *
 *     F_eos (with error bit) on failure because end of string found and cannot process further.
 *     F_output (with error bit) on failure to print to the output file.
 *     F_parameter (with error bit) if a parameter is invalid.
 *     F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *     F_valid_not (with error bit) on invalid syntax.
 *
 *     Success from: f_print_dynamic().
 *     Success from: f_print_dynamic_raw().
 *     Success from: f_print_dynamic_safely().
 *     Success from: f_print_safely().
 *     Success from: f_print_terminated().
 *
 *     Errors (with error bit) from: f_conversion_number_signed_print().
 *     Errors (with error bit) from: f_conversion_number_unsigned_print().
 *     Errors (with error bit) from: f_print_dynamic().
 *     Errors (with error bit) from: f_print_dynamic_raw().
 *     Errors (with error bit) from: f_print_dynamic_safely().
 *     Errors (with error bit) from: f_print_safely().
 *     Errors (with error bit) from: f_print_terminated().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 *
 * @see private_fl_print_convert_number()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_)
  extern f_string_t private_fl_print_format_convert(f_string_t string, FILE * const stream, va_list ap, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_)

/**
 * Private implementation of fl_print_trim_except().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_valid().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_except()
 * @see fl_print_trim_except_dynamic()
 * @see fl_print_trim_except_dynamic_partial()
 * @see fl_print_trim_except_in()
 * @see fl_print_trim_except_in_dynamic()
 * @see fl_print_trim_except_in_dynamic_partial()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)
  extern f_status_t private_fl_print_trim_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)

/**
 * Private implementation of fl_print_trim_except_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_except_raw()
 * @see fl_print_trim_except_dynamic_raw()
 * @see fl_print_trim_except_dynamic_partial_raw()
 * @see fl_print_trim_except_in_raw()
 * @see fl_print_trim_except_in_dynamic_raw()
 * @see fl_print_trim_except_in_dynamic_partial_raw()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)
  extern f_status_t private_fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)

/**
 * Private implementation of fl_print_trim_except_raw_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_valid().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_except_raw_safely()
 * @see fl_print_trim_except_dynamic_raw_safely()
 * @see fl_print_trim_except_dynamic_partial_raw_safely()
 * @see fl_print_trim_except_in_raw_safely()
 * @see fl_print_trim_except_in_dynamic_raw_safely()
 * @see fl_print_trim_except_in_dynamic_partial_raw_safely()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_safely_) || !defined(_di_fl_print_trim_except_in_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_safely_)
  extern f_status_t private_fl_print_trim_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_safely_) || !defined(_di_fl_print_trim_except_in_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_safely_)

/**
 * Private implementation of fl_print_trim_except_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_valid().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_except_dynamic_safely()
 * @see fl_print_trim_except_dynamic_partial_safely()
 * @see fl_print_trim_except_in_dynamic_safely()
 * @see fl_print_trim_except_in_dynamic_partial_safely()
 * @see fl_print_trim_except_in_safely()
 * @see fl_print_trim_except_safely()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_safely_)
  extern f_status_t private_fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_safely_)

/**
 * Private implementation of fl_print_trim().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_valid().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim()
 * @see fl_print_trim_dynamic()
 * @see fl_print_trim_dynamic_partial()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  extern f_status_t private_fl_print_trim(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

/**
 * Private implementation of fl_print_trim_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_raw()
 * @see fl_print_trim_dynamic_raw()
 * @see fl_print_trim_dynamic_partial_raw()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)
  extern f_status_t private_fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)

/**
 * Private implementation of fl_print_trim_raw_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_valid().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_raw_safely()
 * @see fl_print_trim_dynamic_raw_safely()
 * @see fl_print_trim_dynamic_partial_raw_safely()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_raw_safely_) || !defined(_di_fl_print_trim_dynamic_raw_safely_) || !defined(_di_fl_print_trim_dynamic_partial_raw_safely_)
  extern f_status_t private_fl_print_trim_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_raw_safely_) || !defined(_di_fl_print_trim_dynamic_raw_safely_) || !defined(_di_fl_print_trim_dynamic_partial_raw_safely_)

/**
 * Private implementation of fl_print_trim_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_valid().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 * @see fwrite_unlocked()
 *
 * @see fl_print_format()
 * @see fl_print_format_convert()
 * @see fl_print_trim_safely()
 * @see fl_print_trim_dynamic_safely()
 * @see fl_print_trim_dynamic_partial_safely()
 */
#if !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)
  extern f_status_t private_fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_print_format_) || !defined(_di_fl_print_format_convert_) || !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_print_h

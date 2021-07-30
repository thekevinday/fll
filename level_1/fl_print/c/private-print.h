/**
 * FLL - Level 1
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * @param current
 *   The current character position within the string.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable arguments list.
 *
 * @return
 *   F_none on success.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *   F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *   Success from: f_print_dynamic().
 *   Success from: f_print_dynamic_raw().
 *   Success from: f_print_dynamic_safely().
 *   Success from: f_print_safely().
 *   Success from: f_print_terminated().
 *
 *   Errors (with error bit) from: f_conversion_number_signed_to_file().
 *   Errors (with error bit) from: f_conversion_number_unsigned_to_file().
 *   Errors (with error bit) from: f_print_dynamic().
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *   Errors (with error bit) from: f_print_safely().
 *   Errors (with error bit) from: f_print_terminated().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see f_conversion_number_signed_to_file()
 * @see f_conversion_number_unsigned_to_file()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 *
 * @see private_fl_print_convert_number()
 */
#if !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)
  extern f_status_t private_fl_print_string_convert(f_string_t *current, FILE *output, va_list *ap) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)

/**
 * Helper function for processing the number in a convert string.
 *
 * This should be called to convert numbers after a '%', such as the field with or precision.
 *
 * On return the current will point to either the last consecutive character representing a number, the asterisk, or NULL.
 *
 * @param current
 *   The current character position within the string.
 * @param ap
 *   The variable arguments list.
 * @param number
 *   The converted number.
 *
 * @return
 *   F_true on success and end of string (NULL) is found.
 *   F_false on success without reaching the end of string (NULL).
 *
 * @see va_arg()
 */
#if !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)
  extern f_status_t private_fl_print_convert_number(f_string_t *current, va_list *ap, unsigned int *number) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_string_convert_) || !defined(_di_fl_print_string_)

/**
 * Private implementation of fl_print_trim_except().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
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
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see fl_print_trim_except()
 * @see fl_print_trim_except_dynamic()
 * @see fl_print_trim_except_dynamic_partial()
 * @see fl_print_trim_except_in()
 * @see fl_print_trim_except_in_dynamic()
 * @see fl_print_trim_except_in_dynamic_partial()
 */
#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)
  extern f_status_t private_fl_print_trim_except_in(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_) || !defined(_di_fl_print_trim_except_in_) || !defined(_di_fl_print_trim_except_in_dynamic_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_)

/**
 * Private implementation of fl_print_trim_except_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
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
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see fl_print_trim_except_raw()
 * @see fl_print_trim_except_dynamic_raw()
 * @see fl_print_trim_except_dynamic_partial_raw()
 * @see fl_print_trim_except_in_raw()
 * @see fl_print_trim_except_in_dynamic_raw()
 * @see fl_print_trim_except_in_dynamic_partial_raw()
 */
#if !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)
  extern f_status_t private_fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_except_raw_) || !defined(_di_fl_print_trim_except_dynamic_raw_) || !defined(_di_fl_print_trim_except_dynamic_partial_raw_) || !defined(_di_fl_print_trim_except_in_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_raw_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_raw_)

/**
 * Private implementation of fl_print_trim_except_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
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
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see fl_print_trim_except_safely()
 * @see fl_print_trim_except_dynamic_safely()
 * @see fl_print_trim_except_dynamic_partial_safely()
 * @see fl_print_trim_except_in_safely()
 * @see fl_print_trim_except_in_dynamic_safely()
 * @see fl_print_trim_except_in_dynamic_partial_safely()
 */
#if !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)
  extern f_status_t private_fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_except_safely_) || !defined(_di_fl_print_trim_except_dynamic_safely_) || !defined(_di_fl_print_trim_except_dynamic_partial_safely_) || !defined(_di_fl_print_trim_except_in_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_safely_) || !defined(_di_fl_print_trim_except_in_dynamic_partial_safely_)

/**
 * Private implementation of fl_print_trim().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
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
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see fl_print_trim()
 * @see fl_print_trim_dynamic()
 * @see fl_print_trim_dynamic_partial()
 */
#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  extern f_status_t private_fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

/**
 * Private implementation of fl_print_trim_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
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
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see fl_print_trim_raw()
 * @see fl_print_trim_dynamic_raw()
 * @see fl_print_trim_dynamic_partial_raw()
 */
#if !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)
  extern f_status_t private_fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_raw_) || !defined(_di_fl_print_trim_dynamic_raw_) || !defined(_di_fl_print_trim_dynamic_partial_raw_)

/**
 * Private implementation of fl_print_trim_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
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
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 *
 * @see fl_print_trim_safely()
 * @see fl_print_trim_dynamic_safely()
 * @see fl_print_trim_dynamic_partial_safely()
 */
#if !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)
  extern f_status_t private_fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_safely_) || !defined(_di_fl_print_trim_dynamic_safely_) || !defined(_di_fl_print_trim_dynamic_partial_safely_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_print_h

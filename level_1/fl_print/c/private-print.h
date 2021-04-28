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
 * Private implementation of fl_print_trim_except().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fl_print_trim_except()
 * @see fl_print_trim_except_dynamic()
 * @see fl_print_trim_except_dynamic_partial()
 */
#if !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_)
  extern f_status_t private_fl_print_trim_except(FILE *output, const f_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_except_) || !defined(_di_fl_print_trim_except_dynamic_) || !defined(_di_fl_print_trim_except_dynamic_partial_)

/**
 * Private implementation of fl_print_trim_except_utf().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see fl_print_trim_except_utf()
 * @see fl_print_trim_except_utf_dynamic()
 * @see fl_print_trim_except_utf_dynamic_partial()
 */
#if !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)
  extern f_status_t private_fl_print_trim_except_utf(FILE *output, const f_utf_string_t string, const f_array_length_t start, const f_array_length_t stop, const f_array_lengths_t except) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_except_utf_) || !defined(_di_fl_print_trim_except_utf_dynamic_) || !defined(_di_fl_print_trim_except_utf_dynamic_partial_)

/**
 * Private implementation of fl_print_trim().
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fl_print_trim()
 * @see fl_print_trim_dynamic()
 * @see fl_print_trim_dynamic_partial()
 */
#if !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)
  extern f_status_t private_fl_print_trim(FILE *output, const f_string_t string, const f_array_length_t length) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_) || !defined(_di_fl_print_trim_dynamic_) || !defined(_di_fl_print_trim_dynamic_partial_)

/**
 * Private implementation of fl_print_trim_utf().
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see fl_print_trim_utf()
 * @see fl_print_trim_utf_dynamic()
 * @see fl_print_trim_utf_dynamic_partial()
 */
#if !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)
  extern f_status_t private_fl_print_trim_utf(FILE *output, const f_utf_string_t string, const f_array_length_t length) f_attribute_visibility_internal;
#endif // !defined(_di_fl_print_trim_utf_) || !defined(_di_fl_print_trim_utf_dynamic_) || !defined(_di_fl_print_trim_utf_dynamic_partial_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_print_h

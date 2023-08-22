/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_conversion_h
#define _PRIVATE_F_conversion_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Helper function for performing the entire process of printing to the output file.
 *
 * @param number
 *   The number to convert.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative_or_zero
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param file
 *   The file structure containing a valid stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_okay on success.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see ferror_unlocked()
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 *
 * @see private_f_conversion_digit_to_file_number()
 * @see private_f_conversion_digit_to_file_pad()
 * @see private_f_conversion_digit_to_file_prefix()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative_or_zero, const f_file_t file) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for printing the number to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param number
 *   The number to convert.
 *   This number is unsigned to allow for unsigned integers to be used.
 *   To represent a negative number, assign the flag f_conversion_data_flag_is_negative to data.flags.
 * @param digits
 *   The number of digits the number is represented by (based on the base unit).
 * @param file
 *   The file structure containing a valid stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_okay on success.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see ferror_unlocked()
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, const f_file_t file) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for printing the padding to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param pad
 *   The character to print as the padding character.
 *   Should be either f_string_ascii_space_s or f_string_ascii_0_s.
 * @param total
 *   The total number of times to print the pad.
 * @param file
 *   The file structure containing a valid stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_okay on success.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see ferror_unlocked()
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file_pad(const f_conversion_data_t data, const f_string_static_t pad, int total, const f_file_t file) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for printing the prefix to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative_or_zero
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param file
 *   The file structure containing a valid stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_okay on success.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see ferror_unlocked()
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file_prefix(const f_conversion_data_t data, const uint8_t negative_or_zero, const f_file_t file) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for performing the entire process of printing to the output file.
 *
 * @param number
 *   The number to convert.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative_or_zero
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param file
 *   The file structure containing a valid stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 *
 * @see private_f_conversion_digit_to_string_number()
 * @see private_f_conversion_digit_to_string_pad()
 * @see private_f_conversion_digit_to_string_prefix()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern f_status_t private_f_conversion_digit_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative_or_zero, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

/**
 * Helper function for printing the number to the file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param number
 *   The number to convert.
 *   This number is unsigned to allow for unsigned integers to be used.
 *   To represent a negative number, assign the flag f_conversion_data_flag_is_negative to data.flags.
 * @param digits
 *   The number of digits the number is represented by (based on the base unit).
 * @param file
 *   The file structure containing a valid stream to output to, including standard streams such as stdout and stderr.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern void private_f_conversion_digit_to_string_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

/**
 * Helper function for printing the padding to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param pad
 *   The character to print as the padding character.
 *   Should be either f_string_ascii_space_s or f_string_ascii_0_s.
 * @param total
 *   The total number of times to print the pad.
 * @param destination
 *   A string buffer to write to.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern void private_f_conversion_digit_to_string_pad(const f_conversion_data_t data, const f_char_t pad, int total, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

/**
 * Helper function for printing the prefix to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative_or_zero
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param destination
 *   A string buffer to write to.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern void private_f_conversion_digit_to_string_prefix(const f_conversion_data_t data, const uint8_t negative_or_zero, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_conversion_h

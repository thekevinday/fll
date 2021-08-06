/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to convert one data type to another, such as a string to an integer.
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
 * @param negative
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   F_block (with error bit) if file stream is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_output (with error bit) on any other file output error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
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
  extern f_status_t private_f_conversion_digit_to_file(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative, FILE *output) f_attribute_visibility_internal;
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
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   F_block (with error bit) if file stream is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_output (with error bit) on any other file output error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for printing the padding to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param pad
 *   The character to print as the padding character.
 *   Should be either f_string_ascii_space_s[0] or f_string_ascii_0_s[0].
 * @param total
 *   The total number of times to print the pad.
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   F_block (with error bit) if file stream is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_output (with error bit) on any other file output error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file_pad(const f_conversion_data_t data, const char pad, int total, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for printing the prefix to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   F_block (with error bit) if file stream is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_output (with error bit) on any other file output error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 */
#if !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)
  extern f_status_t private_f_conversion_digit_to_file_prefix(const f_conversion_data_t data, const uint8_t negative, FILE *output) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_print_) || !defined(_di_f_conversion_number_unsigned_print_)

/**
 * Helper function for performing the entire process of printing to the output file.
 *
 * @param number
 *   The number to convert.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize()
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 *
 * @see private_f_conversion_digit_to_string_number()
 * @see private_f_conversion_digit_to_string_pad()
 * @see private_f_conversion_digit_to_string_prefix()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern f_status_t private_f_conversion_digit_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, const uint8_t negative, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

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
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern void private_f_conversion_digit_to_string_number(const f_conversion_data_t data, f_number_unsigned_t number, int digits, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

/**
 * Helper function for printing the padding to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param pad
 *   The character to print as the padding character.
 *   Should be either f_string_ascii_space_s[0] or f_string_ascii_0_s[0].
 * @param total
 *   The total number of times to print the pad.
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern void private_f_conversion_digit_to_string_pad(const f_conversion_data_t data, const char pad, int total, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

/**
 * Helper function for printing the prefix to the output file.
 *
 * @param data
 *   The settings designating how to perform the conversion.
 * @param negative
 *   Designate that this number is to be represented as a negative number (or is zero).
 *
 *   Set this to 0 to represent a positive number.
 *   Set this to 1 to represent a negative number.
 *   Set this to 2 to represent the number 0;
 * @param output
 *
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @see f_conversion_number_signed_to_string()
 * @see f_conversion_number_unsigned_to_string()
 */
#if !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)
  extern void private_f_conversion_digit_to_string_prefix(const f_conversion_data_t data, const uint8_t negative, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_f_conversion_number_signed_to_string_) || !defined(_di_f_conversion_number_unsigned_to_string_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_conversion_h

/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
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
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print()
 * @see f_print_dynamic()
 * @see f_print_dynamic_partial()
 */
#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  extern f_status_t private_f_print(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

/**
 * Private implementation of f_print_character_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to verify as safe or not.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_character_safely()
 * @see f_print_safely()
 * @see f_print_safely_dynamic()
 * @see f_print_safely_dynamic_partial()
 * @see f_print_safely_terminated()
 * @see f_print_except_safely()
 * @see f_print_except_dynamic_safely()
 * @see f_print_except_dynamic_partial_safely()
 * @see f_print_except_in_safely()
 * @see f_print_except_in_dynamic_safely()
 * @see f_print_except_in_dynamic_partial_safely()
 */
#if !defined(_di_f_print_character_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)
  extern f_status_t private_f_print_character_safely(const f_char_t character, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_character_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)

/**
 * Private implementation of f_print_character_safely_get().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to verify as safe or not.
 *
 * @return
 *   NULL is returned if the character is already safe or if the character has a UTF-8 width of 2 or greater.
 *   A non-NULL string is returned if the character needs safe replacement.
 *   The non-NULL strings returned are NULL terminated.
 *   The non-NULL strings returned are the 3-byte characters used as placeholder symbols.
 *
 * @see f_print_character_safely_get()
 * @see f_print_dynamic_partial_safely()
 * @see f_print_dynamic_safely()
 * @see f_print_except_dynamic_partial_safely()
 * @see f_print_except_dynamic_safely()
 * @see f_print_except_in_dynamic_safely()
 * @see f_print_except_in_dynamic_partial_safely()
 * @see f_print_except_in_safely_
 * @see f_print_except_safely()
 * @see f_print_safely()
 * @see f_print_safely_terminated()
 * @see f_print_to_dynamic_partial_safely()
 * @see f_print_to_dynamic_safely()
 * @see f_print_to_except_dynamic_partial_safely()
 * @see f_print_to_except_dynamic_safely()
 * @see f_print_to_except_in_dynamic_safely()
 * @see f_print_to_except_in_dynamic_partial_safely()
 * @see f_print_to_except_in_safely_
 * @see f_print_to_except_safely()
 * @see f_print_to_safely()
 */
#if !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)
  extern const f_string_static_t private_f_print_character_safely_get(const f_char_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)

/**
 * Private implementation of f_print_except().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except()
 * @see f_print_except_dynamic()
 * @see f_print_except_dynamic_partial()
 */
#if !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)
  extern f_status_t private_f_print_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)

/**
 * Private implementation of f_print_except_in().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_in()
 * @see f_print_except_in_dynamic()
 * @see f_print_except_in_dynamic_partial()
 */
#if !defined(_di_f_print_except_in_) || !defined(_di_f_print_except_dynamic_in_) || !defined(_di_f_print_except_in_dynamic_partial_)
  extern f_status_t private_f_print_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_in_) || !defined(_di_f_print_except_dynamic_in_) || !defined(_di_f_print_except_in_dynamic_partial_)

/**
 * Private implementation of f_print_except_in_raw().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_in_raw()
 * @see f_print_except_in_dynamic_raw()
 * @see f_print_except_in_dynamic_partial_raw()
 */
#if !defined(_di_f_print_except_in_raw_) || !defined(_di_f_print_except_dynamic_in_raw_) || !defined(_di_f_print_except_in_dynamic_partial_raw_)
  extern f_status_t private_f_print_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_in_raw_) || !defined(_di_f_print_except_dynamic_in_raw_) || !defined(_di_f_print_except_in_dynamic_partial_raw_)

/**
 * Private implementation of f_print_except_in_raw_safely().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_in_raw_safely()
 * @see f_print_except_in_dynamic_raw_safely()
 * @see f_print_except_in_dynamic_partial_raw_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_except_in_raw_safely_) || !defined(_di_f_print_except_dynamic_in_raw_safely_) || !defined(_di_f_print_except_in_dynamic_partial_raw_safely_)
  extern f_status_t private_f_print_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_in_raw_safely_) || !defined(_di_f_print_except_dynamic_in_raw_safely_) || !defined(_di_f_print_except_in_dynamic_partial_raw_safely_)

/**
 * Private implementation of f_print_except_in_safely().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_in_safely()
 * @see f_print_except_in_dynamic_safely()
 * @see f_print_except_in_dynamic_partial_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_dynamic_in_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)
  extern f_status_t private_f_print_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_dynamic_in_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)

/**
 * Private implementation of f_print_except_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_raw()
 * @see f_print_except_dynamic_raw()
 * @see f_print_except_dynamic_partial_raw()
 */
#if !defined(_di_f_print_except_raw_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)
  extern f_status_t private_f_print_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_raw_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)

/**
 * Private implementation of f_print_except_raw_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_raw_safely()
 * @see f_print_except_dynamic_raw_safely()
 * @see f_print_except_dynamic_partial_raw_safely()
 */
#if !defined(_di_f_print_except_raw_safely_) || !defined(_di_f_print_except_dynamic_raw_safely_) || !defined(_di_f_print_except_dynamic_partial_raw_safely_)
  extern f_status_t private_f_print_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_raw_safely_) || !defined(_di_f_print_except_dynamic_raw_safely_) || !defined(_di_f_print_except_dynamic_partial_raw_safely_)

/**
 * Private implementation of f_print_except_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_except_safely()
 * @see f_print_except_dynamic_safely()
 * @see f_print_except_dynamic_partial_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_)
  extern f_status_t private_f_print_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_)

/**
 * Private implementation of f_print_raw().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_raw()
 * @see f_print_raw_dynamic()
 * @see f_print_raw_dynamic_partial()
 */
#if !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)
  extern f_status_t private_f_print_raw(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)

/**
 * Private implementation of f_print_raw_safely().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_raw_safely()
 * @see f_print_raw_safely_dynamic()
 * @see f_print_raw_safely_dynamic_partial()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_raw_safely_) || !defined(_di_f_print_raw_safely_dynamic_) || !defined(_di_f_print_raw_safely_dynamic_partial_)
  extern f_status_t private_f_print_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_raw_safely_) || !defined(_di_f_print_raw_safely_dynamic_) || !defined(_di_f_print_raw_safely_dynamic_partial_)

/**
 * Private implementation of f_print_safely().
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_safely()
 * @see f_print_safely_dynamic()
 * @see f_print_safely_dynamic_partial()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)
  extern f_status_t private_f_print_safely(const f_string_t string, const f_array_length_t length, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)

/**
 * Private implementation of f_print_safely_get().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   A string representing an ASCII or a UTF-8 character to get safe representation.
 * @param width_max
 *   This is set to the max number of bytes available.
 *   This is then updated to represent the max bytes used if enough space is available.
 *
 * @return
 *   NULL is returned if the character is already safe.
 *   A non-NULL string is returned if the character needs safe replacement.
 *   The non-NULL strings returned are NULL terminated.
 *   The non-NULL strings returned are the 3-byte characters used as placeholder symbols.
 *
 * @see f_print_character_safely_get()
 * @see f_print_dynamic_partial_safely()
 * @see f_print_dynamic_safely()
 * @see f_print_except_dynamic_partial_safely()
 * @see f_print_except_dynamic_safely()
 * @see f_print_except_in_dynamic_safely()
 * @see f_print_except_in_dynamic_partial_safely()
 * @see f_print_except_in_safely_
 * @see f_print_except_safely()
 * @see f_print_safely()
 * @see f_print_safely_terminated()
 * @see f_print_to_dynamic_partial_safely()
 * @see f_print_to_dynamic_safely()
 * @see f_print_to_except_dynamic_partial_safely()
 * @see f_print_to_except_dynamic_safely()
 * @see f_print_to_except_in_dynamic_safely()
 * @see f_print_to_except_in_dynamic_partial_safely()
 * @see f_print_to_except_in_safely_
 * @see f_print_to_except_safely()
 * @see f_print_to_safely()
 */
#if !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)
  extern const f_string_static_t private_f_print_safely_get(const f_string_t character, const f_array_length_t width_max) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)

/**
 * Private implementation of f_print_terminated().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_print_terminated()
 * @see f_print_raw_terminated()
 */
#if !defined(_di_f_print_terminated_) || !defined(_di_f_print_raw_terminated_)
  extern f_status_t private_f_print_terminated(const f_string_t string, FILE * const stream) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_terminated_) || !defined(_di_f_print_raw_terminated_)

/**
 * Determine max width, which is the shorter of the byte width and the remaining characters in the string.
 *
 * @param string
 *   The string to process.
 * @param at
 *   The position in the string representing a single character to get the width of.
 *
 * @return
 *   The determined with (the max size is 4).
 *
 * @see f_print_except_dynamic_partial_raw()
 * @see f_print_except_dynamic_partial_safely()
 * @see f_print_except_dynamic_raw()
 * @see f_print_except_dynamic_safely()
 * @see f_print_except_in_dynamic_partial_raw_safely()
 * @see f_print_except_in_dynamic_partial_safely()
 * @see f_print_except_in_dynamic_raw_safely()
 * @see f_print_except_in_dynamic_safely()
 * @see f_print_except_in_raw_safely()
 * @see f_print_except_in_safely()
 * @see f_print_except_raw_safely()
 * @see f_print_except_safely()
 * @see f_print_raw_safely()
 * @see f_print_raw_safely_dynamic()
 * @see f_print_raw_safely_dynamic_partial()
 * @see f_print_safely()
 * @see f_print_safely_dynamic()
 * @see f_print_safely_dynamic_partial()
 */
#if !defined(_di_f_print_except_dynamic_partial_raw_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_raw_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_dynamic_raw_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_raw_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_raw_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_raw_safely_) || !defined(_di_f_print_raw_safely_dynamic_) || !defined(_di_f_print_raw_safely_dynamic_partial_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)
  extern uint8_t private_f_print_width_max(const f_string_t string, const f_array_length_t at) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_except_dynamic_partial_raw_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_raw_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_dynamic_raw_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_raw_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_raw_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_raw_safely_) || !defined(_di_f_print_raw_safely_dynamic_) || !defined(_di_f_print_raw_safely_dynamic_partial_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_print_h

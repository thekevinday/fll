/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_utf8_print_h
#define _PRIVATE_utf8_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the bytesequence character (such as '豸').
 *
 * @param data
 *   The program data.
 * @param character
 *   The character to print.
 *   This is a string that represents a single character.
 */
#ifndef _di_utf8_print_bytesequence_
  extern void utf8_print_bytesequence(utf8_data_t * const data, const f_string_static_t character) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_bytesequence_

/**
 * Print an invalid character either as a Unicode codeblock or as a bytesequence.
 *
 * This handles whether or not the invalid character should be printed or not based on program parameters.
 *
 * @param data
 *   The program data.
 * @param character
 *   The character block to print.
 *
 * @see utf8_print_combining_or_width()
 */
#ifndef _di_utf8_print_character_invalid_
  extern void utf8_print_character_invalid(utf8_data_t * const data, const f_string_static_t character) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_character_invalid_

/**
 * Print the codepoint number as a codepoint string (such as U+8C78).
 *
 * @param data
 *   The program data.
 * @param codepoint
 *   The codepoint to print.
 *   This is the code that represents a single character.
 */
#ifndef _di_utf8_print_codepoint_
  extern void utf8_print_codepoint(utf8_data_t * const data, const uint32_t codepoint) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_codepoint_

/**
 * Print the width or combining state of the given character.
 *
 * @param data
 *   The program data.
 * @param character
 *   The character block whose width or combining state is to be printed.
 *
 * @see utf8_print_width()
 */
#ifndef _di_utf8_print_combining_or_width_
  extern void utf8_print_combining_or_width(utf8_data_t * const data, const f_string_static_t character) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_combining_or_width_

/**
 * Print an error regarding the width or combining state of a some character.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_utf8_print_error_combining_or_width_
  extern void utf8_print_error_combining_or_width(utf8_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_combining_or_width_

/**
 * Print error message when attempt to decode the character failed.
 *
 * @param data
 *   The program data.
 * @param character
 *   The character that is invalid.
 */
#ifndef _di_utf8_print_error_decode_
  extern void utf8_print_error_decode(utf8_data_t * const data, const f_status_t status, const f_string_static_t character) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_decode_

/**
 * Print error message when attempt to encode the character failed.
 *
 * @param data
 *   The program data.
 * @param codepoint
 *   The codepoint that is invalid.
 */
#ifndef _di_utf8_print_error_encode_
  extern void utf8_print_error_encode(utf8_data_t * const data, const f_status_t status, const uint32_t codepoint) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_encode_

/**
 * Print error message for when no sources are provided.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_utf8_print_error_no_from_
  extern void utf8_print_error_no_from(utf8_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_no_from_

/**
 * Print error message for when no sources are provided.
 *
 * @param data
 *   The program data.
 * @param parameter_1
 *   The long parameter name.
 */
#ifndef _di_utf8_print_error_no_value_
  extern void utf8_print_error_no_value(utf8_data_t * const data, const f_string_static_t parameter) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_no_value_

/**
 * Print error message for when the file parameter is an empty string.
 *
 * @param data
 *   The program data.
 * @param index
 *   The index within the argv[] array where the empty string is found.
 */
#ifndef _di_utf8_print_error_parameter_file_name_empty_
  extern void utf8_print_error_parameter_file_name_empty(utf8_data_t * const data, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_file_name_empty_

/**
 * Print error message for when no sources are provided in the main program parameters.
 *
 * @param data
 *   The program data.
 * @param from
 *   If TRUE, then this is a from file (source file).
 *   If FALSE, then this is a to file (destination file).
 * @param name
 *   The file path name.
 */
#ifndef _di_utf8_print_error_parameter_file_not_found_
  extern void utf8_print_error_parameter_file_not_found(utf8_data_t * const data, const bool from, const f_string_static_t name) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_file_not_found_

/**
 * Print error message for when too many 'to' destinations are specified.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  extern void utf8_print_error_parameter_file_to_too_many(utf8_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_file_to_too_many_

/**
 * Print the raw character data (binary / bytesequence).
 *
 * @param data
 *   The program data.
 * @param raw
 *   The raw string in integer format.
 * @param width
 *   The width the raw character represents (a value inclusively from 1 to 4).
 */
#ifndef _di_utf8_print_raw_bytesequence_
  extern void utf8_print_raw_bytesequence(utf8_data_t * const data, const f_utf_char_t raw, const uint8_t width) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_raw_bytesequence_

/**
 * Print the raw character data (codepoint).
 *
 * @param data
 *   The program data.
 * @param raw
 *   The raw string already in codepoint format.
 */
#ifndef _di_utf8_print_raw_codepoint_
  extern void utf8_print_raw_codepoint(utf8_data_t * const data, const f_string_static_t raw) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_raw_codepoint_

/**
 * Print the width or combining state of the for a raw character.
 *
 * @param data
 *   The program data.
 * @param width
 *   The pre-calculated width.
 *
 * @see utf8_print_width()
 */
#ifndef _di_utf8_print_raw_combining_or_width_
  extern void utf8_print_raw_combining_or_width(utf8_data_t * const data, const uint8_t width) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_raw_combining_or_width_

/**
 * Print the input file section header.
 *
 * @param data
 *   The program data.
 * @param name
 *   The name of the file.
 */
#ifndef _di_utf8_print_section_header_file_
  extern void utf8_print_section_header_file(utf8_data_t * const data, const f_string_static_t name) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_section_header_file_

/**
 * Print the input parameter section header.
 *
 * @param data
 *   The program data.
 * @param index
 *   The index position of the parameter.
 */
#ifndef _di_utf8_print_section_header_parameter_
  extern void utf8_print_section_header_parameter(utf8_data_t * const data, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_section_header_parameter_

/**
 * Print the input pipe section header.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_utf8_print_section_header_pipe_
  extern void utf8_print_section_header_pipe(utf8_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_section_header_pipe_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param data
 *   The program data.
 * @param signal
 *   The signal code received.
 */
#ifndef _di_utf8_print_signal_received_
  extern void utf8_print_signal_received(utf8_data_t * const data, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_signal_received_

/**
 * Print the width of the given character.
 *
 * @param data
 *   The program data.
 * @param character
 *   The character block whose width is to be printed.
 */
#ifndef _di_utf8_print_width_
  extern void utf8_print_width(utf8_data_t * const data, const f_string_static_t character) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_width_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_print_h

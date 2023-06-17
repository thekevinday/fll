/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_print_data_h
#define _utf8_print_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the byte sequence character (such as '豸').
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param sequence
 *   A byte sequences representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_bytesequence_
  extern f_status_t utf8_print_data_bytesequence(fl_print_t * const print, const f_string_static_t sequence);
#endif // _di_utf8_print_data_bytesequence_

/**
 * Print an invalid character either as a Unicode codeblock or as a byte sequence.
 *
 * This handles whether or not the invalid character should be printed or not based on program parameters.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param invalid
 *   The byte sequence string or unicode codepoint string representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see utf8_print_combining_or_width()
 */
#ifndef _di_utf8_print_data_character_invalid_
  extern f_status_t utf8_print_data_character_invalid(fl_print_t * const print, const f_string_static_t invalid);
#endif // _di_utf8_print_data_character_invalid_

/**
 * Print the codepoint number as a codepoint string (such as U+8C78).
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param codepoint
 *   The codepoint to print.
 *   This is the code that represents a single character.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_codepoint_
  extern f_status_t utf8_print_data_codepoint(fl_print_t * const print, const uint32_t codepoint);
#endif // _di_utf8_print_data_codepoint_

/**
 * Print the width or combining state of the given character.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param sequence
 *   A byte sequences representing a single character to print.
 *
 * @see utf8_print_width()
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_combining_or_width_
  extern f_status_t utf8_print_data_combining_or_width(fl_print_t * const print, const f_string_static_t sequence);
#endif // _di_utf8_print_data_combining_or_width_

/**
 * Print an error regarding the width or combining state of a some character.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_combining_or_width_invalid_
  extern f_status_t utf8_print_data_combining_or_width_invalid(fl_print_t * const print);
#endif // _di_utf8_print_data_combining_or_width_invalid_

/**
 * Print the raw character data (binary / byte sequence).
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param raw
 *   The raw string in integer format.
 * @param width
 *   The width the raw character represents (a value inclusively from 1 to 4).
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_raw_bytesequence_
  extern f_status_t utf8_print_data_raw_bytesequence(fl_print_t * const print, const f_utf_char_t raw, const uint8_t width);
#endif // _di_utf8_print_data_raw_bytesequence_

/**
 * Print the raw character data (codepoint).
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param raw
 *   The raw string already in codepoint format.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_raw_codepoint_
  extern f_status_t utf8_print_data_raw_codepoint(fl_print_t * const print, const f_string_static_t raw);
#endif // _di_utf8_print_data_raw_codepoint_

/**
 * Print the width or combining state of the for a raw character.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param width
 *   The pre-calculated width.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see utf8_print_data_width()
 */
#ifndef _di_utf8_print_data_raw_combining_or_width_
  extern f_status_t utf8_print_data_raw_combining_or_width(fl_print_t * const print, const uint8_t width);
#endif // _di_utf8_print_data_raw_combining_or_width_

/**
 * Print the input file section header.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the file.
 * @param index
 *   The index position of the file.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_section_header_file_
  extern f_status_t utf8_print_data_section_header_file(fl_print_t * const print, const f_string_static_t name, const f_number_unsigned_t index);
#endif // _di_utf8_print_data_section_header_file_

/**
 * Print the input parameter section header.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param index
 *   The index position of the parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_section_header_parameter_
  extern f_status_t utf8_print_data_section_header_parameter(fl_print_t * const print, const f_number_unsigned_t index);
#endif // _di_utf8_print_data_section_header_parameter_

/**
 * Print the input pipe section header.
 *
 * @param print
 *   Designates the how and where to print.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_section_header_pipe_
  extern f_status_t utf8_print_data_section_header_pipe(fl_print_t * const print);
#endif // _di_utf8_print_data_section_header_pipe_

/**
 * Print the width of the given character.
 *
 * @param print
 *   Designates the how and where to print.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param sequence
 *   A byte sequences representing a single character whose width is to be printed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_data_width_
  extern f_status_t utf8_print_data_width(fl_print_t * const print, const f_string_static_t sequence);
#endif // _di_utf8_print_data_width_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_print_data_h

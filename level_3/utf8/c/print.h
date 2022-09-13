/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _utf8_print_h
#define _utf8_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the byte sequence character (such as '豸').
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param sequence
 *   A byte sequences representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_bytesequence_
  extern f_status_t utf8_print_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence);
#endif // _di_utf8_print_bytesequence_

/**
 * Print an invalid character either as a Unicode codeblock or as a byte sequence.
 *
 * This handles whether or not the invalid character should be printed or not based on program parameters.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param invalid
 *   The byte sequence string or unicode codepoint string representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see utf8_print_combining_or_width()
 */
#ifndef _di_utf8_print_character_invalid_
  extern f_status_t utf8_print_character_invalid(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t invalid);
#endif // _di_utf8_print_character_invalid_

/**
 * Print the codepoint number as a codepoint string (such as U+8C78).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param codepoint
 *   The codepoint to print.
 *   This is the code that represents a single character.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_codepoint_
  extern f_status_t utf8_print_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const uint32_t codepoint);
#endif // _di_utf8_print_codepoint_

/**
 * Print the width or combining state of the given character.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param sequence
 *   A byte sequences representing a single character to print.
 *
 * @see utf8_print_width()
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_combining_or_width_
  extern f_status_t utf8_print_combining_or_width(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence);
#endif // _di_utf8_print_combining_or_width_

/**
 * Print an error regarding the width or combining state of a some character.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_combining_or_width_
  extern f_status_t utf8_print_error_combining_or_width(fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_print_error_combining_or_width_

/**
 * Print error message when attempt to decode the character failed.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param invalid
 *   The byte sequence string or unicode codepoint string representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_decode_
  extern f_status_t utf8_print_error_decode(fll_program_data_t * const main, utf8_setting_t * const setting, const f_status_t status, const f_string_static_t invalid);
#endif // _di_utf8_print_error_decode_

/**
 * Print error message when attempt to encode the character failed.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param codepoint
 *   The codepoint that is invalid.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_encode_
  extern f_status_t utf8_print_error_encode(fll_program_data_t * const main, utf8_setting_t * const setting, const f_status_t status, const uint32_t codepoint);
#endif // _di_utf8_print_error_encode_

/**
 * Print error message for when no sources are provided.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_no_from_
  extern f_status_t utf8_print_error_no_from(fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_print_error_no_from_

/**
 * Print error message for when the file parameter is an empty string.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param index
 *   The index within the argv[] array where the empty string is found.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_parameter_file_name_empty_
  extern f_status_t utf8_print_error_parameter_file_name_empty(fll_program_data_t * const main, utf8_setting_t * const setting, const f_array_length_t index);
#endif // _di_utf8_print_error_parameter_file_name_empty_

/**
 * Print error message for when no sources are provided in the main program parameters.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param from
 *   If TRUE, then this is a from file (source file).
 *   If FALSE, then this is a to file (destination file).
 * @param name
 *   The file path name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_parameter_file_not_found_
  extern f_status_t utf8_print_error_parameter_file_not_found(fll_program_data_t * const main, utf8_setting_t * const setting, const bool from, const f_string_static_t name);
#endif // _di_utf8_print_error_parameter_file_not_found_

/**
 * Print error message for when too many 'to' destinations are specified.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  extern f_status_t utf8_print_error_parameter_file_to_too_many(fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_print_error_parameter_file_to_too_many_

/**
 * Flush the output, if appropriate.
 *
 * This is intended to be run after the utf8_main() is complete.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_flush_
  extern f_status_t utf8_print_flush(fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_print_flush_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_help_
  extern f_status_t utf8_print_help(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_help_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_line_first_locked_
  extern f_status_t utf8_print_line_first_locked(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_line_first_locked_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_line_first_unlocked_
  extern f_status_t utf8_print_line_first_unlocked(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_line_first_unlocked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_line_last_locked_
  extern f_status_t utf8_print_line_last_locked(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_line_last_locked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_line_last_unlocked_
  extern f_status_t utf8_print_line_last_unlocked(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_line_last_unlocked_

/**
 * Print the raw character data (binary / byte sequence).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param raw
 *   The raw string in integer format.
 * @param width
 *   The width the raw character represents (a value inclusively from 1 to 4).
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_raw_bytesequence_
  extern f_status_t utf8_print_raw_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_utf_char_t raw, const uint8_t width);
#endif // _di_utf8_print_raw_bytesequence_

/**
 * Print the raw character data (codepoint).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param raw
 *   The raw string already in codepoint format.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_raw_codepoint_
  extern f_status_t utf8_print_raw_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t raw);
#endif // _di_utf8_print_raw_codepoint_

/**
 * Print the width or combining state of the for a raw character.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param width
 *   The pre-calculated width.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see utf8_print_width()
 */
#ifndef _di_utf8_print_raw_combining_or_width_
  extern f_status_t utf8_print_raw_combining_or_width(fll_program_data_t * const main, utf8_setting_t * const setting, const uint8_t width);
#endif // _di_utf8_print_raw_combining_or_width_

/**
 * Print the input file section header.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param name
 *   The name of the file.
 * @param index
 *   The index position of the file.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_section_header_file_
  extern f_status_t utf8_print_section_header_file(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t name, const f_array_length_t index);
#endif // _di_utf8_print_section_header_file_

/**
 * Print the input parameter section header.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param index
 *   The index position of the parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_section_header_parameter_
  extern f_status_t utf8_print_section_header_parameter(fll_program_data_t * const main, utf8_setting_t * const setting, const f_array_length_t index);
#endif // _di_utf8_print_section_header_parameter_

/**
 * Print the input pipe section header.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_section_header_pipe_
  extern f_status_t utf8_print_section_header_pipe(fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_print_section_header_pipe_

/**
 * Print the width of the given character.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   Assumed to always be non-NULL.
 * @param sequence
 *   A byte sequences representing a single character whose width is to be printed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_utf8_print_width_
  extern f_status_t utf8_print_width(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence);
#endif // _di_utf8_print_width_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_print_h

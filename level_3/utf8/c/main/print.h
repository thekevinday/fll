/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _utf8_print_h
#define _utf8_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_utf8_print_error_
  extern f_status_t utf8_print_error(utf8_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_utf8_print_error_

/**
 * Print error message when attempt to decode the character failed.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param invalid
 *   The byte sequence string or unicode codepoint string representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_error_decode_
  extern f_status_t utf8_print_error_decode(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t invalid);
#endif // _di_utf8_print_error_decode_

/**
 * Print error message when attempt to encode the character failed.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param codepoint
 *   The codepoint that is invalid.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_error_encode_
  extern f_status_t utf8_print_error_encode(utf8_setting_t * const setting, const fl_print_t print, const uint32_t codepoint);
#endif // _di_utf8_print_error_encode_

/**
 * Print file related error or warning messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_utf8_print_error_file_
  extern f_status_t utf8_print_error_file(utf8_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_utf8_print_error_file_

/**
 * Print error message for when no sources are provided.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_error_no_from_
  extern f_status_t utf8_print_error_no_from(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_error_no_from_

/**
 * Print error message for when the file parameter is an empty string.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param index
 *   The index within the argv[] array where the empty string is found.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_error_parameter_file_name_empty_
  extern f_status_t utf8_print_error_parameter_file_name_empty(utf8_setting_t * const setting, const fl_print_t print, const f_array_length_t index);
#endif // _di_utf8_print_error_parameter_file_name_empty_

/**
 * Print error message for when no sources are provided in the main program parameters.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param from
 *   If TRUE, then this is a from file (source file).
 *   If FALSE, then this is a to file (destination file).
 * @param name
 *   The file path name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_error_parameter_file_not_found_
  extern f_status_t utf8_print_error_parameter_file_not_found(utf8_setting_t * const setting, const fl_print_t print, const bool from, const f_string_static_t name);
#endif // _di_utf8_print_error_parameter_file_not_found_

/**
 * Print error message for when too many 'to' destinations are specified.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  extern f_status_t utf8_print_error_parameter_file_to_too_many(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_error_parameter_file_to_too_many_

/**
 * Print the byte sequence character (such as '豸').
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param sequence
 *   A byte sequences representing a single character to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_bytesequence_
  extern f_status_t utf8_print_bytesequence(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t sequence);
#endif // _di_utf8_print_bytesequence_

/**
 * Print an invalid character either as a Unicode codeblock or as a byte sequence.
 *
 * This handles whether or not the invalid character should be printed or not based on program parameters.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
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
#ifndef _di_utf8_print_character_invalid_
  extern f_status_t utf8_print_character_invalid(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t invalid);
#endif // _di_utf8_print_character_invalid_

/**
 * Print the codepoint number as a codepoint string (such as U+8C78).
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
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
#ifndef _di_utf8_print_codepoint_
  extern f_status_t utf8_print_codepoint(utf8_setting_t * const setting, const fl_print_t print, const uint32_t codepoint);
#endif // _di_utf8_print_codepoint_

/**
 * Print the width or combining state of the given character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
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
#ifndef _di_utf8_print_combining_or_width_
  extern f_status_t utf8_print_combining_or_width(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t sequence);
#endif // _di_utf8_print_combining_or_width_

/**
 * Print an error regarding the width or combining state of a some character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_combining_or_width_invalid_
  extern f_status_t utf8_print_combining_or_width_invalid(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_combining_or_width_invalid_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
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
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
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
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
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
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
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
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_line_last_unlocked_
  extern f_status_t utf8_print_line_last_unlocked(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_line_last_unlocked_

/**
 * Print the raw character data (binary / byte sequence).
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
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
#ifndef _di_utf8_print_raw_bytesequence_
  extern f_status_t utf8_print_raw_bytesequence(utf8_setting_t * const setting, const fl_print_t print, const f_utf_char_t raw, const uint8_t width);
#endif // _di_utf8_print_raw_bytesequence_

/**
 * Print the raw character data (codepoint).
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param raw
 *   The raw string already in codepoint format.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_raw_codepoint_
  extern f_status_t utf8_print_raw_codepoint(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t raw);
#endif // _di_utf8_print_raw_codepoint_

/**
 * Print the width or combining state of the for a raw character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param width
 *   The pre-calculated width.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see utf8_print_width()
 */
#ifndef _di_utf8_print_raw_combining_or_width_
  extern f_status_t utf8_print_raw_combining_or_width(utf8_setting_t * const setting, const fl_print_t print, const uint8_t width);
#endif // _di_utf8_print_raw_combining_or_width_

/**
 * Print the input file section header.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
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
#ifndef _di_utf8_print_section_header_file_
  extern f_status_t utf8_print_section_header_file(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_array_length_t index);
#endif // _di_utf8_print_section_header_file_

/**
 * Print the input parameter section header.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param index
 *   The index position of the parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_section_header_parameter_
  extern f_status_t utf8_print_section_header_parameter(utf8_setting_t * const setting, const fl_print_t print, const f_array_length_t index);
#endif // _di_utf8_print_section_header_parameter_

/**
 * Print the input pipe section header.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_section_header_pipe_
  extern f_status_t utf8_print_section_header_pipe(utf8_setting_t * const setting, const fl_print_t print);
#endif // _di_utf8_print_section_header_pipe_

/**
 * Print the width of the given character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param sequence
 *   A byte sequences representing a single character whose width is to be printed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_utf8_print_width_
  extern f_status_t utf8_print_width(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t sequence);
#endif // _di_utf8_print_width_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_print_h

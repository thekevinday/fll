/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_print_error_h
#define _utf8_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
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
 *
 * @see fll_error_print()
 */
#ifndef _di_utf8_print_error_
  extern f_status_t utf8_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_utf8_print_error_

/**
 * Print error message when attempt to decode the character failed.
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
 * @see fl_print_format()
 */
#ifndef _di_utf8_print_error_decode_
  extern f_status_t utf8_print_error_decode(fl_print_t * const print, const f_string_static_t invalid);
#endif // _di_utf8_print_error_decode_

/**
 * Print error message when attempt to encode the character failed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param codepoint
 *   The codepoint that is invalid.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fl_print_format()
 */
#ifndef _di_utf8_print_error_encode_
  extern f_status_t utf8_print_error_encode(fl_print_t * const print, const uint32_t codepoint);
#endif // _di_utf8_print_error_encode_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
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
  extern f_status_t utf8_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_utf8_print_error_file_

/**
 * Print error message for when no sources are provided.
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
 *
 * @see fll_error_file_print()
 */
#ifndef _di_utf8_print_error_no_from_
  extern f_status_t utf8_print_error_no_from(fl_print_t * const print);
#endif // _di_utf8_print_error_no_from_

/**
 * Print error message for when the file parameter is an empty string.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param index
 *   The index within the argv[] array where the empty string is found.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_utf8_print_error_parameter_file_name_empty_
  extern f_status_t utf8_print_error_parameter_file_name_empty(fl_print_t * const print, const f_number_unsigned_t index);
#endif // _di_utf8_print_error_parameter_file_name_empty_

/**
 * Print error message for when no sources are provided in the main program parameters.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
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
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_utf8_print_error_parameter_file_not_found_
  extern f_status_t utf8_print_error_parameter_file_not_found(fl_print_t * const print, const bool from, const f_string_static_t name);
#endif // _di_utf8_print_error_parameter_file_not_found_

/**
 * Print error message for when too many 'to' destinations are specified.
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
 *
 * @see fll_print_format()
 */
#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  extern f_status_t utf8_print_error_parameter_file_to_too_many(fl_print_t * const print);
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_print_error_h

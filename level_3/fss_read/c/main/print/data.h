/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_print_data_h
#define _fss_read_print_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process printing the buffer according to an Object index position and given delimits.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * This processes multiple Content ranges and calls main.callback.print_content() for each individual Content range.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param at
 *   The Object index to be printed.
 * @param delimits_object
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 * @param delimits_content
 *   The delimits array representing a delimited Content.
 *   This represents the positions within the current Content at the "at" position.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_partial()
 * @see fll_print_except_dynamic_partial()
 * @see fll_print_trim_dynamic_partial()
 * @see fll_print_trim_except_dynamic_partial()
 *
 * @see main.callback.print_content()
 * @see main.callback.print_object()
 * @see main.callback.print_object_end()
 * @see main.callback.print_set_end()
 */
#ifndef _di_fss_read_print_at_
  extern f_status_t fss_read_print_at(fl_print_t * const print, const f_number_unsigned_t at, const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content);
#endif // _di_fss_read_print_at_

/**
 * Print the Content.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * This processes single Content range.
 * This does not print a new line after the Content.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param range
 *   The range within the buffer representing the Content to print.
 * @param quote
 *   The quote type representing the character to use (from the f_fss_quote_type_*_e).
 * @param delimits
 *   The delimits array representing a delimited Content.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_except_in_dynamic_partial()
 * @see main.callback.print_content()
 * @see main.callback.print_object_end()
 * @see main.callback.print_set_end()
 */
#ifndef _di_fss_read_print_content_
  extern f_status_t fss_read_print_content(fl_print_t * const print, const f_string_range_t range, const uint8_t quote, const f_number_unsigneds_t delimits);
#endif // _di_fss_read_print_content_

/**
 * Print the ignore character for Content.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_fss_read_print_content_ignore_
  extern f_status_t fss_read_print_content_ignore(fl_print_t * const print);
#endif // _di_fss_read_print_content_ignore_

/**
 * Print the number and a newline.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param number
 *   The number to print.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_fss_read_print_number_
  extern f_status_t fss_read_print_number(fl_print_t * const print, const f_number_unsigned_t number);
#endif // _di_fss_read_print_number_

/**
 * Print the Object at the given Object index position.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * Different standards may want to call this before they perform their final printing.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param at
 *   The Object index to be printed.
 * @param delimits
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_partial()
 * @see fll_print_except_dynamic_partial()
 * @see fll_print_trim_dynamic_partial()
 * @see fll_print_trim_except_dynamic_partial()
 *
 * @see fss_read_print_quote()
 */
#ifndef _di_fss_read_print_object_
  extern f_status_t fss_read_print_object(fl_print_t * const print, const f_number_unsigned_t at, const f_number_unsigneds_t delimits);
#endif // _di_fss_read_print_object_

/**
 * Print the Object at the given Object index position.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param at
 *   The Object index position to be printed.
 * @param delimits
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_fss_read_print_quote_
  extern f_status_t fss_read_print_quote(fl_print_t * const print, const uint8_t type);
#endif // _di_fss_read_print_quote_

/**
 * Print the end of an Object/Content set.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_fss_read_print_set_end_
  extern f_status_t fss_read_print_set_end(fl_print_t * const print);
#endif // _di_fss_read_print_set_end_

/**
 * Print the end of an Object/Content set.
 *
 * This is a variation of fss_read_print_set_end() that does not print the EOL.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_fss_read_print_set_end_no_eol_
  extern f_status_t fss_read_print_set_end_no_eol(fl_print_t * const print);
#endif // _di_fss_read_print_set_end_no_eol_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_print_data_h

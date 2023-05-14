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
 * Print the Content.
 *
 * This does not lock the stream.
 *
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
 * @param delimits
 *   The delimits array representing a delimited Content.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see f_print_except_in_dynamic_partial()
 */
#ifndef _di_fss_read_print_content_
  extern f_status_t fss_read_print_content(fl_print_t * const print, const f_array_length_t at, const f_fss_delimits_t delimits);
#endif // _di_fss_read_print_content_

/**
 * Print the number and a newline.
 *
 * This does not lock the stream.
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
 *   F_none on success.
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
 * Print the Object at the given position.
 *
 * This does not lock the stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param at
 *   The "at" position to be printed.
 * @param delimits
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see f_print_except_dynamic_partial()
 * @see fl_print_trim_except_dynamic_partial()
 *
 * @see fss_read_print_object_end() @todo replace this with appropriate print callback.
 */
#ifndef _di_fss_read_print_object_at_
  extern f_status_t fss_read_print_object_at(fl_print_t * const print, const f_array_length_t at, const f_fss_delimits_t delimits);
#endif // _di_fss_read_print_object_at_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_print_data_h

/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_read_extended_print_h
#define _fss_read_extended_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process printing the buffer according to "at" position and given delimits.
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
 *   The "at" position to be printed.
 * @param delimits_object
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 * @param delimits_content
 *   The delimits array representing a delimited Content.
 *   This represents the positions within the current Content at the "at" position.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_print_dynamic_partial()
 * @see fll_print_except_dynamic_partial()
 * @see fll_print_trim_dynamic_partial()
 * @see fll_print_trim_except_dynamic_partial()
 *
 * @see main.callback.print_object()
 * @see main.callback.print_object_end()
 * @see main.callback.print_set_end()
 */
#ifndef _di_fss_read_extended_print_at_
  extern f_status_t fss_read_extended_print_at(fl_print_t * const print, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content);
#endif // _di_fss_read_extended_print_at_

/**
 * Print help for FSS-0001 (Extended).
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
#ifndef _di_fss_read_extended_print_help_
  extern f_status_t fss_read_extended_print_help(fl_print_t * const print);
#endif // _di_fss_read_extended_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_extended_print_h

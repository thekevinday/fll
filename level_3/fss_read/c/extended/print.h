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
 * Print the next part of a Content.
 *
 * This locks, uses, and unlocks the file stream.
 *
 * This is not the Content set end.
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
#ifndef _di_fss_read_extended_print_data_content_next_
  extern f_status_t fss_read_extended_print_data_content_next(fl_print_t * const print);
#endif // _di_fss_read_extended_print_data_content_next_

/**
 * Print the end of an Object (which is often the start of Content).
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
#ifndef _di_fss_read_extended_print_data_object_end_
  extern f_status_t fss_read_extended_print_data_object_end(fl_print_t * const print);
#endif // _di_fss_read_extended_print_data_object_end_

/**
 * Print help for FSS-0001 (Extended).
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fss_read_extended_print_message_help_
  extern f_status_t fss_read_extended_print_message_help(fl_print_t * const print);
#endif // _di_fss_read_extended_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_extended_print_h

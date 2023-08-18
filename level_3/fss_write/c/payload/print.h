/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_write_payload_print_h
#define _fss_write_payload_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error message about the "payload" not being specified last (when it is specified at all).
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
 * @see fll_error_print()
 */
#ifndef _di_fss_write_payload_print_error_payload_not_last_
  extern f_status_t fss_write_payload_print_error_payload_not_last(fl_print_t * const print);
#endif // _di_fss_write_payload_print_error_payload_not_last_

/**
 * Print help for FSS-000E (Payload).
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
 */
#ifndef _di_fss_write_payload_print_help_
  extern f_status_t fss_write_payload_print_help(fl_print_t * const print);
#endif // _di_fss_write_payload_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_payload_print_h

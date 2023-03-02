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
 * @see fll_error_print()
 */
#ifndef _di_fss_write_payload_print_error_payload_not_last_
  extern f_status_t fss_write_payload_print_error_payload_not_last(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_payload_print_error_payload_not_last_

/**
 * Print help for FSS-000E (Payload).
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
 */
#ifndef _di_fss_write_payload_print_help_
  extern f_status_t fss_write_payload_print_help(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_payload_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_payload_print_h

/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_print_data_h
#define _fss_identify_print_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the given FLL identifier.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param id
 *   The Identifier to print.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fss_identify_print_data_id_
  extern f_status_t fss_identify_print_data_id(fl_print_t * const print, const f_fll_id_t id);
#endif // _di_fss_identify_print_data_id_

/**
 * Print the total.
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
#ifndef _di_fss_identify_print_data_total_
  extern f_status_t fss_identify_print_data_total(fl_print_t * const print);
#endif // _di_fss_identify_print_data_total_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_print_data_h

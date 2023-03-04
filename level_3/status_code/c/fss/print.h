/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_fss_print_h
#define _status_code_fss_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help detailed part of the help for fss_status_code.
 *
 * This is designed to be called from within status_code_print_help().
 * This neither locks nor unlocks the stream and expects the stream to be unlocked.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type status_code_setting_t.)
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
 *
 * @see fl_print_format()
 *
 * @see status_code_print_help()
 */
#ifndef _di_status_code_fss_print_help_detail_
  extern f_status_t status_code_fss_print_help_detail(void * const setting, const fl_print_t print);
#endif // _di_status_code_fss_print_help_detail_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_fss_print_h

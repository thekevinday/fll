/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_identify_print_h
#define _fss_identify_print_h

#ifdef __cplusplus
extern "C" {
#endif

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
 */
#ifndef _di_fss_identify_print_help_
  extern f_status_t fss_identify_print_help(fss_identify_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_identify_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_print_h

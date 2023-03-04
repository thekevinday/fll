/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_write_embedded_list_print_h
#define _fss_write_embedded_list_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help for FSS-0008 (Embedded List).
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
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fss_write_embedded_list_print_help_
  extern f_status_t fss_write_embedded_list_print_help(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_embedded_list_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_embedded_list_print_h

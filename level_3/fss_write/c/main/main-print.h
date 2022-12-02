/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_write_main_print_h
#define _fss_write_main_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error message about a value given to the --as parameter being unknown.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param value
 *   A string representing the value that is of an unknown format.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_main_print_error_format_unknown_
  extern f_status_t fss_write_main_print_error_format_unknown(const fl_print_t print, const f_string_static_t value);
#endif // _di_fss_write_main_print_error_format_unknown_

/**
 * Print help for "main" fss_write.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_print_main_help_
  extern f_status_t fss_write_main_print_help(fss_write_setting_t * const setting, const fl_print_t print);
#endif // _di_fss_write_print_main_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_main_print_h

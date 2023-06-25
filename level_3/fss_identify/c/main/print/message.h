/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_print_message_h
#define _fss_identify_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
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
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fl_print_format()
 *
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_standard()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_fss_identify_print_message_help_
  extern f_status_t fss_identify_print_message_help(fl_print_t * const print);
#endif // _di_fss_identify_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_print_message_h

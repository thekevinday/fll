/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_print_message_h
#define _status_code_print_message_h

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
 *   F_okay on success.
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
#ifndef _di_status_code_print_message_help_
  extern f_status_t status_code_print_message_help(fl_print_t * const print);
#endif // _di_status_code_print_message_help_

/**
 * Print help detailed part of the help.
 *
 * This is designed to be called from within status_code_print_message_help().
 * This neither locks nor unlocks the stream and expects the stream to be unlocked.
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
 *
 * @see fl_print_format()
 *
 * @see status_code_print_message_help()
 */
#ifndef _di_status_code_print_message_help_detail_
  extern f_status_t status_code_print_message_help_detail(fl_print_t * const print);
#endif // _di_status_code_print_message_help_detail_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_message_h

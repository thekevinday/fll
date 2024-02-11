/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_print_message_h
#define _firewall_print_message_h

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
#ifndef _di_firewall_print_message_help_
  extern f_status_t firewall_print_message_help(fl_print_t * const print);
#endif // _di_firewall_print_message_help_

/**
 * Print show option header.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param left
 *   The option to show on the left side of the header text.
 *   The left.used may be 0.
 * @param header
 *   The header text.
 *   The header.used should not be 0.
 * @param right
 *   The option to show on the right side of the header text.
 *   The right.used may be 0.
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
 */
#ifndef _di_firewall_print_message_show_header_
  extern f_status_t firewall_print_message_show_header(fl_print_t * const print, const f_string_static_t left, const f_string_static_t header, const f_string_static_t right);
#endif // _di_firewall_print_message_show_header_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_print_message_h

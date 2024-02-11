/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print warning functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_print_warning_h
#define _firewall_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print warning message regarding a show option not being known.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param option
 *   The show option that is not known.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_firewall_print_warning_show_option_unknown_
  extern f_status_t firewall_print_warning_show_option_unknown(fl_print_t * const print, const f_string_static_t option);
#endif // _di_firewall_print_warning_show_option_unknown_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_print_warning_h

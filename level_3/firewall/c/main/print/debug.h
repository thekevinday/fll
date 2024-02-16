/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print debug functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_print_debug_h
#define _firewall_print_debug_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print debug information about tool execution.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param tool
 *   The name of the function associated with the error.
 * @param arguments
 *   The name of the file, if this error is assocaited with a file.
 *   Otherwise, set file.used to 0 to not have an file related error message.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_firewall_print_debug_tool_
  extern f_status_t firewall_print_debug_tool(fl_print_t * const print, const f_string_static_t tool, const f_string_statics_t arguments);
#endif // _di_firewall_print_debug_tool_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_print_debug_h

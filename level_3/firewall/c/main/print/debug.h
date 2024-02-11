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
 * @param output
 *   The output to print to.
 * @param tool
 *   The iptables tool.
 * @param arguments
 *   The arguments passed to the tool.
 */
#ifndef _di_firewall_print_debug_tool_
  extern void firewall_print_debug_tool(const fl_print_t output, const f_string_static_t tool, const f_string_statics_t arguments);
#endif // _di_firewall_print_debug_tool_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_print_debug_h

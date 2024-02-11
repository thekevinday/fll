/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the buffer functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_buffer_h
#define _firewall_operate_buffer_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Buffer firewall rules.
 *
 * @param data
 *   The program data.
 * @param filename
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_firewall_operate_buffer_rules_
  extern f_status_t firewall_operate_buffer_rules(firewall_main_t * const main, const f_string_static_t filename, const bool optional);
#endif // _di_firewall_operate_buffer_rules_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_buffer_h

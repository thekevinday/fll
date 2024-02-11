/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the load functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_load_h
#define _firewall_operate_load_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process buffered rules.
 *
 * @param data
 *   The program data.
 * @param chain
 *   The position representing the current chain being processed.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_firewall_operate_load_rules_
  extern f_status_t firewall_operate_load_rules(firewall_main_t * const main);
#endif // _di_firewall_operate_load_rules_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_load_h

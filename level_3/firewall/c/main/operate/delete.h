/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the delete functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_operate_delete_h
#define _firewall_operate_delete_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Deallocate chains.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_parameter (with error bit) on invalid parameter passed.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_firewall_operate_delete_chains_
  extern f_status_t firewall_operate_delete_chains(firewall_main_t * const main);
#endif // _di_firewall_operate_delete_chains_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_operate_delete_h

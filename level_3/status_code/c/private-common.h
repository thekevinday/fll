/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_status_code_print_signal_received_
  extern void status_code_print_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_status_code_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h

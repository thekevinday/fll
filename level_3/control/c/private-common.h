/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
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
 * @param signal
 *   The signal received.
 */
#ifndef _di_control_print_signal_received_
  extern void control_print_signal_received(control_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_control_print_signal_received_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_control_signal_received_
  extern f_status_t control_signal_received(control_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h

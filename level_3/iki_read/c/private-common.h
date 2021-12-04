/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide common/generic definitions.
 *
 * iki_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_iki_read_common_
  #define iki_read_common_allocation_large_d 256
  #define iki_read_common_allocation_small_d 16
#endif // _di_iki_read_common_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_iki_read_print_signal_received_
  extern void iki_read_print_signal_received(iki_read_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_signal_received_

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
#ifndef _di_iki_read_signal_received_
  extern f_status_t iki_read_signal_received(iki_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_iki_read_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h

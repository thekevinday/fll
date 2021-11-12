/**
 * FLL - Level 3
 *
 * Project: FSS Status Code
 * API Version: 0.5
 * Licenses: lgplv2.1
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
#ifndef _di_fss_status_code_print_signal_received_
  extern void fss_status_code_print_signal_received(fss_status_code_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_print_signal_received_

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
#ifndef _di_fss_status_code_signal_received_
  extern f_status_t fss_status_code_signal_received(fss_status_code_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h

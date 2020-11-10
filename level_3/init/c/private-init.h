/**
 * FLL - Level 3
 *
 * Project: Init
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_init_h
#define _PRIVATE_init_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @todo
 */
#ifndef _di_init_load_failsafe_
  extern f_return_status init_load_failsafe(const init_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_init_load_failsafe_

/**
 * @todo
 */
#ifndef _di_init_load_kernel_setting_
  extern f_return_status init_load_kernel_setting(const init_data_t data, init_setting_kernel_t *setting_kernel) f_gcc_attribute_visibility_internal;
#endif // _di_init_load_kernel_setting_

/**
 * Check to see if a termination signal has been received.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_true if a termination signal is received.
 *   F_false if no termination signal is received.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_init_signal_read_
  extern f_return_status init_signal_received(const init_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_init_signal_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_init_h

/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_thread_signal_h
#define _PRIVATE_thread_signal_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling signals/interrupts.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param global
 *   The global data.
 */
#ifndef _di_controller_thread_signal_
  extern void controller_thread_signal(const bool is_normal, controller_global_t *global) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_signal_

/**
 * Callback passed to FSS functions for checking for interrupts.
 *
 * @param state
 *   The f_state_t data.
 * @param internal
 *   Not used.
 *
 * @return
 *   F_interrupt_not if not interrupted.
 *
 *   F_interrupt (with error bit) if interrupted.
 */
#ifndef _di_controller_thread_signal_state_fss_
  extern f_status_t controller_thread_signal_state_fss(void *state, void *internal) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_signal_state_fss_

/**
 * Callback passed to IKI functions for checking for interrupts.
 *
 * @param state
 *   The f_state_t data.
 * @param internal
 *   Not used.
 *
 * @return
 *   F_interrupt_not if not interrupted.
 *
 *   F_interrupt (with error bit) if interrupted.
 */
#ifndef _di_controller_thread_signal_state_iki_
  extern f_status_t controller_thread_signal_state_iki(void *state, void *internal) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_signal_state_iki_

/**
 * Thread for handling signals/interrupts during normal operations.
 *
 * Currently this only handles signals to exist, but may be updated to handle interrupt and hangup signals.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_signal()
 */
#ifndef _di_controller_thread_signal_normal_
  extern void * controller_thread_signal_normal(void *arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_signal_normal_

/**
 * Thread for handling signals/interrupts during other operations.
 *
 * Currently this only handles signals to exist, but may be updated to handle interrupt and hangup signals.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_signal()
 */
#ifndef _di_controller_thread_signal_other_
  extern void * controller_thread_signal_other(void *arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_signal_h

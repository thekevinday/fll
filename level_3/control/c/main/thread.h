/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides thread functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_thread_h
#define _control_thread_h

/**
 * Thread handler for signals/interrupts.
 *
 * If main.signal is non-zero, then this handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The program and settings data.
 *
 *   Must be of type control_main_t.
 *
 * @return
 *   0, always.
 *
 * @see f_thread_cancel_state_set()
 *
 * @see control_signal_handler()
 */
#if !defined(_di_control_thread_signal_) && !defined(_di_thread_support_)
  extern void * control_thread_signal(void * const main);
#endif // !defined(_di_control_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_thread_h

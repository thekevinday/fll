/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides thread functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_thread_h
#define _iki_write_thread_h

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
 *   Must be of type iki_write_main_t.
 *
 * @return
 *   0, always.
 *
 * @see f_thread_cancel_state_set()
 *
 * @see iki_write_signal_handler()
 */
#if !defined(_di_iki_write_thread_signal_) && !defined(_di_thread_support_)
  extern void * iki_write_thread_signal(void * const main);
#endif // !defined(_di_iki_write_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_thread_h

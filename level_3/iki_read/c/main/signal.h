/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides signal functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_signal_h
#define _iki_read_signal_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to see if a signal is received.
 *
 * If main.signal is non-zero, then this handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * There is a threaded and a non-threaded version of this.
 * The non-threaded version checks periodically using iki_read_signal_check_d and updates main->signal_check as needed.
 * The threaded version checks the flag state which is set by a separate thread that is blocking until signal is received.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This does not alter main.setting.state.status.
 *
 * @return
 *   F_true on signal received.
 *   F_false otherwise.
 *
 * @see iki_read_signal_handler()
 *
 * @see fll_program_standard_signal_received()
 */
#ifndef _di_iki_read_signal_check_
  extern f_status_t iki_read_signal_check(iki_read_main_t * const main);
#endif // _di_iki_read_signal_check_

/**
 * Signal handler for signals/interrupts.
 *
 * This blocks until an expected signal is recieved.
 * When an expected signal is received it then sets the
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
 *   The main program and settings data.
 *
 *   This alters main.program.signal_received, setting it to a received signal.
 *
 *   This alters main.setting.state.status:
 *     Errors (with error bit) from: f_signal_open()
 *     Errors (with error bit) from: f_signal_wait()
 *
 * @see f_signal_close()
 * @see f_signal_open()
 * @see f_signal_wait()
 */
#if !defined(_di_iki_read_signal_handler_) && !defined(_di_thread_support_)
  extern void iki_read_signal_handler(iki_read_main_t * const main);
#endif // !defined(_di_iki_read_signal_handler_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_signal_h

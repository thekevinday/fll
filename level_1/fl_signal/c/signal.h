/**
 * FLL - Level 1
 *
 * Project: Signal
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common signal functions.
 */
#ifndef _FL_signal_h
#define _FL_signal_h

// Libc includes.
#include <signal.h>
#include <string.h>
#include <sys/signalfd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/signal.h>

// FLL-1 signal includes.
#include <fll/level_1/signal/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to see if a given signal is received.
 *
 * Provides a simple interrupt checker for general use.
 *
 * This is intended to be explicitly use for the interrupt() callback defined in f_state_t.
 *
 * This check all interrupts provided in state->data.interrupts and if a signal is found, store that signal in state->data.trigger and returns F_interrupt (with error bit set).
 * If state->data.signal.id is NULL, then F_enable_not is returned.
 *
 * @param state
 *   The state such that:
 *   - state->handle:    Ignored.
 *   - state->interrupt: A pointer to this function.
 *   - state->callbacks: Ignored.
 *   - state->custom:    The interrupt data, of the type fl_signal_interrupt_t (Must not be NULL).
 *   - state->data:      Ignored.
 * @param internal
 *   This is ignored.
 *
 * @return
 *   F_none on success.
 *   F_enable_not on success but signals are not requested to be processed.
 *   F_interrupt_not on success and no requested signal was found.
 *
 *   F_interrupt (with error bit) if a requested signal is confirmed to be found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_signal_read()
 */
#ifndef _di_fl_signal_state_interrupt_
  extern f_status_t fl_signal_state_interrupt(void * const state, void * const internal);
#endif // _di_fl_signal_state_interrupt_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_signal_h

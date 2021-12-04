/**
 * FLL - Level 1
 *
 * Project: Signal
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project execute.
 *
 * This is auto-included by execute.h and should not need to be explicitly included.
 */
#ifndef _FL_signal_common_h
#define _FL_signal_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure intended to be used as the "data" structure for f_state_t for interrupt related functionality.
 *
 * interrupts: An array of signal codes to treat as interrupts.
 * signal:     The signal structure to use.
 * trigger:    The signal that triggered the interrupt, if applicable.
 */
#ifndef _di_fl_signal_interrupt_t_
  typedef struct {
    f_int32s_t interrupts;
    f_signal_t signal;
    int32_t    trigger;
  } fl_signal_interrupt_t;

  #define fl_signal_interrupt_t_initialize { f_int32s_t_initialize, f_signal_t_initialize, 0 }

  #define macro_fl_signal_interrupt_t_initialize(interrupts, signal) { interrupts, signal, 0 }

  #define macro_fl_signal_interrupt_t_clear(structure) \
    macro_f_int32s_t_clear(structure.interrupts) \
    macro_f_signal_t_clear(structure.signal) \
    structure.trigger = 0;
#endif // _di_fl_signal_interrupt_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_signal_common_h

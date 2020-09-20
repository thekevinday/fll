/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project signal.
 *
 * This is auto-included by signal.h and should not need to be explicitly included.
 */
#ifndef _F_signal_common_h
#define _F_signal_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds a signal type.
 *
 * flags: The signal flags associated with this.
 * id:    The signal descriptor.
 * set:   The signal set.
 */
#ifndef _di_f_signal_t_
  typedef struct {
    int flags;
    int id;
    sigset_t set;
  } f_signal_t;

  #define f_signal_t_initialize {0, 0, { 0 } }

  #define f_macro_signal_t_initialize(flags, id, set) { flags, id, set }
#endif // _di_f_signal_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_signal_common_h

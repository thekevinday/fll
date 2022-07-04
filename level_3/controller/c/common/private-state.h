/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_state_h
#define _PRIVATE_common_state_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for passing data to the interrupt state function.
 *
 * is_normal: Boolean designating if this is operating in a normal state.
 * thread:    The thread data.
 */
#ifndef _di_controller_state_interrupt_t_
  typedef struct {
    bool is_normal;

    controller_thread_t *thread;
  } controller_state_interrupt_t;

  #define controller_state_interrupt_t_initialize { \
    F_true, \
    0, \
  }

  #define macro_controller_state_interrupt_t_initialize(is_normal, thread) { \
    is_normal, \
    thread, \
  }
#endif // _di_controller_state_interrupt_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_state_h

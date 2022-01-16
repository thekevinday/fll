/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_thread_control_h
#define _PRIVATE_thread_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling control requests and responses.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_control_
  extern void * controller_thread_control(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_control_

/**
 * Thread for handling the control listener.
 *
 * This runs on a separate thread entirely to be interuptable and closable distinctly from the main control thread.
 * This is simple and has nothing that needs to be cleaned up and so immediately exits on cancel.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_control_listen_
  extern void * controller_thread_control_listen(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_control_listen_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_control_h

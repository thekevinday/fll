/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_thread_h
#define _PRIVATE_thread_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for periodically cleanup data when not busy.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_cleanup_
  extern void * controller_thread_cleanup(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_cleanup_

/***
 * Detach a thread, assigning id to NULL on success.
 *
 * If the ID is not found, then it is also set to NULL.
 *
 * This should be called for asynchronous processes.
 *
 * @param id
 *   The thread ID.
 *
 * @return
 *   F_okay on success.
 *
 *   Success from: f_thread_detach().
 *
 *   Errors (with error bit) from: f_thread_detach().
 *
 * @see f_thread_detach()
 */
#ifndef _di_controller_thread_detach_
  extern f_status_t controller_thread_detach(f_thread_id_t * const id) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_detach_

/**
 * Check to see if thread is enabled for the normal operations like entry and control or for exit operations.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param thread
 *   The thread data.
 *
 * @return
 *   TRUE when enabled.
 *   FALSE when disabled.
 */
#ifndef _di_controller_thread_is_enabled_
  extern f_status_t controller_thread_is_enabled(const bool is_normal, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_is_enabled_

/**
 * Check to see if thread is enabled for the normal operations like entry and control or for exit operations for some process.
 *
 * @param process
 *   The process to use when checking if thread is enabled.
 * @param thread
 *   The thread data.
 *
 * @return
 *
 *   Success from controller_thread_is_enabled_process_type().
 *
 * @see controller_thread_is_enabled_process_type()
 */
#ifndef _di_controller_thread_is_enabled_process_
  extern f_status_t controller_thread_is_enabled_process(controller_data_t * const process, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_is_enabled_process_

/**
 * Check to see if thread is enabled for the normal operations like entry and control or for exit operations for some process type.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param thread
 *   The thread data.
 *
 * @return
 *
 *   Success from controller_thread_is_enabled().
 *
 * @see controller_thread_is_enabled()
 */
#ifndef _di_controller_thread_is_enabled_process_type_
  extern f_status_t controller_thread_is_enabled_process_type(const uint8_t type, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_is_enabled_process_type_

/**
 * Start all threads, wait on threads, and handle requests.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The controller settings data.
 *
 * @return
 *   F_okay on success.
 *   F_child on child process exiting.
 *
 *   F_failure (with error bit) on any failure.
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 */
#ifndef _di_controller_thread_main_
  extern f_status_t controller_thread_main(controller_main_t * const main, controller_process_t * const setting) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_main_

/***
 * Join a thread, assigning id to NULL on success.
 *
 * If the ID is not found, then it is also set to NULL.
 *
 * @param id
 *   The thread ID.
 *
 * @return
 *   F_okay on success.
 *
 *   Success from: f_thread_join().
 *
 *   Errors (with error bit) from: f_thread_join().
 *
 * @see f_thread_join()
 */
#ifndef _di_controller_thread_join_
  extern f_status_t controller_thread_join(f_thread_id_t * const id) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_join_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_h

/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_thread_process_h
#define _PRIVATE_thread_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Asynchronously execute a Rule process.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param process
 *   The process data.
 *
 * @see controller_rule_process_do()
 */
#ifndef _di_controller_thread_process_
  extern void controller_thread_process(const bool is_normal, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_process_

/**
 * Cancel all process threads.
 *
 * @param global
 *   The global thread data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param by
 *   Designate the way in which the cancellation should operate.
 *
 *   If controller_thread_cancel_signal_e, then this was called from within the signal handling thread, so do not cancel the signal thread.
 *   If controller_thread_cancel_call_e, then this was not called from within the signal handling thread, so cancel the signal thread.
 *   If controller_thread_cancel_execute_e, then this was called from within the Entry/Exit for executing a process, so cancel the signal thread but not the Entry thread.
 * @param caller
 *   (optional) The process that is calling the cancel so that this process itself does not get cancelled.
 *   Set to NULL to not use.
 */
#ifndef _di_controller_thread_process_cancel_
  extern void controller_thread_process_cancel(const controller_global_t global, const bool is_normal, const uint8_t by, controller_process_t * const caller) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_process_cancel_

/**
 * Process the Exit file, if applicable.
 *
 * @param global
 *   The global thread data.
 */
#ifndef _di_controller_thread_process_exit_
  extern void controller_thread_process_exit(controller_global_t * const global) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_process_exit_

/**
 * Asynchronously execute a Rule process during normal operations.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_process_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_process()
 */
#ifndef _di_controller_thread_process_normal_
  extern void * controller_thread_process_normal(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_process_normal_

/**
 * Asynchronously execute a Rule process during other operations.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_process_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_process()
 */
#ifndef _di_controller_thread_process_other_
  extern void * controller_thread_process_other(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_process_other_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_process_h

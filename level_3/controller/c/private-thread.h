/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 *   Must be of type controller_main_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_cleanup_
  extern void * controller_thread_cleanup(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_cleanup_

/**
 * Thread for handling control requests and responses.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_control_
  extern void * controller_thread_control(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_control_

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
  extern f_status_t controller_thread_is_enabled(const bool is_normal, controller_thread_t *thread) f_attribute_visibility_internal;
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
  extern f_status_t controller_thread_is_enabled_process(controller_process_t * const process, controller_thread_t *thread) f_attribute_visibility_internal;
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
  extern f_status_t controller_thread_is_enabled_process_type(const uint8_t type, controller_thread_t *thread) f_attribute_visibility_internal;
#endif // _di_controller_thread_is_enabled_process_type_

/**
 * Start all threads, wait on threads, and handle requests.
 *
 * @param data
 *   The controller data.
 * @param setting
 *   The controller settings data.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on signal received.
 *
 *   F_failure (with error bit) on any failure.
 */
#ifndef _di_controller_thread_main_
  extern f_status_t controller_thread_main(controller_data_t *data, controller_setting_t *setting) f_attribute_visibility_internal;
#endif // _di_controller_thread_main_

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
  extern void controller_thread_process(const bool is_normal, controller_process_t *process) f_attribute_visibility_internal;
#endif // _di_controller_thread_process_

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
  extern void * controller_thread_process_normal(void *arguments) f_attribute_visibility_internal;
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
  extern void * controller_thread_process_other(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_process_other_

/**
 * Cancel all process threads.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param by
 *   Designate the way in which the cancellation should operate.
 *
 *   If controller_thread_cancel_signal, then this was called from within the signal handling thread, so do not cancel the signal thread.
 *   If controller_thread_cancel_call, then this was not called from within the signal handling thread, so cancel the signal thread.
 *   If controller_thread_cancel_execute, then this was called from within the Entry/Exit for executing a process, so cancel the signal thread but not the Entry thread.
 * @param main
 *   The main thread data.
 * @param caller
 *   (optional) The process that is calling the cancel so that this process itself does not get cancelled.
 *   Set to NULL to not use.
 */
#ifndef _di_controller_thread_process_cancel_
  extern void controller_thread_process_cancel(const bool is_normal, const uint8_t by, controller_main_t *main, controller_process_t *caller) f_attribute_visibility_internal;
#endif // _di_controller_thread_process_cancel_

/**
 * Process the Exit file, if applicable.
 *
 * @param main
 *   The main thread data.
 */
#ifndef _di_controller_thread_process_exit_
  extern void controller_thread_process_exit(controller_main_t *main) f_attribute_visibility_internal;
#endif // _di_controller_thread_process_exit_

/**
 * Thread for handling entry processing.
 *
 * This acts as the main rule thread during entry processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_entry_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_entry_
  extern void * controller_thread_entry(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_entry_

/**
 * Thread for handling exit file processing.
 *
 * This acts as the main rule thread during exit processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * Do not confuse this with exiting a thread, this is the what process the exit files (similar to that of an entry file).
 * Exit files process the "stop" action, whereas the Entry files process the "start" Action
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_entry_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_exit_
  extern void * controller_thread_exit(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_exit_

/***
 * Join a thread, assigning id to NULL on success.
 *
 * If the ID is not found, then it is also set to NULL.
 *
 * @param id
 *   The thread ID.
 *
 * @return
 *   F_none on success.
 *
 *   Success from f_thread_join().
 *
 *   Errors (with error bit) from: f_thread_join().
 *
 * @see f_thread_join()
 */
#ifndef _di_controller_thread_join_
  extern f_status_t controller_thread_join(f_thread_id_t *id) f_attribute_visibility_internal;
#endif // _di_controller_thread_join_

/**
 * Thread for handling rule processing.
 *
 *
 * This acts as the main rule thread after entry processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * @todo the control thread should send commands to this thread, somehow.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_rule_
  extern void * controller_thread_rule(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_rule_

/**
 * Thread for handling signals/interrupts.
 *
 * Currently this only handles signals to exist, but may be updated to handle interrupt and hangup signals.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param main
 *   The main data.
 */
#ifndef _di_controller_thread_signal_
  extern void controller_thread_signal(const bool is_normal, controller_main_t *main) f_attribute_visibility_internal;
#endif // _di_controller_thread_signal_

/**
 * Thread for handling signals/interrupts during normal operations.
 *
 * Currently this only handles signals to exist, but may be updated to handle interrupt and hangup signals.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_signal()
 */
#ifndef _di_controller_thread_signal_normal_
  extern void * controller_thread_signal_normal(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_signal_normal_

/**
 * Thread for handling signals/interrupts during other operations.
 *
 * Currently this only handles signals to exist, but may be updated to handle interrupt and hangup signals.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_thread_signal()
 */
#ifndef _di_controller_thread_signal_other_
  extern void * controller_thread_signal_other(void *arguments) f_attribute_visibility_internal;
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_h

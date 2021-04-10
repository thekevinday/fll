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
  extern void * controller_thread_cleanup(void *arguments) f_gcc_attribute_visibility_internal;
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
  extern void * controller_thread_control(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_control_

/**
 * Start all threads, wait on threads, and handle requests.
 *
 * @param entry_name
 *   The entry name string.
 * @param data
 *   The controller data.
 * @param setting
 *   The controller settings data.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on signal received.
 *   F_failure (with error bit) on any failure.
 */
#ifndef _di_controller_thread_main_
  extern f_status_t controller_thread_main(const f_string_static_t entry_name, controller_data_t *data, controller_setting_t *setting) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_main_

/**
 * Asynchronously execute a Rule process.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_process_t.
 *
 * @return
 *   0, always.
 *
 * @see controller_rule_process_do()
 */
#ifndef _di_controller_thread_process_
  extern void * controller_thread_process(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_process_

/**
 * Cancel all process threads.
 *
 * @param main
 *   The main thread data.
 */
#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(controller_main_t *main) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_process_cancel_

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
  extern void * controller_thread_entry(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_entry_

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
  extern void * controller_thread_rule(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_rule_

/**
 * Thread for handling signals/interrupts.
 *
 * Currently this only handles signals to exist, but may be updated to handle interrupt and hangup signals.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_signal_
  extern void * controller_thread_signal(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_signal_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_h

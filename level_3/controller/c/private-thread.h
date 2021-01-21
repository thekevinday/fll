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
 * Asynchronously execute a process.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_asynchronous_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_asynchronous_
  extern void * controller_thread_asynchronous(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_asynchronous_

/**
 * Cancel all asynchronous threads.
 *
 * @param thread
 *   The thread data.
 */
#ifndef _di_controller_thread_asynchronous_cancel_
  void controller_thread_asynchronous_cancel(controller_thread_t *thread) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_asynchronous_cancel_

/**
 * Thread for periodically clearing cache if cache is not busy.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_thread_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_cache_
  extern void * controller_thread_cache(void *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_cache_

/**
 * Thread for handling control requests and responses.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_thread_t.
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
 * @param cache
 *   The main/global cache to use.
 * @param thread
 *   The thread data.
 *
 * @return
 *   F_none on success.
 *   F_child on child process exiting.
 *   F_signal on signal received.
 *   F_failure (with error bit) on any failure.
 */
#ifndef _di_controller_thread_main_
  extern f_status_t controller_thread_main(const f_string_static_t entry_name, controller_cache_t *cache, controller_thread_t *thread) f_gcc_attribute_visibility_internal;
#endif // _di_controller_thread_main_

/**
 * Thread for handling loading of rules into memory.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_thread_t.
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
 *   Must be of type controller_thread_t.
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

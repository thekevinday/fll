/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_thread_h
#define _PRIVATE_common_thread_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for managing threads.
 *
 * This is essentially data shared globally between threads, about threads.
 *
 * The "enabled" and "signal" utilize the lock: lock.process.
 *
 * enabled:    TRUE when threads are active, FALSE when inactive and the program is essentially shutting down, no new threads should be started when FALSE.
 * signal:     The code of any signal received.
 * status:     A status used by the main entry/rule processing thread for synchronous operations.
 * id_cleanup: The thread ID representing the Cleanup Process.
 * id_control: The thread ID representing the Control Process.
 * id_entry:   The thread ID representing the Entry or Exit Process.
 * id_rule:    The thread ID representing the Rule Process.
 * id_signal:  The thread ID representing the Signal Process.
 * lock:       A r/w lock for operating on this structure.
 * processs:   All Rule Process thread data.
 * cache:      A cache used by the main entry/rule processing thread for synchronous operations.
 */
#ifndef _di_controller_thread_t_
  #define controller_thread_cleanup_interval_long_d     3600      // 1 hour in seconds.
  #define controller_thread_cleanup_interval_short_d    180       // 3 minutes in seconds.
  #define controller_thread_exit_timeout_d              500       // 0.5 seconds in milliseconds.
  #define controller_thread_exit_process_cancel_wait_d  600000000 // 0.6 seconds in nanoseconds.
  #define controller_thread_exit_process_cancel_total_d 150       // 90 seconds in multiples of wait.
  #define controller_thread_simulation_timeout_d        200       // 0.2 seconds in milliseconds.

  #define controller_thread_signal_wait_timeout_seconds_d     70
  #define controller_thread_signal_wait_timeout_nanoseconds_d 0

  #define controller_thread_lock_read_timeout_seconds_d      3
  #define controller_thread_lock_read_timeout_nanoseconds_d  0
  #define controller_thread_lock_write_timeout_seconds_d     3
  #define controller_thread_lock_write_timeout_nanoseconds_d 0

  #define controller_thread_wait_timeout_1_before_d 4
  #define controller_thread_wait_timeout_2_before_d 12
  #define controller_thread_wait_timeout_3_before_d 28

  #define controller_thread_wait_timeout_1_seconds_d     0
  #define controller_thread_wait_timeout_1_nanoseconds_d 20000000  // 0.02 seconds in nanoseconds.
  #define controller_thread_wait_timeout_2_seconds_d     0
  #define controller_thread_wait_timeout_2_nanoseconds_d 200000000 // 0.2 seconds in nanoseconds.
  #define controller_thread_wait_timeout_3_seconds_d     2
  #define controller_thread_wait_timeout_3_nanoseconds_d 0
  #define controller_thread_wait_timeout_4_seconds_d     20
  #define controller_thread_wait_timeout_4_nanoseconds_d 0

  #define controller_thread_exit_ready_timeout_seconds_d     0
  #define controller_thread_exit_ready_timeout_nanoseconds_d 500000000 // 0.5 seconds in nanoseconds.

  /**
   * States for enabled, designating how to stop the process.
   *
   * controller_thread_*:
   *   - enabled_not:          The controller is no longer enabled, shut down and abort all work.
   *   - enabled:              The controller is operating normally.
   *   - enabled_execute:      The controller is executing another process, all running operations must terminate.
   *   - enabled_exit:         The controller is shutting down, only process exit rules.
   *   - enabled_exit_execute: The controller is executing another process while in failsafe mode, all running operations must terminate.
   *   - enabled_exit_ready:   The controller is shutting down, only process exit rules, and now ready to send termination signals.
   *
   * controller_thread_cancel_*:
   *   - signal:       Cancellation is triggered by a signal.
   *   - call:         Cancellation is explicitly called.
   *   - execute:      Cancellation is explicitly called due to an "execute" Item Action, when not during Exit.
   *   - exit:         Cancellation is explicitly called during Exit.
   *   - exit_execute: Cancellation is explicitly called due to an "execute" Item Action during Exit.
   */
  enum {
    controller_thread_enabled_not_e = 0,
    controller_thread_enabled_e,
    controller_thread_enabled_execute_e,
    controller_thread_enabled_exit_e,
    controller_thread_enabled_exit_execute_e,
    controller_thread_enabled_exit_ready_e,
  };

  enum {
    controller_thread_cancel_signal_e = 0,
    controller_thread_cancel_call_e,
    controller_thread_cancel_execute_e,
    controller_thread_cancel_exit_e,
    controller_thread_cancel_exit_execute_e,
  };

  typedef struct {
    uint8_t enabled;
    int signal;
    f_status_t status;

    f_thread_id_t id_cleanup;
    f_thread_id_t id_control;
    f_thread_id_t id_entry;
    f_thread_id_t id_rule;
    f_thread_id_t id_signal;

    controller_lock_t lock;
    controller_processs_t processs;
    controller_cache_t cache;
  } controller_thread_t;

  #define controller_thread_t_initialize { \
    controller_thread_enabled_e, \
    0, \
    F_none, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    controller_lock_t_initialize, \
    controller_processs_t_initialize, \
    controller_cache_t_initialize, \
  }
#endif // _di_controller_thread_t_

/**
 * Fully deallocate all memory for the given setting without caring about return status.
 *
 * @param thread
 *   The thread to deallocate.
 *
 * @see controller_asynchronouss_resize()
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_thread_delete_simple_
  extern void controller_thread_delete_simple(controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_thread_h

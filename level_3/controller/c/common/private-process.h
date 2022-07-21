/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_process_h
#define _PRIVATE_common_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of PIDs.
 *
 * array: An array of rule PIDs.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_pids_t_
  typedef struct {
    pid_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_pids_t;

  #define controller_pids_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_pids_t_

/**
 * A Rule Process.
 *
 * This refers to "process" as in the processing of a single rule for the given Rule ID and does not refer to "process" as in a CPU Process.
 *
 * The "cache" should only be used by the function processing/executing the process and as such should not require a write lock on the "process".
 * There should only be a single thread running any given Rule process at a time, guaranteeing the cache to not need read/write locks.
 *
 * Process States:
 *   - idle:   No process is running for this rule.
 *   - busy:   A process is actively using this, and is running synchronously.
 *   - active: A process is actively using this, and is running asynchronously.
 *   - done:   A process has finished running on this and there is a thread that needs to be cleaned up.
 *
 * Process Types:
 *   - entry:   The process is started from an entry.
 *   - exit:    The process is started from an exit.
 *   - control: The process is started from a control operation.
 *
 * id:           The ID of this process relative to the processes array.
 * id_thread:    The thread id, a valid ID when state is "active", and an invalid ID when the state is "busy".
 * action:       The action being performed.
 * active:       A read/write lock representing that something is currently using this (read locks = in use, write lock = begin deleting).
 * cache:        The cache used in this process.
 * child:        The process id of a child process, if one is running (when forking to execute a child process).
 * lock:         A read/write lock on the structure.
 * options:      Configuration options for this asynchronous thread.
 * result:       The last return code from an execution of a process.
 * rule:         A copy of the rule actively being executed.
 * stack:        A stack used to represent dependencies as Rule ID's to avoid circular rule dependencies (If Rule A waits on Rule B, then Rule B must not wait on Rule A).
 * state:        The state of the process.
 * status:       The last execution status of the process.
 * type:         The currently active process type (from the controller_process_type_*_e).
 * wait:         A thread condition to tell a process waiting process that the rule has is done being processed.
 * wait_lock:    A mutex lock for working with "wait".
 *
 * main_data:    Used for passing the controller_main_t data to the process thread (to populate controller_global_t).
 * main_setting: Used for passing the controller_setting_t data to the process thread (to populate controller_global_t).
 * main_thread:  Used for passing the controller_thread_t data to the process thread (to populate controller_global_t).
 */
#ifndef _di_controller_process_t_
  #define controller_process_option_asynchronous_d 0x1
  #define controller_process_option_require_d      0x2
  #define controller_process_option_simulate_d     0x4
  #define controller_process_option_validate_d     0x8
  #define controller_process_option_wait_d         0x10

  enum {
    controller_process_state_idle_e = 1,
    controller_process_state_busy_e,
    controller_process_state_active_e,
    controller_process_state_done_e,
  };

  enum {
    controller_process_type_entry_e = 1,
    controller_process_type_exit_e,
    controller_process_type_control_e,
  };

  typedef struct {
    f_array_length_t id;

    uint8_t state;
    uint8_t action;
    uint8_t options;
    uint8_t type;

    int result;

    f_thread_id_t id_thread;
    f_thread_lock_t lock;
    f_thread_lock_t active;
    f_thread_condition_t wait;
    f_thread_mutex_t wait_lock;

    controller_cache_t cache;
    f_array_lengths_t stack;

    f_string_dynamics_t path_pids;

    controller_pids_t childs;
    controller_rule_t rule;

    void *main_data;
    void *main_setting;
    void *main_thread;
  } controller_process_t;

  #define controller_process_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_thread_id_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_condition_t_initialize, \
    controller_cache_t_initialize, \
    f_array_lengths_t_initialize, \
    f_string_dynamics_t_initialize, \
    controller_pids_t_initialize, \
    controller_rule_t_initialize, \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_process_t_

/**
 * The Rule Processes.
 *
 * Each process is a pointer of a process, to preserve memory locations that may ultimately change due to the resizing the array.
 *
 * array: An array of rule processes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_processs_t_
  typedef struct {
    controller_process_t **array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_processs_t;

  #define controller_processs_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_processs_t_

/**
 * Increase the size of the pid array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param pids
 *   The pid array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_pids_resize()
 */
#ifndef _di_controller_pids_increase_
  extern f_status_t controller_pids_increase(controller_pids_t * const pids) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the pid array.
 *
 * @param length
 *   The new size to use.
 * @param pids
 *   The pid array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_pids_resize_
  extern f_status_t controller_pids_resize(const f_array_length_t length, controller_pids_t * const pids) F_attribute_visibility_internal_d;
#endif // _di_controller_pids_resize_

/**
 * Fully deallocate all memory for the given process without caring about return status.
 *
 * @param process
 *   The process to deallocate.
 *
 * @see f_string_dynamic_resize()
 * @see f_thread_condition_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_process_delete_simple_
  extern void controller_process_delete_simple(controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_process_delete_simple_

/**
 * Fully deallocate all memory for the given processs without caring about return status.
 *
 * @param processs
 *   The process array to deallocate.
 *
 * @see controller_processs_resize()
 */
#ifndef _di_controller_processs_delete_simple_
  extern void controller_processs_delete_simple(controller_processs_t * const processs) F_attribute_visibility_internal_d;
#endif // _di_controller_processs_delete_simple_

/**
 * Increase the size of the rule array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param processs
 *   The process array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_processs_resize()
 */
#ifndef _di_controller_processs_increase_
  extern f_status_t controller_processs_increase(controller_processs_t * const processs) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the rule array.
 *
 * @param length
 *   The new size to use.
 * @param processs
 *   The process array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_process_delete_simple().
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_thread_condition_create().
 *   Errors (with error bit) from: f_thread_lock_create().
 *
 * @see controller_process_delete_simple()
 * @see f_memory_resize()
 * @see f_thread_condition_create()
 * @see f_thread_lock_create()
 */
#ifndef _di_controller_processs_resize_
  extern f_status_t controller_processs_resize(const f_array_length_t length, controller_processs_t * const processs) F_attribute_visibility_internal_d;
#endif // _di_controller_processs_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_process_h

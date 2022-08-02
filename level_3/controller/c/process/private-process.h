/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_process_h
#define _PRIVATE_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prepare the process.
 *
 * The process is initialized with the process id, the rule alias, and the rule action type.
 * These are the necessary parts for uniquely identifying the process.
 *
 * If a process by the given Rule alias and Rule Action already exists, then nothing is done.
 *
 * This requires that a global.thread->lock.process lock be set on process->lock before being called.
 *
 * @param global
 *   The global data.
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param action
 *   The Rule Action to use.
 * @param alias
 *   The Rule alias to use.
 * @param id
 *   (optional) The process ID when found or created.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_found on success, but nothing was done because an existing process was found.
 *
 *   F_lock (with error bit) if failed to re-establish read lock on global.thread->lock.process while returning.
 *
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *   Errors (with error bit) from: controller_lock_write().
 *
 * @see f_string_dynamic_append()
 * @see controller_lock_read()
 * @see controller_lock_write()
 */
#ifndef _di_controller_process_prepare_
  extern f_status_t controller_process_prepare(const controller_global_t global, const bool is_normal, const uint8_t action, const f_string_static_t alias, f_array_length_t *id) F_attribute_visibility_internal_d;
#endif // _di_controller_process_prepare_

/**
 * Prepare the process for some process type.
 *
 * The process is initialized with the process id, the rule alias, and the rule action type.
 * These are the necessary parts for uniquely identifying the process.
 *
 * If a process by the given Rule alias and Rule Action already exists, then nothing is done.
 *
 * This requires that a global.thread->lock.process lock be set on process->lock before being called.
 *
 * @param global
 *   The global data.
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param action
 *   The Rule Action to use.
 * @param alias
 *   The Rule alias to use.
 * @param id
 *   (optional) The process ID when found or created.
 *   Set to NULL to not use.
 *
 * @return
 *   Success from: controller_process_prepare()
 *
 *   Errors (with error bit) from: controller_process_prepare().
 *
 * @see controller_process_prepare()
 */
#ifndef _di_controller_process_prepare_process_type_
  extern f_status_t controller_process_prepare_process_type(const controller_global_t global, const uint8_t type, const uint8_t action, const f_string_static_t alias, f_array_length_t *id) F_attribute_visibility_internal_d;
#endif // _di_controller_process_prepare_process_type_

/**
 * Find an existing process, for the given Rule Action.
 *
 * Do not confuse this with a process in the context of a PID.
 * This is a stucture for the current processing of some rule.
 *
 * This does not do any locking or unlocking for the processs data, be sure to lock appropriately before and after calling this.
 *
 * @param action
 *   The Rule Action to find.
 * @param alias
 *   The Rule alias to find.
 * @param processs
 *   The array of processes to.
 * @param at
 *   The location within processs the id was found.
 *   (optional) Set to NULL to disable.
 *
 * @return
 *   F_none if not given a valid id to search.
 *   F_false if there is no process found.
 *   F_true if there is a process found (address is stored in "at").
 */
#ifndef _di_controller_process_find_
  f_status_t controller_process_find(const f_array_length_t action, const f_string_static_t alias, const controller_processs_t processs, f_array_length_t *at) F_attribute_visibility_internal_d;
#endif // _di_controller_process_find_

/***
 * Safely wait for a process, periodically checking to see if process completed or check if exiting.
 *
 * @param global
 *   The global data.
 * @param process
 *   The process to wait on.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Success from: f_thread_condition_wait_timed().
 *
 *   Errors (with error bit) from: f_thread_condition_wait_timed().
 *
 * @see f_thread_condition_wait_timed()
 */
#ifndef _di_controller_process_wait_
  extern f_status_t controller_process_wait(const controller_global_t global, controller_process_t * const process) F_attribute_visibility_internal_d;
#endif // _di_controller_process_wait_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_process_h

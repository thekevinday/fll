/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_lock_h
#define _PRIVATE_lock_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the initial, required, allocation for the lock.
 *
 * @param lock
 *   The lock to allocate.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_thread_lock_delete().
 *   Errors (with error bit) from: f_thread_mutex_delete().
 *
 * @see f_thread_lock_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_lock_create_
  extern f_status_t controller_lock_create(controller_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_create_

/**
 * Wait to get a read lock.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 * @return
 *   F_okay on success.
 *
 *   F_interrupt (with error bit set) on (exit) signal received, lock will not be set when this is returned.
 *
 *   Status from: f_thread_lock_read_timed().
 *
 *   Errors (with error bit) from: f_thread_lock_read_timed().
 *
 * @see f_thread_lock_read_timed()
 */
#ifndef _di_controller_lock_read_
  extern f_status_t controller_lock_read(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_read_

/**
 * Wait to get a read lock for some process.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param process
 *   The process to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 * @return
 *
 *   Status from: controller_lock_read().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *
 * @see controller_lock_read()
 */
#ifndef _di_controller_lock_read_process_
  extern f_status_t controller_lock_read_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_read_process_

/**
 * Wait to get a read lock for some process type.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 * @return
 *
 *   Status from: controller_lock_read().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *
 * @see controller_lock_read()
 */
#ifndef _di_controller_lock_read_process_type_
  extern f_status_t controller_lock_read_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_read_process_type_

/**
 * Wait to get a write lock.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 * @return
 *   F_okay on success.
 *
 *   F_interrupt (with error bit set) on (exit) signal received, lock will not be set when this is returned.
 *
 *   Status from: f_thread_lock_write_timed().
 *
 *   Errors (with error bit) from: f_thread_lock_write_timed().
 *
 * @see f_thread_lock_write_timed()
 */
#ifndef _di_controller_lock_write_
  extern f_status_t controller_lock_write(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_write_

/**
 * Wait to get a write lock for some process.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param process
 *   The process to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 * @return
 *
 *   Status from: controller_lock_write_process_type().
 *
 *   Errors (with error bit) from: controller_lock_write_process_type().
 *
 * @see controller_lock_write_process_type()
 */
#ifndef _di_controller_lock_write_process_
  extern f_status_t controller_lock_write_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_write_process_

/**
 * Wait to get a write lock for some process type.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 * @return
 *
 *   Status from: controller_lock_write().
 *
 *   Errors (with error bit) from: controller_lock_write().
 *
 * @see controller_lock_write()
 */
#ifndef _di_controller_lock_write_process_type_
  extern f_status_t controller_lock_write_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_write_process_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_lock_h

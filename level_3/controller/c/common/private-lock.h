/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_lock_h
#define _PRIVATE_common_lock_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for sharing mutexes globally between different threads.
 *
 * The alert lock is intended for a generic waiting on alerts operations.
 * The print lock is intended to lock any activity printing to stdout/stderr.
 * The process lock is intended to lock any activity on the processs structure.
 * The rule lock is intended to lock any activity on the rules structure.
 *
 * alert:           The alert mutex lock for waking up on alerts.
 * print:           The print mutex lock.
 * process:         The process r/w lock.
 * rule:            The rule r/w lock.
 * alert_condition: The condition used to trigger alerts.
 */
#ifndef _di_controller_lock_t_
  typedef struct {
    f_thread_mutex_t alert;
    f_thread_mutex_t print;

    f_thread_lock_t process;
    f_thread_lock_t rule;

    f_thread_condition_t alert_condition;
  } controller_lock_t;

  #define controller_lock_t_initialize { \
    f_thread_mutex_t_initialize, \
    f_thread_mutex_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_condition_t_initialize, \
  }
#endif // _di_controller_lock_t_

/**
 * Delete the mutex lock and if the mutex lock is busy, forcibly unlock it and then delete it.
 *
 * @param mutex
 *   The mutex lock to delete.
 *   Will be set to NULL if delete succeeded.
 */
#ifndef _di_controller_lock_delete_mutex_
  extern void controller_lock_delete_mutex(f_thread_mutex_t *mutex) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_delete_mutex_

/**
 * Delete the r/w lock and if the r/w lock is busy, forcibly unlock it and then delete it.
 *
 * @param lock
 *   The r/w lock to delete.
 *   Will be set to NULL if delete succeeded.
 */
#ifndef _di_controller_lock_delete_rw_
  extern void controller_lock_delete_rw(f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_delete_rw_

/**
 * Fully deallocate all memory for the given lock without caring about return status.
 *
 * @param lock
 *   The lock to deallocate.
 *
 * @see f_thread_lock_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_lock_delete_simple_
  extern void controller_lock_delete_simple(controller_lock_t * const lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_lock_h

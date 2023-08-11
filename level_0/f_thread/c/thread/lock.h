/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by POSIX thread related functionality.
 *
 * This is auto-included by thread.h and should not need to be explicitly included.
 */
#ifndef _F_thread_lock_h
#define _F_thread_lock_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A typedef representing pthread_rwlock_t (read/write lock).
 *
 * This must be dynamically initialized using f_thread_lock_create().
 * In some cases, they can be utilized statically, in which case only f_thread_lock_t_initialize is needed.
 */
#ifndef _di_f_thread_lock_t_
  typedef pthread_rwlock_t f_thread_lock_t;

  #define f_thread_lock_t_initialize PTHREAD_RWLOCK_INITIALIZER

  #define macro_f_thread_lock_t_initialize_1(lock) lock
#endif // _di_f_thread_lock_t_

/**
 * An array of thread locks.
 *
 * Properties:
 *   - array: The array of f_thread_lock_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_locks_t_
  typedef struct {
    f_thread_lock_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_thread_locks_t;

  #define f_thread_locks_t_initialize { 0, 0, 0 }

  #define macro_f_thread_locks_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_thread_locks_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_thread_locks_t_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_thread_lockss_t structure.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_thread_locks_adjust_callback_
  extern f_status_t f_thread_locks_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_thread_locks_adjust_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_thread_lockss_t structure.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_thread_locks_resize_callback_
  extern f_status_t f_thread_locks_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_thread_locks_resize_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_lock_h

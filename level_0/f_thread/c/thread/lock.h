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

  #define macro_f_thread_lock_t_delete_simple(lock) f_thread_lock_delete(&lock);
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

  #define macro_f_thread_locks_t_adjust(status, locks, length) status = f_memory_array_adjust(length, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)
  #define macro_f_thread_locks_t_resize(status, locks, length) status = f_memory_array_resize(length, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)

  #define macro_f_thread_locks_t_delete_simple(locks)  f_memory_array_resize(0, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)
  #define macro_f_thread_locks_t_destroy_simple(locks) f_memory_array_adjust(0, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)

  #define macro_f_thread_locks_t_increase(status, step, locks)      status = f_memory_array_increase(step, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)
  #define macro_f_thread_locks_t_increase_by(status, locks, amount) status = f_memory_array_increase_by(amount, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)
  #define macro_f_thread_locks_t_decrease_by(status, locks, amount) status = f_memory_array_decrease_by(amount, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)
  #define macro_f_thread_locks_t_decimate_by(status, locks, amount) status = f_memory_array_decimate_by(amount, sizeof(f_thread_lock_t), (void **) & locks.array, locks.used, locks.size)
#endif // _di_f_thread_locks_t_

/**
 * Resize the thread locks array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The thread locks array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_adjust_
  extern f_status_t f_thread_locks_adjust(const f_number_unsigned_t length, f_thread_locks_t * const structure);
#endif // _di_f_thread_locks_adjust_

/**
 * Resize the thread locks array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The thread locks array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_decimate_by_
  extern f_status_t f_thread_locks_decimate_by(const f_number_unsigned_t amount, f_thread_locks_t * const structure);
#endif // _di_f_thread_locks_decimate_by_

/**
 * Resize the thread locks array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The thread locks array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_decrease_by_
  extern f_status_t f_thread_locks_decrease_by(const f_number_unsigned_t amount, f_thread_locks_t * const structure);
#endif // _di_f_thread_locks_decrease_by_

/**
 * Increase the size of the thread locks array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The thread locks array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_increase_
  extern f_status_t f_thread_locks_increase(const f_number_unsigned_t step, f_thread_locks_t * const structure);
#endif // _di_f_thread_locks_increase_

/**
 * Resize the thread locks array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The thread locks array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_increase_by_
  extern f_status_t f_thread_locks_increase_by(const f_number_unsigned_t amount, f_thread_locks_t * const structure);
#endif // _di_f_thread_locks_increase_by_

/**
 * Resize the thread locks array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The thread locks array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_resize_
  extern f_status_t f_thread_locks_resize(const f_number_unsigned_t length, f_thread_locks_t * const structure);
#endif // _di_f_thread_locks_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_lock_h

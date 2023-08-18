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
#ifndef _F_thread_barrier_h
#define _F_thread_barrier_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A typedef representing pthread_barrier_t.
 */
#ifndef _di_f_thread_barrier_t_
  typedef pthread_barrier_t f_thread_barrier_t;

  #define f_thread_barrier_t_initialize { 0 }

  #define macro_f_thread_barrier_t_initialize_1(barrier) barrier

  #define macro_f_thread_barrier_t_clear(barrier) barrier = 0;
#endif // _di_f_thread_barrier_t_

/**
 * An array of f_thread_barrier_t.
 *
 * Properties:
 *   - array: The array of f_thread_barrier_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_barriers_t_
  typedef struct {
    f_thread_barrier_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_thread_barriers_t;

  #define f_thread_barriers_t_initialize { 0, 0, 0 }

  #define macro_f_thread_barriers_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_thread_barriers_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_thread_barriers_t_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_thread_barriers_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_thread_barriers_delete_callback_
  extern f_status_t f_thread_barriers_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_thread_barriers_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_thread_barriers_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_thread_barriers_destroy_callback_
  extern f_status_t f_thread_barriers_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_thread_barriers_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_thread_barrierss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_thread_barrierss_delete_callback_
  extern f_status_t f_thread_barrierss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_thread_barrierss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_thread_barrierss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_thread_barrierss_destroy_callback_
  extern f_status_t f_thread_barrierss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_thread_barrierss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_barrier_h

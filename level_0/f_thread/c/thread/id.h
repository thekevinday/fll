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
#ifndef _F_thread_id_h
#define _F_thread_id_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A typedef representing pthread_t.
 */
#ifndef _di_f_thread_id_t_
  typedef pthread_t f_thread_id_t;

  #define f_thread_id_t_initialize 0

  #define macro_f_thread_id_t_clear(id) id = 0;
#endif // _di_f_thread_id_t_

/**
 * An array of thread IDs.
 *
 * array: The array of f_thread_id_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_ids_t_
  typedef struct {
    f_thread_id_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_ids_t;

  #define f_thread_ids_t_initialize { 0, 0, 0 }

  #define macro_f_thread_ids_t_initialize(array, size, used) { array, size, used }
  #define macro_f_thread_ids_t_initialize2(array, length) { array, length, length }

  #define macro_f_thread_ids_t_clear(attributes) macro_f_memory_structure_clear(attributes)

  #define macro_f_thread_ids_t_resize(status, attributes, length) status = f_thread_ids_resize(length, &attributes);
  #define macro_f_thread_ids_t_adjust(status, attributes, length) status = f_thread_ids_adjust(length, &attributes);

  #define macro_f_thread_ids_t_delete_simple(attributes)  f_thread_ids_resize(0, &ids);
  #define macro_f_thread_ids_t_destroy_simple(attributes) f_thread_ids_adjust(0, &ids);

  #define macro_f_thread_ids_t_increase(status, step, attributes)      status = f_thread_ids_increase(step, attributes);
  #define macro_f_thread_ids_t_increase_by(status, attributes, amount) status = f_thread_ids_increase_by(amount, attributes);
  #define macro_f_thread_ids_t_decrease_by(status, attributes, amount) status = f_thread_ids_decrease_by(amount, attributes);
  #define macro_f_thread_ids_t_decimate_by(status, attributes, amount) status = f_thread_ids_decimate_by(amount, attributes);
#endif // _di_f_thread_ids_t_

/**
 * Resize the thread ids array.
 *
 * @param length
 *   The new size to use.
 * @param ids
 *   The thread ids array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_ids_adjust_
  extern f_status_t f_thread_ids_adjust(const f_array_length_t length, f_thread_ids_t * const ids);
#endif // _di_f_thread_ids_adjust_

/**
 * Resize the thread ids array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param ids
 *   The thread ids array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_ids_decimate_by_
  extern f_status_t f_thread_ids_decimate_by(const f_array_length_t amount, f_thread_ids_t * const ids);
#endif // _di_f_thread_ids_decimate_by_

/**
 * Resize the thread ids array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param ids
 *   The thread ids array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_ids_decrease_by_
  extern f_status_t f_thread_ids_decrease_by(const f_array_length_t amount, f_thread_ids_t * const ids);
#endif // _di_f_thread_ids_decrease_by_

/**
 * Increase the size of the thread ids array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param ids
 *   The thread ids array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_ids_increase_
  extern f_status_t f_thread_ids_increase(const f_array_length_t step, f_thread_ids_t * const ids);
#endif // _di_f_thread_ids_increase_

/**
 * Resize the thread ids array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param ids
 *   The thread ids array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_ids_increase_by_
  extern f_status_t f_thread_ids_increase_by(const f_array_length_t amount, f_thread_ids_t * const ids);
#endif // _di_f_thread_ids_increase_by_

/**
 * Resize the thread ids array.
 *
 * @param length
 *   The new size to use.
 * @param ids
 *   The thread ids array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_ids_resize_
  extern f_status_t f_thread_ids_resize(const f_array_length_t length, f_thread_ids_t * const ids);
#endif // _di_f_thread_ids_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_id_h

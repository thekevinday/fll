/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by POSIX thread related functionality.
 *
 * This is auto-included by thread.h and should not need to be explicitly included.
 */
#ifndef _F_thread_set_h
#define _F_thread_set_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure containing basic thread information.
 *
 * attribute: The thread attributes (which is a union).
 * id:        The thread identifier.
 * result:    The result of the thread on exit.
 */
#ifndef _di_f_thread_set_t_
  typedef struct {
    f_thread_attribute_t attribute;
    f_thread_id_t id;
    int result;
  } f_thread_set_t;

  #define f_thread_set_t_initialize { f_thread_attribute_t_initialize, f_thread_id_t_initialize, 0 }

  #define macro_f_thread_set_t_initialize(attribute, id, result) { attribute, id, result }

  #define macro_f_thread_set_t_clear(thread) \
    macro_f_thread_attribute_t_clear(thread.attribute) \
    macro_f_thread_id_t_clear(thread.id) \
    result = 0;

  #define macro_f_thread_set_t_delete_simple(set) macro_f_thread_attribute_t_delete_simple(set.attribute)
#endif // _di_f_thread_set_t_

/**
 * An array of f_thread_set_t.
 *
 * array: The array of f_thread_set_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_sets_t_
  typedef struct {
    f_thread_set_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_sets_t;

  #define f_thread_sets_t_initialize { 0, 0, 0 }

  #define macro_f_thread_sets_t_initialize(array, size, used) { array, size, used }
  #define macro_f_thread_sets_t_initialize2(array, length) { array, length, length }

  #define macro_f_thread_sets_t_clear(sets) macro_f_memory_structure_clear(sets)

  #define macro_f_thread_sets_t_resize(status, sets, length) status = f_thread_sets_resize(length, &sets);
  #define macro_f_thread_sets_t_adjust(status, sets, length) status = f_thread_sets_adjust(length, &sets);

  #define macro_f_thread_sets_t_delete_simple(sets)  f_thread_sets_resize(0, &sets);
  #define macro_f_thread_sets_t_destroy_simple(sets) f_thread_sets_adjust(0, &sets);

  #define macro_f_thread_sets_t_increase(status, step, sets)      status = f_thread_sets_increase(step, sets);
  #define macro_f_thread_sets_t_increase_by(status, sets, amount) status = f_thread_sets_increase_by(amount, sets);
  #define macro_f_thread_sets_t_decrease_by(status, sets, amount) status = f_thread_sets_decrease_by(amount, sets);
  #define macro_f_thread_sets_t_decimate_by(status, sets, amount) status = f_thread_sets_decimate_by(amount, sets);
#endif // _di_f_thread_sets_t_

/**
 * Resize the thread sets array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_adjust_
  extern f_status_t f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t * const sets);
#endif // _di_f_thread_sets_adjust_

/**
 * Resize the thread sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_decimate_by_
  extern f_status_t f_thread_sets_decimate_by(const f_array_length_t amount, f_thread_sets_t * const sets);
#endif // _di_f_thread_sets_decimate_by_

/**
 * Resize the thread sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_decrease_by_
  extern f_status_t f_thread_sets_decrease_by(const f_array_length_t amount, f_thread_sets_t * const sets);
#endif // _di_f_thread_sets_decrease_by_

/**
 * Increase the size of the thread sets array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_increase_
  extern f_status_t f_thread_sets_increase(const f_array_length_t step, f_thread_sets_t * const sets);
#endif // _di_f_thread_sets_increase_

/**
 * Resize the thread sets array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_increase_by_
  extern f_status_t f_thread_sets_increase_by(const f_array_length_t amount, f_thread_sets_t * const sets);
#endif // _di_f_thread_sets_increase_by_

/**
 * Resize the thread sets array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The string sets array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_resize_
  extern f_status_t f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t * const sets);
#endif // _di_f_thread_sets_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_set_h

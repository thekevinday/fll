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
#ifndef _F_thread_mutex_attribute_h
#define _F_thread_mutex_attribute_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A typedef representing pthread_mutex_attribute_t.
 */
#ifndef _di_f_thread_mutex_attribute_t_
  typedef pthread_mutexattr_t f_thread_mutex_attribute_t;

  #define f_thread_mutex_attribute_t_initialize { 0 }

  #define macro_f_thread_mutex_attribute_t_initialize_1(attribute) attribute

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define macro_f_thread_mutex_attribute_t_clear(attribute) attribute.__align = 0;

  #define macro_f_thread_mutex_attribute_t_delete_simple(attribute) f_thread_mutex_attribute_delete(&attribute);
#endif // _di_f_thread_mutex_attribute_t_

/**
 * An array of thread mutex_attributees.
 *
 * Properties:
 *   - array: The array of f_thread_mutex_attribute_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_mutex_attributes_t_
  typedef struct {
    f_thread_mutex_attribute_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_thread_mutex_attributes_t;

  #define f_thread_mutex_attributes_t_initialize { 0, 0, 0 }

  #define macro_f_thread_mutex_attributes_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_thread_mutex_attributes_t_initialize_2(array, length) { array, length, length }

  #define macro_f_thread_mutex_attributes_t_clear(attributes) macro_f_memory_structure_clear(attributes)

  #define macro_f_thread_mutex_attributes_t_resize(status, attributes, length) status = f_thread_mutex_attributes_resize(length, &attributes);
  #define macro_f_thread_mutex_attributes_t_adjust(status, attributes, length) status = f_thread_mutex_attributes_adjust(length, &attributes);

  #define macro_f_thread_mutex_attributes_t_delete_simple(attributes)  f_thread_mutex_attributes_resize(0, &attributes);
  #define macro_f_thread_mutex_attributes_t_destroy_simple(attributes) f_thread_mutex_attributes_adjust(0, &attributes);

  #define macro_f_thread_mutex_attributes_t_increase(status, step, attributes)      status = f_thread_mutex_attributes_increase(step, attributes);
  #define macro_f_thread_mutex_attributes_t_increase_by(status, attributes, amount) status = f_thread_mutex_attributes_increase_by(amount, attributes);
  #define macro_f_thread_mutex_attributes_t_decrease_by(status, attributes, amount) status = f_thread_mutex_attributes_decrease_by(amount, attributes);
  #define macro_f_thread_mutex_attributes_t_decimate_by(status, attributes, amount) status = f_thread_mutex_attributes_decimate_by(amount, attributes);
#endif // _di_f_thread_mutex_attributes_t_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The thread mutex attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_adjust_
  extern f_status_t f_thread_mutex_attributes_adjust(const f_number_unsigned_t length, f_thread_mutex_attributes_t * const attributes);
#endif // _di_f_thread_mutex_attributes_adjust_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param attributes
 *   The thread mutex attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_decimate_by_
  extern f_status_t f_thread_mutex_attributes_decimate_by(const f_number_unsigned_t amount, f_thread_mutex_attributes_t * const attributes);
#endif // _di_f_thread_mutex_attributes_decimate_by_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param attributes
 *   The thread mutex attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_decrease_by_
  extern f_status_t f_thread_mutex_attributes_decrease_by(const f_number_unsigned_t amount, f_thread_mutex_attributes_t * const attributes);
#endif // _di_f_thread_mutex_attributes_decrease_by_

/**
 * Increase the size of the thread attributes array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param attributes
 *   The thread mutex attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_increase_
  extern f_status_t f_thread_mutex_attributes_increase(const f_number_unsigned_t step, f_thread_mutex_attributes_t * const attributes);
#endif // _di_f_thread_mutex_attributes_increase_

/**
 * Resize the thread attributes array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param attributes
 *   The thread mutex attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_increase_by_
  extern f_status_t f_thread_mutex_attributes_increase_by(const f_number_unsigned_t amount, f_thread_mutex_attributes_t * const attributes);
#endif // _di_f_thread_mutex_attributes_increase_by_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The thread mutex attributes array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_resize_
  extern f_status_t f_thread_mutex_attributes_resize(const f_number_unsigned_t length, f_thread_mutex_attributes_t * const attributes);
#endif // _di_f_thread_mutex_attributes_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_mutex_attribute_h

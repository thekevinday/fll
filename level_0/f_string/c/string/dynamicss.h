/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines dynamic string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_dynamicss_h
#define _F_string_dynamicss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of dynamic string arrays.
 *
 * array: The array of dynamic dynamicss.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamicss_t_
  typedef f_string_staticss_t f_string_dynamicss_t;

  #define f_string_dynamicss_t_initialize f_string_staticss_t_initialize

  #define macro_f_string_dynamicss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_dynamicss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_dynamicss_t_clear(dynamicss) macro_f_string_staticss_t_clear(dynamicss)

  #define macro_f_string_dynamicss_t_resize(status, dynamicss, length) status = f_string_dynamicss_resize(length, &dynamicss);
  #define macro_f_string_dynamicss_t_adjust(status, dynamicss, length) status = f_string_dynamicss_adjust(length, &dynamicss);

  #define macro_f_string_dynamicss_t_delete_simple(dynamicss)  f_string_dynamicss_resize(0, &dynamicss);
  #define macro_f_string_dynamicss_t_destroy_simple(dynamicss) f_string_dynamicss_adjust(0, &dynamicss);

  #define macro_f_string_dynamicss_t_increase(status, step, dynamicss)      status = f_string_dynamicss_increase(step, &dynamicss);
  #define macro_f_string_dynamicss_t_increase_by(status, dynamicss, amount) status = f_string_dynamicss_increase_by(amount, &dynamicss);
  #define macro_f_string_dynamicss_t_decrease_by(status, dynamicss, amount) status = f_string_dynamicss_decrease_by(amount, &dynamicss);
  #define macro_f_string_dynamicss_t_decimate_by(status, dynamicss, amount) status = f_string_dynamicss_decimate_by(amount, &dynamicss);
#endif // _di_f_string_dynamicss_t_

/**
 * Resize the dynamics string array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The array to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_string_dynamicss_adjust_
  extern f_status_t f_string_dynamicss_adjust(const f_number_unsigned_t length, f_string_dynamicss_t * const structure);
#endif // _di_f_string_dynamicss_adjust_

/**
 * Append the single source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_append_
  extern f_status_t f_string_dynamicss_append(const f_string_dynamics_t source, f_string_dynamicss_t * const destination);
#endif // _di_f_string_dynamicss_append_

/**
 * Append the source strings onto the destination.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_append_all_
  extern f_status_t f_string_dynamicss_append_all(const f_string_dynamicss_t source, f_string_dynamicss_t * const destination);
#endif // _di_f_string_dynamicss_append_all_

/**
 * Resize the dynamics string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_decimate_by_
  extern f_status_t f_string_dynamicss_decimate_by(const f_number_unsigned_t amount, f_string_dynamicss_t * const structure);
#endif // _di_f_string_dynamicss_decimate_by_

/**
 * Resize the dynamics string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_decrease_by_
  extern f_status_t f_string_dynamicss_decrease_by(const f_number_unsigned_t amount, f_string_dynamicss_t * const structure);
#endif // _di_f_string_dynamicss_decrease_by_

/**
 * Increase the size of the dynamics string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_increase_
  extern f_status_t f_string_dynamicss_increase(const f_number_unsigned_t step, f_string_dynamicss_t * const structure);
#endif // _di_f_string_dynamicss_increase_

/**
 * Resize the dynamics string array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_increase_by_
  extern f_status_t f_string_dynamicss_increase_by(const f_number_unsigned_t amount, f_string_dynamicss_t * const structure);
#endif // _di_f_string_dynamicss_increase_by_

/**
 * Resize the dynamics string array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The array to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_resize_
  extern f_status_t f_string_dynamicss_resize(const f_number_unsigned_t length, f_string_dynamicss_t * const structure);
#endif // _di_f_string_dynamicss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamicss_h

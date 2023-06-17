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
#ifndef _F_string_dynamics_h
#define _F_string_dynamics_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of dynamic strings.
 *
 * array: The array of dynamic dynamics.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_t_
  typedef f_string_statics_t f_string_dynamics_t;

  #define f_string_dynamics_t_initialize f_string_statics_t_initialize

  #define macro_f_string_dynamics_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_dynamics_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_dynamics_t_clear(dynamics) macro_f_string_statics_t_clear(dynamics)

  #define macro_f_string_dynamics_t_resize(status, dynamics, length) status = f_string_dynamics_resize(length, &dynamics);
  #define macro_f_string_dynamics_t_adjust(status, dynamics, length) status = f_string_dynamics_adjust(length, &dynamics);

  #define macro_f_string_dynamics_t_delete_simple(dynamics)  f_string_dynamics_resize(0, &dynamics);
  #define macro_f_string_dynamics_t_destroy_simple(dynamics) f_string_dynamics_adjust(0, &dynamics);

  #define macro_f_string_dynamics_t_increase(status, step, dynamics)      status = f_string_dynamics_increase(step, &dynamics);
  #define macro_f_string_dynamics_t_increase_by(status, dynamics, amount) status = f_string_dynamics_increase_by(amount, &dynamics);
  #define macro_f_string_dynamics_t_decrease_by(status, dynamics, amount) status = f_string_dynamics_decrease_by(amount, &dynamics);
  #define macro_f_string_dynamics_t_decimate_by(status, dynamics, amount) status = f_string_dynamics_decimate_by(amount, &dynamics);
#endif // _di_f_string_dynamics_t_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_string_dynamics_adjust_
  extern f_status_t f_string_dynamics_adjust(const f_number_unsigned_t length, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_adjust_

/**
 * Append the single source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_append_
  extern f_status_t f_string_dynamics_append(const f_string_dynamic_t source, f_string_dynamics_t * const destination);
#endif // _di_f_string_dynamics_append_

/**
 * Append the source strings onto the destination.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_append_all_
  extern f_status_t f_string_dynamics_append_all(const f_string_dynamics_t source, f_string_dynamics_t * const destination);
#endif // _di_f_string_dynamics_append_all_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_decimate_by_
  extern f_status_t f_string_dynamics_decimate_by(const f_number_unsigned_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_decimate_by_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_decrease_by_
  extern f_status_t f_string_dynamics_decrease_by(const f_number_unsigned_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_decrease_by_

/**
 * Increase the size of the dynamic string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_increase_
  extern f_status_t f_string_dynamics_increase(const f_number_unsigned_t step, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_increase_

/**
 * Resize the dynamic string array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_increase_by_
  extern f_status_t f_string_dynamics_increase_by(const f_number_unsigned_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_increase_by_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_resize_
  extern f_status_t f_string_dynamics_resize(const f_number_unsigned_t length, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamics_h

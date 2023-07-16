/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines range string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_rangess_h
#define _F_string_rangess_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds an array of f_string_ranges_t.
 *
 * Properties:
 *   - array: The array of ranges arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_rangess_t_
  typedef struct {
    f_string_ranges_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_string_rangess_t;

  #define f_string_rangess_t_initialize { 0, 0, 0 }

  #define macro_f_string_rangess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_rangess_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_rangess_t_clear(rangess) macro_f_memory_structures_clear(rangess)

  #define macro_f_string_rangess_t_resize(status, rangess, length) status = f_string_rangess_resize(length, &rangess);
  #define macro_f_string_rangess_t_adjust(status, rangess, length) status = f_string_rangess_adjust(length, &rangess);

  #define macro_f_string_rangess_t_delete_simple(rangess)  f_string_rangess_resize(0, &rangess);
  #define macro_f_string_rangess_t_destroy_simple(rangess) f_string_rangess_adjust(0, &rangess);

  #define macro_f_string_rangess_t_increase(status, step, rangess)      status = f_string_rangess_increase(step, &rangess);
  #define macro_f_string_rangess_t_increase_by(status, rangess, amount) status = f_string_rangess_increase_by(amount, &rangess);
  #define macro_f_string_rangess_t_decrease_by(status, rangess, amount) status = f_string_rangess_decrease_by(amount, &rangess);
  #define macro_f_string_rangess_t_decimate_by(status, rangess, amount) status = f_string_rangess_decimate_by(amount, &rangess);
#endif // _di_f_string_rangess_t_

/**
 * Resize the string rangess array.
 *
 * @param length
 *   The new size to use.
 * @param rangess
 *   The string rangess array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_rangess_adjust_
  extern f_status_t f_string_rangess_adjust(const f_number_unsigned_t length, f_string_rangess_t * const rangess);
#endif // _di_f_string_rangess_adjust_

/**
 * Append the single source ranges onto the destination.
 *
 * @param source
 *   The source ranges to append.
 * @param destination
 *   The destination rangess the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_rangess_append_
  extern f_status_t f_string_rangess_append(const f_string_ranges_t source, f_string_rangess_t * const destination);
#endif // _di_f_string_rangess_append_

/**
 * Append the source rangess onto the destination.
 *
 * @param source
 *   The source rangess to append.
 * @param destination
 *   The destination rangess the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_rangess_append_all_
  extern f_status_t f_string_rangess_append_all(const f_string_rangess_t source, f_string_rangess_t * const destination);
#endif // _di_f_string_rangess_append_all_

/**
 * Resize the string rangess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param rangess
 *   The string rangess array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_rangess_decimate_by_
  extern f_status_t f_string_rangess_decimate_by(const f_number_unsigned_t amount, f_string_rangess_t * const rangess);
#endif // _di_f_string_rangess_decimate_by_

/**
 * Resize the string rangess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param rangess
 *   The string rangess array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_rangess_decrease_by_
  extern f_status_t f_string_rangess_decrease_by(const f_number_unsigned_t amount, f_string_rangess_t * const rangess);
#endif // _di_f_string_rangess_decrease_by_

/**
 * Increase the size of the string rangess array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param rangess
 *   The string rangess array to resize.
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
#ifndef _di_f_string_rangess_increase_
  extern f_status_t f_string_rangess_increase(const f_number_unsigned_t step, f_string_rangess_t * const rangess);
#endif // _di_f_string_rangess_increase_

/**
 * Resize the string rangess array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param rangess
 *   The string rangess array to resize.
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
#ifndef _di_f_string_rangess_increase_by_
  extern f_status_t f_string_rangess_increase_by(const f_number_unsigned_t amount, f_string_rangess_t * const rangess);
#endif // _di_f_string_rangess_increase_by_

/**
 * Resize the string rangess array.
 *
 * @param length
 *   The new size to use.
 * @param rangess
 *   The string rangess array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_rangess_resize_
  extern f_status_t f_string_rangess_resize(const f_number_unsigned_t length, f_string_rangess_t * const rangess);
#endif // _di_f_string_rangess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_rangess_h

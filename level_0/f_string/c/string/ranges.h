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
#ifndef _F_string_ranges_h
#define _F_string_ranges_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of string ranges.
 *
 * array: the array of string ranges.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_ranges_t_
  typedef struct {
    f_string_range_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_string_ranges_t;

  #define f_string_ranges_t_initialize { 0, 0, 0 }

  #define macro_f_string_ranges_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_ranges_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_ranges_t_clear(ranges) macro_f_memory_structure_clear(ranges)

  #define macro_f_string_ranges_t_resize(status, ranges, length) status = f_string_ranges_resize(length, &ranges);
  #define macro_f_string_ranges_t_adjust(status, ranges, length) status = f_string_ranges_adjust(length, &ranges);

  #define macro_f_string_ranges_t_delete_simple(ranges)  f_string_ranges_resize(0, &ranges);
  #define macro_f_string_ranges_t_destroy_simple(ranges) f_string_ranges_adjust(0, &ranges);

  #define macro_f_string_ranges_t_increase(status, step, ranges)      status = f_string_ranges_increase(step, &ranges);
  #define macro_f_string_ranges_t_increase_by(status, ranges, amount) status = f_string_ranges_increase_by(amount, &ranges);
  #define macro_f_string_ranges_t_decrease_by(status, ranges, amount) status = f_string_ranges_decrease_by(amount, &ranges);
  #define macro_f_string_ranges_t_decimate_by(status, ranges, amount) status = f_string_ranges_decimate_by(amount, &ranges);
#endif // _di_f_string_ranges_t_

/**
 * Resize the string ranges array.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_adjust_
  extern f_status_t f_string_ranges_adjust(const f_number_unsigned_t length, f_string_ranges_t * const ranges);
#endif // _di_f_string_ranges_adjust_

/**
 * Append the single source range onto the destination.
 *
 * @param source
 *   The source range to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_append_
  extern f_status_t f_string_ranges_append(const f_string_range_t source, f_string_ranges_t * const destination);
#endif // _di_f_string_ranges_append_

/**
 * Append the source ranges onto the destination.
 *
 * @param source
 *   The source ranges to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_append_all_
  extern f_status_t f_string_ranges_append_all(const f_string_ranges_t source, f_string_ranges_t * const destination);
#endif // _di_f_string_ranges_append_all_

/**
 * Resize the string ranges array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_decimate_by_
  extern f_status_t f_string_ranges_decimate_by(const f_number_unsigned_t amount, f_string_ranges_t * const ranges);
#endif // _di_f_string_ranges_decimate_by_

/**
 * Resize the string ranges array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_decrease_by_
  extern f_status_t f_string_ranges_decrease_by(const f_number_unsigned_t amount, f_string_ranges_t * const ranges);
#endif // _di_f_string_ranges_decrease_by_

/**
 * Increase the size of the string ranges array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param ranges
 *   The string ranges array to resize.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the new array length is too large.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_increase_
  extern f_status_t f_string_ranges_increase(const f_number_unsigned_t step, f_string_ranges_t * const ranges);
#endif // _di_f_string_ranges_increase_

/**
 * Resize the string ranges array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param ranges
 *   The string ranges array to resize.
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
#ifndef _di_f_string_ranges_increase_by_
  extern f_status_t f_string_ranges_increase_by(const f_number_unsigned_t amount, f_string_ranges_t * const ranges);
#endif // _di_f_string_ranges_increase_by_

/**
 * Resize the string ranges array.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The string ranges array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_resize_
  extern f_status_t f_string_ranges_resize(const f_number_unsigned_t length, f_string_ranges_t * const ranges);
#endif // _di_f_string_ranges_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_ranges_h

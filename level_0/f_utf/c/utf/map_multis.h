/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines map string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_map_multis_h
#define _F_utf_map_multis_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of string maps.
 *
 * Properties:
 *   - array: The array of string maps.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_map_multis_t_
  typedef struct {
    f_utf_string_map_multi_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_utf_string_map_multis_t;

  #define f_utf_string_map_multis_t_initialize f_utf_string_statics_t_initialize

  #define macro_f_utf_string_map_multis_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_utf_string_map_multis_t_initialize_2(array, length) { array, length, length }

  #define macro_f_utf_string_map_multis_t_resize(status, map_multis, length) status = f_utf_string_map_multis_resize(length, &map_multis);
  #define macro_f_utf_string_map_multis_t_adjust(status, map_multis, length) status = f_utf_string_map_multis_adjust(length, &map_multis);

  #define macro_f_utf_string_map_multis_t_delete_simple(map_multis)  f_utf_string_map_multis_resize(0, &map_multis);
  #define macro_f_utf_string_map_multis_t_destroy_simple(map_multis) f_utf_string_map_multis_adjust(0, &map_multis);

  #define macro_f_utf_string_map_multis_t_increase(status, step, map_multis)      status = f_utf_string_map_multis_increase(step, &map_multis);
  #define macro_f_utf_string_map_multis_t_increase_by(status, map_multis, amount) status = f_utf_string_map_multis_increase_by(amount, &map_multis);
  #define macro_f_utf_string_map_multis_t_decrease_by(status, map_multis, amount) status = f_utf_string_map_multis_decrease_by(amount, &map_multis);
  #define macro_f_utf_string_map_multis_t_decimate_by(status, map_multis, amount) status = f_utf_string_map_multis_decimate_by(amount, &map_multis);
#endif // _di_f_utf_string_map_multis_t_

/**
 * Resize the map_multis array.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_map_multis_adjust_
  extern f_status_t f_utf_string_map_multis_adjust(const f_number_unsigned_t length, f_utf_string_map_multis_t * const map_multis);
#endif // _di_f_utf_string_map_multis_adjust_

/**
 * Append a single source map_multi onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_map_multis_append_
  f_status_t f_utf_string_map_multis_append(const f_utf_string_map_multi_t source, f_utf_string_map_multis_t *destination);
#endif // _di_f_utf_string_map_multis_append_

/**
 * Append the source map_multis onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
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
#ifndef _di_f_utf_string_map_multis_append_all_
  f_status_t f_utf_string_map_multis_append_all(const f_utf_string_map_multis_t source, f_utf_string_map_multis_t *destination);
#endif // _di_f_utf_string_map_multis_append_all_

/**
 * Resize the map_multis array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_map_multis_decimate_by_
  extern f_status_t f_utf_string_map_multis_decimate_by(const f_number_unsigned_t amount, f_utf_string_map_multis_t * const map_multis);
#endif // _di_f_utf_string_map_multis_decimate_by_

/**
 * Resize the map_multis array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_map_multis_decrease_by_
  extern f_status_t f_utf_string_map_multis_decrease_by(const f_number_unsigned_t amount, f_utf_string_map_multis_t * const map_multis);
#endif // _di_f_utf_string_map_multis_decrease_by_

/**
 * Increase the size of the map_multis array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param map_multis
 *   The map_multis array to resize.
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
#ifndef _di_f_utf_string_map_multis_increase_
  extern f_status_t f_utf_string_map_multis_increase(const f_number_unsigned_t step, f_utf_string_map_multis_t * const map_multis);
#endif // _di_f_utf_string_map_multis_increase_

/**
 * Resize the map_multis array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param map_multis
 *   The map_multis array to resize.
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
#ifndef _di_f_utf_string_map_multis_increase_by_
  extern f_status_t f_utf_string_map_multis_increase_by(const f_number_unsigned_t amount, f_utf_string_map_multis_t * const map_multis);
#endif // _di_f_utf_string_map_multis_increase_by_

/**
 * Resize the map_multis array.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The map_multis array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_map_multis_resize_
  extern f_status_t f_utf_string_map_multis_resize(const f_number_unsigned_t length, f_utf_string_map_multis_t * const map_multis);
#endif // _di_f_utf_string_map_multis_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_map_multis_h

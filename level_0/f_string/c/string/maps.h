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
#ifndef _F_string_maps_h
#define _F_string_maps_h

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
#ifndef _di_f_string_maps_t_
  typedef struct {
    f_string_map_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_string_maps_t;

  #define f_string_maps_t_initialize f_string_statics_t_initialize

  #define macro_f_string_maps_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_maps_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_maps_t_resize(status, maps, length) status = f_string_maps_resize(length, &maps);
  #define macro_f_string_maps_t_adjust(status, maps, length) status = f_string_maps_adjust(length, &maps);

  #define macro_f_string_maps_t_delete_simple(maps)  f_string_maps_resize(0, &maps);
  #define macro_f_string_maps_t_destroy_simple(maps) f_string_maps_adjust(0, &maps);

  #define macro_f_string_maps_t_increase(status, step, maps)      status = f_string_maps_increase(step, maps);
  #define macro_f_string_maps_t_increase_by(status, maps, amount) status = f_string_maps_increase_by(amount, maps);
  #define macro_f_string_maps_t_decrease_by(status, maps, amount) status = f_string_maps_decrease_by(amount, maps);
  #define macro_f_string_maps_t_decimate_by(status, maps, amount) status = f_string_maps_decimate_by(amount, maps);
#endif // _di_f_string_maps_t_

/**
 * Resize the string maps array.
 *
 * @param length
 *   The new size to use.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_adjust_
  extern f_status_t f_string_maps_adjust(const f_number_unsigned_t length, f_string_maps_t * const maps);
#endif // _di_f_string_maps_adjust_

/**
 * Append a single source map onto the destination.
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
#ifndef _di_f_string_maps_append_
  extern f_status_t f_string_maps_append(const f_string_map_t source, f_string_maps_t * const destination);
#endif // _di_f_string_maps_append_

/**
 * Append the source maps onto the destination.
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
#ifndef _di_f_string_maps_append_all_
  extern f_status_t f_string_maps_append_all(const f_string_maps_t source, f_string_maps_t * const destination);
#endif // _di_f_string_maps_append_all_

/**
 * Resize the string maps array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_decimate_by_
  extern f_status_t f_string_maps_decimate_by(const f_number_unsigned_t amount, f_string_maps_t * const maps);
#endif // _di_f_string_maps_decimate_by_

/**
 * Resize the string maps array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_decrease_by_
  extern f_status_t f_string_maps_decrease_by(const f_number_unsigned_t amount, f_string_maps_t * const maps);
#endif // _di_f_string_maps_decrease_by_

/**
 * Increase the size of the string maps array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param maps
 *   The string maps array to resize.
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
#ifndef _di_f_string_maps_increase_
  extern f_status_t f_string_maps_increase(const f_number_unsigned_t step, f_string_maps_t * const maps);
#endif // _di_f_string_maps_increase_

/**
 * Resize the string maps array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param maps
 *   The string maps array to resize.
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
#ifndef _di_f_string_maps_increase_by_
  extern f_status_t f_string_maps_increase_by(const f_number_unsigned_t amount, f_string_maps_t * const maps);
#endif // _di_f_string_maps_increase_by_

/**
 * Resize the string maps array.
 *
 * @param length
 *   The new size to use.
 * @param maps
 *   The string maps array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_resize_
  extern f_status_t f_string_maps_resize(const f_number_unsigned_t length, f_string_maps_t * const maps);
#endif // _di_f_string_maps_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_maps_h

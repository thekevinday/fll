/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines range string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_range_h
#define _F_string_range_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure designating a start and stop range for some string.
 *
 * In general, this project uses the start and stop position inclusively, meaning that a range of 0 to 1 would include positions 0 and position 1.
 * Therefore, a range from 0 to 0 would be include position 0.
 * Set start to some value larger than stop to designate that there is no range (such as start = 1, stop = 0).
 *
 * A special f_macro_string_range_t_initialize() is provided for the special purpose of easily initialize a static string range.
 *
 * start: the start position.
 * stop: the stop position.
 */
#ifndef _di_f_string_range_t_
  typedef struct {
    f_string_length_t start;
    f_string_length_t stop;
  } f_string_range_t;

  #define f_string_range_t_initialize { 1, 0 }

  #define f_macro_string_range_t_initialize(length) { length ? 0 : 1, length ? length - 1 : 0 }

  #define f_macro_string_range_t_clear(range) \
    range.start = 1; \
    range.stop = 0;
#endif // _di_f_string_range_t_

/**
 * An array of string ranges.
 *
 * array: the array of string ranges.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_ranges_t_
  typedef struct {
    f_string_range_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_ranges_t;

  #define f_string_ranges_t_initialize {0, 0, 0}

  #define f_macro_string_ranges_t_clear(ranges) f_macro_memory_structure_clear(ranges);

  #define f_macro_string_ranges_t_new(status, ranges, length) f_macro_memory_structure_new(status, ranges, f_string_range_t, length);

  #define f_macro_string_ranges_t_resize(status, ranges, length) f_macro_memory_structure_resize(status, ranges, f_string_range_t, length);
  #define f_macro_string_ranges_t_adjust(status, ranges, length) f_macro_memory_structure_adjust(status, ranges, f_string_range_t, length);

  #define f_macro_string_ranges_t_delete(status, ranges)  f_macro_memory_structure_delete(status, ranges, f_string_range_t);
  #define f_macro_string_ranges_t_destroy(status, ranges) f_macro_memory_structure_destroy(status, ranges, f_string_range_t);

  #define f_macro_string_ranges_t_delete_simple(ranges)  f_macro_memory_structure_delete_simple(ranges, f_string_range_t);
  #define f_macro_string_ranges_t_destroy_simple(ranges) f_macro_memory_structure_destroy_simple(ranges, f_string_range_t);

  #define f_macro_string_ranges_t_increase(status, ranges) f_macro_memory_structure_increase(status, ranges, f_string_range_t);
  #define f_macro_string_ranges_t_decrease(status, ranges) f_macro_memory_structure_decrease(status, ranges, f_string_range_t);
  #define f_macro_string_ranges_t_decimate(status, ranges) f_macro_memory_structure_decimate(status, ranges, f_string_range_t);

  #define f_macro_string_ranges_t_increase_by(status, ranges, amount) f_macro_memory_structure_increase_by(status, ranges, f_string_range_t, amount);
  #define f_macro_string_ranges_t_decrease_by(status, ranges, amount) f_macro_memory_structure_decrease_by(status, ranges, f_string_range_t, amount);
  #define f_macro_string_ranges_t_decimate_by(status, ranges, amount) f_macro_memory_structure_decimate_by(status, ranges, f_string_range_t, amount);
#endif // _di_f_string_ranges_t_

/**
 * This holds an array of f_string_ranges_t.
 *
 * array: The array of ranges arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_rangess_t_
  typedef struct {
    f_string_ranges_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_rangess_t;

  #define f_string_rangess_t_initialize { 0, 0, 0 }

  #define f_macro_string_rangess_t_clear(rangess) f_macro_memory_structures_clear(rangess);

  #define f_macro_string_rangess_t_new(status, rangess, length) f_macro_memory_structures_new(status, rangess, f_string_ranges_t, length);

  #define f_macro_string_rangess_t_resize(status, rangess, length) f_macro_memory_structures_resize(status, rangess, f_string_range_t, f_string_ranges_t, length, f_array_length_t);
  #define f_macro_string_rangess_t_adjust(status, rangess, length) f_macro_memory_structures_adjust(status, rangess, f_string_range_t, f_string_ranges_t, length, f_array_length_t);

  #define f_macro_string_rangess_t_delete(status, rangess)  f_macro_memory_structures_delete(status, rangess, f_string_range_t, f_string_ranges_t);
  #define f_macro_string_rangess_t_destroy(status, rangess) f_macro_memory_structures_destroy(status, rangess, f_string_range_t, f_string_ranges_t);

  #define f_macro_string_rangess_t_delete_simple(rangess)  f_macro_memory_structures_delete_simple(rangess, f_string_range_t, f_string_ranges_t);
  #define f_macro_string_rangess_t_destroy_simple(rangess) f_macro_memory_structures_destroy_simple(rangess, f_string_range_t, f_string_ranges_t);

  #define f_macro_string_rangess_t_increase(status, string_ranges) f_macro_memory_structures_increase(status, string_ranges, f_string_range_t, f_array_length_t);
  #define f_macro_string_rangess_t_decrease(status, string_ranges) f_macro_memory_structures_decrease(status, string_ranges, f_string_range_t, f_string_range_t);
  #define f_macro_string_rangess_t_decimate(status, string_ranges) f_macro_memory_structures_decimate(status, string_ranges, f_string_range_t, f_string_range_t);

  #define f_macro_string_rangess_t_increase_by(status, string_ranges, amount) f_macro_memory_structures_increase_by(status, string_ranges, f_string_range_t, f_array_length_t, amount);
  #define f_macro_string_rangess_t_decrease_by(status, string_ranges, amount) f_macro_memory_structures_decrease_by(status, string_ranges, f_string_range_t, f_string_ranges_t, f_array_length_t, amount);
  #define f_macro_string_rangess_t_decimate_by(status, string_ranges, amount) f_macro_memory_structures_decimate_by(status, string_ranges, f_string_range_t, f_string_ranges_t, f_array_length_t, amount);
#endif // _di_f_string_rangess_t_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_adjust_
  extern f_status_t f_string_ranges_adjust(const f_array_length_t length, f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_adjust_

/**
 * Resize the string ranges array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_decimate_
  extern f_status_t f_string_ranges_decimate(f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_decimate_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_decimate_by_
  extern f_status_t f_string_ranges_decimate_by(const f_array_length_t amount, f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_decimate_by_

/**
 * Resize the string ranges array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_decrease_
  extern f_status_t f_string_ranges_decrease(f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_decrease_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_decrease_by_
  extern f_status_t f_string_ranges_decrease_by(const f_array_length_t amount, f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_decrease_by_

/**
 * Delete the array of string ranges.
 *
 * @param ranges
 *   The ranges to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_delete_
  extern f_status_t f_string_ranges_delete(f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_delete_

/**
 * Delete the array of string ranges.
 *
 * @param ranges
 *   The ranges to destroy.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_destroy_
  extern f_status_t f_string_ranges_destroy(f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_destroy_

/**
 * Increase the size of the string ranges array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_increase_
  extern f_status_t f_string_ranges_increase(f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_increase_

/**
 * Resize the string ranges array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param ranges
 *   The string ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_string_ranges_increase_by_
  extern f_status_t f_string_ranges_increase_by(const f_array_length_t amount, f_string_ranges_t *ranges);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_ranges_adjust_
  extern f_status_t f_string_ranges_adjust(const f_array_length_t length, f_string_ranges_t *ranges);
#endif // _di_f_string_ranges_adjust_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_range_h

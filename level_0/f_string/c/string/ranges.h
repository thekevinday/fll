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
 * Properties:
 *   - array: The array of string ranges.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
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

  #define macro_f_string_ranges_t_clear(ranges) \
    ranges.array = 0; \
    ranges.size = 0; \
    ranges.used = 0;
#endif // _di_f_string_ranges_t_

/**
 * Append the single source range onto the destination.
 *
 * @param source
 *   The source range to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_okay on success.
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
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_ranges_append_all_
  extern f_status_t f_string_ranges_append_all(const f_string_ranges_t source, f_string_ranges_t * const destination);
#endif // _di_f_string_ranges_append_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_ranges_h

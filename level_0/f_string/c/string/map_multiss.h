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
#ifndef _F_string_map_multiss_h
#define _F_string_map_multiss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of string maps arrays.
 *
 * Properties:
 *   - array: The array of an array of string maps.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_map_multiss_t_
  typedef struct {
    f_string_map_multis_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_string_map_multiss_t;

  #define f_string_map_multiss_t_initialize f_string_statics_t_initialize

  #define macro_f_string_map_multiss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_map_multiss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_map_multiss_t_clear(map_multiss) \
    map_multiss.array = 0; \
    map_multiss.size = 0; \
    map_multiss.used = 0;
#endif // _di_f_string_map_multiss_t_

/**
 * Append a single source map_multis onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multiss_append_
  f_status_t f_string_map_multiss_append(const f_string_map_multis_t source, f_string_map_multiss_t *destination);
#endif // _di_f_string_map_multiss_append_

/**
 * Append the source map_multiss onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
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
#ifndef _di_f_string_map_multiss_append_all_
  f_status_t f_string_map_multiss_append_all(const f_string_map_multiss_t source, f_string_map_multiss_t *destination);
#endif // _di_f_string_map_multiss_append_all_

/**
 * A callback intended to be passed to f_memory_arrayss_resize() for an f_string_map_multiss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_string_map_multiss_delete_callback_
  extern f_status_t f_string_map_multiss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_string_map_multiss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrayss_adjust() for an f_string_map_multiss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_string_map_multiss_destroy_callback_
  extern f_status_t f_string_map_multiss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_string_map_multiss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_multiss_h

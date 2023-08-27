/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines dynamic string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_dynamicss_h
#define _F_utf_dynamicss_h

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
#ifndef _di_f_utf_string_dynamicss_t_
  typedef f_utf_string_staticss_t f_utf_string_dynamicss_t;

  #define f_utf_string_dynamicss_t_initialize f_utf_string_staticss_t_initialize

  #define macro_f_utf_string_dynamicss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_utf_string_dynamicss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_utf_string_dynamicss_t_clear(dynamicss) macro_f_utf_string_staticss_t_clear(dynamicss)
#endif // _di_f_utf_string_dynamicss_t_

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
#ifndef _di_f_utf_string_dynamicss_append_
  extern f_status_t f_utf_string_dynamicss_append(const f_utf_string_dynamics_t source, f_utf_string_dynamicss_t * const destination);
#endif // _di_f_utf_string_dynamicss_append_

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
#ifndef _di_f_utf_string_dynamicss_append_all_
  extern f_status_t f_utf_string_dynamicss_append_all(const f_utf_string_dynamicss_t source, f_utf_string_dynamicss_t * const destination);
#endif // _di_f_utf_string_dynamicss_append_all_

/**
 * A callback intended to be passed to f_memory_arrayss_resize() for an f_utf_string_dynamicss_t structure.
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
#ifndef _di_f_utf_string_dynamicss_delete_callback_
  extern f_status_t f_utf_string_dynamicss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_utf_string_dynamicss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrayss_adjust() for an f_utf_string_dynamicss_t structure.
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
#ifndef _di_f_utf_string_dynamicss_destroy_callback_
  extern f_status_t f_utf_string_dynamicss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_utf_string_dynamicss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_dynamicss_h

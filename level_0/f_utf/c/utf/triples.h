/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines 3-tuple of string data called a triple (which is an ordered list of 3 strings).
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_triples_h
#define _F_utf_triples_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of string triples.
 *
 * Properties:
 *   - array: The array of string triples.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_triples_t_
  typedef struct {
    f_utf_string_triple_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_utf_string_triples_t;

  #define f_utf_string_triples_t_initialize f_utf_string_statics_t_initialize

  #define macro_f_utf_string_triples_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_utf_string_triples_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_utf_string_triples_t_

/**
 * Append the single source triples onto the destination.
 *
 * @param source
 *   The source triple to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_triples_append_
  extern f_status_t f_utf_string_triples_append(const f_utf_string_triple_t source, f_utf_string_triples_t * const destination);
#endif // _di_f_utf_string_triples_append_

/**
 * Append the source triples onto the destination.
 *
 * @param source
 *   The source triples to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_triples_append_all_
  extern f_status_t f_utf_string_triples_append_all(const f_utf_string_triples_t source, f_utf_string_triples_t * const destination);
#endif // _di_f_utf_string_triples_append_all_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_utf_string_triples_t structure.
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
#ifndef _di_f_utf_string_triples_delete_callback_
  extern f_status_t f_utf_string_triples_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_utf_string_triples_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_utf_string_triples_t structure.
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
#ifndef _di_f_utf_string_triples_destroy_callback_
  extern f_status_t f_utf_string_triples_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_utf_string_triples_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_triples_h

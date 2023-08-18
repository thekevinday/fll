/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by type (array) related functionality.
 *
 * This is auto-included by type_array.h and should not need to be explicitly included.
 */
#ifndef _F_type_array_int8_h
#define _F_type_array_int8_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_int8ss_t structure.
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
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_int8ss_delete_callback_
  extern f_status_t f_int8ss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_int8ss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_int8ss_t structure.
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
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_int8ss_destroy_callback_
  extern f_status_t f_int8ss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_int8ss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_int8_h

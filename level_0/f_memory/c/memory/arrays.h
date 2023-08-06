/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines memory array data.
 *
 * This is auto-included by memory.h and should not need to be explicitly included.
 */
#ifndef _F_memory_arrays_h
#define _F_memory_arrays_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the memory array of arrays.
 *
 * This function is only useful for structures of the form "{ array, used, size }" where the array is a an array of simple types.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * The inner array can be a more complex structure because the callback is expected to know the type.
 *
 * @param length
 *   The new size to use.
 * @param width
 *   The size of the structure represented by array.
 *   The word "width" is used due to conflicts of already using "length" and "size".
 *   Must not be 0.
 * @param array
 *   The structure.array to resize.
 * @param used
 *   The structure.used.
 * @param size
 *   The structure.size.
 * @param callback
 *   A callback to call on each array value when reducing the length of the array.
 *   This callback is expected to know the appropriate type and will cast the structure parameter to the appropriate type.
 *
 *   This is only called when the requested length is less than the given size.
 *
 *   Callback Parameters:
 *     - start: The start position in the array to start deleting.
 *     - stop:  The stop in the array to stop deleting.
 *     - array: The array structure to delete all values of.
 *
 *   Callback Returns:
 *     The standard status codes similar to this function.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_arrays_adjust_
  extern f_status_t f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));
#endif // _di_f_memory_arrays_adjust_

/**
 * Resize the memory array of arrays.
 *
 * This function is only useful for structures of the form "{ array, used, size }" where the array is a an array of simple types.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * The inner array can be a more complex structure because the callback is expected to know the type.
 *
 * @param length
 *   The new size to use.
 * @param width
 *   The size of the structure represented by array.
 *   The word "width" is used due to conflicts of already using "length" and "size".
 *   Must not be 0.
 * @param array
 *   The structure.array to resize.
 * @param used
 *   The structure.used.
 * @param size
 *   The structure.size.
 * @param callback
 *   A callback to call on each array value when reducing the length of the array.
 *   This callback is expected to know the appropriate type and will cast the structure parameter to the appropriate type.
 *
 *   This is only called when the requested length is less than the given size.
 *
 *   Callback Parameters:
 *     - start: The start position in the array to start deleting.
 *     - stop:  The stop in the array to stop deleting.
 *     - array: The array structure to delete all values of.
 *
 *   Callback Returns:
 *     The standard status codes similar to this function.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_arrays_resize_
  extern f_status_t f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));
#endif // _di_f_memory_arrays_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_arrays_h

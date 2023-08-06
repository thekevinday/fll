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
#ifndef _F_memory_array_h
#define _F_memory_array_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the memory array.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
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
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_adjust_
  extern f_status_t f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_adjust_

/**
 * Append the single source onto the destination array.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * @param source
 *   The source structure to copy from.
 * @param width
 *   The size of the structure represented by array.
 *   The word "width" is used due to conflicts of already using "length" and "size".
 *   Must not be 0.
 * @param array
 *   The structure.array destination.
 *
 *   A literal array structure cannot be directly passed or this may segfault.
 *   Bad:
 *     {
 *       int arr[5] = { 0 };
 *       ...
 *       f_memory_array_append(source, width, (void **) &arr, used, size);
 *     }
 *   Better:
 *     {
 *       int arr[5] = { 0 };
 *       int *arr_pounter = arr;
 *       ...
 *       f_memory_array_append(source, width, (void **) &arr_pounter, used, size);
 *     }
 * @param used
 *   The structure.used destination.
 * @param size
 *   The structure.size destination.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_append_
  extern f_status_t f_memory_array_append(const void * const source, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_append_

/**
 * Append the single source onto the destination array.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * Warning: This default implementation of this function uses multiplication between the amount and the width.
 *          Be careful that the resulting multiplication does not overflow f_number_unsigned_t.
 *
 * @param sources
 *   The source structure to copy from.
 *   This is generally a structure.array value.
 * @param amount
 *   The total length of the sources to copy.
 *   The is generally the structure.used value.
 * @param width
 *   The size of the structure represented by array.
 *   The word "width" is used due to conflicts of already using "length" and "size".
 *   Must not be 0.
 * @param array
 *   The structure.array destination.
 *
 *   A literal array structure cannot be directly passed or this may segfault.
 *   Bad:
 *     {
 *       int arr[5] = { 0 };
 *       ...
 *       f_memory_array_append_all(sources, amount, width, (void **) &arr, used, size);
 *     }
 *   Better:
 *     {
 *       int arr[5] = { 0 };
 *       int *arr_pounter = arr;
 *       ...
 *       f_memory_array_append_all(sources, amount, width, (void **) &arr_pounter, used, size);
 *     }
 * @param used
 *   The structure.used destination.
 * @param size
 *   The structure.size destination.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_append_all_
  extern f_status_t f_memory_array_append_all(const void * const sources, const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_append_all_

/**
 * Resize the memory array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
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
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_decimate_by_
  extern f_status_t f_memory_array_decimate_by(const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_decimate_by_

/**
 * Resize the memory array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
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
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_decrease_by_
  extern f_status_t f_memory_array_decrease_by(const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_decrease_by_

/**
 * Increase the size of the memory array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
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
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory..
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_increase_
  extern f_status_t f_memory_array_increase(const f_number_unsigned_t step, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_increase_

/**
 * Resize the memory array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
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
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_memory_array_increase_by_
  extern f_status_t f_memory_array_increase_by(const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_increase_by_

/**
 * Resize the memory array.
 *
 * This function is only useful for simple structures of the form "{ array, used, size }" where the array is a simple type.
 * If the simple type that is "array" requires additional memory manipulation on allocation or de-allocation, then do not use this function.
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
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_memory_array_resize_
  extern f_status_t f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
#endif // _di_f_memory_array_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_array_h

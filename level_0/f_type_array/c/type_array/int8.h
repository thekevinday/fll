/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
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
 * Resize the int8s array.
 *
 * @param length
 *   The new size to use.
 * @param int8s
 *   The int8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_int8s_adjust_
  extern f_status_t f_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s);
#endif // _di_f_int8s_adjust_

/**
 * Append the source int8s onto the destination.
 *
 * @param source
 *   The source int8s to append.
 * @param destination
 *   The destination int8s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int8s_append_
  extern f_status_t f_int8s_append(const f_int8s_t source, f_int8s_t *destination);
#endif // _di_f_int8s_append_

/**
 * Resize the int8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int8s
 *   The int8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_int8s_decimate_by_
  extern f_status_t f_int8s_decimate_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_f_int8s_decimate_by_

/**
 * Resize the int8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int8s
 *   The int8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int8s_decrease_by_
  extern f_status_t f_int8s_decrease_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_f_int8s_decrease_by_

/**
 * Increase the size of the int8s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int8s
 *   The int8s array to resize.
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
#ifndef _di_f_int8s_increase_
  extern f_status_t f_int8s_increase(const f_array_length_t step, f_int8s_t *int8s);
#endif // _di_f_int8s_increase_

/**
 * Resize the int8s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int8s
 *   The int8s array to resize.
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
#ifndef _di_f_int8s_increase_by_
  extern f_status_t f_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_f_int8s_increase_by_

/**
 * Resize the int8s array.
 *
 * @param length
 *   The new size to use.
 * @param int8s
 *   The int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int8s_resize_
  extern f_status_t f_int8s_resize(const f_array_length_t length, f_int8s_t *int8s);
#endif // _di_f_int8s_resize_

/**
 * Resize the int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param int8ss
 *   The int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_int8ss_adjust_
  extern f_status_t f_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_adjust_

/**
 * Append the source int8ss onto the destination.
 *
 * @param source
 *   The source int8ss to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int8ss_append_
  extern f_status_t f_int8ss_append(const f_int8ss_t source, f_int8ss_t *destination);
#endif // _di_f_int8ss_append_

/**
 * Resize the int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param int8ss
 *   The int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_int8ss_adjust_
  extern f_status_t f_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_adjust_

/**
 * Resize the int8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int8ss
 *   The int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_int8ss_decimate_by_
  extern f_status_t f_int8ss_decimate_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_decimate_by_

/**
 * Resize the int8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int8ss
 *   The int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int8ss_decrease_by_
  extern f_status_t f_int8ss_decrease_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_decrease_by_

/**
 * Increase the size of the int8ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int8ss
 *   The int8ss array to resize.
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
#ifndef _di_f_int8ss_increase_
  extern f_status_t f_int8ss_increase(const f_array_length_t step, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_increase_

/**
 * Resize the int8ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int8ss
 *   The int8ss array to resize.
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
#ifndef _di_f_int8ss_increase_by_
  extern f_status_t f_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_increase_by_

/**
 * Resize the int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param int8ss
 *   The int8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int8ss_resize_
  extern f_status_t f_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_int8ss_resize_

/**
 * Resize the string uint8s array.
 *
 * @param length
 *   The new size to use.
 * @param uint8s
 *   The string uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_uint8s_adjust_
  extern f_status_t f_uint8s_adjust(const f_array_length_t length, f_uint8s_t *uint8s);
#endif // _di_f_uint8s_adjust_

/**
 * Append the source uint8s onto the destination.
 *
 * @param source
 *   The source uint8s to append.
 * @param destination
 *   The destination uint8s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_uint8s_append_
  extern f_status_t f_uint8s_append(const f_uint8s_t source, f_uint8s_t *destination);
#endif // _di_f_uint8s_append_

/**
 * Resize the string uint8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint8s
 *   The string uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_uint8s_decimate_by_
  extern f_status_t f_uint8s_decimate_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_f_uint8s_decimate_by_

/**
 * Resize the string uint8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint8s
 *   The string uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_uint8s_decrease_by_
  extern f_status_t f_uint8s_decrease_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_f_uint8s_decrease_by_

/**
 * Increase the size of the string uint8s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint8s
 *   The string uint8s array to resize.
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
#ifndef _di_f_uint8s_increase_
  extern f_status_t f_uint8s_increase(const f_array_length_t step, f_uint8s_t *uint8s);
#endif // _di_f_uint8s_increase_

/**
 * Resize the string uint8s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint8s
 *   The string uint8s array to resize.
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
#ifndef _di_f_uint8s_increase_by_
  extern f_status_t f_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_f_uint8s_increase_by_

/**
 * Resize the string uint8s array.
 *
 * @param length
 *   The new size to use.
 * @param uint8s
 *   The string uint8s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_uint8s_resize_
  extern f_status_t f_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s);
#endif // _di_f_uint8s_resize_

/**
 * Resize the string uint8ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_uint8ss_adjust_
  extern f_status_t f_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_adjust_

/**
 * Append the source uint8ss onto the destination.
 *
 * @param source
 *   The source uint8ss to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_uint8ss_append_
  extern f_status_t f_uint8ss_append(const f_uint8ss_t source, f_uint8ss_t *destination);
#endif // _di_f_uint8ss_append_

/**
 * Resize the string uint8ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_uint8ss_adjust_
  extern f_status_t f_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_adjust_

/**
 * Resize the string uint8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_uint8ss_decimate_by_
  extern f_status_t f_uint8ss_decimate_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_decimate_by_

/**
 * Resize the string uint8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_uint8ss_decrease_by_
  extern f_status_t f_uint8ss_decrease_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_decrease_by_

/**
 * Increase the size of the string uint8ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint8ss
 *   The string uint8ss array to resize.
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
#ifndef _di_f_uint8ss_increase_
  extern f_status_t f_uint8ss_increase(const f_array_length_t step, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_increase_

/**
 * Resize the string uint8ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint8ss
 *   The string uint8ss array to resize.
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
#ifndef _di_f_uint8ss_increase_by_
  extern f_status_t f_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_increase_by_

/**
 * Resize the string uint8ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint8ss
 *   The string uint8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_uint8ss_resize_
  extern f_status_t f_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_uint8ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_int8_h

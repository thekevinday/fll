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
#ifndef _F_type_array_int128_h
#define _F_type_array_int128_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the int128s array.
 *
 * @param length
 *   The new size to use.
 * @param int128s
 *   The int128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int128s_adjust_
  extern f_status_t f_type_int128s_adjust(const f_array_length_t length, f_int128s_t *int128s);
#endif // _di_f_type_int128s_adjust_

/**
 * Append the source int128s onto the destination.
 *
 * @param source
 *   The source int128s to append.
 * @param destination
 *   The destination int128s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int128s_append_
  extern f_status_t f_type_int128s_append(const f_int128s_t source, f_int128s_t *destination);
#endif // _di_f_type_int128s_append_

/**
 * Resize the int128s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int128s
 *   The int128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int128s_decimate_by_
  extern f_status_t f_type_int128s_decimate_by(const f_array_length_t amount, f_int128s_t *int128s);
#endif // _di_f_type_int128s_decimate_by_

/**
 * Resize the int128s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int128s
 *   The int128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int128s_decrease_by_
  extern f_status_t f_type_int128s_decrease_by(const f_array_length_t amount, f_int128s_t *int128s);
#endif // _di_f_type_int128s_decrease_by_

/**
 * Increase the size of the int128s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int128s
 *   The int128s array to resize.
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
#ifndef _di_f_type_int128s_increase_
  extern f_status_t f_type_int128s_increase(const uint16_t step, f_int128s_t *int128s);
#endif // _di_f_type_int128s_increase_

/**
 * Resize the int128s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int128s
 *   The int128s array to resize.
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
#ifndef _di_f_type_int128s_increase_by_
  extern f_status_t f_type_int128s_increase_by(const f_array_length_t amount, f_int128s_t *int128s);
#endif // _di_f_type_int128s_increase_by_

/**
 * Resize the int128s array.
 *
 * @param length
 *   The new size to use.
 * @param int128s
 *   The int128s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int128s_resize_
  extern f_status_t f_type_int128s_resize(const f_array_length_t length, f_int128s_t *int128s);
#endif // _di_f_type_int128s_resize_

/**
 * Resize the int128ss array.
 *
 * @param length
 *   The new size to use.
 * @param int128ss
 *   The int128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int128ss_adjust_
  extern f_status_t f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_adjust_

/**
 * Append the source int128ss onto the destination.
 *
 * @param source
 *   The source int128ss to append.
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
#ifndef _di_f_type_int128ss_append_
  extern f_status_t f_type_int128ss_append(const f_int128ss_t source, f_int128ss_t *destination);
#endif // _di_f_type_int128ss_append_

/**
 * Resize the int128ss array.
 *
 * @param length
 *   The new size to use.
 * @param int128ss
 *   The int128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int128ss_adjust_
  extern f_status_t f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_adjust_

/**
 * Resize the int128ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int128ss
 *   The int128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int128ss_decimate_by_
  extern f_status_t f_type_int128ss_decimate_by(const f_array_length_t amount, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_decimate_by_

/**
 * Resize the int128ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int128ss
 *   The int128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int128ss_decrease_by_
  extern f_status_t f_type_int128ss_decrease_by(const f_array_length_t amount, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_decrease_by_

/**
 * Increase the size of the int128ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int128ss
 *   The int128ss array to resize.
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
#ifndef _di_f_type_int128ss_increase_
  extern f_status_t f_type_int128ss_increase(const uint16_t step, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_increase_

/**
 * Resize the int128ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int128ss
 *   The int128ss array to resize.
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
#ifndef _di_f_type_int128ss_increase_by_
  extern f_status_t f_type_int128ss_increase_by(const f_array_length_t amount, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_increase_by_

/**
 * Resize the int128ss array.
 *
 * @param length
 *   The new size to use.
 * @param int128ss
 *   The int128ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int128ss_resize_
  extern f_status_t f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_resize_

/**
 * Resize the string uint128s array.
 *
 * @param length
 *   The new size to use.
 * @param uint128s
 *   The string uint128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint128s_adjust_
  extern f_status_t f_type_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s);
#endif // _di_f_type_uint128s_adjust_

/**
 * Append the source uint128s onto the destination.
 *
 * @param source
 *   The source uint128s to append.
 * @param destination
 *   The destination uint128s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint128s_append_
  extern f_status_t f_type_uint128s_append(const f_uint128s_t source, f_uint128s_t *destination);
#endif // _di_f_type_uint128s_append_

/**
 * Resize the string uint128s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint128s
 *   The string uint128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint128s_decimate_by_
  extern f_status_t f_type_uint128s_decimate_by(const f_array_length_t amount, f_uint128s_t *uint128s);
#endif // _di_f_type_uint128s_decimate_by_

/**
 * Resize the string uint128s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint128s
 *   The string uint128s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint128s_decrease_by_
  extern f_status_t f_type_uint128s_decrease_by(const f_array_length_t amount, f_uint128s_t *uint128s);
#endif // _di_f_type_uint128s_decrease_by_

/**
 * Increase the size of the string uint128s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint128s
 *   The string uint128s array to resize.
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
#ifndef _di_f_type_uint128s_increase_
  extern f_status_t f_type_uint128s_increase(const uint16_t step, f_uint128s_t *uint128s);
#endif // _di_f_type_uint128s_increase_

/**
 * Resize the string uint128s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint128s
 *   The string uint128s array to resize.
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
#ifndef _di_f_type_uint128s_increase_by_
  extern f_status_t f_type_uint128s_increase_by(const f_array_length_t amount, f_uint128s_t *uint128s);
#endif // _di_f_type_uint128s_increase_by_

/**
 * Resize the string uint128s array.
 *
 * @param length
 *   The new size to use.
 * @param uint128s
 *   The string uint128s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint128s_resize_
  extern f_status_t f_type_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s);
#endif // _di_f_type_uint128s_resize_

/**
 * Resize the string uint128ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint128ss
 *   The string uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint128ss_adjust_
  extern f_status_t f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_adjust_

/**
 * Append the source uint128ss onto the destination.
 *
 * @param source
 *   The source uint128ss to append.
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
#ifndef _di_f_type_uint128ss_append_
  extern f_status_t f_type_uint128ss_append(const f_uint128ss_t source, f_uint128ss_t *destination);
#endif // _di_f_type_uint128ss_append_

/**
 * Resize the string uint128ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint128ss
 *   The string uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint128ss_adjust_
  extern f_status_t f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_adjust_

/**
 * Resize the string uint128ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint128ss
 *   The string uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint128ss_decimate_by_
  extern f_status_t f_type_uint128ss_decimate_by(const f_array_length_t amount, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_decimate_by_

/**
 * Resize the string uint128ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint128ss
 *   The string uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint128ss_decrease_by_
  extern f_status_t f_type_uint128ss_decrease_by(const f_array_length_t amount, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_decrease_by_

/**
 * Increase the size of the string uint128ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint128ss
 *   The string uint128ss array to resize.
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
#ifndef _di_f_type_uint128ss_increase_
  extern f_status_t f_type_uint128ss_increase(const uint16_t step, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_increase_

/**
 * Resize the string uint128ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint128ss
 *   The string uint128ss array to resize.
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
#ifndef _di_f_type_uint128ss_increase_by_
  extern f_status_t f_type_uint128ss_increase_by(const f_array_length_t amount, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_increase_by_

/**
 * Resize the string uint128ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint128ss
 *   The string uint128ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint128ss_resize_
  extern f_status_t f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_int128_h

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
#ifndef _F_type_array_int16_h
#define _F_type_array_int16_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the int16s array.
 *
 * @param length
 *   The new size to use.
 * @param int16s
 *   The int16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_int16s_adjust_
  extern f_status_t f_int16s_adjust(const f_array_length_t length, f_int16s_t *int16s);
#endif // _di_f_int16s_adjust_

/**
 * Append the single source int16 onto the destination.
 *
 * @param source
 *   The source int16 to append.
 * @param destination
 *   The destination int16s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int16s_append_
  extern f_status_t f_int16s_append(const int16_t source, f_int16s_t *destination);
#endif // _di_f_int16s_append_

/**
 * Append the source int16s onto the destination.
 *
 * @param source
 *   The source int16s to append.
 * @param destination
 *   The destination int16s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int16s_append_all_
  extern f_status_t f_int16s_append_all(const f_int16s_t source, f_int16s_t *destination);
#endif // _di_f_int16s_append_all_

/**
 * Resize the int16s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int16s
 *   The int16s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_int16s_decimate_by_
  extern f_status_t f_int16s_decimate_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_f_int16s_decimate_by_

/**
 * Resize the int16s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int16s
 *   The int16s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int16s_decrease_by_
  extern f_status_t f_int16s_decrease_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_f_int16s_decrease_by_

/**
 * Increase the size of the int16s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int16s
 *   The int16s array to resize.
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
#ifndef _di_f_int16s_increase_
  extern f_status_t f_int16s_increase(const f_array_length_t step, f_int16s_t *int16s);
#endif // _di_f_int16s_increase_

/**
 * Resize the int16s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int16s
 *   The int16s array to resize.
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
#ifndef _di_f_int16s_increase_by_
  extern f_status_t f_int16s_increase_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_f_int16s_increase_by_

/**
 * Resize the int16s array.
 *
 * @param length
 *   The new size to use.
 * @param int16s
 *   The int16s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int16s_resize_
  extern f_status_t f_int16s_resize(const f_array_length_t length, f_int16s_t *int16s);
#endif // _di_f_int16s_resize_

/**
 * Resize the int16ss array.
 *
 * @param length
 *   The new size to use.
 * @param int16ss
 *   The int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_int16ss_adjust_
  extern f_status_t f_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss);
#endif // _di_f_int16ss_adjust_

/**
 * Append the single source int16s onto the destination.
 *
 * @param source
 *   The source int16s to append.
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
#ifndef _di_f_int16ss_append_
  extern f_status_t f_int16ss_append(const f_int16s_t source, f_int16ss_t *destination);
#endif // _di_f_int16ss_append_

/**
 * Append the source int16ss onto the destination.
 *
 * @param source
 *   The source int16ss to append.
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
#ifndef _di_f_int16ss_append_all_
  extern f_status_t f_int16ss_append_all(const f_int16ss_t source, f_int16ss_t *destination);
#endif // _di_f_int16ss_append_all_

/**
 * Resize the int16ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int16ss
 *   The int16ss array to resize.
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
#ifndef _di_f_int16ss_decimate_by_
  extern f_status_t f_int16ss_decimate_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_f_int16ss_decimate_by_

/**
 * Resize the int16ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int16ss
 *   The int16ss array to resize.
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
#ifndef _di_f_int16ss_decrease_by_
  extern f_status_t f_int16ss_decrease_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_f_int16ss_decrease_by_

/**
 * Increase the size of the int16ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int16ss
 *   The int16ss array to resize.
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
#ifndef _di_f_int16ss_increase_
  extern f_status_t f_int16ss_increase(const f_array_length_t step, f_int16ss_t *int16ss);
#endif // _di_f_int16ss_increase_

/**
 * Resize the int16ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int16ss
 *   The int16ss array to resize.
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
#ifndef _di_f_int16ss_increase_by_
  extern f_status_t f_int16ss_increase_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_f_int16ss_increase_by_

/**
 * Resize the int16ss array.
 *
 * @param length
 *   The new size to use.
 * @param int16ss
 *   The int16ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_int16ss_resize_
  extern f_status_t f_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss);
#endif // _di_f_int16ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_int16_h

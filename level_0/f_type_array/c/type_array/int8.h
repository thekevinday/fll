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
 * Resize the string int8s array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_int8s_adjust_
  extern f_status_t f_int8s_adjust(const f_number_unsigned_t length, f_int8s_t * const structure);
#endif // _di_f_int8s_adjust_

/**
 * Append the single source int8 onto the destination.
 *
 * @param source
 *   The source int8 to append.
 * @param destination
 *   The destination int8s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_int8s_append_
  extern f_status_t f_int8s_append(const int8_t source, f_int8s_t * const destination);
#endif // _di_f_int8s_append_

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
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_int8s_append_all_
  extern f_status_t f_int8s_append_all(const f_int8s_t source, f_int8s_t * const destination);
#endif // _di_f_int8s_append_all_

/**
 * Resize the string int8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decimate_by().
 *
 * @see f_memory_array_decimate_by()
 */
#ifndef _di_f_int8s_decimate_by_
  extern f_status_t f_int8s_decimate_by(const f_number_unsigned_t amount, f_int8s_t * const structure);
#endif // _di_f_int8s_decimate_by_

/**
 * Resize the string int8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decrease_by().
 *
 * @see f_memory_array_decrease_by()
 */
#ifndef _di_f_int8s_decrease_by_
  extern f_status_t f_int8s_decrease_by(const f_number_unsigned_t amount, f_int8s_t * const structure);
#endif // _di_f_int8s_decrease_by_

/**
 * Increase the size of the string int8s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_int8s_increase_
  extern f_status_t f_int8s_increase(const f_number_unsigned_t step, f_int8s_t * const structure);
#endif // _di_f_int8s_increase_

/**
 * Resize the string int8s array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_int8s_increase_by_
  extern f_status_t f_int8s_increase_by(const f_number_unsigned_t amount, f_int8s_t * const structure);
#endif // _di_f_int8s_increase_by_

/**
 * Resize the string int8s array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_int8s_resize_
  extern f_status_t f_int8s_resize(const f_number_unsigned_t length, f_int8s_t * const structure);
#endif // _di_f_int8s_resize_

/**
 * Resize the string int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_int8ss_adjust_
  extern f_status_t f_int8ss_adjust(const f_number_unsigned_t length, f_int8ss_t * const structure);
#endif // _di_f_int8ss_adjust_

/**
 * Append the single source int8s onto the destination.
 *
 * @param source
 *   The source int8s to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_int8ss_append_
  extern f_status_t f_int8ss_append(const f_int8s_t source, f_int8ss_t * const destination);
#endif // _di_f_int8ss_append_

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
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_int8ss_append_all_
  extern f_status_t f_int8ss_append_all(const f_int8ss_t source, f_int8ss_t * const destination);
#endif // _di_f_int8ss_append_all_

/**
 * Resize the string int8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_int8ss_decimate_by_
  extern f_status_t f_int8ss_decimate_by(const f_number_unsigned_t amount, f_int8ss_t * const structure);
#endif // _di_f_int8ss_decimate_by_

/**
 * Resize the string int8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_int8ss_decrease_by_
  extern f_status_t f_int8ss_decrease_by(const f_number_unsigned_t amount, f_int8ss_t * const structure);
#endif // _di_f_int8ss_decrease_by_

/**
 * Increase the size of the string int8ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_int8ss_increase_
  extern f_status_t f_int8ss_increase(const f_number_unsigned_t step, f_int8ss_t * const structure);
#endif // _di_f_int8ss_increase_

/**
 * Resize the string int8ss array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_int8ss_increase_by_
  extern f_status_t f_int8ss_increase_by(const f_number_unsigned_t amount, f_int8ss_t * const structure);
#endif // _di_f_int8ss_increase_by_

/**
 * Resize the string int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string int8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_int8ss_resize_
  extern f_status_t f_int8ss_resize(const f_number_unsigned_t length, f_int8ss_t * const structure);
#endif // _di_f_int8ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_int8_h

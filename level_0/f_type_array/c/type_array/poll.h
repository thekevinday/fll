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
#ifndef _F_type_array_poll_h
#define _F_type_array_poll_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the string polls array.
 *
 * @param length
 *   The new size to use.
 * @param polls
 *   The string polls array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_polls_adjust_
  extern f_status_t f_polls_adjust(const f_number_unsigned_t length, f_polls_t * const polls);
#endif // _di_f_polls_adjust_

/**
 * Append the single source poll onto the destination.
 *
 * @param source
 *   The source poll to append.
 * @param destination
 *   The destination polls the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_polls_append_
  extern f_status_t f_polls_append(const f_poll_t source, f_polls_t * const destination);
#endif // _di_f_polls_append_

/**
 * Append the source polls onto the destination.
 *
 * @param source
 *   The source polls to append.
 * @param destination
 *   The destination polls the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_polls_append_all_
  extern f_status_t f_polls_append_all(const f_polls_t source, f_polls_t * const destination);
#endif // _di_f_polls_append_all_

/**
 * Resize the string polls array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param polls
 *   The string polls array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_polls_decimate_by_
  extern f_status_t f_polls_decimate_by(const f_number_unsigned_t amount, f_polls_t * const polls);
#endif // _di_f_polls_decimate_by_

/**
 * Resize the string polls array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param polls
 *   The string polls array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_polls_decrease_by_
  extern f_status_t f_polls_decrease_by(const f_number_unsigned_t amount, f_polls_t * const polls);
#endif // _di_f_polls_decrease_by_

/**
 * Increase the size of the string polls array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param polls
 *   The string polls array to resize.
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
#ifndef _di_f_polls_increase_
  extern f_status_t f_polls_increase(const f_number_unsigned_t step, f_polls_t * const polls);
#endif // _di_f_polls_increase_

/**
 * Resize the string polls array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param polls
 *   The string polls array to resize.
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
#ifndef _di_f_polls_increase_by_
  extern f_status_t f_polls_increase_by(const f_number_unsigned_t amount, f_polls_t * const polls);
#endif // _di_f_polls_increase_by_

/**
 * Resize the string polls array.
 *
 * @param length
 *   The new size to use.
 * @param polls
 *   The string polls array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_polls_resize_
  extern f_status_t f_polls_resize(const f_number_unsigned_t length, f_polls_t * const polls);
#endif // _di_f_polls_resize_

/**
 * Resize the string pollss array.
 *
 * @param length
 *   The new size to use.
 * @param pollss
 *   The string pollss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_pollss_adjust_
  extern f_status_t f_pollss_adjust(const f_number_unsigned_t length, f_pollss_t * const pollss);
#endif // _di_f_pollss_adjust_

/**
 * Append the single source polls onto the destination.
 *
 * @param source
 *   The source polls to append.
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
#ifndef _di_f_pollss_append_
  extern f_status_t f_pollss_append(const f_polls_t source, f_pollss_t * const destination);
#endif // _di_f_pollss_append_

/**
 * Append the source pollss onto the destination.
 *
 * @param source
 *   The source pollss to append.
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
#ifndef _di_f_pollss_append_all_
  extern f_status_t f_pollss_append_all(const f_pollss_t source, f_pollss_t * const destination);
#endif // _di_f_pollss_append_all_

/**
 * Resize the string pollss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param pollss
 *   The string pollss array to resize.
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
#ifndef _di_f_pollss_decimate_by_
  extern f_status_t f_pollss_decimate_by(const f_number_unsigned_t amount, f_pollss_t * const pollss);
#endif // _di_f_pollss_decimate_by_

/**
 * Resize the string pollss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param pollss
 *   The string pollss array to resize.
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
#ifndef _di_f_pollss_decrease_by_
  extern f_status_t f_pollss_decrease_by(const f_number_unsigned_t amount, f_pollss_t * const pollss);
#endif // _di_f_pollss_decrease_by_

/**
 * Increase the size of the string pollss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param pollss
 *   The string pollss array to resize.
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
#ifndef _di_f_pollss_increase_
  extern f_status_t f_pollss_increase(const f_number_unsigned_t step, f_pollss_t * const pollss);
#endif // _di_f_pollss_increase_

/**
 * Resize the string pollss array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param pollss
 *   The string pollss array to resize.
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
#ifndef _di_f_pollss_increase_by_
  extern f_status_t f_pollss_increase_by(const f_number_unsigned_t amount, f_pollss_t * const pollss);
#endif // _di_f_pollss_increase_by_

/**
 * Resize the string pollss array.
 *
 * @param length
 *   The new size to use.
 * @param pollss
 *   The string pollss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_pollss_resize_
  extern f_status_t f_pollss_resize(const f_number_unsigned_t length, f_pollss_t * const pollss);
#endif // _di_f_pollss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_poll_h
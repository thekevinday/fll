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
#ifndef _F_type_array_status_h
#define _F_type_array_status_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the string statuss array.
 *
 * @param length
 *   The new size to use.
 * @param statuss
 *   The string statuss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_statuss_adjust_
  extern f_status_t f_statuss_adjust(const f_array_length_t length, f_statuss_t *statuss);
#endif // _di_f_statuss_adjust_

/**
 * Append the source statuss onto the destination.
 *
 * @param source
 *   The source statuss to append.
 * @param destination
 *   The destination statuss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statuss_append_
  extern f_status_t f_statuss_append(const f_statuss_t source, f_statuss_t *destination);
#endif // _di_f_statuss_append_

/**
 * Resize the string statuss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param statuss
 *   The string statuss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_statuss_decimate_by_
  extern f_status_t f_statuss_decimate_by(const f_array_length_t amount, f_statuss_t *statuss);
#endif // _di_f_statuss_decimate_by_

/**
 * Resize the string statuss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param statuss
 *   The string statuss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statuss_decrease_by_
  extern f_status_t f_statuss_decrease_by(const f_array_length_t amount, f_statuss_t *statuss);
#endif // _di_f_statuss_decrease_by_

/**
 * Increase the size of the string statuss array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param statuss
 *   The string statuss array to resize.
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
#ifndef _di_f_statuss_increase_
  extern f_status_t f_statuss_increase(const f_array_length_t step, f_statuss_t *statuss);
#endif // _di_f_statuss_increase_

/**
 * Resize the string statuss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param statuss
 *   The string statuss array to resize.
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
#ifndef _di_f_statuss_increase_by_
  extern f_status_t f_statuss_increase_by(const f_array_length_t amount, f_statuss_t *statuss);
#endif // _di_f_statuss_increase_by_

/**
 * Resize the string statuss array.
 *
 * @param length
 *   The new size to use.
 * @param statuss
 *   The string statuss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statuss_resize_
  extern f_status_t f_statuss_resize(const f_array_length_t length, f_statuss_t *statuss);
#endif // _di_f_statuss_resize_

/**
 * Resize the string statusss array.
 *
 * @param length
 *   The new size to use.
 * @param statusss
 *   The string statusss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_statusss_adjust_
  extern f_status_t f_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss);
#endif // _di_f_statusss_adjust_

/**
 * Append the source statusss onto the destination.
 *
 * @param source
 *   The source statusss to append.
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
#ifndef _di_f_statusss_append_
  extern f_status_t f_statusss_append(const f_statusss_t source, f_statusss_t *destination);
#endif // _di_f_statusss_append_

/**
 * Resize the string statusss array.
 *
 * @param length
 *   The new size to use.
 * @param statusss
 *   The string statusss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_statusss_adjust_
  extern f_status_t f_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss);
#endif // _di_f_statusss_adjust_

/**
 * Resize the string statusss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param statusss
 *   The string statusss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_statusss_decimate_by_
  extern f_status_t f_statusss_decimate_by(const f_array_length_t amount, f_statusss_t *statusss);
#endif // _di_f_statusss_decimate_by_

/**
 * Resize the string statusss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param statusss
 *   The string statusss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statusss_decrease_by_
  extern f_status_t f_statusss_decrease_by(const f_array_length_t amount, f_statusss_t *statusss);
#endif // _di_f_statusss_decrease_by_

/**
 * Increase the size of the string statusss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param statusss
 *   The string statusss array to resize.
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
#ifndef _di_f_statusss_increase_
  extern f_status_t f_statusss_increase(const f_array_length_t step, f_statusss_t *statusss);
#endif // _di_f_statusss_increase_

/**
 * Resize the string statusss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param statusss
 *   The string statusss array to resize.
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
#ifndef _di_f_statusss_increase_by_
  extern f_status_t f_statusss_increase_by(const f_array_length_t amount, f_statusss_t *statusss);
#endif // _di_f_statusss_increase_by_

/**
 * Resize the string statusss array.
 *
 * @param length
 *   The new size to use.
 * @param statusss
 *   The string statusss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statusss_resize_
  extern f_status_t f_statusss_resize(const f_array_length_t length, f_statusss_t *statusss);
#endif // _di_f_statusss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_status_h

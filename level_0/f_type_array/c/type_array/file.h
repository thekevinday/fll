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
#ifndef _F_type_array_file_h
#define _F_type_array_file_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the files array.
 *
 * @param length
 *   The new size to use.
 * @param files
 *   The files array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_files_adjust_
  extern f_status_t f_files_adjust(const f_number_unsigned_t length, f_files_t * const files);
#endif // _di_f_files_adjust_

/**
 * Append the single source file onto the destination.
 *
 * @param source
 *   The source file to append.
 * @param destination
 *   The destination files the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_files_append_
  extern f_status_t f_files_append(const f_file_t source, f_files_t * const destination);
#endif // _di_f_files_append_

/**
 * Append the source files onto the destination.
 *
 * @param source
 *   The source files to append.
 * @param destination
 *   The destination files the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_files_append_all_
  extern f_status_t f_files_append_all(const f_files_t source, f_files_t * const destination);
#endif // _di_f_files_append_all_

/**
 * Resize the files array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param files
 *   The files array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_files_decimate_by_
  extern f_status_t f_files_decimate_by(const f_number_unsigned_t amount, f_files_t * const files);
#endif // _di_f_files_decimate_by_

/**
 * Resize the files array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param files
 *   The files array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_files_decrease_by_
  extern f_status_t f_files_decrease_by(const f_number_unsigned_t amount, f_files_t * const files);
#endif // _di_f_files_decrease_by_

/**
 * Increase the size of the files array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param files
 *   The files array to resize.
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
#ifndef _di_f_files_increase_
  extern f_status_t f_files_increase(const f_number_unsigned_t step, f_files_t * const files);
#endif // _di_f_files_increase_

/**
 * Resize the files array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param files
 *   The files array to resize.
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
#ifndef _di_f_files_increase_by_
  extern f_status_t f_files_increase_by(const f_number_unsigned_t amount, f_files_t * const files);
#endif // _di_f_files_increase_by_

/**
 * Resize the files array.
 *
 * @param length
 *   The new size to use.
 * @param files
 *   The files array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_files_resize_
  extern f_status_t f_files_resize(const f_number_unsigned_t length, f_files_t * const files);
#endif // _di_f_files_resize_

/**
 * Resize the filess array.
 *
 * @param length
 *   The new size to use.
 * @param filess
 *   The filess array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_filess_adjust_
  extern f_status_t f_filess_adjust(const f_number_unsigned_t length, f_filess_t * const filess);
#endif // _di_f_filess_adjust_

/**
 * Append the single source files onto the destination.
 *
 * @param source
 *   The source files to append.
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
#ifndef _di_f_filess_append_
  extern f_status_t f_filess_append(const f_files_t source, f_filess_t * const destination);
#endif // _di_f_filess_append_

/**
 * Append the source filess onto the destination.
 *
 * @param source
 *   The source filess to append.
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
#ifndef _di_f_filess_append_all_
  extern f_status_t f_filess_append_all(const f_filess_t source, f_filess_t * const destination);
#endif // _di_f_filess_append_all_

/**
 * Resize the filess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param filess
 *   The filess array to resize.
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
#ifndef _di_f_filess_decimate_by_
  extern f_status_t f_filess_decimate_by(const f_number_unsigned_t amount, f_filess_t * const filess);
#endif // _di_f_filess_decimate_by_

/**
 * Resize the filess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param filess
 *   The filess array to resize.
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
#ifndef _di_f_filess_decrease_by_
  extern f_status_t f_filess_decrease_by(const f_number_unsigned_t amount, f_filess_t * const filess);
#endif // _di_f_filess_decrease_by_

/**
 * Increase the size of the filess array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param filess
 *   The filess array to resize.
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
#ifndef _di_f_filess_increase_
  extern f_status_t f_filess_increase(const f_number_unsigned_t step, f_filess_t * const filess);
#endif // _di_f_filess_increase_

/**
 * Resize the filess array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param filess
 *   The filess array to resize.
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
#ifndef _di_f_filess_increase_by_
  extern f_status_t f_filess_increase_by(const f_number_unsigned_t amount, f_filess_t * const filess);
#endif // _di_f_filess_increase_by_

/**
 * Resize the filess array.
 *
 * @param length
 *   The new size to use.
 * @param filess
 *   The filess array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_filess_resize_
  extern f_status_t f_filess_resize(const f_number_unsigned_t length, f_filess_t * const filess);
#endif // _di_f_filess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_file_h

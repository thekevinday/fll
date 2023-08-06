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
#ifndef _F_type_array_number_unsigned_h
#define _F_type_array_number_unsigned_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Append the single source number_unsigned onto the destination.
 *
 * @param source
 *   The source number_unsigned to append.
 * @param destination
 *   The destination number_unsigneds the source is appended onto.
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
#ifndef _di_f_number_unsigneds_append_
  extern f_status_t f_number_unsigneds_append(const f_number_unsigned_t source, f_number_unsigneds_t * const destination);
#endif // _di_f_number_unsigneds_append_

/**
 * Append the source number_unsigneds onto the destination.
 *
 * @param source
 *   The source number_unsigneds to append.
 * @param destination
 *   The destination number_unsigneds the source is appended onto.
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
#ifndef _di_f_number_unsigneds_append_all_
  extern f_status_t f_number_unsigneds_append_all(const f_number_unsigneds_t source, f_number_unsigneds_t * const destination);
#endif // _di_f_number_unsigneds_append_all_

/**
 * Resize the string number_unsigneds array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The string number_unsigneds array to resize.
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
#ifndef _di_f_number_unsigneds_decimate_by_
  extern f_status_t f_number_unsigneds_decimate_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const structure);
#endif // _di_f_number_unsigneds_decimate_by_

/**
 * Resize the string number_unsigneds array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The string number_unsigneds array to resize.
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
#ifndef _di_f_number_unsigneds_decrease_by_
  extern f_status_t f_number_unsigneds_decrease_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const structure);
#endif // _di_f_number_unsigneds_decrease_by_

/**
 * Increase the size of the string number_unsigneds array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The string number_unsigneds array to resize.
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
#ifndef _di_f_number_unsigneds_increase_
  extern f_status_t f_number_unsigneds_increase(const f_number_unsigned_t step, f_number_unsigneds_t * const structure);
#endif // _di_f_number_unsigneds_increase_

/**
 * Resize the string number_unsigneds array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The string number_unsigneds array to resize.
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
#ifndef _di_f_number_unsigneds_increase_by_
  extern f_status_t f_number_unsigneds_increase_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const structure);
#endif // _di_f_number_unsigneds_increase_by_

/**
 * Resize the string number_unsignedss array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string number_unsignedss array to resize.
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
#ifndef _di_f_number_unsignedss_adjust_
  extern f_status_t f_number_unsignedss_adjust(const f_number_unsigned_t length, f_number_unsignedss_t * const structure);
#endif // _di_f_number_unsignedss_adjust_

/**
 * Append the single source number_unsigneds onto the destination.
 *
 * @param source
 *   The source number_unsigneds to append.
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
#ifndef _di_f_number_unsignedss_append_
  extern f_status_t f_number_unsignedss_append(const f_number_unsigneds_t source, f_number_unsignedss_t * const destination);
#endif // _di_f_number_unsignedss_append_

/**
 * Append the source number_unsignedss onto the destination.
 *
 * @param source
 *   The source number_unsignedss to append.
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
#ifndef _di_f_number_unsignedss_append_all_
  extern f_status_t f_number_unsignedss_append_all(const f_number_unsignedss_t source, f_number_unsignedss_t * const destination);
#endif // _di_f_number_unsignedss_append_all_

/**
 * Resize the string number_unsignedss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The string number_unsignedss array to resize.
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
#ifndef _di_f_number_unsignedss_decimate_by_
  extern f_status_t f_number_unsignedss_decimate_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const structure);
#endif // _di_f_number_unsignedss_decimate_by_

/**
 * Resize the string number_unsignedss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The string number_unsignedss array to resize.
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
#ifndef _di_f_number_unsignedss_decrease_by_
  extern f_status_t f_number_unsignedss_decrease_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const structure);
#endif // _di_f_number_unsignedss_decrease_by_

/**
 * Increase the size of the string number_unsignedss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The string number_unsignedss array to resize.
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
#ifndef _di_f_number_unsignedss_increase_
  extern f_status_t f_number_unsignedss_increase(const f_number_unsigned_t step, f_number_unsignedss_t * const structure);
#endif // _di_f_number_unsignedss_increase_

/**
 * Resize the string number_unsignedss array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The string number_unsignedss array to resize.
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
#ifndef _di_f_number_unsignedss_increase_by_
  extern f_status_t f_number_unsignedss_increase_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const structure);
#endif // _di_f_number_unsignedss_increase_by_

/**
 * Resize the string number_unsignedss array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string number_unsignedss array to adjust.
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
#ifndef _di_f_number_unsignedss_resize_
  extern f_status_t f_number_unsignedss_resize(const f_number_unsigned_t length, f_number_unsignedss_t * const structure);
#endif // _di_f_number_unsignedss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_number_unsigned_h

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
#ifndef _F_type_array_fll_id_h
#define _F_type_array_fll_id_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the string ids array.
 *
 * @param length
 *   The new size to use.
 * @param ids
 *   The string ids array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_fll_ids_adjust_
  extern f_status_t f_type_fll_ids_adjust(const f_array_length_t length, f_fll_ids_t *ids);
#endif // _di_f_type_fll_ids_adjust_

/**
 * Append the source ids onto the destination.
 *
 * @param source
 *   The source ids to append.
 * @param destination
 *   The destination ids the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_fll_ids_append_
  extern f_status_t f_type_fll_ids_append(const f_fll_ids_t source, f_fll_ids_t *destination);
#endif // _di_f_type_fll_ids_append_

/**
 * Resize the string ids array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param ids
 *   The string ids array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_fll_ids_decimate_by_
  extern f_status_t f_type_fll_ids_decimate_by(const f_array_length_t amount, f_fll_ids_t *ids);
#endif // _di_f_type_fll_ids_decimate_by_

/**
 * Resize the string ids array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param ids
 *   The string ids array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_fll_ids_decrease_by_
  extern f_status_t f_type_fll_ids_decrease_by(const f_array_length_t amount, f_fll_ids_t *ids);
#endif // _di_f_type_fll_ids_decrease_by_

/**
 * Increase the size of the string ids array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param ids
 *   The string ids array to resize.
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
#ifndef _di_f_type_fll_ids_increase_
  extern f_status_t f_type_fll_ids_increase(const uint16_t step, f_fll_ids_t *ids);
#endif // _di_f_type_fll_ids_increase_

/**
 * Resize the string ids array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param ids
 *   The string ids array to resize.
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
#ifndef _di_f_type_fll_ids_increase_by_
  extern f_status_t f_type_fll_ids_increase_by(const f_array_length_t amount, f_fll_ids_t *ids);
#endif // _di_f_type_fll_ids_increase_by_

/**
 * Resize the string ids array.
 *
 * @param length
 *   The new size to use.
 * @param ids
 *   The string ids array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_fll_ids_resize_
  extern f_status_t f_type_fll_ids_resize(const f_array_length_t length, f_fll_ids_t *ids);
#endif // _di_f_type_fll_ids_resize_

/**
 * Resize the string idss array.
 *
 * @param length
 *   The new size to use.
 * @param idss
 *   The string idss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_fll_idss_adjust_
  extern f_status_t f_type_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_adjust_

/**
 * Append the source idss onto the destination.
 *
 * @param source
 *   The source idss to append.
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
#ifndef _di_f_type_fll_idss_append_
  extern f_status_t f_type_fll_idss_append(const f_fll_idss_t source, f_fll_idss_t *destination);
#endif // _di_f_type_fll_idss_append_

/**
 * Resize the string idss array.
 *
 * @param length
 *   The new size to use.
 * @param idss
 *   The string idss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_fll_idss_adjust_
  extern f_status_t f_type_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_adjust_

/**
 * Resize the string idss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param idss
 *   The string idss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_fll_idss_decimate_by_
  extern f_status_t f_type_fll_idss_decimate_by(const f_array_length_t amount, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_decimate_by_

/**
 * Resize the string idss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param idss
 *   The string idss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_fll_idss_decrease_by_
  extern f_status_t f_type_fll_idss_decrease_by(const f_array_length_t amount, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_decrease_by_

/**
 * Increase the size of the string idss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param idss
 *   The string idss array to resize.
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
#ifndef _di_f_type_fll_idss_increase_
  extern f_status_t f_type_fll_idss_increase(const uint16_t step, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_increase_

/**
 * Resize the string idss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param idss
 *   The string idss array to resize.
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
#ifndef _di_f_type_fll_idss_increase_by_
  extern f_status_t f_type_fll_idss_increase_by(const f_array_length_t amount, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_increase_by_

/**
 * Resize the string idss array.
 *
 * @param length
 *   The new size to use.
 * @param idss
 *   The string idss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_fll_idss_resize_
  extern f_status_t f_type_fll_idss_resize(const f_array_length_t length, f_fll_idss_t *idss);
#endif // _di_f_type_fll_idss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_fll_id_h

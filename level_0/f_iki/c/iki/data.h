/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by iki related functionality.
 *
 * This is auto-included by iki.h and should not need to be explicitly included.
 */
#ifndef _F_iki_data_h
#define _F_iki_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Delete the IKI data.
 *
 * @param data
 *   The IKI data to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_array_lengths_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_array_lengths_resize()
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_iki_data_delete_
  extern f_status_t f_iki_data_delete(f_iki_data_t *data);
#endif // _di_f_iki_data_delete_

/**
 * Destroy the IKI data.
 *
 * @param data
 *   The IKI data to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_array_lengths_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_array_lengths_adjust()
 * @see f_string_ranges_adjust()
 */
#ifndef _di_f_iki_data_destroy_
  extern f_status_t f_iki_data_destroy(f_iki_data_t *data);
#endif // _di_f_iki_data_destroy_

/**
 * Resize the iki_datas array.
 *
 * @param length
 *   The new size to use.
 * @param iki_datas
 *   The iki_datas array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_iki_datas_adjust_
  extern f_status_t f_iki_datas_adjust(const f_array_length_t length, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_adjust_

/**
 * Append the single source iki_data onto the destination.
 *
 * @param source
 *   The source iki_data to append.
 * @param destination
 *   The destination iki_datas the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_append_
  extern f_status_t f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination);
#endif // _di_f_iki_datas_append_

/**
 * Append the source iki_datas onto the destination.
 *
 * @param source
 *   The source iki_datas to append.
 * @param destination
 *   The destination iki_datas the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_append_all_
  extern f_status_t f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t *destination);
#endif // _di_f_iki_datas_append_all_

/**
 * Resize the iki_datas array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param iki_datas
 *   The iki_datas array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_iki_datas_decimate_by_
  extern f_status_t f_iki_datas_decimate_by(const f_array_length_t amount, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_decimate_by_

/**
 * Resize the iki_datas array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param iki_datas
 *   The iki_datas array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_decrease_by_
  extern f_status_t f_iki_datas_decrease_by(const f_array_length_t amount, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_decrease_by_

/**
 * Increase the size of the iki_datas array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param iki_datas
 *   The iki_datas array to resize.
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
#ifndef _di_f_iki_datas_increase_
  extern f_status_t f_iki_datas_increase(const f_array_length_t step, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_increase_

/**
 * Resize the iki_datas array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param iki_datas
 *   The iki_datas array to resize.
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
#ifndef _di_f_iki_datas_increase_by_
  extern f_status_t f_iki_datas_increase_by(const f_array_length_t amount, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_increase_by_

/**
 * Resize the iki_datas array.
 *
 * @param length
 *   The new size to use.
 * @param iki_datas
 *   The iki_datas array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_resize_
  extern f_status_t f_iki_datas_resize(const f_array_length_t length, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_resize_

/**
 * Resize the iki_datass array.
 *
 * @param length
 *   The new size to use.
 * @param iki_datass
 *   The iki_datass array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_iki_datass_adjust_
  extern f_status_t f_iki_datass_adjust(const f_array_length_t length, f_iki_datass_t *datass);
#endif // _di_f_iki_datass_adjust_

/**
 * Append the single source iki_datas onto the destination.
 *
 * @param source
 *   The source iki_datas to append.
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
#ifndef _di_f_iki_datass_append_
  extern f_status_t f_iki_datass_append(const f_iki_datas_t source, f_iki_datass_t *destination);
#endif // _di_f_iki_datass_append_

/**
 * Append the source iki_datass onto the destination.
 *
 * @param source
 *   The source iki_datass to append.
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
#ifndef _di_f_iki_datass_append_all_
  extern f_status_t f_iki_datass_append_all(const f_iki_datass_t source, f_iki_datass_t *destination);
#endif // _di_f_iki_datass_append_all_

/**
 * Resize the iki_datass array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param iki_datass
 *   The iki_datass array to resize.
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
#ifndef _di_f_iki_datass_decimate_by_
  extern f_status_t f_iki_datass_decimate_by(const f_array_length_t amount, f_iki_datass_t *datass);
#endif // _di_f_iki_datass_decimate_by_

/**
 * Resize the iki_datass array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param iki_datass
 *   The iki_datass array to resize.
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
#ifndef _di_f_iki_datass_decrease_by_
  extern f_status_t f_iki_datass_decrease_by(const f_array_length_t amount, f_iki_datass_t *datass);
#endif // _di_f_iki_datass_decrease_by_

/**
 * Increase the size of the iki_datass array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param iki_datass
 *   The iki_datass array to resize.
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
#ifndef _di_f_iki_datass_increase_
  extern f_status_t f_iki_datass_increase(const f_array_length_t step, f_iki_datass_t *datass);
#endif // _di_f_iki_datass_increase_

/**
 * Resize the iki_datass array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param iki_datass
 *   The iki_datass array to resize.
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
#ifndef _di_f_iki_datass_increase_by_
  extern f_status_t f_iki_datass_increase_by(const f_array_length_t amount, f_iki_datass_t *datass);
#endif // _di_f_iki_datass_increase_by_

/**
 * Resize the iki_datass array.
 *
 * @param length
 *   The new size to use.
 * @param iki_datass
 *   The iki_datass array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datass_resize_
  extern f_status_t f_iki_datass_resize(const f_array_length_t length, f_iki_datass_t *datass);
#endif // _di_f_iki_datass_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_data_h

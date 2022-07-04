/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by type (array) related functionality.
 *
 * This is auto-included by type_array.h and should not need to be explicitly included.
 */
#ifndef _F_type_array_cell_h
#define _F_type_array_cell_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the string cells array.
 *
 * @param length
 *   The new size to use.
 * @param cells
 *   The string cells array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_cells_adjust_
  extern f_status_t f_cells_adjust(const f_array_length_t length, f_cells_t *cells);
#endif // _di_f_cells_adjust_

/**
 * Append the single source cell onto the destination.
 *
 * @param source
 *   The source cell to append.
 * @param destination
 *   The destination cells the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_cells_append_
  extern f_status_t f_cells_append(const f_cell_t source, f_cells_t *destination);
#endif // _di_f_cells_append_

/**
 * Append the source cells onto the destination.
 *
 * @param source
 *   The source cells to append.
 * @param destination
 *   The destination cells the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_cells_append_all_
  extern f_status_t f_cells_append_all(const f_cells_t source, f_cells_t *destination);
#endif // _di_f_cells_append_all_

/**
 * Resize the string cells array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param cells
 *   The string cells array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_cells_decimate_by_
  extern f_status_t f_cells_decimate_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_f_cells_decimate_by_

/**
 * Resize the string cells array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param cells
 *   The string cells array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_cells_decrease_by_
  extern f_status_t f_cells_decrease_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_f_cells_decrease_by_

/**
 * Increase the size of the string cells array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param cells
 *   The string cells array to resize.
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
#ifndef _di_f_cells_increase_
  extern f_status_t f_cells_increase(const f_array_length_t step, f_cells_t *cells);
#endif // _di_f_cells_increase_

/**
 * Resize the string cells array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param cells
 *   The string cells array to resize.
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
#ifndef _di_f_cells_increase_by_
  extern f_status_t f_cells_increase_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_f_cells_increase_by_

/**
 * Resize the string cells array.
 *
 * @param length
 *   The new size to use.
 * @param cells
 *   The string cells array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_cells_resize_
  extern f_status_t f_cells_resize(const f_array_length_t length, f_cells_t *cells);
#endif // _di_f_cells_resize_

/**
 * Resize the string cellss array.
 *
 * @param length
 *   The new size to use.
 * @param cellss
 *   The string cellss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_cellss_adjust_
  extern f_status_t f_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss);
#endif // _di_f_cellss_adjust_

/**
 * Append the single source cells onto the destination.
 *
 * @param source
 *   The source cells to append.
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
#ifndef _di_f_cellss_append_
  extern f_status_t f_cellss_append(const f_cells_t source, f_cellss_t *destination);
#endif // _di_f_cellss_append_

/**
 * Append the source cellss onto the destination.
 *
 * @param source
 *   The source cellss to append.
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
#ifndef _di_f_cellss_append_all_
  extern f_status_t f_cellss_append_all(const f_cellss_t source, f_cellss_t *destination);
#endif // _di_f_cellss_append_all_

/**
 * Resize the string cellss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param cellss
 *   The string cellss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_cellss_decimate_by_
  extern f_status_t f_cellss_decimate_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_f_cellss_decimate_by_

/**
 * Resize the string cellss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param cellss
 *   The string cellss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_cellss_decrease_by_
  extern f_status_t f_cellss_decrease_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_f_cellss_decrease_by_

/**
 * Increase the size of the string cellss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param cellss
 *   The string cellss array to resize.
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
#ifndef _di_f_cellss_increase_
  extern f_status_t f_cellss_increase(const f_array_length_t step, f_cellss_t *cellss);
#endif // _di_f_cellss_increase_

/**
 * Resize the string cellss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param cellss
 *   The string cellss array to resize.
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
#ifndef _di_f_cellss_increase_by_
  extern f_status_t f_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_f_cellss_increase_by_

/**
 * Resize the string cellss array.
 *
 * @param length
 *   The new size to use.
 * @param cellss
 *   The string cellss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_cellss_resize_
  extern f_status_t f_cellss_resize(const f_array_length_t length, f_cellss_t *cellss);
#endif // _di_f_cellss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_cell_h

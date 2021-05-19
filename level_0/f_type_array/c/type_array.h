/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides an extension to the Type project (f_type) that depends on f_memory (linking to the f_memory library).
 *
 * As an exceptional case, this is an extension to f_type to avoid circular dependency issues with f_memory.
 * The functions and macros in this project therefore are prefixed with 'f_type_' instead of 'f_type_array_'.
 */
#ifndef _F_type_array_h
#define _F_type_array_h

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/memory.h>

// fll-0 type_array includes
#include <fll/level_0/type_array-common.h>

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
#ifndef _di_f_type_cells_adjust_
  extern f_status_t f_type_cells_adjust(const f_array_length_t length, f_cells_t *cells);
#endif // _di_f_type_cells_adjust_

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
#ifndef _di_f_type_cells_append_
  extern f_status_t f_type_cells_append(const f_cells_t source, f_cells_t *destination);
#endif // _di_f_type_cells_append_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_cells_decimate_by_
  extern f_status_t f_type_cells_decimate_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_f_type_cells_decimate_by_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_cells_decrease_by_
  extern f_status_t f_type_cells_decrease_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_f_type_cells_decrease_by_

/**
 * Increase the size of the string cells array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
#ifndef _di_f_type_cells_increase_
  extern f_status_t f_type_cells_increase(const uint16_t step, f_cells_t *cells);
#endif // _di_f_type_cells_increase_

/**
 * Resize the string cells array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
#ifndef _di_f_type_cells_increase_by_
  extern f_status_t f_type_cells_increase_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_f_type_cells_increase_by_

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
#ifndef _di_f_type_cells_resize_
  extern f_status_t f_type_cells_resize(const f_array_length_t length, f_cells_t *cells);
#endif // _di_f_type_cells_resize_

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
#ifndef _di_f_type_cellss_adjust_
  extern f_status_t f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss);
#endif // _di_f_type_cellss_adjust_

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
#ifndef _di_f_type_cellss_append_
  extern f_status_t f_type_cellss_append(const f_cellss_t source, f_cellss_t *destination);
#endif // _di_f_type_cellss_append_

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
#ifndef _di_f_type_cellss_adjust_
  extern f_status_t f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss);
#endif // _di_f_type_cellss_adjust_

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
#ifndef _di_f_type_cellss_decimate_by_
  extern f_status_t f_type_cellss_decimate_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_f_type_cellss_decimate_by_

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
#ifndef _di_f_type_cellss_decrease_by_
  extern f_status_t f_type_cellss_decrease_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_f_type_cellss_decrease_by_

/**
 * Increase the size of the string cellss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
#ifndef _di_f_type_cellss_increase_
  extern f_status_t f_type_cellss_increase(const uint16_t step, f_cellss_t *cellss);
#endif // _di_f_type_cellss_increase_

/**
 * Resize the string cellss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
#ifndef _di_f_type_cellss_increase_by_
  extern f_status_t f_type_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_f_type_cellss_increase_by_

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
#ifndef _di_f_type_cellss_resize_
  extern f_status_t f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss);
#endif // _di_f_type_cellss_resize_

/**
 * Resize the string lengths array.
 *
 * @param length
 *   The new size to use.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_array_lengths_adjust_
  extern f_status_t f_type_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *lengths);
#endif // _di_f_type_array_lengths_adjust_

/**
 * Append the source lengths onto the destination.
 *
 * @param source
 *   The source lengths to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_array_lengths_append_
  extern f_status_t f_type_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination);
#endif // _di_f_type_array_lengths_append_

/**
 * Resize the string lengths array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_array_lengths_decimate_by_
  extern f_status_t f_type_array_lengths_decimate_by(const f_array_length_t amount, f_array_lengths_t *lengths);
#endif // _di_f_type_array_lengths_decimate_by_

/**
 * Resize the string lengths array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_array_lengths_decrease_by_
  extern f_status_t f_type_array_lengths_decrease_by(const f_array_length_t amount, f_array_lengths_t *lengths);
#endif // _di_f_type_array_lengths_decrease_by_

/**
 * Increase the size of the string lengths array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param lengths
 *   The string lengths array to resize.
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
#ifndef _di_f_type_array_lengths_increase_
  extern f_status_t f_type_array_lengths_increase(const uint16_t step, f_array_lengths_t *lengths);
#endif // _di_f_type_array_lengths_increase_

/**
 * Resize the string lengths array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param lengths
 *   The string lengths array to resize.
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
#ifndef _di_f_type_array_lengths_increase_by_
  extern f_status_t f_type_array_lengths_increase_by(const f_array_length_t amount, f_array_lengths_t *lengths);
#endif // _di_f_type_array_lengths_increase_by_

/**
 * Resize the string lengths array.
 *
 * @param length
 *   The new size to use.
 * @param lengths
 *   The string lengths array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_array_lengths_resize_
  extern f_status_t f_type_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths);
#endif // _di_f_type_array_lengths_resize_

/**
 * Resize the string lengthss array.
 *
 * @param length
 *   The new size to use.
 * @param lengthss
 *   The string lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_array_lengthss_adjust_
  extern f_status_t f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_adjust_

/**
 * Append the source lengthss onto the destination.
 *
 * @param source
 *   The source lengthss to append.
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
#ifndef _di_f_type_array_lengthss_append_
  extern f_status_t f_type_array_lengthss_append(const f_array_lengthss_t source, f_array_lengthss_t *destination);
#endif // _di_f_type_array_lengthss_append_

/**
 * Resize the string lengthss array.
 *
 * @param length
 *   The new size to use.
 * @param lengthss
 *   The string lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_array_lengthss_adjust_
  extern f_status_t f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_adjust_

/**
 * Resize the string lengthss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param lengthss
 *   The string lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_array_lengthss_decimate_by_
  extern f_status_t f_type_array_lengthss_decimate_by(const f_array_length_t amount, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_decimate_by_

/**
 * Resize the string lengthss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param lengthss
 *   The string lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_array_lengthss_decrease_by_
  extern f_status_t f_type_array_lengthss_decrease_by(const f_array_length_t amount, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_decrease_by_

/**
 * Increase the size of the string lengthss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param lengthss
 *   The string lengthss array to resize.
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
#ifndef _di_f_type_array_lengthss_increase_
  extern f_status_t f_type_array_lengthss_increase(const uint16_t step, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_increase_

/**
 * Resize the string lengthss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param lengthss
 *   The string lengthss array to resize.
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
#ifndef _di_f_type_array_lengthss_increase_by_
  extern f_status_t f_type_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_increase_by_

/**
 * Resize the string lengthss array.
 *
 * @param length
 *   The new size to use.
 * @param lengthss
 *   The string lengthss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_array_lengthss_resize_
  extern f_status_t f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss);
#endif // _di_f_type_array_lengthss_resize_

/**
 * Resize the string int8s array.
 *
 * @param length
 *   The new size to use.
 * @param int8s
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int8s_adjust_
  extern f_status_t f_type_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s);
#endif // _di_f_type_int8s_adjust_

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
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int8s_append_
  extern f_status_t f_type_int8s_append(const f_int8s_t source, f_int8s_t *destination);
#endif // _di_f_type_int8s_append_

/**
 * Resize the string int8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int8s
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int8s_decimate_by_
  extern f_status_t f_type_int8s_decimate_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_f_type_int8s_decimate_by_

/**
 * Resize the string int8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int8s
 *   The string int8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int8s_decrease_by_
  extern f_status_t f_type_int8s_decrease_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_f_type_int8s_decrease_by_

/**
 * Increase the size of the string int8s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int8s
 *   The string int8s array to resize.
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
#ifndef _di_f_type_int8s_increase_
  extern f_status_t f_type_int8s_increase(const uint16_t step, f_int8s_t *int8s);
#endif // _di_f_type_int8s_increase_

/**
 * Resize the string int8s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int8s
 *   The string int8s array to resize.
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
#ifndef _di_f_type_int8s_increase_by_
  extern f_status_t f_type_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_f_type_int8s_increase_by_

/**
 * Resize the string int8s array.
 *
 * @param length
 *   The new size to use.
 * @param int8s
 *   The string int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int8s_resize_
  extern f_status_t f_type_int8s_resize(const f_array_length_t length, f_int8s_t *int8s);
#endif // _di_f_type_int8s_resize_

/**
 * Resize the string int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param int8ss
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int8ss_adjust_
  extern f_status_t f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_adjust_

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
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int8ss_append_
  extern f_status_t f_type_int8ss_append(const f_int8ss_t source, f_int8ss_t *destination);
#endif // _di_f_type_int8ss_append_

/**
 * Resize the string int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param int8ss
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int8ss_adjust_
  extern f_status_t f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_adjust_

/**
 * Resize the string int8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int8ss
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int8ss_decimate_by_
  extern f_status_t f_type_int8ss_decimate_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_decimate_by_

/**
 * Resize the string int8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int8ss
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int8ss_decrease_by_
  extern f_status_t f_type_int8ss_decrease_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_decrease_by_

/**
 * Increase the size of the string int8ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int8ss
 *   The string int8ss array to resize.
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
#ifndef _di_f_type_int8ss_increase_
  extern f_status_t f_type_int8ss_increase(const uint16_t step, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_increase_

/**
 * Resize the string int8ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int8ss
 *   The string int8ss array to resize.
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
#ifndef _di_f_type_int8ss_increase_by_
  extern f_status_t f_type_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_increase_by_

/**
 * Resize the string int8ss array.
 *
 * @param length
 *   The new size to use.
 * @param int8ss
 *   The string int8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int8ss_resize_
  extern f_status_t f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_resize_

/**
 * Resize the string uint8s array.
 *
 * @param length
 *   The new size to use.
 * @param uint8s
 *   The string uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint8s_adjust_
  extern f_status_t f_type_uint8s_adjust(const f_array_length_t length, f_uint8s_t *uint8s);
#endif // _di_f_type_uint8s_adjust_

/**
 * Append the source uint8s onto the destination.
 *
 * @param source
 *   The source uint8s to append.
 * @param destination
 *   The destination uint8s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint8s_append_
  extern f_status_t f_type_uint8s_append(const f_uint8s_t source, f_uint8s_t *destination);
#endif // _di_f_type_uint8s_append_

/**
 * Resize the string uint8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint8s
 *   The string uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint8s_decimate_by_
  extern f_status_t f_type_uint8s_decimate_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_f_type_uint8s_decimate_by_

/**
 * Resize the string uint8s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint8s
 *   The string uint8s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint8s_decrease_by_
  extern f_status_t f_type_uint8s_decrease_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_f_type_uint8s_decrease_by_

/**
 * Increase the size of the string uint8s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint8s
 *   The string uint8s array to resize.
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
#ifndef _di_f_type_uint8s_increase_
  extern f_status_t f_type_uint8s_increase(const uint16_t step, f_uint8s_t *uint8s);
#endif // _di_f_type_uint8s_increase_

/**
 * Resize the string uint8s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint8s
 *   The string uint8s array to resize.
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
#ifndef _di_f_type_uint8s_increase_by_
  extern f_status_t f_type_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_f_type_uint8s_increase_by_

/**
 * Resize the string uint8s array.
 *
 * @param length
 *   The new size to use.
 * @param uint8s
 *   The string uint8s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint8s_resize_
  extern f_status_t f_type_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s);
#endif // _di_f_type_uint8s_resize_

/**
 * Resize the string uint8ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint8ss_adjust_
  extern f_status_t f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_adjust_

/**
 * Append the source uint8ss onto the destination.
 *
 * @param source
 *   The source uint8ss to append.
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
#ifndef _di_f_type_uint8ss_append_
  extern f_status_t f_type_uint8ss_append(const f_uint8ss_t source, f_uint8ss_t *destination);
#endif // _di_f_type_uint8ss_append_

/**
 * Resize the string uint8ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint8ss_adjust_
  extern f_status_t f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_adjust_

/**
 * Resize the string uint8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint8ss_decimate_by_
  extern f_status_t f_type_uint8ss_decimate_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_decimate_by_

/**
 * Resize the string uint8ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint8ss_decrease_by_
  extern f_status_t f_type_uint8ss_decrease_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_decrease_by_

/**
 * Increase the size of the string uint8ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint8ss
 *   The string uint8ss array to resize.
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
#ifndef _di_f_type_uint8ss_increase_
  extern f_status_t f_type_uint8ss_increase(const uint16_t step, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_increase_

/**
 * Resize the string uint8ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint8ss
 *   The string uint8ss array to resize.
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
#ifndef _di_f_type_uint8ss_increase_by_
  extern f_status_t f_type_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_increase_by_

/**
 * Resize the string uint8ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint8ss
 *   The string uint8ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint8ss_resize_
  extern f_status_t f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_resize_

/**
 * Resize the string int16s array.
 *
 * @param length
 *   The new size to use.
 * @param int16s
 *   The string int16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int16s_adjust_
  extern f_status_t f_type_int16s_adjust(const f_array_length_t length, f_int16s_t *int16s);
#endif // _di_f_type_int16s_adjust_

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
#ifndef _di_f_type_int16s_append_
  extern f_status_t f_type_int16s_append(const f_int16s_t source, f_int16s_t *destination);
#endif // _di_f_type_int16s_append_

/**
 * Resize the string int16s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int16s
 *   The string int16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int16s_decimate_by_
  extern f_status_t f_type_int16s_decimate_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_f_type_int16s_decimate_by_

/**
 * Resize the string int16s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int16s
 *   The string int16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int16s_decrease_by_
  extern f_status_t f_type_int16s_decrease_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_f_type_int16s_decrease_by_

/**
 * Increase the size of the string int16s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int16s
 *   The string int16s array to resize.
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
#ifndef _di_f_type_int16s_increase_
  extern f_status_t f_type_int16s_increase(const uint16_t step, f_int16s_t *int16s);
#endif // _di_f_type_int16s_increase_

/**
 * Resize the string int16s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int16s
 *   The string int16s array to resize.
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
#ifndef _di_f_type_int16s_increase_by_
  extern f_status_t f_type_int16s_increase_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_f_type_int16s_increase_by_

/**
 * Resize the string int16s array.
 *
 * @param length
 *   The new size to use.
 * @param int16s
 *   The string int16s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int16s_resize_
  extern f_status_t f_type_int16s_resize(const f_array_length_t length, f_int16s_t *int16s);
#endif // _di_f_type_int16s_resize_

/**
 * Resize the string int16ss array.
 *
 * @param length
 *   The new size to use.
 * @param int16ss
 *   The string int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int16ss_adjust_
  extern f_status_t f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_adjust_

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
#ifndef _di_f_type_int16ss_append_
  extern f_status_t f_type_int16ss_append(const f_int16ss_t source, f_int16ss_t *destination);
#endif // _di_f_type_int16ss_append_

/**
 * Resize the string int16ss array.
 *
 * @param length
 *   The new size to use.
 * @param int16ss
 *   The string int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int16ss_adjust_
  extern f_status_t f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_adjust_

/**
 * Resize the string int16ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int16ss
 *   The string int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int16ss_decimate_by_
  extern f_status_t f_type_int16ss_decimate_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_decimate_by_

/**
 * Resize the string int16ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int16ss
 *   The string int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int16ss_decrease_by_
  extern f_status_t f_type_int16ss_decrease_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_decrease_by_

/**
 * Increase the size of the string int16ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int16ss
 *   The string int16ss array to resize.
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
#ifndef _di_f_type_int16ss_increase_
  extern f_status_t f_type_int16ss_increase(const uint16_t step, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_increase_

/**
 * Resize the string int16ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int16ss
 *   The string int16ss array to resize.
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
#ifndef _di_f_type_int16ss_increase_by_
  extern f_status_t f_type_int16ss_increase_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_increase_by_

/**
 * Resize the string int16ss array.
 *
 * @param length
 *   The new size to use.
 * @param int16ss
 *   The string int16ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int16ss_resize_
  extern f_status_t f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_resize_

/**
 * Resize the string uint16s array.
 *
 * @param length
 *   The new size to use.
 * @param uint16s
 *   The string uint16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint16s_adjust_
  extern f_status_t f_type_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s);
#endif // _di_f_type_uint16s_adjust_

/**
 * Append the source uint16s onto the destination.
 *
 * @param source
 *   The source uint16s to append.
 * @param destination
 *   The destination uint16s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint16s_append_
  extern f_status_t f_type_uint16s_append(const f_uint16s_t source, f_uint16s_t *destination);
#endif // _di_f_type_uint16s_append_

/**
 * Resize the string uint16s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint16s
 *   The string uint16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint16s_decimate_by_
  extern f_status_t f_type_uint16s_decimate_by(const f_array_length_t amount, f_uint16s_t *uint16s);
#endif // _di_f_type_uint16s_decimate_by_

/**
 * Resize the string uint16s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint16s
 *   The string uint16s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint16s_decrease_by_
  extern f_status_t f_type_uint16s_decrease_by(const f_array_length_t amount, f_uint16s_t *uint16s);
#endif // _di_f_type_uint16s_decrease_by_

/**
 * Increase the size of the string uint16s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint16s
 *   The string uint16s array to resize.
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
#ifndef _di_f_type_uint16s_increase_
  extern f_status_t f_type_uint16s_increase(const uint16_t step, f_uint16s_t *uint16s);
#endif // _di_f_type_uint16s_increase_

/**
 * Resize the string uint16s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint16s
 *   The string uint16s array to resize.
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
#ifndef _di_f_type_uint16s_increase_by_
  extern f_status_t f_type_uint16s_increase_by(const f_array_length_t amount, f_uint16s_t *uint16s);
#endif // _di_f_type_uint16s_increase_by_

/**
 * Resize the string uint16s array.
 *
 * @param length
 *   The new size to use.
 * @param uint16s
 *   The string uint16s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint16s_resize_
  extern f_status_t f_type_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s);
#endif // _di_f_type_uint16s_resize_

/**
 * Resize the string uint16ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint16ss
 *   The string uint16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint16ss_adjust_
  extern f_status_t f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_adjust_

/**
 * Append the source uint16ss onto the destination.
 *
 * @param source
 *   The source uint16ss to append.
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
#ifndef _di_f_type_uint16ss_append_
  extern f_status_t f_type_uint16ss_append(const f_uint16ss_t source, f_uint16ss_t *destination);
#endif // _di_f_type_uint16ss_append_

/**
 * Resize the string uint16ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint16ss
 *   The string uint16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint16ss_adjust_
  extern f_status_t f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_adjust_

/**
 * Resize the string uint16ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint16ss
 *   The string uint16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint16ss_decimate_by_
  extern f_status_t f_type_uint16ss_decimate_by(const f_array_length_t amount, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_decimate_by_

/**
 * Resize the string uint16ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint16ss
 *   The string uint16ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint16ss_decrease_by_
  extern f_status_t f_type_uint16ss_decrease_by(const f_array_length_t amount, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_decrease_by_

/**
 * Increase the size of the string uint16ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint16ss
 *   The string uint16ss array to resize.
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
#ifndef _di_f_type_uint16ss_increase_
  extern f_status_t f_type_uint16ss_increase(const uint16_t step, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_increase_

/**
 * Resize the string uint16ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint16ss
 *   The string uint16ss array to resize.
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
#ifndef _di_f_type_uint16ss_increase_by_
  extern f_status_t f_type_uint16ss_increase_by(const f_array_length_t amount, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_increase_by_

/**
 * Resize the string uint16ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint16ss
 *   The string uint16ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint16ss_resize_
  extern f_status_t f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_resize_

/**
 * Resize the string int32s array.
 *
 * @param length
 *   The new size to use.
 * @param int32s
 *   The string int32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int32s_adjust_
  extern f_status_t f_type_int32s_adjust(const f_array_length_t length, f_int32s_t *int32s);
#endif // _di_f_type_int32s_adjust_

/**
 * Append the source int32s onto the destination.
 *
 * @param source
 *   The source int32s to append.
 * @param destination
 *   The destination int32s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int32s_append_
  extern f_status_t f_type_int32s_append(const f_int32s_t source, f_int32s_t *destination);
#endif // _di_f_type_int32s_append_

/**
 * Resize the string int32s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int32s
 *   The string int32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int32s_decimate_by_
  extern f_status_t f_type_int32s_decimate_by(const f_array_length_t amount, f_int32s_t *int32s);
#endif // _di_f_type_int32s_decimate_by_

/**
 * Resize the string int32s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int32s
 *   The string int32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int32s_decrease_by_
  extern f_status_t f_type_int32s_decrease_by(const f_array_length_t amount, f_int32s_t *int32s);
#endif // _di_f_type_int32s_decrease_by_

/**
 * Increase the size of the string int32s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int32s
 *   The string int32s array to resize.
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
#ifndef _di_f_type_int32s_increase_
  extern f_status_t f_type_int32s_increase(const uint16_t step, f_int32s_t *int32s);
#endif // _di_f_type_int32s_increase_

/**
 * Resize the string int32s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int32s
 *   The string int32s array to resize.
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
#ifndef _di_f_type_int32s_increase_by_
  extern f_status_t f_type_int32s_increase_by(const f_array_length_t amount, f_int32s_t *int32s);
#endif // _di_f_type_int32s_increase_by_

/**
 * Resize the string int32s array.
 *
 * @param length
 *   The new size to use.
 * @param int32s
 *   The string int32s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int32s_resize_
  extern f_status_t f_type_int32s_resize(const f_array_length_t length, f_int32s_t *int32s);
#endif // _di_f_type_int32s_resize_

/**
 * Resize the string int32ss array.
 *
 * @param length
 *   The new size to use.
 * @param int32ss
 *   The string int32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int32ss_adjust_
  extern f_status_t f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_adjust_

/**
 * Append the source int32ss onto the destination.
 *
 * @param source
 *   The source int32ss to append.
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
#ifndef _di_f_type_int32ss_append_
  extern f_status_t f_type_int32ss_append(const f_int32ss_t source, f_int32ss_t *destination);
#endif // _di_f_type_int32ss_append_

/**
 * Resize the string int32ss array.
 *
 * @param length
 *   The new size to use.
 * @param int32ss
 *   The string int32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int32ss_adjust_
  extern f_status_t f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_adjust_

/**
 * Resize the string int32ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int32ss
 *   The string int32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int32ss_decimate_by_
  extern f_status_t f_type_int32ss_decimate_by(const f_array_length_t amount, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_decimate_by_

/**
 * Resize the string int32ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int32ss
 *   The string int32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int32ss_decrease_by_
  extern f_status_t f_type_int32ss_decrease_by(const f_array_length_t amount, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_decrease_by_

/**
 * Increase the size of the string int32ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int32ss
 *   The string int32ss array to resize.
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
#ifndef _di_f_type_int32ss_increase_
  extern f_status_t f_type_int32ss_increase(const uint16_t step, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_increase_

/**
 * Resize the string int32ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int32ss
 *   The string int32ss array to resize.
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
#ifndef _di_f_type_int32ss_increase_by_
  extern f_status_t f_type_int32ss_increase_by(const f_array_length_t amount, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_increase_by_

/**
 * Resize the string int32ss array.
 *
 * @param length
 *   The new size to use.
 * @param int32ss
 *   The string int32ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int32ss_resize_
  extern f_status_t f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_resize_

/**
 * Resize the string uint32s array.
 *
 * @param length
 *   The new size to use.
 * @param uint32s
 *   The string uint32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint32s_adjust_
  extern f_status_t f_type_uint32s_adjust(const f_array_length_t length, f_uint32s_t *uint32s);
#endif // _di_f_type_uint32s_adjust_

/**
 * Append the source uint32s onto the destination.
 *
 * @param source
 *   The source uint32s to append.
 * @param destination
 *   The destination uint32s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint32s_append_
  extern f_status_t f_type_uint32s_append(const f_uint32s_t source, f_uint32s_t *destination);
#endif // _di_f_type_uint32s_append_

/**
 * Resize the string uint32s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint32s
 *   The string uint32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint32s_decimate_by_
  extern f_status_t f_type_uint32s_decimate_by(const f_array_length_t amount, f_uint32s_t *uint32s);
#endif // _di_f_type_uint32s_decimate_by_

/**
 * Resize the string uint32s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint32s
 *   The string uint32s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint32s_decrease_by_
  extern f_status_t f_type_uint32s_decrease_by(const f_array_length_t amount, f_uint32s_t *uint32s);
#endif // _di_f_type_uint32s_decrease_by_

/**
 * Increase the size of the string uint32s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint32s
 *   The string uint32s array to resize.
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
#ifndef _di_f_type_uint32s_increase_
  extern f_status_t f_type_uint32s_increase(const uint16_t step, f_uint32s_t *uint32s);
#endif // _di_f_type_uint32s_increase_

/**
 * Resize the string uint32s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint32s
 *   The string uint32s array to resize.
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
#ifndef _di_f_type_uint32s_increase_by_
  extern f_status_t f_type_uint32s_increase_by(const f_array_length_t amount, f_uint32s_t *uint32s);
#endif // _di_f_type_uint32s_increase_by_

/**
 * Resize the string uint32s array.
 *
 * @param length
 *   The new size to use.
 * @param uint32s
 *   The string uint32s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint32s_resize_
  extern f_status_t f_type_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s);
#endif // _di_f_type_uint32s_resize_

/**
 * Resize the string uint32ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint32ss
 *   The string uint32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint32ss_adjust_
  extern f_status_t f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_adjust_

/**
 * Append the source uint32ss onto the destination.
 *
 * @param source
 *   The source uint32ss to append.
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
#ifndef _di_f_type_uint32ss_append_
  extern f_status_t f_type_uint32ss_append(const f_uint32ss_t source, f_uint32ss_t *destination);
#endif // _di_f_type_uint32ss_append_

/**
 * Resize the string uint32ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint32ss
 *   The string uint32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint32ss_adjust_
  extern f_status_t f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_adjust_

/**
 * Resize the string uint32ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint32ss
 *   The string uint32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint32ss_decimate_by_
  extern f_status_t f_type_uint32ss_decimate_by(const f_array_length_t amount, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_decimate_by_

/**
 * Resize the string uint32ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint32ss
 *   The string uint32ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint32ss_decrease_by_
  extern f_status_t f_type_uint32ss_decrease_by(const f_array_length_t amount, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_decrease_by_

/**
 * Increase the size of the string uint32ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint32ss
 *   The string uint32ss array to resize.
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
#ifndef _di_f_type_uint32ss_increase_
  extern f_status_t f_type_uint32ss_increase(const uint16_t step, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_increase_

/**
 * Resize the string uint32ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint32ss
 *   The string uint32ss array to resize.
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
#ifndef _di_f_type_uint32ss_increase_by_
  extern f_status_t f_type_uint32ss_increase_by(const f_array_length_t amount, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_increase_by_

/**
 * Resize the string uint32ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint32ss
 *   The string uint32ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint32ss_resize_
  extern f_status_t f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_resize_

/**
 * Resize the string int64s array.
 *
 * @param length
 *   The new size to use.
 * @param int64s
 *   The string int64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int64s_adjust_
  extern f_status_t f_type_int64s_adjust(const f_array_length_t length, f_int64s_t *int64s);
#endif // _di_f_type_int64s_adjust_

/**
 * Append the source int64s onto the destination.
 *
 * @param source
 *   The source int64s to append.
 * @param destination
 *   The destination int64s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int64s_append_
  extern f_status_t f_type_int64s_append(const f_int64s_t source, f_int64s_t *destination);
#endif // _di_f_type_int64s_append_

/**
 * Resize the string int64s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int64s
 *   The string int64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_int64s_decimate_by_
  extern f_status_t f_type_int64s_decimate_by(const f_array_length_t amount, f_int64s_t *int64s);
#endif // _di_f_type_int64s_decimate_by_

/**
 * Resize the string int64s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int64s
 *   The string int64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int64s_decrease_by_
  extern f_status_t f_type_int64s_decrease_by(const f_array_length_t amount, f_int64s_t *int64s);
#endif // _di_f_type_int64s_decrease_by_

/**
 * Increase the size of the string int64s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int64s
 *   The string int64s array to resize.
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
#ifndef _di_f_type_int64s_increase_
  extern f_status_t f_type_int64s_increase(const uint16_t step, f_int64s_t *int64s);
#endif // _di_f_type_int64s_increase_

/**
 * Resize the string int64s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int64s
 *   The string int64s array to resize.
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
#ifndef _di_f_type_int64s_increase_by_
  extern f_status_t f_type_int64s_increase_by(const f_array_length_t amount, f_int64s_t *int64s);
#endif // _di_f_type_int64s_increase_by_

/**
 * Resize the string int64s array.
 *
 * @param length
 *   The new size to use.
 * @param int64s
 *   The string int64s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int64s_resize_
  extern f_status_t f_type_int64s_resize(const f_array_length_t length, f_int64s_t *int64s);
#endif // _di_f_type_int64s_resize_

/**
 * Resize the string int64ss array.
 *
 * @param length
 *   The new size to use.
 * @param int64ss
 *   The string int64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int64ss_adjust_
  extern f_status_t f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_adjust_

/**
 * Append the source int64ss onto the destination.
 *
 * @param source
 *   The source int64ss to append.
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
#ifndef _di_f_type_int64ss_append_
  extern f_status_t f_type_int64ss_append(const f_int64ss_t source, f_int64ss_t *destination);
#endif // _di_f_type_int64ss_append_

/**
 * Resize the string int64ss array.
 *
 * @param length
 *   The new size to use.
 * @param int64ss
 *   The string int64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int64ss_adjust_
  extern f_status_t f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_adjust_

/**
 * Resize the string int64ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int64ss
 *   The string int64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_int64ss_decimate_by_
  extern f_status_t f_type_int64ss_decimate_by(const f_array_length_t amount, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_decimate_by_

/**
 * Resize the string int64ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int64ss
 *   The string int64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int64ss_decrease_by_
  extern f_status_t f_type_int64ss_decrease_by(const f_array_length_t amount, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_decrease_by_

/**
 * Increase the size of the string int64ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int64ss
 *   The string int64ss array to resize.
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
#ifndef _di_f_type_int64ss_increase_
  extern f_status_t f_type_int64ss_increase(const uint16_t step, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_increase_

/**
 * Resize the string int64ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int64ss
 *   The string int64ss array to resize.
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
#ifndef _di_f_type_int64ss_increase_by_
  extern f_status_t f_type_int64ss_increase_by(const f_array_length_t amount, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_increase_by_

/**
 * Resize the string int64ss array.
 *
 * @param length
 *   The new size to use.
 * @param int64ss
 *   The string int64ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_int64ss_resize_
  extern f_status_t f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_resize_

/**
 * Resize the string uint64s array.
 *
 * @param length
 *   The new size to use.
 * @param uint64s
 *   The string uint64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint64s_adjust_
  extern f_status_t f_type_uint64s_adjust(const f_array_length_t length, f_uint64s_t *uint64s);
#endif // _di_f_type_uint64s_adjust_

/**
 * Append the source uint64s onto the destination.
 *
 * @param source
 *   The source uint64s to append.
 * @param destination
 *   The destination uint64s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint64s_append_
  extern f_status_t f_type_uint64s_append(const f_uint64s_t source, f_uint64s_t *destination);
#endif // _di_f_type_uint64s_append_

/**
 * Resize the string uint64s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint64s
 *   The string uint64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_type_uint64s_decimate_by_
  extern f_status_t f_type_uint64s_decimate_by(const f_array_length_t amount, f_uint64s_t *uint64s);
#endif // _di_f_type_uint64s_decimate_by_

/**
 * Resize the string uint64s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint64s
 *   The string uint64s array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint64s_decrease_by_
  extern f_status_t f_type_uint64s_decrease_by(const f_array_length_t amount, f_uint64s_t *uint64s);
#endif // _di_f_type_uint64s_decrease_by_

/**
 * Increase the size of the string uint64s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint64s
 *   The string uint64s array to resize.
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
#ifndef _di_f_type_uint64s_increase_
  extern f_status_t f_type_uint64s_increase(const uint16_t step, f_uint64s_t *uint64s);
#endif // _di_f_type_uint64s_increase_

/**
 * Resize the string uint64s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint64s
 *   The string uint64s array to resize.
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
#ifndef _di_f_type_uint64s_increase_by_
  extern f_status_t f_type_uint64s_increase_by(const f_array_length_t amount, f_uint64s_t *uint64s);
#endif // _di_f_type_uint64s_increase_by_

/**
 * Resize the string uint64s array.
 *
 * @param length
 *   The new size to use.
 * @param uint64s
 *   The string uint64s array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint64s_resize_
  extern f_status_t f_type_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s);
#endif // _di_f_type_uint64s_resize_

/**
 * Resize the string uint64ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint64ss
 *   The string uint64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint64ss_adjust_
  extern f_status_t f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_adjust_

/**
 * Append the source uint64ss onto the destination.
 *
 * @param source
 *   The source uint64ss to append.
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
#ifndef _di_f_type_uint64ss_append_
  extern f_status_t f_type_uint64ss_append(const f_uint64ss_t source, f_uint64ss_t *destination);
#endif // _di_f_type_uint64ss_append_

/**
 * Resize the string uint64ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint64ss
 *   The string uint64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint64ss_adjust_
  extern f_status_t f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_adjust_

/**
 * Resize the string uint64ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param uint64ss
 *   The string uint64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_type_uint64ss_decimate_by_
  extern f_status_t f_type_uint64ss_decimate_by(const f_array_length_t amount, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_decimate_by_

/**
 * Resize the string uint64ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param uint64ss
 *   The string uint64ss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint64ss_decrease_by_
  extern f_status_t f_type_uint64ss_decrease_by(const f_array_length_t amount, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_decrease_by_

/**
 * Increase the size of the string uint64ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param uint64ss
 *   The string uint64ss array to resize.
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
#ifndef _di_f_type_uint64ss_increase_
  extern f_status_t f_type_uint64ss_increase(const uint16_t step, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_increase_

/**
 * Resize the string uint64ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param uint64ss
 *   The string uint64ss array to resize.
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
#ifndef _di_f_type_uint64ss_increase_by_
  extern f_status_t f_type_uint64ss_increase_by(const f_array_length_t amount, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_increase_by_

/**
 * Resize the string uint64ss array.
 *
 * @param length
 *   The new size to use.
 * @param uint64ss
 *   The string uint64ss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_type_uint64ss_resize_
  extern f_status_t f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_resize_

/**
 * Resize the string int128s array.
 *
 * @param length
 *   The new size to use.
 * @param int128s
 *   The string int128s array to resize.
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
 * Resize the string int128s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int128s
 *   The string int128s array to resize.
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
 * Resize the string int128s array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int128s
 *   The string int128s array to resize.
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
 * Increase the size of the string int128s array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int128s
 *   The string int128s array to resize.
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
 * Resize the string int128s array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int128s
 *   The string int128s array to resize.
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
 * Resize the string int128s array.
 *
 * @param length
 *   The new size to use.
 * @param int128s
 *   The string int128s array to adjust.
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
 * Resize the string int128ss array.
 *
 * @param length
 *   The new size to use.
 * @param int128ss
 *   The string int128ss array to resize.
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
 * Resize the string int128ss array.
 *
 * @param length
 *   The new size to use.
 * @param int128ss
 *   The string int128ss array to resize.
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
 * Resize the string int128ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param int128ss
 *   The string int128ss array to resize.
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
 * Resize the string int128ss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param int128ss
 *   The string int128ss array to resize.
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
 * Increase the size of the string int128ss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param int128ss
 *   The string int128ss array to resize.
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
 * Resize the string int128ss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param int128ss
 *   The string int128ss array to resize.
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
 * Resize the string int128ss array.
 *
 * @param length
 *   The new size to use.
 * @param int128ss
 *   The string int128ss array to adjust.
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
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
 *   F_memory_not (with error bit) on out of memory.
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

#endif // _F_type_array_h

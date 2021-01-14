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
#include <level_0/type.h>
#include <level_0/memory.h>

// fll-0 type_array includes
#include <level_0/type_array-common.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param cellss
 *   The string cellss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_cellss_increase_
  extern f_status_t f_type_cellss_increase(f_cellss_t *cellss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_cellss_resize_
  extern f_status_t f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss);
#endif // _di_f_type_cellss_resize_

/**
 * Resize the string array_lengthss array.
 *
 * @param length
 *   The new size to use.
 * @param array_lengthss
 *   The string array_lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_array_lengthss_adjust_
  extern f_status_t f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *array_lengthss);
#endif // _di_f_type_array_lengthss_adjust_

/**
 * Resize the string array_lengthss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param array_lengthss
 *   The string array_lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_array_lengthss_decimate_by_
  extern f_status_t f_type_array_lengthss_decimate_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss);
#endif // _di_f_type_array_lengthss_decimate_by_

/**
 * Resize the string array_lengthss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param array_lengthss
 *   The string array_lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_array_lengthss_decrease_by_
  extern f_status_t f_type_array_lengthss_decrease_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss);
#endif // _di_f_type_array_lengthss_decrease_by_

/**
 * Increase the size of the string array_lengthss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param array_lengthss
 *   The string array_lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_array_lengthss_increase_
  extern f_status_t f_type_array_lengthss_increase(f_array_lengthss_t *array_lengthss);
#endif // _di_f_type_array_lengthss_increase_

/**
 * Resize the string array_lengthss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param array_lengthss
 *   The string array_lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_type_array_lengthss_increase_by_
  extern f_status_t f_type_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss);
#endif // _di_f_type_array_lengthss_increase_by_

/**
 * Resize the string array_lengthss array.
 *
 * @param length
 *   The new size to use.
 * @param array_lengthss
 *   The string array_lengthss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_array_lengthss_resize_
  extern f_status_t f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *array_lengthss);
#endif // _di_f_type_array_lengthss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param int8ss
 *   The string int8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int8ss_increase_
  extern f_status_t f_type_int8ss_increase(f_int8ss_t *int8ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int8ss_resize_
  extern f_status_t f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss);
#endif // _di_f_type_int8ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param uint8ss
 *   The string uint8ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint8ss_increase_
  extern f_status_t f_type_uint8ss_increase(f_uint8ss_t *uint8ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint8ss_resize_
  extern f_status_t f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss);
#endif // _di_f_type_uint8ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param int16ss
 *   The string int16ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int16ss_increase_
  extern f_status_t f_type_int16ss_increase(f_int16ss_t *int16ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int16ss_resize_
  extern f_status_t f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss);
#endif // _di_f_type_int16ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param uint16ss
 *   The string uint16ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint16ss_increase_
  extern f_status_t f_type_uint16ss_increase(f_uint16ss_t *uint16ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint16ss_resize_
  extern f_status_t f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss);
#endif // _di_f_type_uint16ss_resize_


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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param int32ss
 *   The string int32ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int32ss_increase_
  extern f_status_t f_type_int32ss_increase(f_int32ss_t *int32ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int32ss_resize_
  extern f_status_t f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss);
#endif // _di_f_type_int32ss_resize_


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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param uint32ss
 *   The string uint32ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint32ss_increase_
  extern f_status_t f_type_uint32ss_increase(f_uint32ss_t *uint32ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint32ss_resize_
  extern f_status_t f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss);
#endif // _di_f_type_uint32ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param int64ss
 *   The string int64ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int64ss_increase_
  extern f_status_t f_type_int64ss_increase(f_int64ss_t *int64ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int64ss_resize_
  extern f_status_t f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss);
#endif // _di_f_type_int64ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param uint64ss
 *   The string uint64ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint64ss_increase_
  extern f_status_t f_type_uint64ss_increase(f_uint64ss_t *uint64ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint64ss_resize_
  extern f_status_t f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss);
#endif // _di_f_type_uint64ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param int128ss
 *   The string int128ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int128ss_increase_
  extern f_status_t f_type_int128ss_increase(f_int128ss_t *int128ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_int128ss_resize_
  extern f_status_t f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss);
#endif // _di_f_type_int128ss_resize_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param uint128ss
 *   The string uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_type_uint128ss_increase_
  extern f_status_t f_type_uint128ss_increase(f_uint128ss_t *uint128ss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
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
 */
#ifndef _di_f_type_uint128ss_resize_
  extern f_status_t f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss);
#endif // _di_f_type_uint128ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_h

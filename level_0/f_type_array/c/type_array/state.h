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
#ifndef _F_type_array_state_h
#define _F_type_array_state_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the string states array.
 *
 * @param length
 *   The new size to use.
 * @param states
 *   The string states array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_states_adjust_
  extern f_status_t f_states_adjust(const f_array_length_t length, f_states_t *states);
#endif // _di_f_states_adjust_

/**
 * Append the source states onto the destination.
 *
 * @param source
 *   The source states to append.
 * @param destination
 *   The destination states the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_states_append_
  extern f_status_t f_states_append(const f_states_t source, f_states_t *destination);
#endif // _di_f_states_append_

/**
 * Resize the string states array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param states
 *   The string states array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_states_decimate_by_
  extern f_status_t f_states_decimate_by(const f_array_length_t amount, f_states_t *states);
#endif // _di_f_states_decimate_by_

/**
 * Resize the string states array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param states
 *   The string states array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_states_decrease_by_
  extern f_status_t f_states_decrease_by(const f_array_length_t amount, f_states_t *states);
#endif // _di_f_states_decrease_by_

/**
 * Increase the size of the string states array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param states
 *   The string states array to resize.
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
#ifndef _di_f_states_increase_
  extern f_status_t f_states_increase(const f_array_length_t step, f_states_t *states);
#endif // _di_f_states_increase_

/**
 * Resize the string states array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param states
 *   The string states array to resize.
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
#ifndef _di_f_states_increase_by_
  extern f_status_t f_states_increase_by(const f_array_length_t amount, f_states_t *states);
#endif // _di_f_states_increase_by_

/**
 * Resize the string states array.
 *
 * @param length
 *   The new size to use.
 * @param states
 *   The string states array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_states_resize_
  extern f_status_t f_states_resize(const f_array_length_t length, f_states_t *states);
#endif // _di_f_states_resize_

/**
 * Resize the string statess array.
 *
 * @param length
 *   The new size to use.
 * @param statess
 *   The string statess array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_statess_adjust_
  extern f_status_t f_statess_adjust(const f_array_length_t length, f_statess_t *statess);
#endif // _di_f_statess_adjust_

/**
 * Append the source statess onto the destination.
 *
 * @param source
 *   The source statess to append.
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
#ifndef _di_f_statess_append_
  extern f_status_t f_statess_append(const f_statess_t source, f_statess_t *destination);
#endif // _di_f_statess_append_

/**
 * Resize the string statess array.
 *
 * @param length
 *   The new size to use.
 * @param statess
 *   The string statess array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_statess_adjust_
  extern f_status_t f_statess_adjust(const f_array_length_t length, f_statess_t *statess);
#endif // _di_f_statess_adjust_

/**
 * Resize the string statess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param statess
 *   The string statess array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_statess_decimate_by_
  extern f_status_t f_statess_decimate_by(const f_array_length_t amount, f_statess_t *statess);
#endif // _di_f_statess_decimate_by_

/**
 * Resize the string statess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param statess
 *   The string statess array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statess_decrease_by_
  extern f_status_t f_statess_decrease_by(const f_array_length_t amount, f_statess_t *statess);
#endif // _di_f_statess_decrease_by_

/**
 * Increase the size of the string statess array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param statess
 *   The string statess array to resize.
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
#ifndef _di_f_statess_increase_
  extern f_status_t f_statess_increase(const f_array_length_t step, f_statess_t *statess);
#endif // _di_f_statess_increase_

/**
 * Resize the string statess array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param statess
 *   The string statess array to resize.
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
#ifndef _di_f_statess_increase_by_
  extern f_status_t f_statess_increase_by(const f_array_length_t amount, f_statess_t *statess);
#endif // _di_f_statess_increase_by_

/**
 * Resize the string statess array.
 *
 * @param length
 *   The new size to use.
 * @param statess
 *   The string statess array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_statess_resize_
  extern f_status_t f_statess_resize(const f_array_length_t length, f_statess_t *statess);
#endif // _di_f_statess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_state_h

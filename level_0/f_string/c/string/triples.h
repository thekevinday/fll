/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines 3-tuple of string data called a triple (which is an ordered list of 3 strings).
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_triples_h
#define _F_string_triples_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of string triples.
 *
 * Properties:
 *   - array: The array of string triples.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_triples_t_
  typedef struct {
    f_string_triple_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_string_triples_t;

  #define f_string_triples_t_initialize f_string_statics_t_initialize

  #define macro_f_string_triples_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_triples_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_triples_t_clear(triples) \
    triples.array = 0; \
    triples.size = 0; \
    triples.used = 0;
#endif // _di_f_string_triples_t_

/**
 * Resize the string triples array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string triples array to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_triples_adjust_
  extern f_status_t f_string_triples_adjust(const f_number_unsigned_t length, f_string_triples_t * const structure);
#endif // _di_f_string_triples_adjust_

/**
 * Append the single source triples onto the destination.
 *
 * @param source
 *   The source triple to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_append_
  extern f_status_t f_string_triples_append(const f_string_triple_t source, f_string_triples_t * const destination);
#endif // _di_f_string_triples_append_

/**
 * Append the source triples onto the destination.
 *
 * @param source
 *   The source triples to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_append_all_
  extern f_status_t f_string_triples_append_all(const f_string_triples_t source, f_string_triples_t * const destination);
#endif // _di_f_string_triples_append_all_

/**
 * Resize the string triples array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param structure
 *   The string triples array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_decimate_by_
  extern f_status_t f_string_triples_decimate_by(const f_number_unsigned_t amount, f_string_triples_t * const structure);
#endif // _di_f_string_triples_decimate_by_

/**
 * Resize the string triples array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param structure
 *   The string triples array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_decrease_by_
  extern f_status_t f_string_triples_decrease_by(const f_number_unsigned_t amount, f_string_triples_t * const structure);
#endif // _di_f_string_triples_decrease_by_

/**
 * Increase the size of the string triples array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param structure
 *   The string triples array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_increase_
  extern f_status_t f_string_triples_increase(const f_number_unsigned_t step, f_string_triples_t * const structure);
#endif // _di_f_string_triples_increase_

/**
 * Resize the string triples array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param structure
 *   The string triples array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_increase_by_
  extern f_status_t f_string_triples_increase_by(const f_number_unsigned_t amount, f_string_triples_t * const structure);
#endif // _di_f_string_triples_increase_by_

/**
 * Resize the string triples array.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The string triples array to adjust.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_resize_
  extern f_status_t f_string_triples_resize(const f_number_unsigned_t length, f_string_triples_t * const structure);
#endif // _di_f_string_triples_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_triples_h

/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines 3-tuple of string data called a triple (which is an ordered list of 3 strings).
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_triple_h
#define _F_string_triple_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string triple consisting of a set of three strings.
 *
 * a: A string representing the first string in the triple.
 * b: A string representing the second string in the triple.
 * c: A string representing the third string in the triple.
 */
#ifndef _di_f_string_triple_t_
  typedef struct {
    f_string_dynamic_t a;
    f_string_dynamic_t b;
    f_string_dynamic_t c;
  } f_string_triple_t;

  #define f_string_triple_t_initialize { f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define macro_f_string_triple_t_clear(triple) \
    triple.a.array = 0; \
    triple.a.size = 0; \
    triple.a.used = 0; \
    triple.b.array = 0; \
    triple.b.size = 0; \
    triple.b.used = 0; \
    triple.c.array = 0; \
    triple.c.size = 0; \
    triple.c.used = 0;

  #define macro_f_string_triple_t_delete_simple(triple) \
    macro_f_string_dynamic_t_delete_simple(triple.a) \
    macro_f_string_dynamic_t_delete_simple(triple.b) \
    macro_f_string_dynamic_t_delete_simple(triple.c)

  #define macro_f_string_triple_t_destroy_simple(triple) \
    macro_f_string_dynamic_t_destroy_simple(triple.a) \
    macro_f_string_dynamic_t_destroy_simple(triple.b) \
    macro_f_string_dynamic_t_destroy_simple(triple.c)
#endif // _di_f_string_triple_t_

/**
 * An array of string triples.
 *
 * array: The array of string triples.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_triples_t_
  typedef struct {
    f_string_triple_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_triples_t;

  #define f_string_triples_t_initialize f_string_statics_t_initialize

  #define macro_f_string_triples_t_clear(triples) macro_f_memory_structure_clear(triples)

  #define macro_f_string_triples_t_resize(status, triples, length) status = f_string_triples_resize(length, &triples);
  #define macro_f_string_triples_t_adjust(status, triples, length) status = f_string_triples_adjust(length, &triples);

  #define macro_f_string_triples_t_delete_simple(triples)  f_string_triples_resize(0, &triples);
  #define macro_f_string_triples_t_destroy_simple(triples) f_string_triples_adjust(0, &triples);

  #define macro_f_string_triples_t_increase(status, step, triples)      status = f_string_triples_increase(step, triples);
  #define macro_f_string_triples_t_increase_by(status, triples, amount) status = f_string_triples_increase_by(amount, triples);
  #define macro_f_string_triples_t_decrease_by(status, triples, amount) status = f_string_triples_decrease_by(amount, triples);
  #define macro_f_string_triples_t_decimate_by(status, triples, amount) status = f_string_triples_decimate_by(amount, triples);
#endif // _di_f_string_triples_t_

/**
 * An array of string tripless.
 *
 * array: The array of string triples.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_tripless_t_
  typedef struct {
    f_string_triples_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_tripless_t;

  #define f_string_tripless_t_initialize f_string_statics_t_initialize

  #define macro_f_string_tripless_t_clear(tripless) macro_f_memory_structure_clear(tripless)

  #define macro_f_string_tripless_t_resize(status, tripless, length) status = f_string_tripless_resize(length, &tripless);
  #define macro_f_string_tripless_t_adjust(status, tripless, length) status = f_string_tripless_adjust(length, &tripless);

  #define macro_f_string_tripless_t_delete_simple(tripless)  f_string_tripless_resize(0, &tripless);
  #define macro_f_string_tripless_t_destroy_simple(tripless) f_string_tripless_adjust(0, &tripless);

  #define macro_f_string_tripless_t_increase(status, step, tripless)      status = f_string_tripless_increase(step, tripless);
  #define macro_f_string_tripless_t_increase_by(status, tripless, amount) status = f_string_tripless_increase_by(amount, tripless);
  #define macro_f_string_tripless_t_decrease_by(status, tripless, amount) status = f_string_tripless_decrease_by(amount, tripless);
  #define macro_f_string_tripless_t_decimate_by(status, tripless, amount) status = f_string_tripless_decimate_by(amount, tripless);
#endif // _di_f_string_tripless_t_

/**
 * Resize the string triples array.
 *
 * @param length
 *   The new size to use.
 * @param triples
 *   The string triples array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_triples_adjust_
  extern f_status_t f_string_triples_adjust(const f_array_length_t length, f_string_triples_t * const triples);
#endif // _di_f_string_triples_adjust_

/**
 * Append the source triples onto the destination.
 *
 * @param source
 *   The source triples to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_append_
  extern f_status_t f_string_triples_append(const f_string_triples_t source, f_string_triples_t * const destination);
#endif // _di_f_string_triples_append_

/**
 * Resize the string triples array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param triples
 *   The string triples array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_decimate_by_
  extern f_status_t f_string_triples_decimate_by(const f_array_length_t amount, f_string_triples_t * const triples);
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
 * @param triples
 *   The string triples array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_decrease_by_
  extern f_status_t f_string_triples_decrease_by(const f_array_length_t amount, f_string_triples_t * const triples);
#endif // _di_f_string_triples_decrease_by_

/**
 * Increase the size of the string triples array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param triples
 *   The string triples array to resize.
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
#ifndef _di_f_string_triples_increase_
  extern f_status_t f_string_triples_increase(const f_array_length_t step, f_string_triples_t * const triples);
#endif // _di_f_string_triples_increase_

/**
 * Resize the string triples array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param triples
 *   The string triples array to resize.
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
#ifndef _di_f_string_triples_increase_by_
  extern f_status_t f_string_triples_increase_by(const f_array_length_t amount, f_string_triples_t * const triples);
#endif // _di_f_string_triples_increase_by_

/**
 * Resize the string triples array.
 *
 * @param length
 *   The new size to use.
 * @param triples
 *   The string triples array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_triples_resize_
  extern f_status_t f_string_triples_resize(const f_array_length_t length, f_string_triples_t * const triples);
#endif // _di_f_string_triples_resize_

/**
 * Resize the string tripless array.
 *
 * @param length
 *   The new size to use.
 * @param tripless
 *   The string tripless array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_tripless_adjust_
  extern f_status_t f_string_tripless_adjust(const f_array_length_t length, f_string_tripless_t * const tripless);
#endif // _di_f_string_tripless_adjust_

/**
 * Append the source tripless onto the destination.
 *
 * @param source
 *   The source tripless to append.
 * @param destination
 *   The destination tripless the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_tripless_append_
  extern f_status_t f_string_tripless_append(const f_string_tripless_t source, f_string_tripless_t * const destination);
#endif // _di_f_string_tripless_append_

/**
 * Resize the string tripless array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param tripless
 *   The string tripless array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_tripless_decimate_by_
  extern f_status_t f_string_tripless_decimate_by(const f_array_length_t amount, f_string_tripless_t * const tripless);
#endif // _di_f_string_tripless_decimate_by_

/**
 * Resize the string tripless array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param tripless
 *   The string tripless array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_tripless_decrease_by_
  extern f_status_t f_string_tripless_decrease_by(const f_array_length_t amount, f_string_tripless_t * const tripless);
#endif // _di_f_string_tripless_decrease_by_

/**
 * Increase the size of the string tripless array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param tripless
 *   The string tripless array to resize.
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
#ifndef _di_f_string_tripless_increase_
  extern f_status_t f_string_tripless_increase(const f_array_length_t step, f_string_tripless_t * const tripless);
#endif // _di_f_string_tripless_increase_

/**
 * Resize the string tripless array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param tripless
 *   The string tripless array to resize.
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
#ifndef _di_f_string_tripless_increase_by_
  extern f_status_t f_string_tripless_increase_by(const f_array_length_t amount, f_string_tripless_t * const tripless);
#endif // _di_f_string_tripless_increase_by_

/**
 * Resize the string tripless array.
 *
 * @param length
 *   The new size to use.
 * @param tripless
 *   The string tripless array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_tripless_resize_
  extern f_status_t f_string_tripless_resize(const f_array_length_t length, f_string_tripless_t * const tripless);
#endif // _di_f_string_tripless_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_triple_h

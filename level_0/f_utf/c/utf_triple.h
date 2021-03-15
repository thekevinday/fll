/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines 3-tuple of string data called a triple (which is an ordered list of 3 strings).
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_string_triple_h
#define _F_utf_string_triple_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string triple consisting of a set of three strings.
 *
 * one: A string representing the first string in the triple.
 * two: A string representing the second string in the triple.
 * three: A string representing the third string in the triple.
 */
#ifndef _di_f_utf_string_triple_t_
  typedef struct {
    f_utf_string_dynamic_t one;
    f_utf_string_dynamic_t two;
    f_utf_string_dynamic_t three;
  } f_utf_string_triple_t;

  #define f_utf_string_triple_t_initialize { f_utf_string_dynamic_t_initialize, f_utf_string_dynamic_t_initialize, f_utf_string_dynamic_t_initialize }

  #define f_macro_utf_string_triple_t_clear(triple) \
    triple.one.array = 0; \
    triple.one.size = 0; \
    triple.one.used = 0; \
    triple.two.array = 0; \
    triple.two.size = 0; \
    triple.two.used = 0; \
    triple.three.array = 0; \
    triple.three.size = 0; \
    triple.three.used = 0;

  #define f_macro_utf_string_triple_t_delete_simple(triple) \
    f_macro_utf_string_dynamic_t_delete_simple(triple.one) \
    f_macro_utf_string_dynamic_t_delete_simple(triple.two) \
    f_macro_utf_string_dynamic_t_delete_simple(triple.three)

  #define f_macro_utf_string_triple_t_destroy_simple(triple) \
    f_macro_utf_string_dynamic_t_destroy_simple(triple.one) \
    f_macro_utf_string_dynamic_t_destroy_simple(triple.two) \
    f_macro_utf_string_dynamic_t_destroy_simple(triple.three)
#endif // _di_f_utf_string_triple_t_

/**
 * An array of string triples.
 *
 * array: the array of string triples.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_triples_t_
  typedef struct {
    f_utf_string_triple_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_triples_t;

  #define f_utf_string_triples_t_initialize f_utf_string_statics_t_initialize

  #define f_macro_utf_string_triples_t_clear(triples) f_macro_memory_structure_clear(triples)

  #define f_macro_utf_string_triples_t_resize(status, triples, length) status = f_utf_string_triples_resize(length, &triples);
  #define f_macro_utf_string_triples_t_adjust(status, triples, length) status = f_utf_string_triples_adjust(length, &triples);

  #define f_macro_utf_string_triples_t_delete_simple(triples)  f_utf_string_triples_resize(0, &triples);
  #define f_macro_utf_string_triples_t_destroy_simple(triples) f_utf_string_triples_adjust(0, &triples);

  #define f_macro_utf_string_triples_t_increase(status, triples)            status = f_utf_string_triples_increase(triples);
  #define f_macro_utf_string_triples_t_increase_by(status, triples, amount) status = f_utf_string_triples_increase_by(amount, triples);
  #define f_macro_utf_string_triples_t_decrease_by(status, triples, amount) status = f_utf_string_triples_decrease_by(amount, triples);
  #define f_macro_utf_string_triples_t_decimate_by(status, triples, amount) status = f_utf_string_triples_decimate_by(amount, triples);
#endif // _di_f_utf_string_triples_t_

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
#ifndef _di_f_utf_string_triples_adjust_
  extern f_status_t f_utf_string_triples_adjust(const f_array_length_t length, f_utf_string_triples_t *triples);
#endif // _di_f_utf_string_triples_adjust_

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
#ifndef _di_f_utf_string_triples_append_
  extern f_status_t f_utf_string_triples_append(const f_utf_string_triples_t source, f_utf_string_triples_t *destination);
#endif // _di_f_utf_string_triples_append_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_triples_decimate_by_
  extern f_status_t f_utf_string_triples_decimate_by(const f_array_length_t amount, f_utf_string_triples_t *triples);
#endif // _di_f_utf_string_triples_decimate_by_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_triples_decrease_by_
  extern f_status_t f_utf_string_triples_decrease_by(const f_array_length_t amount, f_utf_string_triples_t *triples);
#endif // _di_f_utf_string_triples_decrease_by_

/**
 * Increase the size of the string triples array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
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
#ifndef _di_f_utf_string_triples_increase_
  extern f_status_t f_utf_string_triples_increase(f_utf_string_triples_t *triples);
#endif // _di_f_utf_string_triples_increase_

/**
 * Resize the string triples array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
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
#ifndef _di_f_utf_string_triples_increase_by_
  extern f_status_t f_utf_string_triples_increase_by(const f_array_length_t amount, f_utf_string_triples_t *triples);
#endif // _di_f_utf_string_triples_increase_by_

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
#ifndef _di_f_utf_string_triples_resize_
  extern f_status_t f_utf_string_triples_resize(const f_array_length_t length, f_utf_string_triples_t *triples);
#endif // _di_f_utf_string_triples_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_string_triple_h

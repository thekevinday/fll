/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines nest data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_nest_h
#define _F_fss_nest_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds an array of f_fss_items_t.
 *
 * Each array row represents the nesting depth.
 * The top-level will not have any parent, so "parent" must be ignored on anything at index 0.
 * The parent identifier is expected to reference a position in the nesting depth immediately above it.
 *
 * Properties:
 *   - depth: An array of f_fss_items_t, with each index representing the depth.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nest_t_
  typedef struct {
    f_fss_items_t *depth;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_nest_t;

  #define f_fss_nest_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nest_t_initialize_1(depth, size, used) { depth, size, used }
  #define macro_f_fss_nest_t_initialize_2(depth, length)     { depth, length, length }

  #define macro_f_fss_nest_t_clear(nest) macro_f_memory_structures_clear(nest)

  #define macro_f_fss_nest_t_resize(status, nest, length) status = f_fss_nest_resize(length, &nest);
  #define macro_f_fss_nest_t_adjust(status, nest, length) status = f_fss_nest_adjust(length, &nest);

  #define macro_f_fss_nest_t_delete_simple(nest)  f_fss_nest_resize(0, &nest);
  #define macro_f_fss_nest_t_destroy_simple(nest) f_fss_nest_adjust(0, &nest);

  #define macro_f_fss_nest_t_increase(status, step, nest)      status = f_fss_nest_increase(step, &nest);
  #define macro_f_fss_nest_t_increase_by(status, nest, amount) status = f_fss_nest_increase_by(amount, &nest);
  #define macro_f_fss_nest_t_decrease_by(status, nest, amount) status = f_fss_nest_decrease_by(amount, &nest);
  #define macro_f_fss_nest_t_decimate_by(status, nest, amount) status = f_fss_nest_decimate_by(amount, &nest);
#endif // _di_f_fss_nest_t_

/**
 * This holds an array of f_fss_nest_t.
 *
 * Properties:
 *   - array: An array of f_fss_nest_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nests_t_
  typedef struct {
    f_fss_nest_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_nests_t;

  #define f_fss_nests_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nests_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_nests_t_initialize_2(array, length)     { array, length, length }

  #define macro_f_fss_nests_t_clear(nests) macro_f_memory_structures_clear(nests)

  #define macro_f_fss_nests_t_resize(status, nests, length) status = f_fss_nests_resize(length, &nests);
  #define macro_f_fss_nests_t_adjust(status, nests, length) status = f_fss_nests_adjust(length, &nests);

  #define macro_f_fss_nests_t_delete_simple(nests)  f_fss_nests_resize(0, &nests);
  #define macro_f_fss_nests_t_destroy_simple(nests) f_fss_nests_adjust(0, &nests);

  #define macro_f_fss_nests_t_increase(status, step, nests)      status = f_fss_nests_increase(step, &nests);
  #define macro_f_fss_nests_t_increase_by(status, nests, amount) status = f_fss_nests_increase_by(amount, &nests);
  #define macro_f_fss_nests_t_decrease_by(status, nests, amount) status = f_fss_nests_decrease_by(amount, &nests);
  #define macro_f_fss_nests_t_decimate_by(status, nests, amount) status = f_fss_nests_decimate_by(amount, &nests);
#endif // _di_f_fss_nests_t_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_adjust_
  extern f_status_t f_fss_nest_adjust(const f_number_unsigned_t length, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_adjust_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_decimate_by_
  extern f_status_t f_fss_nest_decimate_by(const f_number_unsigned_t amount, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_decimate_by_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_decrease_by_
  extern f_status_t f_fss_nest_decrease_by(const f_number_unsigned_t amount, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_decrease_by_

/**
 * Increase the size of the nest array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_increase_
  extern f_status_t f_fss_nest_increase(const f_number_unsigned_t step, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_increase_

/**
 * Resize the nest array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_nest_increase_by_
  extern f_status_t f_fss_nest_increase_by(const f_number_unsigned_t amount, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_increase_by_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_resize_
  extern f_status_t f_fss_nest_resize(const f_number_unsigned_t length, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_resize_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_adjust_
  extern f_status_t f_fss_nests_adjust(const f_number_unsigned_t length, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_adjust_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_decimate_by_
  extern f_status_t f_fss_nests_decimate_by(const f_number_unsigned_t amount, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_decimate_by_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_decrease_by_
  extern f_status_t f_fss_nests_decrease_by(const f_number_unsigned_t amount, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_decrease_by_

/**
 * Increase the size of the nests array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_increase_
  extern f_status_t f_fss_nests_increase(const f_number_unsigned_t step, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_increase_

/**
 * Resize the nests array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_nests_increase_by_
  extern f_status_t f_fss_nests_increase_by(const f_number_unsigned_t amount, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_increase_by_

/**
 * Resize the nests array.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_resize_
  extern f_status_t f_fss_nests_resize(const f_number_unsigned_t length, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_nest_h

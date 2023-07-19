/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_set_h
#define _F_fss_set_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds an fss object with a set of fss content.
 *
 * The objects and contents should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * Properties:
 *   - objects:  The array of objects.
 *   - contents: The array of contents.
 */
#ifndef _di_f_fss_set_t_
  typedef struct {
    f_string_ranges_t objects;
    f_string_rangess_t contents;
  } f_fss_set_t;

  #define f_fss_set_t_initialize { f_string_ranges_t_initialize, f_string_rangess_t_initialize }

  #define macro_f_fss_set_t_initialize_1(objects, contents) { objects, contents }

  #define macro_f_fss_set_t_clear(set) \
    macro_f_string_ranges_t_clear(set.objects) \
    macro_f_string_rangess_t_clear(set.contents)

  #define macro_f_fss_set_t_resize(status, set, length) status = f_fss_set_resize(length, &set);
  #define macro_f_fss_set_t_adjust(status, set, length) status = f_fss_set_adjust(length, &set);

  #define macro_f_fss_set_t_delete_simple(set)  f_fss_set_resize(0, &set);
  #define macro_f_fss_set_t_destroy_simple(set) f_fss_set_adjust(0, &set);

  #define macro_f_fss_set_t_increase(status, step, set)      status = f_fss_set_increase(step, &set);
  #define macro_f_fss_set_t_increase_by(status, set, amount) status = f_fss_set_increase_by(amount, &set);
  #define macro_f_fss_set_t_decrease_by(status, set, amount) status = f_fss_set_decrease_by(amount, &set);
  #define macro_f_fss_set_t_decimate_by(status, set, amount) status = f_fss_set_decimate_by(amount, &set);
#endif // _di_f_fss_set_t_

/**
 * This holds an array of f_fss_set_t.
 *
 * Properties:
 *   - array: An array of f_fss_set_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_sets_t_
  typedef struct {
    f_fss_set_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_sets_t;

  #define f_fss_sets_t_initialize { 0, 0, 0 }

  #define macro_f_fss_sets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_sets_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_sets_t_resize(status, sets, length) status = f_fss_sets_resize(length, &sets);
  #define macro_f_fss_sets_t_adjust(status, sets, length) status = f_fss_sets_adjust(length, &sets);

  #define macro_f_fss_sets_t_delete_simple(sets)  f_fss_sets_resize(0, &sets);
  #define macro_f_fss_sets_t_destroy_simple(sets) f_fss_sets_adjust(0, &sets);

  #define macro_f_fss_sets_t_increase(status, step, sets)      status = f_fss_sets_increase(step, &sets);
  #define macro_f_fss_sets_t_increase_by(status, sets, amount) status = f_fss_sets_increase_by(amount, &sets);
  #define macro_f_fss_sets_t_decrease_by(status, sets, amount) status = f_fss_sets_decrease_by(amount, &sets);
  #define macro_f_fss_sets_t_decimate_by(status, sets, amount) status = f_fss_sets_decimate_by(amount, &sets);
#endif // _di_f_fss_sets_t_

/**
 * Resize the set array.
 *
 * @param length
 *   The new size to use.
 * @param set
 *   The set array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 */
#ifndef _di_f_fss_set_adjust_
  extern f_status_t f_fss_set_adjust(const f_number_unsigned_t length, f_fss_set_t * const set);
#endif // _di_f_fss_set_adjust_

/**
 * Resize the set array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param set
 *   The set array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 */
#ifndef _di_f_fss_set_decimate_by_
  extern f_status_t f_fss_set_decimate_by(const f_number_unsigned_t amount, f_fss_set_t * const set);
#endif // _di_f_fss_set_decimate_by_

/**
 * Resize the set array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param set
 *   The set array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 */
#ifndef _di_f_fss_set_decrease_by_
  extern f_status_t f_fss_set_decrease_by(const f_number_unsigned_t amount, f_fss_set_t * const set);
#endif // _di_f_fss_set_decrease_by_

/**
 * Increase the size of the set array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param set
 *   The set array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_set_increase_
  extern f_status_t f_fss_set_increase(const f_number_unsigned_t step, f_fss_set_t * const set);
#endif // _di_f_fss_set_increase_

/**
 * Resize the set array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param set
 *   The set array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_set_increase_by_
  extern f_status_t f_fss_set_increase_by(const f_number_unsigned_t amount, f_fss_set_t * const set);
#endif // _di_f_fss_set_increase_by_

/**
 * Resize the set array.
 *
 * @param length
 *   The new size to use.
 * @param set
 *   The set array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_set_resize_
  extern f_status_t f_fss_set_resize(const f_number_unsigned_t length, f_fss_set_t * const set);
#endif // _di_f_fss_set_resize_

/**
 * Resize the set array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_sets_adjust_
  extern f_status_t f_fss_sets_adjust(const f_number_unsigned_t length, f_fss_sets_t * const sets);
#endif // _di_f_fss_sets_adjust_

/**
 * Resize the set array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_sets_decimate_by_
  extern f_status_t f_fss_sets_decimate_by(const f_number_unsigned_t amount, f_fss_sets_t * const sets);
#endif // _di_f_fss_sets_decimate_by_

/**
 * Resize the set array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_sets_decrease_by_
  extern f_status_t f_fss_sets_decrease_by(const f_number_unsigned_t amount, f_fss_sets_t * const sets);
#endif // _di_f_fss_sets_decrease_by_

/**
 * Increase the size of the sets array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @return
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_fss_sets_increase_
  extern f_status_t f_fss_sets_increase(const f_number_unsigned_t step, f_fss_sets_t * const sets);
#endif // _di_f_fss_sets_increase_

/**
 * Resize the sets array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 *
 * @return
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_fss_sets_increase_by_
  extern f_status_t f_fss_sets_increase_by(const f_number_unsigned_t amount, f_fss_sets_t * const sets);
#endif // _di_f_fss_sets_increase_by_

/**
 * Resize the sets array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_fss_sets_resize_
  extern f_status_t f_fss_sets_resize(const f_number_unsigned_t length, f_fss_sets_t * const sets);
#endif // _di_f_fss_sets_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_set_h

/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by limit related functionality.
 *
 * This is auto-included by limit.h and should not need to be explicitly included.
 */
#ifndef _F_limit_set_h
#define _F_limit_set_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A limit value structure.
 *
 * Properties:
 *   - type:  The limit resource type code.
 *   - value: The limit value containing the soft and hard limit.
 */
#ifndef _di_f_limit_set_t_
  typedef struct {
    int type;
    f_limit_value_t value;
  } f_limit_set_t;

  #define f_limit_set_t_initialize { 0, f_limit_value_t_initialize }

  #define macro_f_limit_set_t_initialize_1(type, value) { type, value }

  #define macro_f_limit_set_t_clear(set) \
    set.type = 0; \
    macro_f_limit_value_t_clear(set.value);
#endif // _di_f_limit_set_t_

/**
 * An array of limit sets.
 *
 * Properties:
 *   - array: An array of limit sets.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_limit_sets_t_
  typedef struct {
    f_limit_set_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_limit_sets_t;

  #define f_limit_sets_t_initialize { 0, 0, 0 }

  #define macro_f_limit_sets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_limit_sets_t_initialize_2(array, length) { array, length, length }

  #define macro_f_limit_sets_t_resize(status, sets, length) status = f_limit_sets_resize(length, &sets);
  #define macro_f_limit_sets_t_adjust(status, sets, length) status = f_limit_sets_adjust(length, &sets);

  #define macro_f_limit_sets_t_delete_simple(sets)  f_limit_sets_resize(0, &sets);
  #define macro_f_limit_sets_t_destroy_simple(sets) f_limit_sets_adjust(0, &sets);

  #define macro_f_limit_sets_t_increase(status, step, sets)      status = f_limit_sets_increase(step, &sets);
  #define macro_f_limit_sets_t_increase_by(status, sets, amount) status = f_limit_sets_increase_by(amount, &sets);
  #define macro_f_limit_sets_t_decrease_by(status, sets, amount) status = f_limit_sets_decrease_by(amount, &sets);
  #define macro_f_limit_sets_t_decimate_by(status, sets, amount) status = f_limit_sets_decimate_by(amount, &sets);
#endif // _di_f_limit_sets_t_

/**
 * This holds an array of f_limit_sets_t.
 *
 * Properties:
 *   - array: An array of f_limit_sets_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_limit_setss_t_
  typedef struct {
    f_limit_sets_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_limit_setss_t;

  #define f_limit_setss_t_initialize { 0, 0, 0 }

  #define macro_f_limit_setss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_limit_setss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_limit_setss_t_resize(status, setss, length) status = f_limit_setss_resize(length, &setss);
  #define macro_f_limit_setss_t_adjust(status, setss, length) status = f_limit_setss_adjust(length, &setss);

  #define macro_f_limit_setss_t_delete_simple(setss)  f_limit_setss_resize(0, &setss);
  #define macro_f_limit_setss_t_destroy_simple(setss) f_limit_setss_adjust(0, &setss);

  #define macro_f_limit_setss_t_increase(status, step, setss)      status = f_limit_setss_increase(step, &setss);
  #define macro_f_limit_setss_t_increase_by(status, setss, amount) status = f_limit_setss_increase_by(amount, &setss);
  #define macro_f_limit_setss_t_decrease_by(status, setss, amount) status = f_limit_setss_decrease_by(amount, &setss);
  #define macro_f_limit_setss_t_decimate_by(status, setss, amount) status = f_limit_setss_decimate_by(amount, &setss);
#endif // _di_f_limit_setss_t_

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
#ifndef _di_f_limit_sets_adjust_
  extern f_status_t f_limit_sets_adjust(const f_number_unsigned_t length, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_adjust_

/**
 * Append the single source set onto the destination.
 *
 * @param source
 *   The source set to append.
 * @param destination
 *   The destination sets the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_limit_sets_append_
  extern f_status_t f_limit_sets_append(const f_limit_set_t source, f_limit_sets_t *destination);
#endif // _di_f_limit_sets_append_

/**
 * Append the source sets onto the destination.
 *
 * @param source
 *   The source sets to append.
 * @param destination
 *   The destination sets the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_limit_sets_append_all_
  extern f_status_t f_limit_sets_append_all(const f_limit_sets_t source, f_limit_sets_t *destination);
#endif // _di_f_limit_sets_append_all_

/**
 * Resize the sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 * @return
 *   Success from f_memory_array_decimate_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decimate_by().
 *
 * @see f_memory_array_decimate_by()
 */
#ifndef _di_f_limit_sets_decimate_by_
  extern f_status_t f_limit_sets_decimate_by(const f_number_unsigned_t amount, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_decimate_by_

/**
 * Resize the sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param sets
 *   The sets array to resize.
 *
 * @return
 *   Success from f_memory_array_decrease_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decrease_by().
 *
 * @see f_memory_array_decrease_by()
 */
#ifndef _di_f_limit_sets_decrease_by_
  extern f_status_t f_limit_sets_decrease_by(const f_number_unsigned_t amount, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_decrease_by_

/**
 * Increase the size of the sets array, but only if necesary.
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
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_limit_sets_increase_
  extern f_status_t f_limit_sets_increase(const f_number_unsigned_t step, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_increase_

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
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_limit_sets_increase_by_
  extern f_status_t f_limit_sets_increase_by(const f_number_unsigned_t amount, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_increase_by_

/**
 * Resize the sets array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets array to adjust.
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
#ifndef _di_f_limit_sets_resize_
  extern f_status_t f_limit_sets_resize(const f_number_unsigned_t length, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_resize_

/**
 * Resize the setss array.
 *
 * @param length
 *   The new size to use.
 * @param setss
 *   The setss array to resize.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_limit_setss_adjust_
  extern f_status_t f_limit_setss_adjust(const f_number_unsigned_t length, f_limit_setss_t *setss);
#endif // _di_f_limit_setss_adjust_

/**
 * Append the single source sets onto the destination.
 *
 * @param source
 *   The source sets to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_limit_setss_append_
  extern f_status_t f_limit_setss_append(const f_limit_sets_t source, f_limit_setss_t *destination);
#endif // _di_f_limit_setss_append_

/**
 * Append the source setss onto the destination.
 *
 * @param source
 *   The source setss to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_limit_setss_append_all_
  extern f_status_t f_limit_setss_append_all(const f_limit_setss_t source, f_limit_setss_t *destination);
#endif // _di_f_limit_setss_append_all_

/**
 * Resize the setss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param setss
 *   The setss array to resize.
 *
 * @return
 *   F_data_not on success, but the amount to decrease by is 0.
 *
 *   Success from f_memory_array_decimate_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decimate_by().
 *
 * @see f_memory_array_decimate_by()
 */
#ifndef _di_f_limit_setss_decimate_by_
  extern f_status_t f_limit_setss_decimate_by(const f_number_unsigned_t amount, f_limit_setss_t *setss);
#endif // _di_f_limit_setss_decimate_by_

/**
 * Resize the setss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param setss
 *   The setss array to resize.
 *
 * @return
 *   F_data_not on success, but the amount to decrease by is 0.
 *
 *   Success from f_memory_array_decrease_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decrease_by().
 *
 * @see f_memory_array_decrease_by()
 */
#ifndef _di_f_limit_setss_decrease_by_
  extern f_status_t f_limit_setss_decrease_by(const f_number_unsigned_t amount, f_limit_setss_t *setss);
#endif // _di_f_limit_setss_decrease_by_

/**
 * Increase the size of the setss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param setss
 *   The setss array to resize.
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
#ifndef _di_f_limit_setss_increase_
  extern f_status_t f_limit_setss_increase(const f_number_unsigned_t step, f_limit_setss_t *setss);
#endif // _di_f_limit_setss_increase_

/**
 * Resize the setss array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param setss
 *   The setss array to resize.
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
#ifndef _di_f_limit_setss_increase_by_
  extern f_status_t f_limit_setss_increase_by(const f_number_unsigned_t amount, f_limit_setss_t *setss);
#endif // _di_f_limit_setss_increase_by_

/**
 * Resize the setss array.
 *
 * @param length
 *   The new size to use.
 * @param setss
 *   The setss array to adjust.
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
#ifndef _di_f_limit_setss_resize_
  extern f_status_t f_limit_setss_resize(const f_number_unsigned_t length, f_limit_setss_t *setss);
#endif // _di_f_limit_setss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_set_h

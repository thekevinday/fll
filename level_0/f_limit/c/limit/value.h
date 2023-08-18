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
#ifndef _F_limit_value_h
#define _F_limit_value_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A limit value structure.
 *
 * rlim_cur: The soft limit.
 * rlim_max: The hard limit.
 */
#ifndef _di_f_limit_value_t_
  typedef struct rlimit f_limit_value_t;

  #define f_limit_value_t_initialize { 0, 0 }

  #define macro_f_limit_value_t_initialize_1(current, max) { current, max }

  #define macro_f_limit_value_t_clear(value) \
    value.rlim_cur = 0; \
    value.rlim_max = 0;
#endif // _di_f_limit_value_t_

/**
 * An array of limit values.
 *
 * Properties:
 *   - array: An array of limit values.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_limit_values_t_
  typedef struct {
    f_limit_value_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_limit_values_t;

  #define f_limit_values_t_initialize { 0, 0, 0 }

  #define macro_f_limit_values_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_limit_values_t_initialize_2(array, length) { array, length, length }

  #define macro_f_limit_values_t_resize(status, values, length) status = f_limit_values_resize(length, &values);
  #define macro_f_limit_values_t_adjust(status, values, length) status = f_limit_values_adjust(length, &values);

  #define macro_f_limit_values_t_delete_simple(values)  f_limit_values_resize(0, &values);
  #define macro_f_limit_values_t_destroy_simple(values) f_limit_values_adjust(0, &values);

  #define macro_f_limit_values_t_increase(status, step, values)      status = f_limit_values_increase(step, &values);
  #define macro_f_limit_values_t_increase_by(status, values, amount) status = f_limit_values_increase_by(amount, &values);
  #define macro_f_limit_values_t_decrease_by(status, values, amount) status = f_limit_values_decrease_by(amount, &values);
  #define macro_f_limit_values_t_decimate_by(status, values, amount) status = f_limit_values_decimate_by(amount, &values);
#endif // _di_f_limit_values_t_

/**
 * This holds an array of f_limit_values_t.
 *
 * Properties:
 *   - array: An array of f_limit_values_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_limit_valuess_t_
  typedef struct {
    f_limit_values_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_limit_valuess_t;

  #define f_limit_valuess_t_initialize { 0, 0, 0 }

  #define macro_f_limit_valuess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_limit_valuess_t_initialize_2(array, length) { array, length, length }

  #define macro_f_limit_valuess_t_resize(status, valuess, length) status = f_limit_valuess_resize(length, &valuess);
  #define macro_f_limit_valuess_t_adjust(status, valuess, length) status = f_limit_valuess_adjust(length, &valuess);

  #define macro_f_limit_valuess_t_delete_simple(valuess)  f_limit_valuess_resize(0, &valuess);
  #define macro_f_limit_valuess_t_destroy_simple(valuess) f_limit_valuess_adjust(0, &valuess);

  #define macro_f_limit_valuess_t_increase(status, step, valuess)      status = f_limit_valuess_increase(step, &valuess);
  #define macro_f_limit_valuess_t_increase_by(status, valuess, amount) status = f_limit_valuess_increase_by(amount, &valuess);
  #define macro_f_limit_valuess_t_decrease_by(status, valuess, amount) status = f_limit_valuess_decrease_by(amount, &valuess);
  #define macro_f_limit_valuess_t_decimate_by(status, valuess, amount) status = f_limit_valuess_decimate_by(amount, &valuess);
#endif // _di_f_limit_valuess_t_

/**
 * Resize the values array.
 *
 * @param length
 *   The new size to use.
 * @param values
 *   The values array to resize.
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
#ifndef _di_f_limit_values_adjust_
  extern f_status_t f_limit_values_adjust(const f_number_unsigned_t length, f_limit_values_t *values);
#endif // _di_f_limit_values_adjust_

/**
 * Append the single source value onto the destination.
 *
 * @param source
 *   The source value to append.
 * @param destination
 *   The destination values the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_limit_values_append_
  extern f_status_t f_limit_values_append(const f_limit_value_t source, f_limit_values_t *destination);
#endif // _di_f_limit_values_append_

/**
 * Append the source values onto the destination.
 *
 * @param source
 *   The source values to append.
 * @param destination
 *   The destination values the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_limit_values_append_all_
  extern f_status_t f_limit_values_append_all(const f_limit_values_t source, f_limit_values_t *destination);
#endif // _di_f_limit_values_append_all_

/**
 * Resize the values array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param values
 *   The values array to resize.
 *
 * @return
 *   Success from f_memory_array_decimate_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decimate_by().
 *
 * @see f_memory_array_decimate_by()
 */
#ifndef _di_f_limit_values_decimate_by_
  extern f_status_t f_limit_values_decimate_by(const f_number_unsigned_t amount, f_limit_values_t *values);
#endif // _di_f_limit_values_decimate_by_

/**
 * Resize the values array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param values
 *   The values array to resize.
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
#ifndef _di_f_limit_values_decrease_by_
  extern f_status_t f_limit_values_decrease_by(const f_number_unsigned_t amount, f_limit_values_t *values);
#endif // _di_f_limit_values_decrease_by_

/**
 * Increase the size of the values array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param values
 *   The values array to resize.
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
#ifndef _di_f_limit_values_increase_
  extern f_status_t f_limit_values_increase(const f_number_unsigned_t step, f_limit_values_t *values);
#endif // _di_f_limit_values_increase_

/**
 * Resize the values array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param values
 *   The values array to resize.
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
#ifndef _di_f_limit_values_increase_by_
  extern f_status_t f_limit_values_increase_by(const f_number_unsigned_t amount, f_limit_values_t *values);
#endif // _di_f_limit_values_increase_by_

/**
 * Resize the values array.
 *
 * @param length
 *   The new size to use.
 * @param values
 *   The values array to adjust.
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
#ifndef _di_f_limit_values_resize_
  extern f_status_t f_limit_values_resize(const f_number_unsigned_t length, f_limit_values_t *values);
#endif // _di_f_limit_values_resize_

/**
 * Resize the valuess array.
 *
 * @param length
 *   The new size to use.
 * @param valuess
 *   The valuess array to resize.
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
#ifndef _di_f_limit_valuess_adjust_
  extern f_status_t f_limit_valuess_adjust(const f_number_unsigned_t length, f_limit_valuess_t *valuess);
#endif // _di_f_limit_valuess_adjust_

/**
 * Append the single source values onto the destination.
 *
 * @param source
 *   The source values to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_okay on success.
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
#ifndef _di_f_limit_valuess_append_
  extern f_status_t f_limit_valuess_append(const f_limit_values_t source, f_limit_valuess_t *destination);
#endif // _di_f_limit_valuess_append_

/**
 * Append the source valuess onto the destination.
 *
 * @param source
 *   The source valuess to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_okay on success.
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
#ifndef _di_f_limit_valuess_append_all_
  extern f_status_t f_limit_valuess_append_all(const f_limit_valuess_t source, f_limit_valuess_t *destination);
#endif // _di_f_limit_valuess_append_all_

/**
 * Resize the valuess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param valuess
 *   The valuess array to resize.
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
#ifndef _di_f_limit_valuess_decimate_by_
  extern f_status_t f_limit_valuess_decimate_by(const f_number_unsigned_t amount, f_limit_valuess_t *valuess);
#endif // _di_f_limit_valuess_decimate_by_

/**
 * Resize the valuess array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param valuess
 *   The valuess array to resize.
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
#ifndef _di_f_limit_valuess_decrease_by_
  extern f_status_t f_limit_valuess_decrease_by(const f_number_unsigned_t amount, f_limit_valuess_t *valuess);
#endif // _di_f_limit_valuess_decrease_by_

/**
 * Increase the size of the valuess array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param valuess
 *   The valuess array to resize.
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
#ifndef _di_f_limit_valuess_increase_
  extern f_status_t f_limit_valuess_increase(const f_number_unsigned_t step, f_limit_valuess_t *valuess);
#endif // _di_f_limit_valuess_increase_

/**
 * Resize the valuess array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param valuess
 *   The valuess array to resize.
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
#ifndef _di_f_limit_valuess_increase_by_
  extern f_status_t f_limit_valuess_increase_by(const f_number_unsigned_t amount, f_limit_valuess_t *valuess);
#endif // _di_f_limit_valuess_increase_by_

/**
 * Resize the valuess array.
 *
 * @param length
 *   The new size to use.
 * @param valuess
 *   The valuess array to adjust.
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
#ifndef _di_f_limit_valuess_resize_
  extern f_status_t f_limit_valuess_resize(const f_number_unsigned_t length, f_limit_valuess_t *valuess);
#endif // _di_f_limit_valuess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_value_h

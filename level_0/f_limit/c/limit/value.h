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
#endif // _di_f_limit_values_t_

/**
 * An array of an array of limit values.
 *
 * Properties:
 *   - array: An array of an array of limit values.
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

  #define macro_f_limit_valuess_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_limit_valuess_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_limit_valuess_t_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_limit_valuess_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_limit_valuess_delete_callback_
  extern f_status_t f_limit_valuess_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_limit_valuess_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_limit_valuess_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_limit_valuess_destroy_callback_
  extern f_status_t f_limit_valuess_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_limit_valuess_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_value_h

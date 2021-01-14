/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines dynamic (and static) string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_dynamic_h
#define _F_string_dynamic_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string that is analogous to f_string_dynamic_t but intended for static-only uses.
 *
 * The f_string_static_t type should never be directly allocated or deallocated.
 *
 * A special f_macro_string_static_t_initialize() is provided for the special purpose of easily initialize a static string.
 *
 * string: the string.
 * size:   total amount of space available.
 * used:   total number of space used.
 */
#ifndef _di_f_string_static_t_
  typedef struct {
    f_string_t string;

    f_string_length_t size;
    f_string_length_t used;
  } f_string_static_t;

  #define f_string_static_t_initialize { 0, 0, 0 }

  #define f_macro_string_static_t_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;

  #define f_macro_string_static_t_initialize(string, length) { string, length, length }
#endif // _di_f_string_static_t_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 *
 * Save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * This is a sub-type of f_string_static_t, allowing it to be passed into any f_string_static_t type.
 * It is recommended that f_string_static_t are not otherwise casted into f_string_dynamic_t to avoid potential memory allocation issues.
 *
 * string: the string.
 * size:   total amount of allocated space.
 * used:   total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_t_
  typedef f_string_static_t f_string_dynamic_t;

  #define f_string_dynamic_t_initialize f_string_static_t_initialize

  #define f_macro_string_dynamic_t_clear(dynamic) f_macro_string_static_t_clear(dynamic)

  #define f_macro_string_dynamic_t_resize(status, dynamic, length) status = f_string_dynamic_resize(length, &dynamic);
  #define f_macro_string_dynamic_t_adjust(status, dynamic, length) status = f_string_dynamic_adjust(length, &dynamic);

  #define f_macro_string_dynamic_t_delete_simple(dynamic)  f_string_dynamic_resize(0, &dynamic);
  #define f_macro_string_dynamic_t_destroy_simple(dynamic) f_string_dynamic_adjust(0, &dynamic);

  #define f_macro_string_dynamic_t_increase(status, dynamic)            status = f_string_dynamic_increase(&dynamic);
  #define f_macro_string_dynamic_t_increase_by(status, dynamic, amount) status = f_string_dynamic_increase_by(amount, &dynamic);
  #define f_macro_string_dynamic_t_decrease_by(status, dynamic, amount) status = f_string_dynamic_decrease_by(amount, &dynamic);
  #define f_macro_string_dynamic_t_decimate_by(status, dynamic, amount) status = f_string_dynamic_decimate_by(amount, &dynamic);
#endif // _di_f_string_dynamic_t_

/**
 * An array of static dynamics.
 *
 * array: the array of static dynamics.
 * size:  total amount of space available.
 * used:  total number of space used.
 */
#ifndef _di_f_string_statics_t_
  typedef struct {
    f_string_static_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_statics_t;

  #define f_string_statics_t_initialize { 0, 0, 0 }

  #define f_macro_string_statics_t_clear(statics) \
    statics.array = 0; \
    statics.size = 0; \
    statics.used = 0;
#endif // _di_f_string_statics_t_

/**
 * An array of dynamic dynamics.
 *
 * array: the array of dynamic dynamics.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_t_
  typedef f_string_statics_t f_string_dynamics_t;

  #define f_string_dynamics_t_initialize f_string_statics_t_initialize

  #define f_macro_string_dynamics_t_clear(dynamics) f_macro_string_statics_t_clear(dynamics)

  #define f_macro_string_dynamics_t_resize(status, dynamics, length) status = f_string_dynamics_resize(length, &dynamics);
  #define f_macro_string_dynamics_t_adjust(status, dynamics, length) status = f_string_dynamics_adjust(length, &dynamics);

  #define f_macro_string_dynamics_t_delete_simple(dynamics)  f_string_dynamics_resize(0, &dynamics);
  #define f_macro_string_dynamics_t_destroy_simple(dynamics) f_string_dynamics_adjust(0, &dynamics);

  #define f_macro_string_dynamics_t_increase(status, dynamics)            status = f_string_dynamics_increase(&dynamics);
  #define f_macro_string_dynamics_t_increase_by(status, dynamics, amount) status = f_string_dynamics_increase_by(amount, &dynamics);
  #define f_macro_string_dynamics_t_decrease_by(status, dynamics, amount) status = f_string_dynamics_decrease_by(amount, &dynamics);
  #define f_macro_string_dynamics_t_decimate_by(status, dynamics, amount) status = f_string_dynamics_decimate_by(amount, &dynamics);
#endif // _di_f_string_dynamics_t_

#ifndef _di_f_string_static_empty_s_
  const extern f_string_static_t f_string_static_empty_s;
#endif // _di_f_string_static_empty_s_

/**
 * Resize the dynamic string.
 *
 * @param length
 *   The new size to use.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamic_adjust_
  extern f_status_t f_string_dynamic_adjust(const f_array_length_t length, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_adjust_

/**
 * Resize the dynamic string to a smaller size.
 *
 * This will resize making the string smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to decrease size (size = 0).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamic_decrease_by_
  extern f_status_t f_string_dynamic_decrease_by(const f_string_length_t amount, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_decrease_by_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_string_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_increase_
  extern f_status_t f_string_dynamic_increase(f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_increase_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_string_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_increase_by_
  extern f_status_t f_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_increase_by_

/**
 * Resize the dynamic string.
 *
 * @param length
 *   The new size to use.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamic_resize_
  extern f_status_t f_string_dynamic_resize(const f_array_length_t length, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_resize_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamics_adjust_
  extern f_status_t f_string_dynamics_adjust(const f_array_length_t length, f_string_dynamics_t *dynamics);
#endif // _di_f_string_dynamics_adjust_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param dynamics
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamics_decimate_by_
  extern f_status_t f_string_dynamics_decimate_by(const f_array_length_t amount, f_string_dynamics_t *dynamics);
#endif // _di_f_string_dynamics_decimate_by_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamics
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamics_decrease_by_
  extern f_status_t f_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t *dynamics);
#endif // _di_f_string_dynamics_decrease_by_

/**
 * Increase the size of the dynamic string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param dynamics
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_string_dynamics_increase_
  extern f_status_t f_string_dynamics_increase(f_string_dynamics_t *dynamics);
#endif // _di_f_string_dynamics_increase_

/**
 * Resize the dynamic string array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamics
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_string_dynamics_increase_by_
  extern f_status_t f_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t *dynamics);
#endif // _di_f_string_dynamics_increase_by_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamics_resize_
  extern f_status_t f_string_dynamics_resize(const f_array_length_t length, f_string_dynamics_t *dynamics);
#endif // _di_f_string_dynamics_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamic_h

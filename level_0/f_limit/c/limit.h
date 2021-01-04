/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides limit related functionality.
 */
#ifndef _F_limit_h
#define _F_limit_h

// include pre-requirements
#define _GNU_SOURCE

// libc includes
#include <sys/time.h>
#include <sys/resource.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>

// fll-1 control includes
#include <level_0/limit-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get or set the resource limits for some process.
 *
 * Either value_next or value_current must be non-zero.
 *
 * @param id
 *   The PID to set the resources of.
 * @param type
 *   The resource type to set limit of or get limit of.
 * @param value_next
 *   The resource value to assign.
 *   If 0 is used instead of a valid value, then value_current must be non-zero and will be populated with the current resource value.
 * @param value_current
 *   The resource value currently assigned.
 *   If 0, then value_next is assigning the value but the previous value will not be returned.
 *   If both value_next and value_current are non-zero, then this represents the value prior to the assignment of value_next.
 *
 * @return
 *   F_none on success.
 *   F_address_not (with error bit) if a pointer is outside of valid address space.
 *   F_found_not (with error bit) if no process by the given PID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform this action.
 *
 * @see prlimit()
 */
#ifndef _di_f_limit_process_
  extern f_return_status f_limit_process(const pid_t id, const int type, const f_limit_value_t *value_next, f_limit_value_t *value_current);
#endif // _di_f_limit_process_

/**
 * Resize the sets array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_limit_sets_decrease_
  extern f_return_status f_limit_sets_decrease(f_limit_sets_t *sets);
#endif // _di_f_limit_sets_decrease_

/**
 * Resize the sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_limit_sets_decrease_by_
  extern f_return_status f_limit_sets_decrease_by(const f_array_length_t amount, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_decrease_by_

/**
 * Delete the sets array.
 *
 * @param string
 *   The string to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_limit_sets_delete_
  extern f_return_status f_limit_sets_delete(f_limit_sets_t *sets);
#endif // _di_f_limit_sets_delete_

/**
 * Increase the size of the sets array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_limit_sets_increase_
  extern f_return_status f_limit_sets_increase(f_limit_sets_t *sets);
#endif // _di_f_limit_sets_increase_

/**
 * Resize the sets array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_limit_sets_increase_by_
  extern f_return_status f_limit_sets_increase_by(const f_array_length_t amount, f_limit_sets_t *sets);
#endif // _di_f_limit_sets_increase_by_

/**
 * Resize the values array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param values
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_limit_values_decrease_
  extern f_return_status f_limit_values_decrease(f_limit_values_t *values);
#endif // _di_f_limit_values_decrease_

/**
 * Resize the values array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param values
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_limit_values_decrease_by_
  extern f_return_status f_limit_values_decrease_by(const f_array_length_t amount, f_limit_values_t *values);
#endif // _di_f_limit_values_decrease_by_

/**
 * Delete the values array.
 *
 * @param string
 *   The string to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_limit_values_delete_
  extern f_return_status f_limit_values_delete(f_limit_values_t *values);
#endif // _di_f_limit_values_delete_

/**
 * Increase the size of the values array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param values
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_limit_values_increase_
  extern f_return_status f_limit_values_increase(f_limit_values_t *values);
#endif // _di_f_limit_values_increase_

/**
 * Resize the values array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param values
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_limit_values_increase_by_
  extern f_return_status f_limit_values_increase_by(const f_array_length_t amount, f_limit_values_t *values);
#endif // _di_f_limit_values_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_h

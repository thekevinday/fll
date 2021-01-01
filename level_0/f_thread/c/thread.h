/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides POSIX thread_sets related functionality.
 */
#ifndef _F_thread_h
#define _F_thread_h

// libc includes
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>

// fll-0 thread includes
#include <level_0/thread-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the user account by the user id.
 *
 * @param attribute
 *   The thread attributes.
 * @param id
 *   The thread ID.
 *   This gets populated with the created thread ID (aka: the "child" thread).
 * @param routine
 *   The function to execute.
 * @param argument
 *   The structure containing all arguments to pass to the routine.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to set the scheduling policy and parameters specified in attribute.
 *   F_resource_not (with error bit) if there are not enough resources to create another thread.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_create()
 */
#ifndef _di_f_thread_create_
  extern f_return_status f_thread_create(const pthread_attr_t *attribute, pthread_t *id, void *(*routine) (void *), void *argument);
#endif // _di_f_thread_create_

/**
 * Resize the thread set array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param thread_sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_decrease_
  extern f_return_status f_thread_sets_decrease(f_thread_sets_t *thread_sets);
#endif // _di_f_thread_sets_decrease_

/**
 * Resize the thread set array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param thread_sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_decrease_by_
  extern f_return_status f_thread_sets_decrease_by(const f_array_length_t amount, f_thread_sets_t *thread_sets);
#endif // _di_f_thread_sets_decrease_by_

/**
 * Delete the thread set array.
 *
 * @param string
 *   The string to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_delete_
  extern f_return_status f_thread_sets_delete(f_thread_sets_t *thread_sets);
#endif // _di_f_thread_sets_delete_

/**
 * Increase the size of the thread set array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param thread_sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_thread_sets_increase_
  extern f_return_status f_thread_sets_increase(f_thread_sets_t *thread_sets);
#endif // _di_f_thread_sets_increase_

/**
 * Resize the thread set array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param thread_sets
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_thread_sets_increase_by_
  extern f_return_status f_thread_sets_increase_by(const f_array_length_t amount, f_thread_sets_t *thread_sets);
#endif // _di_f_thread_sets_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_h

/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides POSIX sets related functionality.
 */
#ifndef _F_thread_h
#define _F_thread_h

// include pre-requirements
#define _GNU_SOURCE

// libc includes
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

// fll-0 thread includes
#include <level_0/thread-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform a fork operation.
 *
 * @param before
 *   The function to call before forking.
 * @param after_parent
 *   The function called after forking, for the parent process.
 * @param child_parent
 *   The function called after forking, for the child process.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) if out of memory.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_atfork()
 */
#ifndef _di_f_thread_at_fork_
  extern f_status_t f_thread_at_fork(void (*before) (void), void (*after_parent) (void), void (*after_child) (void));
#endif // _di_f_thread_at_fork_

/**
 * Get the affinity state of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param affinity_size
 *   The size of the affinity_set.
 * @param affinity_set
 *   The assigned affinity information.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getaffinity_np()
 */
#ifndef _di_f_thread_attribute_affinity_get_
  extern f_status_t f_thread_attribute_affinity_get(const f_thread_attribute_t attribute, const size_t affinity_size, cpu_set_t *affinity_set);
#endif // _di_f_thread_attribute_affinity_get_

/**
 * Set the affinity state of the thread attribute.
 *
 * @param affinity_size
 *   The size of the affinity_set.
 * @param affinity_set
 *   The affinity information to assign.
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setaffinity_np()
 */
#ifndef _di_f_thread_attribute_affinity_set_
  extern f_status_t f_thread_attribute_affinity_set(const size_t affinity_size, const cpu_set_t *affinity_set, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_affinity_set_

/**
 * Get the clock selection thread condition attribute.
 *
 * @param attribute
 *   The thread condition attribute.
 * @param id
 *   The clock ID.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_condattr_getclock()
 */
#ifndef _di_f_thread_attribute_clock_get_
  extern f_status_t f_thread_attribute_clock_get(const f_thread_condition_attribute_t *attribute, clockid_t *id);
#endif // _di_f_thread_attribute_clock_get_

/**
 * Set the clock selection thread condition attribute.
 *
 * @param id
 *   The clock ID.
 * @param attribute
 *   The thread condition attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_condattr_setclock()
 */
#ifndef _di_f_thread_attribute_clock_set_
  extern f_status_t f_thread_attribute_clock_set(const clockid_t id, f_thread_condition_attribute_t *attribute);
#endif // _di_f_thread_attribute_clock_set_

/**
 * Get the process shared thread condition attribute.
 *
 * @param attribute
 *   The thread condition attribute.
 * @param shared
 *   The process shared attribute value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_condattr_getpshared()
 */
#ifndef _di_f_thread_attribute_condition_shared_get_
  extern f_status_t f_thread_attribute_condition_shared_get(const f_thread_condition_attribute_t *attribute, int *shared);
#endif // _di_f_thread_attribute_condition_shared_get_

/**
 * Set the process shared thread condition attribute.
 *
 * @param shared
 *   The process shared attribute value.
 * @param attribute
 *   The thread condition attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_condattr_setpshared()
 */
#ifndef _di_f_thread_attribute_condition_shared_set_
  extern f_status_t f_thread_attribute_condition_shared_set(const int shared, f_thread_condition_attribute_t *attribute);
#endif // _di_f_thread_attribute_condition_shared_set_

/**
 * Create (initialize) a thread attribute structure.
 *
 * @param attribute
 *   (optional) The attribute to set.
 *   Set to NULL to not use (in which case the default attribute is used).
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) if out of memory.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_init()
 */
#ifndef _di_f_thread_attribute_create_
  extern f_status_t f_thread_attribute_create(f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_create_

/**
 * Get the default thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_getattr_default_np()
 */
#ifndef _di_f_thread_attribute_default_get_
  extern f_status_t f_thread_attribute_default_get(f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_default_get_

/**
 * Set the default thread attribute.
 *
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setattr_default_np()
 */
#ifndef _di_f_thread_attribute_default_set_
  extern f_status_t f_thread_attribute_default_set(f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_default_set_

/**
 * Delete a thread attribute structure.
 *
 * On successfully delete, the pointer address is set to 0.
 *
 * The pthread_attr_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param attribute
 *   The thread attributes to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_destroy()
 */
#ifndef _di_f_thread_attribute_delete_
  extern f_status_t f_thread_attribute_delete(f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_delete_

/**
 * Get the detached state of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param state
 *   The currently assigned state.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getdetachstate()
 */
#ifndef _di_f_thread_attribute_detach_get_
  extern f_status_t f_thread_attribute_detach_get(const f_thread_attribute_t attribute, int *state);
#endif // _di_f_thread_attribute_detach_get_

/**
 * Set the detached state of the thread attribute.
 *
 * @param state
 *   The state to assign (such as PTHREAD_CREATE_DETACHED or PTHREAD_CREATE_JOINABLE).
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setdetachstate()
 */
#ifndef _di_f_thread_attribute_detach_set_
  extern f_status_t f_thread_attribute_detach_set(const int state, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_detach_set_

/**
 * Get the guard size of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param guard
 *   The currently assigned guard size.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getguardsize()
 */
#ifndef _di_f_thread_attribute_guard_get_
  extern f_status_t f_thread_attribute_guard_get(const f_thread_attribute_t attribute, size_t *guard);
#endif // _di_f_thread_attribute_guard_get_

/**
 * Set the guard size of the thread attribute.
 *
 * @param guard
 *   The guard size to assign.
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setguardsize()
 */
#ifndef _di_f_thread_attribute_guard_set_
  extern f_status_t f_thread_attribute_guard_set(const size_t guard, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_guard_set_

/**
 * Get the scheduler inherit state of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param inherit
 *   The currently assigned scheduler inherit state.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getinheritsched()
 */
#ifndef _di_f_thread_attribute_scheduler_inherit_get_
  extern f_status_t f_thread_attribute_scheduler_inherit_get(const f_thread_attribute_t attribute, int *inherit);
#endif // _di_f_thread_attribute_scheduler_inherit_get_

/**
 * Set the scheduler inherit state of the thread attribute.
 *
 * @param inherit
 *   The inherit state of the scheduler (such as PTHREAD_INHERIT_SCHED or PTHREAD_EXPLICIT_SCHED).
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setinheritsched()
 */
#ifndef _di_f_thread_attribute_scheduler_inherit_set_
  extern f_status_t f_thread_attribute_scheduler_inherit_set(const int inherit, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_scheduler_inherit_set_

/**
 * Get the scheduler parameter state of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param parameter
 *   The currently assigned scheduler parameters.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getschedparam()
 */
#ifndef _di_f_thread_attribute_scheduler_parameter_get_
  extern f_status_t f_thread_attribute_scheduler_parameter_get(const f_thread_attribute_t attribute, struct sched_param *parameter);
#endif // _di_f_thread_attribute_scheduler_parameter_get_

/**
 * Set the scheduler parameter state of the thread attribute.
 *
 * @param parameter
 *   The parameters of the scheduler.
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setschedparam()
 */
#ifndef _di_f_thread_attribute_scheduler_parameter_set_
  extern f_status_t f_thread_attribute_scheduler_parameter_set(const struct sched_param parameter, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_scheduler_parameter_set_

/**
 * Get the scheduler policy state of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param policy
 *   The currently assigned scheduler policy state.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getschedpolicy()
 */
#ifndef _di_f_thread_attribute_scheduler_policy_get_
  extern f_status_t f_thread_attribute_scheduler_policy_get(const f_thread_attribute_t attribute, int *policy);
#endif // _di_f_thread_attribute_scheduler_policy_get_

/**
 * Set the scheduler policy state of the thread attribute.
 *
 * @param policy
 *   The policy state of the scheduler (such as SCHED_FIFO, SCHED_RR, or SCHED_OTHER).
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setschedpolicy()
 */
#ifndef _di_f_thread_attribute_scheduler_policy_set_
  extern f_status_t f_thread_attribute_scheduler_policy_set(const int policy, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_scheduler_policy_set_

/**
 * Get the scheduler scope state of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param scope
 *   The currently assigned scheduler scope state.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getscope()
 */
#ifndef _di_f_thread_attribute_scope_get_
  extern f_status_t f_thread_attribute_scope_get(const f_thread_attribute_t attribute, int *scope);
#endif // _di_f_thread_attribute_scope_get_

/**
 * Set the scheduler scope state of the thread attribute.
 *
 * @param scope
 *   The scope state of the scheduler (such as PTHREAD_SCOPE_SYSTEM or PTHREAD_SCOPE_PROCESS).
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the scope is not supported by the current OS (such as Linux not supporting PTHREAD_SCOPE_PROCESS).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setscope()
 */
#ifndef _di_f_thread_attribute_scope_set_
  extern f_status_t f_thread_attribute_scope_set(const int scope, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_scope_set_

/**
 * Get the stack of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param stack_size
 *   The size of the stack.
 * @param stack
 *   The assigned stack.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) if the caller cannot both read and write to the stack address.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getstack()
 */
#ifndef _di_f_thread_attribute_stack_get_
  extern f_status_t f_thread_attribute_stack_get(const f_thread_attribute_t attribute, size_t *stack_size, void **stack);
#endif // _di_f_thread_attribute_stack_get_

/**
 * Set the stack of the thread attribute.
 *
 * @param stack_size
 *   The size of the stack.
 * @param stack
 *   The stack to assign.
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) if the caller cannot both read and write to the stack address.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setstack()
 */
#ifndef _di_f_thread_attribute_stack_set_
  extern f_status_t f_thread_attribute_stack_set(const size_t stack_size, void * const stack, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_stack_set_

/**
 * Get the stack size of the thread attribute.
 *
 * @param attribute
 *   The thread attributes to process.
 * @param stack_size
 *   The assigned size of the stack.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_getstacksize()
 */
#ifndef _di_f_thread_attribute_stack_size_get_
  extern f_status_t f_thread_attribute_stack_size_get(const f_thread_attribute_t attribute, size_t *stack_size);
#endif // _di_f_thread_attribute_stack_size_get_

/**
 * Set the stack size of the thread attribute.
 *
 * @param stack_size
 *   The size of the stack.
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setstacksize()
 */
#ifndef _di_f_thread_attribute_stack_size_set_
  extern f_status_t f_thread_attribute_stack_size_set(const size_t stack_size, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_stack_size_set_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_attributes_adjust_
  extern f_status_t f_thread_attributes_adjust(const f_array_length_t length, f_thread_attributes_t *attributes);
#endif // _di_f_thread_attributes_adjust_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_attributes_decimate_by_
  extern f_status_t f_thread_attributes_decimate_by(const f_array_length_t amount, f_thread_attributes_t *attributes);
#endif // _di_f_thread_attributes_decimate_by_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_attributes_decrease_by_
  extern f_status_t f_thread_attributes_decrease_by(const f_array_length_t amount, f_thread_attributes_t *attributes);
#endif // _di_f_thread_attributes_decrease_by_

/**
 * Increase the size of the thread attributes array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_attributes_increase_
  extern f_status_t f_thread_attributes_increase(f_thread_attributes_t *attributes);
#endif // _di_f_thread_attributes_increase_

/**
 * Resize the thread attributes array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_attributes_increase_by_
  extern f_status_t f_thread_attributes_increase_by(const f_array_length_t amount, f_thread_attributes_t *attributes);
#endif // _di_f_thread_attributes_increase_by_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_attributes_resize_
  extern f_status_t f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t *attributes);
#endif // _di_f_thread_attributes_resize_

/**
 * Create (initialize) a thread barrier attribute structure.
 *
 * @param attribute
 *   (optional) The attribute to set.
 *   Set to NULL to not use (in which case the default attribute is used).
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) if out of memory.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_barrierattr_init()
 */
#ifndef _di_f_thread_barrier_attribute_create_
  extern f_status_t f_thread_barrier_attribute_create(f_thread_barrier_attribute_t *attribute);
#endif // _di_f_thread_barrier_attribute_create_

/**
 * Delete a thread barrier attribute structure.
 *
 * On successfully delete, the pointer address is set to 0.
 *
 * The pthread_barrierattr_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param attribute
 *   The thread barrier_attributes to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_barrierattr_destroy()
 */
#ifndef _di_f_thread_barrier_attribute_delete_
  extern f_status_t f_thread_barrier_attribute_delete(f_thread_barrier_attribute_t *attribute);
#endif // _di_f_thread_barrier_attribute_delete_

/**
 * Get the barrier process shared thread attribute.
 *
 * @param attribute
 *   The barrier thread attribute.
 * @param shared
 *   The process shared attribute value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_barrierattr_getpshared()
 */
#ifndef _di_f_thread_barrier_attribute_shared_get_
  extern f_status_t f_thread_barrier_attribute_shared_get(const f_thread_barrier_attribute_t *attribute, int *shared);
#endif // _di_f_thread_barrier_attribute_shared_get_

/**
 * Set the barrier process shared thread attribute.
 *
 * @param shared
 *   The process shared attribute value.
 * @param attribute
 *   The barrier thread attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_barrierattr_setpshared()
 */
#ifndef _di_f_thread_barrier_attribute_shared_set_
  extern f_status_t f_thread_barrier_attribute_shared_set(const int shared, f_thread_barrier_attribute_t *attribute);
#endif // _di_f_thread_barrier_attribute_shared_set_

/**
 * Resize the thread barrier attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The thread attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barrier_attributes_adjust_
  extern f_status_t f_thread_barrier_attributes_adjust(const f_array_length_t length, f_thread_barrier_attributes_t *attributes);
#endif // _di_f_thread_barrier_attributes_adjust_

/**
 * Resize the thread barrier attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param attributes
 *   The thread attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barrier_attributes_decimate_by_
  extern f_status_t f_thread_barrier_attributes_decimate_by(const f_array_length_t amount, f_thread_barrier_attributes_t *attributes);
#endif // _di_f_thread_barrier_attributes_decimate_by_

/**
 * Resize the thread barrier attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param attributes
 *   The thread attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barrier_attributes_decrease_by_
  extern f_status_t f_thread_barrier_attributes_decrease_by(const f_array_length_t amount, f_thread_barrier_attributes_t *attributes);
#endif // _di_f_thread_barrier_attributes_decrease_by_

/**
 * Increase the size of the thread barrier attributes array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param attributes
 *   The thread attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barrier_attributes_increase_
  extern f_status_t f_thread_barrier_attributes_increase(f_thread_barrier_attributes_t *attributes);
#endif // _di_f_thread_barrier_attributes_increase_

/**
 * Resize the thread barrier attributes array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param attributes
 *   The thread attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barrier_attributes_increase_by_
  extern f_status_t f_thread_barrier_attributes_increase_by(const f_array_length_t amount, f_thread_barrier_attributes_t *attributes);
#endif // _di_f_thread_barrier_attributes_increase_by_

/**
 * Resize the thread barrier attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The thread attributes array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barrier_attributes_resize_
  extern f_status_t f_thread_barrier_attributes_resize(const f_array_length_t length, f_thread_barrier_attributes_t *attributes);
#endif // _di_f_thread_barrier_attributes_resize_

/**
 * Create (initialize) a thread barrier structure.
 *
 * @param barrier
 *   (optional) The barrier to set.
 *   Set to NULL to not use (in which case the default barrier is used).
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) if out of memory.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_barrier_init()
 */
#ifndef _di_f_thread_barrier_create_
  extern f_status_t f_thread_barrier_create(const unsigned int count, f_thread_barrier_attribute_t * const attribute, f_thread_barrier_t *barrier);
#endif // _di_f_thread_barrier_create_

/**
 * Delete a thread barrier structure.
 *
 * On successfully delete, the pointer address is set to 0.
 *
 * The pthread_barrier_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param barrier
 *   The thread barriers to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_barrier_destroy()
 */
#ifndef _di_f_thread_barrier_delete_
  extern f_status_t f_thread_barrier_delete(f_thread_barrier_t *barrier);
#endif // _di_f_thread_barrier_delete_

/**
 * Wait on a barrier, effectively synchronizing multiple threads with some barrier.
 *
 * @param barrier
 *   The barrier to wait on.
 * @param result
 *   (optional) the return value, which will be PTHREAD_BARRIER_SERIAL_THREAD for one thread and 0 for others.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_barrier_wait()
 */
#ifndef _di_f_thread_barrier_wait_
  extern f_status_t f_thread_barrier_wait(f_thread_barrier_t *barrier, int *result);
#endif // _di_f_thread_barrier_wait_

/**
 * Resize the thread barriers array.
 *
 * @param length
 *   The new size to use.
 * @param barriers
 *   The thread barriers array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barriers_adjust_
  extern f_status_t f_thread_barriers_adjust(const f_array_length_t length, f_thread_barriers_t *barriers);
#endif // _di_f_thread_barriers_adjust_

/**
 * Resize the thread barriers array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param barriers
 *   The thread barriers array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barriers_decimate_by_
  extern f_status_t f_thread_barriers_decimate_by(const f_array_length_t amount, f_thread_barriers_t *barriers);
#endif // _di_f_thread_barriers_decimate_by_

/**
 * Resize the thread barriers array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param barriers
 *   The thread barriers array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barriers_decrease_by_
  extern f_status_t f_thread_barriers_decrease_by(const f_array_length_t amount, f_thread_barriers_t *barriers);
#endif // _di_f_thread_barriers_decrease_by_

/**
 * Increase the size of the thread barriers array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param barriers
 *   The thread barriers array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barriers_increase_
  extern f_status_t f_thread_barriers_increase(f_thread_barriers_t *barriers);
#endif // _di_f_thread_barriers_increase_

/**
 * Resize the thread barriers array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param barriers
 *   The thread barriers array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barriers_increase_by_
  extern f_status_t f_thread_barriers_increase_by(const f_array_length_t amount, f_thread_barriers_t *barriers);
#endif // _di_f_thread_barriers_increase_by_

/**
 * Resize the thread barriers array.
 *
 * @param length
 *   The new size to use.
 * @param barriers
 *   The thread barriers array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_barriers_resize_
  extern f_status_t f_thread_barriers_resize(const f_array_length_t length, f_thread_barriers_t *barriers);
#endif // _di_f_thread_barriers_resize_

/**
 * Get the ID of the calling thread.
 *
 * @return
 *   ID of the calling thread
 *
 * @see pthread_self()
 */
#ifndef _di_f_thread_caller_
  extern f_thread_id_t f_thread_caller();
#endif // _di_f_thread_caller_

/**
 * Cancel a thread.
 *
 * @param id
 *   The thread to cancel.
 *
 * @return
 *   F_none on success.
 *
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cancel()
 */
#ifndef _di_f_thread_cancel_
  extern f_status_t f_thread_cancel(const f_thread_id_t id);
#endif // _di_f_thread_cancel_

/**
 * Assign a cancellation state.
 *
 * @param state
 *   The cancellation state to assign.
 * @param previous
 *   (optional) The previously assigned cancellation state.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setcancelstate()
 */
#ifndef _di_f_thread_cancel_state_set_
  extern f_status_t f_thread_cancel_state_set(const int state, int *previous);
#endif // _di_f_thread_cancel_state_set_

/**
 * Force any pending thread cancellation to be processed.
 *
 * If there is no pending thread cancel, nothing happens.
 * If there is a pending thread cancel, the thread cancels and this function never returns.
 *
 * @return
 *   F_none on success.
 *
 * @see pthread_testcancel()
 */
#ifndef _di_f_thread_cancel_test_
  extern f_status_t f_thread_cancel_test();
#endif // _di_f_thread_cancel_test_

/**
 * Assign a cancellation type.
 *
 * @param type
 *   The cancellation type to assign.
 * @param previous
 *   (optional) The previously assigned cancellation type.
 *   Set to NULL to not use.
 *   (Note: Linux allows this to be optional/NULL but POSIX does not explicitly defined this and there may be portability issues.)
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setcanceltype()
 */
#ifndef _di_f_thread_cancel_type_set_
  extern f_status_t f_thread_cancel_type_set(const int type, int *previous);
#endif // _di_f_thread_cancel_type_set_

/**
 * Get the clock ID for the given thread.
 *
 * @param id_thread
 *   The ID of the thread to use.
 * @param id_clock
 *   The retrieved clock ID.
 *
 * @return
 *   F_none on success.
 *
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_supported_not (with error bit) if per-CPU clocks are not supported by the OS.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_getcpuclockid()
 */
#ifndef _di_f_thread_clock_get_id_
  extern f_status_t f_thread_clock_get_id(const f_thread_id_t id_thread, clockid_t *id_clock);
#endif // _di_f_thread_clock_get_id_

/**
 * Compare two different thread IDs.
 *
 * POSIX designates that the thread id (pthread_t) to be loosely defined and can be anything from an integer to a structure.
 * For portability purposes, calling pthread_equal() is the only safe way to compare two thread ids.
 *
 * @return
 *   F_equal_to if the two thread IDs are the same.
 *   F_equal_to_not if the two thread IDs are different.
 *
 * @see pthread_equal()
 */
#ifndef _di_f_thread_compare_
  extern f_status_t f_thread_compare(const f_thread_id_t id1, const f_thread_id_t id2);
#endif // _di_f_thread_compare_

/**
 * Get the level of concurrency.
 *
 * A level of 0 designates the system to automatically choose concurrency level.
 * Any non-zero level is considered a hint and will be followed at the systems discretion.
 *
 * @param level
 *   The concurrency level.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if the new level would cause the system to exceed available resources.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_getconcurrency()
 */
#ifndef _di_f_thread_attribute_concurrency_get_
  extern f_status_t f_thread_attribute_concurrency_get(int *level);
#endif // _di_f_thread_attribute_concurrency_get_

/**
 * Set the level of concurrency.
 *
 * A level of 0 designates the system to automatically choose concurrency level.
 * Any non-zero level is considered a hint and will be followed at the systems discretion.
 *
 * @param level
 *   The concurrency level.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setconcurrency()
 */
#ifndef _di_f_thread_attribute_concurrency_set_
  extern f_status_t f_thread_attribute_concurrency_set(const int level);
#endif // _di_f_thread_attribute_concurrency_set_

/**
 * Initialize a attribute.
 *
 * @param attribute
 *   The attribute to set.
 *   This assigns the default to the attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_condattr_init()
 */
#ifndef _di_f_thread_condition_attribute_create_
  extern f_status_t f_thread_condition_attribute_create(f_thread_condition_attribute_t *attribute);
#endif // _di_f_thread_condition_attribute_create_

/**
 * Delete a thread attribute.
 *
 * The pthread_condattr_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param attribute
 *   The attribute to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the attribute is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_condattr_destroy()
 */
#ifndef _di_f_thread_condition_attribute_delete_
  extern f_status_t f_thread_condition_attribute_delete(f_thread_condition_attribute_t *attribute);
#endif // _di_f_thread_condition_attribute_delete_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_condition_attributes_adjust_
  extern f_status_t f_thread_condition_attributes_adjust(const f_array_length_t length, f_thread_condition_attributes_t *attributes);
#endif // _di_f_thread_condition_attributes_adjust_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_condition_attributes_decimate_by_
  extern f_status_t f_thread_condition_attributes_decimate_by(const f_array_length_t amount, f_thread_condition_attributes_t *attributes);
#endif // _di_f_thread_condition_attributes_decimate_by_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_condition_attributes_decrease_by_
  extern f_status_t f_thread_condition_attributes_decrease_by(const f_array_length_t amount, f_thread_condition_attributes_t *attributes);
#endif // _di_f_thread_condition_attributes_decrease_by_

/**
 * Increase the size of the thread attributes array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_condition_attributes_increase_
  extern f_status_t f_thread_condition_attributes_increase(f_thread_condition_attributes_t *attributes);
#endif // _di_f_thread_condition_attributes_increase_

/**
 * Resize the thread attributes array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_condition_attributes_increase_by_
  extern f_status_t f_thread_condition_attributes_increase_by(const f_array_length_t amount, f_thread_condition_attributes_t *attributes);
#endif // _di_f_thread_condition_attributes_increase_by_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_condition_attributes_resize_
  extern f_status_t f_thread_condition_attributes_resize(const f_array_length_t length, f_thread_condition_attributes_t *attributes);
#endif // _di_f_thread_condition_attributes_resize_

/**
 * Initialize a condition.
 *
 * @param attribute
 *   (optional) The attribute to set.
 *   Set to NULL to not use (in which case the default attribute is used).
 * @param condition
 *   The condition to wait on.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_init()
 */
#ifndef _di_f_thread_condition_create_
  extern f_status_t f_thread_condition_create(const f_thread_condition_attribute_t *attribute, f_thread_condition_t *condition);
#endif // _di_f_thread_condition_create_

/**
 * Delete a thread condition.
 *
 * The pthread_cond_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param condition
 *   The condition to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the condition is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_destroy()
 */
#ifndef _di_f_thread_condition_delete_
  extern f_status_t f_thread_condition_delete(f_thread_condition_t *condition);
#endif // _di_f_thread_condition_delete_

/**
 * Signal all threads waiting on a condition.
 *
 * @param condition
 *   The condition to broadcast the unblock signal to.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_broadcast()
 */
#ifndef _di_f_thread_condition_signal_all_
  extern f_status_t f_thread_condition_signal_all(f_thread_condition_t *condition);
#endif // _di_f_thread_condition_signal_all_

/**
 * Signal a thread waiting on a condition.
 *
 * Only a single thread waiting on this condition is signaled.
 *
 * @param condition
 *   The condition to broadcast the unblock signal to.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_signal()
 */
#ifndef _di_f_thread_condition_signal_
  extern f_status_t f_thread_condition_signal(f_thread_condition_t *condition);
#endif // _di_f_thread_condition_signal_

/**
 * Wait until condition is triggered.
 *
 * This is a blocking operation.
 *
 * @param condition
 *   The condition to wait on.
 * @param mutex
 *   The mutex to use for waiting on condition.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_wait()
 */
#ifndef _di_f_thread_condition_wait_
  extern f_status_t f_thread_condition_wait(f_thread_condition_t *condition, f_thread_mutex_t *mutex);
#endif // _di_f_thread_condition_wait_

/**
 * Wait until condition is triggered, blocking until the timeout expires.
 *
 * This is a semi-blocking operation.
 * This will block until timeout and then no longer block.
 *
 * @param wait
 *   The amount of time to wait for.
 *   The wait time is relative to the clock, so consider calling clock_gettime() and then adding the amount of wait time.
 * @param condition
 *   The condition to wait on.
 * @param mutex
 *   The mutex to use for waiting on condition.
 *
 * @return
 *   F_none on success.
 *   F_time on success, and wait timeout was reached before condition was triggered.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation (possibly because mutex is not owned by current thread).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_timedwait()
 */
#ifndef _di_f_thread_condition_wait_timed_
  extern f_status_t f_thread_condition_wait_timed(const struct timespec *wait, f_thread_condition_t *condition, f_thread_mutex_t *mutex);
#endif // _di_f_thread_condition_wait_timed_

/**
 * Resize the thread conditions array.
 *
 * @param length
 *   The new size to use.
 * @param conditions
 *   The string conditions array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_conditions_adjust_
  extern f_status_t f_thread_conditions_adjust(const f_array_length_t length, f_thread_conditions_t *conditions);
#endif // _di_f_thread_conditions_adjust_

/**
 * Resize the thread conditions array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param conditions
 *   The string conditions array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_conditions_decimate_by_
  extern f_status_t f_thread_conditions_decimate_by(const f_array_length_t amount, f_thread_conditions_t *conditions);
#endif // _di_f_thread_conditions_decimate_by_

/**
 * Resize the thread conditions array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param conditions
 *   The string conditions array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_conditions_decrease_by_
  extern f_status_t f_thread_conditions_decrease_by(const f_array_length_t amount, f_thread_conditions_t *conditions);
#endif // _di_f_thread_conditions_decrease_by_

/**
 * Increase the size of the thread conditions array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param conditions
 *   The string conditions array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_conditions_increase_
  extern f_status_t f_thread_conditions_increase(f_thread_conditions_t *conditions);
#endif // _di_f_thread_conditions_increase_

/**
 * Resize the thread conditions array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param conditions
 *   The string conditions array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_conditions_increase_by_
  extern f_status_t f_thread_conditions_increase_by(const f_array_length_t amount, f_thread_conditions_t *conditions);
#endif // _di_f_thread_conditions_increase_by_

/**
 * Resize the thread conditions array.
 *
 * @param length
 *   The new size to use.
 * @param conditions
 *   The string conditions array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_conditions_resize_
  extern f_status_t f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t *conditions);
#endif // _di_f_thread_conditions_resize_

/**
 * Create a thread.
 *
 * @param attribute
 *   (optional) The thread attributes.
 *   Set to NULL to use default attributes.
 * @param id
 *   The thread ID.
 *   This gets populated with the created thread ID (aka: the "child" thread).
 * @param routine
 *   The function to execute.
 * @param argument
 *   (optional) The structure containing all arguments to pass to the routine.
 *   Set to NULL to not pass an argument.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to set the scheduling policy and parameters specified in attribute.
 *   F_resource_not (with error bit) if there are not enough resources to create another thread.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_create()
 */
#ifndef _di_f_thread_create_
  extern f_status_t f_thread_create(const f_thread_attribute_t *attribute, f_thread_id_t *id, void *(*routine) (void *), void *argument);
#endif // _di_f_thread_create_

/**
 * Detatch the given thread.
 *
 * When a detached thread exits, the resources will automatically be returned to the system without needing another thread to join with it.
 *
 * Only joinable, undetached, threads are detachable.
 *
 * Once a thread is detached, it can no longer be joined.
 *
 * @param id
 *   The ID of the thread to detach.
 *
 * @return
 *   F_none on success.
 *
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_detach()
 */
#ifndef _di_f_thread_detach_
  extern f_status_t f_thread_detach(const f_thread_id_t id);
#endif // _di_f_thread_detach_

/**
 * Have the current thread exit.
 *
 * @param result
 *   The code returned by the exited thread.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_exit()
 */
#ifndef _di_f_thread_exit_
  extern f_status_t f_thread_exit(int *result);
#endif // _di_f_thread_exit_

/**
 * Wait until the given thread exits and then join it to the current thread.
 *
 * This is a blocking operation.
 *
 * @param id
 *   The ID of the thread to wait for.
 * @param result
 *   (optional) The data returned by the terminated thread (usually the exist status).
 *   If the terminated thread is cancelled, then this holds PTHREAD_CANCELED.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.ead.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thread.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_join()
 */
#ifndef _di_f_thread_join_
  extern f_status_t f_thread_join(const f_thread_id_t id, void **result);
#endif // _di_f_thread_join_

/**
 * Try to join the given thread to the current thread.
 *
 * This is a non-blocking operation.
 *
 * @param id
 *   The ID of the thread to wait for.
 * @param result
 *   (optional) The data returned by the terminated thread (usually the exist status).
 *   If the terminated thread is cancelled, then this holds PTHREAD_CANCELED.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but thread could not be joined because it has not yet exited.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.ead.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thread.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_tryjoin_np()
 */
#ifndef _di_f_thread_join_try_
  extern f_status_t f_thread_join_try(const f_thread_id_t id, void **result);
#endif // _di_f_thread_join_try_

/**
 * Try to join the given thread to the current thread, blocking until the timeout expires.
 *
 * This is a semi-blocking operation.
 * This will block until timeout and then no longer block.
 *
 * @param id
 *   The ID of the thread to wait for.
 * @param wait
 *   The amount of time to wait for.
 *   The wait time is relative to the clock, so consider calling clock_gettime() and then adding the amount of wait time.
 * @param result
 *   (optional) The data returned by the terminated thread (usually the exist status).
 *   If the terminated thread is cancelled, then this holds PTHREAD_CANCELED.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but thread could not be joined because it has not yet exited.
 *   F_time on success, but thread could not be joined because it has not yet exited and the wait timeout was reached.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thread.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_timedjoin_np()
 */
#ifndef _di_f_thread_join_timed_
  extern f_status_t f_thread_join_timed(const f_thread_id_t id, const struct timespec wait, void **result);
#endif // _di_f_thread_join_timed_

/**
 * Create a thread key.
 *
 * @param routine
 *   The function to execute for deallocation/deleting.
 * @param key
 *   The thread key.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to set the scheduling policy and parameters specified in attribute.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_key_create()
 */
#ifndef _di_f_thread_key_create_
  extern f_status_t f_thread_key_create(void (*routine) (void *), f_thread_key_t *key);
#endif // _di_f_thread_key_create_

/**
 * Delete a thread key.
 *
 * The pthread_key_delete() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param key
 *   The key to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_key_delete()
 */
#ifndef _di_f_thread_key_delete_
  extern f_status_t f_thread_key_delete(f_thread_key_t *key);
#endif // _di_f_thread_key_delete_

/**
 * Get the value of a thread key.
 *
 * @param key
 *   The thread key.
 * @param value
 *   The assigned thread key value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_getspecific()
 */
#ifndef _di_f_thread_key_get_
  extern f_status_t f_thread_key_get(const f_thread_key_t key, void **value);
#endif // _di_f_thread_key_get_

/**
 * Get the value of a thread key.
 *
 * @param key
 *   The thread key.
 * @param value
 *   The thread key value to assign.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setspecific()
 */
#ifndef _di_f_thread_key_set_
  extern f_status_t f_thread_key_set(const f_thread_key_t key, const void *value);
#endif // _di_f_thread_key_set_

/**
 * Resize the thread keys array.
 *
 * @param length
 *   The new size to use.
 * @param keys
 *   The string keys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_keys_adjust_
  extern f_status_t f_thread_keys_adjust(const f_array_length_t length, f_thread_keys_t *keys);
#endif // _di_f_thread_keys_adjust_

/**
 * Resize the thread keys array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param keys
 *   The string keys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_keys_decimate_by_
  extern f_status_t f_thread_keys_decimate_by(const f_array_length_t amount, f_thread_keys_t *keys);
#endif // _di_f_thread_keys_decimate_by_

/**
 * Resize the thread keys array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param keys
 *   The string keys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_keys_decrease_by_
  extern f_status_t f_thread_keys_decrease_by(const f_array_length_t amount, f_thread_keys_t *keys);
#endif // _di_f_thread_keys_decrease_by_

/**
 * Increase the size of the thread keys array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param keys
 *   The string keys array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_keys_increase_
  extern f_status_t f_thread_keys_increase(f_thread_keys_t *keys);
#endif // _di_f_thread_keys_increase_

/**
 * Resize the thread keys array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param keys
 *   The string keys array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_keys_increase_by_
  extern f_status_t f_thread_keys_increase_by(const f_array_length_t amount, f_thread_keys_t *keys);
#endif // _di_f_thread_keys_increase_by_

/**
 * Resize the thread keys array.
 *
 * @param length
 *   The new size to use.
 * @param keys
 *   The string keys array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_keys_resize_
  extern f_status_t f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t *keys);
#endif // _di_f_thread_keys_resize_

/**
 * Create a thread lock attribute.
 *
 * @param attribute
 *   The lock attributes to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the lock is busy.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_resource_not (with error bit) if max lockes is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlockattr_init()
 */
#ifndef _di_f_thread_lock_attribute_create_
  extern f_status_t f_thread_lock_attribute_create(f_thread_lock_attribute_t *attribute);
#endif // _di_f_thread_lock_attribute_create_

/**
 * Delete a thread lock attribute.
 *
 * The pthread_lockattr_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param attribute
 *   The attribute to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the lock is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlockattr_destroy()
 */
#ifndef _di_f_thread_lock_attribute_delete_
  extern f_status_t f_thread_lock_attribute_delete(f_thread_lock_attribute_t *attribute);
#endif // _di_f_thread_lock_attribute_delete_

/**
 * Get the lock attribute process shared thread attribute.
 *
 * @param attribute
 *   The lock attribute.
 * @param shared
 *   The lock shared attribute value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlockattr_getpshared()
 */
#ifndef _di_f_thread_lock_attribute_shared_get_
  extern f_status_t f_thread_lock_attribute_shared_get(const f_thread_lock_attribute_t *attribute, int *shared);
#endif // _di_f_thread_lock_attribute_shared_get_

/**
 * Set the lock attribute process shared thread attribute.
 *
 * @param attribute
 *   The lock attribute.
 * @param shared
 *   The lock shared attribute value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlockattr_setpshared()
 */
#ifndef _di_f_thread_lock_attribute_shared_set_
  extern f_status_t f_thread_lock_attribute_shared_set(const int shared, f_thread_lock_attribute_t *attribute);
#endif // _di_f_thread_lock_attribute_shared_set_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_lock_attributes_adjust_
  extern f_status_t f_thread_lock_attributes_adjust(const f_array_length_t length, f_thread_lock_attributes_t *attributes);
#endif // _di_f_thread_lock_attributes_adjust_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_lock_attributes_decimate_by_
  extern f_status_t f_thread_lock_attributes_decimate_by(const f_array_length_t amount, f_thread_lock_attributes_t *attributes);
#endif // _di_f_thread_lock_attributes_decimate_by_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_lock_attributes_decrease_by_
  extern f_status_t f_thread_lock_attributes_decrease_by(const f_array_length_t amount, f_thread_lock_attributes_t *attributes);
#endif // _di_f_thread_lock_attributes_decrease_by_

/**
 * Increase the size of the thread attributes array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_lock_attributes_increase_
  extern f_status_t f_thread_lock_attributes_increase(f_thread_lock_attributes_t *attributes);
#endif // _di_f_thread_lock_attributes_increase_

/**
 * Resize the thread attributes array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_lock_attributes_increase_by_
  extern f_status_t f_thread_lock_attributes_increase_by(const f_array_length_t amount, f_thread_lock_attributes_t *attributes);
#endif // _di_f_thread_lock_attributes_increase_by_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_lock_attributes_resize_
  extern f_status_t f_thread_lock_attributes_resize(const f_array_length_t length, f_thread_lock_attributes_t *attributes);
#endif // _di_f_thread_lock_attributes_resize_

/**
 * Create a thread read/write lock.
 *
 * @param attribute
 *   The lock attribute.
 * @param lock
 *   The lock to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max lockes is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_init()
 */
#ifndef _di_f_thread_lock_create_
  extern f_status_t f_thread_lock_create(const f_thread_lock_attribute_t *attribute, f_thread_lock_t *lock);
#endif // _di_f_thread_lock_create_

/**
 * Delete a thread read/write lock.
 *
 * The pthread_lock_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param lock
 *   The lock to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the lock is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_destroy()
 */
#ifndef _di_f_thread_lock_delete_
  extern f_status_t f_thread_lock_delete(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_delete_

/**
 * Lock the read part of a read/write lock.
 *
 * This is a blocking function.
 *
 * @param lock
 *   The thread lock.
 *
 * @return
 *   F_none on success.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_rdlock()
 */
#ifndef _di_f_thread_lock_read_
  extern f_status_t f_thread_lock_read(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_read_

/**
 * Lock the read part of a read/write lock, waiting for a set period of time to get the lock if already locked.
 *
 * If the read part of the read/write lock is already locked and the timeout expires, then the lock attempt fails.
 *
 * This is a blocking function (until timeout expires).
 *
 * @param timeout
 *   The timeout.
 * @param lock
 *   The read/write lock.
 *
 * @return
 *   F_none on success.
 *   F_time if the timeout was reached before obtaining the lock.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_timedrdlock()
 */
#ifndef _di_f_thread_lock_read_timed_
  extern f_status_t f_thread_lock_read_timed(const struct timespec *timeout, f_thread_lock_t *lock);
#endif // _di_f_thread_lock_read_timed_

/**
 * Try to lock the read part of a read/write lock.
 *
 * If lock is already locked, return immediately.
 *
 * This is a non-blocking function.
 *
 * @param lock
 *   The thread lock.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but the lock is already locked.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_tryrdlock()
 */
#ifndef _di_f_thread_lock_read_try_
  extern f_status_t f_thread_lock_read_try(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_read_try_

/**
 * Lock the write part of a read/write lock.
 *
 * This is a blocking function.
 *
 * @param lock
 *   The thread lock.
 *
 * @return
 *   F_none on success.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_wrlock()
 */
#ifndef _di_f_thread_lock_write_
  extern f_status_t f_thread_lock_write(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_write_

/**
 * Lock the write part of a read/write lock, waiting for a set period of time to get the lock if already locked.
 *
 * If the write part of the read/write lock is already locked and the timeout expires, then the lock attempt fails.
 *
 * This is a blocking function (until timeout expires).
 *
 * @param timeout
 *   The timeout.
 * @param lock
 *   The read/write lock.
 *
 * @return
 *   F_none on success.
 *   F_time if the timeout was reached before obtaining the lock.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_timedwrlock()
 */
#ifndef _di_f_thread_lock_write_timed_
  extern f_status_t f_thread_lock_write_timed(const struct timespec *timeout, f_thread_lock_t *lock);
#endif // _di_f_thread_lock_write_timed_

/**
 * Try to lock the read part of a read/write lock.
 *
 * If lock is already locked, return immediately.
 *
 * This is a non-blocking function.
 *
 * @param lock
 *   The thread lock.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but the lock is already locked.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_trywrlock()
 */
#ifndef _di_f_thread_lock_write_try_
  extern f_status_t f_thread_lock_write_try(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_write_try_

/**
 * Resize the read/write locks array.
 *
 * @param length
 *   The new size to use.
 * @param locks
 *   The string locks array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_adjust_
  extern f_status_t f_thread_locks_adjust(const f_array_length_t length, f_thread_locks_t *locks);
#endif // _di_f_thread_locks_adjust_

/**
 * Resize the read/write locks array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param locks
 *   The string locks array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_decimate_by_
  extern f_status_t f_thread_locks_decimate_by(const f_array_length_t amount, f_thread_locks_t *locks);
#endif // _di_f_thread_locks_decimate_by_

/**
 * Resize the read/write locks array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param locks
 *   The string locks array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_decrease_by_
  extern f_status_t f_thread_locks_decrease_by(const f_array_length_t amount, f_thread_locks_t *locks);
#endif // _di_f_thread_locks_decrease_by_

/**
 * Increase the size of the read/write array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param locks
 *   The string locks array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_increase_
  extern f_status_t f_thread_locks_increase(f_thread_locks_t *locks);
#endif // _di_f_thread_locks_increase_

/**
 * Resize the read/write locks array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param locks
 *   The string locks array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_increase_by_
  extern f_status_t f_thread_locks_increase_by(const f_array_length_t amount, f_thread_locks_t *locks);
#endif // _di_f_thread_locks_increase_by_

/**
 * Resize the read/write locks array.
 *
 * @param length
 *   The new size to use.
 * @param locks
 *   The string locks array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_locks_resize_
  extern f_status_t f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t *locks);
#endif // _di_f_thread_locks_resize_

/**
 * Create a thread mutex attribute.
 *
 * @param attribute
 *   The mutex attributes to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the mutex is busy.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_resource_not (with error bit) if max mutexes is reached.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_init()
 */
#ifndef _di_f_thread_mutex_attribute_create_
  extern f_status_t f_thread_mutex_attribute_create(f_thread_mutex_attribute_t *attribute);
#endif // _di_f_thread_mutex_attribute_create_

/**
 * Delete a thread mutex attribute.
 *
 * The pthread_mutexattr_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param attribute
 *   The attribute to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the mutex is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_destroy()
 */
#ifndef _di_f_thread_mutex_attribute_delete_
  extern f_status_t f_thread_mutex_attribute_delete(f_thread_mutex_attribute_t *attribute);
#endif // _di_f_thread_mutex_attribute_delete_

/**
 * Get the mutex attribute priority ceiling.
 *
 * @param attribute
 *   The thread mutex attribute.
 * @param ceiling
 *   The priority ceiling.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *
 * @see pthread_mutexattr_getprioceiling()
 */
#ifndef _di_f_thread_mutex_attribute_priority_ceiling_get_
  extern f_status_t f_thread_mutex_attribute_priority_ceiling_get(const f_thread_mutex_attribute_t *attribute, int *ceiling);
#endif // _di_f_thread_mutex_attribute_priority_ceiling_get_

/**
 * Set the mutex attribute priority ceiling.
 *
 * @param ceiling
 *   The priority ceiling.
 * @param attribute
 *   The thread mutex attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *
 * @see pthread_mutexattr_setprioceiling()
 */
#ifndef _di_f_thread_mutex_attribute_priority_ceiling_set_
  extern f_status_t f_thread_mutex_attribute_priority_ceiling_set(const int ceiling, f_thread_mutex_attribute_t *attribute);
#endif // _di_f_thread_mutex_attribute_priority_ceiling_set_

/**
 * Get the mutex attribute process shared thread attribute.
 *
 * @param attribute
 *   The mutex attribute.
 * @param shared
 *   The mutex shared attribute value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_getpshared()
 */
#ifndef _di_f_thread_mutex_attribute_shared_get_
  extern f_status_t f_thread_mutex_attribute_shared_get(const f_thread_mutex_attribute_t *attribute, int *shared);
#endif // _di_f_thread_mutex_attribute_shared_get_

/**
 * Set the mutex attribute process shared thread attribute.
 *
 * @param attribute
 *   The mutex attribute.
 * @param shared
 *   The mutex shared attribute value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_setpshared()
 */
#ifndef _di_f_thread_mutex_attribute_shared_set_
  extern f_status_t f_thread_mutex_attribute_shared_set(const int shared, f_thread_mutex_attribute_t *attribute);
#endif // _di_f_thread_mutex_attribute_shared_set_

/**
 * Get the mutex attribute type.
 *
 * @param attribute
 *   The mutex attribute.
 * @param type
 *   The type.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_gettype()
 */
#ifndef _di_f_thread_mutex_attribute_type_get_
  extern f_status_t f_thread_mutex_attribute_type_get(const f_thread_mutex_attribute_t *attribute, int *type);
#endif // _di_f_thread_mutex_attribute_type_get_

/**
 * Set the mutex attribute process shared thread attribute.
 *
 * @param type
 *   The type.
 * @param attribute
 *   The mutex attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_settype()
 */
#ifndef _di_f_thread_mutex_attribute_type_set_
  extern f_status_t f_thread_mutex_attribute_type_set(const int type, f_thread_mutex_attribute_t *attribute);
#endif // _di_f_thread_mutex_attribute_type_set_

/**
 * Get the mutex attribute protocol.
 *
 * @param attribute
 *   The thread mutex attribute.
 * @param protocol
 *   The protocol.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_getprotocol()
 */
#ifndef _di_f_thread_mutex_attribute_protocol_get_
  extern f_status_t f_thread_mutex_attribute_protocol_get(const f_thread_mutex_attribute_t *attribute, int *protocol);
#endif // _di_f_thread_mutex_attribute_protocol_get_

/**
 * Set the mutex attribute protocol.
 *
 * @param protocol
 *   The protocol.
 * @param attribute
 *   The thread mutex attribute.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_supported_not (with error bit) if the protocol is not supported.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutexattr_setprotocol()
 */
#ifndef _di_f_thread_mutex_attribute_protocol_set_
  extern f_status_t f_thread_mutex_attribute_protocol_set(const int protocol, f_thread_mutex_attribute_t *attribute);
#endif // _di_f_thread_mutex_attribute_protocol_set_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_adjust_
  extern f_status_t f_thread_mutex_attributes_adjust(const f_array_length_t length, f_thread_mutex_attributes_t *attributes);
#endif // _di_f_thread_mutex_attributes_adjust_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_decimate_by_
  extern f_status_t f_thread_mutex_attributes_decimate_by(const f_array_length_t amount, f_thread_mutex_attributes_t *attributes);
#endif // _di_f_thread_mutex_attributes_decimate_by_

/**
 * Resize the thread attributes array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_decrease_by_
  extern f_status_t f_thread_mutex_attributes_decrease_by(const f_array_length_t amount, f_thread_mutex_attributes_t *attributes);
#endif // _di_f_thread_mutex_attributes_decrease_by_

/**
 * Increase the size of the thread attributes array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_increase_
  extern f_status_t f_thread_mutex_attributes_increase(f_thread_mutex_attributes_t *attributes);
#endif // _di_f_thread_mutex_attributes_increase_

/**
 * Resize the thread attributes array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param attributes
 *   The string attributes array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_increase_by_
  extern f_status_t f_thread_mutex_attributes_increase_by(const f_array_length_t amount, f_thread_mutex_attributes_t *attributes);
#endif // _di_f_thread_mutex_attributes_increase_by_

/**
 * Resize the thread attributes array.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The string attributes array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutex_attributes_resize_
  extern f_status_t f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t *attributes);
#endif // _di_f_thread_mutex_attributes_resize_

/**
 * Create a thread mutex.
 *
 * @param attribute
 *   (optional) The mutex attributes to set.
 *   Set to NULL to not use (in which case the default attributes are used).
 * @param mutex
 *   The mutex to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the mutex is busy.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_resource_not (with error bit) if max mutexes is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_init()
 */
#ifndef _di_f_thread_mutex_create_
  extern f_status_t f_thread_mutex_create(f_thread_mutex_attribute_t * const attribute, f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_create_

/**
 * Delete a thread mutex.
 *
 * The pthread_mutex_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param mutex
 *   The mutex to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the mutex is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_destroy()
 */
#ifndef _di_f_thread_mutex_delete_
  extern f_status_t f_thread_mutex_delete(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_delete_

/**
 * Lock the mutex.
 *
 * This is a blocking function.
 *
 * @param mutex
 *   The thread mutex.
 *
 * @return
 *   F_none on success.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_lock()
 */
#ifndef _di_f_thread_mutex_lock_
  extern f_status_t f_thread_mutex_lock(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_lock_

/**
 * Lock the mutex, waiting for a set period of time to get the lock if already locked.
 *
 * If the mutex is already locked and the timeout expires, then the lock attempt fails.
 *
 * This is a blocking function (until timeout expires).
 *
 * @param timeout
 *   The timeout.
 * @param mutex
 *   The thread mutex.
 *
 * @return
 *   F_none on success.
 *   F_time if the timeout was reached before obtaining the lock.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_recover_not (with error bit) if the state protected by the mutex is not recoverable.
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *   F_thread_not (with error bit) if the owning thread terminated while holding the mutex lock (thread is dead).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_timedlock()
 */
#ifndef _di_f_thread_mutex_lock_timed_
  extern f_status_t f_thread_mutex_lock_timed(const struct timespec *timeout, f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_lock_timed_

/**
 * Try to lock the mutex.
 *
 * If mutex is already locked, return immediately.
 *
 * This is a non-blocking function.
 *
 * @param mutex
 *   The thread mutex.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but the mutex is already locked.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_trylock()
 */
#ifndef _di_f_thread_mutex_lock_try_
  extern f_status_t f_thread_mutex_lock_try(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_lock_try_

/**
 * Get the mutex priority ceiling.
 *
 * @param mutex
 *   The thread mutex.
 * @param ceiling
 *   The priority ceiling.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_getprioceiling()
 */
#ifndef _di_f_thread_mutex_priority_ceiling_get_
  extern f_status_t f_thread_mutex_priority_ceiling_get(f_thread_mutex_t *mutex, int *ceiling);
#endif // _di_f_thread_mutex_priority_ceiling_get_

/**
 * Set the mutex priority ceiling.
 *
 * @param ceiling
 *   The priority ceiling.
 * @param mutex
 *   The thread mutex.
 * @param previous
 *   (optional) The previous priority ceiling.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_recover_not (with error bit) if the state protected by the mutex is not recoverable (for a "robust" mutex).
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *   F_thread_not (with error bit) if the owning thread terminated while holding the mutex lock (thread is dead).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_setprioceiling()
 */
#ifndef _di_f_thread_mutex_priority_ceiling_set_
  extern f_status_t f_thread_mutex_priority_ceiling_set(const int ceiling, f_thread_mutex_t *mutex, int *previous);
#endif // _di_f_thread_mutex_priority_ceiling_set_

/**
 * Unlock the mutex.
 *
 * @param mutex
 *   The thread mutex.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation (possibly because mutex is not owned by current thread).
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_unlock()
 */
#ifndef _di_f_thread_mutex_unlock_
  extern f_status_t f_thread_mutex_unlock(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_unlock_

/**
 * Resize the thread mutexs array.
 *
 * @param length
 *   The new size to use.
 * @param mutexs
 *   The string mutexs array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutexs_adjust_
  extern f_status_t f_thread_mutexs_adjust(const f_array_length_t length, f_thread_mutexs_t *mutexs);
#endif // _di_f_thread_mutexs_adjust_

/**
 * Resize the thread mutexs array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param mutexs
 *   The string mutexs array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutexs_decimate_by_
  extern f_status_t f_thread_mutexs_decimate_by(const f_array_length_t amount, f_thread_mutexs_t *mutexs);
#endif // _di_f_thread_mutexs_decimate_by_

/**
 * Resize the thread mutexs array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param mutexs
 *   The string mutexs array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutexs_decrease_by_
  extern f_status_t f_thread_mutexs_decrease_by(const f_array_length_t amount, f_thread_mutexs_t *mutexs);
#endif // _di_f_thread_mutexs_decrease_by_

/**
 * Increase the size of the thread mutexs array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param mutexs
 *   The string mutexs array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutexs_increase_
  extern f_status_t f_thread_mutexs_increase(f_thread_mutexs_t *mutexs);
#endif // _di_f_thread_mutexs_increase_

/**
 * Resize the thread mutexs array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param mutexs
 *   The string mutexs array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutexs_increase_by_
  extern f_status_t f_thread_mutexs_increase_by(const f_array_length_t amount, f_thread_mutexs_t *mutexs);
#endif // _di_f_thread_mutexs_increase_by_

/**
 * Resize the thread mutexs array.
 *
 * @param length
 *   The new size to use.
 * @param mutexs
 *   The string mutexs array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_mutexs_resize_
  extern f_status_t f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t *mutexs);
#endif // _di_f_thread_mutexs_resize_

/**
 * Call the given routine only one time and never again.
 *
 * Subsequent calls will not call the given routine.
 *
 * @param once
 *   The once variable designating that the given routine will be called only once.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_once()
 */
#ifndef _di_f_thread_once_
  extern f_status_t f_thread_once(void (*routine) (void), f_thread_once_t *once);
#endif // _di_f_thread_once_

/**
 * Get the thread scheduler parameter.
 *
 * @param id
 *   The thread ID.
 * @param policy
 *   The scheduler policy
 * @param parameter
 *   The scheduler parameter
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the policy or scheduling parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_getschedparam()
 */
#ifndef _di_f_thread_scheduler_parameter_get_
  extern f_status_t f_thread_scheduler_parameter_get(const f_thread_id_t id, int *policy, struct sched_param *parameter);
#endif // _di_f_thread_scheduler_parameter_get_

/**
 * Set the thread scheduler parameter.
 *
 * @param id
 *   The thread ID.
 * @param policy
 *   The scheduler policy
 * @param parameter
 *   The scheduler parameter
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if insufficient privileges or scheduler (or policy) does not allow operation.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setschedparam()
 */
#ifndef _di_f_thread_scheduler_parameter_set_
  extern f_status_t f_thread_scheduler_parameter_set(const f_thread_id_t id, const int policy, const struct sched_param *parameter);
#endif // _di_f_thread_scheduler_parameter_set_

/**
 * Set the thread scheduler priority.
 *
 * @param id
 *   The thread ID.
 * @param priority
 *   The scheduler priority.
 *
 * @return
 *   F_none on success.
 *
 *   F_found_not (with error bit) no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if insufficient privileges.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_setschedprio()
 */
#ifndef _di_f_thread_scheduler_priority_set_
  extern f_status_t f_thread_scheduler_priority_set(const f_thread_id_t id, const int priority);
#endif // _di_f_thread_scheduler_priority_set_

/**
 * Create a thread semaphore.
 *
 * @param shared
 *   If TRUE, then the semaphore is shared between processes (stored as posix shared memory, memory mapped, etc..).
 *   IF FALSE, then the semphore is shared between threads of a process (stored as a global variable or in the heap).
 *   Not all systems support semaphores shared amongst processes.
 * @param value
 *   The value to initially assign the semaphore on creation.
 * @param semaphore
 *   The semaphore to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the system does not support the process shared semaphore (shared == true).
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_init()
 */
#ifndef _di_f_thread_semaphore_create_
  extern f_status_t f_thread_semaphore_create(const bool shared, const unsigned int value, f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_create_

/**
 * Delete a thread semaphore.
 *
 * The sem_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param semaphore
 *   The semaphore to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the semaphore is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_destroy()
 */
#ifndef _di_f_thread_semaphore_delete_
  extern f_status_t f_thread_semaphore_delete(f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_delete_

/**
 * Create a thread (named) semaphore.
 *
 * @param name
 *   The semaphore file name to create.
 * @param flag
 *   The file create/open flags.
 * @param mode
 *   (optional) The file permissions to assign the semaphore.
 *   Ignored if O_CREAT is not used in flag.
 *   Ignored if the named semaphore already exists.
 * @param value
 *   (optional) The value to initially assign the semaphore on creation.
 *   Ignored if O_CREAT is not used in flag.
 *   Ignored if the named semaphore already exists.
 * @param semaphore
 *   The thread semaphore.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_file_descriptor_max (with error bit) if max file descrriptors was reached.
 *   F_file_found (with error bit) if the file was found and both the O_CREAT and O_EXCL flags are set.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_found_not (with error bit) if the file was not found and the O_CREAT is not set.
 *   F_name_not (with error bit) if file name is too long.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the system does not support the process shared semaphore (shared == true).
 *   F_memory_not (with error bit) if out of memory.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_open()
 */
#ifndef _di_f_thread_semaphore_file_create_
  extern f_status_t f_thread_semaphore_file_create(const f_string_t name, const int flag, mode_t mode, unsigned int value, f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_file_create_

/**
 * Delete a thread (named) semaphore.
 *
 * A named semaphore should be deleted with this function or with f_thread_semephore_file_destroy().
 *
 * @param semaphore
 *   The semaphore to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * A named semaphore should be deleted with this function or with f_thread_semephore_file_destroy().
 *
 * @see sem_close()
 *
 * @see f_thread_semaphore_file_destroy()
 */
#ifndef _di_f_thread_semaphore_file_delete_
  extern f_status_t f_thread_semaphore_file_delete(f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_file_delete_

/**
 * Destroy a thread (named) semaphore.
 *
 * This will immediately delete the semaphore file and all processes holding this semaphore will be forced to close.
 *
 * A named semaphore should be deleted with this function or with f_thread_semephore_file_delete().
 *
 * @param name
 *   The semaphore name to delete.
 *
 * @return
 *   F_none on success.
 *   F_file_found_not the named file was not found.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_name_not (with error bit) if file name is too long.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_unlink()
 *
 * @see f_thread_semaphore_file_delete()
 */
#ifndef _di_f_thread_semaphore_file_destroy_
  extern f_status_t f_thread_semaphore_file_destroy(const f_string_t name);
#endif // _di_f_thread_semaphore_file_destroy_

/**
 * Lock the semaphore.
 *
 * This is a blocking function.
 *
 * @param semaphore
 *   The thread semaphore.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_interrupt (with error bit) if returned due to an interrupt signal.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_wait()
 */
#ifndef _di_f_thread_semaphore_lock_
  extern f_status_t f_thread_semaphore_lock(f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_lock_

/**
 * Lock the semaphore, waiting for a set period of time to get the lock if already locked.
 *
 * If the semaphore is already locked and the timeout expires, then the lock attempt fails.
 *
 * This is a blocking function (until timeout expires).
 *
 * @param timeout
 *   The timeout.
 * @param semaphore
 *   The thread semaphore.
 *
 * @return
 *   F_none on success.
 *   F_time if the timeout was reached before obtaining the lock.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_interrupt (with error bit) if returned due to an interrupt signal.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_timedwait()
 */
#ifndef _di_f_thread_semaphore_lock_timed_
  extern f_status_t f_thread_semaphore_lock_timed(const struct timespec *timeout, f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_lock_timed_

/**
 * Try to lock the semaphore.
 *
 * If semaphore is already locked, return immediately.
 *
 * This is a non-blocking function.
 *
 * @param semaphore
 *   The thread semaphore.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_interrupt (with error bit) if returned due to an interrupt signal.
 *   F_resource_not (with error bit) if max semaphore locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_trywait()
 */
#ifndef _di_f_thread_semaphore_lock_try_
  extern f_status_t f_thread_semaphore_lock_try(f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_lock_try_

/**
 * Unlock the semaphore.
 *
 * @param semaphore
 *   The thread semaphore.
 *
 * @return
 *   F_none on success.
 *
 *   F_number_overflow (with error bit) if max semaphore value is reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_post()
 */
#ifndef _di_f_thread_semaphore_unlock_
  extern f_status_t f_thread_semaphore_unlock(f_thread_semaphore_t *semaphore);
#endif // _di_f_thread_semaphore_unlock_

/**
 * Get the semaphore value.
 *
 * @param semaphore
 *   The thread semaphore.
 * @param value
 *   The semaphore's value.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see sem_getvalue()
 */
#ifndef _di_f_thread_semaphore_value_get_
  extern f_status_t f_thread_semaphore_value_get(f_thread_semaphore_t *semaphore, int *value);
#endif // _di_f_thread_semaphore_value_get_

/**
 * Resize the thread semaphores array.
 *
 * @param length
 *   The new size to use.
 * @param semaphores
 *   The string semaphores array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_semaphores_adjust_
  extern f_status_t f_thread_semaphores_adjust(const f_array_length_t length, f_thread_semaphores_t *semaphores);
#endif // _di_f_thread_semaphores_adjust_

/**
 * Resize the thread semaphores array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param semaphores
 *   The string semaphores array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_semaphores_decimate_by_
  extern f_status_t f_thread_semaphores_decimate_by(const f_array_length_t amount, f_thread_semaphores_t *semaphores);
#endif // _di_f_thread_semaphores_decimate_by_

/**
 * Resize the thread semaphores array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param semaphores
 *   The string semaphores array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_semaphores_decrease_by_
  extern f_status_t f_thread_semaphores_decrease_by(const f_array_length_t amount, f_thread_semaphores_t *semaphores);
#endif // _di_f_thread_semaphores_decrease_by_

/**
 * Increase the size of the thread semaphores array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param semaphores
 *   The string semaphores array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_semaphores_increase_
  extern f_status_t f_thread_semaphores_increase(f_thread_semaphores_t *semaphores);
#endif // _di_f_thread_semaphores_increase_

/**
 * Resize the thread semaphores array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param semaphores
 *   The string semaphores array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_semaphores_increase_by_
  extern f_status_t f_thread_semaphores_increase_by(const f_array_length_t amount, f_thread_semaphores_t *semaphores);
#endif // _di_f_thread_semaphores_increase_by_

/**
 * Resize the thread semaphores array.
 *
 * @param length
 *   The new size to use.
 * @param semaphores
 *   The string semaphores array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_semaphores_resize_
  extern f_status_t f_thread_semaphores_resize(const f_array_length_t length, f_thread_semaphores_t *semaphores);
#endif // _di_f_thread_semaphores_resize_

/**
 * Resize the thread sets array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_adjust_
  extern f_status_t f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t *sets);
#endif // _di_f_thread_sets_adjust_

/**
 * Resize the thread sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_decimate_by_
  extern f_status_t f_thread_sets_decimate_by(const f_array_length_t amount, f_thread_sets_t *sets);
#endif // _di_f_thread_sets_decimate_by_

/**
 * Resize the thread sets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_decrease_by_
  extern f_status_t f_thread_sets_decrease_by(const f_array_length_t amount, f_thread_sets_t *sets);
#endif // _di_f_thread_sets_decrease_by_

/**
 * Increase the size of the thread sets array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_increase_
  extern f_status_t f_thread_sets_increase(f_thread_sets_t *sets);
#endif // _di_f_thread_sets_increase_

/**
 * Resize the thread sets array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param sets
 *   The string sets array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_increase_by_
  extern f_status_t f_thread_sets_increase_by(const f_array_length_t amount, f_thread_sets_t *sets);
#endif // _di_f_thread_sets_increase_by_

/**
 * Resize the thread sets array.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The string sets array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_sets_resize_
  extern f_status_t f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *sets);
#endif // _di_f_thread_sets_resize_

/**
 * Send a signal to the given thread.
 *
 * @param id
 *   The ID of the thread to signal.
 * @param signal
 *   The signal to send to the thread.
 *   If 0 is used instead of a valid signal, then instead check to see if the thread exists.
 *
 * @return
 *   F_none on success and signal is not 0.
 *   F_found on success, signal is 0, and the thread by the given ID does exist.
 *
 *   F_found_not on success, signal is 0, and the thread by the given ID does not exist.
 *   F_found_not (with error bit) if no thread by the given ID was found (and signal is not 0).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_kill()
 */
#ifndef _di_f_thread_signal_
  extern f_status_t f_thread_signal(const f_thread_id_t id, const int signal);
#endif // _di_f_thread_signal_

/**
 * Get or assign the current signal set in use.
 *
 * Either set or previous may be NULL but not both (at least one is required).
 *
 * @param how
 *   How to handle the signal.
 *   Set this to 0 when only trying to get the current signal set.
 * @param next
 *   (optional) The new set of signals to handle.
 *   Set to NULL to not use.
 * @param current
 *   (optional) The current set of signals being handled.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_sigmask()
 */
#ifndef _di_f_thread_signal_mask_
  extern f_status_t f_thread_signal_mask(const int how, const sigset_t *next, sigset_t *current);
#endif // _di_f_thread_signal_mask_

/**
 * Send the signal and value to the given thread.
 *
 * @param id
 *   The ID of the thread to signal.
 * @param signal
 *   The signal to send to the thread.
 * @param value
 *   The signal value to send.
 *
 * @return
 *   F_none on success but no signal found.
 *
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if the max signals is reached.
 *   F_supported_not (with error bit) if this action is not supported by the current OS.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_sigqueue()
 */
#ifndef _di_f_thread_signal_queue_
  extern f_status_t f_thread_signal_queue(const f_thread_id_t id, const int signal, const union sigval value);
#endif // _di_f_thread_signal_queue_

/**
 * Create a thread spin lock.
 *
 * @param shared
 *   The shared process setting.
 * @param spin
 *   The spin to create.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max spines is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_spin_init()
 */
#ifndef _di_f_thread_spin_create_
  extern f_status_t f_thread_spin_create(const int shared, f_thread_spin_t *spin);
#endif // _di_f_thread_spin_create_

/**
 * Delete a thread spin lock.
 *
 * The pthread_spin_destroy() function has no distinction like the *_destroy() and the *_delete() used by the FLL project.
 * Therefore there is only this function for both deleting and destroying.
 *
 * @param spin
 *   The spin to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the spin is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_spin_destroy()
 */
#ifndef _di_f_thread_spin_delete_
  extern f_status_t f_thread_spin_delete(f_thread_spin_t *spin);
#endif // _di_f_thread_spin_delete_

/**
 * Lock the spin lock.
 *
 * This is a blocking function.
 *
 * @param spin
 *   The thread spin.
 *
 * @return
 *   F_none on success.
 *
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max spin locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_spin_lock()
 */
#ifndef _di_f_thread_spin_lock_
  extern f_status_t f_thread_spin_lock(f_thread_spin_t *spin);
#endif // _di_f_thread_spin_lock_

/**
 * Try to lock the spin lock.
 *
 * If spin is already locked, return immediately.
 *
 * This is a non-blocking function.
 *
 * @param spin
 *   The thread spin.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but the spin is already locked.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max spin locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_spin_trylock()
 */
#ifndef _di_f_thread_spin_lock_try_
  extern f_status_t f_thread_spin_lock_try(f_thread_spin_t *spin);
#endif // _di_f_thread_spin_lock_try_

/**
 * Unlock the spin lock.
 *
 * @param spin
 *   The thread spin.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation (possibly because spin is not owned by current thread).
 *   F_resource_not (with error bit) if max spin locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_spin_unlock()
 */
#ifndef _di_f_thread_spin_unlock_
  extern f_status_t f_thread_spin_unlock(f_thread_spin_t *spin);
#endif // _di_f_thread_spin_unlock_

/**
 * Resize the thread spin locks array.
 *
 * @param length
 *   The new size to use.
 * @param spins
 *   The string spins array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_spins_adjust_
  extern f_status_t f_thread_spins_adjust(const f_array_length_t length, f_thread_spins_t *spins);
#endif // _di_f_thread_spins_adjust_

/**
 * Resize the thread spin locks array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param spins
 *   The string spins array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_spins_decimate_by_
  extern f_status_t f_thread_spins_decimate_by(const f_array_length_t amount, f_thread_spins_t *spins);
#endif // _di_f_thread_spins_decimate_by_

/**
 * Resize the thread spin locks array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param spins
 *   The string spins array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_spins_decrease_by_
  extern f_status_t f_thread_spins_decrease_by(const f_array_length_t amount, f_thread_spins_t *spins);
#endif // _di_f_thread_spins_decrease_by_

/**
 * Increase the size of the thread spin locks array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param spins
 *   The string spins array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_spins_increase_
  extern f_status_t f_thread_spins_increase(f_thread_spins_t *spins);
#endif // _di_f_thread_spins_increase_

/**
 * Resize the thread spin locks array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param spins
 *   The string spins array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_spins_increase_by_
  extern f_status_t f_thread_spins_increase_by(const f_array_length_t amount, f_thread_spins_t *spins);
#endif // _di_f_thread_spins_increase_by_

/**
 * Resize the thread spin locks array.
 *
 * @param length
 *   The new size to use.
 * @param spins
 *   The string spins array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_thread_spins_resize_
  extern f_status_t f_thread_spins_resize(const f_array_length_t length, f_thread_spins_t *spins);
#endif // _di_f_thread_spins_resize_

/**
 * Unlock the read/write lock.
 *
 * @param lock
 *   The thread lock.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation (possibly because lock is not owned by current thread).
 *   F_resource_not (with error bit) if max lock locks is reached.
 *
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_rwlock_unlock()
 */
#ifndef _di_f_thread_unlock_
  extern f_status_t f_thread_unlock(f_thread_lock_t *lock);
#endif // _di_f_thread_unlock_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_h

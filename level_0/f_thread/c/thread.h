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
#include <signal.h>
#include <sys/types.h>
#include <time.h>
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) if out of memory.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setaffinity_np()
 */
#ifndef _di_f_thread_attribute_affinity_set_
  extern f_status_t f_thread_attribute_affinity_set(const size_t affinity_size, const cpu_set_t *affinity_set, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_affinity_set_

/**
 * Create (initialize) a thread attribute structure.
 *
 * @param attribute
 *   The thread attributes to create.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) if out of memory.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 * @param attribute
 *   The thread attributes to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the scope is not supported by the current OS (such as Linux not supporting PTHREAD_SCOPE_PROCESS).
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
 *   F_access_denied (with error bit) if the caller cannot both read and write to the stack address.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   The size of the stack_set.
 * @param stack
 *   The stack to assign.
 * @param attribute
 *   The thread attributes to update.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) if the caller cannot both read and write to the stack address.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_attr_setstack()
 */
#ifndef _di_f_thread_attribute_stack_set_
  extern f_status_t f_thread_attribute_stack_set(const size_t stack_size, void * const stack, f_thread_attribute_t *attribute);
#endif // _di_f_thread_attribute_stack_set_

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
 *   F_found_not (with error bit) if no thread by the given ID was found.
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
 *   (Note: Linux allows this to be optional/NULL but POSIX does not explicitly defined this and there may be portability issues.)
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_supported_not (with error bit) if per-CPU clocks are not supported by the OS.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_equal()
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
 * Unblock all threads waiting on a condition.
 *
 * @param condition
 *   The condition to broadcast the unblock signal to.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_broadcast()
 */
#ifndef _di_f_thread_condition_unblock_all_
  extern f_status_t f_thread_condition_unblock_all(f_thread_condition_t *condition);
#endif // _di_f_thread_condition_unblock_all_

/**
 * Unblock all threads waiting on a condition.
 *
 * @param condition
 *   The condition to broadcast the unblock signal to.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_signal()
 */
#ifndef _di_f_thread_condition_unblock_any_
  extern f_status_t f_thread_condition_unblock_any(f_thread_condition_t *condition);
#endif // _di_f_thread_condition_unblock_any_

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
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation (possibly because mutex is not owned by current thread).
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_cond_timedwait()
 */
#ifndef _di_f_thread_condition_wait_timed_
  extern f_status_t f_thread_condition_wait_timed(const struct timespec *wait, f_thread_condition_t *condition, f_thread_mutex_t *mutex);
#endif // _di_f_thread_condition_wait_timed_

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
 *   F_deadlock (with error bit) if operation would cause a deadlock.ead.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thr
 *
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
 *   F_deadlock (with error bit) if operation would cause a deadlock.ead.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thr
 *
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
 *   F_deadlock (with error bit) if operation would cause a deadlock.ead.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thr
 *
 *
 * @see pthread_tryjoin_np()
 */
#ifndef _di_f_thread_join_try_
  extern f_status_t f_thread_try(const f_thread_id_t id, void **result);
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
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_supported_not (with error bit) if the thread is not joinable or is already being joined by another thread.
 *
 *
 * @see pthread_timedjoin_np()
 */
#ifndef _di_f_thread_join_timed_
  extern f_status_t f_thread_timed(const f_thread_id_t id, const struct timespec wait, void **result);
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
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to set the scheduling policy and parameters specified in attribute.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_key_create()
 */
#ifndef _di_f_thread_key_create_
  extern f_status_t f_thread_key_create(void (*routine) (void *), f_thread_key_t *key);
#endif // _di_f_thread_key_create_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_setspecific()
 */
#ifndef _di_f_thread_key_set_
  extern f_status_t f_thread_key_set(const f_thread_key_t key, const void *value);
#endif // _di_f_thread_key_set_

/**
 * Make a read lock on the read/write lock.
 *
 * @param lock
 *   The read/write lock.
 *
 * @return
 *   F_none on success.
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max read/write locks is reached.
 *
 * @see pthread_rwlock_rdlock()
 */
#ifndef _di_f_thread_lock_
  extern f_status_t f_thread_lock(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_

/**
 * Try to make a read lock on the read/write lock.
 *
 * @param lock
 *   The read/write lock.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but the read/write lock is already locked.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max read/write locks is reached.
 *
 * @see pthread_rwlock_tryrdlock()
 */
#ifndef _di_f_thread_lock_try_
  extern f_status_t f_thread_lock_try(f_thread_lock_t *lock);
#endif // _di_f_thread_lock_try_

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
 *   F_busy (with error bit) if the mutex is busy.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation.
 *   F_resource_not (with error bit) if max mutexes is reached.
 *   F_failure (with error bit) on any other error.
 *
 * @see pthread_mutex_init()
 */
#ifndef _di_f_thread_mutex_create_
  extern f_status_t f_thread_mutex_create(f_thread_mutex_attribute_t * const attribute, f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_create_

/**
 * Create a thread mutex.
 *
 * @param mutex
 *   The mutex to delete.
 *
 * @return
 *   F_none on success.
 *   F_busy (with error bit) if the mutex is busy.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *
 * @see pthread_mutex_lock()
 */
#ifndef _di_f_thread_mutex_lock_
  extern f_status_t f_thread_mutex_lock(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_lock_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *
 * @see pthread_mutex_trylock()
 */
#ifndef _di_f_thread_mutex_lock_try_
  extern f_status_t f_thread_mutex_lock_try(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_lock_try_

/**
 * Unlock the mutex.
 *
 * @param mutex
 *   The thread mutex.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform the operation (possibly because mutex is not owned by current thread).
 *   F_resource_not (with error bit) if max mutex locks is reached.
 *
 * @see pthread_mutex_unlock()
 */
#ifndef _di_f_thread_mutex_unlock_
  extern f_status_t f_thread_mutex_unlock(f_thread_mutex_t *mutex);
#endif // _di_f_thread_mutex_unlock_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_once()
 */
#ifndef _di_f_thread_once_
  extern f_status_t f_thread_once(void (*routine) (void), f_thread_once_t *once);
#endif // _di_f_thread_once_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
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
 *   F_found_not (with error bit) if no thread by the given ID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_resource_not (with error bit) if the max signals is reached.
 *   F_supported_not (with error bit) if this action is not supported by the current OS.
 *   F_failure (with error bit) for any other error.
 *
 * @see pthread_sigqueue()
 */
#ifndef _di_f_thread_signal_queue_
  extern f_status_t f_thread_signal_queue(const f_thread_id_t id, const int signal, const union sigval value);
#endif // _di_f_thread_signal_queue_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_h

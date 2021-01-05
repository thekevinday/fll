#include "thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_at_fork_
  f_status_t f_thread_at_fork(void (*before) (void), void (*after_parent) (void), void (*after_child) (void)) {
    #ifndef _di_level_0_parameter_checking_
      if (!before) return F_status_set_error(F_parameter);
      if (!after_parent) return F_status_set_error(F_parameter);
      if (!after_child) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_atfork(before, after_parent, after_child);

    if (error) {
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_key_create_

#ifndef _di_f_thread_attribute_affinity_get_
  f_status_t f_thread_attribute_affinity_get(const f_thread_attribute_t attribute, const size_t affinity_size, cpu_set_t *affinity_set) {
    #ifndef _di_level_0_parameter_checking_
      if (!affinity_set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getaffinity_np(&attribute, affinity_size, affinity_set);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_affinity_get_

#ifndef _di_f_thread_attribute_affinity_set_
  f_status_t f_thread_attribute_affinity_set(const size_t affinity_size, const cpu_set_t *affinity_set, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setaffinity_np(attribute, affinity_size, affinity_set);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_affinity_set_

#ifndef _di_f_thread_attribute_create_
  f_status_t f_thread_attribute_create(f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_init(attribute);

    if (error) {
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_create_

#ifndef _di_f_thread_attribute_default_get_
  f_status_t f_thread_attribute_default_get(f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_getattr_default_np(attribute);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_default_get_

#ifndef _di_f_thread_attribute_default_set_
  f_status_t f_thread_attribute_default_set(f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_setattr_default_np(attribute);

    if (error) {
      if (error == ENOMEM) return F_status_set_error(F_memory_not);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_default_set_

#ifndef _di_f_thread_attribute_delete_
  f_status_t f_thread_attribute_delete(f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_destroy(attribute);

    if (error) {
      return F_status_set_error(F_failure);
    }

    attribute = 0;

    return F_none;
  }
#endif // _di_f_thread_attribute_delete_

#ifndef _di_f_thread_attribute_detach_get_
  f_status_t f_thread_attribute_detach_get(const f_thread_attribute_t attribute, int *state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getdetachstate(&attribute, state);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_detach_get_

#ifndef _di_f_thread_attribute_detach_set_
  f_status_t f_thread_attribute_detach_set(const int state, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setdetachstate(attribute, state);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_detach_set_

#ifndef _di_f_thread_attribute_guard_get_
  f_status_t f_thread_attribute_guard_get(const f_thread_attribute_t attribute, size_t *guard) {
    #ifndef _di_level_0_parameter_checking_
      if (!guard) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getguardsize(&attribute, guard);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_guard_get_

#ifndef _di_f_thread_attribute_guard_set_
  f_status_t f_thread_attribute_guard_set(const size_t guard, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setguardsize(attribute, guard);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_guard_set_

#ifndef _di_f_thread_attribute_scheduler_inherit_get_
  f_status_t f_thread_attribute_scheduler_inherit_get(const f_thread_attribute_t attribute, int *inherit) {
    #ifndef _di_level_0_parameter_checking_
      if (!inherit) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getinheritsched(&attribute, inherit);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scheduler_inherit_get_

#ifndef _di_f_thread_attribute_scheduler_inherit_set_
  f_status_t f_thread_attribute_scheduler_inherit_set(const int inherit, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setinheritsched(attribute, inherit);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scheduler_inherit_set_

#ifndef _di_f_thread_attribute_scheduler_parameter_get_
  f_status_t f_thread_attribute_scheduler_parameter_get(const f_thread_attribute_t attribute, struct sched_param *parameter) {
    #ifndef _di_level_0_parameter_checking_
      if (!parameter) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getschedparam(&attribute, parameter);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scheduler_parameter_get_

#ifndef _di_f_thread_attribute_scheduler_parameter_set_
  f_status_t f_thread_attribute_scheduler_parameter_set(const struct sched_param parameter, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setschedparam(attribute, &parameter);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scheduler_parameter_set_

#ifndef _di_f_thread_attribute_scheduler_policy_get_
  f_status_t f_thread_attribute_scheduler_policy_get(const f_thread_attribute_t attribute, int *policy) {
    #ifndef _di_level_0_parameter_checking_
      if (!policy) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getschedpolicy(&attribute, policy);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scheduler_policy_get_

#ifndef _di_f_thread_attribute_scheduler_policy_set_
  f_status_t f_thread_attribute_scheduler_policy_set(const int policy, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setschedpolicy(attribute, policy);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scheduler_policy_set_

#ifndef _di_f_thread_attribute_scope_get_
  f_status_t f_thread_attribute_scope_get(const f_thread_attribute_t attribute, int *scope) {
    #ifndef _di_level_0_parameter_checking_
      if (!scope) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getscope(&attribute, scope);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scope_get_

#ifndef _di_f_thread_attribute_scope_set_
  f_status_t f_thread_attribute_scope_set(const int scope, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setscope(attribute, scope);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOTSUP) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_scope_set_

#ifndef _di_f_thread_attribute_stack_get_
  f_status_t f_thread_attribute_stack_get(const f_thread_attribute_t attribute, size_t *stack_size, void **stack) {
    #ifndef _di_level_0_parameter_checking_
      if (!stack) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getstack(&attribute, stack, stack_size);

    if (error) {
      if (error == EACCES) return F_status_set_error(F_access_denied);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_stack_get_

#ifndef _di_f_thread_attribute_stack_set_
  f_status_t f_thread_attribute_stack_set(const size_t stack_size, void * const stack, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setstack(attribute, stack, stack_size);

    if (error) {
      if (error == EACCES) return F_status_set_error(F_access_denied);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_stack_set_

#ifndef _di_f_thread_caller_
  f_thread_id_t f_thread_caller() {
    return pthread_self();
  }
#endif // _di_f_thread_caller_

#ifndef _di_f_thread_cancel_
  f_status_t f_thread_cancel(const f_thread_id_t id) {

    const int error = pthread_cancel(id);

    if (error) {
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_cancel_

#ifndef _di_f_thread_cancel_state_set_
  f_status_t f_thread_cancel_state_set(const int state, int *previous) {

    const int error = pthread_setcancelstate(state, previous);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_cancel_state_set_

#ifndef _di_f_thread_cancel_test_
  f_status_t f_thread_cancel_test() {

    pthread_testcancel();

    return F_none;
  }
#endif // _di_f_thread_cancel_test_

#ifndef _di_f_thread_cancel_type_set_
  f_status_t f_thread_cancel_type_set(const int type, int *previous) {

    const int error = pthread_setcanceltype(type, previous);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_cancel_type_set_

#ifndef _di_f_thread_clock_get_id_
  f_status_t f_thread_clock_get_id(const f_thread_id_t id_thread, clockid_t *id_clock) {

    const int error = pthread_getcpuclockid(id_thread, id_clock);

    if (error) {
      if (error == ENOENT) return F_status_set_error(F_supported_not);
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_clock_get_id_

#ifndef _di_f_thread_compare_
  f_status_t f_thread_compare(const f_thread_id_t id1, const f_thread_id_t id2) {

    if (pthread_equal(id1, id2)) {
      return F_equal_to;
    }

    return F_equal_to_not;
  }
#endif // _di_f_thread_compare_

#ifndef _di_f_thread_condition_unblock_all_
  f_status_t f_thread_condition_unblock_all(f_thread_condition_t *condition) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_cond_broadcast(condition);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_unblock_all_

#ifndef _di_f_thread_condition_unblock_any_
  f_status_t f_thread_condition_unblock_any(f_thread_condition_t *condition) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_cond_signal(condition);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_unblock_any_

#ifndef _di_f_thread_condition_wait_
  f_status_t f_thread_condition_wait(f_thread_condition_t *condition, f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_cond_wait(condition, mutex);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_wait_

#ifndef _di_f_thread_condition_wait_timed_
  f_status_t f_thread_condition_wait_timed(const struct timespec *wait, f_thread_condition_t *condition, f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_cond_timedwait(condition, mutex, wait);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_wait_timed_

#ifndef _di_f_thread_create_
  f_status_t f_thread_create(const f_thread_attribute_t *attribute, f_thread_id_t *id, void *(*routine) (void *), void *argument) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!id) return F_status_set_error(F_parameter);
      if (!routine) return F_status_set_error(F_parameter);
      if (!argument) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_create(id, attribute, routine, argument);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_create_

#ifndef _di_f_thread_exit_
  f_status_t f_thread_exit(int *result) {
    #ifndef _di_level_0_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    pthread_exit(result);

    return F_none;
  }
#endif // _di_f_thread_exit_

#ifndef _di_f_thread_join_
  f_status_t f_thread_join(const f_thread_id_t id, void **result) {

    const int error = pthread_join(id, result);

    if (error) {
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_supported_not);
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_join_

#ifndef _di_f_thread_join_try_
  f_status_t f_thread_try(const f_thread_id_t id, void **result) {

    const int error = pthread_tryjoin_np(id, result);

    if (error) {
      if (error == EBUSY) return F_busy;
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_supported_not);
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_join_try_

#ifndef _di_f_thread_join_timed_
  f_status_t f_thread_timed(const f_thread_id_t id, const struct timespec wait, void **result) {

    const int error = pthread_timedjoin_np(id, result, &wait);

    if (error) {
      if (error == EBUSY) return F_busy;
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_supported_not);
      if (error == ESRCH) return F_status_set_error(F_found_not);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_join_timed_

#ifndef _di_f_thread_key_create_
  f_status_t f_thread_key_create(void (*routine) (void *), f_thread_key_t *key) {
    #ifndef _di_level_0_parameter_checking_
      if (!routine) return F_status_set_error(F_parameter);
      if (!key) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_key_create(key, routine);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_key_create_

#ifndef _di_f_thread_key_get_
  f_status_t f_thread_key_get(const f_thread_key_t key, void **value) {
    #ifndef _di_level_0_parameter_checking_
      if (!value) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *value = pthread_getspecific(key);

    return F_none;
  }
#endif // _di_f_thread_key_get_

#ifndef _di_f_thread_key_set_
  f_status_t f_thread_key_set(const f_thread_key_t key, const void *value) {
    #ifndef _di_level_0_parameter_checking_
      if (!value) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_setspecific(key, value);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_key_set_

#ifndef _di_f_thread_lock_
  f_status_t f_thread_lock(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_rdlock(lock);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_

#ifndef _di_f_thread_lock_try_
  f_status_t f_thread_lock_try(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_tryrdlock(lock);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_busy;
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_try_

#ifndef _di_f_thread_mutex_create_
  f_status_t f_thread_mutex_create(f_thread_mutex_attribute_t * const attribute, f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_init(mutex, attribute);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_create_

#ifndef _di_f_thread_mutex_delete_
  f_status_t f_thread_mutex_delete(f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_destroy(mutex);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_delete_

#ifndef _di_f_thread_mutex_lock_
  f_status_t f_thread_mutex_lock(f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_lock(mutex);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_lock_

#ifndef _di_f_thread_mutex_lock_try_
  f_status_t f_thread_mutex_lock_try(f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_trylock(mutex);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_busy;
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_lock_try_

#ifndef _di_f_thread_mutex_unlock_
  f_status_t f_thread_mutex_unlock(f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_unlock(mutex);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_unlock_

#ifndef _di_f_thread_once_
  f_status_t f_thread_once(void (*routine) (void), f_thread_once_t *once) {
    #ifndef _di_level_0_parameter_checking_
      if (!routine) return F_status_set_error(F_parameter);
      if (!once) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_once(once, routine);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_once_

#ifndef _di_f_thread_signal_
  f_status_t f_thread_signal(const f_thread_id_t id, const int signal) {

    const int error = pthread_kill(id, signal);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      if (error == ESRCH) {
        if (signal) return F_status_set_error(F_found_not);

        return F_found_not;
      }

      return F_status_set_error(F_failure);
    }

    if (signal) {
      return F_none;
    }

    return F_found;
  }
#endif // _di_f_thread_signal_

#ifndef _di_f_thread_signal_mask_
  f_status_t f_thread_signal_mask(const int how, const sigset_t *next, sigset_t *current) {
    #ifndef _di_level_0_parameter_checking_
      if (!next && !current) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_sigmask(how, next, current) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_signal_mask_

#ifndef _di_f_thread_signal_queue_
  f_status_t f_thread_signal_queue(const f_thread_id_t id, const int signal, const union sigval value) {

    const int error = pthread_sigqueue(id, signal, value);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == ENOSYS) return F_status_set_error(F_supported_not);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_signal_queue_

#ifdef __cplusplus
} // extern "C"
#endif

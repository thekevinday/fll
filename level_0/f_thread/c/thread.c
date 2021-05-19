#include "thread.h"
#include "private-thread.h"

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

#if defined(_pthread_attr_unsupported_) && !defined(_di_f_thread_attribute_affinity_get_)
  f_status_t f_thread_attribute_affinity_get(const f_thread_attribute_t attribute, const size_t affinity_size, cpu_set_t *affinity_set) {
    #ifndef _di_level_0_parameter_checking_
      if (!affinity_set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return F_status_set_error(F_implemented_not);
  }
#elif !defined(_di_f_thread_attribute_affinity_get_)
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
#endif // defined(_pthread_attr_unsupported_) && !defined(_di_f_thread_attribute_affinity_get_)

#if defined(_pthread_attr_unsupported_) && !defined(_di_f_thread_attribute_affinity_set_)
  f_status_t f_thread_attribute_affinity_set(const size_t affinity_size, const cpu_set_t *affinity_set, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return F_status_set_error(F_implemented_not);
  }
#elif !defined(_di_f_thread_attribute_affinity_set_)
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
#endif // defined(_pthread_attr_unsupported_) && !defined(_di_f_thread_attribute_affinity_set_)

#ifndef _di_f_thread_attribute_clock_get_
  f_status_t f_thread_attribute_clock_get(const f_thread_condition_attribute_t *attribute, clockid_t *id) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_condattr_getclock(attribute, id)) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_clock_get_

#ifndef _di_f_thread_attribute_clock_set_
  f_status_t f_thread_attribute_clock_set(const clockid_t id, f_thread_condition_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_condattr_setclock(attribute, id);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_clock_set_

#ifndef _di_f_thread_attribute_condition_shared_get_
  f_status_t f_thread_attribute_condition_shared_get(const f_thread_condition_attribute_t *attribute, int *shared) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!shared) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_condattr_getpshared(attribute, shared)) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_condition_shared_get_

#ifndef _di_f_thread_attribute_condition_shared_set_
  f_status_t f_thread_attribute_condition_shared_set(const int shared, f_thread_condition_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_condattr_setpshared(attribute, shared);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_condition_shared_set_

#ifndef _di_f_thread_attribute_create_
  f_status_t f_thread_attribute_create(f_thread_attribute_t *attribute) {

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

    return private_f_thread_attribute_delete(attribute);
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

#ifndef _di_f_thread_attribute_stack_size_get_
  f_status_t f_thread_attribute_stack_size_get(const f_thread_attribute_t attribute, size_t *stack_size) {
    #ifndef _di_level_0_parameter_checking_
      if (!stack_size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_getstacksize(&attribute, stack_size);

    if (error) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_stack_size_get_

#ifndef _di_f_thread_attribute_stack_size_set_
  f_status_t f_thread_attribute_stack_size_set(const size_t stack_size, f_thread_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_attr_setstacksize(attribute, stack_size);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_stack_size_set_

#ifndef _di_f_thread_attributes_adjust_
  f_status_t f_thread_attributes_adjust(const f_array_length_t length, f_thread_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_attributes_adjust(length, attributes);
  }
#endif // _di_f_thread_attributes_adjust_

#ifndef _di_f_thread_attributes_decimate_by_
  f_status_t f_thread_attributes_decimate_by(const f_array_length_t amount, f_thread_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_attributes_adjust(attributes->size - amount, attributes);
    }

    return private_f_thread_attributes_adjust(0, attributes);
  }
#endif // _di_f_thread_attributes_decimate_by_

#ifndef _di_f_thread_attributes_decrease_by_
  f_status_t f_thread_attributes_decrease_by(const f_array_length_t amount, f_thread_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_attributes_resize(attributes->size - amount, attributes);
    }

    return private_f_thread_attributes_resize(0, attributes);
  }
#endif // _di_f_thread_attributes_decrease_by_

#ifndef _di_f_thread_attributes_increase_
  f_status_t f_thread_attributes_increase(const uint16_t step, f_thread_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + 1 > attributes->size) {
      f_array_length_t size = attributes->used + step;

      if (size > f_array_length_t_size) {
        if (attributes->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_attributes_resize(size, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_attributes_increase_

#ifndef _di_f_thread_attributes_increase_by_
  f_status_t f_thread_attributes_increase_by(const f_array_length_t amount, f_thread_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + amount > attributes->size) {
      if (attributes->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_attributes_resize(attributes->used + amount, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_attributes_increase_by_

#ifndef _di_f_thread_attributes_resize_
  f_status_t f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_attributes_resize(length, attributes);
  }
#endif // _di_f_thread_attributes_resize_

#ifndef _di_f_thread_barrier_attribute_create_
  f_status_t f_thread_barrier_attribute_create(f_thread_barrier_attribute_t *attribute) {

    const int error = pthread_barrierattr_init(attribute);

    if (error) {
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_barrier_attribute_create_

#ifndef _di_f_thread_barrier_attribute_delete_
  f_status_t f_thread_barrier_attribute_delete(f_thread_barrier_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barrier_attribute_delete(attribute);
  }
#endif // _di_f_thread_barrier_attribute_delete_

#ifndef _di_f_thread_barrier_attribute_shared_get_
  f_status_t f_thread_barrier_attribute_shared_get(const f_thread_barrier_attribute_t *attribute, int *shared) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!shared) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_barrierattr_getpshared(attribute, shared)) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_barrier_attribute_shared_get_

#ifndef _di_f_thread_barrier_attribute_shared_set_
  f_status_t f_thread_barrier_attribute_shared_set(const int shared, f_thread_barrier_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_barrierattr_setpshared(attribute, shared);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_barrier_attribute_shared_set_

#ifndef _di_f_thread_barrier_attributes_adjust_
  f_status_t f_thread_barrier_attributes_adjust(const f_array_length_t length, f_thread_barrier_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barrier_attributes_adjust(length, attributes);
  }
#endif // _di_f_thread_barrier_attributes_adjust_

#ifndef _di_f_thread_barrier_attributes_decimate_by_
  f_status_t f_thread_barrier_attributes_decimate_by(const f_array_length_t amount, f_thread_barrier_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_barrier_attributes_adjust(attributes->size - amount, attributes);
    }

    return private_f_thread_barrier_attributes_adjust(0, attributes);
  }
#endif // _di_f_thread_barrier_attributes_decimate_by_

#ifndef _di_f_thread_barrier_attributes_decrease_by_
  f_status_t f_thread_barrier_attributes_decrease_by(const f_array_length_t amount, f_thread_barrier_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_barrier_attributes_resize(attributes->size - amount, attributes);
    }

    return private_f_thread_barrier_attributes_resize(0, attributes);
  }
#endif // _di_f_thread_barrier_attributes_decrease_by_

#ifndef _di_f_thread_barrier_attributes_increase_
  f_status_t f_thread_barrier_attributes_increase(const uint16_t step, f_thread_barrier_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + 1 > attributes->size) {
      f_array_length_t size = attributes->used + step;

      if (size > f_array_length_t_size) {
        if (attributes->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_barrier_attributes_resize(size, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_barrier_attributes_increase_

#ifndef _di_f_thread_barrier_attributes_increase_by_
  f_status_t f_thread_barrier_attributes_increase_by(const f_array_length_t amount, f_thread_barrier_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + amount > attributes->size) {
      if (attributes->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_barrier_attributes_resize(attributes->used + amount, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_barrier_attributes_increase_by_

#ifndef _di_f_thread_barrier_attributes_resize_
  f_status_t f_thread_barrier_attributes_resize(const f_array_length_t length, f_thread_barrier_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barrier_attributes_resize(length, attributes);
  }
#endif // _di_f_thread_barrier_attributes_resize_

#ifndef _di_f_thread_barrier_create_
  f_status_t f_thread_barrier_create(const unsigned int count, f_thread_barrier_attribute_t * const attribute, f_thread_barrier_t *barrier) {

    const int error = pthread_barrier_init(barrier, attribute, count);

    if (error) {
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_barrier_create_

#ifndef _di_f_thread_barrier_delete_
  f_status_t f_thread_barrier_delete(f_thread_barrier_t *barrier) {
    #ifndef _di_level_0_parameter_checking_
      if (!barrier) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barrier_delete(barrier);
  }
#endif // _di_f_thread_barrier_delete_

#ifndef _di_f_thread_barrier_wait_
  f_status_t f_thread_barrier_wait(f_thread_barrier_t *barrier, int *result) {
    #ifndef _di_level_0_parameter_checking_
      if (!barrier) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (result) {
      *result = pthread_barrier_wait(barrier);
    }
    else {
      pthread_barrier_wait(barrier);
    }

    return F_none;
  }
#endif // _di_f_thread_barrier_wait_

#ifndef _di_f_thread_barriers_adjust_
  f_status_t f_thread_barriers_adjust(const f_array_length_t length, f_thread_barriers_t *barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barriers_adjust(length, barriers);
  }
#endif // _di_f_thread_barriers_adjust_

#ifndef _di_f_thread_barriers_decimate_by_
  f_status_t f_thread_barriers_decimate_by(const f_array_length_t amount, f_thread_barriers_t *barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (barriers->size - amount > 0) {
      return private_f_thread_barriers_adjust(barriers->size - amount, barriers);
    }

    return private_f_thread_barriers_adjust(0, barriers);
  }
#endif // _di_f_thread_barriers_decimate_by_

#ifndef _di_f_thread_barriers_decrease_by_
  f_status_t f_thread_barriers_decrease_by(const f_array_length_t amount, f_thread_barriers_t *barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (barriers->size - amount > 0) {
      return private_f_thread_barriers_resize(barriers->size - amount, barriers);
    }

    return private_f_thread_barriers_resize(0, barriers);
  }
#endif // _di_f_thread_barriers_decrease_by_

#ifndef _di_f_thread_barriers_increase_
  f_status_t f_thread_barriers_increase(const uint16_t step, f_thread_barriers_t *barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (barriers->used + 1 > barriers->size) {
      f_array_length_t size = barriers->used + step;

      if (size > f_array_length_t_size) {
        if (barriers->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_barriers_resize(size, barriers);
    }

    return F_data_not;
  }
#endif // _di_f_thread_barriers_increase_

#ifndef _di_f_thread_barriers_increase_by_
  f_status_t f_thread_barriers_increase_by(const f_array_length_t amount, f_thread_barriers_t *barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (barriers->used + amount > barriers->size) {
      if (barriers->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_barriers_resize(barriers->used + amount, barriers);
    }

    return F_data_not;
  }
#endif // _di_f_thread_barriers_increase_by_

#ifndef _di_f_thread_barriers_resize_
  f_status_t f_thread_barriers_resize(const f_array_length_t length, f_thread_barriers_t *barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barriers_resize(length, barriers);
  }
#endif // _di_f_thread_barriers_resize_

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

    int error = 0;

    // POSIX doesn't allow this to be NULL, so make POSIX happy.
    if (previous == 0) {
      int ignore = 0;

      error = pthread_setcancelstate(state, &ignore);
    }
    else {
      error = pthread_setcancelstate(state, previous);
    }

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

#ifndef _di_f_thread_attribute_concurrency_get_
  f_status_t f_thread_attribute_concurrency_get(int *level) {
    #ifndef _di_level_0_parameter_checking_
      if (!level) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *level = pthread_getconcurrency();

    return F_none;
  }
#endif // _di_f_thread_attribute_concurrency_get_

#ifndef _di_f_thread_attribute_concurrency_set_
  f_status_t f_thread_attribute_concurrency_set(const int level) {

    const int error = pthread_setconcurrency(level);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EAGAIN) return F_status_set_error(F_resource_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_attribute_concurrency_set_

#ifndef _di_f_thread_condition_attribute_create_
  f_status_t f_thread_condition_attribute_create(f_thread_condition_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_condattr_init(attribute);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_attribute_create_

#ifndef _di_f_thread_condition_attribute_delete_
  f_status_t f_thread_condition_attribute_delete(f_thread_condition_attribute_t *condition_attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition_attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_condition_attribute_delete(condition_attribute);
  }
#endif // _di_f_thread_condition_attribute_delete_

#ifndef _di_f_thread_condition_attributes_adjust_
  f_status_t f_thread_condition_attributes_adjust(const f_array_length_t length, f_thread_condition_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_condition_attributes_adjust(length, attributes);
  }
#endif // _di_f_thread_condition_attributes_adjust_

#ifndef _di_f_thread_condition_attributes_decimate_by_
  f_status_t f_thread_condition_attributes_decimate_by(const f_array_length_t amount, f_thread_condition_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_condition_attributes_adjust(attributes->size - amount, attributes);
    }

    return private_f_thread_condition_attributes_adjust(0, attributes);
  }
#endif // _di_f_thread_condition_attributes_decimate_by_

#ifndef _di_f_thread_condition_attributes_decrease_by_
  f_status_t f_thread_condition_attributes_decrease_by(const f_array_length_t amount, f_thread_condition_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_condition_attributes_resize(attributes->size - amount, attributes);
    }

    return private_f_thread_condition_attributes_resize(0, attributes);
  }
#endif // _di_f_thread_condition_attributes_decrease_by_

#ifndef _di_f_thread_condition_attributes_increase_
  f_status_t f_thread_condition_attributes_increase(const uint16_t step, f_thread_condition_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + 1 > attributes->size) {
      f_array_length_t size = attributes->used + step;

      if (size > f_array_length_t_size) {
        if (attributes->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_condition_attributes_resize(size, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_condition_attributes_increase_

#ifndef _di_f_thread_condition_attributes_increase_by_
  f_status_t f_thread_condition_attributes_increase_by(const f_array_length_t amount, f_thread_condition_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + amount > attributes->size) {
      if (attributes->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_condition_attributes_resize(attributes->used + amount, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_condition_attributes_increase_by_

#ifndef _di_f_thread_condition_attributes_resize_
  f_status_t f_thread_condition_attributes_resize(const f_array_length_t length, f_thread_condition_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_condition_attributes_resize(length, attributes);
  }
#endif // _di_f_thread_condition_attributes_resize_

#ifndef _di_f_thread_condition_create_
  f_status_t f_thread_condition_create(const f_thread_condition_attribute_t *attribute, f_thread_condition_t *condition) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_cond_init(condition, attribute);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_create_

#ifndef _di_f_thread_condition_delete_
  f_status_t f_thread_condition_delete(f_thread_condition_t *condition) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_condition_delete(condition);
  }
#endif // _di_f_thread_condition_delete_

#ifndef _di_f_thread_condition_signal_all_
  f_status_t f_thread_condition_signal_all(f_thread_condition_t *condition) {
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
#endif // _di_f_thread_condition_signal_all_

#ifndef _di_f_thread_condition_signal_
  f_status_t f_thread_condition_signal(f_thread_condition_t *condition) {
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
#endif // _di_f_thread_condition_signal_

#ifndef _di_f_thread_condition_wait_
  f_status_t f_thread_condition_wait(f_thread_condition_t *condition, f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!condition) return F_status_set_error(F_parameter);
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_cond_wait(condition, mutex);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOTRECOVERABLE) return F_status_set_error(F_recover_not);
      if (error == EOWNERDEAD) return F_status_set_error(F_dead);
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
      if (error == ENOTRECOVERABLE) return F_status_set_error(F_recover_not);
      if (error == EOWNERDEAD) return F_status_set_error(F_dead);
      if (error == EPERM) return F_status_set_error(F_prohibited);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_condition_wait_timed_

#ifndef _di_f_thread_conditions_adjust_
  f_status_t f_thread_conditions_adjust(const f_array_length_t length, f_thread_conditions_t *conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_conditions_adjust(length, conditions);
  }
#endif // _di_f_thread_conditions_adjust_

#ifndef _di_f_thread_conditions_decimate_by_
  f_status_t f_thread_conditions_decimate_by(const f_array_length_t amount, f_thread_conditions_t *conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (conditions->size - amount > 0) {
      return private_f_thread_conditions_adjust(conditions->size - amount, conditions);
    }

    return private_f_thread_conditions_adjust(0, conditions);
  }
#endif // _di_f_thread_conditions_decimate_by_

#ifndef _di_f_thread_conditions_decrease_by_
  f_status_t f_thread_conditions_decrease_by(const f_array_length_t amount, f_thread_conditions_t *conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (conditions->size - amount > 0) {
      return private_f_thread_conditions_resize(conditions->size - amount, conditions);
    }

    return private_f_thread_conditions_resize(0, conditions);
  }
#endif // _di_f_thread_conditions_decrease_by_

#ifndef _di_f_thread_conditions_increase_
  f_status_t f_thread_conditions_increase(const uint16_t step, f_thread_conditions_t *conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (conditions->used + 1 > conditions->size) {
      f_array_length_t size = conditions->used + step;

      if (size > f_array_length_t_size) {
        if (conditions->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_conditions_resize(size, conditions);
    }

    return F_data_not;
  }
#endif // _di_f_thread_conditions_increase_

#ifndef _di_f_thread_conditions_increase_by_
  f_status_t f_thread_conditions_increase_by(const f_array_length_t amount, f_thread_conditions_t *conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (conditions->used + amount > conditions->size) {
      if (conditions->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_conditions_resize(conditions->used + amount, conditions);
    }

    return F_data_not;
  }
#endif // _di_f_thread_conditions_increase_by_

#ifndef _di_f_thread_conditions_resize_
  f_status_t f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t *conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_conditions_resize(length, conditions);
  }
#endif // _di_f_thread_conditions_resize_

#ifndef _di_f_thread_create_
  f_status_t f_thread_create(const f_thread_attribute_t *attribute, f_thread_id_t *id, void *(*routine) (void *), void *argument) {
    #ifndef _di_level_0_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
      if (!routine) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_create(id, attribute, routine, argument);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_create_

#ifndef _di_f_thread_detach_
  f_status_t f_thread_detach(const f_thread_id_t id) {

    const int error = pthread_detach(id);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_detach_

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
  f_status_t f_thread_join_try(const f_thread_id_t id, void **result) {

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
  f_status_t f_thread_join_timed(const f_thread_id_t id, const struct timespec wait, void **result) {

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

#ifndef _di_f_thread_key_delete_
  f_status_t f_thread_key_delete(f_thread_key_t *key) {
    #ifndef _di_level_0_parameter_checking_
      if (!key) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_key_delete(key);
  }
#endif // _di_f_thread_key_delete_

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

#ifndef _di_f_thread_keys_adjust_
  f_status_t f_thread_keys_adjust(const f_array_length_t length, f_thread_keys_t *keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_keys_adjust(length, keys);
  }
#endif // _di_f_thread_keys_adjust_

#ifndef _di_f_thread_keys_decimate_by_
  f_status_t f_thread_keys_decimate_by(const f_array_length_t amount, f_thread_keys_t *keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (keys->size - amount > 0) {
      return private_f_thread_keys_adjust(keys->size - amount, keys);
    }

    return private_f_thread_keys_adjust(0, keys);
  }
#endif // _di_f_thread_keys_decimate_by_

#ifndef _di_f_thread_keys_decrease_by_
  f_status_t f_thread_keys_decrease_by(const f_array_length_t amount, f_thread_keys_t *keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (keys->size - amount > 0) {
      return private_f_thread_keys_resize(keys->size - amount, keys);
    }

    return private_f_thread_keys_resize(0, keys);
  }
#endif // _di_f_thread_keys_decrease_by_

#ifndef _di_f_thread_keys_increase_
  f_status_t f_thread_keys_increase(const uint16_t step, f_thread_keys_t *keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (keys->used + 1 > keys->size) {
      f_array_length_t size = keys->used + step;

      if (size > f_array_length_t_size) {
        if (keys->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_keys_resize(size, keys);
    }

    return F_data_not;
  }
#endif // _di_f_thread_keys_increase_

#ifndef _di_f_thread_keys_increase_by_
  f_status_t f_thread_keys_increase_by(const f_array_length_t amount, f_thread_keys_t *keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (keys->used + amount > keys->size) {
      if (keys->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_keys_resize(keys->used + amount, keys);
    }

    return F_data_not;
  }
#endif // _di_f_thread_keys_increase_by_

#ifndef _di_f_thread_keys_resize_
  f_status_t f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t *keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_keys_resize(length, keys);
  }
#endif // _di_f_thread_keys_resize_

#ifndef _di_f_thread_lock_attribute_create_
  f_status_t f_thread_lock_attribute_create(f_thread_lock_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlockattr_init(attribute);

    // @todo figure out the error codes and update accordingly.
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
#endif // _di_f_thread_lock_attribute_create_

#ifndef _di_f_thread_lock_attribute_delete_
  f_status_t f_thread_lock_attribute_delete(f_thread_lock_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_lock_attribute_delete(attribute);
  }
#endif // _di_f_thread_lock_attribute_delete_

#ifndef _di_f_thread_lock_attribute_shared_get_
  f_status_t f_thread_lock_attribute_shared_get(const f_thread_lock_attribute_t *attribute, int *shared) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!shared) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_rwlockattr_getpshared(attribute, shared)) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_attribute_shared_get_

#ifndef _di_f_thread_lock_attribute_shared_set_
  f_status_t f_thread_lock_attribute_shared_set(const int shared, f_thread_lock_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlockattr_setpshared(attribute, shared);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_attribute_shared_set_

#ifndef _di_f_thread_lock_attributes_adjust_
  f_status_t f_thread_lock_attributes_adjust(const f_array_length_t length, f_thread_lock_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_lock_attributes_adjust(length, attributes);
  }
#endif // _di_f_thread_lock_attributes_adjust_

#ifndef _di_f_thread_lock_attributes_decimate_by_
  f_status_t f_thread_lock_attributes_decimate_by(const f_array_length_t amount, f_thread_lock_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_lock_attributes_adjust(attributes->size - amount, attributes);
    }

    return private_f_thread_lock_attributes_adjust(0, attributes);
  }
#endif // _di_f_thread_lock_attributes_decimate_by_

#ifndef _di_f_thread_lock_attributes_decrease_by_
  f_status_t f_thread_lock_attributes_decrease_by(const f_array_length_t amount, f_thread_lock_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_lock_attributes_resize(attributes->size - amount, attributes);
    }

    return private_f_thread_lock_attributes_resize(0, attributes);
  }
#endif // _di_f_thread_lock_attributes_decrease_by_

#ifndef _di_f_thread_lock_attributes_increase_
  f_status_t f_thread_lock_attributes_increase(const uint16_t step, f_thread_lock_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + 1 > attributes->size) {
      f_array_length_t size = attributes->used + step;

      if (size > f_array_length_t_size) {
        if (attributes->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_lock_attributes_resize(size, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_lock_attributes_increase_

#ifndef _di_f_thread_lock_attributes_increase_by_
  f_status_t f_thread_lock_attributes_increase_by(const f_array_length_t amount, f_thread_lock_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + amount > attributes->size) {
      if (attributes->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_lock_attributes_resize(attributes->used + amount, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_lock_attributes_increase_by_

#ifndef _di_f_thread_lock_attributes_resize_
  f_status_t f_thread_lock_attributes_resize(const f_array_length_t length, f_thread_lock_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_lock_attributes_resize(length, attributes);
  }
#endif // _di_f_thread_lock_attributes_resize_

#ifndef _di_f_thread_lock_create_
  f_status_t f_thread_lock_create(const f_thread_lock_attribute_t *attribute, f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_init(lock, attribute);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_create_

#ifndef _di_f_thread_lock_delete_
  f_status_t f_thread_lock_delete(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_lock_delete(lock);
  }
#endif // _di_f_thread_lock_delete_

#ifndef _di_f_thread_lock_read_
  f_status_t f_thread_lock_read(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_rdlock(lock);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_read_

#ifndef _di_f_thread_lock_read_timed_
  f_status_t f_thread_lock_read_timed(const struct timespec *timeout, f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!timeout) return F_status_set_error(F_parameter);
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_timedrdlock(lock, timeout);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_read_timed_

#ifndef _di_f_thread_lock_read_try_
  f_status_t f_thread_lock_read_try(f_thread_lock_t *lock) {
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
#endif // _di_f_thread_lock_read_try_

#ifndef _di_f_thread_lock_write_
  f_status_t f_thread_lock_write(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_wrlock(lock);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_write_

#ifndef _di_f_thread_lock_write_timed_
  f_status_t f_thread_lock_write_timed(const struct timespec *timeout, f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!timeout) return F_status_set_error(F_parameter);
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_timedwrlock(lock, timeout);

    if (error) {
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_write_timed_

#ifndef _di_f_thread_lock_write_try_
  f_status_t f_thread_lock_write_try(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_trywrlock(lock);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_busy;
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_lock_write_try_

#ifndef _di_f_thread_locks_adjust_
  f_status_t f_thread_locks_adjust(const f_array_length_t length, f_thread_locks_t *locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_locks_adjust(length, locks);
  }
#endif // _di_f_thread_locks_adjust_

#ifndef _di_f_thread_locks_decimate_by_
  f_status_t f_thread_locks_decimate_by(const f_array_length_t amount, f_thread_locks_t *locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (locks->size - amount > 0) {
      return private_f_thread_locks_adjust(locks->size - amount, locks);
    }

    return private_f_thread_locks_adjust(0, locks);
  }
#endif // _di_f_thread_locks_decimate_by_

#ifndef _di_f_thread_locks_decrease_by_
  f_status_t f_thread_locks_decrease_by(const f_array_length_t amount, f_thread_locks_t *locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (locks->size - amount > 0) {
      return private_f_thread_locks_resize(locks->size - amount, locks);
    }

    return private_f_thread_locks_resize(0, locks);
  }
#endif // _di_f_thread_locks_decrease_by_

#ifndef _di_f_thread_locks_increase_
  f_status_t f_thread_locks_increase(const uint16_t step, f_thread_locks_t *locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (locks->used + 1 > locks->size) {
      f_array_length_t size = locks->used + step;

      if (size > f_array_length_t_size) {
        if (locks->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_locks_resize(size, locks);
    }

    return F_data_not;
  }
#endif // _di_f_thread_locks_increase_

#ifndef _di_f_thread_locks_increase_by_
  f_status_t f_thread_locks_increase_by(const f_array_length_t amount, f_thread_locks_t *locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (locks->used + amount > locks->size) {
      if (locks->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_locks_resize(locks->used + amount, locks);
    }

    return F_data_not;
  }
#endif // _di_f_thread_locks_increase_by_

#ifndef _di_f_thread_locks_resize_
  f_status_t f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t *locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_locks_resize(length, locks);
  }
#endif // _di_f_thread_locks_resize_

#ifndef _di_f_thread_mutex_attribute_create_
  f_status_t f_thread_mutex_attribute_create(f_thread_mutex_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_init(attribute);

    // @todo figure out the error codes and update accordingly.
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
#endif // _di_f_thread_mutex_attribute_create_

#ifndef _di_f_thread_mutex_attribute_delete_
  f_status_t f_thread_mutex_attribute_delete(f_thread_mutex_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutex_attribute_delete(attribute);
  }
#endif // _di_f_thread_mutex_attribute_delete_

#ifndef _di_f_thread_mutex_attribute_priority_ceiling_get_
  f_status_t f_thread_mutex_attribute_priority_ceiling_get(const f_thread_mutex_attribute_t *attribute, int *ceiling) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!ceiling) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_getprioceiling(attribute, ceiling);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_priority_ceiling_get_

#ifndef _di_f_thread_mutex_attribute_priority_ceiling_set_
  f_status_t f_thread_mutex_attribute_priority_ceiling_set(const int ceiling, f_thread_mutex_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_setprioceiling(attribute, ceiling);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_priority_ceiling_set_

#ifndef _di_f_thread_mutex_attribute_shared_get_
  f_status_t f_thread_mutex_attribute_shared_get(const f_thread_mutex_attribute_t *attribute, int *shared) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!shared) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_mutexattr_getpshared(attribute, shared)) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_shared_get_

#ifndef _di_f_thread_mutex_attribute_shared_set_
  f_status_t f_thread_mutex_attribute_shared_set(const int shared, f_thread_mutex_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_setpshared(attribute, shared);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_shared_set_

#ifndef _di_f_thread_mutex_attribute_type_get_
  f_status_t f_thread_mutex_attribute_type_get(const f_thread_mutex_attribute_t *attribute, int *type) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!type) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (pthread_mutexattr_gettype(attribute, type)) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_type_get_

#ifndef _di_f_thread_mutex_attribute_type_set_
  f_status_t f_thread_mutex_attribute_type_set(const int type, f_thread_mutex_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_settype(attribute, type);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_type_set_

#ifndef _di_f_thread_mutex_attribute_protocol_get_
  f_status_t f_thread_mutex_attribute_protocol_get(const f_thread_mutex_attribute_t *attribute, int *protocol) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
      if (!protocol) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_getprotocol(attribute, protocol);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_protocol_get_

#ifndef _di_f_thread_mutex_attribute_protocol_set_
  f_status_t f_thread_mutex_attribute_protocol_set(const int protocol, f_thread_mutex_attribute_t *attribute) {
    #ifndef _di_level_0_parameter_checking_
      if (!attribute) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutexattr_setprotocol(attribute, protocol);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);
      if (error == ENOTSUP) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_attribute_protocol_set_

#ifndef _di_f_thread_mutex_attributes_adjust_
  f_status_t f_thread_mutex_attributes_adjust(const f_array_length_t length, f_thread_mutex_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutex_attributes_adjust(length, attributes);
  }
#endif // _di_f_thread_mutex_attributes_adjust_

#ifndef _di_f_thread_mutex_attributes_decimate_by_
  f_status_t f_thread_mutex_attributes_decimate_by(const f_array_length_t amount, f_thread_mutex_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_mutex_attributes_adjust(attributes->size - amount, attributes);
    }

    return private_f_thread_mutex_attributes_adjust(0, attributes);
  }
#endif // _di_f_thread_mutex_attributes_decimate_by_

#ifndef _di_f_thread_mutex_attributes_decrease_by_
  f_status_t f_thread_mutex_attributes_decrease_by(const f_array_length_t amount, f_thread_mutex_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->size - amount > 0) {
      return private_f_thread_mutex_attributes_resize(attributes->size - amount, attributes);
    }

    return private_f_thread_mutex_attributes_resize(0, attributes);
  }
#endif // _di_f_thread_mutex_attributes_decrease_by_

#ifndef _di_f_thread_mutex_attributes_increase_
  f_status_t f_thread_mutex_attributes_increase(const uint16_t step, f_thread_mutex_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + 1 > attributes->size) {
      f_array_length_t size = attributes->used + step;

      if (size > f_array_length_t_size) {
        if (attributes->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_mutex_attributes_resize(size, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutex_attributes_increase_

#ifndef _di_f_thread_mutex_attributes_increase_by_
  f_status_t f_thread_mutex_attributes_increase_by(const f_array_length_t amount, f_thread_mutex_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (attributes->used + amount > attributes->size) {
      if (attributes->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_mutex_attributes_resize(attributes->used + amount, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutex_attributes_increase_by_

#ifndef _di_f_thread_mutex_attributes_resize_
  f_status_t f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t *attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutex_attributes_resize(length, attributes);
  }
#endif // _di_f_thread_mutex_attributes_resize_

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

    return private_f_thread_mutex_delete(mutex);
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

#ifndef _di_f_thread_mutex_lock_timed_
  f_status_t f_thread_mutex_lock_timed(const struct timespec *timeout, f_thread_mutex_t *mutex) {
    #ifndef _di_level_0_parameter_checking_
      if (!timeout) return F_status_set_error(F_parameter);
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_timedlock(mutex, timeout);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOTRECOVERABLE) return F_status_set_error(F_recover_not);
      if (error == EOWNERDEAD) return F_status_set_error(F_dead);
      if (error == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_lock_timed_

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

#ifndef _di_f_thread_semaphore_create_
  f_status_t f_thread_semaphore_create(const bool shared, const unsigned int value, f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_init(semaphore, shared, value) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOSYS) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_create_

#ifndef _di_f_thread_semaphore_delete_
  f_status_t f_thread_semaphore_delete(f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_semaphore_delete(semaphore);
  }
#endif // _di_f_thread_semaphore_delete_

#ifndef _di_f_thread_semaphore_file_create_
  f_status_t f_thread_semaphore_file_create(const f_string_t name, const int flag, mode_t mode, unsigned int value, f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (flag & O_CREAT) {
      semaphore = sem_open(name, flag, mode, value);
    }
    else {
      semaphore = sem_open(name, flag);
    }

    if (semaphore == SEM_FAILED) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_file_create_

#ifndef _di_f_thread_semaphore_file_delete_
  f_status_t f_thread_semaphore_file_delete(f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_close(semaphore) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_file_delete_

#ifndef _di_f_thread_semaphore_file_destroy_
  f_status_t f_thread_semaphore_file_destroy(const f_string_t name) {

    if (sem_unlink(name) == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
      if (errno == ENOENT) return F_file_found_not;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_file_destroy_

#ifndef _di_f_thread_semaphore_lock_
  f_status_t f_thread_semaphore_lock(f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_wait(semaphore) == -1) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_lock_

#ifndef _di_f_thread_semaphore_lock_timed_
  f_status_t f_thread_semaphore_lock_timed(const struct timespec *timeout, f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!timeout) return F_status_set_error(F_parameter);
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_timedwait(semaphore, timeout) == -1) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ETIMEDOUT) return F_time;

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_lock_timed_

#ifndef _di_f_thread_semaphore_lock_try_
  f_status_t f_thread_semaphore_lock_try(f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_trywait(semaphore) == -1) {
      if (errno == EAGAIN) return F_status_set_error(F_resource_not);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_lock_try_

#ifndef _di_f_thread_semaphore_unlock_
  f_status_t f_thread_semaphore_unlock(f_thread_semaphore_t *semaphore) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_post(semaphore) == -1) {
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_unlock_

#ifndef _di_f_thread_semaphore_value_get_
  f_status_t f_thread_semaphore_value_get(f_thread_semaphore_t *semaphore, int *value) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphore) return F_status_set_error(F_parameter);
      if (!value) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sem_getvalue(semaphore, value) == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_semaphore_value_get_

#ifndef _di_f_thread_mutex_priority_ceiling_get_
  f_status_t f_thread_mutex_priority_ceiling_get(f_thread_mutex_t *mutex, int *ceiling) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
      if (!ceiling) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_getprioceiling(mutex, ceiling);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_priority_ceiling_get_

#ifndef _di_f_thread_mutex_priority_ceiling_set_
  f_status_t f_thread_mutex_priority_ceiling_set(const int ceiling, f_thread_mutex_t *mutex, int *previous) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutex) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_mutex_setprioceiling(mutex, ceiling, previous);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == ENOTRECOVERABLE) return F_status_set_error(F_recover_not);
      if (error == EOWNERDEAD) return F_status_set_error(F_dead);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_mutex_priority_ceiling_set_

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

#ifndef _di_f_thread_mutexs_adjust_
  f_status_t f_thread_mutexs_adjust(const f_array_length_t length, f_thread_mutexs_t *mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutexs_adjust(length, mutexs);
  }
#endif // _di_f_thread_mutexs_adjust_

#ifndef _di_f_thread_mutexs_decimate_by_
  f_status_t f_thread_mutexs_decimate_by(const f_array_length_t amount, f_thread_mutexs_t *mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mutexs->size - amount > 0) {
      return private_f_thread_mutexs_adjust(mutexs->size - amount, mutexs);
    }

    return private_f_thread_mutexs_adjust(0, mutexs);
  }
#endif // _di_f_thread_mutexs_decimate_by_

#ifndef _di_f_thread_mutexs_decrease_by_
  f_status_t f_thread_mutexs_decrease_by(const f_array_length_t amount, f_thread_mutexs_t *mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mutexs->size - amount > 0) {
      return private_f_thread_mutexs_resize(mutexs->size - amount, mutexs);
    }

    return private_f_thread_mutexs_resize(0, mutexs);
  }
#endif // _di_f_thread_mutexs_decrease_by_

#ifndef _di_f_thread_mutexs_increase_
  f_status_t f_thread_mutexs_increase(const uint16_t step, f_thread_mutexs_t *mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mutexs->used + 1 > mutexs->size) {
      f_array_length_t size = mutexs->used + step;

      if (size > f_array_length_t_size) {
        if (mutexs->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_mutexs_resize(size, mutexs);
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutexs_increase_

#ifndef _di_f_thread_mutexs_increase_by_
  f_status_t f_thread_mutexs_increase_by(const f_array_length_t amount, f_thread_mutexs_t *mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mutexs->used + amount > mutexs->size) {
      if (mutexs->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_mutexs_resize(mutexs->used + amount, mutexs);
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutexs_increase_by_

#ifndef _di_f_thread_mutexs_resize_
  f_status_t f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t *mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutexs_resize(length, mutexs);
  }
#endif // _di_f_thread_mutexs_resize_

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

#ifndef _di_f_thread_scheduler_parameter_get_
  f_status_t f_thread_scheduler_parameter_get(const f_thread_id_t id, int *policy, struct sched_param *parameter) {
    #ifndef _di_level_0_parameter_checking_
      if (!policy) return F_status_set_error(F_parameter);
      if (!parameter) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_getschedparam(id, policy, parameter);

    if (error) {
      if (error == ENOTSUP) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_scheduler_parameter_get_

#ifndef _di_f_thread_scheduler_parameter_set_
  f_status_t f_thread_scheduler_parameter_set(const f_thread_id_t id, const int policy, const struct sched_param *parameter) {
    #ifndef _di_level_0_parameter_checking_
      if (!policy) return F_status_set_error(F_parameter);
      if (!parameter) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_setschedparam(id, policy, parameter);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_scheduler_parameter_set_

#ifndef _di_f_thread_scheduler_priority_set_
  f_status_t f_thread_scheduler_priority_set(const f_thread_id_t id, const int priority) {

    const int error = pthread_setschedprio(id, priority);

    if (error) {
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);
      if (error == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_scheduler_priority_set_

#ifndef _di_f_thread_semaphores_adjust_
  f_status_t f_thread_semaphores_adjust(const f_array_length_t length, f_thread_semaphores_t *semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_semaphores_adjust(length, semaphores);
  }
#endif // _di_f_thread_semaphores_adjust_

#ifndef _di_f_thread_semaphores_decimate_by_
  f_status_t f_thread_semaphores_decimate_by(const f_array_length_t amount, f_thread_semaphores_t *semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (semaphores->size - amount > 0) {
      return private_f_thread_semaphores_adjust(semaphores->size - amount, semaphores);
    }

    return private_f_thread_semaphores_adjust(0, semaphores);
  }
#endif // _di_f_thread_semaphores_decimate_by_

#ifndef _di_f_thread_semaphores_decrease_by_
  f_status_t f_thread_semaphores_decrease_by(const f_array_length_t amount, f_thread_semaphores_t *semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (semaphores->size - amount > 0) {
      return private_f_thread_semaphores_resize(semaphores->size - amount, semaphores);
    }

    return private_f_thread_semaphores_resize(0, semaphores);
  }
#endif // _di_f_thread_semaphores_decrease_by_

#ifndef _di_f_thread_semaphores_increase_
  f_status_t f_thread_semaphores_increase(const uint16_t step, f_thread_semaphores_t *semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (semaphores->used + 1 > semaphores->size) {
      f_array_length_t size = semaphores->used + step;

      if (size > f_array_length_t_size) {
        if (semaphores->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_semaphores_resize(size, semaphores);
    }

    return F_data_not;
  }
#endif // _di_f_thread_semaphores_increase_

#ifndef _di_f_thread_semaphores_increase_by_
  f_status_t f_thread_semaphores_increase_by(const f_array_length_t amount, f_thread_semaphores_t *semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (semaphores->used + amount > semaphores->size) {
      if (semaphores->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_semaphores_resize(semaphores->used + amount, semaphores);
    }

    return F_data_not;
  }
#endif // _di_f_thread_semaphores_increase_by_

#ifndef _di_f_thread_semaphores_resize_
  f_status_t f_thread_semaphores_resize(const f_array_length_t length, f_thread_semaphores_t *semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_semaphores_resize(length, semaphores);
  }
#endif // _di_f_thread_semaphores_resize_

#ifndef _di_f_thread_sets_adjust_
  f_status_t f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_sets_adjust(length, sets);
  }
#endif // _di_f_thread_sets_adjust_

#ifndef _di_f_thread_sets_decimate_by_
  f_status_t f_thread_sets_decimate_by(const f_array_length_t amount, f_thread_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->size - amount > 0) {
      return private_f_thread_sets_adjust(sets->size - amount, sets);
    }

    return private_f_thread_sets_adjust(0, sets);
  }
#endif // _di_f_thread_sets_decimate_by_

#ifndef _di_f_thread_sets_decrease_by_
  f_status_t f_thread_sets_decrease_by(const f_array_length_t amount, f_thread_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->size - amount > 0) {
      return private_f_thread_sets_resize(sets->size - amount, sets);
    }

    return private_f_thread_sets_resize(0, sets);
  }
#endif // _di_f_thread_sets_decrease_by_

#ifndef _di_f_thread_sets_increase_
  f_status_t f_thread_sets_increase(const uint16_t step, f_thread_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->used + 1 > sets->size) {
      f_array_length_t size = sets->used + step;

      if (size > f_array_length_t_size) {
        if (sets->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_sets_resize(size, sets);
    }

    return F_data_not;
  }
#endif // _di_f_thread_sets_increase_

#ifndef _di_f_thread_sets_increase_by_
  f_status_t f_thread_sets_increase_by(const f_array_length_t amount, f_thread_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->used + amount > sets->size) {
      if (sets->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_sets_resize(sets->used + amount, sets);
    }

    return F_data_not;
  }
#endif // _di_f_thread_sets_increase_by_

#ifndef _di_f_thread_sets_resize_
  f_status_t f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_sets_resize(length, sets);
  }
#endif // _di_f_thread_sets_resize_

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

#if defined(_pthread_sigqueue_unsupported_) && !defined(_di_f_thread_signal_queue_)
  f_status_t f_thread_signal_queue(const f_thread_id_t id, const int signal, const union sigval value) {

    return F_status_set_error(F_implemented_not);
  }
#elif !defined(_di_f_thread_signal_queue_)
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
#endif // defined(_pthread_sigqueue_unsupported_) && !defined(_di_f_thread_signal_queue_)

#ifndef _di_f_thread_spin_create_
  f_status_t f_thread_spin_create(const int shared, f_thread_spin_t *spin) {
    #ifndef _di_level_0_parameter_checking_
      if (!spin) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_spin_init(spin, shared);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_spin_create_

#ifndef _di_f_thread_spin_delete_
  f_status_t f_thread_spin_delete(f_thread_spin_t *spin) {
    #ifndef _di_level_0_parameter_checking_
      if (!spin) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_spin_delete(spin);
  }
#endif // _di_f_thread_spin_delete_

#ifndef _di_f_thread_spin_lock_
  f_status_t f_thread_spin_lock(f_thread_spin_t *spin) {
    #ifndef _di_level_0_parameter_checking_
      if (!spin) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_spin_lock(spin);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EDEADLK) return F_status_set_error(F_deadlock);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_spin_lock_

#ifndef _di_f_thread_spin_lock_try_
  f_status_t f_thread_spin_lock_try(f_thread_spin_t *spin) {
    #ifndef _di_level_0_parameter_checking_
      if (!spin) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_spin_trylock(spin);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_busy;
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_spin_lock_try_

#ifndef _di_f_thread_spin_unlock_
  f_status_t f_thread_spin_unlock(f_thread_spin_t *spin) {
    #ifndef _di_level_0_parameter_checking_
      if (!spin) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_spin_unlock(spin);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_spin_unlock_

#ifndef _di_f_thread_spins_adjust_
  f_status_t f_thread_spins_adjust(const f_array_length_t length, f_thread_spins_t *spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_spins_adjust(length, spins);
  }
#endif // _di_f_thread_spins_adjust_

#ifndef _di_f_thread_spins_decimate_by_
  f_status_t f_thread_spins_decimate_by(const f_array_length_t amount, f_thread_spins_t *spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (spins->size - amount > 0) {
      return private_f_thread_spins_adjust(spins->size - amount, spins);
    }

    return private_f_thread_spins_adjust(0, spins);
  }
#endif // _di_f_thread_spins_decimate_by_

#ifndef _di_f_thread_spins_decrease_by_
  f_status_t f_thread_spins_decrease_by(const f_array_length_t amount, f_thread_spins_t *spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (spins->size - amount > 0) {
      return private_f_thread_spins_resize(spins->size - amount, spins);
    }

    return private_f_thread_spins_resize(0, spins);
  }
#endif // _di_f_thread_spins_decrease_by_

#ifndef _di_f_thread_spins_increase_
  f_status_t f_thread_spins_increase(const uint16_t step, f_thread_spins_t *spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (spins->used + 1 > spins->size) {
      f_array_length_t size = spins->used + step;

      if (size > f_array_length_t_size) {
        if (spins->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_spins_resize(size, spins);
    }

    return F_data_not;
  }
#endif // _di_f_thread_spins_increase_

#ifndef _di_f_thread_spins_increase_by_
  f_status_t f_thread_spins_increase_by(const f_array_length_t amount, f_thread_spins_t *spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (spins->used + amount > spins->size) {
      if (spins->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_spins_resize(spins->used + amount, spins);
    }

    return F_data_not;
  }
#endif // _di_f_thread_spins_increase_by_

#ifndef _di_f_thread_spins_resize_
  f_status_t f_thread_spins_resize(const f_array_length_t length, f_thread_spins_t *spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_spins_resize(length, spins);
  }
#endif // _di_f_thread_spins_resize_

#ifndef _di_f_thread_unlock_
  f_status_t f_thread_unlock(f_thread_lock_t *lock) {
    #ifndef _di_level_0_parameter_checking_
      if (!lock) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int error = pthread_rwlock_unlock(lock);

    if (error) {
      if (error == EAGAIN) return F_status_set_error(F_resource_not);
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);
      if (error == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_unlock_

#ifdef __cplusplus
} // extern "C"
#endif

#include "thread.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_create_
  f_return_status f_thread_create(const pthread_attr_t *attribute, pthread_t *id, void *(*routine) (void *), void *argument) {
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

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_thread_create_

#ifndef _di_f_thread_sets_decrease_
  f_return_status f_thread_sets_decrease(f_thread_sets_t *thread_sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!thread_sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (thread_sets->size > 1) {
      return private_f_thread_sets_resize(thread_sets->size - 1, thread_sets);
    }

    return private_f_thread_sets_delete(thread_sets);
  }
#endif // _di_f_thread_sets_decrease_

#ifndef _di_f_thread_sets_decrease_by_
  f_return_status f_thread_sets_decrease_by(const f_array_length_t amount, f_thread_sets_t *thread_sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!thread_sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (thread_sets->size - amount > 0) {
      return private_f_thread_sets_resize(thread_sets->size - amount, thread_sets);
    }

    return private_f_thread_sets_delete(thread_sets);
  }
#endif // _di_f_thread_sets_decrease_by_

#ifndef _di_f_thread_sets_delete_
  f_return_status f_thread_sets_delete(f_thread_sets_t *thread_sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!thread_sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_sets_delete(thread_sets);
  }
#endif // _di_f_thread_sets_delete_

#ifndef _di_f_thread_sets_increase_
  f_return_status f_thread_sets_increase(f_thread_sets_t *thread_sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!thread_sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (thread_sets->used + 1 > thread_sets->size) {
      f_array_length_t size = thread_sets->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (thread_sets->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_thread_sets_resize(size, thread_sets);
    }

    return F_none;
  }
#endif // _di_f_thread_sets_increase_

#ifndef _di_f_thread_sets_increase_by_
  f_return_status f_thread_sets_increase_by(const f_array_length_t amount, f_thread_sets_t *thread_sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!thread_sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (thread_sets->used + amount > thread_sets->size) {
      if (thread_sets->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_sets_resize(thread_sets->used + amount, thread_sets);
    }

    return F_none;
  }
#endif // _di_f_thread_sets_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

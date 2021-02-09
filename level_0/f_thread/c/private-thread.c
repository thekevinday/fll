#include "thread.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_) || !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_) || !defined(_di_f_thread_attributes_resize_) || !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_) || !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_) || !defined(_di_f_thread_sets_resize_)
  f_status_t private_f_thread_attribute_delete(f_thread_attribute_t *attribute) {

    if (pthread_attr_destroy(attribute)) {
      return F_status_set_error(F_failure);
    }

    attribute = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_) || !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_) || !defined(_di_f_thread_attributes_resize_) || !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_) || !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_) || !defined(_di_f_thread_sets_resize_)

#if !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_)
  f_status_t private_f_thread_attributes_adjust(const f_array_length_t length, f_thread_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(attributes->size, length, sizeof(f_thread_attribute_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_)

#if !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)
  f_status_t private_f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(attributes->size, length, sizeof(f_thread_attribute_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)

#if !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_) || !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_) || !defined(_di_f_thread_barriers_resize_)
  f_status_t private_f_thread_barrier_delete(f_thread_barrier_t *barrier) {

    if (pthread_barrier_destroy(barrier)) {
      return F_status_set_error(F_failure);
    }

    barrier = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_) || !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_) || !defined(_di_f_thread_barriers_resize_)

#if !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_)
  f_status_t private_f_thread_barriers_adjust(const f_array_length_t length, f_thread_barriers_t *barriers) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < barriers->size; ++i) {

      status = private_f_thread_barrier_delete(&barriers->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(barriers->size, length, sizeof(f_thread_barrier_t), (void **) & barriers->array);

    if (F_status_is_error_not(status)) {
      barriers->size = length;

      if (barriers->used > barriers->size) {
        barriers->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_)

#if !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_)
  f_status_t private_f_thread_barriers_resize(const f_array_length_t length, f_thread_barriers_t *barriers) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < barriers->size; ++i) {

      status = private_f_thread_barrier_delete(&barriers->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(barriers->size, length, sizeof(f_thread_barrier_t), (void **) & barriers->array);

    if (F_status_is_error_not(status)) {
      barriers->size = length;

      if (barriers->used > barriers->size) {
        barriers->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_)

#if !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_) || !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_) || !defined(_di_f_thread_barrier_attributes_resize_)
  f_status_t private_f_thread_barrier_attribute_delete(f_thread_barrier_attribute_t *attribute) {

    if (pthread_barrierattr_destroy(attribute)) {
      return F_status_set_error(F_failure);
    }

    attribute = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_) || !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_) || !defined(_di_f_thread_barrier_attributes_resize_)

#if !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_)
  f_status_t private_f_thread_barrier_attributes_adjust(const f_array_length_t length, f_thread_barrier_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_barrier_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(attributes->size, length, sizeof(f_thread_barrier_attribute_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_)

#if !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_)
  f_status_t private_f_thread_barrier_attributes_resize(const f_array_length_t length, f_thread_barrier_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_barrier_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(attributes->size, length, sizeof(f_thread_barrier_attribute_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_)

#if !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_) || !defined(_di_f_thread_condition_attributes_decrease_) || !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_) || !defined(_di_f_thread_condition_attributes_resize_)
  f_status_t private_f_thread_condition_attribute_delete(f_thread_condition_attribute_t *attribute) {

    const int error = pthread_condattr_destroy(attribute);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_) || !defined(_di_f_thread_condition_attributes_decrease_) || !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_) || !defined(_di_f_thread_condition_attributes_resize_)

#if !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_)
  f_status_t private_f_thread_condition_attributes_adjust(const f_array_length_t length, f_thread_condition_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_condition_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(attributes->size, length, sizeof(f_thread_condition_attribute_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_)

#if !defined(_di_f_thread_condition_attributes_decrease_) || !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_)
  f_status_t private_f_thread_condition_attributes_resize(const f_array_length_t length, f_thread_condition_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_condition_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(attributes->size, length, sizeof(f_thread_condition_attribute_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_condition_attributes_decrease_) || !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_)

#if !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_) || !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_) || !defined(_di_f_thread_conditions_resize_)
  f_status_t private_f_thread_condition_delete(f_thread_condition_t *condition) {

    const int error = pthread_cond_destroy(condition);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_) || !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_) || !defined(_di_f_thread_conditions_resize_)

#if !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_)
  f_status_t private_f_thread_conditions_adjust(const f_array_length_t length, f_thread_conditions_t *conditions) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < conditions->size; ++i) {

      status = private_f_thread_condition_delete(&conditions->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(conditions->size, length, sizeof(f_thread_condition_t), (void **) & conditions->array);

    if (F_status_is_error_not(status)) {
      conditions->size = length;

      if (conditions->used > conditions->size) {
        conditions->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_)

#if !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)
  f_status_t private_f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t *conditions) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < conditions->size; ++i) {

      status = private_f_thread_condition_delete(&conditions->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(conditions->size, length, sizeof(f_thread_condition_t), (void **) & conditions->array);

    if (F_status_is_error_not(status)) {
      conditions->size = length;

      if (conditions->used > conditions->size) {
        conditions->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)

#if !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_) || !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_) || !defined(_di_f_thread_keys_resize_)
  f_status_t private_f_thread_key_delete(f_thread_key_t *key) {

    if (pthread_key_delete(*key)) {
      return F_status_set_error(F_failure);
    }

    key = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_) || !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_) || !defined(_di_f_thread_keys_resize_)

#if !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_)
  f_status_t private_f_thread_keys_adjust(const f_array_length_t length, f_thread_keys_t *keys) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < keys->size; ++i) {

      status = private_f_thread_key_delete(&keys->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(keys->size, length, sizeof(f_thread_key_t), (void **) & keys->array);

    if (F_status_is_error_not(status)) {
      keys->size = length;

      if (keys->used > keys->size) {
        keys->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_)

#if !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)
  f_status_t private_f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t *keys) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < keys->size; ++i) {

      status = private_f_thread_key_delete(&keys->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(keys->size, length, sizeof(f_thread_key_t), (void **) & keys->array);

    if (F_status_is_error_not(status)) {
      keys->size = length;

      if (keys->used > keys->size) {
        keys->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)

#if !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)
  f_status_t private_f_thread_lock_delete(f_thread_lock_t *lock) {

    const int error = pthread_rwlock_destroy(lock);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)

#if !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_)
  f_status_t private_f_thread_locks_adjust(const f_array_length_t length, f_thread_locks_t *locks) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < locks->size; ++i) {

      status = private_f_thread_lock_delete(&locks->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(locks->size, length, sizeof(f_thread_lock_t), (void **) & locks->array);

    if (F_status_is_error_not(status)) {
      locks->size = length;

      if (locks->used > locks->size) {
        locks->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_)

#if !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)
  f_status_t private_f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t *locks) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < locks->size; ++i) {

      status = private_f_thread_lock_delete(&locks->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(locks->size, length, sizeof(f_thread_lock_t), (void **) & locks->array);

    if (F_status_is_error_not(status)) {
      locks->size = length;

      if (locks->used > locks->size) {
        locks->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)

#if !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_) || !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_) || !defined(_di_f_thread_lock_attributes_resize_)
  f_status_t private_f_thread_lock_attribute_delete(f_thread_lock_attribute_t *attribute) {

    const int error = pthread_rwlockattr_destroy(attribute);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_) || !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_) || !defined(_di_f_thread_lock_attributes_resize_)

#if !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_)
  f_status_t private_f_thread_lock_attributes_adjust(const f_array_length_t length, f_thread_lock_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_lock_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(attributes->size, length, sizeof(f_thread_lock_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_)

#if !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)
  f_status_t private_f_thread_lock_attributes_resize(const f_array_length_t length, f_thread_lock_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_lock_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(attributes->size, length, sizeof(f_thread_lock_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)

#if !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_) || !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_) || !defined(_di_f_thread_mutex_attributes_resize_)
  f_status_t private_f_thread_mutex_attribute_delete(f_thread_mutex_attribute_t *attribute) {

    const int error = pthread_mutexattr_destroy(attribute);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_) || !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_) || !defined(_di_f_thread_mutex_attributes_resize_)

#if !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_)
  f_status_t private_f_thread_mutex_attributes_adjust(const f_array_length_t length, f_thread_mutex_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_mutex_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(attributes->size, length, sizeof(f_thread_mutex_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_)

#if !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)
  f_status_t private_f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t *attributes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_mutex_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(attributes->size, length, sizeof(f_thread_mutex_t), (void **) & attributes->array);

    if (F_status_is_error_not(status)) {
      attributes->size = length;

      if (attributes->used > attributes->size) {
        attributes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)

#if !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)
  f_status_t private_f_thread_mutex_delete(f_thread_mutex_t *mutex) {

    const int error = pthread_mutex_destroy(mutex);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)

#if !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_)
  f_status_t private_f_thread_mutexs_adjust(const f_array_length_t length, f_thread_mutexs_t *mutexs) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < mutexs->size; ++i) {

      status = private_f_thread_mutex_delete(&mutexs->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(mutexs->size, length, sizeof(f_thread_mutex_t), (void **) & mutexs->array);

    if (F_status_is_error_not(status)) {
      mutexs->size = length;

      if (mutexs->used > mutexs->size) {
        mutexs->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_)

#if !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)
  f_status_t private_f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t *mutexs) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < mutexs->size; ++i) {

      status = private_f_thread_mutex_delete(&mutexs->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(mutexs->size, length, sizeof(f_thread_mutex_t), (void **) & mutexs->array);

    if (F_status_is_error_not(status)) {
      mutexs->size = length;

      if (mutexs->used > mutexs->size) {
        mutexs->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)

#if !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_)
  f_status_t private_f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t *sets) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < sets->size; ++i) {

      status = private_f_thread_attribute_delete(&sets->array[i].attribute);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(sets->size, length, sizeof(f_thread_set_t), (void **) & sets->array);

    if (F_status_is_error_not(status)) {
      sets->size = length;

      if (sets->used > sets->size) {
        sets->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_)

#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)
  f_status_t private_f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *sets) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < sets->size; ++i) {

      status = private_f_thread_attribute_delete(&sets->array[i].attribute);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(sets->size, length, sizeof(f_thread_set_t), (void **) & sets->array);

    if (F_status_is_error_not(status)) {
      sets->size = length;

      if (sets->used > sets->size) {
        sets->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)

#if !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_) || !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_) || !defined(_di_f_thread_spins_resize_)
  f_status_t private_f_thread_spin_delete(f_thread_spin_t *spin) {

    const int error = pthread_spin_destroy(spin);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_) || !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_) || !defined(_di_f_thread_spins_resize_)

#if !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_)
  f_status_t private_f_thread_spins_adjust(const f_array_length_t length, f_thread_spins_t *spins) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < spins->size; ++i) {

      status = private_f_thread_spin_delete(&spins->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(spins->size, length, sizeof(f_thread_spin_t), (void **) & spins->array);

    if (F_status_is_error_not(status)) {
      spins->size = length;

      if (spins->used > spins->size) {
        spins->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_)

#if !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)
  f_status_t private_f_thread_spins_resize(const f_array_length_t length, f_thread_spins_t *spins) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < spins->size; ++i) {

      status = private_f_thread_spin_delete(&spins->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(spins->size, length, sizeof(f_thread_spin_t), (void **) & spins->array);

    if (F_status_is_error_not(status)) {
      spins->size = length;

      if (spins->used > spins->size) {
        spins->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

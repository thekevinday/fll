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

#ifdef __cplusplus
} // extern "C"
#endif

#include "../thread.h"
#include "private-lock_attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

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
  f_status_t private_f_thread_lock_attributes_adjust(const f_number_unsigned_t length, f_thread_lock_attributes_t * const attributes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_lock_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_lock_attribute_t), (void **) &attributes->array, &attributes->used, &attributes->size);
  }
#endif // !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_)

#if !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)
  f_status_t private_f_thread_lock_attributes_resize(const f_number_unsigned_t length, f_thread_lock_attributes_t * const attributes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_lock_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_lock_attribute_t), (void **) &attributes->array, &attributes->used, &attributes->size);
  }
#endif // !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../thread.h"
#include "private-barrier_attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_) || !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_) || !defined(_di_f_thread_barrier_attributes_resize_)
  f_status_t private_f_thread_barrier_attribute_delete(f_thread_barrier_attribute_t *attribute) {

    if (pthread_barrierattr_destroy(attribute)) return F_status_set_error(F_failure);

    attribute = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_) || !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_) || !defined(_di_f_thread_barrier_attributes_resize_)

#if !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_)
  f_status_t private_f_thread_barrier_attributes_adjust(const f_number_unsigned_t length, f_thread_barrier_attributes_t * const attributes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_barrier_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_barrier_attribute_t), (void **) &attributes->array, &attributes->used, &attributes->size);
  }
#endif // !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_)

#if !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_)
  f_status_t private_f_thread_barrier_attributes_resize(const f_number_unsigned_t length, f_thread_barrier_attributes_t * const attributes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_barrier_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_barrier_attribute_t), (void **) &attributes->array, &attributes->used, &attributes->size);
  }
#endif // !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

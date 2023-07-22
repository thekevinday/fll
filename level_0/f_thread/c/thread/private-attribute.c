#include "../thread.h"
#include "private-attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_) || !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_) || !defined(_di_f_thread_attributes_resize_) || !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_) || !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_) || !defined(_di_f_thread_sets_resize_)
  f_status_t private_f_thread_attribute_delete(f_thread_attribute_t *structure) {

    if (pthread_attr_destroy(structure)) return F_status_set_error(F_failure);

    return F_none;
  }
#endif // !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_) || !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_) || !defined(_di_f_thread_attributes_resize_) || !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_) || !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_) || !defined(_di_f_thread_sets_resize_)

#if !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_)
  f_status_t private_f_thread_attributes_adjust(const f_number_unsigned_t length, f_thread_attributes_t * const attributes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_attribute_t), (void **) &attributes->array, &attributes->used, &attributes->size);
  }
#endif // !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_)

#if !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)
  f_status_t private_f_thread_attributes_resize(const f_number_unsigned_t length, f_thread_attributes_t * const attributes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < attributes->size; ++i) {

      status = private_f_thread_attribute_delete(&attributes->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_attribute_t), (void **) &attributes->array, &attributes->used, &attributes->size);
  }
#endif // !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

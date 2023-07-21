#include "../thread.h"
#include "private-attribute.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_)
  f_status_t private_f_thread_sets_adjust(const f_number_unsigned_t length, f_thread_sets_t * const sets) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < sets->size; ++i) {

      status = private_f_thread_attribute_delete(&sets->array[i].attribute);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_)

#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)
  f_status_t private_f_thread_sets_resize(const f_number_unsigned_t length, f_thread_sets_t * const sets) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < sets->size; ++i) {

      status = private_f_thread_attribute_delete(&sets->array[i].attribute);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

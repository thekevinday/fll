#include "../thread.h"
#include "private-key.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_) || !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_) || !defined(_di_f_thread_keys_resize_)
  f_status_t private_f_thread_key_delete(f_thread_key_t *structure) {

    if (pthread_key_delete(*structure)) return F_status_set_error(F_failure);

    *structure = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_) || !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_) || !defined(_di_f_thread_keys_resize_)

#if !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_)
  f_status_t private_f_thread_keys_adjust(const f_number_unsigned_t length, f_thread_keys_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_thread_key_delete(&structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_key_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_)

#if !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)
  f_status_t private_f_thread_keys_resize(const f_number_unsigned_t length, f_thread_keys_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_thread_key_delete(&structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_key_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

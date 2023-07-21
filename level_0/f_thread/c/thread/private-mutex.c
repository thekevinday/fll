#include "../thread.h"
#include "private-mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_mutex_delete_) || !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)
  f_status_t private_f_thread_mutex_delete(f_thread_mutex_t *mutex) {

    const int error = pthread_mutex_destroy(mutex);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_mutex_delete_) || !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)

#if !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_)
  f_status_t private_f_thread_mutexs_adjust(const f_number_unsigned_t length, f_thread_mutexs_t * const mutexs) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < mutexs->size; ++i) {

      status = private_f_thread_mutex_delete(&mutexs->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_mutex_t), (void **) &mutexs->array, &mutexs->used, &mutexs->size);
  }
#endif // !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_)

#if !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)
  f_status_t private_f_thread_mutexs_resize(const f_number_unsigned_t length, f_thread_mutexs_t * const mutexs) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < mutexs->size; ++i) {

      status = private_f_thread_mutex_delete(&mutexs->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_mutex_t), (void **) &mutexs->array, &mutexs->used, &mutexs->size);
  }
#endif // !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

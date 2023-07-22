#include "../thread.h"
#include "private-semaphore.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_) || !defined(_di_f_thread_semaphores_decrease_) || !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_) || !defined(_di_f_thread_semaphores_resize_)
  f_status_t private_f_thread_semaphore_delete(f_thread_semaphore_t *structure) {

    const int result = sem_destroy(structure);

    if (result == -1) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_) || !defined(_di_f_thread_semaphores_decrease_) || !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_) || !defined(_di_f_thread_semaphores_resize_)

#if !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_)
  f_status_t private_f_thread_semaphores_adjust(const f_number_unsigned_t length, f_thread_semaphores_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_thread_semaphore_delete(&structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_semaphore_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_)

#if !defined(_di_f_thread_semaphores_decrease_) || !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_)
  f_status_t private_f_thread_semaphores_resize(const f_number_unsigned_t length, f_thread_semaphores_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_thread_semaphore_delete(&structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_semaphore_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_thread_semaphores_decrease_) || !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../thread.h"
#include "private-barrier.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_) || !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_) || !defined(_di_f_thread_barriers_resize_)
  f_status_t private_f_thread_barrier_delete(f_thread_barrier_t *barrier) {

    const int error = pthread_barrier_destroy(barrier);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    barrier = 0;

    return F_none;
  }
#endif // !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_) || !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_) || !defined(_di_f_thread_barriers_resize_)

#if !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_)
  f_status_t private_f_thread_barriers_adjust(const f_number_unsigned_t length, f_thread_barriers_t * const barriers) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < barriers->size; ++i) {

      status = private_f_thread_barrier_delete(&barriers->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_barrier_t), (void **) &barriers->array, &barriers->used, &barriers->size);
  }
#endif // !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_)

#if !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_)
  f_status_t private_f_thread_barriers_resize(const f_number_unsigned_t length, f_thread_barriers_t * const barriers) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < barriers->size; ++i) {

      status = private_f_thread_barrier_delete(&barriers->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_barrier_t), (void **) &barriers->array, &barriers->used, &barriers->size);
  }
#endif // !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

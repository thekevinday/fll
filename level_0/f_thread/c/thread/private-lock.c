#include "../thread.h"
#include "private-lock.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_lock_delete_) || !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)
  f_status_t private_f_thread_lock_delete(f_thread_lock_t *lock) {

    const int error = pthread_rwlock_destroy(lock);

    if (error) {
      if (error == EBUSY) return F_status_set_error(F_busy);
      if (error == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_thread_lock_delete_) || !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)

#if !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_)
  f_status_t private_f_thread_locks_adjust(const f_number_unsigned_t length, f_thread_locks_t * const locks) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < locks->size; ++i) {

      status = private_f_thread_lock_delete(&locks->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_thread_lock_t), (void **) &locks->array, &locks->used, &locks->size);
  }
#endif // !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_)

#if !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)
  f_status_t private_f_thread_locks_resize(const f_number_unsigned_t length, f_thread_locks_t * const locks) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < locks->size; ++i) {

      status = private_f_thread_lock_delete(&locks->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_thread_lock_t), (void **) &locks->array, &locks->used, &locks->size);
  }
#endif // !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

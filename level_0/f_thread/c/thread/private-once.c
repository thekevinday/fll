#include "../thread.h"
#include "private-once.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_onces_adjust_) || !defined(_di_f_thread_onces_decimate_by_)
  f_status_t private_f_thread_onces_adjust(const f_number_unsigned_t length, f_thread_onces_t * const onces) {

    if (onces->size) {
      memset(onces->array, 0, sizeof(f_thread_once_t) * onces->size);
    }

    return f_memory_array_adjust(length, sizeof(f_thread_once_t), (void **) &onces->array, &onces->used, &onces->size);
  }
#endif // !defined(_di_f_thread_onces_adjust_) || !defined(_di_f_thread_onces_decimate_by_)

#if !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)
  f_status_t private_f_thread_onces_resize(const f_number_unsigned_t length, f_thread_onces_t * const onces) {

    return f_memory_array_resize(length, sizeof(f_thread_once_t), (void **) &onces->array, &onces->used, &onces->size);
  }
#endif // !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

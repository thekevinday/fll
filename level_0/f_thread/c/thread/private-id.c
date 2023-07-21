#include "../thread.h"
#include "private-id.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_ids_adjust_) || !defined(_di_f_thread_ids_decimate_by_)
  f_status_t private_f_thread_ids_adjust(const f_number_unsigned_t length, f_thread_ids_t * const ids) {

    if (ids->size) {
      memset(ids->array, 0, sizeof(f_thread_id_t) * ids->size);
    }

    return f_memory_array_adjust(length, sizeof(f_thread_id_t), (void **) &ids->array, &ids->used, &ids->size);
  }
#endif // !defined(_di_f_thread_ids_adjust_) || !defined(_di_f_thread_ids_decimate_by_)

#if !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)
  f_status_t private_f_thread_ids_resize(const f_number_unsigned_t length, f_thread_ids_t * const ids) {

    return f_memory_array_resize(length, sizeof(f_thread_id_t), (void **) &ids->array, &ids->used, &ids->size);
  }
#endif // !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

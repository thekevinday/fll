#include "../thread.h"
#include "private-id.h"
#include "id.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_ids_adjust_
  f_status_t f_thread_ids_adjust(const f_number_unsigned_t length, f_thread_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_thread_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_ids_adjust_

#ifndef _di_f_thread_ids_decimate_by_
  f_status_t f_thread_ids_decimate_by(const f_number_unsigned_t amount, f_thread_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_thread_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_ids_decimate_by_

#ifndef _di_f_thread_ids_decrease_by_
  f_status_t f_thread_ids_decrease_by(const f_number_unsigned_t amount, f_thread_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_thread_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_ids_decrease_by_

#ifndef _di_f_thread_ids_increase_
  f_status_t f_thread_ids_increase(const f_number_unsigned_t step, f_thread_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_thread_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_ids_increase_

#ifndef _di_f_thread_ids_increase_by_
  f_status_t f_thread_ids_increase_by(const f_number_unsigned_t amount, f_thread_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_thread_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_ids_increase_by_

#ifndef _di_f_thread_ids_resize_
  f_status_t f_thread_ids_resize(const f_number_unsigned_t length, f_thread_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_thread_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_ids_resize_

#ifdef __cplusplus
} // extern "C"
#endif

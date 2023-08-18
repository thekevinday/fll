#include "../limit.h"
#include "value.h"
#include "private-value.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_valuess_append_)
  extern f_status_t private_f_limit_values_append(const f_limit_value_t source, f_limit_values_t *destination) {

    const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_limit_value_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    destination->array[destination->used++] = source;

    return F_okay;
  }
#endif // !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_valuess_append_)

#if !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_values_append_all_) || !defined(_di_f_limit_valuess_append_all_)
  extern f_status_t private_f_limit_values_append_all(const f_limit_values_t source, f_limit_values_t *destination) {

    const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_limit_value_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_okay;
  }
#endif // !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_values_append_all_) || !defined(_di_f_limit_valuess_append_all_)

#if !defined(_di_f_limit_valuess_adjust_) || !defined(_di_f_limit_valuess_decimate_by_)
  f_status_t private_f_limit_valuess_adjust(const f_number_unsigned_t length, f_limit_valuess_t *valuess) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < valuess->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_limit_value_t), (void **) &valuess->array[i].array, &valuess->array[i].used, &valuess->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_limit_values_t), (void **) &valuess->array, &valuess->used, &valuess->size);
  }
#endif // !defined(_di_f_limit_valuess_adjust_) || !defined(_di_f_limit_valuess_decimate_by_)

#if !defined(_di_f_limit_valuess_decrease_by_) || !defined(_di_f_limit_valuess_increase_) || !defined(_di_f_limit_valuess_increase_by_) || !defined(_di_f_limit_valuess_resize_)
  f_status_t private_f_limit_valuess_resize(const f_number_unsigned_t length, f_limit_valuess_t *valuess) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < valuess->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_limit_value_t), (void **) &valuess->array[i].array, &valuess->array[i].used, &valuess->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_limit_values_t), (void **) &valuess->array, &valuess->used, &valuess->size);
  }
#endif // !defined(_di_f_limit_valuess_decrease_by_) || !defined(_di_f_limit_valuess_increase_) || !defined(_di_f_limit_valuess_increase_by_) || !defined(_di_f_limit_valuess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

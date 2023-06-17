#include "../limit.h"
#include "value.h"
#include "private-value.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_limit_values_adjust_) || !defined(_di_f_limit_values_decimate_by_)
  f_status_t private_f_limit_values_adjust(const f_number_unsigned_t length, f_limit_values_t *values) {

    const f_status_t status = f_memory_adjust(values->size, length, sizeof(f_limit_value_t), (void **) & values->array);
    if (F_status_is_error(status)) return status;

    values->size = length;

    if (values->used > values->size) {
      values->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_values_adjust_) || !defined(_di_f_limit_values_decimate_by_)

#if !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_valuess_append_)
  extern f_status_t private_f_limit_values_append(const f_limit_value_t source, f_limit_values_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_limit_values_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_valuess_append_)

#if !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_values_append_all_) || !defined(_di_f_limit_valuess_append_all_)
  extern f_status_t private_f_limit_values_append_all(const f_limit_values_t source, f_limit_values_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_limit_values_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_values_append_all_) || !defined(_di_f_limit_valuess_append_all_)

#if !defined(_di_f_limit_values_resize_) || !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_values_decimate_by_) || !defined(_di_f_limit_valuess_append_)
  f_status_t private_f_limit_values_resize(const f_number_unsigned_t length, f_limit_values_t *values) {

    const f_status_t status = f_memory_resize(values->size, length, sizeof(f_limit_value_t), (void **) & values->array);
    if (F_status_is_error(status)) return status;

    values->size = length;

    if (values->used > values->size) {
      values->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_values_resize_) || !defined(_di_f_limit_values_append_) || !defined(_di_f_limit_values_decimate_by_) || !defined(_di_f_limit_valuess_append_)

#if !defined(_di_f_limit_valuess_adjust_) || !defined(_di_f_limit_valuess_decimate_by_)
  f_status_t private_f_limit_valuess_adjust(const f_number_unsigned_t length, f_limit_valuess_t *valuess) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < valuess->size; ++i) {

      status = f_memory_destroy(valuess->array[i].size, sizeof(f_limit_values_t), (void **) & valuess->array[i].array);
      if (F_status_is_error(status)) return status;

      valuess->array[i].size = 0;
      valuess->array[i].used = 0;
    } // for

    status = f_memory_adjust(valuess->size, length, sizeof(f_limit_values_t), (void **) & valuess->array);
    if (F_status_is_error(status)) return status;

    valuess->size = length;

    if (valuess->used > valuess->size) {
      valuess->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_valuess_adjust_) || !defined(_di_f_limit_valuess_decimate_by_)

#if !defined(_di_f_limit_valuess_decrease_by_) || !defined(_di_f_limit_valuess_increase_) || !defined(_di_f_limit_valuess_increase_by_) || !defined(_di_f_limit_valuess_resize_)
  f_status_t private_f_limit_valuess_resize(const f_number_unsigned_t length, f_limit_valuess_t *valuess) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < valuess->size; ++i) {

      status = f_memory_delete(valuess->array[i].size, sizeof(f_limit_values_t), (void **) & valuess->array[i].array);
      if (F_status_is_error(status)) return status;

      valuess->array[i].size = 0;
      valuess->array[i].used = 0;
    } // for

    status = f_memory_resize(valuess->size, length, sizeof(f_limit_values_t), (void **) & valuess->array);
    if (F_status_is_error(status)) return status;

    valuess->size = length;

    if (valuess->used > valuess->size) {
      valuess->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_valuess_decrease_by_) || !defined(_di_f_limit_valuess_increase_) || !defined(_di_f_limit_valuess_increase_by_) || !defined(_di_f_limit_valuess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

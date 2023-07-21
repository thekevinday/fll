#include "../limit.h"
#include "value.h"
#include "private-value.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_limit_values_adjust_
  f_status_t f_limit_values_adjust(const f_number_unsigned_t length, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_limit_value_t), (void **) &values->array, &values->used, &values->size);
  }
#endif // _di_f_limit_values_adjust_

#ifndef _di_f_limit_values_append_
  f_status_t f_limit_values_append(const f_limit_value_t source, f_limit_values_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_values_append(source, destination);
  }
#endif // _di_f_limit_values_append_

#ifndef _di_f_limit_values_append_all_
  f_status_t f_limit_values_append_all(const f_limit_values_t source, f_limit_values_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_limit_values_append_all(source, destination);
  }
#endif // _di_f_limit_values_append_all_

#ifndef _di_f_limit_values_decimate_by_
  f_status_t f_limit_values_decimate_by(const f_number_unsigned_t amount, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_limit_value_t), (void **) &values->array, &values->used, &values->size);
  }
#endif // _di_f_limit_values_decimate_by_

#ifndef _di_f_limit_values_decrease_by_
  f_status_t f_limit_values_decrease_by(const f_number_unsigned_t amount, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_limit_value_t), (void **) &values->array, &values->used, &values->size);
  }
#endif // _di_f_limit_values_decrease_by_

#ifndef _di_f_limit_values_increase_
  f_status_t f_limit_values_increase(const f_number_unsigned_t step, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_limit_value_t), (void **) &values->array, &values->used, &values->size);
  }
#endif // _di_f_limit_values_increase_

#ifndef _di_f_limit_values_increase_by_
  f_status_t f_limit_values_increase_by(const f_number_unsigned_t amount, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_limit_value_t), (void **) &values->array, &values->used, &values->size);
  }
#endif // _di_f_limit_values_increase_by_

#ifndef _di_f_limit_values_resize_
  f_status_t f_limit_values_resize(const f_number_unsigned_t length, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_limit_value_t), (void **) &values->array, &values->used, &values->size);
  }
#endif // _di_f_limit_values_resize_

#ifndef _di_f_limit_valuess_adjust_
  f_status_t f_limit_valuess_adjust(const f_number_unsigned_t length, f_limit_valuess_t *valuess) {
    #ifndef _di_level_0_parameter_checking_
      if (!valuess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_valuess_adjust(length, valuess);
  }
#endif // _di_f_limit_valuess_adjust_

#ifndef _di_f_limit_valuess_append_
  f_status_t f_limit_valuess_append(const f_limit_values_t source, f_limit_valuess_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_limit_values_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_limit_values_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_limit_valuess_append_

#ifndef _di_f_limit_valuess_append_all_
  f_status_t f_limit_valuess_append_all(const f_limit_valuess_t source, f_limit_valuess_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_limit_values_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_limit_values_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_limit_valuess_append_all_

#ifndef _di_f_limit_valuess_decimate_by_
  f_status_t f_limit_valuess_decimate_by(const f_number_unsigned_t amount, f_limit_valuess_t *valuess) {
    #ifndef _di_level_0_parameter_checking_
      if (!valuess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_limit_valuess_adjust((valuess->size > amount) ? valuess->size - amount : 0, valuess);
  }
#endif // _di_f_limit_valuess_decimate_by_

#ifndef _di_f_limit_valuess_decrease_by_
  f_status_t f_limit_valuess_decrease_by(const f_number_unsigned_t amount, f_limit_valuess_t *valuess) {
    #ifndef _di_level_0_parameter_checking_
      if (!valuess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_limit_valuess_resize((valuess->size > amount) ? valuess->size - amount : 0, valuess);
  }
#endif // _di_f_limit_valuess_decrease_by_

#ifndef _di_f_limit_valuess_increase_
  f_status_t f_limit_valuess_increase(const f_number_unsigned_t step, f_limit_valuess_t *valuess) {
    #ifndef _di_level_0_parameter_checking_
      if (!valuess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_limit_values_t), (void **) &valuess->array, &valuess->used, &valuess->size);
  }
#endif // _di_f_limit_valuess_increase_

#ifndef _di_f_limit_valuess_increase_by_
  f_status_t f_limit_valuess_increase_by(const f_number_unsigned_t amount, f_limit_valuess_t *valuess) {
    #ifndef _di_level_0_parameter_checking_
      if (!valuess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_limit_values_t), (void **) &valuess->array, &valuess->used, &valuess->size);
  }
#endif // _di_f_limit_valuess_increase_by_

#ifndef _di_f_limit_valuess_resize_
  f_status_t f_limit_valuess_resize(const f_number_unsigned_t length, f_limit_valuess_t *valuess) {
    #ifndef _di_level_0_parameter_checking_
      if (!valuess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_valuess_resize(length, valuess);
  }
#endif // _di_f_limit_valuess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

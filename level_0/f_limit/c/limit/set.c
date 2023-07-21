#include "../limit.h"
#include "set.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_limit_sets_adjust_
  f_status_t f_limit_sets_adjust(const f_number_unsigned_t length, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_limit_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_limit_sets_adjust_

#ifndef _di_f_limit_sets_append_
  f_status_t f_limit_sets_append(const f_limit_set_t source, f_limit_sets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_sets_append(source, destination);
  }
#endif // _di_f_limit_sets_append_

#ifndef _di_f_limit_sets_append_all_
  f_status_t f_limit_sets_append_all(const f_limit_sets_t source, f_limit_sets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_limit_sets_append_all(source, destination);
  }
#endif // _di_f_limit_sets_append_all_

#ifndef _di_f_limit_sets_decimate_by_
  f_status_t f_limit_sets_decimate_by(const f_number_unsigned_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_limit_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_limit_sets_decimate_by_

#ifndef _di_f_limit_sets_decrease_by_
  f_status_t f_limit_sets_decrease_by(const f_number_unsigned_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_limit_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_limit_sets_decrease_by_

#ifndef _di_f_limit_sets_increase_
  f_status_t f_limit_sets_increase(const f_number_unsigned_t step, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_limit_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_limit_sets_increase_

#ifndef _di_f_limit_sets_increase_by_
  f_status_t f_limit_sets_increase_by(const f_number_unsigned_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_limit_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_limit_sets_increase_by_

#ifndef _di_f_limit_sets_resize_
  f_status_t f_limit_sets_resize(const f_number_unsigned_t length, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_limit_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_limit_sets_resize_

#ifndef _di_f_limit_setss_adjust_
  f_status_t f_limit_setss_adjust(const f_number_unsigned_t length, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_setss_adjust(length, setss);
  }
#endif // _di_f_limit_setss_adjust_

#ifndef _di_f_limit_setss_append_
  f_status_t f_limit_setss_append(const f_limit_sets_t source, f_limit_setss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_limit_sets_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_limit_sets_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_limit_setss_append_

#ifndef _di_f_limit_setss_append_all_
  f_status_t f_limit_setss_append_all(const f_limit_setss_t source, f_limit_setss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_limit_sets_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_limit_sets_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_limit_setss_append_all_

#ifndef _di_f_limit_setss_decimate_by_
  f_status_t f_limit_setss_decimate_by(const f_number_unsigned_t amount, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_limit_setss_adjust((setss->size > amount) ? setss->size - amount : 0, setss);
  }
#endif // _di_f_limit_setss_decimate_by_

#ifndef _di_f_limit_setss_decrease_by_
  f_status_t f_limit_setss_decrease_by(const f_number_unsigned_t amount, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_limit_setss_resize((setss->size > amount) ? setss->size - amount : 0, setss);
  }
#endif // _di_f_limit_setss_decrease_by_

#ifndef _di_f_limit_setss_increase_
  f_status_t f_limit_setss_increase(const f_number_unsigned_t step, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_limit_sets_t), (void **) &setss->array, &setss->used, &setss->size);
  }
#endif // _di_f_limit_setss_increase_

#ifndef _di_f_limit_setss_increase_by_
  f_status_t f_limit_setss_increase_by(const f_number_unsigned_t amount, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_limit_sets_t), (void **) &setss->array, &setss->used, &setss->size);
  }
#endif // _di_f_limit_setss_increase_by_

#ifndef _di_f_limit_setss_resize_
  f_status_t f_limit_setss_resize(const f_number_unsigned_t length, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_setss_resize(length, setss);
  }
#endif // _di_f_limit_setss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

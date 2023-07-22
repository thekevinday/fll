#include "../type_array.h"
#include "status.h"
#include "private-status.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_statuss_adjust_
  f_status_t f_statuss_adjust(const f_number_unsigned_t length, f_statuss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_status_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_statuss_adjust_

#ifndef _di_f_statuss_append_
  f_status_t f_statuss_append(const f_status_t source, f_statuss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statuss_append(source, destination);
  }
#endif // _di_f_statuss_append_

#ifndef _di_f_statuss_append_all_
  f_status_t f_statuss_append_all(const f_statuss_t source, f_statuss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_statuss_append_all(source, destination);
  }
#endif // _di_f_statuss_append_all_

#ifndef _di_f_statuss_decimate_by_
  f_status_t f_statuss_decimate_by(const f_number_unsigned_t amount, f_statuss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_status_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_statuss_decimate_by_

#ifndef _di_f_statuss_decrease_by_
  f_status_t f_statuss_decrease_by(const f_number_unsigned_t amount, f_statuss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_status_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_statuss_decrease_by_

#ifndef _di_f_statuss_increase_
  f_status_t f_statuss_increase(const f_number_unsigned_t step, f_statuss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_status_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_statuss_increase_

#ifndef _di_f_statuss_increase_by_
  f_status_t f_statuss_increase_by(const f_number_unsigned_t amount, f_statuss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_status_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_statuss_increase_by_

#ifndef _di_f_statuss_resize_
  f_status_t f_statuss_resize(const f_number_unsigned_t length, f_statuss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_status_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_statuss_resize_

#ifndef _di_f_statusss_adjust_
  f_status_t f_statusss_adjust(const f_number_unsigned_t length, f_statusss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statusss_adjust(length, structure);
  }
#endif // _di_f_statusss_adjust_

#ifndef _di_f_statusss_append_
  f_status_t f_statusss_append(const f_statuss_t source, f_statusss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_statuss_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_statuss_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_statusss_append_

#ifndef _di_f_statusss_append_all_
  f_status_t f_statusss_append_all(const f_statusss_t source, f_statusss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_statuss_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_statuss_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_statusss_append_all_

#ifndef _di_f_statusss_decimate_by_
  f_status_t f_statusss_decimate_by(const f_number_unsigned_t amount, f_statusss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_statusss_adjust((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_statusss_decimate_by_

#ifndef _di_f_statusss_decrease_by_
  f_status_t f_statusss_decrease_by(const f_number_unsigned_t amount, f_statusss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_statusss_resize((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_statusss_decrease_by_

#ifndef _di_f_statusss_increase_
  f_status_t f_statusss_increase(const f_number_unsigned_t step, f_statusss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_statusss_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_statusss_increase_

#ifndef _di_f_statusss_increase_by_
  f_status_t f_statusss_increase_by(const f_number_unsigned_t amount, f_statusss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_statusss_resize(structure->used + amount, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_statusss_increase_by_

#ifndef _di_f_statusss_resize_
  f_status_t f_statusss_resize(const f_number_unsigned_t length, f_statusss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statusss_resize(length, structure);
  }
#endif // _di_f_statusss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

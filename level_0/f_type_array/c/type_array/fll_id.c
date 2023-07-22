#include "../type_array.h"
#include "fll_id.h"
#include "private-fll_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fll_ids_adjust_
  f_status_t f_fll_ids_adjust(const f_number_unsigned_t length, f_fll_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_fll_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_fll_ids_adjust_

#ifndef _di_f_fll_ids_append_
  f_status_t f_fll_ids_append(const f_fll_id_t source, f_fll_ids_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_ids_append(source, destination);
  }
#endif // _di_f_fll_ids_append_

#ifndef _di_f_fll_ids_append_all_
  f_status_t f_fll_ids_append_all(const f_fll_ids_t source, f_fll_ids_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_fll_ids_append_all(source, destination);
  }
#endif // _di_f_fll_ids_append_all_

#ifndef _di_f_fll_ids_decimate_by_
  f_status_t f_fll_ids_decimate_by(const f_number_unsigned_t amount, f_fll_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_fll_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_fll_ids_decimate_by_

#ifndef _di_f_fll_ids_decrease_by_
  f_status_t f_fll_ids_decrease_by(const f_number_unsigned_t amount, f_fll_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_fll_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_fll_ids_decrease_by_

#ifndef _di_f_fll_ids_increase_
  f_status_t f_fll_ids_increase(const f_number_unsigned_t step, f_fll_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fll_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_fll_ids_increase_

#ifndef _di_f_fll_ids_increase_by_
  f_status_t f_fll_ids_increase_by(const f_number_unsigned_t amount, f_fll_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fll_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_fll_ids_increase_by_

#ifndef _di_f_fll_ids_resize_
  f_status_t f_fll_ids_resize(const f_number_unsigned_t length, f_fll_ids_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_fll_id_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_fll_ids_resize_

#ifndef _di_f_fll_idss_adjust_
  f_status_t f_fll_idss_adjust(const f_number_unsigned_t length, f_fll_idss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_idss_adjust(length, structure);
  }
#endif // _di_f_fll_idss_adjust_

#ifndef _di_f_fll_idss_append_
  f_status_t f_fll_idss_append(const f_fll_ids_t source, f_fll_idss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_fll_ids_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_fll_ids_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_fll_idss_append_

#ifndef _di_f_fll_idss_append_all_
  f_status_t f_fll_idss_append_all(const f_fll_idss_t source, f_fll_idss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_fll_ids_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_fll_ids_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_fll_idss_append_all_

#ifndef _di_f_fll_idss_decimate_by_
  f_status_t f_fll_idss_decimate_by(const f_number_unsigned_t amount, f_fll_idss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fll_idss_adjust((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_fll_idss_decimate_by_

#ifndef _di_f_fll_idss_decrease_by_
  f_status_t f_fll_idss_decrease_by(const f_number_unsigned_t amount, f_fll_idss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fll_idss_resize((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_fll_idss_decrease_by_

#ifndef _di_f_fll_idss_increase_
  f_status_t f_fll_idss_increase(const f_number_unsigned_t step, f_fll_idss_t * const structure) {
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

      return private_f_fll_idss_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_fll_idss_increase_

#ifndef _di_f_fll_idss_increase_by_
  f_status_t f_fll_idss_increase_by(const f_number_unsigned_t amount, f_fll_idss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_fll_idss_resize(structure->used + amount, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_fll_idss_increase_by_

#ifndef _di_f_fll_idss_resize_
  f_status_t f_fll_idss_resize(const f_number_unsigned_t length, f_fll_idss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_idss_resize(length, structure);
  }
#endif // _di_f_fll_idss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

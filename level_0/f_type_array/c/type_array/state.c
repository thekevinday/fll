#include "../type_array.h"
#include "state.h"
#include "private-state.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_states_adjust_
  f_status_t f_states_adjust(const f_number_unsigned_t length, f_states_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_state_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_states_adjust_

#ifndef _di_f_states_append_
  f_status_t f_states_append(const f_state_t source, f_states_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_states_append(source, destination);
  }
#endif // _di_f_states_append_

#ifndef _di_f_states_append_all_
  f_status_t f_states_append_all(const f_states_t source, f_states_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_states_append_all(source, destination);
  }
#endif // _di_f_states_append_all_

#ifndef _di_f_states_decimate_by_
  f_status_t f_states_decimate_by(const f_number_unsigned_t amount, f_states_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_state_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_states_decimate_by_

#ifndef _di_f_states_decrease_by_
  f_status_t f_states_decrease_by(const f_number_unsigned_t amount, f_states_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_state_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_states_decrease_by_

#ifndef _di_f_states_increase_
  f_status_t f_states_increase(const f_number_unsigned_t step, f_states_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_state_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_states_increase_

#ifndef _di_f_states_increase_by_
  f_status_t f_states_increase_by(const f_number_unsigned_t amount, f_states_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_state_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_states_increase_by_

#ifndef _di_f_states_resize_
  f_status_t f_states_resize(const f_number_unsigned_t length, f_states_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_state_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_states_resize_

#ifndef _di_f_statess_adjust_
  f_status_t f_statess_adjust(const f_number_unsigned_t length, f_statess_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statess_adjust(length, structure);
  }
#endif // _di_f_statess_adjust_

#ifndef _di_f_statess_append_
  f_status_t f_statess_append(const f_states_t source, f_statess_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_states_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_states_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_statess_append_

#ifndef _di_f_statess_append_all_
  f_status_t f_statess_append_all(const f_statess_t source, f_statess_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_states_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_states_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_statess_append_all_

#ifndef _di_f_statess_decimate_by_
  f_status_t f_statess_decimate_by(const f_number_unsigned_t amount, f_statess_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_statess_adjust((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_statess_decimate_by_

#ifndef _di_f_statess_decrease_by_
  f_status_t f_statess_decrease_by(const f_number_unsigned_t amount, f_statess_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_statess_resize((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_statess_decrease_by_

#ifndef _di_f_statess_increase_
  f_status_t f_statess_increase(const f_number_unsigned_t step, f_statess_t * const structure) {
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

      return private_f_statess_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_statess_increase_

#ifndef _di_f_statess_increase_by_
  f_status_t f_statess_increase_by(const f_number_unsigned_t amount, f_statess_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_statess_resize(structure->used + amount, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_statess_increase_by_

#ifndef _di_f_statess_resize_
  f_status_t f_statess_resize(const f_number_unsigned_t length, f_statess_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statess_resize(length, structure);
  }
#endif // _di_f_statess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

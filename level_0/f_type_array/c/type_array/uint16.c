#include "../type_array.h"
#include "uint16.h"
#include "private-uint16.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint16s_adjust_
  f_status_t f_uint16s_adjust(const f_number_unsigned_t length, f_uint16s_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(uint16_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_uint16s_adjust_

#ifndef _di_f_uint16s_append_
  f_status_t f_uint16s_append(const uint16_t source, f_uint16s_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16s_append(source, destination);
  }
#endif // _di_f_uint16s_append_

#ifndef _di_f_uint16s_append_all_
  f_status_t f_uint16s_append_all(const f_uint16s_t source, f_uint16s_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint16s_append_all(source, destination);
  }
#endif // _di_f_uint16s_append_all_

#ifndef _di_f_uint16s_decimate_by_
  f_status_t f_uint16s_decimate_by(const f_number_unsigned_t amount, f_uint16s_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(uint16_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_uint16s_decimate_by_

#ifndef _di_f_uint16s_decrease_by_
  f_status_t f_uint16s_decrease_by(const f_number_unsigned_t amount, f_uint16s_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(uint16_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_uint16s_decrease_by_

#ifndef _di_f_uint16s_increase_
  f_status_t f_uint16s_increase(const f_number_unsigned_t step, f_uint16s_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(uint16_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_uint16s_increase_

#ifndef _di_f_uint16s_increase_by_
  f_status_t f_uint16s_increase_by(const f_number_unsigned_t amount, f_uint16s_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(uint16_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_uint16s_increase_by_

#ifndef _di_f_uint16s_resize_
  f_status_t f_uint16s_resize(const f_number_unsigned_t length, f_uint16s_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(uint16_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_uint16s_resize_

#ifndef _di_f_uint16ss_adjust_
  f_status_t f_uint16ss_adjust(const f_number_unsigned_t length, f_uint16ss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16ss_adjust(length, structure);
  }
#endif // _di_f_uint16ss_adjust_

#ifndef _di_f_uint16ss_append_
  f_status_t f_uint16ss_append(const f_uint16s_t source, f_uint16ss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_uint16s_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_uint16s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_uint16ss_append_

#ifndef _di_f_uint16ss_append_all_
  f_status_t f_uint16ss_append_all(const f_uint16ss_t source, f_uint16ss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_uint16s_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_uint16s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_uint16ss_append_all_

#ifndef _di_f_uint16ss_decimate_by_
  f_status_t f_uint16ss_decimate_by(const f_number_unsigned_t amount, f_uint16ss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_uint16ss_adjust((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_uint16ss_decimate_by_

#ifndef _di_f_uint16ss_decrease_by_
  f_status_t f_uint16ss_decrease_by(const f_number_unsigned_t amount, f_uint16ss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_uint16ss_resize((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_uint16ss_decrease_by_

#ifndef _di_f_uint16ss_increase_
  f_status_t f_uint16ss_increase(const f_number_unsigned_t step, f_uint16ss_t * const structure) {
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

      return private_f_uint16ss_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_uint16ss_increase_

#ifndef _di_f_uint16ss_increase_by_
  f_status_t f_uint16ss_increase_by(const f_number_unsigned_t amount, f_uint16ss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_uint16ss_resize(structure->used + amount, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_uint16ss_increase_by_

#ifndef _di_f_uint16ss_resize_
  f_status_t f_uint16ss_resize(const f_number_unsigned_t length, f_uint16ss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16ss_resize(length, structure);
  }
#endif // _di_f_uint16ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

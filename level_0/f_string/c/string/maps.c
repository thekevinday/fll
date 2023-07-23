#include "../string.h"
#include "../private-string.h"
#include "private-maps.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_maps_adjust_
  f_status_t f_string_maps_adjust(const f_number_unsigned_t length, f_string_maps_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_maps_adjust(length, structure);
  }
#endif // _di_f_string_maps_adjust_

#ifndef _di_f_string_maps_append_
  f_status_t f_string_maps_append(const f_string_map_t source, f_string_maps_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_string_maps_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].name.used = 0;
    destination->array[destination->used].value.used = 0;

    if (source.name.used) {
      status = private_f_string_append(source.name.string, source.name.used, &destination->array[destination->used].name);
      if (F_status_is_error(status)) return status;
    }

    if (source.value.used) {
      status = private_f_string_append(source.value.string, source.value.used, &destination->array[destination->used].value);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // _di_f_string_maps_append_

#ifndef _di_f_string_maps_append_all_
  f_status_t f_string_maps_append_all(const f_string_maps_t source, f_string_maps_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_string_maps_append_all(source, destination);
  }
#endif // _di_f_string_maps_append_all_

#ifndef _di_f_string_maps_decimate_by_
  f_status_t f_string_maps_decimate_by(const f_number_unsigned_t amount, f_string_maps_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_string_maps_adjust((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_string_maps_decimate_by_

#ifndef _di_f_string_maps_decrease_by_
  f_status_t f_string_maps_decrease_by(const f_number_unsigned_t amount, f_string_maps_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_string_maps_resize((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_string_maps_decrease_by_

#ifndef _di_f_string_maps_increase_
  f_status_t f_string_maps_increase(const f_number_unsigned_t step, f_string_maps_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_string_maps_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_string_maps_increase_

#ifndef _di_f_string_maps_increase_by_
  f_status_t f_string_maps_increase_by(const f_number_unsigned_t amount, f_string_maps_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_string_maps_resize(length, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_string_maps_increase_by_

#ifndef _di_f_string_maps_resize_
  f_status_t f_string_maps_resize(const f_number_unsigned_t length, f_string_maps_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_maps_resize(length, structure);
  }
#endif // _di_f_string_maps_resize_

#ifdef __cplusplus
} // extern "C"
#endif

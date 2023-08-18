#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamic.h"
#include "private-dynamics.h"
#include "private-map_multis.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_map_multis_adjust_
  f_status_t f_utf_string_map_multis_adjust(const f_number_unsigned_t length, f_utf_string_map_multis_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_map_multis_adjust(length, structure);
  }
#endif // _di_f_utf_string_map_multis_adjust_

#ifndef _di_f_utf_string_map_multis_append_
  f_status_t f_utf_string_map_multis_append(const f_utf_string_map_multi_t source, f_utf_string_map_multis_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_okay;

    if (destination->used + 1 > destination->size) {
      status = private_f_utf_string_map_multis_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].name.used = 0;
    destination->array[destination->used].value.used = 0;

    if (source.name.used) {
      status = private_f_utf_string_append(source.name.string, source.name.used, &destination->array[destination->used].name);
      if (F_status_is_error(status)) return status;
    }

    if (source.value.used) {
      status = private_f_utf_string_dynamics_append_all(source.value, &destination->array[destination->used].value);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_utf_string_map_multis_append_

#ifndef _di_f_utf_string_map_multis_append_all_
  f_status_t f_utf_string_map_multis_append_all(const f_utf_string_map_multis_t source, f_utf_string_map_multis_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_map_multis_append_all(source, destination);
  }
#endif // _di_f_utf_string_map_multis_append_all_

#ifndef _di_f_utf_string_map_multis_decimate_by_
  f_status_t f_utf_string_map_multis_decimate_by(const f_number_unsigned_t amount, f_utf_string_map_multis_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_utf_string_map_multis_adjust((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_utf_string_map_multis_decimate_by_

#ifndef _di_f_utf_string_map_multis_decrease_by_
  f_status_t f_utf_string_map_multis_decrease_by(const f_number_unsigned_t amount, f_utf_string_map_multis_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_utf_string_map_multis_resize((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_utf_string_map_multis_decrease_by_

#ifndef _di_f_utf_string_map_multis_increase_
  f_status_t f_utf_string_map_multis_increase(const f_number_unsigned_t step, f_utf_string_map_multis_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_utf_string_map_multis_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_map_multis_increase_

#ifndef _di_f_utf_string_map_multis_increase_by_
  f_status_t f_utf_string_map_multis_increase_by(const f_number_unsigned_t amount, f_utf_string_map_multis_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_utf_string_map_multis_resize(length, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_map_multis_increase_by_

#ifndef _di_f_utf_string_map_multis_resize_
  f_status_t f_utf_string_map_multis_resize(const f_number_unsigned_t length, f_utf_string_map_multis_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_map_multis_resize(length, structure);
  }
#endif // _di_f_utf_string_map_multis_resize_

#ifdef __cplusplus
} // extern "C"
#endif

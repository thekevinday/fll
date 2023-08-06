#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-dynamics.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_dynamics_adjust(const f_number_unsigned_t length, f_string_dynamics_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &structure->array[i].string, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_dynamic_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)
  f_status_t private_f_string_dynamics_append(const f_string_dynamic_t source, f_string_dynamics_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_string_dynamics_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_string_append(source.string, source.used, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)

#if !defined(_di_f_string_dynamics_append_all_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)
  f_status_t private_f_string_dynamics_append_all(const f_string_dynamics_t source, f_string_dynamics_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_dynamics_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_string_append(source.array[i].string, source.array[i].used, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_dynamics_append_all_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)

#if !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_) || !defined(f_string_dynamics_resize) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_) || !defined(_di_f_string_map_multis_decrease_by_) || !defined(_di_f_string_map_multis_increase_) || !defined(_di_f_string_map_multis_increase_by_) || !defined(_di_f_string_map_multis_resize_) || !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multiss_append_all_) || !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)
  f_status_t private_f_string_dynamics_resize(const f_number_unsigned_t length, f_string_dynamics_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &structure->array[i].string, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_dynamic_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_) || !defined(f_string_dynamics_resize) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_) || !defined(_di_f_string_map_multis_decrease_by_) || !defined(_di_f_string_map_multis_increase_) || !defined(_di_f_string_map_multis_increase_by_) || !defined(_di_f_string_map_multis_resize_) || !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multiss_append_all_) || !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

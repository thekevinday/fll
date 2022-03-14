#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-map_multi.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_decimate_by_)
  f_status_t private_f_string_map_multis_adjust(const f_array_length_t length, f_string_map_multis_t * const map_multis) {

    if (map_multis->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < map_multis->size; ++i) {

      status = private_f_string_dynamic_adjust(0, &map_multis->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamics_adjust(0, &map_multis->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(map_multis->size, length, sizeof(f_string_map_multi_t), (void **) & map_multis->array);
    if (F_status_is_error(status)) return status;

    map_multis->size = length;

    if (map_multis->used > map_multis->size) {
      map_multis->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_decimate_by_)

#if !defined(_di_f_string_map_multis_append_all_) || !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multiss_append_all_)
  f_status_t private_f_string_map_multis_append_all(const f_string_map_multis_t source, f_string_map_multis_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_map_multis_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].name.used = 0;
      destination->array[destination->used].value.used = 0;

      if (source.array[i].name.used) {
        status = private_f_string_append(source.array[i].name.string, source.array[i].name.used, &destination->array[destination->used].name);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].value.used) {
        status = private_f_string_dynamics_append_all(source.array[i].value, &destination->array[destination->used].value);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_map_multis_append_all_) || !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multiss_append_all_)

#if !defined(_di_f_string_map_multis_decrease_by_) || !defined(_di_f_string_map_multis_increase_) || !defined(_di_f_string_map_multis_increase_by_) || !defined(_di_f_string_map_multis_terminate_) || !defined(_di_f_string_map_multis_terminate_after_)
  f_status_t private_f_string_map_multis_resize(const f_array_length_t length, f_string_map_multis_t * const map_multis) {

    if (map_multis->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < map_multis->size; ++i) {

      status = private_f_string_dynamic_resize(0, &map_multis->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamics_resize(0, &map_multis->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(map_multis->size, length, sizeof(f_string_map_multi_t), (void **) & map_multis->array);
    if (F_status_is_error(status)) return status;

    map_multis->size = length;

    if (map_multis->used > map_multis->size) {
      map_multis->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_map_multis_decrease_by_) || !defined(_di_f_string_map_multis_increase_) || !defined(_di_f_string_map_multis_increase_by_) || !defined(_di_f_string_map_multis_terminate_) || !defined(_di_f_string_map_multis_terminate_after_)

#if !defined(_di_f_string_map_multiss_adjust_) || !defined(_di_f_string_map_multiss_decimate_by_)
  f_status_t private_f_string_map_multiss_adjust(const f_array_length_t length, f_string_map_multiss_t * const map_multiss) {

    if (map_multiss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < map_multiss->size; ++i) {

      status = private_f_string_map_multis_adjust(0, &map_multiss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(map_multiss->size, length, sizeof(f_string_map_multis_t), (void **) & map_multiss->array);
    if (F_status_is_error(status)) return status;

    map_multiss->size = length;

    if (map_multiss->used > map_multiss->size) {
      map_multiss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_map_multiss_adjust_) || !defined(_di_f_string_map_multiss_decimate_by_)

#if !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_) || !defined(_di_f_string_map_multiss_terminate_) || !defined(_di_f_string_map_multiss_terminate_after_)
  f_status_t private_f_string_map_multiss_resize(const f_array_length_t length, f_string_map_multiss_t * const map_multiss) {

    if (map_multiss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < map_multiss->size; ++i) {

      status = private_f_string_map_multis_resize(0, &map_multiss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(map_multiss->size, length, sizeof(f_string_map_multis_t), (void **) & map_multiss->array);
    if (F_status_is_error(status)) return status;

    map_multiss->size = length;

    if (map_multiss->used > map_multiss->size) {
      map_multiss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_) || !defined(_di_f_string_map_multiss_terminate_) || !defined(_di_f_string_map_multiss_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

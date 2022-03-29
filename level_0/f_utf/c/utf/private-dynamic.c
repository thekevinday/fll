#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamic.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  f_status_t private_f_utf_string_dynamic_adjust(const f_array_length_t length, f_utf_string_dynamic_t * const dynamic) {

    const f_status_t status = f_memory_adjust(dynamic->size, length, sizeof(f_utf_char_t), (void **) & dynamic->string);
    if (F_status_is_error(status)) return status;

    dynamic->size = length;

    if (dynamic->used > dynamic->size) {
      dynamic->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)
  f_status_t private_f_utf_string_dynamic_increase_by(const f_array_length_t amount, f_utf_string_dynamic_t * const dynamic) {

    if (dynamic->used + amount > dynamic->size) {
      if (dynamic->used + amount > F_string_t_size_d) {
        return F_status_set_error(F_string_too_large);
      }

      return private_f_utf_string_dynamic_resize(dynamic->used + amount, dynamic);
    }

    return F_data_not;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)
  f_status_t private_f_utf_string_dynamic_resize(const f_array_length_t length, f_utf_string_dynamic_t * const dynamic) {

    const f_status_t status = f_memory_resize(dynamic->size, length, sizeof(f_utf_char_t), (void **) & dynamic->string);
    if (F_status_is_error(status)) return status;

    dynamic->size = length;

    if (dynamic->used > dynamic->size) {
      dynamic->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)

#if !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)
  f_status_t private_f_utf_string_dynamics_adjust(const f_array_length_t length, f_utf_string_dynamics_t * const dynamics) {

    if (dynamics->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamics->size; ++i) {

      status = private_f_utf_string_dynamic_adjust(0, &dynamics->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(dynamics->size, length, sizeof(f_utf_string_dynamic_t), (void **) & dynamics->array);
    if (F_status_is_error(status)) return status;

    dynamics->size = length;

    if (dynamics->used > dynamics->size) {
      dynamics->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)

#if !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)
  f_status_t private_f_utf_string_dynamics_append(const f_utf_string_dynamic_t source, f_utf_string_dynamics_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_utf_string_dynamics_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_utf_string_append(source.string, source.used, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)


#if !defined(_di_f_utf_string_dynamics_append_all_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)
  f_status_t private_f_utf_string_dynamics_append_all(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_utf_string_dynamics_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_utf_string_append(source.array[i].string, source.array[i].used, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamics_append_all_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)

#if !defined(_di_f_utf_string_dynamics_decrease_by_) || !defined(_di_f_utf_string_dynamics_increase_) || !defined(_di_f_utf_string_dynamics_increase_by_) || !defined(f_utf_string_map_multis_append)
  f_status_t private_f_utf_string_dynamics_resize(const f_array_length_t length, f_utf_string_dynamics_t * const dynamics) {

    if (dynamics->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamics->size; ++i) {

      status = private_f_utf_string_dynamic_resize(0, &dynamics->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(dynamics->size, length, sizeof(f_utf_string_dynamic_t), (void **) & dynamics->array);
    if (F_status_is_error(status)) return status;

    dynamics->size = length;

    if (dynamics->used > dynamics->size) {
      dynamics->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamics_decrease_by_) || !defined(_di_f_utf_string_dynamics_increase_) || !defined(_di_f_utf_string_dynamics_increase_by_) || !defined(f_utf_string_map_multis_append)

#if !defined(_di_f_utf_string_dynamicss_adjust_) || !defined(_di_f_utf_string_dynamicss_append_) || !defined(_di_f_utf_string_dynamicss_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)
  f_status_t private_f_utf_string_dynamicss_adjust(const f_array_length_t length, f_utf_string_dynamicss_t * const dynamicss) {

    if (dynamicss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamicss->size; ++i) {

      status = private_f_utf_string_dynamics_adjust(0, &dynamicss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(dynamicss->size, length, sizeof(f_utf_string_dynamics_t), (void **) & dynamicss->array);
    if (F_status_is_error(status)) return status;

    dynamicss->size = length;

    if (dynamicss->used > dynamicss->size) {
      dynamicss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamicss_adjust_) || !defined(_di_f_utf_string_dynamicss_append_) || !defined(_di_f_utf_string_dynamicss_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)

#if !defined(_di_f_utf_string_dynamicss_decrease_by_) || !defined(_di_f_utf_string_dynamicss_increase_) || !defined(_di_f_utf_string_dynamicss_increase_by_) || !defined(_di_f_utf_string_dynamicss_append_all_) || !defined(_di_f_utf_string_map_multis_append_all_)
  f_status_t private_f_utf_string_dynamicss_resize(const f_array_length_t length, f_utf_string_dynamicss_t * const dynamicss) {

    if (dynamicss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamicss->size; ++i) {

      status = private_f_utf_string_dynamics_resize(0, &dynamicss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(dynamicss->size, length, sizeof(f_utf_string_dynamics_t), (void **) & dynamicss->array);
    if (F_status_is_error(status)) return status;

    dynamicss->size = length;

    if (dynamicss->used > dynamicss->size) {
      dynamicss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamicss_decrease_by_) || !defined(_di_f_utf_string_dynamicss_increase_) || !defined(_di_f_utf_string_dynamicss_increase_by_) || !defined(_di_f_utf_string_dynamicss_append_all_) || !defined(_di_f_utf_string_map_multis_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

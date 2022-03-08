#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_mash_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_triples_append_)
  f_status_t private_f_string_append(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) {

    if (destination->used + length + 1 > destination->size) {
      const f_status_t status = private_f_string_dynamic_increase_by(length + 1, destination);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source, length);
    destination->used += length;
    destination->string[destination->used] = 0;

    return F_none;
  }
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_mash_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_triples_append_)

#if !defined(_di_f_string_append_assure_nulless_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_assure_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_string_dynamic_partial_append_nulless_) || !defined(_di_f_string_dynamic_partial_mash_nulless_) || !defined(_di_f_string_mash_nulless_)
  f_status_t private_f_string_append_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) {

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t size = 0;

    // Count all of the NULLs and subtract them from the total size.
    for (; i < length; ++i) {
      if (source[i]) ++size;
    } // for

    if (destination->used + size + 1 > destination->size) {
      status = private_f_string_dynamic_increase_by(size + 1, destination);
      if (F_status_is_error(status)) return status;
    }

    f_array_length_t first = 0;

    for (i = 0, size = 0; i < length; ++i) {

      if (source[i]) continue;

      if (i && i > first) {
        size = i - first;

        memcpy(destination->string + destination->used, source + first, size);
        destination->used += size;
      }

      while (i + 1 < length && !source[i + 1]) {
        ++i;
      } // while

      first = i + 1;
    } // for

    if (i > first) {
      size = i - first;

      memcpy(destination->string + destination->used, source + first, size);
      destination->used += size;
    }

    destination->string[destination->used] = 0;

    return F_none;
  }
#endif // !defined(_di_f_string_append_assure_nulless_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_assure_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_string_dynamic_partial_append_nulless_) || !defined(_di_f_string_dynamic_partial_mash_nulless_) || !defined(_di_f_string_mash_nulless_)

#if !defined(_di_f_string_dynamic_adjust_) || !defined(_di_f_string_dynamic_decimate_by_) || !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)
  f_status_t private_f_string_dynamic_adjust(const f_array_length_t length, f_string_dynamic_t * const dynamic) {

    f_status_t status = f_memory_adjust(dynamic->size, length, sizeof(unsigned char), (void **) & dynamic->string);

    if (F_status_is_error_not(status)) {
      dynamic->size = length;

      if (dynamic->used > dynamic->size) {
        dynamic->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_dynamic_adjust_) || !defined(_di_f_string_dynamic_decimate_by_) || !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)

#if !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)
  f_status_t private_f_string_dynamic_increase_by(const f_array_length_t amount, f_string_dynamic_t * const dynamic) {

    if (dynamic->used + amount > dynamic->size) {
      if (dynamic->used + amount > F_string_t_size_d) {
        return F_status_set_error(F_string_too_large);
      }

      return private_f_string_dynamic_resize(dynamic->used + amount, dynamic);
    }

    return F_data_not;
  }
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)

#if !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_increase_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamic_terminate_) || !defined(_di_f_string_dynamic_terminate_after_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)
  f_status_t private_f_string_dynamic_resize(const f_array_length_t length, f_string_dynamic_t * const dynamic) {

    const f_status_t status = f_memory_resize(dynamic->size, length, sizeof(unsigned char), (void **) & dynamic->string);

    if (F_status_is_error_not(status)) {
      dynamic->size = length;

      if (dynamic->used > dynamic->size) {
        dynamic->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_increase_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamic_terminate_) || !defined(_di_f_string_dynamic_terminate_after_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)

#if !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_dynamics_adjust(const f_array_length_t length, f_string_dynamics_t * const dynamics) {

    if (dynamics->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamics->size; ++i) {

      status = private_f_string_dynamic_adjust(0, &dynamics->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(dynamics->size, length, sizeof(f_string_dynamic_t), (void **) & dynamics->array);

    if (F_status_is_error_not(status)) {
      dynamics->size = length;

      if (dynamics->used > dynamics->size) {
        dynamics->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_dynamics_append(const f_string_dynamics_t source, f_string_dynamics_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_dynamics_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_string_append(source.array[i].string, source.array[i].used, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_)
  f_status_t private_f_string_dynamics_resize(const f_array_length_t length, f_string_dynamics_t * const dynamics) {

    if (dynamics->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamics->size; ++i) {

      status = private_f_string_dynamic_resize(0, &dynamics->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(dynamics->size, length, sizeof(f_string_dynamic_t), (void **) & dynamics->array);

    if (F_status_is_error_not(status)) {
      dynamics->size = length;

      if (dynamics->used > dynamics->size) {
        dynamics->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_)

#if !defined(_di_f_string_dynamicss_adjust_) || !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_dynamicss_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_dynamicss_adjust(const f_array_length_t length, f_string_dynamicss_t * const dynamicss) {

    if (dynamicss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamicss->size; ++i) {

      status = private_f_string_dynamics_adjust(0, &dynamicss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(dynamicss->size, length, sizeof(f_string_dynamics_t), (void **) & dynamicss->array);

    if (F_status_is_error_not(status)) {
      dynamicss->size = length;

      if (dynamicss->used > dynamicss->size) {
        dynamicss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_dynamicss_adjust_) || !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_dynamicss_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_dynamicss_append(const f_string_dynamicss_t source, f_string_dynamicss_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_dynamicss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_string_dynamics_append(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_dynamicss_decrease_by_) || !defined(_di_f_string_dynamicss_increase_) || !defined(_di_f_string_dynamicss_increase_by_)
  f_status_t private_f_string_dynamicss_resize(const f_array_length_t length, f_string_dynamicss_t * const dynamicss) {

    if (dynamicss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamicss->size; ++i) {

      status = private_f_string_dynamics_resize(0, &dynamicss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(dynamicss->size, length, sizeof(f_string_dynamics_t), (void **) & dynamicss->array);

    if (F_status_is_error_not(status)) {
      dynamicss->size = length;

      if (dynamicss->used > dynamicss->size) {
        dynamicss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_dynamicss_decrease_by_) || !defined(_di_f_string_dynamicss_increase_) || !defined(_di_f_string_dynamicss_increase_by_)

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

    if (F_status_is_error_not(status)) {
      map_multis->size = length;

      if (map_multis->used > map_multis->size) {
        map_multis->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_decimate_by_)

#if !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_map_multis_append(const f_string_map_multi_t source, f_string_map_multis_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_string_map_multis_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].name.used = 0;
    destination->array[destination->used].value.used = 0;

    if (source.name.used) {
      status = private_f_string_append(source.name.string, source.name.used, &destination->array[destination->used].name);
      if (F_status_is_error(status)) return status;
    }

    if (source.value.used) {
      status = private_f_string_dynamics_append(source.value, &destination->array[destination->used].value);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_map_multiss_append_all_) || !defined(_di_f_string_map_multis_append_all_)
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
        status = private_f_string_dynamics_append(source.array[i].value, &destination->array[destination->used].value);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_map_multiss_append_all_) || !defined(_di_f_string_map_multis_append_all_)

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

    if (F_status_is_error_not(status)) {
      map_multis->size = length;

      if (map_multis->used > map_multis->size) {
        map_multis->used = length;
      }
    }

    return status;
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

    if (F_status_is_error_not(status)) {
      map_multiss->size = length;

      if (map_multiss->used > map_multiss->size) {
        map_multiss->used = length;
      }
    }

    return status;
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

    if (F_status_is_error_not(status)) {
      map_multiss->size = length;

      if (map_multiss->used > map_multiss->size) {
        map_multiss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_) || !defined(_di_f_string_map_multiss_terminate_) || !defined(_di_f_string_map_multiss_terminate_after_)

#if !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)
  f_status_t private_f_string_maps_adjust(const f_array_length_t length, f_string_maps_t * const maps) {

    if (maps->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < maps->size; ++i) {

      status = private_f_string_dynamic_adjust(0, &maps->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_adjust(0, &maps->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(maps->size, length, sizeof(f_string_map_t), (void **) & maps->array);

    if (F_status_is_error_not(status)) {
      maps->size = length;

      if (maps->used > maps->size) {
        maps->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)

#if !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_maps_append_)
  f_status_t private_f_string_maps_append(const f_string_map_t source, f_string_maps_t * const destination) {

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
#endif // !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_maps_append_)

#if !defined(_di_f_string_mapss_append_all_) || !defined(_di_f_string_maps_append_all_)
  f_status_t private_f_string_maps_append_all(const f_string_maps_t source, f_string_maps_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_maps_resize(destination->used + source.used, destination);
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
        status = private_f_string_append(source.array[i].value.string, source.array[i].value.used, &destination->array[destination->used].value);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_mapss_append_all_) || !defined(_di_f_string_maps_append_all_)

#if !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_terminate_) || !defined(_di_f_string_maps_terminate_after_)
  f_status_t private_f_string_maps_resize(const f_array_length_t length, f_string_maps_t * const maps) {

    if (maps->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < maps->size; ++i) {

      status = private_f_string_dynamic_resize(0, &maps->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_resize(0, &maps->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(maps->size, length, sizeof(f_string_map_t), (void **) & maps->array);

    if (F_status_is_error_not(status)) {
      maps->size = length;

      if (maps->used > maps->size) {
        maps->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_terminate_) || !defined(_di_f_string_maps_terminate_after_)

#if !defined(_di_f_string_mapss_adjust_) || !defined(_di_f_string_mapss_decimate_by_)
  f_status_t private_f_string_mapss_adjust(const f_array_length_t length, f_string_mapss_t * const mapss) {

    if (mapss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < mapss->size; ++i) {

      status = private_f_string_maps_adjust(0, &mapss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(mapss->size, length, sizeof(f_string_maps_t), (void **) & mapss->array);

    if (F_status_is_error_not(status)) {
      mapss->size = length;

      if (mapss->used > mapss->size) {
        mapss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_mapss_adjust_) || !defined(_di_f_string_mapss_decimate_by_)

#if !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_) || !defined(_di_f_string_mapss_terminate_) || !defined(_di_f_string_mapss_terminate_after_)
  f_status_t private_f_string_mapss_resize(const f_array_length_t length, f_string_mapss_t * const mapss) {

    if (mapss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < mapss->size; ++i) {

      status = private_f_string_maps_resize(0, &mapss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(mapss->size, length, sizeof(f_string_maps_t), (void **) & mapss->array);

    if (F_status_is_error_not(status)) {
      mapss->size = length;

      if (mapss->used > mapss->size) {
        mapss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_) || !defined(_di_f_string_mapss_terminate_) || !defined(_di_f_string_mapss_terminate_after_)

#if !defined(_di_f_string_dynamic_mish_) || !defined(_di_f_string_dynamic_partial_mish_) || !defined(_di_f_string_dynamic_partial_prepend_assure_) || !defined(_di_f_string_dynamic_partial_prepend_) || !defined(_di_f_string_dynamic_prepend_assure_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_mish_) || !defined(_di_f_string_prepend_assure_) || !defined(_di_f_string_prepend_)
  f_status_t private_f_string_prepend(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) {

    if (destination->used + length > F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    if (destination->used + length > destination->size) {
      const f_status_t status = private_f_string_dynamic_increase_by(length, destination);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used) {
      memmove(destination->string + length, destination->string, destination->used);
      memcpy(destination->string, source, length);
    }
    else {
      memcpy(destination->string, source, length);
    }

    destination->used += length;
    return F_none;
  }
#endif // !defined(_di_f_string_dynamic_mish_) || !defined(_di_f_string_dynamic_partial_mish_) || !defined(_di_f_string_dynamic_partial_prepend_assure_) || !defined(_di_f_string_dynamic_partial_prepend_) || !defined(_di_f_string_dynamic_prepend_assure_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_mish_) || !defined(_di_f_string_prepend_assure_) || !defined(_di_f_string_prepend_)

#if !defined(_di_f_string_dynamic_mish_nulless_) || !defined(_di_f_string_dynamic_partial_mish_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_mish_nulless_) || !defined(_di_f_string_prepend_assure_nulless_) || !defined(_di_f_string_prepend_nulless_)
  f_status_t private_f_string_prepend_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) {

    if (destination->used + length > F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    f_array_length_t first = 0;
    f_array_length_t offset = 0;

    f_array_length_t size = 0;

    for (f_array_length_t i = 0; i <= length; ++i) {

      if (i == length) {
        if (i > first) {
          size = i - first;

          if (destination->used + size > destination->size) {
            status = private_f_string_dynamic_increase_by(size, destination);
            if (F_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
          memcpy(destination->string + offset, source + first, size);

          destination->used += size;
          offset += size;
        }

        break;
      }

      if (!source[i]) {
        if (i > 0) {
          if (i > first) {
            size = i - first;

            if (destination->used + size > destination->size) {
              status = private_f_string_dynamic_increase_by(size, destination);
              if (F_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
            memcpy(destination->string + offset, source + first, size);

            destination->used += size;
            offset += size;
          }
        }

        while (i + 1 < length && !source[i + 1]) {
          ++i;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_dynamic_mish_nulless_) || !defined(_di_f_string_dynamic_partial_mish_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_mish_nulless_) || !defined(_di_f_string_prepend_assure_nulless_) || !defined(_di_f_string_prepend_nulless_)

#if !defined(_di_f_string_quantitys_adjust_) || !defined(_di_f_string_quantitys_decimate_by_)
  f_status_t private_f_string_quantitys_adjust(const f_array_length_t length, f_string_quantitys_t * const quantitys) {

    if (quantitys->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_adjust(quantitys->size, length, sizeof(f_string_quantity_t), (void **) & quantitys->array);

    if (F_status_is_error_not(status)) {
      quantitys->size = length;

      if (quantitys->used > quantitys->size) {
        quantitys->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_quantitys_adjust_) || !defined(_di_f_string_quantitys_decimate_by_)

#if !defined(_di_f_string_quantitys_decrease_) || !defined(_di_f_string_quantitys_decrease_by_) || !defined(_di_f_string_quantitys_increase_) || !defined(_di_f_string_quantitys_increase_by_) || !defined(_di_f_string_quantitys_terminate_) || !defined(_di_f_string_quantitys_terminate_after_)
  f_status_t private_f_string_quantitys_resize(const f_array_length_t length, f_string_quantitys_t * const quantitys) {

    if (quantitys->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_resize(quantitys->size, length, sizeof(f_string_quantity_t), (void **) & quantitys->array);

    if (F_status_is_error_not(status)) {
      quantitys->size = length;

      if (quantitys->used > quantitys->size) {
        quantitys->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_quantitys_decrease_) || !defined(_di_f_string_quantitys_decrease_by_) || !defined(_di_f_string_quantitys_increase_) || !defined(_di_f_string_quantitys_increase_by_) || !defined(_di_f_string_quantitys_terminate_) || !defined(_di_f_string_quantitys_terminate_after_)

#if !defined(_di_f_string_quantityss_adjust_) || !defined(_di_f_string_quantityss_decimate_by_)
  f_status_t private_f_string_quantityss_adjust(const f_array_length_t length, f_string_quantityss_t * const quantityss) {

    if (quantityss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < quantityss->size; ++i) {

      status = private_f_string_quantitys_adjust(0, &quantityss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(quantityss->size, length, sizeof(f_string_quantitys_t), (void **) & quantityss->array);

    if (F_status_is_error_not(status)) {
      quantityss->size = length;

      if (quantityss->used > quantityss->size) {
        quantityss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_quantityss_adjust_) || !defined(_di_f_string_quantityss_decimate_by_)

#if !defined(_di_f_string_quantityss_decrease_) || !defined(_di_f_string_quantityss_decrease_by_) || !defined(_di_f_string_quantityss_increase_) || !defined(_di_f_string_quantityss_increase_by_) || !defined(_di_f_string_quantityss_terminate_) || !defined(_di_f_string_quantityss_terminate_after_)
  f_status_t private_f_string_quantityss_resize(const f_array_length_t length, f_string_quantityss_t * const quantityss) {

    if (quantityss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < quantityss->size; ++i) {

      status = private_f_string_quantitys_resize(0, &quantityss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(quantityss->size, length, sizeof(f_string_quantitys_t), (void **) & quantityss->array);

    if (F_status_is_error_not(status)) {
      quantityss->size = length;

      if (quantityss->used > quantityss->size) {
        quantityss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_quantityss_decrease_) || !defined(_di_f_string_quantityss_decrease_by_) || !defined(_di_f_string_quantityss_increase_) || !defined(_di_f_string_quantityss_increase_by_) || !defined(_di_f_string_quantityss_terminate_) || !defined(_di_f_string_quantityss_terminate_after_)

#if !defined(_di_f_string_ranges_adjust_) || !defined(_di_f_string_ranges_decimate_by_)
  f_status_t private_f_string_ranges_adjust(const f_array_length_t length, f_string_ranges_t * const ranges) {

    if (ranges->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_adjust(ranges->size, length, sizeof(f_string_range_t), (void **) & ranges->array);

    if (F_status_is_error_not(status)) {
      ranges->size = length;

      if (ranges->used > ranges->size) {
        ranges->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_ranges_adjust_) || !defined(_di_f_string_ranges_decimate_by_)

#if !defined(_di_f_string_ranges_decrease_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_terminate_) || !defined(_di_f_string_ranges_terminate_after_)
  f_status_t private_f_string_ranges_resize(const f_array_length_t length, f_string_ranges_t * const ranges) {

    if (ranges->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_resize(ranges->size, length, sizeof(f_string_range_t), (void **) & ranges->array);

    if (F_status_is_error_not(status)) {
      ranges->size = length;

      if (ranges->used > ranges->size) {
        ranges->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_ranges_decrease_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_terminate_) || !defined(_di_f_string_ranges_terminate_after_)

#if !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)
  f_status_t private_f_string_rangess_adjust(const f_array_length_t length, f_string_rangess_t * const rangess) {

    if (rangess->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < rangess->size; ++i) {

      status = private_f_string_ranges_adjust(0, &rangess->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(rangess->size, length, sizeof(f_string_ranges_t), (void **) & rangess->array);

    if (F_status_is_error_not(status)) {
      rangess->size = length;

      if (rangess->used > rangess->size) {
        rangess->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)

#if !defined(_di_f_string_rangess_decrease_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_) || !defined(_di_f_string_rangess_terminate_) || !defined(_di_f_string_rangess_terminate_after_)
  f_status_t private_f_string_rangess_resize(const f_array_length_t length, f_string_rangess_t * const rangess) {

    if (rangess->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < rangess->size; ++i) {

      status = private_f_string_ranges_resize(0, &rangess->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(rangess->size, length, sizeof(f_string_ranges_t), (void **) & rangess->array);

    if (F_status_is_error_not(status)) {
      rangess->size = length;

      if (rangess->used > rangess->size) {
        rangess->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_rangess_decrease_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_) || !defined(_di_f_string_rangess_terminate_) || !defined(_di_f_string_rangess_terminate_after_)

#if !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)
  f_status_t private_f_string_triples_adjust(const f_array_length_t length, f_string_triples_t * const triples) {

    if (triples->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < triples->size; ++i) {

      status = private_f_string_dynamic_adjust(0, &triples->array[i].a);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_adjust(0, &triples->array[i].b);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_adjust(0, &triples->array[i].c);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(triples->size, length, sizeof(f_string_triple_t), (void **) & triples->array);

    if (F_status_is_error_not(status)) {
      triples->size = length;

      if (triples->used > triples->size) {
        triples->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)

#if !defined(_di_f_string_triples_decrease_) || !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_) || !defined(_di_f_string_triples_terminate_) || !defined(_di_f_string_triples_terminate_after_)
  f_status_t private_f_string_triples_resize(const f_array_length_t length, f_string_triples_t * const triples) {

    if (triples->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < triples->size; ++i) {

      status = private_f_string_dynamic_resize(0, &triples->array[i].a);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_resize(0, &triples->array[i].b);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_resize(0, &triples->array[i].c);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(triples->size, length, sizeof(f_string_triple_t), (void **) & triples->array);

    if (F_status_is_error_not(status)) {
      triples->size = length;

      if (triples->used > triples->size) {
        triples->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_triples_decrease_) || !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_) || !defined(_di_f_string_triples_terminate_) || !defined(_di_f_string_triples_terminate_after_)

#if !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)
  f_status_t private_f_string_tripless_adjust(const f_array_length_t length, f_string_tripless_t * const tripless) {

    if (tripless->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < tripless->size; ++i) {

      status = private_f_string_triples_adjust(0, &tripless->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(tripless->size, length, sizeof(f_string_triples_t), (void **) & tripless->array);

    if (F_status_is_error_not(status)) {
      tripless->size = length;

      if (tripless->used > tripless->size) {
        tripless->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)

#if !defined(_di_f_string_tripless_decrease_) || !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_) || !defined(_di_f_string_tripless_terminate_) || !defined(_di_f_string_tripless_terminate_after_)
  f_status_t private_f_string_tripless_resize(const f_array_length_t length, f_string_tripless_t * const tripless) {

    if (tripless->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < tripless->size; ++i) {

      status = private_f_string_triples_resize(0, &tripless->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(tripless->size, length, sizeof(f_string_triples_t), (void **) & tripless->array);

    if (F_status_is_error_not(status)) {
      tripless->size = length;

      if (tripless->used > tripless->size) {
        tripless->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_string_tripless_decrease_) || !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_) || !defined(_di_f_string_tripless_terminate_) || !defined(_di_f_string_tripless_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

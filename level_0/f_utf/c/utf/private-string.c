#include "../utf.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_triples_append_)
  f_status_t private_f_utf_string_append(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_increase_by(length, destination);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source, length);
    destination->used = destination->used + length;

    return F_none;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_triples_append_)

#if !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_mash_nulless_)
  f_status_t private_f_utf_string_append_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t first = 0;
    f_array_length_t size = 0;

    for (; i < length; ++i) {

      if (source[i]) continue;

      if (i && i > first) {
        size = i - first;

        if (destination->used + size > destination->size) {
          status = private_f_utf_string_dynamic_increase_by(size, destination);
          if (F_status_is_error(status)) return status;
        }

        memcpy(destination->string + destination->used, source + first, size);
        destination->used = destination->used + size;
      }

      while (i + 1 < length && !source[i + 1]) {
        ++i;
      } // while

      first = i + 1;
    } // for

    if (i > first) {
      size = i - first;

      if (destination->used + size > destination->size) {
        status = private_f_utf_string_dynamic_increase_by(size, destination);
        if (F_status_is_error(status)) return status;
      }

      memcpy(destination->string + destination->used, source + first, size);
      destination->used = destination->used + size;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_mash_nulless_)

#if !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  f_status_t private_f_utf_string_dynamic_adjust(const f_array_length_t length, f_utf_string_dynamic_t *dynamic) {

    f_status_t status = f_memory_adjust(dynamic->size, length, sizeof(f_utf_string_t), (void **) & dynamic->string);

    if (F_status_is_error_not(status)) {
      dynamic->size = length;

      if (dynamic->used > dynamic->size) {
        dynamic->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)
  f_status_t private_f_utf_string_dynamic_increase_by(const f_array_length_t amount, f_utf_string_dynamic_t *dynamic) {

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
  f_status_t private_f_utf_string_dynamic_resize(const f_array_length_t length, f_utf_string_dynamic_t *dynamic) {

    const f_status_t status = f_memory_resize(dynamic->size, length, sizeof(f_utf_string_t), (void **) & dynamic->string);

    if (F_status_is_error_not(status)) {
      dynamic->size = length;

      if (dynamic->used > dynamic->size) {
        dynamic->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)

#if !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)
  f_status_t private_f_utf_string_dynamics_adjust(const f_array_length_t length, f_utf_string_dynamics_t *dynamics) {

    if (dynamics->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamics->size; ++i) {

      status = private_f_utf_string_dynamic_adjust(0, &dynamics->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(dynamics->size, length, sizeof(f_utf_string_dynamic_t), (void **) & dynamics->array);

    if (F_status_is_error_not(status)) {
      dynamics->size = length;

      if (dynamics->used > dynamics->size) {
        dynamics->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)

#if !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_)
  f_status_t private_f_utf_string_dynamics_append(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_utf_string_dynamics_adjust(destination->used + source.used, destination);
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
#endif // !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_)

#if !defined(_di_f_utf_string_dynamics_decrease_by_) || !defined(_di_f_utf_string_dynamics_increase_) || !defined(_di_f_utf_string_dynamics_increase_by_)
  f_status_t private_f_utf_string_dynamics_resize(const f_array_length_t length, f_utf_string_dynamics_t *dynamics) {

    if (dynamics->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamics->size; ++i) {
      status = private_f_utf_string_dynamic_resize(0, &dynamics->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(dynamics->size, length, sizeof(f_utf_string_dynamic_t), (void **) & dynamics->array);

    if (F_status_is_error_not(status)) {
      dynamics->size = length;

      if (dynamics->used > dynamics->size) {
        dynamics->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_dynamics_decrease_by_) || !defined(_di_f_utf_string_dynamics_increase_) || !defined(_di_f_utf_string_dynamics_increase_by_)

#if !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_decimate_by_)
  f_status_t private_f_utf_string_map_multis_adjust(const f_array_length_t length, f_utf_string_map_multis_t *map_multis) {

    if (map_multis->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < map_multis->size; ++i) {

      status = private_f_utf_string_dynamic_adjust(0, &map_multis->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamics_adjust(0, &map_multis->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(map_multis->size, length, sizeof(f_utf_string_map_multi_t), (void **) & map_multis->array);

    if (F_status_is_error_not(status)) {
      map_multis->size = length;

      if (map_multis->used > map_multis->size) {
        map_multis->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_decimate_by_)

#if !defined(_di_f_utf_string_map_multis_decrease_by_) || !defined(_di_f_utf_string_map_multis_increase_) || !defined(_di_f_utf_string_map_multis_increase_by_) || !defined(_di_f_utf_string_map_multis_terminate_) || !defined(_di_f_utf_string_map_multis_terminate_after_)
  f_status_t private_f_utf_string_map_multis_resize(const f_array_length_t length, f_utf_string_map_multis_t *map_multis) {

    if (map_multis->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < map_multis->size; ++i) {

      status = private_f_utf_string_dynamic_resize(0, &map_multis->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamics_resize(0, &map_multis->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(map_multis->size, length, sizeof(f_utf_string_map_multi_t), (void **) & map_multis->array);

    if (F_status_is_error_not(status)) {
      map_multis->size = length;

      if (map_multis->used > map_multis->size) {
        map_multis->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_map_multis_decrease_by_) || !defined(_di_f_utf_string_map_multis_increase_) || !defined(_di_f_utf_string_map_multis_increase_by_) || !defined(_di_f_utf_string_map_multis_terminate_) || !defined(_di_f_utf_string_map_multis_terminate_after_)

#if !defined(_di_f_utf_string_maps_adjust_) || !defined(_di_f_utf_string_maps_decimate_by_)
  f_status_t private_f_utf_string_maps_adjust(const f_array_length_t length, f_utf_string_maps_t *maps) {

    if (maps->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < maps->size; ++i) {

      status = private_f_utf_string_dynamic_adjust(0, &maps->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamic_adjust(0, &maps->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(maps->size, length, sizeof(f_utf_string_map_t), (void **) & maps->array);

    if (F_status_is_error_not(status)) {
      maps->size = length;

      if (maps->used > maps->size) {
        maps->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_maps_adjust_) || !defined(_di_f_utf_string_maps_decimate_by_)

#if !defined(_di_f_utf_string_maps_decrease_by_) || !defined(_di_f_utf_string_maps_increase_) || !defined(_di_f_utf_string_maps_increase_by_) || !defined(_di_f_utf_string_maps_terminate_) || !defined(_di_f_utf_string_maps_terminate_after_)
  f_status_t private_f_utf_string_maps_resize(const f_array_length_t length, f_utf_string_maps_t *maps) {

    if (maps->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < maps->size; ++i) {

      status = private_f_utf_string_dynamic_resize(0, &maps->array[i].name);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamic_resize(0, &maps->array[i].value);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(maps->size, length, sizeof(f_utf_string_map_t), (void **) & maps->array);

    if (F_status_is_error_not(status)) {
      maps->size = length;

      if (maps->used > maps->size) {
        maps->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_maps_decrease_by_) || !defined(_di_f_utf_string_maps_increase_) || !defined(_di_f_utf_string_maps_increase_by_) || !defined(_di_f_utf_string_maps_terminate_) || !defined(_di_f_utf_string_maps_terminate_after_)

#if !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_)
  f_status_t private_f_utf_string_prepend(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {

    if (destination->used + length > F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    if (destination->used + length > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_increase_by(length, destination);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used) {
      memmove(destination->string + length, destination->string, destination->used);
      memcpy(destination->string, source, length);
    }
    else {
      memcpy(destination->string, source, length);
    }

    destination->used = destination->used + length;
    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_)

#if !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_)
  f_status_t private_f_utf_string_prepend_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) {

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
            status = private_f_utf_string_dynamic_increase_by(size, destination);
            if (F_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
          memcpy(destination->string + offset, source + first, size);

          destination->used = destination->used + size;
          offset += size;
        }

        break;
      }

      if (!source[i]) {
        if (i > 0) {
          if (i > first) {
            size = i - first;

            if (destination->used + size > destination->size) {
              status = private_f_utf_string_dynamic_increase_by(size, destination);
              if (F_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
            memcpy(destination->string + offset, source + first, size);

            destination->used = destination->used + size;
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
#endif // !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_)

#if !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  f_status_t private_f_utf_string_triples_adjust(const f_array_length_t length, f_utf_string_triples_t *triples) {

    if (triples->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < triples->size; ++i) {

      status = private_f_utf_string_dynamic_adjust(0, &triples->array[i].a);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamic_adjust(0, &triples->array[i].b);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamic_adjust(0, &triples->array[i].c);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(triples->size, length, sizeof(f_utf_string_triple_t), (void **) & triples->array);

    if (F_status_is_error_not(status)) {
      triples->size = length;

      if (triples->used > triples->size) {
        triples->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

#if !defined(_di_f_utf_string_triples_decrease_) || !defined(_di_f_utf_string_triples_decrease_by_) || !defined(_di_f_utf_string_triples_increase_) || !defined(_di_f_utf_string_triples_increase_by_) || !defined(_di_f_utf_string_triples_terminate_) || !defined(_di_f_utf_string_triples_terminate_after_)
  f_status_t private_f_utf_string_triples_resize(const f_array_length_t length, f_utf_string_triples_t *triples) {

    if (triples->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < triples->size; ++i) {

      status = private_f_utf_string_dynamic_resize(0, &triples->array[i].a);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamic_resize(0, &triples->array[i].b);
      if (F_status_is_error(status)) return status;

      status = private_f_utf_string_dynamic_resize(0, &triples->array[i].c);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(triples->size, length, sizeof(f_utf_string_triple_t), (void **) & triples->array);

    if (F_status_is_error_not(status)) {
      triples->size = length;

      if (triples->used > triples->size) {
        triples->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_utf_string_triples_decrease_) || !defined(_di_f_utf_string_triples_decrease_by_) || !defined(_di_f_utf_string_triples_increase_) || !defined(_di_f_utf_string_triples_increase_by_) || !defined(_di_f_utf_string_triples_terminate_) || !defined(_di_f_utf_string_triples_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

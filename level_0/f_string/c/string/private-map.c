#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-map.h"

#ifdef __cplusplus
extern "C" {
#endif

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
    if (F_status_is_error(status)) return status;

    maps->size = length;

    if (maps->used > maps->size) {
      maps->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)

#if !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_)
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
#endif // !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_)

#if !defined(_di_f_string_maps_append_) || !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_resize_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_) || !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_)
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
    if (F_status_is_error(status)) return status;

    maps->size = length;

    if (maps->used > maps->size) {
      maps->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_maps_append_) || !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_resize_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_) || !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_)

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
    if (F_status_is_error(status)) return status;

    mapss->size = length;

    if (mapss->used > mapss->size) {
      mapss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_mapss_adjust_) || !defined(_di_f_string_mapss_decimate_by_)

#if !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_)
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
    if (F_status_is_error(status)) return status;

    mapss->size = length;

    if (mapss->used > mapss->size) {
      mapss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

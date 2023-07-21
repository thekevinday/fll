#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-maps.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)
  f_status_t private_f_string_maps_adjust(const f_number_unsigned_t length, f_string_maps_t * const maps) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < maps->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_string_t), (void **) &maps->array[i].name.string, &maps->array[i].name.used, &maps->array[i].name.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_string_t), (void **) &maps->array[i].value.string, &maps->array[i].value.used, &maps->array[i].value.size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_map_t), (void **) &maps->array, &maps->used, &maps->size);
  }
#endif // !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)

#if !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_)
  f_status_t private_f_string_maps_append_all(const f_string_maps_t source, f_string_maps_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_maps_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

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
  f_status_t private_f_string_maps_resize(const f_number_unsigned_t length, f_string_maps_t * const maps) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < maps->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_string_t), (void **) &maps->array[i].name.string, &maps->array[i].name.used, &maps->array[i].name.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_string_t), (void **) &maps->array[i].value.string, &maps->array[i].value.used, &maps->array[i].value.size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_map_t), (void **) &maps->array, &maps->used, &maps->size);
  }
#endif // !defined(_di_f_string_maps_append_) || !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_resize_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_) || !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

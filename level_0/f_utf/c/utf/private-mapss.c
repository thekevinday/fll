#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamic.h"
#include "private-maps.h"
#include "private-mapss.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_mapss_adjust_) || !defined(_di_f_utf_string_mapss_decimate_by_)
  f_status_t private_f_utf_string_mapss_adjust(const f_number_unsigned_t length, f_utf_string_mapss_t * const mapss) {

    if (mapss->used + length > F_number_t_size_unsigned_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < mapss->size; ++i) {

      status = private_f_utf_string_maps_adjust(0, &mapss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(mapss->size, length, sizeof(f_utf_string_maps_t), (void **) & mapss->array);
    if (F_status_is_error(status)) return status;

    mapss->size = length;

    if (mapss->used > mapss->size) {
      mapss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_mapss_adjust_) || !defined(_di_f_utf_string_mapss_decimate_by_)

#if !defined(_di_f_utf_string_mapss_decrease_by_) || !defined(_di_f_utf_string_mapss_increase_) || !defined(_di_f_utf_string_mapss_increase_by_)
  f_status_t private_f_utf_string_mapss_resize(const f_number_unsigned_t length, f_utf_string_mapss_t * const mapss) {

    if (mapss->used + length > F_number_t_size_unsigned_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < mapss->size; ++i) {

      status = private_f_utf_string_maps_resize(0, &mapss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(mapss->size, length, sizeof(f_utf_string_maps_t), (void **) & mapss->array);
    if (F_status_is_error(status)) return status;

    mapss->size = length;

    if (mapss->used > mapss->size) {
      mapss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_mapss_decrease_by_) || !defined(_di_f_utf_string_mapss_increase_) || !defined(_di_f_utf_string_mapss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

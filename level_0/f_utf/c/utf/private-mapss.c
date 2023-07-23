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
  f_status_t private_f_utf_string_mapss_adjust(const f_number_unsigned_t length, f_utf_string_mapss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_utf_string_maps_adjust(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_utf_string_maps_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_utf_string_mapss_adjust_) || !defined(_di_f_utf_string_mapss_decimate_by_)

#if !defined(_di_f_utf_string_mapss_decrease_by_) || !defined(_di_f_utf_string_mapss_increase_) || !defined(_di_f_utf_string_mapss_increase_by_)
  f_status_t private_f_utf_string_mapss_resize(const f_number_unsigned_t length, f_utf_string_mapss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_utf_string_maps_resize(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_utf_string_maps_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_utf_string_mapss_decrease_by_) || !defined(_di_f_utf_string_mapss_increase_) || !defined(_di_f_utf_string_mapss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

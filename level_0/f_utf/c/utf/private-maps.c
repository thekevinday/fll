#include "../utf.h"
#include "../private-utf.h"
#include "private-maps.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_maps_append_all_) || !defined(_di_f_utf_string_mapss_append_) || !defined(_di_f_utf_string_mapss_append_all_)
  f_status_t private_f_utf_string_maps_append_all(const f_utf_string_maps_t source, f_utf_string_maps_t * const destination) {

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_utf_string_map_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination->array[destination->used].key.used = 0;
        destination->array[destination->used].value.used = 0;

        if (source.array[i].key.used) {
          status = private_f_utf_string_append(source.array[i].key.string, source.array[i].key.used, &destination->array[destination->used].key);
          if (F_status_is_error(status)) return status;
        }

        if (source.array[i].value.used) {
          status = private_f_utf_string_append(source.array[i].value.string, source.array[i].value.used, &destination->array[destination->used].value);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // !defined(_di_f_utf_string_maps_append_all_) || !defined(_di_f_utf_string_mapss_append_) || !defined(_di_f_utf_string_mapss_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamics.h"
#include "private-map_multis.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_)
  f_status_t private_f_utf_string_map_multis_append_all(const f_utf_string_map_multis_t source, f_utf_string_map_multis_t * const destination) {

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_utf_string_map_multi_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination->array[destination->used].key.used = 0;
        destination->array[destination->used].value.used = 0;

        if (source.array[i].key.used) {
          status = private_f_utf_string_append(source.array[i].key.string, source.array[i].key.used, &destination->array[destination->used].key);
          if (F_status_is_error(status)) return status;
        }

        if (source.array[i].value.used) {
          status = private_f_utf_string_dynamics_append_all(source.array[i].value, &destination->array[destination->used].value);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

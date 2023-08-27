#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamics.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)
  f_status_t private_f_utf_string_dynamics_append(const f_utf_string_dynamic_t source, f_utf_string_dynamics_t * const destination) {

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_utf_string_dynamic_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      destination->array[destination->used].used = 0;

      if (source.used) {
        status = private_f_utf_string_append(source.string, source.used, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)

#if !defined(_di_f_utf_string_dynamics_append_all_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)
  f_status_t private_f_utf_string_dynamics_append_all(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t * const destination) {

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_utf_string_dynamic_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination->array[destination->used].used = 0;

        if (source.array[i].used) {
          status = private_f_utf_string_append(source.array[i].string, source.array[i].used, &destination->array[destination->used]);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // !defined(_di_f_utf_string_dynamics_append_all_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

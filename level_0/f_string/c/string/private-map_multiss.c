#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-dynamics.h"
#include "private-map_multis.h"
#include "private-map_multiss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_map_multiss_adjust_) || !defined(_di_f_string_map_multiss_decimate_by_)
  f_status_t private_f_string_map_multiss_adjust(const f_number_unsigned_t length, f_string_map_multiss_t * const map_multiss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < map_multiss->size; ++i) {

      status = private_f_string_map_multis_adjust(0, &map_multiss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_map_multis_t), (void **) &map_multiss->array, &map_multiss->used, &map_multiss->size);
  }
#endif // !defined(_di_f_string_map_multiss_adjust_) || !defined(_di_f_string_map_multiss_decimate_by_)

#if !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)
  f_status_t private_f_string_map_multiss_resize(const f_number_unsigned_t length, f_string_map_multiss_t * const map_multiss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < map_multiss->size; ++i) {

      status = private_f_string_map_multis_resize(0, &map_multiss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_map_multis_t), (void **) &map_multiss->array, &map_multiss->used, &map_multiss->size);
  }
#endif // !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

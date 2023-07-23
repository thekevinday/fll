#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamic.h"
#include "private-dynamics.h"
#include "private-dynamicss.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_dynamicss_adjust_) || !defined(_di_f_utf_string_dynamicss_append_) || !defined(_di_f_utf_string_dynamicss_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)
  f_status_t private_f_utf_string_dynamicss_adjust(const f_number_unsigned_t length, f_utf_string_dynamicss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_utf_string_dynamics_adjust(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_utf_string_dynamics_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_utf_string_dynamicss_adjust_) || !defined(_di_f_utf_string_dynamicss_append_) || !defined(_di_f_utf_string_dynamicss_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)

#if !defined(_di_f_utf_string_dynamicss_decrease_by_) || !defined(_di_f_utf_string_dynamicss_increase_) || !defined(_di_f_utf_string_dynamicss_increase_by_) || !defined(_di_f_utf_string_dynamicss_append_all_) || !defined(_di_f_utf_string_map_multis_append_all_)
  f_status_t private_f_utf_string_dynamicss_resize(const f_number_unsigned_t length, f_utf_string_dynamicss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_utf_string_dynamics_resize(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_utf_string_dynamics_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_utf_string_dynamicss_decrease_by_) || !defined(_di_f_utf_string_dynamicss_increase_) || !defined(_di_f_utf_string_dynamicss_increase_by_) || !defined(_di_f_utf_string_dynamicss_append_all_) || !defined(_di_f_utf_string_map_multis_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

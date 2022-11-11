#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-dynamics.h"
#include "private-dynamicss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_dynamicss_adjust_) || !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_dynamicss_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)
  f_status_t private_f_string_dynamicss_adjust(const f_array_length_t length, f_string_dynamicss_t * const dynamicss) {

    if (dynamicss->used + length > F_array_length_t_size_d) return F_status_set_error(F_array_too_large);

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamicss->size; ++i) {

      status = private_f_string_dynamics_adjust(0, &dynamicss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(dynamicss->size, length, sizeof(f_string_dynamics_t), (void **) & dynamicss->array);
    if (F_status_is_error(status)) return status;

    dynamicss->size = length;

    if (dynamicss->used > dynamicss->size) {
      dynamicss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_dynamicss_adjust_) || !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_dynamicss_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)

#if !defined(_di_f_string_dynamicss_decrease_by_) || !defined(_di_f_string_dynamicss_increase_) || !defined(_di_f_string_dynamicss_increase_by_) || !defined(_di_f_string_dynamicss_append_all_) || !defined(_di_f_string_map_multis_append_all_)
  f_status_t private_f_string_dynamicss_resize(const f_array_length_t length, f_string_dynamicss_t * const dynamicss) {

    if (dynamicss->used + length > F_array_length_t_size_d) return F_status_set_error(F_array_too_large);

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < dynamicss->size; ++i) {

      status = private_f_string_dynamics_resize(0, &dynamicss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(dynamicss->size, length, sizeof(f_string_dynamics_t), (void **) & dynamicss->array);
    if (F_status_is_error(status)) return status;

    dynamicss->size = length;

    if (dynamicss->used > dynamicss->size) {
      dynamicss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_dynamicss_decrease_by_) || !defined(_di_f_string_dynamicss_increase_) || !defined(_di_f_string_dynamicss_increase_by_) || !defined(_di_f_string_dynamicss_append_all_) || !defined(_di_f_string_map_multis_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

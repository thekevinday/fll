#include "../utf.h"
#include "../private-utf.h"
#include "private-dynamic.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  f_status_t private_f_utf_string_dynamic_adjust(const f_number_unsigned_t length, f_utf_string_dynamic_t * const dynamic) {

    const f_status_t status = f_memory_adjust(dynamic->size, length, sizeof(f_utf_char_t), (void **) & dynamic->string);
    if (F_status_is_error(status)) return status;

    dynamic->size = length;

    if (dynamic->used > dynamic->size) {
      dynamic->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_append_all_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_maps_append_all_) || !defined(_di_f_utf_string_mapss_append_) || !defined(_di_f_utf_string_mapss_append_all_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_) || !defined(_di_f_utf_string_triples_append_all_) || !defined(_di_f_utf_string_tripless_append_) || !defined(_di_f_utf_string_tripless_append_all_)
  f_status_t private_f_utf_string_dynamic_increase_by(const f_number_unsigned_t amount, f_utf_string_dynamic_t * const dynamic) {

    if (dynamic->used + amount > dynamic->size) {
      if (dynamic->used + amount > F_string_t_size_d) {
        return F_status_set_error(F_string_too_large);
      }

      return private_f_utf_string_dynamic_resize(dynamic->used + amount, dynamic);
    }

    return F_data_not;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_append_all_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_maps_append_all_) || !defined(_di_f_utf_string_mapss_append_) || !defined(_di_f_utf_string_mapss_append_all_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_) || !defined(_di_f_utf_string_triples_append_all_) || !defined(_di_f_utf_string_tripless_append_) || !defined(_di_f_utf_string_tripless_append_all_)

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decrease_by) || !defined(_di_f_utf_string_dynamics_increase) || !defined(_di_f_utf_string_dynamics_increase_by) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_decrease_by) || !defined(_di_f_utf_string_map_multis_increase) || !defined(_di_f_utf_string_map_multis_increase_by) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)
  f_status_t private_f_utf_string_dynamic_resize(const f_number_unsigned_t length, f_utf_string_dynamic_t * const dynamic) {

    const f_status_t status = f_memory_resize(dynamic->size, length, sizeof(f_utf_char_t), (void **) & dynamic->string);
    if (F_status_is_error(status)) return status;

    dynamic->size = length;

    if (dynamic->used > dynamic->size) {
      dynamic->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decrease_by) || !defined(_di_f_utf_string_dynamics_increase) || !defined(_di_f_utf_string_dynamics_increase_by) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_decrease_by) || !defined(_di_f_utf_string_map_multis_increase) || !defined(_di_f_utf_string_map_multis_increase_by) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)

#ifdef __cplusplus
} // extern "C"
#endif

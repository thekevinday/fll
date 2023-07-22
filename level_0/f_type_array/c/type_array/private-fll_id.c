#include "../type_array.h"
#include "private-fll_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_idss_append_)
  extern f_status_t private_f_fll_ids_append(const f_fll_id_t source, f_fll_ids_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_fll_id_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->array[destination->used].name, source.name, sizeof(char) * f_fll_id_name_length_d);

    destination->array[destination->used].type = source.type;
    destination->array[destination->used++].used = source.used;

    return F_none;
  }
#endif // !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_idss_append_)

#if !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_append_all_) || !defined(_di_f_fll_idss_append_all_)
  extern f_status_t private_f_fll_ids_append_all(const f_fll_ids_t source, f_fll_ids_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_fll_id_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      memcpy(destination->array[destination->used].name, source.array[i].name, sizeof(char) * f_fll_id_name_length_d);

      destination->array[destination->used].type = source.array[i].type;
      destination->array[destination->used++].used = source.array[i].used;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_append_all_) || !defined(_di_f_fll_idss_append_all_)

#if !defined(_di_f_fll_idss_adjust_) || !defined(_di_f_fll_idss_decimate_by_)
  f_status_t private_f_fll_idss_adjust(const f_number_unsigned_t length, f_fll_idss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_fll_id_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_fll_ids_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_fll_idss_adjust_) || !defined(_di_f_fll_idss_decimate_by_)

#if !defined(_di_f_fll_idss_decrease_by_) || !defined(_di_f_fll_idss_increase_) || !defined(_di_f_fll_idss_increase_by_) || !defined(_di_f_fll_idss_resize_)
  f_status_t private_f_fll_idss_resize(const f_number_unsigned_t length, f_fll_idss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_fll_id_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_fll_ids_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_fll_idss_decrease_by_) || !defined(_di_f_fll_idss_increase_) || !defined(_di_f_fll_idss_increase_by_) || !defined(_di_f_fll_idss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

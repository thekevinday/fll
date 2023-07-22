#include "../type_array.h"
#include "private-fll_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fll_ids_adjust_) || !defined(_di_f_fll_ids_decimate_by_)
  f_status_t private_f_fll_ids_adjust(const f_array_length_t length, f_fll_ids_t *ids) {

    const f_status_t status = f_memory_adjust(ids->size, length, sizeof(f_fll_id_t), (void **) & ids->array);
    if (F_status_is_error(status)) return status;

    ids->size = length;

    if (ids->used > ids->size) {
      ids->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fll_ids_adjust_) || !defined(_di_f_fll_ids_decimate_by_)

#if !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_idss_append_)
  extern f_status_t private_f_fll_ids_append(const f_fll_id_t source, f_fll_ids_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_fll_ids_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->array[destination->used].name, source.name, sizeof(char) * f_fll_id_name_length_d);

    destination->array[destination->used].type = source.type;
    destination->array[destination->used++].used = source.used;

    return F_none;
  }
#endif // !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_idss_append_)

#if !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_append_all_) || !defined(_di_f_fll_idss_append_all_)
  extern f_status_t private_f_fll_ids_append_all(const f_fll_ids_t source, f_fll_ids_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_fll_ids_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {

      memcpy(destination->array[destination->used].name, source.array[i].name, sizeof(char) * f_fll_id_name_length_d);

      destination->array[destination->used].type = source.array[i].type;
      destination->array[destination->used++].used = source.array[i].used;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_append_all_) || !defined(_di_f_fll_idss_append_all_)

#if !defined(_di_f_fll_ids_resize_) || !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_decrease_by_) || !defined(_di_f_fll_idss_append_)
  f_status_t private_f_fll_ids_resize(const f_array_length_t length, f_fll_ids_t *ids) {

    const f_status_t status = f_memory_resize(ids->size, length, sizeof(f_fll_id_t), (void **) & ids->array);
    if (F_status_is_error(status)) return status;

    ids->size = length;

    if (ids->used > ids->size) {
      ids->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fll_ids_resize_) || !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_decrease_by_) || !defined(_di_f_fll_idss_append_)

#if !defined(_di_f_fll_idss_adjust_) || !defined(_di_f_fll_idss_decimate_by_)
  f_status_t private_f_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *idss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < idss->size; ++i) {

      status = f_memory_destroy(idss->array[i].size, sizeof(f_fll_id_t), (void **) & idss->array[i].array);
      if (F_status_is_error(status)) return status;

      idss->array[i].size = 0;
      idss->array[i].used = 0;
    } // for

    status = f_memory_adjust(idss->size, length, sizeof(f_fll_ids_t), (void **) & idss->array);
    if (F_status_is_error(status)) return status;

    idss->size = length;

    if (idss->used > idss->size) {
      idss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fll_idss_adjust_) || !defined(_di_f_fll_idss_decimate_by_)

#if !defined(_di_f_fll_idss_decrease_by_) || !defined(_di_f_fll_idss_increase_) || !defined(_di_f_fll_idss_increase_by_) || !defined(_di_f_fll_idss_resize_)
  f_status_t private_f_fll_idss_resize(const f_array_length_t length, f_fll_idss_t *idss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < idss->size; ++i) {

      status = f_memory_delete(idss->array[i].size, sizeof(f_fll_id_t), (void **) & idss->array[i].array);
      if (F_status_is_error(status)) return status;

      idss->array[i].size = 0;
      idss->array[i].used = 0;
    } // for

    status = f_memory_resize(idss->size, length, sizeof(f_fll_ids_t), (void **) & idss->array);
    if (F_status_is_error(status)) return status;

    idss->size = length;

    if (idss->used > idss->size) {
      idss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fll_idss_decrease_by_) || !defined(_di_f_fll_idss_increase_) || !defined(_di_f_fll_idss_increase_by_) || !defined(_di_f_fll_idss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

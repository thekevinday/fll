#include "../limit.h"
#include "set.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_limit_sets_adjust_) || !defined(_di_f_limit_sets_decimate_by_)
  f_status_t private_f_limit_sets_adjust(const f_array_length_t length, f_limit_sets_t *sets) {

    const f_status_t status = f_memory_adjust(sets->size, length, sizeof(f_limit_set_t), (void **) & sets->array);
    if (F_status_is_error(status)) return status;

    sets->size = length;

    if (sets->used > sets->size) {
      sets->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_sets_adjust_) || !defined(_di_f_limit_sets_decimate_by_)

#if !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_setss_append_)
  extern f_status_t private_f_limit_sets_append(const f_limit_set_t source, f_limit_sets_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_limit_sets_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_setss_append_)

#if !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_sets_append_all_) || !defined(_di_f_limit_setss_append_all_)
  extern f_status_t private_f_limit_sets_append_all(const f_limit_sets_t source, f_limit_sets_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_limit_sets_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_sets_append_all_) || !defined(_di_f_limit_setss_append_all_)

#if !defined(_di_f_limit_sets_resize_) || !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_sets_decimate_by_) || !defined(_di_f_limit_setss_append_)
  f_status_t private_f_limit_sets_resize(const f_array_length_t length, f_limit_sets_t *sets) {

    const f_status_t status = f_memory_resize(sets->size, length, sizeof(f_limit_set_t), (void **) & sets->array);
    if (F_status_is_error(status)) return status;

    sets->size = length;

    if (sets->used > sets->size) {
      sets->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_sets_resize_) || !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_sets_decimate_by_) || !defined(_di_f_limit_setss_append_)

#if !defined(_di_f_limit_setss_adjust_) || !defined(_di_f_limit_setss_decimate_by_)
  f_status_t private_f_limit_setss_adjust(const f_array_length_t length, f_limit_setss_t *setss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < setss->size; ++i) {

      status = f_memory_destroy(setss->array[i].size, sizeof(f_limit_sets_t), (void **) & setss->array[i].array);
      if (F_status_is_error(status)) return status;

      setss->array[i].size = 0;
      setss->array[i].used = 0;
    } // for

    status = f_memory_adjust(setss->size, length, sizeof(f_limit_sets_t), (void **) & setss->array);
    if (F_status_is_error(status)) return status;

    setss->size = length;

    if (setss->used > setss->size) {
      setss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_setss_adjust_) || !defined(_di_f_limit_setss_decimate_by_)

#if !defined(_di_f_limit_setss_decrease_by_) || !defined(_di_f_limit_setss_increase_) || !defined(_di_f_limit_setss_increase_by_) || !defined(_di_f_limit_setss_resize_)
  f_status_t private_f_limit_setss_resize(const f_array_length_t length, f_limit_setss_t *setss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < setss->size; ++i) {

      status = f_memory_delete(setss->array[i].size, sizeof(f_limit_sets_t), (void **) & setss->array[i].array);
      if (F_status_is_error(status)) return status;

      setss->array[i].size = 0;
      setss->array[i].used = 0;
    } // for

    status = f_memory_resize(setss->size, length, sizeof(f_limit_sets_t), (void **) & setss->array);
    if (F_status_is_error(status)) return status;

    setss->size = length;

    if (setss->used > setss->size) {
      setss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_limit_setss_decrease_by_) || !defined(_di_f_limit_setss_increase_) || !defined(_di_f_limit_setss_increase_by_) || !defined(_di_f_limit_setss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../fss.h"
#include "private-item.h"
#include "private-nest.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)
  f_status_t private_f_fss_nest_adjust(const f_number_unsigned_t length, f_fss_nest_t * const nest) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < nest->size; ++i) {

      status = private_f_fss_items_adjust(0, &nest->depth[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(nest->size, length, sizeof(f_fss_items_t), (void **) & nest->depth);
    if (F_status_is_error(status)) return status;

    nest->size = length;

    if (nest->used > nest->size) {
      nest->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)

#if !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)
  f_status_t private_f_fss_nest_resize(const f_number_unsigned_t length, f_fss_nest_t * const nest) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < nest->size; ++i) {

      status = private_f_fss_items_resize(0, &nest->depth[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(nest->size, length, sizeof(f_fss_items_t), (void **) & nest->depth);
    if (F_status_is_error(status)) return status;

    nest->size = length;

    if (nest->used > nest->size) {
      nest->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)

#if !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)
  f_status_t private_f_fss_nests_adjust(const f_number_unsigned_t length, f_fss_nests_t *nests) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < nests->size; ++i) {

      status = private_f_fss_nest_adjust(0, &nests->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(nests->size, length, sizeof(f_fss_nest_t), (void **) & nests->array);
    if (F_status_is_error(status)) return status;

    nests->size = length;

    if (nests->used > nests->size) {
      nests->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)

#if !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)
  f_status_t private_f_fss_nests_resize(const f_number_unsigned_t length, f_fss_nests_t * const nests) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < nests->size; ++i) {

      status = private_f_fss_nest_resize(0, &nests->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(nests->size, length, sizeof(f_fss_nest_t), (void **) & nests->array);
    if (F_status_is_error(status)) return status;

    nests->size = length;

    if (nests->used > nests->size) {
      nests->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

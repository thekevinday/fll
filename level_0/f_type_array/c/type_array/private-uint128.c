#include "../type_array.h"
#include "private-uint128.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128ss_append_)
  extern f_status_t private_f_uint128s_append(const uint128_t source, f_uint128s_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(uint128_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128ss_append_)

#if !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_append_all_) || !defined(_di_f_uint128ss_append_all_)
  extern f_status_t private_f_uint128s_append_all(const f_uint128s_t source, f_uint128s_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(uint128_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_append_all_) || !defined(_di_f_uint128ss_append_all_)

#if !defined(_di_f_uint128ss_adjust_) || !defined(_di_f_uint128ss_decimate_by_)
  f_status_t private_f_uint128ss_adjust(const f_number_unsigned_t length, f_uint128ss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(uint128_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_uint128s_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_uint128ss_adjust_) || !defined(_di_f_uint128ss_decimate_by_)

#if !defined(_di_f_uint128ss_decrease_by_) || !defined(_di_f_uint128ss_increase_) || !defined(_di_f_uint128ss_increase_by_) || !defined(_di_f_uint128ss_resize_)
  f_status_t private_f_uint128ss_resize(const f_number_unsigned_t length, f_uint128ss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_resize(0, sizeof(uint128_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_uint128s_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_uint128ss_decrease_by_) || !defined(_di_f_uint128ss_increase_) || !defined(_di_f_uint128ss_increase_by_) || !defined(_di_f_uint128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

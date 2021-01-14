#include "type_array.h"
#include "private-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)
  f_status_t private_f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*cellss), f_cell_t, f_cells_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)

#if !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_)
  f_status_t private_f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*cellss), f_cell_t, f_cells_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_)

#if !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)
  f_status_t private_f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*array_lengthss), f_array_length_t, f_array_lengths_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)

#if !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_)
  f_status_t private_f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*array_lengthss), f_array_length_t, f_array_lengths_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_)

#if !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)
  f_status_t private_f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*int8ss), int8_t, f_int8s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)

#if !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_)
  f_status_t private_f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*int8ss), int8_t, f_int8s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_)

#if !defined(_di_f_type_uint8ss_adjust_) || !defined(_di_f_type_uint8ss_decimate_by_)
  f_status_t private_f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*uint8ss), uint8_t, f_uint8s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint8ss_adjust_) || !defined(_di_f_type_uint8ss_decimate_by_)

#if !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_)
  f_status_t private_f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*uint8ss), uint8_t, f_uint8s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_)

#if !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)
  f_status_t private_f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*int16ss), int16_t, f_int16s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)

#if !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_)
  f_status_t private_f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*int16ss), int16_t, f_int16s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_)

#if !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)
  f_status_t private_f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*uint16ss), uint16_t, f_uint16s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)

#if !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_)
  f_status_t private_f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*uint16ss), uint16_t, f_uint16s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_)

#if !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)
  f_status_t private_f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*int32ss), int32_t, f_int32s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)

#if !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_)
  f_status_t private_f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*int32ss), int32_t, f_int32s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_)

#if !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)
  f_status_t private_f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*uint32ss), uint32_t, f_uint32s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)

#if !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_)
  f_status_t private_f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*uint32ss), uint32_t, f_uint32s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_)

#if !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)
  f_status_t private_f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*int64ss), int64_t, f_int64s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)

#if !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_)
  f_status_t private_f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*int64ss), int64_t, f_int64s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_)

#if !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)
  f_status_t private_f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*uint64ss), uint64_t, f_uint64s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)

#if !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_)
  f_status_t private_f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*uint64ss), uint64_t, f_uint64s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_)

#if !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)
  f_status_t private_f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*int128ss), f_int128_t, f_int128s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)

#if !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_)
  f_status_t private_f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*int128ss), f_int128_t, f_int128s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_)

#if !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)
  f_status_t private_f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_adjust(status, (*uint128ss), f_uint128_t, f_uint128s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)

#if !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_)
  f_status_t private_f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    f_status_t status = F_none;

    f_macro_memory_structures_resize(status, (*uint128ss), f_uint128_t, f_uint128s_t, length, f_array_length_t)

    return status;
  }
#endif // !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

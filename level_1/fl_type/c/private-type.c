#include "type.h"
#include "private-type.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_type_cellss_delete_)
  void private_fl_type_cellss_delete(f_cellss_t *cellss) {
    f_macro_cellss_t_delete_simple((*cellss));
  }
#endif // !defined(_di_fl_type_cellss_delete_)

#if !defined(_di_fl_type_cellss_increase_) || !defined(_di_fl_type_cellss_increase_by_)
  f_status_t private_fl_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) {
    f_status_t status = F_none;

    f_macro_cellss_t_resize(status, (*cellss), length);

    return status;
  }
#endif // !defined(_di_fl_type_cellss_increase_) || !defined(_di_fl_type_cellss_increase_by_)

#if !defined(_di_fl_type_array_lengthss_delete_)
  void private_fl_type_array_lengthss_delete(f_array_lengthss_t *lengthss) {
    f_macro_array_lengthss_t_delete_simple((*lengthss));
  }
#endif // !defined(_di_fl_type_array_lengthss_delete_)

#if !defined(_di_fl_type_array_lengthss_increase_) || !defined(_di_fl_type_array_lengthss_increase_by_)
  f_status_t private_fl_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    f_status_t status = F_none;

    f_macro_array_lengthss_t_resize(status, (*array_lengthss), length);

    return status;
  }
#endif // !defined(_di_fl_type_array_lengthss_increase_) || !defined(_di_fl_type_array_lengthss_increase_by_)

#if !defined(_di_fl_type_int8ss_delete_)
  void private_fl_type_int8ss_delete(f_int8ss_t *int8ss) {
    f_macro_int8ss_t_delete_simple((*int8ss));
  }
#endif // !defined(_di_fl_type_int8ss_delete_)

#if !defined(_di_fl_type_int8ss_increase_) || !defined(_di_fl_type_int8ss_increase_by_)
  f_status_t private_fl_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) {
    f_status_t status = F_none;

    f_macro_int8ss_t_resize(status, (*int8ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_int8ss_increase_) || !defined(_di_fl_type_int8ss_increase_by_)

#if !defined(_di_fl_type_uint8ss_delete_)
  void private_fl_type_uint8ss_delete(f_uint8ss_t *uint8ss) {
    f_macro_uint8ss_t_delete_simple((*uint8ss));
  }
#endif // !defined(_di_fl_type_uint8ss_delete_)

#if !defined(_di_fl_type_uint8ss_increase_) || !defined(_di_fl_type_uint8ss_increase_by_)
  f_status_t private_fl_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    f_status_t status = F_none;

    f_macro_uint8ss_t_resize(status, (*uint8ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_uint8ss_increase_) || !defined(_di_fl_type_uint8ss_increase_by_)

#if !defined(_di_fl_type_int16ss_delete_)
  void private_fl_type_int16ss_delete(f_int16ss_t *int16ss) {
    f_macro_int16ss_t_delete_simple((*int16ss));
  }
#endif // !defined(_di_fl_type_int16ss_delete_)

#if !defined(_di_fl_type_int16ss_increase_) || !defined(_di_fl_type_int16ss_increase_by_)
  f_status_t private_fl_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) {
    f_status_t status = F_none;

    f_macro_int16ss_t_resize(status, (*int16ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_int16ss_increase_) || !defined(_di_fl_type_int16ss_increase_by_)

#if !defined(_di_fl_type_uint16ss_delete_)
  void private_fl_type_uint16ss_delete(f_uint16ss_t *uint16ss) {
    f_macro_uint16ss_t_delete_simple((*uint16ss));
  }
#endif // !defined(_di_fl_type_uint16ss_delete_)

#if !defined(_di_fl_type_uint16ss_increase_) || !defined(_di_fl_type_uint16ss_increase_by_)
  f_status_t private_fl_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    f_status_t status = F_none;

    f_macro_uint16ss_t_resize(status, (*uint16ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_uint16ss_increase_) || !defined(_di_fl_type_uint16ss_increase_by_)

#if !defined(_di_fl_type_int32ss_delete_)
  void private_fl_type_int32ss_delete(f_int32ss_t *int32ss) {
    f_macro_int32ss_t_delete_simple((*int32ss));
  }
#endif // !defined(_di_fl_type_int32ss_delete_)

#if !defined(_di_fl_type_int32ss_increase_) || !defined(_di_fl_type_int32ss_increase_by_)
  f_status_t private_fl_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) {
    f_status_t status = F_none;

    f_macro_int32ss_t_resize(status, (*int32ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_int32ss_increase_) || !defined(_di_fl_type_int32ss_increase_by_)

#if !defined(_di_fl_type_uint32ss_delete_)
  void private_fl_type_uint32ss_delete(f_uint32ss_t *uint32ss) {
    f_macro_uint32ss_t_delete_simple((*uint32ss));
  }
#endif // !defined(_di_fl_type_uint32ss_delete_)

#if !defined(_di_fl_type_uint32ss_increase_) || !defined(_di_fl_type_uint32ss_increase_by_)
  f_status_t private_fl_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    f_status_t status = F_none;

    f_macro_uint32ss_t_resize(status, (*uint32ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_uint32ss_increase_) || !defined(_di_fl_type_uint32ss_increase_by_)

#if !defined(_di_fl_type_int64ss_delete_)
  void private_fl_type_int64ss_delete(f_int64ss_t *int64ss) {
    f_macro_int64ss_t_delete_simple((*int64ss));
  }
#endif // !defined(_di_fl_type_int64ss_delete_)

#if !defined(_di_fl_type_int64ss_increase_) || !defined(_di_fl_type_int64ss_increase_by_)
  f_status_t private_fl_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) {
    f_status_t status = F_none;

    f_macro_int64ss_t_resize(status, (*int64ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_int64ss_increase_) || !defined(_di_fl_type_int64ss_increase_by_)

#if !defined(_di_fl_type_uint64ss_delete_)
  void private_fl_type_uint64ss_delete(f_uint64ss_t *uint64ss) {
    f_macro_uint64ss_t_delete_simple((*uint64ss));
  }
#endif // !defined(_di_fl_type_uint64ss_delete_)

#if !defined(_di_fl_type_uint64ss_increase_) || !defined(_di_fl_type_uint64ss_increase_by_)
  f_status_t private_fl_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    f_status_t status = F_none;

    f_macro_uint64ss_t_resize(status, (*uint64ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_uint64ss_increase_) || !defined(_di_fl_type_uint64ss_increase_by_)

#if !defined(_di_fl_type_int128ss_delete_)
  void private_fl_type_int128ss_delete(f_int128ss_t *int128ss) {
    f_macro_int128ss_t_delete_simple((*int128ss));
  }
#endif // !defined(_di_fl_type_int128ss_delete_)

#if !defined(_di_fl_type_int128ss_increase_) || !defined(_di_fl_type_int128ss_increase_by_)
  f_status_t private_fl_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) {
    f_status_t status = F_none;

    f_macro_int128ss_t_resize(status, (*int128ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_int128ss_increase_) || !defined(_di_fl_type_int128ss_increase_by_)

#if !defined(_di_fl_type_uint128ss_delete_)
  void private_fl_type_uint128ss_delete(f_uint128ss_t *uint128ss) {
    f_macro_uint128ss_t_delete_simple((*uint128ss));
  }
#endif // !defined(_di_fl_type_uint128ss_delete_)

#if !defined(_di_fl_type_uint128ss_increase_) || !defined(_di_fl_type_uint128ss_increase_by_)
  f_status_t private_fl_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    f_status_t status = F_none;

    f_macro_uint128ss_t_resize(status, (*uint128ss), length);

    return status;
  }
#endif // !defined(_di_fl_type_uint128ss_increase_) || !defined(_di_fl_type_uint128ss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

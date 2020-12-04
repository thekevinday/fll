/**
 * FLL - Level 1
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides type management functions.
 */
#ifndef _FL_type_h
#define _FL_type_h

// libc includes

// fll-0 includes
#include <level_0/type.h>
#include <level_0/type_array.h>
#include <level_0/status.h>
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Increase the size of cells array, but only if necessary.
 *
 * @param cells
 *   The cells array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_cells_increase_
  extern f_return_status fl_type_cells_increase(f_cells_t *cells) ;
#endif // _di_fl_type_cells_increase_

/**
 * Increase the size of cells array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param cells
 *   The cells array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_cells_increase_by_
  extern f_return_status fl_type_cells_increase_by(const f_array_length_t amount, f_cells_t *cells);
#endif // _di_fl_type_cells_increase_by_

/**
 * Increase the size of cells array, but only if necessary.
 *
 * @param cells
 *   The cells array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_cellss_increase_
  extern f_return_status fl_type_cellss_increase(f_cellss_t *cellss);
#endif // _di_fl_type_cellss_increase_

/**
 * Increase the size of cellss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param cellss
 *   The cellss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_cellss_increase_by_
  extern f_return_status fl_type_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss);
#endif // _di_fl_type_cellss_increase_by_

/**
 * Increase the size of array_lengths array, but only if necessary.
 *
 * @param array_lengths
 *   The array_lengths array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_array_lengths_increase_
  extern f_return_status fl_type_array_lengths_increase(f_array_lengths_t *array_lengths) ;
#endif // _di_fl_type_array_lengths_increase_

/**
 * Increase the size of array_lengths array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param array_lengths
 *   The array_lengths array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_array_lengths_increase_by_
  extern f_return_status fl_type_array_lengths_increase_by(const f_array_length_t amount, f_array_lengths_t *array_lengths);
#endif // _di_fl_type_array_lengths_increase_by_

/**
 * Increase the size of array_lengths array, but only if necessary.
 *
 * @param array_lengths
 *   The array_lengths array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_array_lengthss_increase_
  extern f_return_status fl_type_array_lengthss_increase(f_array_lengthss_t *array_lengthss);
#endif // _di_fl_type_array_lengthss_increase_

/**
 * Increase the size of array_lengthss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param array_lengthss
 *   The array_lengthss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_array_lengthss_increase_by_
  extern f_return_status fl_type_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss);
#endif // _di_fl_type_array_lengthss_increase_by_

/**
 * Increase the size of int8s array, but only if necessary.
 *
 * @param int8s
 *   The int8s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int8s_increase_
  extern f_return_status fl_type_int8s_increase(f_int8s_t *int8s) ;
#endif // _di_fl_type_int8s_increase_

/**
 * Increase the size of int8s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int8s
 *   The int8s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int8s_increase_by_
  extern f_return_status fl_type_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s);
#endif // _di_fl_type_int8s_increase_by_

/**
 * Increase the size of int8s array, but only if necessary.
 *
 * @param int8s
 *   The int8s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int8ss_increase_
  extern f_return_status fl_type_int8ss_increase(f_int8ss_t *int8ss);
#endif // _di_fl_type_int8ss_increase_

/**
 * Increase the size of int8ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int8ss
 *   The int8ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int8ss_increase_by_
  extern f_return_status fl_type_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss);
#endif // _di_fl_type_int8ss_increase_by_

/**
 * Increase the size of uint8s array, but only if necessary.
 *
 * @param uint8s
 *   The uint8s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint8s_increase_
  extern f_return_status fl_type_uint8s_increase(f_uint8s_t *uint8s) ;
#endif // _di_fl_type_uint8s_increase_

/**
 * Increase the size of uint8s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint8s
 *   The uint8s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint8s_increase_by_
  extern f_return_status fl_type_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s);
#endif // _di_fl_type_uint8s_increase_by_

/**
 * Increase the size of uint8s array, but only if necessary.
 *
 * @param uint8s
 *   The uint8s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint8ss_increase_
  extern f_return_status fl_type_uint8ss_increase(f_uint8ss_t *uint8ss);
#endif // _di_fl_type_uint8ss_increase_

/**
 * Increase the size of uint8ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint8ss
 *   The uint8ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint8ss_increase_by_
  extern f_return_status fl_type_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss);
#endif // _di_fl_type_uint8ss_increase_by_

/**
 * Increase the size of int16s array, but only if necessary.
 *
 * @param int16s
 *   The int16s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int16s_increase_
  extern f_return_status fl_type_int16s_increase(f_int16s_t *int16s) ;
#endif // _di_fl_type_int16s_increase_

/**
 * Increase the size of int16s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int16s
 *   The int16s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int16s_increase_by_
  extern f_return_status fl_type_int16s_increase_by(const f_array_length_t amount, f_int16s_t *int16s);
#endif // _di_fl_type_int16s_increase_by_

/**
 * Increase the size of int16s array, but only if necessary.
 *
 * @param int16s
 *   The int16s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int16ss_increase_
  extern f_return_status fl_type_int16ss_increase(f_int16ss_t *int16ss);
#endif // _di_fl_type_int16ss_increase_

/**
 * Increase the size of int16ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int16ss
 *   The int16ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int16ss_increase_by_
  extern f_return_status fl_type_int16ss_increase_by(const f_array_length_t amount, f_int16ss_t *int16ss);
#endif // _di_fl_type_int16ss_increase_by_

/**
 * Increase the size of uint16s array, but only if necessary.
 *
 * @param uint16s
 *   The uint16s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint16s_increase_
  extern f_return_status fl_type_uint16s_increase(f_uint16s_t *uint16s) ;
#endif // _di_fl_type_uint16s_increase_

/**
 * Increase the size of uint16s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint16s
 *   The uint16s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint16s_increase_by_
  extern f_return_status fl_type_uint16s_increase_by(const f_array_length_t amount, f_uint16s_t *uint16s);
#endif // _di_fl_type_uint16s_increase_by_

/**
 * Increase the size of uint16s array, but only if necessary.
 *
 * @param uint16s
 *   The uint16s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint16ss_increase_
  extern f_return_status fl_type_uint16ss_increase(f_uint16ss_t *uint16ss);
#endif // _di_fl_type_uint16ss_increase_

/**
 * Increase the size of uint16ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint16ss
 *   The uint16ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint16ss_increase_by_
  extern f_return_status fl_type_uint16ss_increase_by(const f_array_length_t amount, f_uint16ss_t *uint16ss);
#endif // _di_fl_type_uint16ss_increase_by_

/**
 * Increase the size of int32s array, but only if necessary.
 *
 * @param int32s
 *   The int32s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int32s_increase_
  extern f_return_status fl_type_int32s_increase(f_int32s_t *int32s) ;
#endif // _di_fl_type_int32s_increase_

/**
 * Increase the size of int32s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int32s
 *   The int32s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int32s_increase_by_
  extern f_return_status fl_type_int32s_increase_by(const f_array_length_t amount, f_int32s_t *int32s);
#endif // _di_fl_type_int32s_increase_by_

/**
 * Increase the size of int32s array, but only if necessary.
 *
 * @param int32s
 *   The int32s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int32ss_increase_
  extern f_return_status fl_type_int32ss_increase(f_int32ss_t *int32ss);
#endif // _di_fl_type_int32ss_increase_

/**
 * Increase the size of int32ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int32ss
 *   The int32ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int32ss_increase_by_
  extern f_return_status fl_type_int32ss_increase_by(const f_array_length_t amount, f_int32ss_t *int32ss);
#endif // _di_fl_type_int32ss_increase_by_

/**
 * Increase the size of uint32s array, but only if necessary.
 *
 * @param uint32s
 *   The uint32s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint32s_increase_
  extern f_return_status fl_type_uint32s_increase(f_uint32s_t *uint32s) ;
#endif // _di_fl_type_uint32s_increase_

/**
 * Increase the size of uint32s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint32s
 *   The uint32s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint32s_increase_by_
  extern f_return_status fl_type_uint32s_increase_by(const f_array_length_t amount, f_uint32s_t *uint32s);
#endif // _di_fl_type_uint32s_increase_by_

/**
 * Increase the size of uint32s array, but only if necessary.
 *
 * @param uint32s
 *   The uint32s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint32ss_increase_
  extern f_return_status fl_type_uint32ss_increase(f_uint32ss_t *uint32ss);
#endif // _di_fl_type_uint32ss_increase_

/**
 * Increase the size of uint32ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint32ss
 *   The uint32ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint32ss_increase_by_
  extern f_return_status fl_type_uint32ss_increase_by(const f_array_length_t amount, f_uint32ss_t *uint32ss);
#endif // _di_fl_type_uint32ss_increase_by_

/**
 * Increase the size of int64s array, but only if necessary.
 *
 * @param int64s
 *   The int64s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_int64s_increase_
  extern f_return_status fl_int64s_increase(f_int64s_t *int64s) ;
#endif // _di_fl_int64s_increase_

/**
 * Increase the size of int64s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int64s
 *   The int64s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_int64s_increase_by_
  extern f_return_status fl_int64s_increase_by(const f_array_length_t amount, f_int64s_t *int64s);
#endif // _di_fl_int64s_increase_by_

/**
 * Increase the size of int64s array, but only if necessary.
 *
 * @param int64s
 *   The int64s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_int64ss_increase_
  extern f_return_status fl_int64ss_increase(f_int64ss_t *int64ss);
#endif // _di_fl_int64ss_increase_

/**
 * Increase the size of int64ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int64ss
 *   The int64ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_int64ss_increase_by_
  extern f_return_status fl_int64ss_increase_by(const f_array_length_t amount, f_int64ss_t *int64ss);
#endif // _di_fl_int64ss_increase_by_

/**
 * Increase the size of uint64s array, but only if necessary.
 *
 * @param uint64s
 *   The uint64s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_uint64s_increase_
  extern f_return_status fl_uint64s_increase(f_uint64s_t *uint64s) ;
#endif // _di_fl_uint64s_increase_

/**
 * Increase the size of uint64s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint64s
 *   The uint64s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_uint64s_increase_by_
  extern f_return_status fl_uint64s_increase_by(const f_array_length_t amount, f_uint64s_t *uint64s);
#endif // _di_fl_uint64s_increase_by_

/**
 * Increase the size of uint64s array, but only if necessary.
 *
 * @param uint64s
 *   The uint64s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_uint64ss_increase_
  extern f_return_status fl_uint64ss_increase(f_uint64ss_t *uint64ss);
#endif // _di_fl_uint64ss_increase_

/**
 * Increase the size of uint64ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint64ss
 *   The uint64ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_uint64ss_increase_by_
  extern f_return_status fl_uint64ss_increase_by(const f_array_length_t amount, f_uint64ss_t *uint64ss);
#endif // _di_fl_uint64ss_increase_by_

/**
 * Increase the size of int128s array, but only if necessary.
 *
 * @param int128s
 *   The int128s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int128s_increase_
  extern f_return_status fl_type_int128s_increase(f_int128s_t *int128s) ;
#endif // _di_fl_type_int128s_increase_

/**
 * Increase the size of int128s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int128s
 *   The int128s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int128s_increase_by_
  extern f_return_status fl_type_int128s_increase_by(const f_array_length_t amount, f_int128s_t *int128s);
#endif // _di_fl_type_int128s_increase_by_

/**
 * Increase the size of int128s array, but only if necessary.
 *
 * @param int128s
 *   The int128s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int128ss_increase_
  extern f_return_status fl_type_int128ss_increase(f_int128ss_t *int128ss);
#endif // _di_fl_type_int128ss_increase_

/**
 * Increase the size of int128ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param int128ss
 *   The int128ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_int128ss_increase_by_
  extern f_return_status fl_type_int128ss_increase_by(const f_array_length_t amount, f_int128ss_t *int128ss);
#endif // _di_fl_type_int128ss_increase_by_

/**
 * Increase the size of uint128s array, but only if necessary.
 *
 * @param uint128s
 *   The uint128s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint128s_increase_
  extern f_return_status fl_type_uint128s_increase(f_uint128s_t *uint128s) ;
#endif // _di_fl_type_uint128s_increase_

/**
 * Increase the size of uint128s array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint128s
 *   The uint128s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint128s_increase_by_
  extern f_return_status fl_type_uint128s_increase_by(const f_array_length_t amount, f_uint128s_t *uint128s);
#endif // _di_fl_type_uint128s_increase_by_

/**
 * Increase the size of uint128s array, but only if necessary.
 *
 * @param uint128s
 *   The uint128s array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint128ss_increase_
  extern f_return_status fl_type_uint128ss_increase(f_uint128ss_t *uint128ss);
#endif // _di_fl_type_uint128ss_increase_

/**
 * Increase the size of uint128ss array by the given amount, but only if necessary.
 *
 * @param amount
 *   The amount to increase by.
 * @param uint128ss
 *   The uint128ss array to increase.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 */
#ifndef _di_fl_type_uint128ss_increase_by_
  extern f_return_status fl_type_uint128ss_increase_by(const f_array_length_t amount, f_uint128ss_t *uint128ss);
#endif // _di_fl_type_uint128ss_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_type_h

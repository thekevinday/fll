/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_uint128_h
#define _PRIVATE_F_type_array_uint128_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the uint128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128s
 *   The uint128s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_uint128s_adjust()
 * @see f_uint128s_decimate_by()
 */
#if !defined(_di_f_uint128s_adjust_) || !defined(_di_f_uint128s_decimate_by_)
  extern f_status_t private_f_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint128s_adjust_) || !defined(_di_f_uint128s_decimate_by_)

/**
 * Private implementation for appending the uint128 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint128 to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_uint128s_append()
 * @see f_uint128ss_append()
 */
#if !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128ss_append_)
  extern f_status_t private_f_uint128s_append(const uint128_t source, f_uint128s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128ss_append_)

/**
 * Private implementation for appending the uint128 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint128s to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_uint128s_append_all()
 * @see f_uint128ss_append()
 * @see f_uint128ss_append_all()
 */
#if !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_append_all_) || !defined(_di_f_uint128ss_append_all_)
  extern f_status_t private_f_uint128s_append_all(const f_uint128s_t source, f_uint128s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_append_all_) || !defined(_di_f_uint128ss_append_all_)

/**
 * Private implementation for resizing the uint128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128s
 *   The uint128s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_uint128s_resize()
 * @see f_uint128s_append()
 * @see f_uint128s_decimate_by()
 * @see f_uint128ss_append()
 */
#if !defined(_di_f_uint128s_resize_) || !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_decimate_by_) || !defined(_di_f_uint128ss_append_)
  extern f_status_t private_f_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint128s_resize_) || !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_decimate_by_) || !defined(_di_f_uint128ss_append_)

/**
 * Private implementation for resizing the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128ss
 *   The uint128ss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 *
 * @see f_uint128ss_adjust()
 * @see f_uint128ss_decimate_by()
 */
#if !defined(_di_f_uint128ss_adjust_) || !defined(_di_f_uint128ss_decimate_by_)
  extern f_status_t private_f_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint128ss_adjust_) || !defined(_di_f_uint128ss_decimate_by_)

/**
 * Private implementation for resizing the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint128ss
 *   The uint128ss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_uint128ss_decrease_by()
 * @see f_uint128ss_increase()
 * @see f_uint128ss_increase_by()
 * @see f_uint128ss_resize()
 */
#if !defined(_di_f_uint128ss_decrease_by_) || !defined(_di_f_uint128ss_increase_) || !defined(_di_f_uint128ss_increase_by_) || !defined(_di_f_uint128ss_resize_)
  extern f_status_t private_f_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint128ss_decrease_by_) || !defined(_di_f_uint128ss_increase_) || !defined(_di_f_uint128ss_increase_by_) || !defined(_di_f_uint128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_uint128_h

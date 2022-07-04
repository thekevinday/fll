/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_uint16_h
#define _PRIVATE_F_type_array_uint16_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the uint16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16s
 *   The uint16s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_uint16s_adjust()
 * @see f_uint16s_decimate_by()
 */
#if !defined(_di_f_uint16s_adjust_) || !defined(_di_f_uint16s_decimate_by_)
  extern f_status_t private_f_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint16s_adjust_) || !defined(_di_f_uint16s_decimate_by_)

/**
 * Private implementation for appending the uint16 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint16 to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_uint16s_append()
 * @see f_uint16ss_append()
 */
#if !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16ss_append_)
  extern f_status_t private_f_uint16s_append(const uint16_t source, f_uint16s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16ss_append_)

/**
 * Private implementation for appending the uint16 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint16s to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_uint16s_append_all()
 * @see f_uint16ss_append()
 * @see f_uint16ss_append_all()
 */
#if !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_append_all_) || !defined(_di_f_uint16ss_append_all_)
  extern f_status_t private_f_uint16s_append_all(const f_uint16s_t source, f_uint16s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_append_all_) || !defined(_di_f_uint16ss_append_all_)

/**
 * Private implementation for resizing the uint16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16s
 *   The uint16s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_uint16s_resize()
 * @see f_uint16s_append()
 * @see f_uint16s_decimate_by()
 * @see f_uint16ss_append()
 */
#if !defined(_di_f_uint16s_resize_) || !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_decimate_by_) || !defined(_di_f_uint16ss_append_)
  extern f_status_t private_f_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint16s_resize_) || !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_decimate_by_) || !defined(_di_f_uint16ss_append_)

/**
 * Private implementation for resizing the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16ss
 *   The uint16ss array to adjust.
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
 * @see f_uint16ss_adjust()
 * @see f_uint16ss_decimate_by()
 */
#if !defined(_di_f_uint16ss_adjust_) || !defined(_di_f_uint16ss_decimate_by_)
  extern f_status_t private_f_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint16ss_adjust_) || !defined(_di_f_uint16ss_decimate_by_)

/**
 * Private implementation for resizing the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint16ss
 *   The uint16ss array to resize.
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
 * @see f_uint16ss_decrease_by()
 * @see f_uint16ss_increase()
 * @see f_uint16ss_increase_by()
 * @see f_uint16ss_resize()
 */
#if !defined(_di_f_uint16ss_decrease_by_) || !defined(_di_f_uint16ss_increase_) || !defined(_di_f_uint16ss_increase_by_) || !defined(_di_f_uint16ss_resize_)
  extern f_status_t private_f_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_uint16ss_decrease_by_) || !defined(_di_f_uint16ss_increase_) || !defined(_di_f_uint16ss_increase_by_) || !defined(_di_f_uint16ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_uint16_h

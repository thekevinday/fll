/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_int8_h
#define _PRIVATE_F_type_array_int8_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the int8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8s
 *   The int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_int8s_adjust()
 * @see f_int8s_decimate_by()
 */
#if !defined(_di_f_int8s_adjust_) || !defined(_di_f_int8s_decimate_by_)
  extern f_status_t private_f_int8s_adjust(const f_number_unsigned_t length, f_int8s_t * const int8s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_int8s_adjust_) || !defined(_di_f_int8s_decimate_by_)

/**
 * Private implementation for appending the int8 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int8 to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_int8s_append()
 * @see f_int8ss_append()
 */
#if !defined(_di_f_int8s_append_) || !defined(_di_f_int8ss_append_)
  extern f_status_t private_f_int8s_append(const int8_t source, f_int8s_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_int8s_append_) || !defined(_di_f_int8ss_append_)

/**
 * Private implementation for appending the int8 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int8s to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_int8s_append_all()
 * @see f_int8ss_append()
 * @see f_int8ss_append_all()
 */
#if !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_append_all_) || !defined(_di_f_int8ss_append_all_)
  extern f_status_t private_f_int8s_append_all(const f_int8s_t source, f_int8s_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_append_all_) || !defined(_di_f_int8ss_append_all_)

/**
 * Private implementation for resizing the int8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8s
 *   The int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_int8s_append()
 * @see f_int8s_append_all()
 * @see f_int8s_decrease_by()
 * @see f_int8s_increase()
 * @see f_int8s_increase_by()
 * @see f_int8s_resize()
 * @see f_int8ss_append()
 * @see f_int8ss_append_all()
 *
 */
#if !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_append_all_) || !defined(_di_f_int8s_decrease_by_) || !defined(_di_f_int8s_increase_) || !defined(_di_f_int8s_increase_by_) || !defined(_di_f_int8s_resize_) || !defined(_di_f_int8ss_append_) || !defined(_di_f_int8ss_append_all_)
  extern f_status_t private_f_int8s_resize(const f_number_unsigned_t length, f_int8s_t * const int8s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_append_all_) || !defined(_di_f_int8s_decrease_by_) || !defined(_di_f_int8s_increase_) || !defined(_di_f_int8s_increase_by_) || !defined(_di_f_int8s_resize_) || !defined(_di_f_int8ss_append_) || !defined(_di_f_int8ss_append_all_)

/**
 * Private implementation for resizing the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8ss
 *   The int8ss array to adjust.
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
 * @see f_int8ss_adjust()
 * @see f_int8ss_decimate_by()
 */
#if !defined(_di_f_int8ss_adjust_) || !defined(_di_f_int8ss_decimate_by_)
  extern f_status_t private_f_int8ss_adjust(const f_number_unsigned_t length, f_int8ss_t * const int8ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_int8ss_adjust_) || !defined(_di_f_int8ss_decimate_by_)

/**
 * Private implementation for resizing the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int8ss
 *   The int8ss array to resize.
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
 * @see f_int8ss_decrease_by()
 * @see f_int8ss_increase()
 * @see f_int8ss_increase_by()
 * @see f_int8ss_resize()
 */
#if !defined(_di_f_int8ss_decrease_by_) || !defined(_di_f_int8ss_increase_) || !defined(_di_f_int8ss_increase_by_) || !defined(_di_f_int8ss_resize_)
  extern f_status_t private_f_int8ss_resize(const f_number_unsigned_t length, f_int8ss_t * const int8ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_int8ss_decrease_by_) || !defined(_di_f_int8ss_increase_) || !defined(_di_f_int8ss_increase_by_) || !defined(_di_f_int8ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_int8_h

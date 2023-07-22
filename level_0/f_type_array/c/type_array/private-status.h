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
#ifndef _PRIVATE_F_type_array_status_h
#define _PRIVATE_F_type_array_status_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for appending the status array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source status to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 *
 * @see f_statuss_append()
 * @see f_statusss_append()
 */
#if !defined(_di_f_statuss_append_) || !defined(_di_f_statusss_append_)
  extern f_status_t private_f_statuss_append(const f_status_t source, f_statuss_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statuss_append_) || !defined(_di_f_statusss_append_)

/**
 * Private implementation for appending the status array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source statuss to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 *
 * @see f_statuss_append_all()
 * @see f_statusss_append()
 * @see f_statusss_append_all()
 */
#if !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_append_all_) || !defined(_di_f_statusss_append_all_)
  extern f_status_t private_f_statuss_append_all(const f_statuss_t source, f_statuss_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_append_all_) || !defined(_di_f_statusss_append_all_)

/**
 * Private implementation for resizing the statusss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param structure
 *   The statusss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 *
 * @see f_statusss_adjust()
 * @see f_statusss_decimate_by()
 */
#if !defined(_di_f_statusss_adjust_) || !defined(_di_f_statusss_decimate_by_)
  extern f_status_t private_f_statusss_adjust(const f_number_unsigned_t length, f_statusss_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statusss_adjust_) || !defined(_di_f_statusss_decimate_by_)

/**
 * Private implementation for resizing the statusss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param structure
 *   The statusss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_statusss_decrease_by()
 * @see f_statusss_increase()
 * @see f_statusss_increase_by()
 * @see f_statusss_resize()
 */
#if !defined(_di_f_statusss_decrease_by_) || !defined(_di_f_statusss_increase_) || !defined(_di_f_statusss_increase_by_) || !defined(_di_f_statusss_resize_)
  extern f_status_t private_f_statusss_resize(const f_number_unsigned_t length, f_statusss_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statusss_decrease_by_) || !defined(_di_f_statusss_increase_) || !defined(_di_f_statusss_increase_by_) || !defined(_di_f_statusss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_status_h

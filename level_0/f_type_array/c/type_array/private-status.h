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
#ifndef _PRIVATE_F_type_array_status_h
#define _PRIVATE_F_type_array_status_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the statuss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statuss
 *   The statuss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_statuss_adjust()
 * @see f_statuss_decimate_by()
 */
#if !defined(_di_f_statuss_adjust_) || !defined(_di_f_statuss_decimate_by_)
  extern f_status_t private_f_statuss_adjust(const f_array_length_t length, f_statuss_t *statuss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statuss_adjust_) || !defined(_di_f_statuss_decimate_by_)

/**
 * Private implementation for appending the status array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source statuss to append.
 * @param destination
 *   The destination statuss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_statuss_append()
 * @see f_statusss_append()
 */
#if !defined(_di_f_statuss_append_) || !defined(_di_f_statusss_append_)
  extern f_status_t private_f_statuss_append(const f_statuss_t source, f_statuss_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statuss_append_) || !defined(_di_f_statusss_append_)

/**
 * Private implementation for resizing the statuss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statuss
 *   The statuss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_statuss_resize()
 * @see f_statuss_append()
 * @see f_statuss_decimate_by()
 * @see f_statusss_append()
 */
#if !defined(_di_f_statuss_resize_) || !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_decimate_by_) || !defined(_di_f_statusss_append_)
  extern f_status_t private_f_statuss_resize(const f_array_length_t length, f_statuss_t *statuss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statuss_resize_) || !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_decimate_by_) || !defined(_di_f_statusss_append_)

/**
 * Private implementation for resizing the statusss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statusss
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
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 *
 * @see f_statusss_adjust()
 * @see f_statusss_decimate_by()
 */
#if !defined(_di_f_statusss_adjust_) || !defined(_di_f_statusss_decimate_by_)
  extern f_status_t private_f_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statusss_adjust_) || !defined(_di_f_statusss_decimate_by_)

/**
 * Private implementation for resizing the statusss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param statusss
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
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_statusss_decrease_by()
 * @see f_statusss_increase()
 * @see f_statusss_increase_by()
 * @see f_statusss_resize()
 */
#if !defined(_di_f_statusss_decrease_by_) || !defined(_di_f_statusss_increase_) || !defined(_di_f_statusss_increase_by_) || !defined(_di_f_statusss_resize_)
  extern f_status_t private_f_statusss_resize(const f_array_length_t length, f_statusss_t *statusss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statusss_decrease_by_) || !defined(_di_f_statusss_increase_) || !defined(_di_f_statusss_increase_by_) || !defined(_di_f_statusss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_status_h
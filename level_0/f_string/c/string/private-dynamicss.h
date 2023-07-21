/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_string_dynamicss_h
#define _PRIVATE_F_string_dynamicss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param dynamicss
 *   The dynamicss to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 *
 * @see f_string_dynamicss_adjust()
 * @see f_string_dynamicss_append()
 * @see f_string_dynamicss_decimate_by()
 * @see f_string_map_multis_adjust()
 * @see f_string_map_multis_append()
 */
#if !defined(_di_f_string_dynamicss_adjust_) || !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_dynamicss_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)
  extern f_status_t private_f_string_dynamicss_adjust(const f_number_unsigned_t length, f_string_dynamicss_t * const dynamicss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamicss_adjust_) || !defined(_di_f_string_dynamicss_append_) || !defined(_di_f_string_dynamicss_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param dynamicss
 *   The dynamicss to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 *
 * @see f_string_dynamicss_append_all()
 * @see f_string_dynamicss_decrease_by()
 * @see f_string_dynamicss_increase()
 * @see f_string_dynamicss_increase_by()
 * @see f_string_map_multis_append_all()
 */
#if !defined(_di_f_string_dynamicss_decrease_by_) || !defined(_di_f_string_dynamicss_increase_) || !defined(_di_f_string_dynamicss_increase_by_) || !defined(_di_f_string_dynamicss_append_all_) || !defined(_di_f_string_map_multis_append_all_)
  extern f_status_t private_f_string_dynamicss_resize(const f_number_unsigned_t length, f_string_dynamicss_t * const dynamicss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamicss_decrease_by_) || !defined(_di_f_string_dynamicss_increase_) || !defined(_di_f_string_dynamicss_increase_by_) || !defined(_di_f_string_dynamicss_append_all_) || !defined(_di_f_string_map_multis_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_dynamicss_h

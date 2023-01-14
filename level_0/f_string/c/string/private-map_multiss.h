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
#ifndef _PRIVATE_F_string_map_multiss_h
#define _PRIVATE_F_string_map_multiss_h

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
 * @param map_multiss
 *   The map_multiss to adjust.
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
 * @see f_string_map_multiss_adjust()
 */
#if !defined(_di_f_string_map_multiss_adjust_) || !defined(_di_f_string_map_multiss_decimate_by_)
  extern f_status_t private_f_string_map_multiss_adjust(const f_array_length_t length, f_string_map_multiss_t * const map_multiss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_map_multiss_adjust_) || !defined(_di_f_string_map_multiss_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param map_multiss
 *   The map_multiss to resize.
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
 * @see f_string_map_multiss_decrease_by()
 * @see f_string_map_multiss_increase()
 * @see f_string_map_multiss_increase_by()
 */
#if !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)
  extern f_status_t private_f_string_map_multiss_resize(const f_array_length_t length, f_string_map_multiss_t * const map_multiss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_map_multiss_h

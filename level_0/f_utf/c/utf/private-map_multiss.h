/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_utf_map_multiss_h
#define _PRIVATE_F_utf_map_multiss_h

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
 * @param structure
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
 * @see f_utf_string_map_multiss_adjust()
 */
#if !defined(_di_f_utf_string_map_multiss_adjust_) || !defined(_di_f_utf_string_map_multiss_decimate_by_)
  extern f_status_t private_f_utf_string_map_multiss_adjust(const f_number_unsigned_t length, f_utf_string_map_multiss_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multiss_adjust_) || !defined(_di_f_utf_string_map_multiss_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
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
 * @see f_utf_string_map_multiss_decrease_by()
 * @see f_utf_string_map_multiss_increase()
 * @see f_utf_string_map_multiss_increase_by()
 */
#if !defined(_di_f_utf_string_map_multiss_decrease_by_) || !defined(_di_f_utf_string_map_multiss_increase_) || !defined(_di_f_utf_string_map_multiss_increase_by_)
  extern f_status_t private_f_utf_string_map_multiss_resize(const f_number_unsigned_t length, f_utf_string_map_multiss_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multiss_decrease_by_) || !defined(_di_f_utf_string_map_multiss_increase_) || !defined(_di_f_utf_string_map_multiss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_map_multiss_h

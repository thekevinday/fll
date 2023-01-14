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
#ifndef _PRIVATE_F_map_multis_h
#define _PRIVATE_F_map_multis_h

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
 * @param map_multis
 *   The map_multis to adjust.
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
 * @see f_utf_string_map_multis_adjust()
 */
#if !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_decimate_by_)
  extern f_status_t private_f_utf_string_map_multis_adjust(const f_array_length_t length, f_utf_string_map_multis_t * const map_multis) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_decimate_by_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source map_multis to append.
 * @param destination
 *   The destination map_multis the source is appended onto.
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
 * @see f_utf_string_map_multis_append_all()
 * @see f_utf_string_map_multiss_append()
 * @see f_utf_string_map_multiss_append_all()
 */
#if !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_)
  extern f_status_t private_f_utf_string_map_multis_append_all(const f_utf_string_map_multis_t source, f_utf_string_map_multis_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The map_multis to resize.
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
 * @see f_utf_string_map_multis_append()
 * @see f_utf_string_map_multis_append_all()
 * @see f_utf_string_map_multis_decrease_by()
 * @see f_utf_string_map_multis_increase()
 * @see f_utf_string_map_multis_increase_by()
 * @see f_utf_string_map_multis_resize()
 * @see f_utf_string_map_multiss_append()
 * @see f_utf_string_map_multiss_append_all()
 * @see f_utf_string_map_multiss_decrease_by()
 * @see f_utf_string_map_multiss_increase()
 * @see f_utf_string_map_multiss_increase_by()
 */
#if !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multis_decrease_by_) || !defined(_di_f_utf_string_map_multis_increase_) || !defined(_di_f_utf_string_map_multis_increase_by_) || !defined(_di_f_utf_string_map_multis_resize_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_) || !defined(_di_f_utf_string_map_multiss_decrease_by_) || !defined(_di_f_utf_string_map_multiss_increase_) || !defined(_di_f_utf_string_map_multiss_increase_by_)
  extern f_status_t private_f_utf_string_map_multis_resize(const f_array_length_t length, f_utf_string_map_multis_t * const map_multis) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multis_decrease_by_) || !defined(_di_f_utf_string_map_multis_increase_) || !defined(_di_f_utf_string_map_multis_increase_by_) || !defined(_di_f_utf_string_map_multis_resize_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_) || !defined(_di_f_utf_string_map_multiss_decrease_by_) || !defined(_di_f_utf_string_map_multiss_increase_) || !defined(_di_f_utf_string_map_multiss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_map_multis_h

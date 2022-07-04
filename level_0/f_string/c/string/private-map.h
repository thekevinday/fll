/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_string_map_h
#define _PRIVATE_F_string_map_h

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
 * @param maps
 *   The maps to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_maps_adjust()
 */
#if !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)
  extern f_status_t private_f_string_maps_adjust(const f_array_length_t length, f_string_maps_t * const maps) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_maps_adjust_) || !defined(_di_f_string_maps_decimate_by_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_string_maps_append_all()
 * @see f_string_mapss_append()
 * @see f_string_mapss_append_all()
 */
#if !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_)
  extern f_status_t private_f_string_maps_append_all(const f_string_maps_t source, f_string_maps_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_maps_append_all_) || !defined(_di_f_string_mapss_append_) || !defined(_di_f_string_mapss_append_all_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param maps
 *   The maps to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_adjust()
 * @see f_string_maps_decrease_by()
 * @see f_string_maps_increase()
 * @see f_string_maps_increase_by()
 * @see f_string_maps_terminate()
 * @see f_string_maps_terminate_after()
 */
#if !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_terminate_) || !defined(_di_f_string_maps_terminate_after_)
  extern f_status_t private_f_string_maps_resize(const f_array_length_t length, f_string_maps_t * const maps) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_terminate_) || !defined(_di_f_string_maps_terminate_after_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param mapss
 *   The mapss to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_mapss_adjust()
 */
#if !defined(_di_f_string_mapss_adjust_) || !defined(_di_f_string_mapss_decimate_by_)
  extern f_status_t private_f_string_mapss_adjust(const f_array_length_t length, f_string_mapss_t * const mapss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_mapss_adjust_) || !defined(_di_f_string_mapss_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param mapss
 *   The mapss to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_adjust()
 * @see f_string_mapss_decrease_by()
 * @see f_string_mapss_increase()
 * @see f_string_mapss_increase_by()
 * @see f_string_mapss_terminate()
 * @see f_string_mapss_terminate_after()
 */
#if !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_) || !defined(_di_f_string_mapss_terminate_) || !defined(_di_f_string_mapss_terminate_after_)
  extern f_status_t private_f_string_mapss_resize(const f_array_length_t length, f_string_mapss_t * const mapss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_mapss_decrease_by_) || !defined(_di_f_string_mapss_increase_) || !defined(_di_f_string_mapss_increase_by_) || !defined(_di_f_string_mapss_terminate_) || !defined(_di_f_string_mapss_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_map_h

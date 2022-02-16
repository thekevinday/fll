/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 string capabilities.
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_utf_string_h
#define _PRIVATE_F_utf_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_string_append().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see memcpy()
 *
 * @see f_utf_string_append()
 * @see f_utf_string_append_assure()
 * @see f_utf_string_dynamic_append()
 * @see f_utf_string_dynamic_append_assure()
 * @see f_utf_string_dynamic_mash()
 * @see f_utf_string_dynamic_partial_append)
 * @see f_utf_string_dynamic_partial_append_assure()
 * @see f_utf_string_dynamic_partial_mash()
 * @see f_utf_string_dynamics_append()
 * @see f_utf_string_map_multis_append()
 * @see f_utf_string_mash()
 * @see f_utf_string_maps_append()
 * @see f_utf_string_triples_append()
 */
#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_triples_append_)
  extern f_status_t private_f_utf_string_append(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_triples_append_)

/**
 * Private implementation of f_utf_string_append_nulless().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 * @see memcpy()
 *
 * @see f_utf_string_append_assure_nulless()
 * @see f_utf_string_append_nulless()
 * @see f_utf_string_dynamic_append_assure_nulless()
 * @see f_utf_string_dynamic_append_nulless()
 * @see f_utf_string_dynamic_mash_nulless()
 * @see f_utf_string_dynamic_partial_append_assure_nulless()
 * @see f_utf_string_dynamic_partial_append_nulless()
 * @see f_utf_string_dynamic_partial_mash_nulless()
 * @see f_utf_string_mash_nulless()
 */
#if !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_mash_nulless_)
  extern f_status_t private_f_utf_string_append_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_mash_nulless_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param string
 *   The string to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_utf_string_dynamic_adjust()
 * @see f_utf_string_dynamic_decimate_by()
 * @see f_utf_string_dynamics_adjust()
 * @see f_utf_string_dynamics_append()
 * @see f_utf_string_dynamics_decimate_by()
 * @see f_utf_string_map_multis_adjust()
 * @see f_utf_string_map_multis_append()
 * @see f_utf_string_triples_adjust()
 * @see f_utf_string_triples_decimate_by()
 */
#if !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  extern f_status_t private_f_utf_string_dynamic_adjust(const f_array_length_t length, f_utf_string_dynamic_t *string) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_dynamic_adjust_) || !defined(_di_f_utf_string_dynamic_decimate_by_) || !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

/**
 * Private implementation of f_utf_string_dynamic_increase_by().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see memcpy()
 *
 * @see f_utf_string_append()
 * @see f_utf_string_append_assure()
 * @see f_utf_string_append_mash()
 * @see f_utf_string_append_nulless()
 * @see f_utf_string_dynamic_append()
 * @see f_utf_string_dynamic_append_assure()
 * @see f_utf_string_dynamic_append_nulless()
 * @see f_utf_string_dynamic_increase_by()
 * @see f_utf_string_dynamic_mash()
 * @see f_utf_string_dynamic_mash_nulless()
 * @see f_utf_string_dynamic_partial_append)
 * @see f_utf_string_dynamic_partial_append_assure()
 * @see f_utf_string_dynamic_partial_mash()
 * @see f_utf_string_dynamic_prepend()
 * @see f_utf_string_dynamic_prepend_nulless()
 * @see f_utf_string_dynamics_append()
 * @see f_utf_string_map_multis_append()
 * @see f_utf_string_mash()
 * @see f_utf_string_mash_nulless()
 * @see f_utf_string_maps_append()
 * @see f_utf_string_prepend()
 * @see f_utf_string_prepend_nulless()
 * @see f_utf_string_triples_append()
 */
#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)
  extern f_status_t private_f_utf_string_dynamic_increase_by(const f_array_length_t amount, f_utf_string_dynamic_t *string) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_utf_string_append()
 * @see f_utf_string_append_assure()
 * @see f_utf_string_append_mash()
 * @see f_utf_string_append_nulless()
 * @see f_utf_string_dynamic_append()
 * @see f_utf_string_dynamic_append_assure()
 * @see f_utf_string_dynamic_append_nulless()
 * @see f_utf_string_dynamic_decrease_by()
 * @see f_utf_string_dynamic_increase()
 * @see f_utf_string_dynamic_increase_by()
 * @see f_utf_string_dynamic_mash()
 * @see f_utf_string_dynamic_mash_nulless()
 * @see f_utf_string_dynamic_partial_append)
 * @see f_utf_string_dynamic_partial_append_assure()
 * @see f_utf_string_dynamic_partial_mash()
 * @see f_utf_string_dynamic_prepend()
 * @see f_utf_string_dynamic_prepend_nulless()
 * @see f_utf_string_dynamic_terminate()
 * @see f_utf_string_dynamic_terminate_after()
 * @see f_utf_string_dynamics_append()
 * @see f_utf_string_map_multis_append()
 * @see f_utf_string_mash_nulless()
 * @see f_utf_string_mash()
 * @see f_utf_string_maps_append()
 * @see f_utf_string_prepend()
 * @see f_utf_string_prepend_nulless()
 * @see f_utf_string_triples_append()
 */
#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)
  extern f_status_t private_f_utf_string_dynamic_resize(const f_array_length_t length, f_utf_string_dynamic_t *string) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_append_mash_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_decrease_by_) || !defined(_di_f_utf_string_dynamic_increase_) || !defined(_di_f_utf_string_dynamic_increase_by_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(f_utf_string_dynamic_partial_append) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_terminate_) || !defined(_di_f_utf_string_dynamic_terminate_after_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_nulless_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_prepend_) || !defined(_di_f_utf_string_prepend_nulless_) || !defined(_di_f_utf_string_triples_append_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param strings
 *   The strings to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_utf_string_dynamics_adjust()
 * @see f_utf_string_dynamics_append()
 * @see f_utf_string_dynamics_decimate_by()
 * @see f_utf_string_map_multis_adjust()
 * @see f_utf_string_map_multis_append()
 */
#if !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)
  extern f_status_t private_f_utf_string_dynamics_adjust(const f_array_length_t length, f_utf_string_dynamics_t *strings) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_dynamics_adjust_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_dynamics_decimate_by_) || !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_append_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_utf_string_dynamics_append()
 * @see f_utf_string_map_multis_append()
 */
#if !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_)
  extern f_status_t private_f_utf_string_dynamics_append(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param strings
 *   The strings to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_utf_string_dynamics_decrease_by()
 * @see f_utf_string_dynamics_increase()
 * @see f_utf_string_dynamics_increase_by()
 */
#if !defined(_di_f_utf_string_dynamics_decrease_by_) || !defined(_di_f_utf_string_dynamics_increase_) || !defined(_di_f_utf_string_dynamics_increase_by_)
  extern f_status_t private_f_utf_string_dynamics_resize(const f_array_length_t length, f_utf_string_dynamics_t *strings) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_dynamics_decrease_by_) || !defined(_di_f_utf_string_dynamics_increase_) || !defined(_di_f_utf_string_dynamics_increase_by_)

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
 * @see f_utf_string_map_multis_adjust()
 */
#if !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_decimate_by_)
  extern f_status_t private_f_utf_string_map_multis_adjust(const f_array_length_t length, f_utf_string_map_multis_t *map_multis) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multis_adjust_) || !defined(_di_f_utf_string_map_multis_decimate_by_)

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
 * @see f_memory_adjust()
 * @see f_utf_string_map_multis_decrease_by()
 * @see f_utf_string_map_multis_increase()
 * @see f_utf_string_map_multis_increase_by()
 * @see f_utf_string_map_multis_terminate()
 * @see f_utf_string_map_multis_terminate_after()
 */
#if !defined(_di_f_utf_string_map_multis_decrease_by_) || !defined(_di_f_utf_string_map_multis_increase_) || !defined(_di_f_utf_string_map_multis_increase_by_) || !defined(_di_f_utf_string_map_multis_terminate_) || !defined(_di_f_utf_string_map_multis_terminate_after_)
  extern f_status_t private_f_utf_string_map_multis_resize(const f_array_length_t length, f_utf_string_map_multis_t *map_multis) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multis_decrease_by_) || !defined(_di_f_utf_string_map_multis_increase_) || !defined(_di_f_utf_string_map_multis_increase_by_) || !defined(_di_f_utf_string_map_multis_terminate_) || !defined(_di_f_utf_string_map_multis_terminate_after_)

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
 * @see f_utf_string_maps_adjust()
 */
#if !defined(_di_f_utf_string_maps_adjust_) || !defined(_di_f_utf_string_maps_decimate_by_)
  extern f_status_t private_f_utf_string_maps_adjust(const f_array_length_t length, f_utf_string_maps_t *maps) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_maps_adjust_) || !defined(_di_f_utf_string_maps_decimate_by_)

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
 * @see f_utf_string_maps_decrease_by()
 * @see f_utf_string_maps_increase()
 * @see f_utf_string_maps_increase_by()
 * @see f_utf_string_maps_terminate()
 * @see f_utf_string_maps_terminate_after()
 */
#if !defined(_di_f_utf_string_maps_decrease_by_) || !defined(_di_f_utf_string_maps_increase_) || !defined(_di_f_utf_string_maps_increase_by_) || !defined(_di_f_utf_string_maps_terminate_) || !defined(_di_f_utf_string_maps_terminate_after_)
  extern f_status_t private_f_utf_string_maps_resize(const f_array_length_t length, f_utf_string_maps_t *maps) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_maps_decrease_by_) || !defined(_di_f_utf_string_maps_increase_) || !defined(_di_f_utf_string_maps_increase_by_) || !defined(_di_f_utf_string_maps_terminate_) || !defined(_di_f_utf_string_maps_terminate_after_)

/**
 * Private implementation of f_utf_string_prepend().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are prepended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see memcopy()
 * @see memmove()
 *
 * @see f_utf_string_dynamic_mish()
 * @see f_utf_string_dynamic_partial_mish()
 * @see f_utf_string_dynamic_partial_prepend_assure()
 * @see f_utf_string_dynamic_partial_prepend()
 * @see f_utf_string_dynamic_prepend_assure()
 * @see f_utf_string_dynamic_prepend()
 * @see f_utf_string_mish()
 * @see f_utf_string_prepend_assure()
 * @see f_utf_string_prepend()
 */
#if !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_)
  extern f_status_t private_f_utf_string_prepend(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_)

/**
 * Private implementation of f_utf_string_prepend_nulless().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are prepended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see memcopy()
 * @see memmove()
 *
 * @see f_utf_string_dynamic_mish_nulless()
 * @see f_utf_string_dynamic_partial_mish_nulless()
 * @see f_utf_string_dynamic_partial_prepend_assure_nulless()
 * @see f_utf_string_dynamic_partial_prepend_nulless()
 * @see f_utf_string_dynamic_prepend_assure_nulless()
 * @see f_utf_string_dynamic_prepend_nulless()
 * @see f_utf_string_mish_nulless()
 * @see f_utf_string_prepend_assure_nulless()
 * @see f_utf_string_prepend_nulless()
 */
#if !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_)
  extern f_status_t private_f_utf_string_prepend_nulless(const f_utf_string_t source, f_array_length_t length, f_utf_string_dynamic_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param triples
 *   The triples to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_utf_string_triples_adjust()
 * @see f_utf_string_triples_decimate_by()
 */
#if !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  extern f_status_t private_f_utf_string_triples_adjust(const f_array_length_t length, f_utf_string_triples_t *triples) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param triples
 *   The triples to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_utf_string_triples_decrease_by()
 * @see f_utf_string_triples_increase()
 * @see f_utf_string_triples_increase_by()
 * @see f_utf_string_triples_terminate()
 * @see f_utf_string_triples_terminate_after()
 */
#if !defined(_di_f_utf_string_triples_decrease_by_) || !defined(_di_f_utf_string_triples_increase_) || !defined(_di_f_utf_string_triples_increase_by_) || !defined(_di_f_utf_string_triples_terminate_) || !defined(_di_f_utf_string_triples_terminate_after_)
  extern f_status_t private_f_utf_string_triples_resize(const f_array_length_t length, f_utf_string_triples_t *triples) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_triples_decrease_by_) || !defined(_di_f_utf_string_triples_increase_) || !defined(_di_f_utf_string_triples_increase_by_) || !defined(_di_f_utf_string_triples_terminate_) || !defined(_di_f_utf_string_triples_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_string_h

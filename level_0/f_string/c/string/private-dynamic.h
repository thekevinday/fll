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
#ifndef _PRIVATE_F_string_dynamic_h
#define _PRIVATE_F_string_dynamic_h

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
 * @param dynamic
 *   The string to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 * @see f_string_dynamic_decimate_by()
 * @see f_string_dynamics_adjust()
 * @see f_string_dynamics_append()
 * @see f_string_dynamics_decimate_by()
 * @see f_string_map_multis_adjust()
 * @see f_string_map_multis_append()
 * @see f_string_triples_adjust()
 * @see f_string_triples_decimate_by()
 */
#if !defined(_di_f_string_dynamic_adjust_) || !defined(_di_f_string_dynamic_decimate_by_) || !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)
  extern f_status_t private_f_string_dynamic_adjust(const f_number_unsigned_t length, f_string_dynamic_t * const dynamic) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamic_adjust_) || !defined(_di_f_string_dynamic_decimate_by_) || !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)

/**
 * Private implementation of f_string_dynamic_increase_by().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamic
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
 * @see f_string_append()
 * @see f_string_append_assure()
 * @see f_string_append_mash()
 * @see f_string_append_nulless()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamic_mash()
 * @see f_string_dynamic_mash_nulless()
 * @see f_string_dynamic_partial_append)
 * @see f_string_dynamic_partial_append_assure()
 * @see f_string_dynamic_partial_mash()
 * @see f_string_dynamic_prepend()
 * @see f_string_dynamic_prepend_nulless()
 * @see f_string_dynamics_append()
 * @see f_string_map_multis_append()
 * @see f_string_mash()
 * @see f_string_mash_nulless()
 * @see f_string_maps_append()
 * @see f_string_prepend()
 * @see f_string_prepend_nulless()
 * @see f_string_triples_append()
 */
#if !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)
  extern f_status_t private_f_string_dynamic_increase_by(const f_number_unsigned_t amount, f_string_dynamic_t * const dynamic) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_string_append()
 * @see f_string_append_assure()
 * @see f_string_append_mash()
 * @see f_string_append_nulless()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_decrease_by()
 * @see f_string_dynamic_increase()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamic_mash()
 * @see f_string_dynamic_mash_nulless()
 * @see f_string_dynamic_partial_append)
 * @see f_string_dynamic_partial_append_assure()
 * @see f_string_dynamic_partial_mash()
 * @see f_string_dynamic_prepend()
 * @see f_string_dynamic_prepend_nulless()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamic_terminate_after()
 * @see f_string_dynamics_append()
 * @see f_string_map_multis_append()
 * @see f_string_mash_nulless()
 * @see f_string_mash()
 * @see f_string_maps_append()
 * @see f_string_prepend()
 * @see f_string_prepend_nulless()
 * @see f_string_triples_append()
 */
#if !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_increase_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamic_terminate_) || !defined(_di_f_string_dynamic_terminate_after_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)
  extern f_status_t private_f_string_dynamic_resize(const f_number_unsigned_t length, f_string_dynamic_t * const dynamic) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_increase_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_dynamic_terminate_) || !defined(_di_f_string_dynamic_terminate_after_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_triples_append_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_dynamic_h

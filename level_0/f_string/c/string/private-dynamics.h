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
#ifndef _PRIVATE_F_string_dynamics_h
#define _PRIVATE_F_string_dynamics_h

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
 *   The dynamics to adjust.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 *
 * @see f_string_dynamics_adjust()
 * @see f_string_dynamics_append()
 * @see f_string_dynamics_decimate_by()
 * @see f_string_map_multis_adjust()
 * @see f_string_map_multis_append()
 */
#if !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)
  extern f_status_t private_f_string_dynamics_adjust(const f_number_unsigned_t length, f_string_dynamics_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamics_adjust_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_map_multis_adjust_) || !defined(_di_f_string_map_multis_append_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination dynamics the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 *
 * @see f_string_dynamics_append()
 * @see f_string_map_multis_append()
 * @see f_string_map_multis_append_all()
 */
#if !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)
  extern f_status_t private_f_string_dynamics_append(const f_string_dynamic_t source, f_string_dynamics_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination dynamics the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 *
 * @see f_string_dynamics_append_all()
 * @see f_string_map_multis_append()
 * @see f_string_map_multis_append_all()
 */
#if  !defined(_di_f_string_dynamics_append_all_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)
  extern f_status_t private_f_string_dynamics_append_all(const f_string_dynamics_t source, f_string_dynamics_t * const destination) F_attribute_visibility_internal_d;
#endif //  !defined(_di_f_string_dynamics_append_all_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The dynamics to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 *
 * @see f_string_dynamics_decrease_by()
 * @see f_string_dynamics_increase()
 * @see f_string_dynamics_increase_by()
 * @see f_string_dynamics_resize()
 * @see f_string_map_multis_append()
 * @see f_string_map_multis_append_all()
 * @see f_string_map_multis_decrease_by()
 * @see f_string_map_multis_increase()
 * @see f_string_map_multis_increase_by()
 * @see f_string_map_multis_resize()
 * @see f_string_map_multiss_append()
 * @see f_string_map_multiss_append_all()
 * @see f_string_map_multiss_decrease_by()
 * @see f_string_map_multiss_increase()
 * @see f_string_map_multiss_increase_by()
 */
#if !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_) || !defined(f_string_dynamics_resize) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_) || !defined(_di_f_string_map_multis_decrease_by_) || !defined(_di_f_string_map_multis_increase_) || !defined(_di_f_string_map_multis_increase_by_) || !defined(_di_f_string_map_multis_resize_) || !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multiss_append_all_) || !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)
  extern f_status_t private_f_string_dynamics_resize(const f_number_unsigned_t length, f_string_dynamics_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_) || !defined(f_string_dynamics_resize) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_map_multis_append_all_) || !defined(_di_f_string_map_multis_decrease_by_) || !defined(_di_f_string_map_multis_increase_) || !defined(_di_f_string_map_multis_increase_by_) || !defined(_di_f_string_map_multis_resize_) || !defined(_di_f_string_map_multiss_append_) || !defined(_di_f_string_map_multiss_append_all_) || !defined(_di_f_string_map_multiss_decrease_by_) || !defined(_di_f_string_map_multiss_increase_) || !defined(_di_f_string_map_multiss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_dynamics_h

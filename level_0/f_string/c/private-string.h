/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_string_h
#define _PRIVATE_F_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_string_append().
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
 * @see f_string_append()
 * @see f_string_append_assure()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_mash()
 * @see f_string_dynamic_partial_append)
 * @see f_string_dynamic_partial_append_assure()
 * @see f_string_dynamic_partial_mash()
 * @see f_string_dynamics_append()
 * @see f_string_map_multis_append()
 * @see f_string_mash()
 * @see f_string_maps_append()
 * @see f_string_triples_append()
 */
#if !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_mash_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_triples_append_)
  extern f_status_t private_f_string_append(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_append_assure_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_append_assure_) || !defined(_di_f_string_dynamic_mash_) || !defined(f_string_dynamic_partial_append) || !defined(_di_f_string_dynamic_partial_append_assure_) || !defined(_di_f_string_dynamic_partial_mash_) || !defined(_di_f_string_dynamics_append_) || !defined(_di_f_string_map_multis_append_) || !defined(_di_f_string_mash_) || !defined(_di_f_string_maps_append_) || !defined(_di_f_string_triples_append_)

/**
 * Private implementation of f_string_append_nulless().
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
 * @see f_string_append_assure_nulless()
 * @see f_string_append_nulless()
 * @see f_string_dynamic_append_assure_nulless()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_mash_nulless()
 * @see f_string_dynamic_partial_append_assure_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_partial_mash_nulless()
 * @see f_string_mash_nulless()
 */
#if !defined(_di_f_string_append_assure_nulless_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_assure_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_string_dynamic_partial_append_nulless_) || !defined(_di_f_string_dynamic_partial_mash_nulless_) || !defined(_di_f_string_mash_nulless_)
  extern f_status_t private_f_string_append_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_append_assure_nulless_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_assure_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_string_dynamic_partial_append_nulless_) || !defined(_di_f_string_dynamic_partial_mash_nulless_) || !defined(_di_f_string_mash_nulless_)

/**
 * Private implementation of f_string_prepend().
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
 * @see f_string_dynamic_mish()
 * @see f_string_dynamic_partial_mish()
 * @see f_string_dynamic_partial_prepend_assure()
 * @see f_string_dynamic_partial_prepend()
 * @see f_string_dynamic_prepend_assure()
 * @see f_string_dynamic_prepend()
 * @see f_string_mish()
 * @see f_string_prepend_assure()
 * @see f_string_prepend()
 */
#if !defined(_di_f_string_dynamic_mish_) || !defined(_di_f_string_dynamic_partial_mish_) || !defined(_di_f_string_dynamic_partial_prepend_assure_) || !defined(_di_f_string_dynamic_partial_prepend_) || !defined(_di_f_string_dynamic_prepend_assure_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_mish_) || !defined(_di_f_string_prepend_assure_) || !defined(_di_f_string_prepend_)
  extern f_status_t private_f_string_prepend(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamic_mish_) || !defined(_di_f_string_dynamic_partial_mish_) || !defined(_di_f_string_dynamic_partial_prepend_assure_) || !defined(_di_f_string_dynamic_partial_prepend_) || !defined(_di_f_string_dynamic_prepend_assure_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_mish_) || !defined(_di_f_string_prepend_assure_) || !defined(_di_f_string_prepend_)

/**
 * Private implementation of f_string_prepend_nulless().
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
 * @see f_string_dynamic_mish_nulless()
 * @see f_string_dynamic_partial_mish_nulless()
 * @see f_string_dynamic_partial_prepend_assure_nulless()
 * @see f_string_dynamic_partial_prepend_nulless()
 * @see f_string_dynamic_prepend_assure_nulless()
 * @see f_string_dynamic_prepend_nulless()
 * @see f_string_mish_nulless()
 * @see f_string_prepend_assure_nulless()
 * @see f_string_prepend_nulless()
 */
#if !defined(_di_f_string_dynamic_mish_nulless_) || !defined(_di_f_string_dynamic_partial_mish_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_mish_nulless_) || !defined(_di_f_string_prepend_assure_nulless_) || !defined(_di_f_string_prepend_nulless_)
  extern f_status_t private_f_string_prepend_nulless(const f_string_t source, f_array_length_t length, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_dynamic_mish_nulless_) || !defined(_di_f_string_dynamic_partial_mish_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_mish_nulless_) || !defined(_di_f_string_prepend_assure_nulless_) || !defined(_di_f_string_prepend_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_h

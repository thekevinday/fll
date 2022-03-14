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
#ifndef _PRIVATE_F_string_triple_h
#define _PRIVATE_F_string_triple_h

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
 * @see f_string_triples_adjust()
 */
#if !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)
  extern f_status_t private_f_string_triples_adjust(const f_array_length_t length, f_string_triples_t * const triples) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source triples to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_string_triples_append_all()
 * @see f_string_tripless_append()
 * @see f_string_tripless_append_all()
 */
#if !defined(_di_f_string_triples_append_all_) || !defined(_di_f_string_tripless_append_) || !defined(_di_f_string_tripless_append_all_)
  extern f_status_t private_f_string_triples_append_all(const f_string_triples_t source, f_string_triples_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_triples_append_all_) || !defined(_di_f_string_tripless_append_) || !defined(_di_f_string_tripless_append_all_)

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
 * @see f_memory_adjust()
 * @see f_string_triples_decrease_by()
 * @see f_string_triples_increase()
 * @see f_string_triples_increase_by()
 * @see f_string_triples_terminate()
 * @see f_string_triples_terminate_after()
 */
#if !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_) || !defined(_di_f_string_triples_terminate_) || !defined(_di_f_string_triples_terminate_after_)
  extern f_status_t private_f_string_triples_resize(const f_array_length_t length, f_string_triples_t * const triples) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_) || !defined(_di_f_string_triples_terminate_) || !defined(_di_f_string_triples_terminate_after_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param tripless
 *   The tripless to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_tripless_adjust()
 */
#if !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)
  extern f_status_t private_f_string_tripless_adjust(const f_array_length_t length, f_string_tripless_t * const tripless) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param tripless
 *   The tripless to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_adjust()
 * @see f_string_tripless_decrease_by()
 * @see f_string_tripless_increase()
 * @see f_string_tripless_increase_by()
 * @see f_string_tripless_terminate()
 * @see f_string_tripless_terminate_after()
 */
#if !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_) || !defined(_di_f_string_tripless_terminate_) || !defined(_di_f_string_tripless_terminate_after_)
  extern f_status_t private_f_string_tripless_resize(const f_array_length_t length, f_string_tripless_t * const tripless) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_) || !defined(_di_f_string_tripless_terminate_) || !defined(_di_f_string_tripless_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_triple_h

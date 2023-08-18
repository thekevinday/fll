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
#ifndef _PRIVATE_F_utf_triple_h
#define _PRIVATE_F_utf_triple_h

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
 *   The triples to adjust.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_utf_string_triples_adjust()
 */
#if !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)
  extern f_status_t private_f_utf_string_triples_adjust(const f_number_unsigned_t length, f_utf_string_triples_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_triples_adjust_) || !defined(_di_f_utf_string_triples_decimate_by_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source destination to append.
 * @param destination
 *   The destination triples the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_utf_string_triples_append_all()
 * @see f_utf_string_tripless_append()
 * @see f_utf_string_tripless_append_all()
 */
#if !defined(_di_f_utf_string_triples_append_all_) || !defined(_di_f_utf_string_tripless_append_) || !defined(_di_f_utf_string_tripless_append_all_)
  extern f_status_t private_f_utf_string_triples_append_all(const f_utf_string_triples_t source, f_utf_string_triples_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_triples_append_all_) || !defined(_di_f_utf_string_tripless_append_) || !defined(_di_f_utf_string_tripless_append_all_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The triples to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_utf_string_triples_decrease_by()
 * @see f_utf_string_triples_increase()
 * @see f_utf_string_triples_increase_by()
 */
#if !defined(_di_f_utf_string_triples_decrease_by_) || !defined(_di_f_utf_string_triples_increase_) || !defined(_di_f_utf_string_triples_increase_by_)
  extern f_status_t private_f_utf_string_triples_resize(const f_number_unsigned_t length, f_utf_string_triples_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_triples_decrease_by_) || !defined(_di_f_utf_string_triples_increase_) || !defined(_di_f_utf_string_triples_increase_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The tripless to adjust.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_utf_string_tripless_adjust()
 */
#if !defined(_di_f_utf_string_tripless_adjust_) || !defined(_di_f_utf_string_tripless_decimate_by_)
  extern f_status_t private_f_utf_string_tripless_adjust(const f_number_unsigned_t length, f_utf_string_tripless_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_tripless_adjust_) || !defined(_di_f_utf_string_tripless_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The tripless to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_utf_string_tripless_decrease_by()
 * @see f_utf_string_tripless_increase()
 * @see f_utf_string_tripless_increase_by()
 */
#if !defined(_di_f_utf_string_tripless_decrease_by_) || !defined(_di_f_utf_string_tripless_increase_) || !defined(_di_f_utf_string_tripless_increase_by_)
  extern f_status_t private_f_utf_string_tripless_resize(const f_number_unsigned_t length, f_utf_string_tripless_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_tripless_decrease_by_) || !defined(_di_f_utf_string_tripless_increase_) || !defined(_di_f_utf_string_tripless_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_triple_h

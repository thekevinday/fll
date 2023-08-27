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
#ifndef _PRIVATE_F_utf_map_multis_h
#define _PRIVATE_F_utf_map_multis_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source destination to append.
 * @param destination
 *   The destination map_multis the source is appended onto.
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
 * @see f_utf_string_map_multis_append_all()
 * @see f_utf_string_map_multiss_append()
 * @see f_utf_string_map_multiss_append_all()
 */
#if !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_)
  extern f_status_t private_f_utf_string_map_multis_append_all(const f_utf_string_map_multis_t source, f_utf_string_map_multis_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_string_map_multis_append_all_) || !defined(_di_f_utf_string_map_multiss_append_) || !defined(_di_f_utf_string_map_multiss_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_map_multis_h

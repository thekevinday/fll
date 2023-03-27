/**
 * FLL - Level 0
 *
 * Project: Rip
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides basic UTF-8 string rip capabilities.
 */
#ifndef _F_rip_utf_h
#define _F_rip_utf_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocate a new UTF-8 string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested length.
 *
 * @param source
 *   The string to rip from.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_rip_utf_
  extern f_status_t f_rip_utf(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_rip_utf_

/**
 * Allocate a new UTF-8 string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * @param source
 *   The buffer to rip from.
 * @param range
 *   A range within the buffer representing the string to rip.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_string_append().
 *
 * @see f_utf_string_append()
 */
#ifndef _di_f_rip_utf_dynamic_
  extern f_status_t f_rip_utf_dynamic(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t * const destination);
#endif // _di_f_rip_utf_dynamic_

/**
 * Allocate a new UTF-8 string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The string to rip from.
 * @param range
 *   A range within the buffer representing the string to rip.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_string_append_nulless().
 *
 * @see f_utf_string_append_nulless()
 */
#ifndef _di_f_rip_utf_dynamic_nulless_
  extern f_status_t f_rip_utf_dynamic_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t * const destination);
#endif // _di_f_rip_utf_dynamic_nulless_

/**
 * Allocate a new UTF-8 string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested length.
 *
 * Skips over NULL characters from source when ripping.
 *
 * @param source
 *   The string to rip from.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_rip_utf_nulless_
  extern f_status_t f_rip_utf_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_rip_utf_nulless_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_rip_utf_h

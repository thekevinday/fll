/**
 * FLL - Level 0
 *
 * Project: Rip
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_rip_utf_h
#define _PRIVATE_F_rip_utf_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_rip_utf(), but only the part for finding the start/stop range.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The string to rip from.
 * @param start
 *   Inclusive start point of string to rip.
 *   Will be updated to reflect the new start range.
 * @param stop
 *   Inclusive stop point of string to rip.
 *   Will be updated to reflect the new stop range.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but only white space found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace()
 *
 * @see f_utf_character_is_whitespace()
 * @see f_rip_utf_dynamic()
 * @see f_rip_utf()
 */
#if !defined(_di_f_rip_utf_) || !defined(_di_f_rip_utf_dynamic_) || !defined(_di_f_rip_utf_nulless_) || !defined(_di_f_rip_utf_dynamic_nulless_)
  extern f_status_t private_f_rip_utf_find_range(const f_utf_string_t source, f_array_length_t *start, f_array_length_t *stop) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_rip_utf_) || !defined(_di_f_rip_utf_dynamic_) || !defined(_di_f_rip_utf_nulless_) || !defined(_di_f_rip_utf_dynamic_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_rip_utf_h

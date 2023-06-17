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
#ifndef _PRIVATE_F_rip_h
#define _PRIVATE_F_rip_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_rip(), but only the part for finding the start/stop range.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
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
 *   F_utf_not (with error bit) if a character is not valid UTF-8.
 *
 *   F_parameter (with error bit) from: f_utf_is_combining().
 *   F_parameter (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 *
 * @see f_rip_dynamic_partial()
 * @see f_rip_dynamic_partial_nulless()
 * @see f_rip_dynamic()
 * @see f_rip()
 * @see f_rip_nulless()
 */
#if !defined(_di_f_rip_dynamic_partial_) || !defined(_di_f_rip_dynamic_partial_nulless_) || !defined(_di_f_rip_dynamic_)  || !defined(_di_f_rip_) || !defined(_di_f_rip_nulless_)
  extern f_status_t private_f_rip_find_range(const f_string_t string, f_number_unsigned_t * const start, f_number_unsigned_t * const stop) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_rip_dynamic_partial_) || !defined(_di_f_rip_dynamic_partial_nulless_) || !defined(_di_f_rip_dynamic_)  || !defined(_di_f_rip_) || !defined(_di_f_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_rip_h

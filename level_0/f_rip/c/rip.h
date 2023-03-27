/**
 * FLL - Level 0
 *
 * Project: Rip
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides basic string rip capabilities.
 */
#ifndef _F_rip_h
#define _F_rip_h

// Libc includes.
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type.h>
#include <fll/level_0/utf.h>

// FLL-0 compare includes.
#include <fll/level_0/rip/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *   F_data_not if the range to rip is empty.
 *   F_data_not_eos if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_string_append_nulless().
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_string_append()
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_rip_
  extern f_status_t f_rip(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_rip_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
 * As a result, resulting size may be smaller than requested range.
 *
 * @param source
 *   The buffer to rip from.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_data_not if the range to rip is empty.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_string_append().
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_string_append()
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_rip_dynamic_
  extern f_status_t f_rip_dynamic(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_rip_dynamic_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
 * As a result, resulting size may be smaller than requested range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The string to rip from.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_data_not if the range to rip is empty.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_string_append_nulless().
 *
 *   Errors (with error bit) from: f_string_append_nulless().
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_string_append_nulless()
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_rip_dynamic_nulless_
  extern f_status_t f_rip_dynamic_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_rip_dynamic_nulless_

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *   F_data_not if the range to rip is empty.
 *   F_data_not_eos if source length is 0.
 *
 *   Success from: f_string_append_nulless().
 *
 *   Errors (with error bit) from: f_string_append_nulless().
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_string_append_nulless()
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_rip_nulless_
  extern f_status_t f_rip_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_rip_nulless_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *   F_data_not if the range to rip is empty.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_string_append().
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_string_append()
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_rip_dynamic_partial_
  extern f_status_t f_rip_dynamic_partial(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_rip_dynamic_partial_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *   F_data_not if the range to rip is empty.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_string_append_nulless().
 *
 *   Errors (with error bit) from: f_string_append_nulless().
 *   Errors (with error bit) from: f_utf_is_combining().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_string_append_nulless()
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_rip_dynamic_partial_nulless_
  extern f_status_t f_rip_dynamic_partial_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_rip_dynamic_partial_nulless_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_rip_h

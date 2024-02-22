/**
 * FLL - Level 1
 *
 * Project: Status
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides status code functions, such as those that translate status codes into strings.
 */
#ifndef _FL_status_string_h
#define _FL_status_string_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/compare.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/parse.h>
#include <fll/level_0/status_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert status codes from their string equivalents to a status code.
 *
 * Error, warning, and signal flags will not be assigned to the error.
 *
 * This processes the string until either a match or NULL is reached.
 *
 * @param name
 *   The status name to process.
 * @param code
 *   The status code a matched string represents.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if string is empty.
 *
 *   F_data (with error bit) if not found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_conversion_character_is_decimal().
 */
#ifndef _di_fl_status_string_from_
  extern f_status_t fl_status_string_from(const f_string_static_t name, f_status_t * const code);
#endif // _di_fl_status_string_from_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_status_string_h

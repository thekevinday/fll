/**
 * FLL - Level 2
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides status code functions, such as those that translate status codes into strings.
 */
#ifndef _FLL_status_h
#define _FLL_status_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/conversion.h>

// fll-1 includes
#include <level_1/string.h>
#include <level_1/status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert status codes from their string equivalents to a status code.
 *
 * Error, warning, and signal flags will not be assigned to the error.
 *
 * This process the string until either a match or NULL is reached.
 *
 * @param string
 *   The error name to process.
 * @param code
 *   The status code a matched string represents.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string is empty.
 *   F_data (with error bit) if not found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_conversion_character_is_decimal().
 */
#ifndef _di_fll_status_from_string_
  extern f_return_status fll_status_from_string(const f_string_t string, f_status_t *code);
#endif // _di_fll_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_status_h

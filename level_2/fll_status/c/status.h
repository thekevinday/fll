/**
 * FLL - Level 2
 *
 * Project: Errors
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides error functions, such as those that translate status codes into strings.
 */
#ifndef _FLL_errors_h
#define _FLL_errors_h

// fll-0 includes
#include <level_0/conversion.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

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
 *   f_none on success.
 *   f_no_data if string is empty.
 *   f_invalid_data (with error bit) if not found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fll_status_from_string_
  extern f_return_status fll_status_from_string(const f_string string, f_status *code);
#endif // _di_fll_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_errors_h

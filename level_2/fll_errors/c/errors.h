/**
 * FLL - Level 2
 *
 * Project: Errors
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides error functions, such as those that translate error codes into strings.
 */
#ifndef _FLL_errors_h
#define _FLL_errors_h

// fll-0 includes
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/strings.h>
#include <level_1/errors.h>

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
 * @param error
 *   The error code a matched string represents.
 *
 * @return
 *   f_none on success.
 *   f_invalid_data if not found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fll_errors_from_string_
  extern f_return_status fll_errors_from_string(const f_string string, f_status *error);
#endif // _di_fll_errors_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_errors_h

/**
 * FLL - Level 2
 *
 * Project: Error
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide functions commonly used by FLL based programs.
 */
#ifndef _FLL_error_h
#define _FLL_error_h

// libc include
#include <stdio.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/color.h>
#include <level_0/file.h>

// fll-1 includes
#include <level_1/string.h>

// fll-2 error includes
#include <level_2/error-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error or warning messages.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_false is returned on successful print of known errors.
 *   F_true is returned if the status code is unknown.
 */
#ifndef _di_fll_error_print_
  extern f_return_status fll_error_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback);
#endif // _di_fll_error_print_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fll_error_file_print_
  extern f_return_status fll_error_file_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type);
#endif // _di_fll_error_file_print_

/**
 * Print integer related error or warning messages.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 * @param parameter
 *   The name of the parameter.
 * @param argument
 *   The argument associated with the given parameter.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fll_error_parameter_integer_print_
  extern f_return_status fll_error_parameter_integer_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t parameter, const f_string_t argument);
#endif // _di_fll_error_parameter_integer_print_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_error_h

/* FLL - Level 2
 * Project:       FSS
 * Version:       0.4.2
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This provides fss error code translation.
 */
#ifndef _FLL_fss_errors_h
#define _FLL_fss_errors_h

// fll-0 includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/memory.h>
#include <level_0/fss.h>

// fll-1 includes
#include <level_1/errors.h>
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_errors.h>
#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_fss_errors_to_string_
  // Convert error codes to their string equivalents.
  f_extern f_return_status fll_fss_errors_to_string(const f_status error, f_string *string);
#endif // _di_fll_errors_to_string_

#ifndef _di_fll_fss_errors_is_error_
  // Returns true or false depending on whether the standard context of the error code represents an error.
  // Keep in mind that many of the error codes are context-specific and may be reported as an error here when it is in fact not an error.
  f_extern f_return_status fll_fss_errors_is_error(const f_status error);
#endif // _di_fll_fss_errors_is_error_

#ifndef _di_fll_fss_errors_is_warning_
  // Returns true or false depending on whether the standard context of the error code represents a warning.
  // Keep in mind that many of the error codes are context-specific and may be reported as a warning here when it is in fact not a warning.
  f_extern f_return_status fll_fss_errors_is_warning(const f_status error);
#endif // _di_fll_fss_errors_is_warning_


#ifndef _di_fll_fss_errors_is_fine_
  // Returns true or false depending on whether the standard context of the error code represents an normal return status and not an error.
  // Keep in mind that many of the error codes are context-specific and may be reported as "fine" here when it is in fact not fine.
  f_extern f_return_status fll_fss_errors_is_fine(const f_status error);
#endif // _di_fll_fss_errors_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_errors_h

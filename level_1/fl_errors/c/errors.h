/* FLL - Level 1
 * Project:       Errors
 * Version:       0.4.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides error functions, such as those that translate error codes into strings.
 */
#ifndef _FL_errors_h
#define _FL_errors_h

// fll-0 includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_errors_to_string_
  // Convert error codes to their string equivalents.
  extern f_return_status fl_errors_to_string(const f_status error, f_string *string);
#endif // _di_fl_errors_to_string_

#ifndef _di_fl_errors_is_error_
  // Returns true or false depending on whether the standard context of the error code represents an error.
  // Keep in mind that many of the error codes are context-specific and may be reported as an error here when it is in fact not an error.
  extern f_return_status fl_errors_is_error(const f_status error);
#endif // _di_fl_errors_is_error_

#ifndef _di_fl_errors_is_warning_
  // Returns true or false depending on whether the standard context of the error code represents a warning.
  // Keep in mind that many of the error codes are context-specific and may be reported as a warning here when it is in fact not a warning.
  extern f_return_status fl_errors_is_warning(const f_status error);
#endif // _di_fl_errors_is_warning_

#ifndef _di_fl_errors_is_fine_
  // Returns true or false depending on whether the standard context of the error code represents an normal return status and not an error.
  // Keep in mind that many of the error codes are context-specific and may be reported as an "fine" here when it is in fact not fine.
  extern f_return_status fl_errors_is_fine(const f_status error);
#endif // _di_fl_errors_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_errors_h

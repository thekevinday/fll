/* FLL - Level 1
 * Project:       Errors
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides error functions, such as those that translate error codes into strings.
 */
#ifndef _FL_errors_h
#define _FL_errors_h

// fll-0 includes
#include <level_0/errors.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_errors_to_string_
  // Convert error codes to their string equivalents.
  extern f_return_status fl_errors_to_string(const f_status error, f_string *string);
#endif // _di_fl_errors_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_errors_h

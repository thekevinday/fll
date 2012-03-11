/* FLL - Level 1
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#ifndef _FL_fss_h
#define _FL_fss_h

// libc includes
#include <string.h>
#include <ctype.h>

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/errors.h>
#include <level_0/types.h>
#include <level_0/fss.h>
#include <level_0/file.h>
#include <level_0/conversion.h>

// fll-1 includes
#include <level_1/fss_errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_identify_
  extern f_return_status fl_fss_identify(const f_dynamic_string buffer, f_fss_header *header);
#endif // _di_fl_fss_identify_

#ifndef _di_fl_fss_identify_file_
  extern f_return_status fl_fss_identify_file(f_file *file_information, f_fss_header *header);
#endif // _di_fl_fss_identify_file_

#ifndef _di_fl_fss_shift_delimiters_
  // This provides a means to shift all of the delimiters to the end of the used buffer
  // This allows one to do a printf on the dynamic string without the delimiters arbitrarily stopping the output
  // No reallocations are performed, this will only shift characters
  extern f_return_status fl_fss_shift_delimiters(f_dynamic_string *buffer, const f_string_location location);
#endif // _di_fl_fss_shift_delimiters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_h

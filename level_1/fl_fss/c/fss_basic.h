/* FLL - Level 1
 * Project:       FSS
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This is the fss-0000 implementation
 */
#ifndef _FL_fss_basic_h
#define _FL_fss_basic_h

// libc includes
#include <string.h>
#include <ctype.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/memory.h>
#include <level_0/fss.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_errors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_object_read_
  // read an fss-0000 object
  f_extern f_return_status fl_fss_basic_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found);
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_content_read_
  // read an fss-0000 content
  f_extern f_return_status fl_fss_basic_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found);
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_object_write_
  // write an fss-0000 object
  f_extern f_return_status fl_fss_basic_object_write(f_dynamic_string *buffer, f_const f_dynamic_string object, f_string_location *input);
#endif // _di_fl_fss_basic_object_write_

#ifndef _di_fl_fss_basic_content_write_
  // write an fss-0000 content
  f_extern f_return_status fl_fss_basic_content_write(f_dynamic_string *buffer, f_const f_dynamic_string content, f_string_location *input);
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_basic_h

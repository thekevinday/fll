/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0001 implementation.
 */
#ifndef _FL_fss_extended_h
#define _FL_fss_extended_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/types.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_object_read_
  /**
   * read an fss-0001 object.
   */
  extern f_return_status fl_fss_extended_object_read(f_string_dynamic *buffer, f_string_location *input, f_fss_object *found);
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_content_read_
  /**
   * read an fss-0001 content.
   */
  extern f_return_status fl_fss_extended_content_read(f_string_dynamic *buffer, f_string_location *input, f_fss_content *found);
#endif // _di_fl_fss_extended_content_read_

#ifndef _di_fl_fss_extended_object_write_
  /**
   * write an fss-0001 object.
   */
  extern f_return_status fl_fss_extended_object_write(const f_string_dynamic object, f_string_location *input, f_string_dynamic *buffer);
#endif // _di_fl_fss_extended_object_write_

#ifndef _di_fl_fss_extended_content_write_
  /**
   * write an fss-0001 content.
   */
  extern f_return_status fl_fss_extended_content_write(const f_string_dynamic content, f_string_location *input, f_string_dynamic *buffer);
#endif // _di_fl_fss_extended_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_extended_h
